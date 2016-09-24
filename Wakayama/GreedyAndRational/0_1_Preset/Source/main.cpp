/**
 * main.cpp
 *
 * Copyright (c) 2016 HIROMOTO,Masaki
 *
 */
#include "main.hpp"

using namespace hiro;


// 【この関数の目的】
// 様々な設定
// Greedy
// ・営業領域の外枠の設定
// ・追加する複数の営業領域（長方形）の指定
// ・除去する複数の営業領域（長方形）の指定
// ・セルの一辺の大きさ（メートル）の指定
// ・表示ピンの抽出条件の設定（時間幅や日にちの範囲(何日前，何分前から何分後までか)）
// ・オブジェクト決定のためのタクシーを中心にしたセル探索範囲（メートル）
// ・セル探索範囲を扇型により制限するときの扇型の中心角度[deg]（45度から180度まで）
// ・探索範囲内でのオブジェクトの底辺の長さの定義（探索範囲の最大値に1を探索範囲の中心点に0を割り当て，1のときの底辺の長さをl_1, 0のときの底辺の長さをl_0とする．その間の位置の時の底辺の長さは関数で決定する．）
// ・タクシーの方向を決定するときに使用する二点間（現在位置と少し前の位置）の距離の最大値（最大値を越すとdir1の探索範囲になる．越していなければdir2からdir9までの8方向のうちどれかの探索範囲になる）
// ・需要が集中していると判別するためのしきい値
//
// Rational
// ・営業領域の外枠の設定
// ・追加する複数の営業領域（長方形）の指定
// ・除去する複数の営業領域（長方形）の指定
// ・セルの一辺の大きさ（メートル）の指定
// ・表示ピンの抽出条件の設定（時間幅や日にちの範囲(何日前，何分前から何分後までか)）
// ・オブジェクト決定のためのタクシーを中心にしたセル探索範囲（メートル）
// ・セル探索範囲を扇型により制限するときの扇型の中心角度[deg]（45度から180度まで）
// ・探索範囲内でのオブジェクトの底辺の長さの定義（探索範囲の最大値に1を探索範囲の中心点に0を割り当て，1のときの底辺の長さをl_1, 0のときの底辺の長さをl_0とする．その間の位置の時の底辺の長さは関数で決定する．）
// ・タクシーの方向を決定するときに使用する二点間（現在位置と少し前の位置）の距離の最大値（最大値を越すとdir1の探索範囲になる．越していなければdir2からdir9までの8方向のうちどれかの探索範囲になる）
// ・需要が集中している場所を示すサークルの半径
// ・需要が集中している場所を示すサークルと判別するためのしきい値
// ・サークルの近隣描写を防ぐために，複数のセルで営業領域の分割をして，そのセルの集合の中で最も大きい需要数を持つサークルを残す．複数セルの南北の個数（東西の個数も同じ）
// ・空車の台数を計測するためのサークルの半径


int myTestFunc();
int myTestFunc()
{
	std::string fileName = "Greedy.xml";
	std::string fileDire = "./../Data/0_1_Preset";
	std::string fileRela = fileDire + "/" + fileName;
	std::cout << fileName << "の読込開始" << std::endl;
	{
		// create an empty property tree
		boost::property_tree::ptree pt;
		// read the xml file
		boost::property_tree::read_xml(fileRela, pt, boost::property_tree::xml_parser::no_comments);
		// ループなし
		{
			GeographicCoordinate gCoorNW_G;
			gCoorNW_G.setPhi( pt.get<double>( "table.gCoorNW_G.phi" ) );
			gCoorNW_G.setLambda( pt.get<double>( "table.gCoorNW_G.lambda" ) );
			gCoorNW_G.print();
		}
		// ループあり
		{
			boost::property_tree::ptree::iterator itr_first, itr_last, it;
			itr_first = pt.get_child( "table.removeArea_G" ).begin();
			itr_last = pt.get_child( "table.removeArea_G" ).end();
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
	// ピンの抽出条件についてはGreedyに従うものとする
	// Greedy
	GeographicCoordinate gCoorNW_G( 34.706409, 135.465044 );
	GeographicCoordinate gCoorSE_G( 34.57148, 135.555 );
	double addArea_G[][4] = {
		{ 34.706409, 135.465044, 34.57148, 135.555 },
		{ 34.706409, 135.475044, 34.57148, 135.555 }, // テスト
	};
	double removeArea_G[][4] = {
		{ -1, -1, -1, -1},				// 除去エリアがない場合に要素が0になってしまうため入れている
		{ 34.606409, 135.485044, 34.58148, 135.515 },
	};
	double cellSizeMeter_G = 200;
	int displayDate_G[][1] = {
		{7*5},
		{7*6},
		{7*7},
		{7*8},
	};
	int displayTimeFrom_G = -2;
	int displayTimeTo_G = 4;
	double searchRange_G = 3000;
	double searchDegree_G = 180;
	double baseLengthMin_G = 200;
	double baseLengthMax_G = 1000;
	double maxDistance_G = 3000;
	double threshold_G = 2;
	// Rational
	GeographicCoordinate gCoorNW_R( 34.706409, 135.465044 );
	GeographicCoordinate gCoorSE_R( 34.57148, 135.555 );
	double addArea_R[][4] = {
		{ 34.706409, 135.465044, 34.57148, 135.555 },
	};
	double removeArea_R[][4] = {
		{ -1, -1, -1, -1},				// 除去エリアがない場合に要素が0になってしまうため入れている
		{ 34.606409, 135.485044, 34.58148, 135.515 },
	};
	double cellSizeMeter_R = 200;
	int displayDate_R[][1] = {
		{7*5},
		{7*6},
		{7*7},
		{7*8},
	};
	int displayTimeFrom_R = -2;
	int displayTimeTo_R = 4;
	double searchRange_R = 3000;
	double searchDegree_R = 180;
	double baseLengthMin_R = 200;
	double baseLengthMax_R = 1000;
	double maxDistance_R = 3000;
	double demandCircleSize_R = 500;
	double demandCircleThreshould_R = 3;
	double numOfSetOfCellAlongLat_R = 5;
    double vacantTaxiCircleSize_R = 1000;
	// ------------------------------------------- //

	// 確認
	{
		std::cout << "========= 確認 =========" << "\n";
		std::cout << "----- Greedy -----" << "\n";
		{
			std::cout << "* 営業領域の外枠" << "\n";
			std::cout << "北西 ： " << "\n";
			gCoorNW_G.print();
			std::cout << "南東 ： " << "\n";
			gCoorSE_G.print();
			std::cout << "* 追加領域" << "\n";
			{
				int N = sizeof(addArea_G) / sizeof(addArea_G[0]);
				std::cout << "追加領域の数 ： " << N << "\n";
				for (int i = 0; i < N; i++) {
					std::cout << "No." << i+1 << " : 北西 = (" << addArea_G[i][0] << ", " << addArea_G[i][1] << "), 南西 = (" << addArea_G[i][2] << ", " << addArea_G[i][3] << ")" << "\n";
				}
			}
			std::cout << "* 削除領域" << "\n";
			{
				int N = sizeof(removeArea_G) / sizeof(removeArea_G[0]);
				if (N == 1) {
					std::cout << "削除領域はありません．" << "\n";
				}else{
					std::cout << "削除領域の数 ： " << N-1 << "\n";
					for (int i = 1; i < N; i++) {
						std::cout << "No." << i << " : 北西 = (" << removeArea_G[i][0] << ", " << removeArea_G[i][1] << "), 南西 = (" << removeArea_G[i][2] << ", " << removeArea_G[i][3] << ")" << "\n";
					}
				}
			}
			std::cout <<"* セルサイズ ： " << cellSizeMeter_G << "\n";
			std::cout << "* 表示ピンが何日前のものか" << "\n";
			{
				int N = sizeof(displayDate_G) / sizeof(displayDate_G[0]);
				for (int i = 0; i < N; i++) {
					std::cout << displayDate_G[i][0];
					if (i != N-1) {
						std::cout << ", ";
					}
				}
				std::cout << "\n";
			}
			std::cout << "* 表示ピンを表示する現時刻からの時間範囲" << "\n";
			{
				std::cout << "Pre : " << displayTimeFrom_G << "\n";
				std::cout << "Post : " << displayTimeTo_G << "\n";
			}
			std::cout << "* 探索範囲円の半径[m] ： " << searchRange_G << "\n";
			std::cout << "* 進行方向によって方向が定まる扇型の探索範囲の中心角度[deg]：" << searchDegree_G << "\n";
			std::cout << "* オブジェクトの底辺の長さ[m]の最小値：" << baseLengthMin_G << "\n";
			std::cout << "* オブジェクトの底辺の長さ[m]の最大値：" << baseLengthMax_G << "\n";
			std::cout << "* タクシーの進行方向を決定する際の二点間の距離[m]の最大値" << maxDistance_G << "\n";
			std::cout << "需要が集中しているか判別するためのしきい値：" << threshold_G << "\n";
		}
		std::cout << "----- Rational -----" << "\n";
		{
			std::cout << "* 営業領域の外枠" << "\n";
			std::cout << "北西 ： " << "\n";
			gCoorNW_R.print();
			std::cout << "南東 ： " << "\n";
			gCoorSE_R.print();
			std::cout << "* 追加領域" << "\n";
			{
				int N = sizeof(addArea_R) / sizeof(addArea_R[0]);
				std::cout << "追加領域の数 ： " << N << "\n";
				for (int i = 0; i < N; i++) {
					std::cout << "No." << i+1 << " : 北西 = (" << addArea_R[i][0] << ", " << addArea_R[i][1] << "), 南西 = (" << addArea_R[i][2] << ", " << addArea_R[i][3] << ")" << "\n";
				}
			}
			std::cout << "* 削除領域" << "\n";
			{
				int N = sizeof(removeArea_R) / sizeof(removeArea_R[0]);
				if (N == 1) {
					std::cout << "削除領域はありません．" << "\n";
				}else{
					std::cout << "削除領域の数 ： " << N-1 << "\n";
					for (int i = 1; i < N; i++) {
						std::cout << "No." << i << " : 北西 = (" << removeArea_R[i][0] << ", " << removeArea_R[i][1] << "), 南西 = (" << removeArea_R[i][2] << ", " << removeArea_R[i][3] << ")" << "\n";
					}
				}
			}
			std::cout <<"* セルサイズ ： " << cellSizeMeter_R << "\n";
			std::cout << "* 表示ピンが何日前のものか" << "\n";
			{
				int N = sizeof(displayDate_R) / sizeof(displayDate_R[0]);
				for (int i = 0; i < N; i++) {
					std::cout << displayDate_R[i][0];
					if (i != N-1) {
						std::cout << ", ";
					}
				}
				std::cout << "\n";
			}
			std::cout << "* 表示ピンを表示する現時刻からの時間範囲" << "\n";
			{
				std::cout << "Pre : " << displayTimeFrom_R << "\n";
				std::cout << "Post : " << displayTimeTo_R << "\n";
			}
			std::cout << "* 探索範囲円の半径[m] ： " << searchRange_R << "\n";
			std::cout << "* 進行方向によって方向が定まる扇型の探索範囲の中心角度[deg]：" << searchDegree_R << "\n";
			std::cout << "* オブジェクトの底辺の長さ[m]の最小値：" << baseLengthMin_R << "\n";
			std::cout << "* オブジェクトの底辺の長さ[m]の最大値：" << baseLengthMax_R << "\n";
			std::cout << "* タクシーの進行方向を決定する際の二点間の距離[m]の最大値" << maxDistance_R << "\n";
			std::cout << "* 需要サークルの半径[m] : " << demandCircleSize_R << "\n";
			std::cout << "* 需要サークル内の合計需要に対するしきい値 : " << demandCircleThreshould_R << "\n";
			std::cout << "* セルの集合の南北(東西)方向の個数 : " << numOfSetOfCellAlongLat_R << "\n";
			std::cout << "* 空車タクシーサークルの半径 : " << vacantTaxiCircleSize_R << "\n";
		}
		std::cout << "========================" << "\n";
	}

	// 保存
	{
		{
			std::string fileName = "Greedy.xml";
			std::string fileDire = "./../Data/0_1_Preset";
			// create a folder
			{
				boost::filesystem::path path(fileDire);
				boost::system::error_code error;
				const bool result = boost::filesystem::create_directories(path, error);
				if (!result || error) {
					// std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
				}
			}
			std::string fileRela = fileDire + "/" + fileName;
			std::cout << fileName << "の作成開始" << std::endl;
			{
				// create an empty property tree
				boost::property_tree::ptree pt;

				// create the root element
				boost::property_tree::ptree& root = pt.put("table", "");

				// add child elements
				{
					{
						boost::property_tree::ptree& child = root.add("gCoorNW_G", "");
						child.put("phi", gCoorNW_G.getPhi());
						child.put("lambda", gCoorNW_G.getLambda());
					}
					{
						boost::property_tree::ptree& child = root.add("gCoorSE_G", "");
						child.put("phi", gCoorSE_G.getPhi());
						child.put("lambda", gCoorSE_G.getLambda());
					}
					{
						boost::property_tree::ptree& child = root.add("addArea_G", "");
						int N = sizeof(addArea_G) / sizeof(addArea_G[0]);
						for (int i = 0; i < N; i++) {
							boost::property_tree::ptree& cchild = child.add("tuples", "");
							cchild.put("phiNW", addArea_G[i][0]);
							cchild.put("lambdaNW", addArea_G[i][1]);
							cchild.put("phiSE", addArea_G[i][2]);
							cchild.put("lambdaSE", addArea_G[i][3]);
						}
					}
					{
						boost::property_tree::ptree& child = root.add("removeArea_G", "");
						int N = sizeof(removeArea_G) / sizeof(removeArea_G[0]);
						for (int i = 0; i < N; i++) {
							boost::property_tree::ptree& cchild = child.add("tuples", "");
							cchild.put("phiNW", removeArea_G[i][0]);
							cchild.put("lambdaNW", removeArea_G[i][1]);
							cchild.put("phiSE", removeArea_G[i][2]);
							cchild.put("lambdaSE", removeArea_G[i][3]);
						}
					}
					{
						boost::property_tree::ptree& child = root.add("cellSizeMeter_G", "");
						child.put("value", cellSizeMeter_G);
					}
					{
						boost::property_tree::ptree& child = root.add("displayDate_G", "");
						int N = sizeof(displayDate_G) / sizeof(displayDate_G[0]);
						for (int i = 0; i < N; i++) {
							boost::property_tree::ptree& cchild = child.add("date", "");
							cchild.put("value", displayDate_G[i][0]);
						}
					}
					{
						boost::property_tree::ptree& child = root.add("displayTimeFrom_G", "");
						child.put("value", displayTimeFrom_G);
					}
					{
						boost::property_tree::ptree& child = root.add("displayTimeTo_G", "");
						child.put("value", displayTimeTo_G);
					}
					{
						boost::property_tree::ptree& child = root.add("searchRange_G", "");
						child.put("value", searchRange_G);
					}
					{
						boost::property_tree::ptree& child = root.add("searchDegree_G", "");
						child.put("value", searchDegree_G);
					}
					{
						boost::property_tree::ptree& child = root.add("baseLengthMin_G", "");
						child.put("value", baseLengthMin_G);
					}
					{
						boost::property_tree::ptree& child = root.add("baseLengthMax_G", "");
						child.put("value", baseLengthMax_G);
					}
					{
						boost::property_tree::ptree& child = root.add("maxDistance_G", "");
						child.put("value", maxDistance_G);
					}
					{
						boost::property_tree::ptree& child = root.add("threshold_G", "");
						child.put("value", threshold_G);
					}
				}
				// output
				boost::property_tree::write_xml(fileRela, pt, std::locale(),
												boost::property_tree::xml_writer_make_settings<std::string>(' ', 2));
			}
			std::cout << fileName << "の作成終了" << std::endl;
		}
		{
			std::string fileName = "Rational.xml";
			std::string fileDire = "./../Data/0_1_Preset";
			// create a folder
			{
				boost::filesystem::path path(fileDire);
				boost::system::error_code error;
				const bool result = boost::filesystem::create_directories(path, error);
				if (!result || error) {
					// std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
				}
			}
			std::string fileRela = fileDire + "/" + fileName;
			std::cout << fileName << "の作成開始" << std::endl;
			{
				// create an empty property tree
				boost::property_tree::ptree pt;

				// create the root element
				boost::property_tree::ptree& root = pt.put("table", "");

				// add child elements
				{
					{
						boost::property_tree::ptree& child = root.add("gCoorNW_R", "");
						child.put("phi", gCoorNW_R.getPhi());
						child.put("lambda", gCoorNW_R.getLambda());
					}
					{
						boost::property_tree::ptree& child = root.add("gCoorSE_R", "");
						child.put("phi", gCoorSE_R.getPhi());
						child.put("lambda", gCoorSE_R.getLambda());
					}
					{
						boost::property_tree::ptree& child = root.add("addArea_R", "");
						int N = sizeof(addArea_R) / sizeof(addArea_R[0]);
						for (int i = 0; i < N; i++) {
							boost::property_tree::ptree& cchild = child.add("tuples", "");
							cchild.put("phiNW", addArea_R[i][0]);
							cchild.put("lambdaNW", addArea_R[i][1]);
							cchild.put("phiSE", addArea_R[i][2]);
							cchild.put("lambdaSE", addArea_R[i][3]);
						}
					}
					{
						boost::property_tree::ptree& child = root.add("removeArea_R", "");
						int N = sizeof(removeArea_R) / sizeof(removeArea_R[0]);
						for (int i = 0; i < N; i++) {
							boost::property_tree::ptree& cchild = child.add("tuples", "");
							cchild.put("phiNW", removeArea_R[i][0]);
							cchild.put("lambdaNW", removeArea_R[i][1]);
							cchild.put("phiSE", removeArea_R[i][2]);
							cchild.put("lambdaSE", removeArea_R[i][3]);
						}
					}
					{
						boost::property_tree::ptree& child = root.add("cellSizeMeter_R", "");
						child.put("value", cellSizeMeter_R);
					}
					{
						boost::property_tree::ptree& child = root.add("displayDate_R", "");
						int N = sizeof(displayDate_R) / sizeof(displayDate_R[0]);
						for (int i = 0; i < N; i++) {
							boost::property_tree::ptree& cchild = child.add("date", "");
							cchild.put("value", displayDate_R[i][0]);
						}
					}
					{
						boost::property_tree::ptree& child = root.add("displayTimeFrom_R", "");
						child.put("value", displayTimeFrom_R);
					}
					{
						boost::property_tree::ptree& child = root.add("displayTimeTo_R", "");
						child.put("value", displayTimeTo_R);
					}
					{
						boost::property_tree::ptree& child = root.add("searchRange_R", "");
						child.put("value", searchRange_R);
					}
					{
						boost::property_tree::ptree& child = root.add("searchDegree_R", "");
						child.put("value", searchDegree_R);
					}
					{
						boost::property_tree::ptree& child = root.add("baseLengthMin_R", "");
						child.put("value", baseLengthMin_R);
					}
					{
						boost::property_tree::ptree& child = root.add("baseLengthMax_R", "");
						child.put("value", baseLengthMax_R);
					}
					{
						boost::property_tree::ptree& child = root.add("maxDistance_R", "");
						child.put("value", maxDistance_R);
					}
					{
						boost::property_tree::ptree& child = root.add("demandCircleSize_R", "");
						child.put("value", demandCircleSize_R);
					}
					{
						boost::property_tree::ptree& child = root.add("demandCircleThreshould_R", "");
						child.put("value", demandCircleThreshould_R);
					}
					{
						boost::property_tree::ptree& child = root.add("numOfSetOfCellAlongLat_R", "");
						child.put("value", numOfSetOfCellAlongLat_R);
					}
					{
						boost::property_tree::ptree& child = root.add("vacantTaxiCircleSize_R", "");
						child.put("value", vacantTaxiCircleSize_R);
					}
				}
				// output
				boost::property_tree::write_xml(fileRela, pt, std::locale(),
												boost::property_tree::xml_writer_make_settings<std::string>(' ', 2));
			}
			std::cout << fileName << "の作成終了" << std::endl;
		}
	}

	// テスト
	std::cout << "読込テスト" << "\n";
	myTestFunc();

    return EXIT_SUCCESS;
}
