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

int myFuncGreedy();
int myFuncGreedy()
{
	std::cout << "Greedyの設定ファイルの作成開始" << "\n";
	// 変数宣言
	GeographicCoordinate gCoorNW_G;
	GeographicCoordinate gCoorSE_G;
	std::vector<GeographicCoordinate> gCoorAddAreaNW_G;
	std::vector<GeographicCoordinate> gCoorAddAreaSE_G;
	std::vector<GeographicCoordinate> gCoorRemoveAreaNW_G;
	std::vector<GeographicCoordinate> gCoorRemoveAreaSE_G;
	double cellSizeMeter_G = 0;
	std::vector<int> displayDate_G;
	int displayTimeFrom_G = 0;
	int displayTimeTo_G = 0;
	double searchRange_G = 0;
	double searchDegree_G = 0;
	double baseLengthMin_G = 0;
	double baseLengthMax_G = 0;
	double maxDistance_G = 0;
	double threshold_G = 0;
	std::cout << "0_1_Presetで設定したファイルの読込開始" << "\n";
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
			{
				gCoorNW_G.setPhi( pt.get<double>( "table.gCoorNW_G.phi" ) );
				gCoorNW_G.setLambda( pt.get<double>( "table.gCoorNW_G.lambda" ) );
			}
			{
				gCoorSE_G.setPhi( pt.get<double>( "table.gCoorSE_G.phi" ) );
				gCoorSE_G.setLambda( pt.get<double>( "table.gCoorSE_G.lambda" ) );
			}
			{
				// addAreaの数を調べる
				int N = 0;
				{
					boost::property_tree::ptree::iterator itr_first, itr_last, it;
					itr_first = pt.get_child( "table.addArea_G" ).begin();
					itr_last = pt.get_child( "table.addArea_G" ).end();
					N = std::distance(itr_first, itr_last);
				}
				// 要素の追加
				gCoorAddAreaNW_G.reserve(N);
				gCoorAddAreaSE_G.reserve(N);
				{
					boost::property_tree::ptree::iterator itr_first, itr_last, it;
					itr_first = pt.get_child( "table.addArea_G" ).begin();
					itr_last = pt.get_child( "table.addArea_G" ).end();
					for(it = itr_first; it != itr_last; ++it) {
						GeographicCoordinate gCoorNWHoge( it->second.get<double>("phiNW"), it->second.get<double>("lambdaNW") );
						GeographicCoordinate gCoorSEHoge( it->second.get<double>("phiSE"), it->second.get<double>("lambdaSE") );
						gCoorAddAreaNW_G.push_back(gCoorNWHoge);
						gCoorAddAreaSE_G.push_back(gCoorSEHoge);
					}
				}
			}
			{
				// removeAreaの数を調べる
				int N = 0;
				{
					boost::property_tree::ptree::iterator itr_first, itr_last, it;
					itr_first = pt.get_child( "table.removeArea_G" ).begin();
					itr_last = pt.get_child( "table.removeArea_G" ).end();
					N = std::distance(itr_first, itr_last);
				}
				// 要素の追加
				gCoorRemoveAreaNW_G.reserve(N);
				gCoorRemoveAreaSE_G.reserve(N);
				{
					boost::property_tree::ptree::iterator itr_first, itr_last, it;
					itr_first = pt.get_child( "table.removeArea_G" ).begin();
					itr_last = pt.get_child( "table.removeArea_G" ).end();
					for(it = itr_first; it != itr_last; ++it) {
						GeographicCoordinate gCoorNWHoge( it->second.get<double>("phiNW"), it->second.get<double>("lambdaNW") );
						GeographicCoordinate gCoorSEHoge( it->second.get<double>("phiSE"), it->second.get<double>("lambdaSE") );
						gCoorRemoveAreaNW_G.push_back(gCoorNWHoge);
						gCoorRemoveAreaSE_G.push_back(gCoorSEHoge);
					}
				}
			}
			{
				cellSizeMeter_G = pt.get<double>("table.cellSizeMeter_G.value");
			}
			{
				// displayDate_Gの数を調べる
				int N = 0;
				{
					boost::property_tree::ptree::iterator itr_first, itr_last, it;
					itr_first = pt.get_child( "table.displayDate_G" ).begin();
					itr_last = pt.get_child( "table.displayDate_G" ).end();
					N = std::distance(itr_first, itr_last);
				}
				// 要素の追加
				displayDate_G.reserve(N);
				{
					boost::property_tree::ptree::iterator itr_first, itr_last, it;
					itr_first = pt.get_child( "table.displayDate_G" ).begin();
					itr_last = pt.get_child( "table.displayDate_G" ).end();
					for(it = itr_first; it != itr_last; ++it) {
						int hoge = it->second.get<int>("value");
						displayDate_G.push_back(hoge);
					}
				}
			}
			{
				displayTimeFrom_G = pt.get<double>("table.displayTimeFrom_G.value");
				displayTimeTo_G = pt.get<double>("table.displayTimeTo_G.value");
				searchRange_G = pt.get<double>("table.searchRange_G.value");
				searchDegree_G = pt.get<double>("table.searchDegree_G.value");
				baseLengthMin_G = pt.get<double>("table.baseLengthMin_G.value");
				baseLengthMax_G = pt.get<double>("table.baseLengthMax_G.value");
				maxDistance_G = pt.get<double>("table.maxDistance_G.value");
				threshold_G = pt.get<double>("table.threshold_G.value");
			}
		}
		std::cout << fileName << "の読込終了" << std::endl;
        // 確認
		{
			std::cout << "========= 確認 =========" << "\n";
			{
				std::cout << "* 営業領域の外枠" << "\n";
				std::cout << "北西 ： " << "\n";
				gCoorNW_G.print();
				std::cout << "南東 ： " << "\n";
				gCoorSE_G.print();
				std::cout << "* 追加領域" << "\n";
				{
					int N = gCoorAddAreaNW_G.size();
					std::cout << "追加領域の数 ： " << N << "\n";
					for (int i = 0; i < N; i++) {
						std::cout << "No." << i+1 << " : 北西 = (" << gCoorAddAreaNW_G[i].getPhi() << ", " << gCoorAddAreaNW_G[i].getLambda() << "), 南西 = (" << gCoorAddAreaSE_G[i].getPhi() << ", " << gCoorAddAreaSE_G[i].getLambda() << ")" << "\n";
					}
				}
				std::cout << "* 削除領域" << "\n";
				{
					int N = gCoorRemoveAreaNW_G.size();
					if (N == 1) {
						std::cout << "削除領域はありません．" << "\n";
					}else{
						std::cout << "削除領域の数 ： " << N-1 << "\n";
						for (int i = 1; i < N; i++) {
							std::cout << "No." << i << " : 北西 = (" << gCoorRemoveAreaNW_G[i].getPhi() << ", " << gCoorRemoveAreaNW_G[i].getLambda() << "), 南西 = (" << gCoorRemoveAreaSE_G[i].getPhi() << ", " << gCoorRemoveAreaSE_G[i].getLambda() << ")" << "\n";
						}
					}
				}
				std::cout <<"* セルサイズ ： " << cellSizeMeter_G << "\n";
				std::cout << "* 表示ピンが何日前のものか" << "\n";
				{
					int N = displayDate_G.size();
					for (int i = 0; i < N; i++) {
						std::cout << displayDate_G[i];
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
			std::cout << "========================" << "\n";
		}
	}
	std::cout << "0_1_Presetで設定したファイルの読込終了" << "\n";
	{
		std::cout << "基本的なマップ情報の作成" << "\n";
		GeographicCoordinate gCoorNW = gCoorNW_G;
		GeographicCoordinate gCoorSE = gCoorSE_G;
		double cellSizeMeter = cellSizeMeter_G;
		// gCoorNWをデカルト座標系の原点にした時のgCoorSEのデカルト座標系での位置を求める。
		CartesianCoordinate cCoorSE = convertGCoorIntoCCoor( gCoorSE, gCoorNW );
		// デカルト座標系で定義された営業領域に対して北から南まで一辺cellSizeMeterの格子を敷き詰めていくと、何枚で営業領域の南北を埋めることができるのか計算する。
		int numRow = ceil( fabs( cCoorSE.getX() ) / cellSizeMeter ); // 絶対値の小数切り上げ
		// デカルト座標系で定義された営業領域に対して西から東まで一辺cellSizeMeterの格子を敷き詰めていくと、何枚で営業領域の東西を埋めることができるのか計算する。
		int numCol = ceil( fabs( cCoorSE.getY() ) / cellSizeMeter ); // 絶対値の小数切り上げ
		int numCell = numRow* numCol;
		// 営業領域の新しい最南東位置に置き換える(デカルト座標)
		cCoorSE.set( (const double)( - numRow * cellSizeMeter ), (const double)( numCol * cellSizeMeter ) );
		// 営業領域の新しい最南東位置に置き換える(地理座標)
		gCoorSE = convertCCoorIntoGCoor( cCoorSE, gCoorNW );
		// 緯度(latitude)方向, 経度(longitude)方向のcellSizeを計算
		double cellSizePhi = (gCoorNW.getPhi() - gCoorSE.getPhi()) / (double)numRow;
		double cellSizeLambda = (gCoorSE.getLambda() - gCoorNW.getLambda()) / (double)numCol;
		// 保存
		{
			std::string fileName = "baseMap.xml";
			std::string fileDire = "./../Data/0_2_Set/Greedy";
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
						boost::property_tree::ptree& child = root.add("numRow", "");
						child.put("value", numRow);
					}
					{
						boost::property_tree::ptree& child = root.add("numCol", "");
						child.put("value", numCol);
					}
					{
						boost::property_tree::ptree& child = root.add("numCell", "");
						child.put("value", numCell);
					}
					{
						boost::property_tree::ptree& child = root.add("cellSizePhi", "");
						child.put("value", cellSizePhi);
					}
					{
						boost::property_tree::ptree& child = root.add("cellSizeLambda", "");
						child.put("value", cellSizeLambda);
					}
				}
				// output
				boost::property_tree::write_xml(fileRela, pt, std::locale(),
												boost::property_tree::xml_writer_make_settings<std::string>(' ', 2));
			}
			std::cout << fileName << "の作成終了" << std::endl;
		}
		std::cout << "各セルの代表点の計算" << "\n";
		std::vector<GeographicCoordinate> gCoorAddAreaNW = gCoorAddAreaNW_G;
		std::vector<GeographicCoordinate> gCoorAddAreaSE = gCoorAddAreaSE_G;
		std::vector<GeographicCoordinate> gCoorRemoveAreaNW = gCoorRemoveAreaNW_G;
		std::vector<GeographicCoordinate> gCoorRemoveAreaSE = gCoorRemoveAreaSE_G;
		// 代表点ベクトルの生成
		std::vector<GeographicCoordinate> vRepresentativePoint(numCell);
		std::vector<int> vIndex(numCell);
		std::vector<int> vRow(numCell);
		std::vector<int> vCol(numCell);
		std::vector<bool> vValid(numCell, false);
		std::vector<int> vTrueIndex(numCell, -1);
		// 値を求める
		{
			std::vector<GeographicCoordinate>::iterator it, itr_first, itr_last;
			itr_first = vRepresentativePoint.begin();
			itr_last = vRepresentativePoint.end();
			for(it = itr_first; it != itr_last; it++) {
				std::size_t i = std::distance(itr_first, it);
				vIndex[i] = i + 1;
				int row = calculateRowFromIndex( i + 1, numCol, numCell );
				vRow[i] = row;
				int col = calculateColFromIndex( i + 1, numCol, numCell );
				vCol[i] = col;
				vRepresentativePoint[i].setPhi( gCoorNW.getPhi() - row * cellSizePhi + cellSizePhi / 2.0 );
				vRepresentativePoint[i].setLambda( gCoorNW.getLambda() + col * cellSizeLambda - cellSizeLambda / 2.0 );
			}
			// addAreaについて
			{
				int N = gCoorAddAreaNW.size();
				for (int i = 0; i < N; i++) {
					// gCoorArea[i]とgCoorが示す領域に重なりがあるのか確認
					// 重なっていない条件
					// 
					// a1 <= x1 < x2 <= a2, b1 <= y1 < y2 <= b2
					// 
					bool overlap = (  ) && (  );


					int addRowN = calculateRowFromLatitudes( gCoorAddAreaNW[i].getPhi(), gCoorNW.getPhi(), gCoorSE.getPhi(), cellSizePhi );
					int addRowS = calculateRowFromLatitudes( gCoorAddAreaSE[i].getPhi(), gCoorNW.getPhi(), gCoorSE.getPhi(), cellSizePhi );
					int addColW = calculateColFromLongitudes( gCoorAddAreaNW[i].getLambda(), gCoorNW.getLambda(), gCoorSE.getLambda(), cellSizeLambda );
					int addColE = calculateColFromLongitudes( gCoorAddAreaSE[i].getLambda(), gCoorNW.getLambda(), gCoorSE.getLambda(), cellSizeLambda );
					// vValidがtrueになる範囲

					// gCoorAddAreaNW[i];
					// gCoorAddAreaSE[i];
				}
			}
			// removeAreaについて
			

		}
		std::cout << "addAreaとremoveAreaから有効セルのindexを求める" << "\n";

		std::cout << "有効セル番号を" << "\n";

	}
	std::cout << "Greedyの設定ファイルの作成終了" << "\n";
    return EXIT_SUCCESS;
}

int myFuncRational();
int myFuncRational()
{
	std::cout << "Rationalの設定ファイルの作成開始" << "\n";
	// 変数宣言
	GeographicCoordinate gCoorNW_R;
	GeographicCoordinate gCoorSE_R;
	std::vector<GeographicCoordinate> gCoorAddAreaNW_R;
	std::vector<GeographicCoordinate> gCoorAddAreaSE_R;
	std::vector<GeographicCoordinate> gCoorRemoveAreaNW_R;
	std::vector<GeographicCoordinate> gCoorRemoveAreaSE_R;
	double cellSizeMeter_R = 0;
	std::vector<int> displayDate_R;
	int displayTimeFrom_R = 0;
	int displayTimeTo_R = 0;
	double searchRange_R = 0;
	double searchDegree_R = 0;
	double baseLengthMin_R = 0;
	double baseLengthMax_R = 0;
	double maxDistance_R = 0;
	double demandCircleSize_R = 0;
	double demandCircleThreshould_R = 0;
	double numOfSetOfCellAlongLat_R = 0;
    double vacantTaxiCircleSize_R = 0;
	std::cout << "0_1_Presetで設定したファイルの読込開始" << "\n";
	{
		std::string fileName = "Rational.xml";
		std::string fileDire = "./../Data/0_1_Preset";
		std::string fileRela = fileDire + "/" + fileName;
		std::cout << fileName << "の読込開始" << std::endl;
		{
			// create an empty property tree
			boost::property_tree::ptree pt;
			// read the xml file
			boost::property_tree::read_xml(fileRela, pt, boost::property_tree::xml_parser::no_comments);
			{
				gCoorNW_R.setPhi( pt.get<double>( "table.gCoorNW_R.phi" ) );
				gCoorNW_R.setLambda( pt.get<double>( "table.gCoorNW_R.lambda" ) );
			}
			{
				gCoorSE_R.setPhi( pt.get<double>( "table.gCoorSE_R.phi" ) );
				gCoorSE_R.setLambda( pt.get<double>( "table.gCoorSE_R.lambda" ) );
			}
			{
				// addAreaの数を調べる
				int N = 0;
				{
					boost::property_tree::ptree::iterator itr_first, itr_last, it;
					itr_first = pt.get_child( "table.addArea_R" ).begin();
					itr_last = pt.get_child( "table.addArea_R" ).end();
					N = std::distance(itr_first, itr_last);
				}
				// 要素の追加
				gCoorAddAreaNW_R.reserve(N);
				gCoorAddAreaSE_R.reserve(N);
				{
					boost::property_tree::ptree::iterator itr_first, itr_last, it;
					itr_first = pt.get_child( "table.addArea_R" ).begin();
					itr_last = pt.get_child( "table.addArea_R" ).end();
					for(it = itr_first; it != itr_last; ++it) {
						GeographicCoordinate gCoorNWHoge( it->second.get<double>("phiNW"), it->second.get<double>("lambdaNW") );
						GeographicCoordinate gCoorSEHoge( it->second.get<double>("phiSE"), it->second.get<double>("lambdaSE") );
						gCoorAddAreaNW_R.push_back(gCoorNWHoge);
						gCoorAddAreaSE_R.push_back(gCoorSEHoge);
					}
				}
			}
			{
				// removeAreaの数を調べる
				int N = 0;
				{
					boost::property_tree::ptree::iterator itr_first, itr_last, it;
					itr_first = pt.get_child( "table.removeArea_R" ).begin();
					itr_last = pt.get_child( "table.removeArea_R" ).end();
					N = std::distance(itr_first, itr_last);
				}
				// 要素の追加
				gCoorRemoveAreaNW_R.reserve(N);
				gCoorRemoveAreaSE_R.reserve(N);
				{
					boost::property_tree::ptree::iterator itr_first, itr_last, it;
					itr_first = pt.get_child( "table.removeArea_R" ).begin();
					itr_last = pt.get_child( "table.removeArea_R" ).end();
					for(it = itr_first; it != itr_last; ++it) {
						GeographicCoordinate gCoorNWHoge( it->second.get<double>("phiNW"), it->second.get<double>("lambdaNW") );
						GeographicCoordinate gCoorSEHoge( it->second.get<double>("phiSE"), it->second.get<double>("lambdaSE") );
						gCoorRemoveAreaNW_R.push_back(gCoorNWHoge);
						gCoorRemoveAreaSE_R.push_back(gCoorSEHoge);
					}
				}
			}
			{
				cellSizeMeter_R = pt.get<double>("table.cellSizeMeter_R.value");
			}
			{
				// displayDate_Gの数を調べる
				int N = 0;
				{
					boost::property_tree::ptree::iterator itr_first, itr_last, it;
					itr_first = pt.get_child( "table.displayDate_R" ).begin();
					itr_last = pt.get_child( "table.displayDate_R" ).end();
					N = std::distance(itr_first, itr_last);
				}
				// 要素の追加
				displayDate_R.reserve(N);
				{
					boost::property_tree::ptree::iterator itr_first, itr_last, it;
					itr_first = pt.get_child( "table.displayDate_R" ).begin();
					itr_last = pt.get_child( "table.displayDate_R" ).end();
					for(it = itr_first; it != itr_last; ++it) {
						int hoge = it->second.get<int>("value");
						displayDate_R.push_back(hoge);
					}
				}
			}
			{
				displayTimeFrom_R = pt.get<double>("table.displayTimeFrom_R.value");
				displayTimeTo_R = pt.get<double>("table.displayTimeTo_R.value");
				searchRange_R = pt.get<double>("table.searchRange_R.value");
				searchDegree_R = pt.get<double>("table.searchDegree_R.value");
				baseLengthMin_R = pt.get<double>("table.baseLengthMin_R.value");
				baseLengthMax_R = pt.get<double>("table.baseLengthMax_R.value");
				maxDistance_R = pt.get<double>("table.maxDistance_R.value");
				demandCircleSize_R = pt.get<double>("table.demandCircleSize_R.value");
				demandCircleThreshould_R = pt.get<double>("table.demandCircleThreshould_R.value");
				numOfSetOfCellAlongLat_R = pt.get<double>("table.numOfSetOfCellAlongLat_R.value");
				vacantTaxiCircleSize_R = pt.get<double>("table.vacantTaxiCircleSize_R.value");
			}
		}
		std::cout << fileName << "の読込終了" << std::endl;
        // 確認
		{
			std::cout << "========= 確認 =========" << "\n";
			{
				std::cout << "* 営業領域の外枠" << "\n";
				std::cout << "北西 ： " << "\n";
				gCoorNW_R.print();
				std::cout << "南東 ： " << "\n";
				gCoorSE_R.print();
				std::cout << "* 追加領域" << "\n";
				{
					int N = gCoorAddAreaNW_R.size();
					std::cout << "追加領域の数 ： " << N << "\n";
					for (int i = 0; i < N; i++) {
						std::cout << "No." << i+1 << " : 北西 = (" << gCoorAddAreaNW_R[i].getPhi() << ", " << gCoorAddAreaNW_R[i].getLambda() << "), 南西 = (" << gCoorAddAreaSE_R[i].getPhi() << ", " << gCoorAddAreaSE_R[i].getLambda() << ")" << "\n";
					}
				}
				std::cout << "* 削除領域" << "\n";
				{
					int N = gCoorRemoveAreaNW_R.size();
					if (N == 1) {
						std::cout << "削除領域はありません．" << "\n";
					}else{
						std::cout << "削除領域の数 ： " << N-1 << "\n";
						for (int i = 1; i < N; i++) {
							std::cout << "No." << i << " : 北西 = (" << gCoorRemoveAreaNW_R[i].getPhi() << ", " << gCoorRemoveAreaNW_R[i].getLambda() << "), 南西 = (" << gCoorRemoveAreaSE_R[i].getPhi() << ", " << gCoorRemoveAreaSE_R[i].getLambda() << ")" << "\n";
						}
					}
				}
				std::cout <<"* セルサイズ ： " << cellSizeMeter_R << "\n";
				std::cout << "* 表示ピンが何日前のものか" << "\n";
				{
					int N = displayDate_R.size();
					for (int i = 0; i < N; i++) {
						std::cout << displayDate_R[i];
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
	}
	std::cout << "0_1_Presetで設定したファイルの読込終了" << "\n";
	
	std::cout << "Rationalの設定ファイルの作成終了" << "\n";
    return EXIT_SUCCESS;
}

int main()
{
	// Greedy
	myFuncGreedy();
	// Rational
	myFuncRational();

    return EXIT_SUCCESS;
}
