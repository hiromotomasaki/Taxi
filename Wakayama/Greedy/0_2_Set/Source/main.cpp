/**
 * main.cpp
 *
 * Copyright (c) 2016 HIROMOTO,Masaki
 *
 */
#include "main.hpp"

using namespace hiro;

// 【この関数の目的】
// Greedy関係の設定値のxmlファイルを基に1_Cron, 2_ForEachRequestで使用する値を事前に作成する.

int main()
{
	// ------------- fileNameから取得するもの  ------------- //
	// 営業領域の外枠の最北西
	GeographicCoordinate gCoorNW;
	// 営業領域の外枠の最南東
	GeographicCoordinate gCoorSE;
	// 追加する営業領域の最北西
	std::vector<GeographicCoordinate> gCoorAddNW;
	// 追加する営業領域の最南東
	std::vector<GeographicCoordinate> gCoorAddSE;
	// 追加する営業領域の最北西
	std::vector<GeographicCoordinate> gCoorRemoveNW;
	// 追加する営業領域の最南東
	std::vector<GeographicCoordinate> gCoorRemoveSE;
	// セルの一辺の長さ[m]
	double cellSizeMeter;
	// 表示するピンの日にちに関する抽出条件
	std::vector<int> displayDate;
	// 表示するピンの時間幅の始点は現在時刻から何分前なのか
	int displayTimeFrom;
	// 表示するピンの時間幅の始点は現在時刻から何分後なのか
	int displayTimeTo;
	// セルから描画するオブジェクトの有効範囲の円の半径[m]
	double searchRange;
	// タクシーの進行方向を考慮した時に描画するオブジェクトの有効範囲の扇型（円に含まれる）の中心角度[deg](45度から180度まで)
	double searchDegree;
	// オブジェクトの底辺の長さの最小値
	double baseLengthMin;
	// オブジェクトの底辺の長さの最大値
	double baseLengthMax;
	// タクシーの進行方向を計算するときに使用する二点間の座標間の距離の最大値．これを越すとオブジェクトは円の中から探索して選ばれる(dir1に相当)．越さなければ進行方向(dir2からdir9)の扇型の中から探索して選ばれる
	double maxDistanceFromPreposition;
	// 需要が集中していると判定するためのしきい値．このしきい値以上であれば需要が集中しているとみなす．
	double threshold;
	// ----------------------------------------------------- //
	// ----------------------- その他 ---------------------- //
	// 設定値の確認表示をするかどうか
	// bool display = true;
	bool display = false;
	// ----------------------------------------------------- //

	// 処理
	{
		// 0_1_Presetで設定したファイルの読込
		{
			std::cout << "0_1_Presetで設定したファイルの読込中..." << "\n";
			// 設定値読み込みファイル名
			std::string fileName = "base.xml";
			// 設定値読み込みファイル先のディレクトリのmakefileからの相対位置
			std::string fileDire = "./../Data/0_1_Preset";
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
					// 数を調べる
					int N = 0;
					{
						boost::property_tree::ptree::iterator itr_first, itr_last, it;
						itr_first = pt.get_child( "table.gCoorAdd" ).begin();
						itr_last = pt.get_child( "table.gCoorAdd" ).end();
						N = std::distance(itr_first, itr_last);
					}
					// 要素の追加
					gCoorAddNW.reserve(N);
					gCoorAddSE.reserve(N);
					{
						boost::property_tree::ptree::iterator itr_first, itr_last, it;
						itr_first = pt.get_child( "table.gCoorAdd" ).begin();
						itr_last = pt.get_child( "table.gCoorAdd" ).end();
						for(it = itr_first; it != itr_last; ++it) {
							gCoorAddNW.push_back(GeographicCoordinate(it->second.get<double>("phiNW"), it->second.get<double>("lambdaNW")));
							gCoorAddSE.push_back(GeographicCoordinate(it->second.get<double>("phiSE"), it->second.get<double>("lambdaSE")));
						}
					}
				}
				{
					// 数を調べる
					int N = 0;
					{
						boost::property_tree::ptree::iterator itr_first, itr_last, it;
						itr_first = pt.get_child( "table.gCoorRemove" ).begin();
						itr_last = pt.get_child( "table.gCoorRemove" ).end();
						N = std::distance(itr_first, itr_last);
					}
					// 要素の追加
					gCoorRemoveNW.reserve(N);
					gCoorRemoveSE.reserve(N);
					{
						boost::property_tree::ptree::iterator itr_first, itr_last, it;
						itr_first = pt.get_child( "table.gCoorRemove" ).begin();
						itr_last = pt.get_child( "table.gCoorRemove" ).end();
						for(it = itr_first; it != itr_last; ++it) {
							gCoorRemoveNW.push_back(GeographicCoordinate(it->second.get<double>("phiNW"), it->second.get<double>("lambdaNW")));
							gCoorRemoveSE.push_back(GeographicCoordinate(it->second.get<double>("phiSE"), it->second.get<double>("lambdaSE")));
						}
					}
				}
				{
					cellSizeMeter = pt.get<double>("table.cellSizeMeter.value");
				}
				{
					// 数を調べる
					int N = 0;
					{
						boost::property_tree::ptree::iterator itr_first, itr_last, it;
						itr_first = pt.get_child( "table.displayDate" ).begin();
						itr_last = pt.get_child( "table.displayDate" ).end();
						N = std::distance(itr_first, itr_last);
					}
					// 要素の追加
					displayDate.reserve(N);
					{
						boost::property_tree::ptree::iterator itr_first, itr_last, it;
						itr_first = pt.get_child( "table.displayDate" ).begin();
						itr_last = pt.get_child( "table.displayDate" ).end();
						for(it = itr_first; it != itr_last; ++it) {
							displayDate.push_back(it->second.get<int>("value"));
						}
					}
				}
				{
					displayTimeFrom = pt.get<double>("table.displayTimeFrom.value");
					displayTimeTo = pt.get<double>("table.displayTimeTo.value");
					searchRange = pt.get<double>("table.searchRange.value");
					searchDegree = pt.get<double>("table.searchDegree.value");
					baseLengthMin = pt.get<double>("table.baseLengthMin.value");
					baseLengthMax = pt.get<double>("table.baseLengthMax.value");
					maxDistanceFromPreposition = pt.get<double>("table.maxDistanceFromPreposition.value");
					threshold = pt.get<double>("table.threshold.value");
				}
			}
		}
		// 基本的な営業領域の情報の作成(内部でgCoorSEに変更あり)
		// 営業領域の外枠の行数
		int numRow;
		// 営業領域の外枠の列数
		int numCol;
		// 営業領域の外枠内にあるセル数
		int numCell;
		// セルの南北の緯度差
		double cellSizePhi;
		// セルの東西の経度差
		double cellSizeLambda;
		{
			std::cout << "基本的な営業領域の情報の作成中..." << "\n";
			// gCoorNWをデカルト座標系の原点にした時のgCoorSEのデカルト座標系での位置を求める。
			CartesianCoordinate cCoorSE = convertGCoorIntoCCoor( gCoorSE, gCoorNW );
			// デカルト座標系で定義された営業領域に対して北から南まで一辺cellSizeMeterの格子を敷き詰めていくと、何枚で営業領域の南北を埋めることができるのか計算する。
			numRow = ceil( fabs( cCoorSE.getX() ) / cellSizeMeter ); // 絶対値の小数切り上げ
			// デカルト座標系で定義された営業領域に対して西から東まで一辺cellSizeMeterの格子を敷き詰めていくと、何枚で営業領域の東西を埋めることができるのか計算する。
			numCol = ceil( fabs( cCoorSE.getY() ) / cellSizeMeter ); // 絶対値の小数切り上げ
			numCell = numRow * numCol;
			// 営業領域の新しい最南東位置に置き換える(デカルト座標)
			cCoorSE.set( (const double)( - numRow * cellSizeMeter ), (const double)( numCol * cellSizeMeter ) );
			// 営業領域の新しい最南東位置に置き換える(地理座標)
			gCoorSE = convertCCoorIntoGCoor( cCoorSE, gCoorNW );
			// 緯度(latitude)方向, 経度(longitude)方向のcellSizeを計算
			cellSizePhi = (gCoorNW.getPhi() - gCoorSE.getPhi()) / (double)numRow;
			cellSizeLambda = (gCoorSE.getLambda() - gCoorNW.getLambda()) / (double)numCol;
		}
		// 各セルの代表点や有効かどうかなどの情報を計算
		std::vector<GeographicCoordinate> vRepresentativePoint(numCell);
		std::vector<int> vIndex(numCell);
		std::vector<int> vRow(numCell);
		std::vector<int> vCol(numCell);
		std::vector<bool> vValid(numCell, false);
		int numValidCell;
		{
			std::cout << "各セルの代表点や有効かどうかなどの情報を計算中..." << "\n";
			// vRepresentativePoint, vIndex, vRow, vColの作成
			{
				std::vector<GeographicCoordinate>::iterator it, itr_first, itr_last;
				itr_first = vRepresentativePoint.begin();
				itr_last = vRepresentativePoint.end();
				for(it = itr_first; it != itr_last; it++) {
					std::size_t i = std::distance(itr_first, it);
					vIndex[i] = i + 1;
					int row = calculateRowFromIndex( vIndex[i], numCol, numCell );
					vRow[i] = row;
					int col = calculateColFromIndex( vIndex[i], numCol, numCell );
					vCol[i] = col;
					vRepresentativePoint[i].setPhi( gCoorNW.getPhi() - row * cellSizePhi + cellSizePhi / 2.0 );
					vRepresentativePoint[i].setLambda( gCoorNW.getLambda() + col * cellSizeLambda - cellSizeLambda / 2.0 );
				}
			}
			// vValid, numValidCellの作成
			{
				// gCoorAddに基づいてvValidを編集
				{
					int N = gCoorAddNW.size();
					for (int i = 0; i < N; i++) {
						// gCoorに対してgCoorAddが重なりを持つか確認
						bool isOver = ( gCoorAddSE[i].getPhi() >= gCoorNW.getPhi() );
						bool isUnder = ( gCoorAddNW[i].getPhi() <= gCoorSE.getPhi() );
						bool isOnTheRight = ( gCoorAddNW[i].getLambda() >= gCoorSE.getLambda() );
						bool isOnTheLeft = ( gCoorAddSE[i].getLambda() <= gCoorNW.getLambda() );
						bool overlap = !( isOver || isUnder || isOnTheRight || isOnTheLeft );
						if (overlap) {
							int RowN = calculateRowFromLatitudes( gCoorAddNW[i].getPhi(), gCoorNW.getPhi(), gCoorSE.getPhi(), cellSizePhi );
							int RowS = calculateRowFromLatitudes( gCoorAddSE[i].getPhi(), gCoorNW.getPhi(), gCoorSE.getPhi(), cellSizePhi );
							int ColE = calculateColFromLongitudes( gCoorAddSE[i].getLambda(), gCoorNW.getLambda(), gCoorSE.getLambda(), cellSizeLambda );
							int ColW = calculateColFromLongitudes( gCoorAddNW[i].getLambda(), gCoorNW.getLambda(), gCoorSE.getLambda(), cellSizeLambda );
							{
								if (RowN == 0) {
									RowN = 1;
								}
								if (RowS == 0) {
									RowS = numRow;
								}
								if (ColE == 0) {
									ColE = numCol;
								}
								if (ColW == 0) {
									ColW = 1;
								}
							}
							// (RowN, RowS, ColE, ColW)の領域のvValidをtrueにする
							for (int j = RowN; j <= RowS; j++) {
								for (int k = ColW; k <= ColE; k++) {
									int indexHoge = calculateIndexFromRowCol( j, k, numRow, numCol );
									vValid[indexHoge - 1] = true;
								}
							}
						}
					}
				}
				// gCoorRemoveに基づいてvValidを編集
				{
					{
						// 配列の1行目はダミー
						int N = gCoorRemoveNW.size();
						if (N >= 2) {
							for (int i = 1; i < N; i++) {
								// gCoorに対してgCoorAddが重なりを持つか確認
								bool isOver = ( gCoorRemoveSE[i].getPhi() >= gCoorNW.getPhi() );
								bool isUnder = ( gCoorRemoveNW[i].getPhi() <= gCoorSE.getPhi() );
								bool isOnTheRight = ( gCoorRemoveNW[i].getLambda() >= gCoorSE.getLambda() );
								bool isOnTheLeft = ( gCoorRemoveSE[i].getLambda() <= gCoorNW.getLambda() );
								bool overlap = !( isOver || isUnder || isOnTheRight || isOnTheLeft );
								if (overlap) {
									int RowN = calculateRowFromLatitudes( gCoorAddNW[i].getPhi(), gCoorNW.getPhi(), gCoorSE.getPhi(), cellSizePhi );
									int RowS = calculateRowFromLatitudes( gCoorAddSE[i].getPhi(), gCoorNW.getPhi(), gCoorSE.getPhi(), cellSizePhi );
									int ColE = calculateColFromLongitudes( gCoorAddSE[i].getLambda(), gCoorNW.getLambda(), gCoorSE.getLambda(), cellSizeLambda );
									int ColW = calculateColFromLongitudes( gCoorAddNW[i].getLambda(), gCoorNW.getLambda(), gCoorSE.getLambda(), cellSizeLambda );
									{
										if (RowN == 0) {
											RowN = 1;
										}else{
											RowN++;
										}
										if (RowS == 0) {
											RowS = numRow;
										}else{
											RowS--;
										}
										if (ColE == 0) {
											ColE = numCol;
										}else{
											ColE--;
										}
										if (ColW == 0) {
											ColW = 1;
										}else{
											ColW++;
										}
									}
									bool checkRow = ( RowN >= 1 ) && ( RowN <= numRow ) && ( RowS >= 1 ) && ( RowS <= numRow ) && ( RowN <= RowS );
									bool checkCol = ( ColE >= 1 ) && ( ColE <= numCol ) && ( ColW >= 1 ) && ( ColW <= numCol ) && ( ColW <= ColE );
									bool check = checkRow && checkCol;
									if (check) {
										// (RowN, RowS, ColE, ColW)の領域のvValidをtrueにする
										for (int j = RowN; j <= RowS; j++) {
											for (int k = ColW; k <= ColE; k++) {
												int indexHoge = calculateIndexFromRowCol( j, k, numRow, numCol );
												vValid[indexHoge - 1] = false;
											}
										}
									}
								}
							}
						}
					}
				}
				// vValidのtrueの数を数えてnumValidCellを作成
				{
					numValidCell = 0;
					std::vector<bool>::iterator it, itr_first, itr_last;
					itr_first = vValid.begin();
					itr_last = vValid.end();
					for(it = itr_first; it != itr_last; it++) {
						if (*it) {
							numValidCell++;
						}
					}
				}
			}
		}
		// ここまでの営業領域に関する情報を保存
		{
			std::cout << "ここまでの営業領域に関する情報を保存" << "\n";
			// baseMap.xml
			{
				// 設定値保存ファイル名
				std::string fileName = "baseMap.xml";
				// 設定値保存ファイル先のディレクトリのmakefileからの相対位置
				std::string fileDire = "./../Data/0_2_Set";
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
							boost::property_tree::ptree& child = root.add("cellSizeMeter", "");
							child.put("value", cellSizeMeter);
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
							boost::property_tree::ptree& child = root.add("numValidCell", "");
							child.put("value", numValidCell);
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
					boost::property_tree::write_xml(fileRela, pt, std::locale(), boost::property_tree::xml_writer_make_settings<std::string>(' ', 2));
				}

			}
			// representativePoints.xml
			{
				// 設定値保存ファイル名
				std::string fileName = "representativePoints.xml";
				// 設定値保存ファイル先のディレクトリのmakefileからの相対位置
				std::string fileDire = "./../Data/0_2_Set";
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
						for (int i = 0; i < numCell; i++) {
							boost::property_tree::ptree& child = root.add("cell", "");
							child.put("index", vIndex[i]);
							child.put("isValid", vValid[i]);
							child.put("row", vRow[i]);
							child.put("col", vCol[i]);
							child.put("position.phi", vRepresentativePoint[i].getPhi());
							child.put("position.lambda", vRepresentativePoint[i].getLambda());
						}
					}

					// output
					boost::property_tree::write_xml(fileRela, pt, std::locale(), boost::property_tree::xml_writer_make_settings<std::string>(' ', 2));
				}
			}
			// isValid/(i+1).xml
			{
				// 設定値保存ファイル先のディレクトリのmakefileからの相対位置
				std::string fileDire = "./../Data/0_2_Set/isValid";
				// ディレクトリの削除 : isValid/
				{
					boost::filesystem::path path(fileDire);
					boost::filesystem::remove_all(path);
				}
				// ディレクトリの作成
				{
					boost::filesystem::path path(fileDire);
					boost::system::error_code error;
					const bool result = boost::filesystem::create_directories(path, error);
					if (!result || error) {
						// std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
					}
				}
				std::cout << fileDire << "内のファイルを保存中..." << std::endl;
				// 設定値保存ファイル名
				for (int i = 0; i < numCell; i++) {
					std::string fileName = boost::lexical_cast<std::string>( i+1 ) + ".xml";
										// 保存path
					std::string fileRela = fileDire + "/" + fileName;
					// create an empty property tree
					boost::property_tree::ptree pt;

					// create the root element
					boost::property_tree::ptree& root = pt.put("table", "");

					// add child elements
					{
						{
							boost::property_tree::ptree& child = root.add("isValid", "");
							child.put("value", vValid[i]);
						}
					}
					// output
					boost::property_tree::write_xml(fileRela, pt, std::locale(), boost::property_tree::xml_writer_make_settings<std::string>(' ', 2));
				}
			}
		}
		// vValidがtrueのセルに対してのみ, 円状の探索範囲や描画するオブジェクト, 扇型の探索範囲を定めて保存
		{
			std::cout << "vValidがtrueのセルに対してのみ, 円状の探索範囲や描画するオブジェクト, 扇型の探索範囲を定める" << "\n";
			// ディレクトリの削除 : infoAboutValidCells/
			{
				// 設定値保存ファイル先のディレクトリのmakefileからの相対位置
				std::string fileDire = "./../Data/0_2_Set/infoAboutValidCells";
				boost::filesystem::path path(fileDire);
				boost::filesystem::remove_all(path);
			}
			for (int i = 0; i < numCell; i++) {
				// 進行状況の描画
				if (display) {
					if (vValid[i]) {
						std::cout << "[" << i+1 << ", " << numCell << "]" << "\n";
					}else{
						std::cout << "[" << i+1 << ", " << numCell << "]" << " -> Passed" << "\n";
					}
				}
				// 有効な各セルでの処理
				if (vValid[i]) {
					// ディレクトリの作成
					// infoAboutValidCells/(i+1)/
					{
						std::string fileDire = "./../Data/0_2_Set/infoAboutValidCells/" + boost::lexical_cast<std::string>( i+1 );
						boost::filesystem::path path(fileDire);
						boost::system::error_code error;
						const bool result = boost::filesystem::create_directories(path, error);
						if (!result || error) {
							// std::cout << "ディレクトリの作成に失敗したか、すでにあります。" << std::endl;
						}
					}



















					
					// vValidを考慮した円状の探索範囲を定める : infoAboutValidCells/(i+1)/searchRange.xml
					{
						
					}
					// 先ほど作成した円状の探索範囲に対応するオブジェクトを生成する．
					// : infoAboutValidCells/(i+1)/object/(j+1).xml
					// : infoAboutValidCells/(i+1)/object/(j+1)/dir(k).xml  (i == jのとき. kは1から9まで)
					{

					}
					// 先ほど作成した円状の探索範囲に対応する扇型の探索範囲を作成する
				}
			}
		}
		// 空のオブジェクトの生成
		{

		}
		


	}
    return EXIT_SUCCESS;
}
