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
// ./../../Data/OtherData/FromServer/Data.xmlに乗降車データ
// ./../../Data/OtherData/FromServer/CurrentTimeに現在時刻
// ./../../Data/OtherData/Threshold.xmlに判別パラメータ
// ./../../Data/OtherData/GreedySearchRange/に探索範囲情報
// // ./../../Data/OtherData/Map.xmlに貪欲版のマップ情報
// ./../../Data/OtherData/OtherParameters.xmlに離散時間幅と予測ステップ数
// があるので、これらを利用して各セルiに対して需要が集中しているセルjを計算して
// ./../../Data/OtherData/GreedyTargetInfo/index_i.xml
// に格納する。
// ただし、需要が探索範囲内に全くなければ-1を格納する。
// =================================================================================== //

// =================================================================================== //

int main(void) {
  // Data.xmlの読込み
  boost::property_tree::ptree tree_1;
  {
    // ----------- 読込ファイル名 ----------- //
    const std::string fileName = "Data.xml";
    // -------------------------------------- //
    const std::string fileDire = "./../../Data/OtherData/FromServer";
    const std::string file = fileDire + "/" + fileName;
    const int flag = boost::property_tree::xml_parser::no_comments;
    boost::property_tree::read_xml(file, tree_1, flag);
  }
  // --------------------------------------------------------------- //
  // CurrentTime.xmlの読込み
  boost::posix_time::ptime cTime;
  {
    boost::property_tree::ptree tree;
    // ----------- 読込ファイル名 ----------- //
    const std::string fileName = "CurrentTime.xml";
    // -------------------------------------- //
    const std::string fileDire = "./../../Data/OtherData/FromServer";
    const std::string file = fileDire + "/" + fileName;
    const int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない(もし読み込みならchild.second.getをchild.second.get_optionalにしないといけない)
    boost::property_tree::read_xml(file, tree, flag);
    {
      // 文字列の取得
      std::string timeStr = tree.get<std::string>("table.data.currentTime");
      // 空文字の削除
      boost::trim (timeStr);
      // boost::posix_time::ptime 型に変換
      cTime = boost::posix_time::time_from_string(timeStr);
    }
  }
  // std::cout << cTime << std::endl;
  // --------------------------------------------------------------- //
  // OtherParameters.xmlの読込み
  int discreteTimeWidth = 0;
  int timeHorizon = 0;
  {
    boost::property_tree::ptree tree;
    // ----------- 読込ファイル名 ----------- //
    const std::string fileName = "OtherParameters.xml";
    // -------------------------------------- //
    const std::string fileDire = "./../../Data/OtherData/ProcessedInitialData";
    const std::string file = fileDire + "/" + fileName;
    const int flag = boost::property_tree::xml_parser::no_comments;
    boost::property_tree::read_xml(file, tree, flag);
    {
      // 取得
      discreteTimeWidth = tree.get<int>("table.discreteTimeWidth");
      timeHorizon = tree.get<int>("table.timeHorizon");
    }
  }
  // std::cout << discreteTimeWidth << std::endl;
  // std::cout << timeHorizon << std::endl;
  // --------------------------------------------------------------- //

  // --------------------------------------------------------------- //
  // Map.xmlの読込み
  int numRow = 0;
  int numCol = 0;
  int numCell = 0;
  GeographicCoordinate gCoorNW;
  GeographicCoordinate gCoorSE;
  double cellSizePhi = 0;
  double cellSizeLambda = 0;
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
      numRow = tree.get<int>("table.numRow");
      numCol = tree.get<int>("table.numCol");
      numCell = tree.get<int>("table.numCell");
      cellSizePhi = tree.get<double>("table.cellSizePhi");
      cellSizeLambda = tree.get<double>("table.cellSizeLambda");
      gCoorNW.set( tree.get<double>("table.northWestLatitude"), tree.get<double>("table.northWestLongitude") );
      gCoorSE.set( tree.get<double>("table.southEastLatitude"), tree.get<double>("table.southEastLongitude") );
    }
  }
  // std::cout << numRow << std::endl;
  // std::cout << numCol << std::endl;
  // std::cout << numCell << std::endl;
  // std::cout << cellSizePhi << std::endl;
  // std::cout << cellSizeLambda << std::endl;
  // gCoorNW.print();
  // gCoorSE.print();
  // --------------------------------------------------------------- //

  // データ抽出する期間を定める
  // cTimeの値をdiscreteTimeWidthで丸める.
  boost::posix_time::ptime cTimeRound = roundPTime(cTime, discreteTimeWidth);
  boost::posix_time::ptime cTimeStart = cTimeRound - ( boost::posix_time::seconds( discreteTimeWidth * 60 + discreteTimeWidth * 30 ) );
  boost::posix_time::ptime cTimeEnd = cTimeRound + ( boost::posix_time::seconds( timeHorizon * discreteTimeWidth * 60 + discreteTimeWidth * 30 ) );
  // 1週間前,...weeks週間前のcTimeStartとcTimeEndを求める
  int weeks = 4;
  std::vector<boost::posix_time::ptime> vTimeStart(weeks, cTimeStart);
  std::vector<boost::posix_time::ptime> vTimeEnd(weeks, cTimeEnd);
  for(int i = 0; i < (int)vTimeStart.size(); i++) {
	  vTimeStart[i] -= boost::gregorian::days( 7 * i );
	  vTimeStart[i] -= boost::gregorian::months(1);
	  vTimeEnd[i] -= boost::gregorian::days( 7 * i );
	  vTimeEnd[i] -= boost::gregorian::months(1);
  }

  // Data.xmlから読み込んだtree_1から各セルでの需要数を計算する
  // 需要数をカウントするための動的配列を確保(0で初期化)
  std::vector<int> vDemand(numCell, 0);
  // treeの子ノードを一つづつ読んでいく
  boost::property_tree::ptree::iterator itr_first, itr_last, it;
  itr_first = tree_1.get_child( "table" ).begin();
  itr_last = tree_1.get_child( "table" ).end();

  // メモ
  // TABLE-DATA-ID
  //           -START_DATE
  //           -START_POINT
  //           -END_DATE
  //           -END_POINT

  for(it = itr_first; it != itr_last; it++) {
    // START_POINTを取得する
    std::string sPointStr = it->second.get<std::string>("startPoint");
    // 空文字の除去
    boost::trim (sPointStr);
    // 文字列から緯度と経度の文字列を抽出
    std::vector<std::string> v;
    boost::algorithm::split(v, sPointStr, boost::is_any_of(","));
    double phi = boost::lexical_cast<double>(v[0]);
    double lambda = boost::lexical_cast<double>(v[1]);
    // ( phi, lambda ) -> セル番号index
    int row = calculateRowFromLatitudes( phi, gCoorNW.getPhi(), gCoorSE.getPhi(), cellSizePhi );
    int col = calculateColFromLongitudes( lambda, gCoorNW.getLambda(), gCoorSE.getLambda(), cellSizeLambda );
    int index = calculateIndexFromRowCol( row, col, numRow, numCol );
//    std::cout << "[row, col, index] = [" << row <<", " << col <<", "<< index << "]" << std::endl;
    // 範囲外だとindex = 0になる
    if( index != 0 ) {
      // START_DATEを取得する
      std::string sTimeStr = it->second.get<std::string>("startDate");
      // 空文字の除去
      boost::trim (sTimeStr);
      // boost::posix_time::ptime 型に変換
      boost::posix_time::ptime sTime = boost::posix_time::time_from_string(sTimeStr);
      // Does there exist i s.t. vTimeStart[i] <= sTime < vTimeEnd[i]?
      bool exists = false;
//      std::cout << sTime << std::endl;
      for(int i = 0; i < (int)vTimeStart.size(); i++) {
//    	std::cout << vTimeStart[i] << vTimeEnd[i] << std::endl;
        exists = ( ( vTimeStart[i] <= sTime ) && ( sTime < vTimeEnd[i] ) );
        if( exists == true ) {
//            std::cout << "AAAAAAAAAAAAAAAAAAAAAA" << std::endl;
          break;
        }
      }
      if( exists == true) {
        // 需要数のカウントアップ
        vDemand[ index - 1 ]++;
      }
    }
  }

  std::cout << std::accumulate(vDemand.begin(), vDemand.end(), 0.0) << std::endl;

  for(int i = 0; i < numCell; i++) {
	  std::cout << "index = " << (i+1) << ", demand = " << vDemand[i] << std::endl;
  }



  // vDemandの取得が完了
  // 各セルが目指すターゲットのセルを探索範囲内から見つける
  // ターゲットのセルを格納する動的配列の確保
  // -1はターゲット無しということ
  for(int k = 1; k <= 9; k++) {
    std::vector<int> vTarget(numCell, -1);
    for(int i = 0; i < (int)vTarget.size(); i++) {
      int indexTaxi = i+1;
      // indexTaxiの場所における探索範囲の取得
      // ./../../Data/OtherData/GreedySearchRange/Range_(indexTaxi).xml の読込み
      boost::property_tree::ptree tree;
      {
	// ----------- 読込ファイル名 ----------- //
	const std::string fileName = "Range_" + boost::lexical_cast<std::string>(indexTaxi) + ".xml";
	// -------------------------------------- //
	const std::string fileDire = "./../../Data/OtherData/OtherData/GreedySearchRange/Dir_" + boost::lexical_cast<std::string>(k);
	const std::string file = fileDire + "/" + fileName;
	const int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない(もし読み込みならchild.second.getをchild.second.get_optionalにしないといけない)
	boost::property_tree::read_xml(file, tree, flag);
      }
      //
      boost::property_tree::ptree::iterator itr_first, itr_last, it;
      itr_first = tree.get_child( "table" ).begin();
      itr_last = tree.get_child( "table" ).end();
      for(it = itr_first; it != itr_last; it++) {
	// すでに距離についてはソート済み
	int indexTarget = it->second.get<int>("index");
	int demandTarget = vDemand[ indexTarget - 1 ];
	if( demandTarget != 0 ) {
	  vTarget[ i ] = indexTarget;
	  break;
	}
      }
    }
    // vTargetの保存
    const std::locale loc = std::locale();
    const boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
    for(int i = 0; i < (int)vTarget.size(); i++) {
      const std::string fileName_write = "index_" + boost::lexical_cast<std::string>(i+1) + ".xml";
      const std::string fileDire_write = "./../../Data/OtherData/OtherData/GreedyTarget/Dir_" + boost::lexical_cast<std::string>(k);
      const std::string fileRela = fileDire_write + "/" + fileName_write;
      // xmlのtreeの新規作成
      boost::property_tree::ptree tree_write;
      tree_write.put("table.target", vTarget[i]);
      boost::property_tree::xml_parser::write_xml( fileRela, tree_write, loc, settings );
    }
  }

  return EXIT_SUCCESS;
}
// =================================================================================== //



// =================================================================================== //



