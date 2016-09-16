/*
 * main.cpp -
 *
 *   Copyright (c) 2016  Higepon(Masaki Hiromoto)  <hiromoto@hopf.sys.es.osaka-u.ac.jp>
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *   TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  $Id: main.cpp 183 2016-05-19 15:33:28Z higepon $
 */

#include "main.h"

using namespace scheme;

// =================================================================================== //
// [関数の目的]
// 位置情報と走行方向を受け取り
// 描画情報を取得して./../../Data/OtherData/Result/GreedyObject.xml
// に格納する
// =================================================================================== //

// =================================================================================== //

int main(int argc, char *argv[])
{
  // 第二引数はタクシーのID番号の文字列
  if( argc != 2 ) {
    return 0;
  }

  int taxiID = boost::lexical_cast<int>( argv[1] );
  std::string taxiID_str = boost::lexical_cast<std::string>( taxiID );
  // TaxiPosition_ID_(taxiID).xmlの読込み
  GeographicCoordinate gCoor;
  int dir = 1;                  // dir = 1, 2, ..., 9
  {
    boost::property_tree::ptree tree;
    // ----------- 読込ファイル名 ----------- //
    const std::string fileName1 = "TaxiPosition_ID_";
    const std::string fileName2 = ".xml";
    const std::string fileName = fileName1 + taxiID_str + fileName2;
    // -------------------------------------- //
    const std::string fileDire = "./../../Data/OtherData/FromServer/TaxiPosition";
    const std::string file = fileDire + "/" + fileName;
    const int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない(もし読み込みならchild.second.getをchild.second.get_optionalにしないといけない)
    boost::property_tree::read_xml(file, tree, flag);
    {
      // 取得
      dir = tree.get<int>("table.dir");
      // POSITIONを取得する
      std::string sPointStr = tree.get<std::string>("table.position");
      // 空文字の除去
      boost::trim (sPointStr);
      // 文字列から緯度と経度の文字列を抽出
      std::vector<std::string> v;
      boost::algorithm::split(v, sPointStr, boost::is_any_of(","));
      double phi = boost::lexical_cast<double>(v[0]);
      double lambda = boost::lexical_cast<double>(v[1]);
      gCoor.set( phi, lambda );
    }
  }
  // Map.xmlの読込み
  GeographicCoordinate gCoorNW;
  GeographicCoordinate gCoorSE;
  double cellSizePhi = 0;
  double cellSizeLambda = 0;
  int numRow = 0;
  int numCol = 0;
  {
    boost::property_tree::ptree tree;
    // ----------- 読込ファイル名 ----------- //
    const std::string fileName = "Map.xml";
    // -------------------------------------- //
    const std::string fileDire = "./../../Data/OtherData/ProcessedInitialData";
    const std::string file = fileDire + "/" + fileName;
    const int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない(もし読み込みならchild.second.getをchild.second.get_optionalにしないといけない)
    boost::property_tree::read_xml(file, tree, flag);
    {
      // 取得
      double phi = tree.get<double>("table.northWestLatitude");
      double lambda = tree.get<double>("table.northWestLongitude");
      gCoorNW.set( phi, lambda );
      phi = tree.get<double>("table.southEastLatitude");
      lambda = tree.get<double>("table.southEastLongitude");
      gCoorSE.set( phi, lambda );
      cellSizePhi = tree.get<double>("table.cellSizePhi");
      cellSizeLambda = tree.get<double>("table.cellSizeLambda");
      numCol = tree.get<int>("table.numCol");
      numRow = tree.get<int>("table.numRow");
    }
  }
  // タクシー(taxiID)いるセルのindexを計算
  int index = 0;
  int row = calculateRowFromLatitudes( gCoor.getPhi(), gCoorNW.getPhi(), gCoorSE.getPhi(), cellSizePhi );
  int col = calculateColFromLongitudes( gCoor.getLambda(), gCoorNW.getLambda(), gCoorSE.getLambda(), cellSizeLambda );
  index = calculateIndexFromRowCol( row, col, numRow, numCol );
  if( index == 0 ) {
    // 営業領域外なので空のオブジェクト情報を渡す
    try {
      boost::filesystem::path src("./../../Data/OtherData/OtherData/EmptyObjectInfo.xml");
      boost::filesystem::path dst("./../../Data/OtherData/Result/GreedyObject/GreedyObject_ID_" + taxiID_str + ".xml");
        boost::filesystem::copy_file(src, dst, boost::filesystem::copy_option::overwrite_if_exists);
    } catch (std::exception& e) {
      // std::cout << e.what() << std::endl;
    }
  }else{
    // タクシーがindexにいて方向がDir_kのときにターゲットにするindexTargetを読み取る

	  std::cout << "indextTaxi = " << index << std::endl;

    int indexTarget = -1;
    {
      boost::property_tree::ptree tree;
      const std::string file = "./../../Data/OtherData/OtherData/GreedyTarget/Dir_" + boost::lexical_cast<std::string>(dir) + "/index_" + boost::lexical_cast<std::string>(index) + ".xml";
      boost::property_tree::read_xml(file, tree, boost::property_tree::xml_parser::no_comments);
      indexTarget = tree.get<int>("table.target");
    }
	  std::cout << "indextTarget = " << indexTarget << std::endl;
    if( indexTarget == -1 ) {
      // 周囲に需要がない
      try {
  	boost::filesystem::path src("./../../Data/OtherData/OtherData/EmptyObjectInfo.xml");
  	boost::filesystem::path dst("./../../Data/OtherData/Result/GreedyObject/GreedyObject_ID_" + taxiID_str + ".xml");
        boost::filesystem::copy_file(src, dst, boost::filesystem::copy_option::overwrite_if_exists);
      } catch (std::exception& e) {
        // std::cout << e.what() << std::endl;
      }
    }else if( index != indexTarget ) {
      // 周囲に需要が集中している場所がある
      try {
        const std::string file = "./../../Data/OtherData/OtherData/GreedyObjectInfo/Cell_" + boost::lexical_cast<std::string>(index) + "/Vertex_" + boost::lexical_cast<std::string>(indexTarget) + ".xml";
        boost::filesystem::path src(file);
  	boost::filesystem::path dst("./../../Data/OtherData/Result/GreedyObject/GreedyObject_ID_" + taxiID_str + ".xml");
        boost::filesystem::copy_file(src, dst, boost::filesystem::copy_option::overwrite_if_exists);
      } catch (std::exception& e) {
        // std::cout << e.what() << std::endl;
      }
    }else{
      // 今いる場所が需要が集中している
      try {
        const std::string file = "./../../Data/OtherData/OtherData/GreedyObjectInfo/Cell_" + boost::lexical_cast<std::string>(index) + "/Vertex_" + boost::lexical_cast<std::string>(index) + "/Vertex_dir_" + boost::lexical_cast<std::string>(dir) + ".xml";
        boost::filesystem::path src(file);
  	boost::filesystem::path dst("./../../Data/OtherData/Result/GreedyObject/GreedyObject_ID_" + taxiID_str + ".xml");
        boost::filesystem::copy_file(src, dst, boost::filesystem::copy_option::overwrite_if_exists);
      } catch (std::exception& e) {
        // std::cout << e.what() << std::endl;
      }
    }
  }

  return EXIT_SUCCESS;
}

// =================================================================================== //

