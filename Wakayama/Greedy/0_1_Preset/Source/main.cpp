/**
 * main.cpp
 *
 * Copyright (c) 2016 HIROMOTO,Masaki
 *
 */
#include "main.hpp"

using namespace hiro;

// 【この関数の目的】
// Greedy関係の設定値のxmlファイルを作成する．

int myTestFunc();
int myTestFunc()
{
	std::cout << "読み込みテスト中..." << "\n";
	std::string fileName = "base.xml";
	std::string fileDire = "./../Data/0_1_Preset";
	std::string fileRela = fileDire + "/" + fileName;
	{
		// create an empty property tree
		boost::property_tree::ptree pt;
		// read the xml file
		boost::property_tree::read_xml(fileRela, pt, boost::property_tree::xml_parser::no_comments);
		// ループなし
		{
			GeographicCoordinate gCoorNW;
			gCoorNW.setPhi( pt.get<double>( "table.gCoorNW.phi" ) );
			gCoorNW.setLambda( pt.get<double>( "table.gCoorNW.lambda" ) );
			gCoorNW.print();
		}
		// ループあり
		{
			boost::property_tree::ptree::iterator itr_first, itr_last, it;
			itr_first = pt.get_child( "table.gCoorRemove" ).begin();
			itr_last = pt.get_child( "table.gCoorRemove" ).end();
			int N = std::distance(itr_first, itr_last);
			std::cout << "要素数 ： " << N << "\n";
			for(it = itr_first; it != itr_last; ++it) {
				std::cout << "[" << std::distance(itr_first, it) << "]" << "\n";
				std::cout << it->second.get<double>("phiNW") << "\n";
			}
		}
	}
	std::cout << fileName << "の読込終了" << std::endl;
    return EXIT_SUCCESS;
}

int main()
{
	// ------------- ユーザー入力値  ------------- //
	// 営業領域の外枠の最北西
	GeographicCoordinate gCoorNW( 34.706409, 135.465044 );
	// 営業領域の外枠の最南東
	GeographicCoordinate gCoorSE( 34.57148, 135.555 );
	// 追加する営業領域の最北西
	std::vector<GeographicCoordinate> gCoorAddNW;
	gCoorAddNW.push_back( GeographicCoordinate( 34.706409, 135.465044 ) );
	gCoorAddNW.push_back( GeographicCoordinate( 34.706409, 135.465044 ) ); // test
	// 追加する営業領域の最南東
	std::vector<GeographicCoordinate> gCoorAddSE;
	gCoorAddSE.push_back( GeographicCoordinate( 34.57148, 135.555 ) );
	gCoorAddSE.push_back( GeographicCoordinate( 34.57148, 135.555 ) ); // test
	// 追加する営業領域の最北西
	std::vector<GeographicCoordinate> gCoorRemoveNW;
	gCoorRemoveNW.push_back( GeographicCoordinate( -1, -1 ) );
	gCoorRemoveNW.push_back( GeographicCoordinate( 34.606409, 135.485044 ) );
	// 追加する営業領域の最南東
	std::vector<GeographicCoordinate> gCoorRemoveSE;
	gCoorRemoveSE.push_back( GeographicCoordinate( -1, -1 ) );
	gCoorRemoveSE.push_back( GeographicCoordinate( 34.58148, 135.515 ) );
	// セルの一辺の長さ[m]
	double cellSizeMeter = 200;
	// 表示するピンの日にちに関する抽出条件
	std::vector<int> displayDate;
	displayDate.push_back( 7*5 );
	displayDate.push_back( 7*6 );
	displayDate.push_back( 7*7 );
	displayDate.push_back( 7*8 );
	// 表示するピンの時間幅の始点は現在時刻から何分前なのか
	int displayTimeFrom = -2;
	// 表示するピンの時間幅の始点は現在時刻から何分後なのか
	int displayTimeTo = 4;
	// セルから描画するオブジェクトの有効範囲の円の半径[m]
	double searchRange = 3000;
	// タクシーの進行方向を考慮した時に描画するオブジェクトの有効範囲の扇型（円に含まれる）の中心角度[deg](45度から180度まで)
	double searchDegree = 180;
	// オブジェクトの底辺の長さの最小値
	double baseLengthMin = 200;
	// オブジェクトの底辺の長さの最大値
	double baseLengthMax = 1000;
	// タクシーの進行方向を計算するときに使用する二点間の座標間の距離の最大値．これを越すとオブジェクトは円の中から探索して選ばれる(dir1に相当)．越さなければ進行方向(dir2からdir9)の扇型の中から探索して選ばれる
	double maxDistanceFromPreposition = 3000;
	// 需要が集中していると判定するためのしきい値．このしきい値以上であれば需要が集中しているとみなす．
	double threshold = 2;
	// ------------------------------------------- //
	// ------------------ その他 ----------------- //
	// 設定値の確認表示をするかどうか
	bool display = true;
	// 保存ファイルの一部読み込みをしてチェックするか
	bool check = true;
	// ------------------------------------------- //

	// 表示
	if (display) {
		std::cout << "============== 確認 ==============" << "\n";
		std::cout << "--------- 営業領域の外枠 ---------" << "\n";
		{
			std::cout << "北西 ： " << "\n";
			gCoorNW.print();
			std::cout << "南東 ： " << "\n";
			gCoorSE.print();
		}
		std::cout << "--------- 追加される営業領域 ---------" << "\n";
		{
			int N = gCoorAddNW.size();
			std::cout << "追加領域の数 ： " << N << "\n";
			for (int i = 0; i < N; i++) {
				std::cout << "No." << i+1 << " : 北西 = (" << gCoorAddNW[i].getPhi() << ", " << gCoorAddNW[i].getLambda() << "), 南東 = (" << gCoorAddSE[i].getPhi() << ", " << gCoorAddSE[i].getLambda() << ")" << "\n";
			}
		}
		std::cout << "--------- 削除される営業領域 ---------" << "\n";
		{
			int N = gCoorRemoveNW.size();
			if (N == 1) {
				std::cout << "削除領域はありません．" << "\n";
			}else{
				std::cout << "削除領域の数 ： " << N-1 << "\n";
				for (int i = 1; i < N; i++) {
					std::cout << "No." << i << " : 北西 = (" << gCoorRemoveNW[i].getPhi() << ", " << gCoorRemoveNW[i].getLambda() << "), 南東 = (" << gCoorRemoveSE[i].getPhi() << ", " << gCoorRemoveSE[i].getLambda() << ")" << "\n";
				}
			}
		}
		std::cout << "--------- セルの一辺の長さ[m] ---------" << "\n";
		std::cout << cellSizeMeter << "\n";
		std::cout << "--------- 表示するピンは何日前のものか ---------" << "\n";
		{
			int N = displayDate.size();
			for (int i = 0; i < N; i++) {
				std::cout << displayDate[i];
				if (i != N-1) {
					std::cout << ", ";
				}
			}
			std::cout << "\n";
		}
		std::cout << "---------  表示するピンの時間幅の始点は現在時刻から何分前なのか ---------" << "\n";
		std::cout << displayTimeFrom << "\n";
		std::cout << "---------  表示するピンの時間幅の始点は現在時刻から何分後なのか ---------" << "\n";
		std::cout << displayTimeTo << "\n";
		std::cout << "--------- セルから描画するオブジェクトの有効範囲の円の半径[m]  ---------" << "\n";
		std::cout << searchRange << "\n";
		std::cout << "--------- タクシーの進行方向を考慮した時に描画するオブジェクトの有効範囲の扇型（円に含まれる）の中心角度[deg](45度から180度まで)  ---------" << "\n";
		std::cout << searchDegree << "\n";
		std::cout << "--------- オブジェクトの底辺の長さの最小値  ---------" << "\n";
		std::cout << baseLengthMin << "\n";
		std::cout << "--------- オブジェクトの底辺の長さの最大値  ---------" << "\n";
		std::cout << baseLengthMax << "\n";
		std::cout << "--------- タクシーの進行方向を計算するときに使用する二点間の座標間の距離の最大値．これを越すとオブジェクトは円の中から探索して選ばれる(dir1に相当)．越さなければ進行方向(dir2からdir9)の扇型の中から探索して選ばれる  ---------" << "\n";
		std::cout << maxDistanceFromPreposition << "\n";
		std::cout << "--------- 需要が集中していると判定するためのしきい値．このしきい値以上であれば需要が集中しているとみなす．  ---------" << "\n";
		std::cout << threshold << "\n";
		std::cout << "==================================" << "\n";
	}

	// 設定値の保存
	{
		// 設定値保存ファイル名
		std::string fileName = "base.xml";
		// 設定値保存ファイル先のディレクトリのmakefileからの相対位置
		std::string fileDire = "./../Data/0_1_Preset";
		std::cout << fileName << "を保存中..." << std::endl;
		// ディレクトリの作成
		{
			boost::filesystem::path path(fileDire);
			boost::system::error_code error;
			const bool result = boost::filesystem::create_directories(path, error);
			if (!result || error) {
				// std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
			}
		}
		// 保存
		{
			// 保存path
			std::string fileRela = fileDire + "/" + fileName;
			// create an empty property tree
			boost::property_tree::ptree pt;

			// create the root element
			boost::property_tree::ptree& root = pt.put("table", "");

			// add child elements
			{
				{
					boost::property_tree::ptree& child = root.add("gCoorNW", "");
					child.put("phi", gCoorNW.getPhi());
					child.put("lambda", gCoorNW.getLambda());
				}
				{
					boost::property_tree::ptree& child = root.add("gCoorSE", "");
					child.put("phi", gCoorSE.getPhi());
					child.put("lambda", gCoorSE.getLambda());
				}
				{
					boost::property_tree::ptree& child = root.add("gCoorAdd", "");
					int N = gCoorAddNW.size();
					for (int i = 0; i < N; i++) {
						boost::property_tree::ptree& cchild = child.add("tuples", "");
						cchild.put("phiNW", gCoorAddNW[i].getPhi());
						cchild.put("lambdaNW", gCoorAddNW[i].getLambda());
						cchild.put("phiSE", gCoorAddSE[i].getPhi());
						cchild.put("lambdaSE", gCoorAddSE[i].getLambda());
					}
				}
				{
					boost::property_tree::ptree& child = root.add("gCoorRemove", "");
					int N = gCoorRemoveNW.size();
					for (int i = 0; i < N; i++) {
						boost::property_tree::ptree& cchild = child.add("tuples", "");
						cchild.put("phiNW", gCoorRemoveNW[i].getPhi());
						cchild.put("lambdaNW", gCoorRemoveNW[i].getLambda());
						cchild.put("phiSE", gCoorRemoveSE[i].getPhi());
						cchild.put("lambdaSE", gCoorRemoveSE[i].getLambda());
					}
				}
				{
					boost::property_tree::ptree& child = root.add("cellSizeMeter", "");
					child.put("value", cellSizeMeter);
				}
				{
					boost::property_tree::ptree& child = root.add("displayDate", "");
					int N = displayDate.size();
					for (int i = 0; i < N; i++) {
						boost::property_tree::ptree& cchild = child.add("date", "");
						cchild.put("value", displayDate[i]);
					}
				}
				{
					boost::property_tree::ptree& child = root.add("displayTimeFrom", "");
					child.put("value", displayTimeFrom);
				}
				{
					boost::property_tree::ptree& child = root.add("displayTimeTo", "");
					child.put("value", displayTimeTo);
				}
				{
					boost::property_tree::ptree& child = root.add("searchRange", "");
					child.put("value", searchRange);
				}
				{
					boost::property_tree::ptree& child = root.add("searchDegree", "");
					child.put("value", searchDegree);
				}
				{
					boost::property_tree::ptree& child = root.add("baseLengthMin", "");
					child.put("value", baseLengthMin);
				}
				{
					boost::property_tree::ptree& child = root.add("baseLengthMax", "");
					child.put("value", baseLengthMax);
				}
				{
					boost::property_tree::ptree& child = root.add("maxDistanceFromPreposition", "");
					child.put("value", maxDistanceFromPreposition);
				}
				{
					boost::property_tree::ptree& child = root.add("threshold", "");
					child.put("value", threshold);
				}
			}

			// output
			boost::property_tree::write_xml(fileRela, pt, std::locale(), boost::property_tree::xml_writer_make_settings<std::string>(' ', 2));
			}
		}

	// テスト
	if (check) {
		myTestFunc();
	}

    return EXIT_SUCCESS;
}
