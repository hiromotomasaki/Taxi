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
// InitialDataフォルダの中にあるxmlファイルを読み込む。
// そして再編集をしたり、これらのデータから自動で生成できる以後のプログラムで利用可能なファイルを作成したりして、Dataフォルダ内のOtherData以下のフォルダに保存する。
// =================================================================================== //

// =================================================================================== //

int main(void) {
  // Data/OtherData/FromServer Data/OtherData/ProcessedInitialData Data/OtherData/OtherData Data/OtherData/Result
  // のフォルダの作成
  {
    {
      std::string fileDire = "./../../Data/OtherData/FromServer";
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      const bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
      }
    }
    {
      std::string fileDire = "./../../Data/OtherData/ProcessedInitialData";
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      const bool result = boost::filesystem::create_directories(path, error);
	if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
      }
    }
    {
      std::string fileDire = "./../../Data/OtherData/Result";
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
      }
    }
    {
      std::string fileDire = "./../../Data/OtherData/OtherData";
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
      }
    }
  }
  // Data/OtherData/Result/GreedyObject Data/OtherData/Result/RationalObject
  // のフォルダの作成
  {
    {
      std::string fileDire = "./../../Data/OtherData/Result/GreedyObject";
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
      }
    }
    {
      std::string fileDire = "./../../Data/OtherData/Result/RationalObject";
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
      }
    }
  }
  // Data/OtherData/OtherData/GreedyObjectInfo Data/OtherData/OtherData/GreedySearchRange Data/OtherData/OtherData/GreedyTarget Data/OtherData/OtherData/RationalObjectInfo Data/OtherData/OtherData/RationalSearchRange Data/OtherData/OtherData/RationalTarget Data/OtherData/OtherData/Neural
  // のフォルダの作成
  {
    {
      std::string fileDire = "./../../Data/OtherData/OtherData/GreedyObjectInfo";
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
      }
    }
    {
      std::string fileDire = "./../../Data/OtherData/OtherData/GreedySearchRange";
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
      }
    }
    {
      std::string fileDire = "./../../Data/OtherData/OtherData/GreedyTarget";
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
      }
    }
    {
      std::string fileDire = "./../../Data/OtherData/OtherData/RationalObjectInfo";
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
      }
    }
    {
      std::string fileDire = "./../../Data/OtherData/OtherData/RationalSearchRange";
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
      }
    }
    {
      std::string fileDire = "./../../Data/OtherData/OtherData/RationalTarget";
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
      }
    }
    {
      std::string fileDire = "./../../Data/OtherData/OtherData/Neural";
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
      }
    }
  }
  // Data/OtherData/OtherData/GreedySearchRange/Dir_i
  // のフォルダの作成
  {
    {
      for (int i = 1 ; i <= 9; i++) {
	std::string fileDire = "./../../Data/OtherData/OtherData/GreedySearchRange/Dir_" + boost::lexical_cast<std::string>( i );
	boost::filesystem::path path(fileDire);
	boost::system::error_code error;
	bool result = boost::filesystem::create_directories(path, error);
	if (!result || error) {
	  std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
	}
      }
    }
  }
  // Data/OtherData/OtherData/GreedyTarget/Dir_i
  // のフォルダの作成
  {
    {
      for (int i = 1 ; i <= 9; i++) {
	std::string fileDire = "./../../Data/OtherData/OtherData/GreedyTarget/Dir_" + boost::lexical_cast<std::string>( i );
	boost::filesystem::path path(fileDire);
	boost::system::error_code error;
	bool result = boost::filesystem::create_directories(path, error);
	if (!result || error) {
	  std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
	}
      }
    }
  }
  // Data/OtherData/FromServer/TaxiPotition
  // のフォルダの作成
  {
    {
      std::string fileDire = "./../../Data/OtherData/FromServer/TaxiPosition";
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
      }
    }
  }

  // 空のファイル, EmptyNeuralCirclePositions.xmlとEmptyObjectInfo.xmlをData/OtherData/OtherDataに作成
  {
    {
      std::string fileName = "EmptyNeuralCirclePositions.xml";
      std::string fileDire = "./../../Data/OtherData/OtherData";
      // 保存先
      std::string fileRela = fileDire + "/" + fileName;
      // xmlのtreeの新規作成
      boost::property_tree::ptree tree;
      // treeのノードの追加
      {
  	tree.put( "table.data.position", "-1,-1" );
      }
      // 保存
      {
  	std::locale loc = std::locale();
  	boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
  	boost::property_tree::xml_parser::write_xml( fileRela, tree, loc, settings );
      }
    }
    {
      std::string fileName = "EmptyObjectInfo.xml";
      std::string fileDire = "./../../Data/OtherData/OtherData";
      // 保存先
      std::string fileRela = fileDire + "/" + fileName;
      // xmlのtreeの新規作成
      boost::property_tree::ptree tree;
      // treeのノードの追加
      {
  	tree.put( "table.latitude1", -1 );
  	tree.put( "table.longitude1", -1 );
  	tree.put( "table.latitude2", -1 );
  	tree.put( "table.longitude2", -1 );
      }
      // 保存
      {
  	std::locale loc = std::locale();
  	boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
  	boost::property_tree::xml_parser::write_xml( fileRela, tree, loc, settings );
      }
    }
  }

  // 設定ファイルの加工と移動
  {
    createMap();
    createRationalMap();
    createNeighborhood();
    createThreshold();
    createOtherParameters();
  }
  // その他必要なファイルを生成
  {
    createMapRepresentativePoints();
    createGreedySearchRange();
    createGreedyObjectInfo();

    createRationalMapRepresentativePoints();
    createRationalSearchRange();
    createRationalObjectInfo();
  }

  return EXIT_SUCCESS;
}
// =================================================================================== //

// =================================================================================== //
int createMap() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName_read = "Map.xml";
  std::string fileDire_read = "./../../Data/InitialData";
  std::string fileName_write = "Map.xml";
  std::string fileDire_write = "./../../Data/OtherData/ProcessedInitialData";
  // ------------------------------------ //
  // 読み込まれるもの
  double northWestLatitude = 0;
  double northWestLongitude = 0;
  double southEastLatitude = 0;
  double southEastLongitude = 0;
  int cellSizeMeter = 0;

  std::cout << fileName_read << "の読込開始" << std::endl;
  {
    // 読込先
    std::string fileRela = fileDire_read + "/" + fileName_read;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
    // 取得
    boost::property_tree::read_xml(fileRela, tree, flag);
    {
      northWestLatitude = tree.get<double>("table.northWestLatitude");
      northWestLongitude = tree.get<double>("table.northWestLongitude");
      southEastLatitude = tree.get<double>("table.southEastLatitude");
      southEastLongitude = tree.get<double>("table.southEastLongitude");
      cellSizeMeter = tree.get<int>("table.cellSizeMeter");
    }
  }
  std::cout << fileName_read << "の読込終了" << std::endl;

  std::cout << fileName_write << "の作成開始" << std::endl;
  {
    // 読み込まれたものを用いて指定された営業領域を含む新たな営業領域の範囲を定める。
    GeographicCoordinate gCoorNW( northWestLatitude, northWestLongitude );
    GeographicCoordinate gCoorSE( southEastLatitude, southEastLongitude );
    // gCoorNWをデカルト座標系の原点にした時のgCoorSEのデカルト座標系での位置を求める。
    CartesianCoordinate cCoorSE = convertGCoorIntoCCoor( gCoorSE, gCoorNW );
    // デカルト座標系で定義された営業領域に対して北から南まで一辺cellSizeMeterの格子を敷き詰めていくと、何枚で営業領域の南北を埋めることができるのか計算する。
    int numRow = ceil( fabs( cCoorSE.getX() ) / cellSizeMeter ); // 絶対値の小数切り上げ
    // デカルト座標系で定義された営業領域に対して西から東まで一辺cellSizeMeterの格子を敷き詰めていくと、何枚で営業領域の東西を埋めることができるのか計算する。
    int numCol = ceil( fabs( cCoorSE.getY() ) / cellSizeMeter ); // 絶対値の小数切り上げ
    int numCell = numRow * numCol;
    // 営業領域の新しい最南東位置に置き換える(デカルト座標)
    cCoorSE.set( (const double)( - numRow * cellSizeMeter ), (const double)( numCol * cellSizeMeter ) );
    // 営業領域の新しい最南東位置に置き換える(地理座標)
    gCoorSE = convertCCoorIntoGCoor( cCoorSE, gCoorNW );
    // 緯度(latitude)方向, 経度(longitude)方向のcellSizeを計算
    double cellSizePhi = (gCoorNW.getPhi() - gCoorSE.getPhi()) / (double)numRow;
    double cellSizeLambda = (gCoorSE.getLambda() - gCoorNW.getLambda()) / (double)numCol;
    // 書き込みを行う
    {
      // 保存先
      std::string fileRela = fileDire_write + "/" + fileName_write;
      // xmlのtreeの新規作成
      boost::property_tree::ptree tree;
      // treeのノードの追加
      {
        tree.put( "table.northWestLatitude", gCoorNW.getPhi() );
        tree.put( "table.northWestLongitude", gCoorNW.getLambda() );
        tree.put( "table.southEastLatitude", gCoorSE.getPhi() );
        tree.put( "table.southEastLongitude", gCoorSE.getLambda() );
        tree.put( "table.cellSizeMeter", cellSizeMeter );
        tree.put( "table.numRow", numRow );
        tree.put( "table.numCol", numCol );
        tree.put( "table.numCell", numCell );
        tree.put( "table.cellSizePhi", cellSizePhi );
        tree.put( "table.cellSizeLambda", cellSizeLambda );
      }
      // 保存
      {
        std::locale loc = std::locale();
        boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
        boost::property_tree::xml_parser::write_xml( fileRela, tree, loc, settings );
      }
    }
  }
  std::cout << fileName_write << "の作成終了" << std::endl;

  return EXIT_SUCCESS;
}
int createRationalMap() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName_read = "RationalMap.xml";
  std::string fileDire_read = "./../../Data/InitialData";
  std::string fileName_write = "RationalMap.xml";
  std::string fileDire_write = "./../../Data/OtherData/ProcessedInitialData";
  // ------------------------------------ //
  // 読み込まれるもの
  double northWestLatitude = 0;
  double northWestLongitude = 0;
  double southEastLatitude = 0;
  double southEastLongitude = 0;
  int cellSizeMeter = 0;

  std::cout << fileName_read << "の読込開始" << std::endl;
  {
    // 読込先
    std::string fileRela = fileDire_read + "/" + fileName_read;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
    // 取得
    boost::property_tree::read_xml(fileRela, tree, flag);
    {
      northWestLatitude = tree.get<double>("table.northWestLatitude");
      northWestLongitude = tree.get<double>("table.northWestLongitude");
      southEastLatitude = tree.get<double>("table.southEastLatitude");
      southEastLongitude = tree.get<double>("table.southEastLongitude");
      cellSizeMeter = tree.get<int>("table.cellSizeMeter");
    }
  }
  std::cout << fileName_read << "の読込終了" << std::endl;

  std::cout << fileName_write << "の作成開始" << std::endl;
  {
    // 読み込まれたものを用いて指定された営業領域を含む新たな営業領域の範囲を定める。
    GeographicCoordinate gCoorNW( northWestLatitude, northWestLongitude );
    GeographicCoordinate gCoorSE( southEastLatitude, southEastLongitude );
    // gCoorNWをデカルト座標系の原点にした時のgCoorSEのデカルト座標系での位置を求める。
    CartesianCoordinate cCoorSE = convertGCoorIntoCCoor( gCoorSE, gCoorNW );
    // デカルト座標系で定義された営業領域に対して北から南まで一辺cellSizeMeterの格子を敷き詰めていくと、何枚で営業領域の南北を埋めることができるのか計算する。
    int numRow = ceil( fabs( cCoorSE.getX() ) / cellSizeMeter ); // 絶対値の小数切り上げ
    // デカルト座標系で定義された営業領域に対して西から東まで一辺cellSizeMeterの格子を敷き詰めていくと、何枚で営業領域の東西を埋めることができるのか計算する。
    int numCol = ceil( fabs( cCoorSE.getY() ) / cellSizeMeter ); // 絶対値の小数切り上げ
    int numCell = numRow * numCol;
    // 営業領域の新しい最南東位置に置き換える(デカルト座標)
    cCoorSE.set( (const double)( - numRow * cellSizeMeter ), (const double)( numCol * cellSizeMeter ) );
    // 営業領域の新しい最南東位置に置き換える(地理座標)
    gCoorSE = convertCCoorIntoGCoor( cCoorSE, gCoorNW );
    // 緯度(latitude)方向, 経度(longitude)方向のcellSizeを計算
    double cellSizePhi = (gCoorNW.getPhi() - gCoorSE.getPhi()) / (double)numRow;
    double cellSizeLambda = (gCoorSE.getLambda() - gCoorNW.getLambda()) / (double)numCol;
    // 書き込みを行う
    {
      // 保存先
      std::string fileRela = fileDire_write + "/" + fileName_write;
      // xmlのtreeの新規作成
      boost::property_tree::ptree tree;
      // treeのノードの追加
      {
        tree.put( "table.northWestLatitude", gCoorNW.getPhi() );
        tree.put( "table.northWestLongitude", gCoorNW.getLambda() );
        tree.put( "table.southEastLatitude", gCoorSE.getPhi() );
        tree.put( "table.southEastLongitude", gCoorSE.getLambda() );
        tree.put( "table.cellSizeMeter", cellSizeMeter );
        tree.put( "table.numRow", numRow );
        tree.put( "table.numCol", numCol );
        tree.put( "table.numCell", numCell );
        tree.put( "table.cellSizePhi", cellSizePhi );
        tree.put( "table.cellSizeLambda", cellSizeLambda );
      }
      // 保存
      {
        std::locale loc = std::locale();
        boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
        boost::property_tree::xml_parser::write_xml( fileRela, tree, loc, settings );
      }
    }
  }
  std::cout << fileName_write << "の作成終了" << std::endl;

  return EXIT_SUCCESS;
}
int createNeighborhood() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName_read = "Neighborhood.xml";
  std::string fileDire_read = "./../../Data/InitialData";
  std::string fileName_write = "Neighborhood.xml";
  std::string fileDire_write = "./../../Data/OtherData/ProcessedInitialData";
  // ------------------------------------ //
  // コピー元
  std::string fileRela_read = fileDire_read + "/" + fileName_read;
  // コピー先
  std::string fileRela_write = fileDire_write + "/" + fileName_write;
  std::cout << fileRela_read << "をコピーします" << std::endl;
  try {
    boost::filesystem::copy_file(fileRela_read, fileRela_write, boost::filesystem::copy_option::overwrite_if_exists);
  }
  catch (boost::filesystem::filesystem_error& ex) {
    std::cout << ex.what() << std::endl;
    throw;
  }
  std::cout << fileRela_write << "にコピーしました" << std::endl;

  return EXIT_SUCCESS;
}
int createThreshold() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName_read = "Threshold.xml";
  std::string fileDire_read = "./../../Data/InitialData";
  std::string fileName_write = "Threshold.xml";
  std::string fileDire_write = "./../../Data/OtherData/ProcessedInitialData";
  // ------------------------------------ //
  // コピー元
  std::string fileRela_read = fileDire_read + "/" + fileName_read;
  // コピー先
  std::string fileRela_write = fileDire_write + "/" + fileName_write;
  std::cout << fileRela_read << "をコピーします" << std::endl;
  try {
    boost::filesystem::copy_file(fileRela_read, fileRela_write, boost::filesystem::copy_option::overwrite_if_exists);
  }
  catch (boost::filesystem::filesystem_error& ex) {
    std::cout << ex.what() << std::endl;
    throw;
  }
  std::cout << fileRela_write << "にコピーしました" << std::endl;

  return EXIT_SUCCESS;
}
int createOtherParameters() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName_read = "OtherParameters.xml";
  std::string fileDire_read = "./../../Data/InitialData";
  std::string fileName_write = "OtherParameters.xml";
  std::string fileDire_write = "./../../Data/OtherData/ProcessedInitialData";
  // ------------------------------------ //
  // コピー元
  std::string fileRela_read = fileDire_read + "/" + fileName_read;
  // コピー先
  std::string fileRela_write = fileDire_write + "/" + fileName_write;
  std::cout << fileRela_read << "をコピーします" << std::endl;
  try {
    boost::filesystem::copy_file(fileRela_read, fileRela_write, boost::filesystem::copy_option::overwrite_if_exists);
  }
  catch (boost::filesystem::filesystem_error& ex) {
    std::cout << ex.what() << std::endl;
    throw;
  }
  std::cout << fileRela_write << "にコピーしました" << std::endl;

  return EXIT_SUCCESS;
}

int createMapRepresentativePoints() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName = "MapRepresentativePoints.xml";
  std::string fileDire = "./../../Data/OtherData/OtherData";
  std::string fileName_read = "Map.xml";
  std::string fileDire_read = "./../../Data/OtherData/ProcessedInitialData";
  // ------------------------------------ //
  // int numRow = 0;
  int numCol = 0;
  int numCell = 0;
  GeographicCoordinate gCoorNW;
  GeographicCoordinate gCoorSE;
  double cellSizePhi = 0;
  double cellSizeLambda = 0;
  // ファイル作成に必要なデータを取得
  {
    // 読込先
    std::string fileRela_read = fileDire_read + "/" + fileName_read;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
    // 取得
    boost::property_tree::read_xml(fileRela_read, tree, flag);
    // numRow = tree.get<int>("table.numRow");
    numCol = tree.get<int>("table.numCol");
    numCell = tree.get<int>("table.numCell");
    cellSizePhi = tree.get<double>("table.cellSizePhi");
    cellSizeLambda = tree.get<double>("table.cellSizeLambda");
    gCoorNW.set( tree.get<double>("table.northWestLatitude"), tree.get<double>("table.northWestLongitude") );
    gCoorSE.set( tree.get<double>("table.southEastLatitude"), tree.get<double>("table.southEastLongitude") );
  }
  std::cout << fileName << "の作成開始" << std::endl;
  {
    // 代表点ベクトルの生成
    std::vector<GeographicCoordinate> vRepresentativePoint(numCell);
    std::vector<int> vRow(numCell);
    std::vector<int> vCol(numCell);
    // 値を求める
    {
      std::vector<GeographicCoordinate>::iterator it, itr_first, itr_last;
      itr_first = vRepresentativePoint.begin();
      itr_last = vRepresentativePoint.end();
      for(it = itr_first; it != itr_last; it++) {
        std::size_t index = std::distance(itr_first, it); // std::distance(itr_first, itr_first) == 0
        int row = calculateRowFromIndex( index + 1, numCol, numCell );
        vRow[index] = row;
        int col = calculateColFromIndex( index + 1, numCol, numCell );
        vCol[index] = col;
        vRepresentativePoint[index].setPhi( gCoorNW.getPhi() - row * cellSizePhi + cellSizePhi / 2.0 );
        vRepresentativePoint[index].setLambda( gCoorNW.getLambda() + col * cellSizeLambda - cellSizeLambda / 2.0 );
      }
    }
    // 保存先
    std::string fileRela = fileDire + "/" + fileName;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    // treeのノードの追加
    {
      std::vector<GeographicCoordinate>::iterator it, itr_first, itr_last;
      itr_first = vRepresentativePoint.begin();
      itr_last = vRepresentativePoint.end();
      for(it = itr_first; it != itr_last; it++) {
        std::size_t index = std::distance(itr_first, it);
        boost::property_tree::ptree childTree;
        childTree.put("index", index+1);
        childTree.put("row", vRow[index]);
        childTree.put("col", vCol[index]);
        childTree.put("latitude", vRepresentativePoint[index].getPhi());
        childTree.put("longitude", vRepresentativePoint[index].getLambda());
        tree.add_child("table.cell", childTree);
      }
    }
    // 保存
    {
      std::locale loc = std::locale();
      boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
      boost::property_tree::xml_parser::write_xml( fileRela, tree, loc, settings );
    }
  }
  std::cout << fileName << "の作成終了" << std::endl;
  return EXIT_SUCCESS;
}
int createGreedySearchRange() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName = "Range"; // あとでfilename + "_" + i + ".xml"をする
  std::string fileDire = "./../../Data/OtherData/OtherData/GreedySearchRange/Dir_"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  std::string fileName_read = "Neighborhood.xml";
  std::string fileDire_read = "./../../Data/OtherData/ProcessedInitialData"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  std::string fileName_read_2 = "Map.xml";
  std::string fileDire_read_2 = "./../../Data/OtherData/ProcessedInitialData"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  std::string fileName_read_3 = "MapRepresentativePoints.xml";
  std::string fileDire_read_3 = "./../../Data/OtherData/OtherData"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  // ------------------------------------ //
  std::cout << "Dir_1/Range_(i+1).xmlの作成開始" << std::endl;
  int neighborhoodLongDistance = 0;
  // ファイル作成に必要なデータを取得
  {
    // 読込先
    std::string fileRela_read = fileDire_read + "/" + fileName_read;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
    // 取得
    boost::property_tree::read_xml(fileRela_read, tree, flag);
    neighborhoodLongDistance = tree.get<int>( "table.neighborhoodLongDistance" );
  }
  int numCell = 0;
  {
    // 読込先
    std::string fileRela_read = fileDire_read_2 + "/" + fileName_read_2;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
    // 取得
    boost::property_tree::read_xml(fileRela_read, tree, flag);
    numCell = tree.get<int>( "table.numCell" );
  }
  // 代表点ベクトルの読込み
  std::vector<GeographicCoordinate> vRepresentativePoint(numCell);
  std::vector<int> vRow(numCell);
  std::vector<int> vCol(numCell);
  {
    // 読込先
    std::string fileRela_read = fileDire_read_3 + "/" + fileName_read_3;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
    // 取得
    boost::property_tree::read_xml(fileRela_read, tree, flag);
    boost::property_tree::ptree childTree = tree.get_child("table");
    boost::property_tree::ptree::iterator itr_first, itr_last, it;
    itr_first = childTree.begin();
    itr_last = childTree.end();
    for(it = itr_first; it != itr_last; it++) {
      std::size_t index = std::distance(itr_first, it); // std::distance(itr_first, itr_first) == 0
      vRepresentativePoint[index].set( it->second.get<double>("latitude"), it->second.get<double>("longitude") );
      vRow[index] = it->second.get<int>("row");
      vCol[index] = it->second.get<int>("col");
    }
  }
  // 辞書式ソートができるように構造体を宣言し、ソートの規則をクラスで書く
  struct PairIndexTSTation {
    int index;
    TotalStation tStation;
  };
  class MyLessDefinition {
  public:
    bool operator()(const PairIndexTSTation& a, const PairIndexTSTation& b)
    {
      if( a.tStation.getLength() == b.tStation.getLength() ) {
        if( a.tStation.getAzimuth() == b.tStation.getAzimuth() ) {
          return a.index < b.index;
        }else{
          return a.tStation.getAzimuth() < b.tStation.getAzimuth();
        }
      }else{
        return a.tStation.getLength() < b.tStation.getLength();
      }
      return a.tStation.getLength() < b.tStation.getLength();
    }
  };
  // Range_(i+1).xmlの作成
  for (int i = 0; i < numCell; i++) {
    // 保存先
    int k = 1;
    std::string fileRela = fileDire + boost::lexical_cast<std::string>(k) + "/" + fileName + "_" + boost::lexical_cast<std::string>(i+1) + ".xml";
    // validCellsを求める
    std::vector<PairIndexTSTation> vPairIndexTSTation;
    for (int j = 0; j < numCell; j++) {
      PairIndexTSTation pairHoge;
      // セル(i+1)からセル(j+1)への測地線長と方位角を取得する
      pairHoge.tStation = calculateTStationFromGCoor( vRepresentativePoint[i], vRepresentativePoint[j] );
      bool isWithinNeighborhood = ( pairHoge.tStation.getLength() <= neighborhoodLongDistance );
      if( isWithinNeighborhood ) {
        // 有効セルのindexを取得
        pairHoge.index = j+1;
        // 有効セルの情報ベクトルへプッシュ
        vPairIndexTSTation.push_back(pairHoge);
      }
    }
    // 第一辞書を測地線長, 第二辞書を方位角, 第三辞書をindexとしてソート
    {
      std::vector<PairIndexTSTation>::iterator it, itr_first, itr_last;
      itr_first = vPairIndexTSTation.begin();
      itr_last = vPairIndexTSTation.end();
      sort(itr_first, itr_last, MyLessDefinition());
    }
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    {
      std::vector<PairIndexTSTation>::iterator it, itr_first, itr_last;
      itr_first = vPairIndexTSTation.begin();
      itr_last = vPairIndexTSTation.end();
      for(it = itr_first; it != itr_last; it++) {
        std::size_t index = std::distance(itr_first, it); // std::distance(itr_first, itr_first) == 0
        boost::property_tree::ptree childTree;
        childTree.put("index", vPairIndexTSTation[index].index);
        childTree.put("length", vPairIndexTSTation[index].tStation.getLength());
        childTree.put("azimuth", vPairIndexTSTation[index].tStation.getAzimuth());
        tree.add_child("table.cell", childTree);
      }
    }
    // 保存
    {
      std::locale loc = std::locale();
      boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
      boost::property_tree::xml_parser::write_xml( fileRela, tree, loc, settings );
    }
  }
  std::cout << "Dir_1/Range_(i+1).xmlの作成終了" << std::endl;
  std::cout << "Dir_k/Range_(i+1).xmlの作成開始" << std::endl;
  double azi[8][2] = {
    { 270, 90 },
    { 270 + 45, 90 + 45 },
    { 0, 180 },
    { 0 + 45, 180 + 45 },
    { 0 + 45*2, 180 + 45*2 },
    { 0 + 45*3, 180 + 45*3 },
    { 0 + 45*4, 180 + 45*4 },
    { 0 + 45*5, 45 },
  };
  for (int k = 2; k <= 9; k++) {
    for (int i = 0; i < numCell; i++) {
      // 読込先
      std::string fileRela_read = fileDire + boost::lexical_cast<std::string>(1) + "/" + fileName + "_" + boost::lexical_cast<std::string>(i+1) + ".xml";
      // 保存先
      std::string fileRela_write = fileDire + boost::lexical_cast<std::string>(k) + "/" + fileName + "_" + boost::lexical_cast<std::string>(i+1) + ".xml";
      // 読み込む
      boost::property_tree::ptree tree_1;
      {
  	std::string file = fileRela_read;
  	int flag = boost::property_tree::xml_parser::no_comments;
  	boost::property_tree::read_xml(file, tree_1, flag);
      }
      // tree_1から方向に対して有効なデータを抽出
      std::vector<PairIndexTSTation> vPairIndexTSTation;
      {
	boost::property_tree::ptree::iterator itr_first, itr_last, it;
	itr_first = tree_1.get_child( "table" ).begin();
	itr_last = tree_1.get_child( "table" ).end();
	for(it = itr_first; it != itr_last; it++) {
	  double azimuth = it->second.get<double>("azimuth");
	  bool isWithinValidResion = false;
	  if( k == 2 || k == 3 || k == 9 ) {
	    isWithinValidResion = ( azimuth >= azi[k-2][0] || azimuth < azi[k-2][1] ) || ( it == itr_first );
	  }else{
	    isWithinValidResion = ( azimuth >= azi[k-2][0] && azimuth < azi[k-2][1] ) || ( it == itr_first );
	  }
	  if( isWithinValidResion ) {
	    // Dir_kに対して有効な方向
	    int index = it->second.get<int>("index");
	    double length = it->second.get<double>("length");
	    PairIndexTSTation pairHoge;
	    pairHoge.index = index;
	    pairHoge.tStation.set(length, azimuth);
	    // 有効セルの情報ベクトルへプッシュ
	    vPairIndexTSTation.push_back(pairHoge);
	  }
	}
      }
      // xmlのtreeの新規作成
      boost::property_tree::ptree tree;
      {
      	std::vector<PairIndexTSTation>::iterator it, itr_first, itr_last;
      	itr_first = vPairIndexTSTation.begin();
      	itr_last = vPairIndexTSTation.end();
      	for(it = itr_first; it != itr_last; it++) {
      	  std::size_t index = std::distance(itr_first, it); // std::distance(itr_first, itr_first) == 0
      	  boost::property_tree::ptree childTree;
      	  childTree.put("index", vPairIndexTSTation[index].index);
      	  childTree.put("length", vPairIndexTSTation[index].tStation.getLength());
      	  childTree.put("azimuth", vPairIndexTSTation[index].tStation.getAzimuth());
      	  tree.add_child("table.cell", childTree);
      	}
      }
      // 保存
      {
      	std::locale loc = std::locale();
      	boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
      	boost::property_tree::xml_parser::write_xml( fileRela_write, tree, loc, settings );
      }
    }
  }
  std::cout << "Dir_k/Range_(i+1).xmlの作成終了" << std::endl;
  return EXIT_SUCCESS;
}
int createGreedyObjectInfo() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName_read_1 = "Map.xml";
  std::string fileDire_read_1 = "./../../Data/OtherData/ProcessedInitialData"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  std::string fileName_read_2 = "Neighborhood.xml";
  std::string fileDire_read_2 = "./../../Data/OtherData/ProcessedInitialData"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  std::string fileName_read_3 = "MapRepresentativePoints.xml";
  std::string fileDire_read_3 = "./../../Data/OtherData/OtherData"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  std::string fileName_read_4 = "Range"; // あとでfilename + "_" + i + ".xml"をする
  std::string fileDire_read_4 = "./../../Data/OtherData/OtherData/GreedySearchRange/Dir_1"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  // ------------------------------------ //
  std::cout << "オブジェクト情報の作成開始" << std::endl;

  // 営業領域の最北西を取得, Map.xml
  GeographicCoordinate gCoorNW;
  int numCell;
  {
    // 読込先
    std::string fileRela_read = fileDire_read_1 + "/" + fileName_read_1;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
    // 取得
    boost::property_tree::read_xml(fileRela_read, tree, flag);
    gCoorNW.set( tree.get<double>("table.northWestLatitude"), tree.get<double>("table.northWestLongitude") );
    numCell = tree.get<int>("table.numCell");
  }
  // 近傍の定義と描画ルールを取得, Neighborhood.xml
  int neighborhoodLongDistance = 0;
  int cellSizeMeterForLongDistance = 0;
  int neighborhoodMiddleDistance = 0;
  int cellSizeMeterForMiddleDistance = 0;
  int neighborhoodShortDistance = 0;
  int cellSizeMeterForShortDistance = 0;
  {
    // 読込先
    std::string fileRela_read = fileDire_read_2 + "/" + fileName_read_2;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
    // 取得
    boost::property_tree::read_xml(fileRela_read, tree, flag);
    neighborhoodLongDistance = tree.get<int>("table.neighborhoodLongDistance");
    cellSizeMeterForLongDistance = tree.get<int>("table.cellSizeMeterForLongDistance");
    neighborhoodMiddleDistance = tree.get<int>("table.neighborhoodMiddleDistance");
    cellSizeMeterForMiddleDistance = tree.get<int>("table.cellSizeMeterForMiddleDistance");
    neighborhoodShortDistance = tree.get<int>("table.neighborhoodShortDistance");
    cellSizeMeterForShortDistance = tree.get<int>("table.cellSizeMeterForShortDistance");
  }
  // 各セルの代表点を取得, MapRepresentativePoints.xml
  std::vector<GeographicCoordinate> vRepresentativePoint(numCell);
  {
    // 読込先
    std::string fileRela_read = fileDire_read_3 + "/" + fileName_read_3;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
    // 取得
    boost::property_tree::read_xml(fileRela_read, tree, flag);
    boost::property_tree::ptree childTree = tree.get_child("table");
    boost::property_tree::ptree::iterator itr_first, itr_last, it;
    itr_first = childTree.begin();
    itr_last = childTree.end();
    for(it = itr_first; it != itr_last; it++) {
      std::size_t index = std::distance(itr_first, it); // std::distance(itr_first, itr_first) == 0
      vRepresentativePoint[index].set( it->second.get<double>("latitude"), it->second.get<double>("longitude") );
    }
  }
  // 描画オブジェクトを求めるのにデカルト座標系式の代表点の情報が必要
  std::vector<CartesianCoordinate> vCCoorRepresentativePoint(numCell);
  // RepresentativePointを元にvCCoorRepresentativePointを作成する
  {
    std::vector<GeographicCoordinate>::iterator it, itr_first, itr_last;
    itr_first = vRepresentativePoint.begin();
    itr_last = vRepresentativePoint.end();
    for(it = itr_first; it != itr_last; it++) {
      std::size_t i = std::distance(itr_first, it); // std::distance(itr_first, itr_first) == 0
      vCCoorRepresentativePoint[i] = convertGCoorIntoCCoor( vRepresentativePoint[i], gCoorNW );
    }
  }
  // 構造体を宣言
  struct PairIndexTSTation {
    int index;
    TotalStation tStation;
  };
  // 描画情報を求めていく
  std::vector<GeographicCoordinate>::iterator it, itr_first, itr_last;
  itr_first = vRepresentativePoint.begin();
  itr_last = vRepresentativePoint.end();
  for(it = itr_first; it != itr_last; it++) {
    // ***************************************** //
    // タクシーがindex_taxi = i+1 にいるとき
    // ***************************************** //
    std::size_t i = std::distance(itr_first, it); // std::distance(itr_first, itr_first) == 0
    // Data/OtherData/GreedySearchRange/Range_(i+1).xmlを読み込む
    // 読込先
    std::string fileRela = fileDire_read_4+ "/" + fileName_read_4 + "_" + boost::lexical_cast<std::string>(i+1) + ".xml";
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
    // 取得
    boost::property_tree::read_xml(fileRela, tree, flag);
    boost::property_tree::ptree childTree = tree.get_child("table");
    // 動的配列の確保
    std::vector<PairIndexTSTation> vPairIndexTSTation(childTree.size());
    boost::property_tree::ptree::iterator it_j, itr_first_j, itr_last_j;
    itr_first_j = childTree.begin();
    itr_last_j = childTree.end();
    // データの取得
    for(it_j = itr_first_j; it_j != itr_last_j; it_j++) {
      std::size_t j = std::distance(itr_first_j, it_j); // std::distance(itr_first, itr_first) == 0
      vPairIndexTSTation[j].index = it_j->second.get<double>("index");
      vPairIndexTSTation[j].tStation.set( it_j->second.get<double>("length"), it_j->second.get<double>("azimuth") );
    }
    for(it_j = itr_first_j; it_j != itr_last_j; it_j++) {
      std::size_t j = std::distance(itr_first_j, it_j); // std::distance(itr_first, itr_first) == 0
      // ***************************************** //
      // index_target = vPairIndexTSTation[j].index のセルをオブジェクトで指したい状況を考える
      // ***************************************** //
      int index_taxi = i + 1;   // タクシーのいるセルのindex
      int index_target = vPairIndexTSTation[j].index; // そのタクシーがターゲットとするセルのindex(有効なindexしか現れない)
      TotalStation tStation_taxi_to_target = vPairIndexTSTation[j].tStation;
      // ==================================== //
      // 使えるもの
      // # index_taxi
      // # index_target
      //
      // # tStation_taxi_to_target
      //
      // # vCCoorRepresentativePoint
      // # vRepresentativePoint
      //
      // # gCoorNW
      //
      // # neighborhoodLongDistance
      // # cellSizeMeterForLongDistance
      // # neighborhoodMiddleDistance
      // # cellSizeMeterForMiddleDistance
      // # neighborhoodShortDistance
      // # cellSizeMeterForShortDistance
      // ==================================== //
      if( j == 0 ) {
        // index_taxi == index_target という特殊な場合
        // Range_(i+1).xmlの中身を距離でソートしているのでこのように書ける
        // タクシーの各走行方向に対して描画オブジェクトを変える
        {
          // フォルダの作成
          std::string fileDire_write = "./../../Data/OtherData/OtherData/GreedyObjectInfo/Cell_" + boost::lexical_cast<std::string>(index_taxi) + "/Vertex_" + boost::lexical_cast<std::string>(index_taxi);
          {
            boost::filesystem::path path(fileDire_write);
            boost::system::error_code error;
            bool result = boost::filesystem::create_directories(path, error);
            if (!result || error) {
              // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
            }
          }
          for( int k = 1; k <= 9; k++ ) {
            // 保存先, OtherData/GreedyObjectInfo/Cell_i/Vertex_i/Vertex_dir_k.xml
            // k = 1 : 真横
            // k = 2 : 真横
            // k = 3 : 下り斜め
            // k = 4 : 縦
            // k = 5 : 上り斜め
            // k = 6 : 真横
            // k = 7 : 下り斜め
            // k = 8 : 縦
            // k = 9 : 上り斜め
            // 無条件にオブジェクト先のブロックの大きさはcellSizeMeterForShortDistanceである。
            // 代表点はvCCoorRepresentativePoint[index_target - 1]
            // これらからオブジェクトの二点を求める
            int cSM = cellSizeMeterForShortDistance;
            std::string fileName_write = "Vertex_dir_" + boost::lexical_cast<std::string>(k) + ".xml";
            std::string fileRela = fileDire_write + "/" + fileName_write;
            // xmlのtreeの新規作成
            boost::property_tree::ptree tree;
            {
              CartesianCoordinate cCoor_1;
              CartesianCoordinate cCoor_2;
              // 0度に正のほうから近いほうがcCoor_1
              // 描画オブジェクトの情報の計算
              if( k == 1 || k == 2 || k == 6 ) {
                // 真横(X変わらず)
                cCoor_1.setX( vCCoorRepresentativePoint[index_target - 1].getX() );
                cCoor_1.setY( vCCoorRepresentativePoint[index_target - 1].getY() + cSM / 2.0 );
                cCoor_2.setX( vCCoorRepresentativePoint[index_target - 1].getX() );
                cCoor_2.setY( vCCoorRepresentativePoint[index_target - 1].getY() - cSM / 2.0 );
              }else if( k == 4 || k == 8 ) {
                // 縦(Y変わらず)
                cCoor_1.setX( vCCoorRepresentativePoint[index_target - 1].getX() + cSM / 2.0 );
                cCoor_1.setY( vCCoorRepresentativePoint[index_target - 1].getY() );
                cCoor_2.setX( vCCoorRepresentativePoint[index_target - 1].getX() - cSM / 2.0 );
                cCoor_2.setY( vCCoorRepresentativePoint[index_target - 1].getY() );
              }else if( k == 5 || k == 9  ) {
                // 上り斜め
                cCoor_1.setX( vCCoorRepresentativePoint[index_target - 1].getX() + cSM / 2.0 );
                cCoor_1.setY( vCCoorRepresentativePoint[index_target - 1].getY() + cSM / 2.0 );
                cCoor_2.setX( vCCoorRepresentativePoint[index_target - 1].getX() - cSM / 2.0 );
                cCoor_2.setY( vCCoorRepresentativePoint[index_target - 1].getY() - cSM / 2.0 );
              }else{
                // 下り斜め
                cCoor_1.setX( vCCoorRepresentativePoint[index_target - 1].getX() - cSM / 2.0 );
                cCoor_1.setY( vCCoorRepresentativePoint[index_target - 1].getY() + cSM / 2.0 );
                cCoor_2.setX( vCCoorRepresentativePoint[index_target - 1].getX() + cSM / 2.0 );
                cCoor_2.setY( vCCoorRepresentativePoint[index_target - 1].getY() - cSM / 2.0 );
              }
              GeographicCoordinate gCoor_1 = convertCCoorIntoGCoor( cCoor_1, gCoorNW );
              GeographicCoordinate gCoor_2 = convertCCoorIntoGCoor( cCoor_2, gCoorNW );
              // treeにその情報を登録
              tree.put("table.latitude1", gCoor_1.getPhi());
              tree.put("table.longitude1", gCoor_1.getLambda());
              tree.put("table.latitude2", gCoor_2.getPhi());
              tree.put("table.longitude2", gCoor_2.getLambda());
            }
            // 保存
            {
              std::locale loc = std::locale();
              boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
              boost::property_tree::xml_parser::write_xml( fileRela, tree, loc, settings );
            }
          }
        }
      }else{
        // タクシーの走行方向は気にせずにindex_taxiとindex_targetの位置関係で描画オブジェクトを変える
        {
          // フォルダの作成
          std::string fileDire_write = "./../../Data/OtherData/OtherData/GreedyObjectInfo/Cell_" + boost::lexical_cast<std::string>(index_taxi);
          {
            boost::filesystem::path path(fileDire_write);
            boost::system::error_code error;
            bool result = boost::filesystem::create_directories(path, error);
            if (!result || error) {
              // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
            }
          }
          // 保存先, OtherData/GreedyObjectInfo/Cell_i/Vertex_j.xml
          std::string fileName_write = "Vertex_" + boost::lexical_cast<std::string>(index_target) + ".xml";
          std::string fileRela = fileDire_write + "/" + fileName_write;
          // xmlのtreeの新規作成
          boost::property_tree::ptree tree;
          {
            CartesianCoordinate cCoor_1;
            CartesianCoordinate cCoor_2;
            // 0度に正のほうから近いほうがcCoor_1
            // 描画オブジェクトの情報の計算
            // index_taxiとindex_targetの方位角はtStation_taxi_to_target.getAzimuth()
            // index_taxiとindex_targetの測地線長はtStation_taxi_to_target.getLength()
            // オブジェクト先のブロックの大きさは測地線長によってきまる。
            // [1] cellSizeMeterForLongDistance
            // [2] cellSizeMeterForMiddleDistance
            // [3] cellSizeMeterForShortDistance
            // の3種類
            // 代表点はvCCoorRepresentativePoint[index_target - 1]
            // これらからオブジェクトの二点を求める
            int cSM = 0;
            if( tStation_taxi_to_target.getLength() <= neighborhoodLongDistance && tStation_taxi_to_target.getLength() > neighborhoodMiddleDistance ) {
              // 長距離
              cSM = cellSizeMeterForLongDistance;
            }else if( tStation_taxi_to_target.getLength() <= neighborhoodMiddleDistance && tStation_taxi_to_target.getLength() > neighborhoodShortDistance ) {
              // 中距離
              cSM = cellSizeMeterForMiddleDistance;
            }else{
              // 短距離
              cSM = cellSizeMeterForShortDistance;
            }
            double deg_10 = tStation_taxi_to_target.getAzimuth();
            // cSMとdeg_10とvCCoorRepresentativePoint[index_target - 1]がわかったので計算できる
            if( deg_10 == 90 || deg_10 == 270 ) {
              // tanが定義できないので例外処理
              cCoor_1.setX( vCCoorRepresentativePoint[index_target - 1].getX() + cSM / 2.0 );
              cCoor_1.setY( vCCoorRepresentativePoint[index_target - 1].getY() );
              cCoor_2.setX( vCCoorRepresentativePoint[index_target - 1].getX() - cSM / 2.0 );
              cCoor_2.setY( vCCoorRepresentativePoint[index_target - 1].getY() );
            }else {
              if( (deg_10 >= 0 && deg_10 < 45) || (deg_10 >= 135 && deg_10 < 225) || (deg_10 >= 315 && deg_10 < 360) ) {
                double x = ( -tan( deg_10 * M_PI / 180.0 ) ) * (cSM / 2.0);
                cCoor_1.setX( vCCoorRepresentativePoint[index_target - 1].getX() + x );
                cCoor_1.setY( vCCoorRepresentativePoint[index_target - 1].getY() + cSM / 2.0 );
                cCoor_2.setX( vCCoorRepresentativePoint[index_target - 1].getX() + (-x) );
                cCoor_2.setY( vCCoorRepresentativePoint[index_target - 1].getY() - cSM / 2.0 );
              }else{
                double y = (cSM / 2.0) / (-tan( deg_10 * M_PI / 180.0 ));
                if( y > 0 ) {
                  // x = cSM / 2.0 と yの組が1
                  cCoor_1.setX( vCCoorRepresentativePoint[index_target - 1].getX() + cSM / 2.0 );
                  cCoor_1.setY( vCCoorRepresentativePoint[index_target - 1].getY() + y  );
                  cCoor_2.setX( vCCoorRepresentativePoint[index_target - 1].getX() + (- cSM / 2.0) );
                  cCoor_2.setY( vCCoorRepresentativePoint[index_target - 1].getY() + (-y) );
                }else{
                  // x = cSM / 2.0 と yの組が2
                  cCoor_2.setX( vCCoorRepresentativePoint[index_target - 1].getX() + cSM / 2.0 );
                  cCoor_2.setY( vCCoorRepresentativePoint[index_target - 1].getY() + y  );
                  cCoor_1.setX( vCCoorRepresentativePoint[index_target - 1].getX() + (- cSM / 2.0) );
                  cCoor_1.setY( vCCoorRepresentativePoint[index_target - 1].getY() + (-y) );
                }
              }
            }
            // treeにその情報を登録
            GeographicCoordinate gCoor_1 = convertCCoorIntoGCoor( cCoor_1, gCoorNW );
            GeographicCoordinate gCoor_2 = convertCCoorIntoGCoor( cCoor_2, gCoorNW );
            tree.put("table.latitude1", gCoor_1.getPhi());
            tree.put("table.longitude1", gCoor_1.getLambda());
            tree.put("table.latitude2", gCoor_2.getPhi());
            tree.put("table.longitude2", gCoor_2.getLambda());
          }
          // 保存
          {
            std::locale loc = std::locale();
            boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
            boost::property_tree::xml_parser::write_xml( fileRela, tree, loc, settings );
          }
        }
      }
    }
  }
  std::cout << "オブジェクト情報の作成終了" << std::endl;
  return EXIT_SUCCESS;
}

int createRationalMapRepresentativePoints() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName = "RationalMapRepresentativePoints.xml";
  std::string fileDire = "./../../Data/OtherData/OtherData";
  std::string fileName_read = "RationalMap.xml";
  std::string fileDire_read = "./../../Data/OtherData/ProcessedInitialData";
  // ------------------------------------ //
  // int numRow = 0;
  int numCol = 0;
  int numCell = 0;
  GeographicCoordinate gCoorNW;
  GeographicCoordinate gCoorSE;
  double cellSizePhi = 0;
  double cellSizeLambda = 0;
  // ファイル作成に必要なデータを取得
  {
    // 読込先
    std::string fileRela_read = fileDire_read + "/" + fileName_read;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
    // 取得
    boost::property_tree::read_xml(fileRela_read, tree, flag);
    // numRow = tree.get<int>("table.numRow");
    numCol = tree.get<int>("table.numCol");
    numCell = tree.get<int>("table.numCell");
    cellSizePhi = tree.get<double>("table.cellSizePhi");
    cellSizeLambda = tree.get<double>("table.cellSizeLambda");
    gCoorNW.set( tree.get<double>("table.northWestLatitude"), tree.get<double>("table.northWestLongitude") );
    gCoorSE.set( tree.get<double>("table.southEastLatitude"), tree.get<double>("table.southEastLongitude") );
  }
  std::cout << fileName << "の作成開始" << std::endl;
  {
    // 代表点ベクトルの生成
    std::vector<GeographicCoordinate> vRepresentativePoint(numCell);
    std::vector<int> vRow(numCell);
    std::vector<int> vCol(numCell);
    // 値を求める
    {
      std::vector<GeographicCoordinate>::iterator it, itr_first, itr_last;
      itr_first = vRepresentativePoint.begin();
      itr_last = vRepresentativePoint.end();
      for(it = itr_first; it != itr_last; it++) {
        std::size_t index = std::distance(itr_first, it); // std::distance(itr_first, itr_first) == 0
        int row = calculateRowFromIndex( index + 1, numCol, numCell );
        vRow[index] = row;
        int col = calculateColFromIndex( index + 1, numCol, numCell );
        vCol[index] = col;
        vRepresentativePoint[index].setPhi( gCoorNW.getPhi() - row * cellSizePhi + cellSizePhi / 2.0 );
        vRepresentativePoint[index].setLambda( gCoorNW.getLambda() + col * cellSizeLambda - cellSizeLambda / 2.0 );
      }
    }
    // 保存先
    std::string fileRela = fileDire + "/" + fileName;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    // treeのノードの追加
    {
      std::vector<GeographicCoordinate>::iterator it, itr_first, itr_last;
      itr_first = vRepresentativePoint.begin();
      itr_last = vRepresentativePoint.end();
      for(it = itr_first; it != itr_last; it++) {
        std::size_t index = std::distance(itr_first, it);
        boost::property_tree::ptree childTree;
        childTree.put("index", index+1);
        childTree.put("row", vRow[index]);
        childTree.put("col", vCol[index]);
        childTree.put("latitude", vRepresentativePoint[index].getPhi());
        childTree.put("longitude", vRepresentativePoint[index].getLambda());
        tree.add_child("table.cell", childTree);
      }
    }
    // 保存
    {
      std::locale loc = std::locale();
      boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
      boost::property_tree::xml_parser::write_xml( fileRela, tree, loc, settings );
    }
  }
  std::cout << fileName << "の作成終了" << std::endl;
  return EXIT_SUCCESS;
}
int createRationalSearchRange() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName = "Range"; // あとでfilename + "_" + i + ".xml"をする
  std::string fileDire = "./../../Data/OtherData/OtherData/RationalSearchRange"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  std::string fileName_read_2 = "RationalMap.xml";
  std::string fileDire_read_2 = "./../../Data/OtherData/ProcessedInitialData"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  std::string fileName_read_3 = "RationalMapRepresentativePoints.xml";
  std::string fileDire_read_3 = "./../../Data/OtherData/OtherData"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  // ------------------------------------ //
  std::cout << "Range_(i+1).xmlの作成開始" << std::endl;
  int numCell = 0;
  {
    // 読込先
    std::string fileRela_read = fileDire_read_2 + "/" + fileName_read_2;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
    // 取得
    boost::property_tree::read_xml(fileRela_read, tree, flag);
    numCell = tree.get<int>( "table.numCell" );
  }
  // 代表点ベクトルの読込み
  std::vector<GeographicCoordinate> vRepresentativePoint(numCell);
  std::vector<int> vRow(numCell);
  std::vector<int> vCol(numCell);
  {
    // 読込先
    std::string fileRela_read = fileDire_read_3 + "/" + fileName_read_3;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
    // 取得
    boost::property_tree::read_xml(fileRela_read, tree, flag);
    boost::property_tree::ptree childTree = tree.get_child("table");
    boost::property_tree::ptree::iterator itr_first, itr_last, it;
    itr_first = childTree.begin();
    itr_last = childTree.end();
    for(it = itr_first; it != itr_last; it++) {
      std::size_t index = std::distance(itr_first, it); // std::distance(itr_first, itr_first) == 0
      vRepresentativePoint[index].set( it->second.get<double>("latitude"), it->second.get<double>("longitude") );
      vRow[index] = it->second.get<int>("row");
      vCol[index] = it->second.get<int>("col");
    }
  }
  // 辞書式ソートができるように構造体を宣言し、ソートの規則をクラスで書く
  struct PairIndexTSTation {
    int index;
    TotalStation tStation;
  };
  class MyLessDefinition {
  public:
    bool operator()(const PairIndexTSTation& a, const PairIndexTSTation& b)
    {
      if( a.tStation.getLength() == b.tStation.getLength() ) {
        if( a.tStation.getAzimuth() == b.tStation.getAzimuth() ) {
          return a.index < b.index;
        }else{
          return a.tStation.getAzimuth() < b.tStation.getAzimuth();
        }
      }else{
        return a.tStation.getLength() < b.tStation.getLength();
      }
      return a.tStation.getLength() < b.tStation.getLength();
    }
  };
  // Range_(i+1).xmlの作成
  for (int i = 0; i < numCell; i++) {
    // 保存先
    std::string fileRela = fileDire + "/" + fileName + "_" + boost::lexical_cast<std::string>(i+1) + ".xml";
    // validCellsを求める
    std::vector<PairIndexTSTation> vPairIndexTSTation;
    for (int j = 0; j < numCell; j++) {
      PairIndexTSTation pairHoge;
      // セル(i+1)からセル(j+1)への測地線長と方位角を取得する
      pairHoge.tStation = calculateTStationFromGCoor( vRepresentativePoint[i], vRepresentativePoint[j] );
      bool isWithinValidResion = ( abs( vRow[i] - vRow[j] ) <= 1 && abs( vCol[i] - vCol[j] ) <= 1 );
      if( isWithinValidResion ) {
        // 有効セルのindexを取得
        pairHoge.index = j+1;
        // 有効セルの情報ベクトルへプッシュ
        vPairIndexTSTation.push_back(pairHoge);
      }
    }
    // 第一辞書を測地線長, 第二辞書を方位角, 第三辞書をindexとしてソート
    {
      std::vector<PairIndexTSTation>::iterator it, itr_first, itr_last;
      itr_first = vPairIndexTSTation.begin();
      itr_last = vPairIndexTSTation.end();
      sort(itr_first, itr_last, MyLessDefinition());
    }
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    {
      std::vector<PairIndexTSTation>::iterator it, itr_first, itr_last;
      itr_first = vPairIndexTSTation.begin();
      itr_last = vPairIndexTSTation.end();
      for(it = itr_first; it != itr_last; it++) {
        std::size_t index = std::distance(itr_first, it); // std::distance(itr_first, itr_first) == 0
        boost::property_tree::ptree childTree;
        childTree.put("index", vPairIndexTSTation[index].index);
        childTree.put("length", vPairIndexTSTation[index].tStation.getLength());
        childTree.put("azimuth", vPairIndexTSTation[index].tStation.getAzimuth());
        tree.add_child("table.cell", childTree);
      }
    }
    // 保存
    {
      std::locale loc = std::locale();
      boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
      boost::property_tree::xml_parser::write_xml( fileRela, tree, loc, settings );
    }
  }
  std::cout << "Range_(i+1).xmlの作成終了" << std::endl;
  return EXIT_SUCCESS;
}
int createRationalObjectInfo() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName_read_1 = "RationalMap.xml";
  std::string fileDire_read_1 = "./../../Data/OtherData/ProcessedInitialData"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  std::string fileName_read_2 = "RationalMapRepresentativePoints.xml";
  std::string fileDire_read_2 = "./../../Data/OtherData/OtherData"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  // ------------------------------------ //
  std::cout << "オブジェクト情報の作成開始" << std::endl;

  // 営業領域の最北西を取得, RationalMap.xml
  GeographicCoordinate gCoorNW;
  int numCell;
  int cellSizeMeter;
  {
    // 読込先
    std::string fileRela_read = fileDire_read_1 + "/" + fileName_read_1;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
    // 取得
    boost::property_tree::read_xml(fileRela_read, tree, flag);
    gCoorNW.set( tree.get<double>("table.northWestLatitude"), tree.get<double>("table.northWestLongitude") );
    numCell = tree.get<int>("table.numCell");
    cellSizeMeter = tree.get<int>("table.cellSizeMeter");
  }
  // 各セルの代表点を取得, RationalMapRepresentativePoints.xml
  std::vector<GeographicCoordinate> vRepresentativePoint(numCell);
  {
    // 読込先
    std::string fileRela_read = fileDire_read_2 + "/" + fileName_read_2;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
    // 取得
    boost::property_tree::read_xml(fileRela_read, tree, flag);
    boost::property_tree::ptree childTree = tree.get_child("table");
    boost::property_tree::ptree::iterator itr_first, itr_last, it;
    itr_first = childTree.begin();
    itr_last = childTree.end();
    for(it = itr_first; it != itr_last; it++) {
      std::size_t index = std::distance(itr_first, it); // std::distance(itr_first, itr_first) == 0
      vRepresentativePoint[index].set( it->second.get<double>("latitude"), it->second.get<double>("longitude") );
    }
  }
  // 描画オブジェクトを求めるのにデカルト座標系式の代表点の情報が必要
  std::vector<CartesianCoordinate> vCCoorRepresentativePoint(numCell);
  // RepresentativePointを元にvCCoorRepresentativePointを作成する
  {
    std::vector<GeographicCoordinate>::iterator it, itr_first, itr_last;
    itr_first = vRepresentativePoint.begin();
    itr_last = vRepresentativePoint.end();
    for(it = itr_first; it != itr_last; it++) {
      std::size_t i = std::distance(itr_first, it); // std::distance(itr_first, itr_first) == 0
      vCCoorRepresentativePoint[i] = convertGCoorIntoCCoor( vRepresentativePoint[i], gCoorNW );
    }
  }
  // 描画情報を求めていく
  std::vector<GeographicCoordinate>::iterator it, itr_first, itr_last;
  itr_first = vRepresentativePoint.begin();
  itr_last = vRepresentativePoint.end();
  for(it = itr_first; it != itr_last; it++) {
    std::size_t i = std::distance(itr_first, it); // std::distance(itr_first, itr_first) == 0
    // ***************************************** //
    // タクシーがindex_taxi = i+1 にいるとき
    // ***************************************** //
    // 最適な方向がlのとき
    for( int l = 1; l <= 9; l++ ) {
      // 動かないのが最適の時
      if( l == 1 ) {
        // OtherData/RationalObjectInfo/Cell_i/dir_1/Vertex_dir_k.xmlを作る
        // タクシーがkの方向に移動している場合
        for( int k = 1; k <= 9; k++ ) {
          // フォルダの生成
          std::string fileDire_write = "./../../Data/OtherData/OtherData/RationalObjectInfo/Cell_" + boost::lexical_cast<std::string>(i+1) + "/dir_1";
          {
            boost::filesystem::path path(fileDire_write);
            boost::system::error_code error;
            bool result = boost::filesystem::create_directories(path, error);
            if (!result || error) {
              // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
            }
          }
          std::string fileName_write = "Vertex_dir_" + boost::lexical_cast<std::string>(k) + ".xml";
          std::string fileRela = fileDire_write + "/" + fileName_write;
          // xmlのtreeの新規作成
          boost::property_tree::ptree tree;
          {
            // 描画オブジェクトの情報の計算
            // 補足情報
            // k = 1 : 真横
            // k = 2 : 真横
            // k = 3 : 下り斜め
            // k = 4 : 縦
            // k = 5 : 上り斜め
            // k = 6 : 真横
            // k = 7 : 下り斜め
            // k = 8 : 縦
            // k = 9 : 上り斜め
            //
            // vCCoorRepresentativePoint[i]
            // cellSizeMeter
            // gCoorNW
            CartesianCoordinate cCoor_1;
            CartesianCoordinate cCoor_2;
            // 0度に正のほうから近いほうがcCoor_1
            if( k == 1 || k == 2 || k == 6 ) {
              // 真横(X変わらず)
              cCoor_1.setX( vCCoorRepresentativePoint[i].getX() );
              cCoor_1.setY( vCCoorRepresentativePoint[i].getY() + cellSizeMeter / 2.0 );
              cCoor_2.setX( vCCoorRepresentativePoint[i].getX() );
              cCoor_2.setY( vCCoorRepresentativePoint[i].getY() - cellSizeMeter / 2.0 );
            }else if( k == 4 || k == 8 ) {
              // 縦(Y変わらず)
              cCoor_1.setX( vCCoorRepresentativePoint[i].getX() + cellSizeMeter / 2.0 );
              cCoor_1.setY( vCCoorRepresentativePoint[i].getY() );
              cCoor_2.setX( vCCoorRepresentativePoint[i].getX() - cellSizeMeter / 2.0 );
              cCoor_2.setY( vCCoorRepresentativePoint[i].getY() );
            }else if( k == 5 || k == 9  ) {
              // 上り斜め
              cCoor_1.setX( vCCoorRepresentativePoint[i].getX() + cellSizeMeter / 2.0 );
              cCoor_1.setY( vCCoorRepresentativePoint[i].getY() + cellSizeMeter / 2.0 );
              cCoor_2.setX( vCCoorRepresentativePoint[i].getX() - cellSizeMeter / 2.0 );
              cCoor_2.setY( vCCoorRepresentativePoint[i].getY() - cellSizeMeter / 2.0 );
            }else{
              // 下り斜め
              cCoor_1.setX( vCCoorRepresentativePoint[i].getX() - cellSizeMeter / 2.0 );
              cCoor_1.setY( vCCoorRepresentativePoint[i].getY() + cellSizeMeter / 2.0 );
              cCoor_2.setX( vCCoorRepresentativePoint[i].getX() + cellSizeMeter / 2.0 );
              cCoor_2.setY( vCCoorRepresentativePoint[i].getY() - cellSizeMeter / 2.0 );
            }
            GeographicCoordinate gCoor_1 = convertCCoorIntoGCoor( cCoor_1, gCoorNW );
            GeographicCoordinate gCoor_2 = convertCCoorIntoGCoor( cCoor_2, gCoorNW );
            // treeにその情報を登録
            tree.put("table.latitude1", gCoor_1.getPhi());
            tree.put("table.longitude1", gCoor_1.getLambda());
            tree.put("table.latitude2", gCoor_2.getPhi());
            tree.put("table.longitude2", gCoor_2.getLambda());
          }
          // 保存
          {
            std::locale loc = std::locale();
            boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
            boost::property_tree::xml_parser::write_xml( fileRela, tree, loc, settings );
          }
        }
      }else{
        // OtherData/RationalObjectInfo/Cell_i/dir_l.xmlを作る
        // フォルダの生成
        std::string fileDire_write = "./../../Data/OtherData/OtherData/RationalObjectInfo/Cell_" + boost::lexical_cast<std::string>(i+1);
        {
          boost::filesystem::path path(fileDire_write);
          boost::system::error_code error;
          bool result = boost::filesystem::create_directories(path, error);
          if (!result || error) {
            // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
          }
        }
        std::string fileName_write = "dir_" + boost::lexical_cast<std::string>(l) + ".xml";
        std::string fileRela = fileDire_write + "/" + fileName_write;
        // xmlのtreeの新規作成
        boost::property_tree::ptree tree;
        {
          // 描画オブジェクトの情報の計算
          // vCCoorRepresentativePoint[i]
          // cellSizeMeter
          // gCoorNW
          // 最適な方向（l=2, 3, ..., 9）
          CartesianCoordinate cCoor_1;
          CartesianCoordinate cCoor_2;
          double X = vCCoorRepresentativePoint[i].getX();
          double Y = vCCoorRepresentativePoint[i].getY();
          double L = cellSizeMeter;
          if( l == 2 ) {
            cCoor_1.setX( X + L );
            cCoor_1.setY( Y + 0.5 * L );
            cCoor_2.setX( X + L );
            cCoor_2.setY( Y - 0.5 * L );
          }else if( l == 3 ) {
            cCoor_1.setX( X + 1.5 * L );
            cCoor_1.setY( Y + 0.5 * L );
            cCoor_2.setX( X + 0.5 * L );
            cCoor_2.setY( Y + 1.5 * L );
          }else if( l == 4 ) {
            cCoor_1.setX( X + 0.5 * L );
            cCoor_1.setY( Y + 1.0 * L );
            cCoor_2.setX( X - 0.5 * L );
            cCoor_2.setY( Y + 1.0 * L );
          }else if( l == 5 ) {
            cCoor_1.setX( X - 0.5 * L );
            cCoor_1.setY( Y + 1.5 * L );
            cCoor_2.setX( X - 1.5 * L );
            cCoor_2.setY( Y + 0.5 * L );
          }else if( l == 6 ) {
            cCoor_1.setX( X - 1.0 * L );
            cCoor_1.setY( Y + 0.5 * L );
            cCoor_2.setX( X - 1.0 * L );
            cCoor_2.setY( Y + 0.5 * L );
          }else if( l == 7 ) {
            cCoor_1.setX( X - 1.5 * L );
            cCoor_1.setY( Y - 0.5 * L );
            cCoor_2.setX( X - 0.5 * L );
            cCoor_2.setY( Y - 1.5 * L );
          }else if( l == 8 ) {
            cCoor_1.setX( X - 0.5 * L );
            cCoor_1.setY( Y - 1.0 * L );
            cCoor_2.setX( X + 0.5 * L );
            cCoor_2.setY( Y - 1.0 * L );
          }else{
            cCoor_1.setX( X + 0.5 * L );
            cCoor_1.setY( Y - 1.5 * L );
            cCoor_2.setX( X + 1.5 * L );
            cCoor_2.setY( Y - 0.5 * L );
          }
          GeographicCoordinate gCoor_1 = convertCCoorIntoGCoor( cCoor_1, gCoorNW );
          GeographicCoordinate gCoor_2 = convertCCoorIntoGCoor( cCoor_2, gCoorNW );
          // treeにその情報を登録
          tree.put("table.latitude1", gCoor_1.getPhi());
          tree.put("table.longitude1", gCoor_1.getLambda());
          tree.put("table.latitude2", gCoor_2.getPhi());
          tree.put("table.longitude2", gCoor_2.getLambda());
        }
        // 保存
        {
          std::locale loc = std::locale();
          boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
          boost::property_tree::xml_parser::write_xml( fileRela, tree, loc, settings );
        }
      }
    }
  }
  std::cout << "オブジェクト情報の作成終了" << std::endl;
  return EXIT_SUCCESS;
}

