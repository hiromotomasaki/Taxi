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
// Main_0_Calculatingのフォルダ内にある実行ファイルを実行すると読み込まれるファイルを生成する。
// 生成するファイルは
// [1] Map.xml
//     貪欲版の営業領域の定義（ニューラルネットワークはこちらの営業領域を使用）
// [2] RationalMap.xml
//     合理的版の営業領域の定義
// [3] Neighborhood.xml
//     貪欲版の近傍の定義の定義（targetとの距離に応じて描画オブジェクトを変更するときのパラメータになる）
// [4] Threshold.xml（ニューラルネットワークの結果を利用する際の閾値やチューニングパラメータ）
//     閾値の定義
// [5] OtherParameters.xml
//     その他のパラメータの定義
// の5つである。
// =================================================================================== //

// =================================================================================== //

int main(void) {

  createMap();
  createRationalMap();
  createNeighborhood();
  createThreshold();
  createOtherParametes();

  return EXIT_SUCCESS;
}
// =================================================================================== //

// =================================================================================== //
int createMap() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName = "Map.xml";
  std::string fileDire = "./../../Data/InitialData"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  double northWestLatitude = 34.706409;
  double northWestLongitude = 135.465044;
  double southEastLatitude = 34.57148;
  double southEastLongitude = 135.555;
  // 縮小版
  // double southEastLatitude = 34.67;
  // double southEastLongitude = 135.54;
  int cellSizeMeter = 200;
  // ------------------------------------ //





  std::cout << fileName << "の作成開始" << std::endl;
  {
    // 保存先
    std::string fileRela = fileDire + "/" + fileName;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    // treeのノードの追加
    {
      tree.put("table.northWestLatitude", northWestLatitude);
      tree.put("table.northWestLongitude", northWestLongitude);
      tree.put("table.southEastLatitude", southEastLatitude);
      tree.put("table.southEastLongitude", southEastLongitude);
      tree.put("table.cellSizeMeter", cellSizeMeter);
    }
    // フォルダの生成
    {
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
      }
    }
    // 保存
    {
//      std::locale loc = std::locale();
//      boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
//      boost::property_tree::xml_parser::write_xml( fileRela, tree, loc, settings );
      boost::property_tree::xml_parser::write_xml( fileRela, tree );
    }
  }
  std::cout << fileName << "の作成終了" << std::endl;
  return EXIT_SUCCESS;
}
int createRationalMap() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName = "RationalMap.xml";
  std::string fileDire = "./../../Data/InitialData"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  double northWestLatitude = 34.706409;
  double northWestLongitude = 135.465044;
  double southEastLatitude = 34.57148;
  double southEastLongitude = 135.555;
  // 縮小版
  // double southEastLatitude = 34.67;
  // double southEastLongitude = 135.54;
  int cellSizeMeter = 2000;
  // ------------------------------------ //





  std::cout << fileName << "の作成開始" << std::endl;
  {
    // 保存先
    std::string fileRela = fileDire + "/" + fileName;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    // treeのノードの追加
    {
      tree.put("table.northWestLatitude", northWestLatitude);
      tree.put("table.northWestLongitude", northWestLongitude);
      tree.put("table.southEastLatitude", southEastLatitude);
      tree.put("table.southEastLongitude", southEastLongitude);
      tree.put("table.cellSizeMeter", cellSizeMeter);
    }
    // フォルダの生成
    {
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
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
int createNeighborhood() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName = "Neighborhood.xml";
  std::string fileDire = "./../../Data/InitialData"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  int neighborhoodLongDistance = 3000;
  int cellSizeMeterForLongDistance = 1000;
  int neighborhoodMiddleDistance = 1000;
  int cellSizeMeterForMiddleDistance = 500;
  int neighborhoodShortDistance = 500;
  int cellSizeMeterForShortDistance = 200;
  // ------------------------------------ //





  std::cout << fileName << "の作成開始" << std::endl;
  {
    // 保存先
    std::string fileRela = fileDire + "/" + fileName;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    // treeのノードの追加
    {
      tree.put("table.neighborhoodLongDistance", neighborhoodLongDistance);
      tree.put("table.cellSizeMeterForLongDistance", cellSizeMeterForLongDistance);
      tree.put("table.neighborhoodMiddleDistance", neighborhoodMiddleDistance);
      tree.put("table.cellSizeMeterForMiddleDistance", cellSizeMeterForMiddleDistance);
      tree.put("table.neighborhoodShortDistance", neighborhoodShortDistance);
      tree.put("table.cellSizeMeterForShortDistance", cellSizeMeterForShortDistance);
    }
    // フォルダの生成
    {
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
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
int createThreshold() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName = "Threshold.xml";
  std::string fileDire = "./../../Data/InitialData"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  int threshold = 1;                                 // threshold以上の値があれば需要が集中しているとみなす
  double gamma = 0.1;                                 // 営業領域全体の需要数と需要分布から、各セルの需要数を計算するときに必要なパラメータ
  // ------------------------------------ //

  std::cout << fileName << "の作成開始" << std::endl;
  {
    // 保存先
    std::string fileRela = fileDire + "/" + fileName;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    // treeのノードの追加
    {
      tree.put("table.threshold", threshold);
      tree.put("table.gamma", gamma);
    }
    // フォルダの生成
    {
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
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
int createOtherParametes() {
  // ----------- ユーザー入力 ----------- //
  std::string fileName = "OtherParameters.xml";
  std::string fileDire = "./../../Data/InitialData"; // ./../../Data/Init だと何故か保存できなかった(予約文字かもしれない)
  int discreteTimeWidth = 2;
  int timeHorizon = 2;
  // ------------------------------------ //


  std::cout << fileName << "の作成開始" << std::endl;
  {
    // 保存先
    std::string fileRela = fileDire + "/" + fileName;
    // xmlのtreeの新規作成
    boost::property_tree::ptree tree;
    // treeのノードの追加
    {
      tree.put("table.discreteTimeWidth", discreteTimeWidth);
      tree.put("table.timeHorizon", timeHorizon);
    }
    // フォルダの生成
    {
      boost::filesystem::path path(fileDire);
      boost::system::error_code error;
      bool result = boost::filesystem::create_directories(path, error);
      if (!result || error) {
        // std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
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
// =================================================================================== //
