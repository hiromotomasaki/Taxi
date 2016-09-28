/**
 * main.cpp
 *
 * Copyright (c) 2016 HIROMOTO,Masaki
 *
 */
#include "main.hpp"

using namespace hiro;

// 【この関数の目的】
// タクシーからの描画要求ごとに実行する．1_Cronでの結果を参照して描画オブジェクトを返す．

int main(int argc, char *argv[])
{
	// 第一引数は実行ファイル名
	// 第二引数はタクシーのID番号の文字列
	if( argc != 2 ) {
		return EXIT_FAILURE;
	}
		std::cout << "AAAAAAA" << "\n";
	// 入力された番号の文字列を数字やstringに変換
	int idTaxi = boost::lexical_cast<int>( argv[1] );
	std::string idTaxi_str = boost::lexical_cast<std::string>( idTaxi );
	// FromViswa/TaxiPosition/TaxiPosition_ID_(idTaxi).xmlを読み込む
		std::cout << "AAAAAAA" << "\n";
	GeographicCoordinate gCoor;
	GeographicCoordinate gCoorPre;
	{
		// 設定値読み込みファイル名
		std::string fileName = "taxiPosition_ID_" + idTaxi_str + ".xml";
		// 設定値読み込みファイル先のディレクトリのmakefileからの相対位置
		std::string fileDire = "./../Data/2_ForEachRequest/FromViswa/TaxiPosition";
		std::string fileRela = fileDire + "/" + fileName;
		// create an empty property tree
		boost::property_tree::ptree pt;
		// read the xml file
		boost::property_tree::read_xml(fileRela, pt, boost::property_tree::xml_parser::no_comments);
		{
			{
				// positionを取得する
				std::string sPointStr = pt.get<std::string>("table.position");
				// 空文字の除去
				boost::trim (sPointStr);
				// 文字列から緯度と経度の文字列を抽出
				std::vector<std::string> v;
				boost::algorithm::split(v, sPointStr, boost::is_any_of(","));
				double phi = boost::lexical_cast<double>(v[0]);
				double lambda = boost::lexical_cast<double>(v[1]);
				gCoor.set( phi, lambda );
			}
			{
				// positionを取得する
				std::string sPointStr = pt.get<std::string>("table.prePosition");
				// 空文字の除去
				boost::trim (sPointStr);
				// 文字列から緯度と経度の文字列を抽出
				std::vector<std::string> v;
				boost::algorithm::split(v, sPointStr, boost::is_any_of(","));
				double phi = boost::lexical_cast<double>(v[0]);
				double lambda = boost::lexical_cast<double>(v[1]);
				gCoorPre.set( phi, lambda );
			}
		}

	}

	// ------------- 取得するもの  ------------- //
	// 営業領域の外枠の最北西
	GeographicCoordinate gCoorNW;
	// 営業領域の外枠の最南東
	GeographicCoordinate gCoorSE;
	// 営業領域の外枠内にあるセル数
	int numCell;
	// 営業領域の外枠の行数
	int numRow;
	// 営業領域の外枠の列数
	int numCol;
	// セルの南北の緯度差
	double cellSizePhi;
	// セルの東西の経度差
	double cellSizeLambda;

	// タクシーの進行方向を計算するときに使用する二点間の座標間の距離の最大値．これを越すとオブジェクトは円の中から探索して選ばれる(dir1に相当)．越さなければ進行方向(dir2からdir9)の扇型の中から探索して選ばれる
	double maxDistanceFromPreposition;
	// ----------------------------------------------------- //

	// Data/0_2_Set/InputDataFor2_ForEachRequest.xmlから読み込む
	{
		// 設定値読み込みファイル名
		std::string fileName = "InputDataFor2_ForEachRequest.xml";
		// 設定値読み込みファイル先のディレクトリのmakefileからの相対位置
		std::string fileDire = "./../Data/0_2_Set";
		std::string fileRela = fileDire + "/" + fileName;
		{
			// create an empty property tree
			boost::property_tree::ptree pt;
			// read the xml file
			boost::property_tree::read_xml(fileRela, pt, boost::property_tree::xml_parser::no_comments);
			{
				gCoorNW.setPhi( pt.get<double>( "table.gCoorNW.phi" ) );
				gCoorNW.setLambda( pt.get<double>( "table.gCoorNW.lambda" ) );
			}
			{
				gCoorSE.setPhi( pt.get<double>( "table.gCoorSE.phi" ) );
				gCoorSE.setLambda( pt.get<double>( "table.gCoorSE.lambda" ) );
			}
			{
				numCell = pt.get<int>("table.numCell.value");
				numRow = pt.get<int>("table.numRow.value");
				numCol = pt.get<int>("table.numCol.value");
				cellSizePhi = pt.get<double>("table.cellSizePhi.value");
				cellSizeLambda = pt.get<double>("table.cellSizeLambda.value");
				maxDistanceFromPreposition = pt.get<double>("table.maxDistanceFromPreposition.value");
			}
		}
	}

	// 二点間の距離と方角を計算し，dirを決定する．
	int dir = 1;
	{
		TotalStation tStation = calculateTStationFromGCoor( gCoorPre, gCoor );
		if (tStation.getLength() > maxDistanceFromPreposition) {
			dir = 1;
		}else{
			double theta = tStation.getAzimuth();
			if((theta >= 0) && (theta < 22.5)) {
				dir = 2;
			}else if((theta >= 45 - 22.5) && (theta < 45 + 22.5 )) {
				dir = 3;
			}else if((theta >= 90 - 22.5) && (theta < 90 + 22.5 )) {
				dir = 4;
			}else if((theta >= 135 - 22.5) && (theta < 135 + 22.5 )) {
				dir = 5;
			}else if((theta >= 180 - 22.5) && (theta < 180 + 22.5 )) {
				dir = 6;
			}else if((theta >= 225 - 22.5) && (theta < 225 + 22.5 )) {
				dir = 7;
			}else if((theta >= 270 - 22.5) && (theta < 270 + 22.5 )) {
				dir = 8;
			}else if((theta >= 315 - 22.5) && (theta < 315 + 22.5 )) {
				dir = 9;
			}else{
				dir = 2;
			}
		}
	}

	// indexTaxiを求める
	int indexTaxi;
	{
		int row = calculateRowFromLatitudes( gCoor.getPhi(), gCoorNW.getPhi(), gCoorSE.getPhi(), cellSizePhi );
		int col = calculateColFromLongitudes( gCoor.getLambda(), gCoorNW.getLambda(), gCoorSE.getLambda(), cellSizeLambda );
		indexTaxi = calculateIndexFromRowCol( row, col, numRow, numCol );
	}

	std::cout << indexTaxi << "\n";

	// タクシーの情報を読み込む

    return EXIT_SUCCESS;
}
