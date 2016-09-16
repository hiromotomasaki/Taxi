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
// ミューラルネットワークを学習する
// 時間幅を最小に見積もって1分なので, 1時間で60, 24時間で1440, 1年で525600, 2年で1051200個となり、学習データ数の最大値は1051200である。
// 約数は
// 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 16, 18, 20, 24, 25, 30, 32, 36, 40, 45, 48, 50, 60, 64, 72, 73, 75, 80, 90, 96, 100, 120, 144, 146, 150, 160, 180, 192, 200, 219, 225, 240, 288, 292, 300, 320, 360, 365, 400, 438, 450, 480, 576, 584, 600, 657, 720, 730, 800, 876, 900, 960, 1095, 1168, 1200, 1314, 1440, 1460, 1600, 1752, 1800, 1825, 2190, 2336, 2400, 2628, 2880, 2920, 3285, 3504, 3600, 3650, 4380, 4672, 4800, 5256, 5475, 5840, 6570, 7008, 7200, 7300, 8760, 10512, 10950, 11680, 13140, 14016, 14400, 14600, 16425, 17520, 21024, 21900, 23360, 26280, 29200, 32850, 35040, 42048, 43800, 52560, 58400, 65700, 70080, 87600, 105120, 116800, 131400, 175200, 210240, 262800, 350400, 525600, 1051200
// である。
// まず、入力データの不足があれば1051200になるようにランダムに複製する。
// もし、2年以上分の入力データがあり1051200を超過する場合はランダムにデータを取り除き、1051200個のデータにする。
//
// =================================================================================== //


// 構造体の宣言
struct InputData {
  boost::posix_time::ptime pTimeRound;
  double maxTemp;
  double minTemp;
  double dayW;
  double nightW;
};
struct OutputData {
  double allDemand;
  std::vector<double> demand;
};
struct PairData {
  InputData input;
  OutputData output;
};
struct X {
  std::vector<double> x;
};
struct Y {
  std::vector<double> y;
};


  // std::vector<double> step;			// 1日のうち何ステップ目なのか(もし時間幅が2分なら1日は1440分なので720ステップ, 1ステップ目は前日の23:59から0:00:59, 720ステップ目は23:57から23:58:59)
  // double day_5_10_20_lastDay;	// 5, 10, 20日, 月末であれば1, そうでなければ0
  // double holiday;			// 土日や祝日なら1, そうでなければ0
  // double month12to2;		// 12月から2月なら1, そうでなければ0
  // double month3to5;		// 3月から5月なら1, そうでなければ0
  // double month6to8;		// 6月から8月なら1, そうでなければ0
  // double month9to11;		// 9月から11月なら1, そうでなければ0

  // double dayW;			// (6:00から18:00までの天候, 雨 : 1, 雨ではない : 0)
  // double nightW;			// (18:00から翌日の6:00までの天候, 雨 : 1, 雨ではない : 0)

  // double maxTemp;	     // その日の最高気温
  // double minTemp;	     // その日の最低気温

// vectorからindex番目の要素を削除する
template<typename T>
void remove(std::vector<T>& vector, unsigned int index)
{
    vector.erase(vector.begin() + index);
}

int main(void)
{


  int batchSize = 100;
  std::cout << "[学習時のバッチサイズ]" << batchSize << std::endl;

  // full_data.xmlの読込み
  boost::property_tree::ptree tree;
  {
    // ----------- 読込ファイル名 ----------- //
    const std::string fileName = "full_data.xml";
    // -------------------------------------- //
    const std::string fileDire = "./../../Data/OtherData/FromServer";
    const std::string file = fileDire + "/" + fileName;
    const int flag = boost::property_tree::xml_parser::no_comments;
    boost::property_tree::read_xml(file, tree, flag);
  }
  // データ数
  std::size_t numTreeNode = 0;
  {
    boost::property_tree::ptree::iterator itr_first, itr_last, it;
    itr_first = tree.get_child( "table" ).begin();
    itr_last = tree.get_child( "table" ).end();
    numTreeNode = std::distance(itr_first, itr_last);
  }
  std::cout << "[ノードの数] : " << numTreeNode << std::endl;
  if( numTreeNode <= 1 ) {
    std::cout << "データ数が少なすぎます" << std::endl;
    return EXIT_FAILURE;
  }
  // 営業領域情報の取得
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
  // 時間幅の取得
  int discreteTimeWidth = 0;
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
    }
  }
  // メモ
  // TABLE-DATA-ID
  //           -START_DATE
  //           -START_POINT
  //           -END_DATE
  //           -END_POINT
  //           -MAX_TEMP (その日の最高気温)
  //           -MIN_TEMP (その日の最低気温)
  //           -DAY_W (6:00から18:00までの天候, 雨 : 1, 雨ではない : 0)
  //           -NIGHT_W (18:00から翌日の6:00までの天候, 雨 : 1, 雨ではない : 0)
  std::cout << "学習データ領域準備" << std::endl;
  std::vector<X> vecX;
  vecX.reserve(1051200);
  std::vector<Y> vecY;
  vecY.reserve(1051200);

  std::cout << "学習データ領域準備完了" << std::endl;
  {
    std::vector<PairData> pairData;
    std::cout << "学習対データ領域準備" << std::endl;
    pairData.reserve(numTreeNode);
    std::cout << "学習対データ領域準備完了" << std::endl;
    {
      boost::property_tree::ptree::iterator itr_first, itr_last, it;
      itr_first = tree.get_child( "table" ).begin();
      itr_last = tree.get_child( "table" ).end();
      for(it = itr_first; it != itr_last; it++) {
	// ************ データの種類 ************ //
	// it->second.get<int>("ID");
	// it->second.get<std::string>("START_DATE");
	// it->second.get<std::string>("START_POINT");
	// it->second.get<std::string>("END_DATE");
	// it->second.get<std::string>("END_POINT");
	// it->second.get<double>("MAX_TEMP");
	// it->second.get<double>("MIN_TEMP");
	// it->second.get<int>("DAY_W");
	// it->second.get<int>("NIGHT_W");
	// ************************************* //
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
	// 範囲外だとindex = 0になる
	if( index != 0 ) {
	  // START_DATEを取得する
	  std::string sTimeStr = it->second.get<std::string>("startDate");
	  // 空文字の除去
	  boost::trim (sTimeStr);
	  // boost::posix_time::ptime 型に変換
	  boost::posix_time::ptime pTime = boost::posix_time::time_from_string(sTimeStr);
	  // 時間を丸める
	  boost::posix_time::ptime pTimeRound = roundPTime(pTime, discreteTimeWidth);
	  // 前データノードに追加する
	  if( pairData.size() == 0 ) {
	    // データの単純な追加
	    PairData hogePairData;
	    hogePairData.input.pTimeRound = pTimeRound;
	    hogePairData.input.maxTemp = it->second.get<double>("maxTemp");
	    hogePairData.input.minTemp = it->second.get<double>("minTemp");
	    hogePairData.input.dayW = it->second.get<int>("dayW");
	    hogePairData.input.nightW = it->second.get<int>("nightW");
	    hogePairData.output.demand.resize(numCell, 0);
	    hogePairData.output.demand[index-1]++;
	    hogePairData.output.allDemand = 1;
	    pairData.push_back(hogePairData);
	  }else{
	    // pairDataの要素をループして、pTimeRoundと一致するpairData.input.pTimeRoundが無いか探す。
	    std::vector<PairData>::iterator itr_PairData_first, itr_PairData_last, it_PairData;
	    itr_PairData_first = pairData.begin();
	    itr_PairData_last = pairData.end();
	    bool existsPairData = false;
	    for(it_PairData = itr_PairData_first; it_PairData != itr_PairData_last; it_PairData++) {
	      if( it_PairData -> input.pTimeRound == pTimeRound ) {
		existsPairData = true;
		// 既存の要素の内容を変更する
		{
		  it_PairData -> output.demand[index-1]++;
		  it_PairData -> output.allDemand++;
		}
		break;
	      }
	    }
	    if( existsPairData == false ) {
	      // 新規の要素を追加する
	      PairData hogePairData;
	      hogePairData.input.pTimeRound = pTimeRound;
	      hogePairData.input.maxTemp = it->second.get<double>("maxTemp");
	      hogePairData.input.minTemp = it->second.get<double>("minTemp");
	      hogePairData.input.dayW = it->second.get<int>("dayW");
	      hogePairData.input.nightW = it->second.get<int>("nightW");
	      hogePairData.output.demand.resize(numCell, 0);
	      hogePairData.output.demand[index-1]++;
	      hogePairData.output.allDemand = 1;
	      pairData.push_back(hogePairData);
	    }
	  }
	}
      }
    }
    // pairDataの確認
    // {
    //   std::vector<PairData>::iterator itr_PairData_first, itr_PairData_last, it_PairData;
    //   itr_PairData_first = pairData.begin();
    //   itr_PairData_last = pairData.end();
    //   for(it_PairData = itr_PairData_first; it_PairData != itr_PairData_last; it_PairData++) {
    //     std::cout << it_PairData -> input.pTimeRound << std::endl;
    //   }
    // }
    // データのシャッフル
    std::cout << "データシャッフル開始" << std::endl;
    {
      std::random_device rnd;
      // メルセンヌ・ツイスタ 引数は初期シード値 ファンクタを渡す
      std::mt19937 mt(rnd());
      std::shuffle(pairData.begin(), pairData.end(), mt);
    }
    std::cout << "データシャッフル終了" << std::endl;
    // pairDataの確認
    // {
    //   std::vector<PairData>::iterator itr_PairData_first, itr_PairData_last, it_PairData;
    //   itr_PairData_first = pairData.begin();
    //   itr_PairData_last = pairData.end();
    //   for(it_PairData = itr_PairData_first; it_PairData != itr_PairData_last; it_PairData++) {
    //     std::cout << it_PairData -> input.pTimeRound << std::endl;
    //   }
    // }

    vecX.resize( pairData.size() );
    vecY.resize( pairData.size() );
    // 要素の確保
    // 720+10=730
    for (int i = 0; i < (int)vecX.size(); i++) {
      vecX[i].x.reserve(730);
      vecX[i].x.resize(730, 0);
    }
    for (int i = 0; i < (int)vecY.size(); i++) {
      vecY[i].y.reserve(numCell+1);
      vecY[i].y.resize( numCell+1, 0 );
    }
    // vecXとvecYにpairDataの情報を変換して詰め込む
    {
      std::vector<PairData>::iterator itr_PairData_first, itr_PairData_last, it_PairData;
      itr_PairData_first = pairData.begin();
      itr_PairData_last = pairData.end();
      for(it_PairData = itr_PairData_first; it_PairData != itr_PairData_last; it_PairData++) {
	std::size_t num = std::distance(itr_PairData_first, it_PairData);
	// inputのデータの処理
	int step = 0;		// vecX[num].x[0~719]
	int day_5_10_20_lastDay = 0; // vecX[num].x[720]
	int holiday = 0;	     // vecX[num].x[721]
	int month12to2 = 0;	     // vecX[num].x[722]
	int month3to5 = 0;	     // vecX[num].x[723]
	int month6to8 = 0;	     // vecX[num].x[724]
	int month9to11 = 0;	     // vecX[num].x[725]

	int dayW = 0;		// vecX[num].x[726]
	int nightW = 0;		// vecX[num].x[727]

	double maxTemp = 0;	// vecX[num].x[728]
	double minTemp = 0;	// vecX[num].x[729]
	{
	  boost::posix_time::ptime pTimeRound = it_PairData -> input.pTimeRound;
	  maxTemp = it_PairData -> input.maxTemp;
	  minTemp = it_PairData -> input.minTemp;
	  dayW = it_PairData -> input.dayW;
	  nightW = it_PairData -> input.nightW;
	  {
	    // 時刻と分を取得
	    int hours = pTimeRound.time_of_day().hours();
	    int minutes = pTimeRound.time_of_day().minutes();
	    int sumMinutes = 60 * hours + minutes;
	    step = sumMinutes / discreteTimeWidth + 1;
	  }
	  {
	    int days = pTimeRound.date().day();
	    if( days == 5 || days == 10 || days == 20 ) {
	      day_5_10_20_lastDay = 1;
	    }else{
	      int years = pTimeRound.date().year();
	      int months = pTimeRound.date().month().as_number();
	      bool isMonthEnd = ( days == GetLastDay( years, months) );
	      if( isMonthEnd == true ) {
		day_5_10_20_lastDay = 1;
	      }
	    }
	  }
	  {
	    int dayOfWeek = pTimeRound.date().day_of_week().as_number(); // Sunday == 0, Monday == 1, Saturday == 6
	    if( dayOfWeek == 0 || dayOfWeek == 6 ) {
	      holiday = 1;
	    }else {
	      // 祝日かどうかの確認
	      bool isHoliday = false;
	      if( 5 == Holiday( my_to_time_t( pTimeRound ) ) ) {
		isHoliday = true;
	      }
	      if( isHoliday == true ) {
		holiday = 1;
	      }
	    }
	  }
	  {
	    int months = pTimeRound.date().month().as_number();
	    if( months == 12 || months == 1 || months == 2 ) {
	      month12to2 = 1;
	    }else if( months == 3 || months == 4 || months == 5 ) {
	      month3to5 = 1;
	    }else if( months == 6 || months == 7 || months == 8 ) {
	      month6to8 = 1;
	    }else{
	      month9to11 =1;
	    }
	  }
	}
	vecX[num].x[step-1] = 1;
	vecX[num].x[720] = day_5_10_20_lastDay;
	vecX[num].x[721] = holiday;
	vecX[num].x[722] = month12to2;
	vecX[num].x[723] = month3to5;
	vecX[num].x[724] = month6to8;
	vecX[num].x[725] = month9to11;
	vecX[num].x[726] = dayW;
	vecX[num].x[727] = nightW;
	vecX[num].x[728] = maxTemp; // 後で正規化
	vecX[num].x[729] = minTemp; // 後で正規化

	// outputのデータの処理
	vecY[num].y[0] = it_PairData -> output.allDemand;
	for (int i = 1; i <= numCell; i++) {
	  vecY[num].y[i] = it_PairData -> output.demand[i-1];
	}
      }
    }
  }
  std::cout << "[同年月日同時刻のデータをまとめてできるデータの数]" << vecX.size() << std::endl;
  if( batchSize > (int)vecX.size() ) {
    std::cout << "データ数が少なすぎます" << std::endl;
    return EXIT_FAILURE;
  }
  // データの準備完了(vecX[num].xは720 + 10次元)
  // 気温に関して、正規化処理を行う(一様分布を仮定)
  // minとmaxを求める.
  std::vector<double> vecXMin(2, DBL_MAX);
  std::vector<double> vecXMax(2, -DBL_MAX);

  for (int i = 0; i < (int)vecX.size(); i++) {
    {
      double hoge = vecX[i].x[728]; // maxTemp
      if( hoge > vecXMax[0] ) {
  	vecXMax[0] = hoge;
      }
      if( hoge < vecXMin[0] ) {
  	vecXMin[0] = hoge;
      }
    }
    {
      double hoge = vecX[i].x[729]; // minTemp
      if( hoge > vecXMax[1] ) {
  	vecXMax[1] = hoge;
      }
      if( hoge < vecXMin[1] ) {
  	vecXMin[1] = hoge;
      }
    }
  }

  // minとmaxがほぼ一致(pow(10, -4))した時の例外処理(差を1にする)
  {
    double sa = pow(10, -4);
    for (int i = 0; i < (int)vecXMin.size(); i++) {
      if( vecXMax[i] - vecXMin[i] < sa ) {
  	vecXMax[i] = vecXMin[i] + 1;
      }
    }
  }

  for (int i = 0; i < (int)vecX.size(); i++) {
    vecX[i].x[728] = (vecX[i].x[728] - vecXMin[0]) / (double) (vecXMax[0] - vecXMin[0]);
    vecX[i].x[729] = (vecX[i].x[729] - vecXMin[1]) / (double) (vecXMax[1] - vecXMin[1]);
  }
  ///////////////////////////////////////////////////

  std::cout << "データ準備完了" << std::endl;

  // ニューラルネットワークの学習
  {
    int numData = vecX.size() - vecX.size() % batchSize;
    std::cout << "[バッチサイズの大きさを考慮して実際に使用するデータ数]" << numData << std::endl;
    int numInputVar = 730;
    int numOutputVar = vecY[0].y.size();
    std::cout << "[入力次元]" << numInputVar << std::endl;
    std::cout << "[出力次元]" << numOutputVar << std::endl;
    std::vector<double> input_data( numInputVar * numData );
    std::vector<double> target_data( numOutputVar * numData );
    for (int i = 0; i < numData; i++) {
      for (int j = 0; j < numInputVar; j++) {
  	input_data[i * numInputVar + j] = vecX[i].x[j];
      }
      for (int j = 0; j < numOutputVar; j++) {
  	target_data[i * numOutputVar + j] = vecY[i].y[j];
      }
    }
    // 入力と出力の準備はできた
    // ダミーデータの作成
    std::vector<double> dummy_data( numData, 0 );
    // 求解の設定パラメータを保持する型
    caffe::SolverParameter solver_param;
    // 設定ファイルから設定パラメータを読み込む(const string &filename, Message *proto)
    caffe::ReadProtoFromTextFileOrDie("Source/solver.prototxt", &solver_param);
    // std::shared_ptrはスマートポインタ.
    // std::shared_ptr<リソース型> 変数名(リソースの生ポインタ);
    // caffe::Solver<double>
    // An interface for classes that perform optimization on Nets.
    // solveをスマートポインタの変数名として使う
    caffe::SolverRegistry<double>::CreateSolver(solver_param);
    // Get a solver using a SolverParameter.
    std::shared_ptr<caffe::Solver<double>> solver(caffe::SolverRegistry<double>::CreateSolver(solver_param));
    const boost::shared_ptr<caffe::Net<double> > net = solver->net();
    const boost::shared_ptr<caffe::MemoryDataLayer<double> > input_layer = boost::dynamic_pointer_cast<caffe::MemoryDataLayer<double>>( net->layer_by_name("input") );
    // num_dataはバッチサイズの整数倍でなければいけない
    input_layer -> caffe::MemoryDataLayer<double>::Reset( &input_data[0], &dummy_data[0], numData);

    // 層の中からoutputの名前がつけられた層のポインタを取得
    const boost::shared_ptr<caffe::MemoryDataLayer<double> > target_layer = boost::dynamic_pointer_cast<caffe::MemoryDataLayer<double>>( net->layer_by_name("target") );
    // num_dataはバッチサイズの整数倍でなければいけない
    target_layer -> caffe::MemoryDataLayer<double>::Reset( &target_data[0], &dummy_data[0], numData);

    // Solverの設定通りに学習を行う
    std::cout << "学習開始" << std::endl;
    solver->Solve();
    std::cout << "学習終了" << std::endl;
    // 学習結果は自動保存
  }

  std::cout << "正規化パラメータの保存" << std::endl;
  {
    boost::property_tree::ptree tree;
    const std::string fileDire = "./../../Data/OtherData/OtherData/Neural";
    const std::string fileName = "MaxAndMin.xml";
    const std::string fileRela = fileDire + "/" + fileName;
    // treeのノードの追加
    {
      for (int i = 0; i < 2; i++) {
        boost::property_tree::ptree childTree;
        childTree.put("max", (double)vecXMax[i]);
        childTree.put("min", (double)vecXMin[i]);
  	tree.add_child("table.data", childTree);
      }
    }
    // 保存
    {
      const std::locale loc = std::locale();
      const boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
      boost::property_tree::xml_parser::write_xml( fileRela, tree, loc, settings );
    }
  }
  std::cout << "正規化パラメータの保存終了" << std::endl;
  return EXIT_SUCCESS;
}

// =================================================================================== //




bool IsLeapYear(int year) {
    if (((year % 4 == 0) && (year % 100 != 0)) || year % 400 == 0) {
        return true;
    } else {
        return false;
    }
}
int GetLastDay(int year, int month) {
    bool leap;
    int lmdays[] = {31,29,31,30,31,30,31,31,30,31,30,31};
    int mdays[]  = {31,28,31,30,31,30,31,31,30,31,30,31};

    leap = IsLeapYear(year);
    // leap year
    if (leap == true) {
        return lmdays[month - 1];
    // no_leap year
    } else {
        return mdays[month - 1];
    }
}

int Holiday(const time_t t) {
  int yy;
  int mm;
  int dd;
  int ww;
  int r;
  struct tm *Hizuke;
  const time_t SYUKUJITSU=-676976400; /*1948年7月20日*/
  const time_t FURIKAE=103388400; /*1973年04月12日*/
  Hizuke=localtime(&t);
  yy=Hizuke->tm_year+1900;
  mm=Hizuke->tm_mon+1;
  dd=Hizuke->tm_mday;
  ww=Hizuke->tm_wday;

  r=0;
  if (ww==6){
    r=1;
  } else if (ww==0){
    r=2;
  }

  if (t<SYUKUJITSU){
    return r;
  }

  switch (mm) {
  case 1:
    if (dd==1){
      r=5; /*元日*/
    } else {
      if (yy>=2000){
        if (((int)((dd-1)/7)==1)&&(ww==1)){
          r=5; /*成人の日*/
        }
      } else {
        if (dd==15){
          r=5; /*成人の日*/
        }
      }
    }
    break;
  case 2:
    if (dd==11){
      if (yy>=1967){
        r=5; /*建国記念の日*/
      }
    } else if ((yy==1989)&&(dd==24)){
      r=5; /*昭和天皇の大喪の礼*/
    }
    break;
  case 3:
    if (dd==Syunbun(yy)){
      r=5; /*春分の日*/
    }
    break;
  case 4:
    if (dd==29){
      if (yy>=2007){
        r=5; /*昭和の日*/
      } else if (yy>=1989){
        r=5; /*みどりの日*/
      } else {
        r=5; /*天皇誕生日*/
      }
    } else if ((yy==1959)&&(dd==10)){
      r=5; /*皇太子明仁親王の結婚の儀*/
    }
    break;
  case 5:
    if (dd==3){
      r=5; /*憲法記念日*/
    } else if (dd==4){
      if (yy>=2007) {
        r=5; /*みどりの日*/
      } else if (yy>=1986) {
          /* 5/4が日曜日は『只の日曜』､月曜日は『憲法記念日の振替休日』(～2006年)*/
          if (ww>1) {
            r=3; /*国民の休日*/
          }
      }
    } else if (dd==5) {
      r=5; /*こどもの日*/
    } else if (dd==6) {
      /* [5/3,5/4が日曜]ケースのみ、ここで判定 */
      if ((yy>=2007)&&((ww==2)||(ww==3))){
        r=4; /*振替休日*/
      }
    }
    break;
  case 6:
    if ((yy==1993)&&(dd==9)){
      r=5; /*皇太子徳仁親王の結婚の儀*/
    }
    break;
  case 7:
    if (yy>=2003){
      if (((int)((dd-1)/7)==2)&&(ww==1)){
        r=5; /*海の日*/
      }
    } else if (yy>=1996){
      if (dd==20) {
        r=5; /*海の日*/
      }
    }
    break;
  case 8:
    if (dd==11){
      if (yy>=2016){
        r=5; /*山の日*/
      }
    }
    break;
  case 9:
    if (dd==Syubun(yy)){
      r=5; /*秋分の日*/
    } else {
      if (yy>=2003) {
        if (((int)((dd-1)/7)==2)&&(ww==1)){
          r=5; /*敬老の日*/
        } else if (ww==2){
          if (dd==Syubun(yy)-1){
            r=3; /*国民の休日*/
          }
        }
      } else if (yy>=1966){
        if (dd==15) {
          r=5; /*敬老の日*/
        }
      }
    }
    break;
  case 10:
    if (yy>=2000){
      if (((int)((dd-1)/7)==1)&&(ww==1)){
        r=5; /*体育の日*/
      }
    } else if (yy>=1966){
      if (dd==10){
        r=5; /*体育の日*/
      }
    }
    break;
  case 11:
    if (dd==3){
      r=5; /*文化の日*/
    } else if (dd==23) {
      r=5; /*勤労感謝の日*/
    } else if ((yy==1990)&&(dd==12)){
      r=5; /*即位礼正殿の儀*/
    }
    break;
  case 12:
    if (dd==23){
      if (yy>=1989){
        r=5; /*天皇誕生日*/
      }
    }
  }

  if ((r<=3)&&(ww==1)){
     /*月曜以外は振替休日判定不要
        5/6(火,水)の判定は上記ステップで処理済
        5/6(月)はここで判定する  */
    if (t>=FURIKAE) {
      if (Holiday(t-86400)==5){    /* 再帰呼出 */
        r=4;
      }
    }
  }
  return r;
}

/*  春分/秋分日の略算式は
    『海上保安庁水路部 暦計算研究会編 新こよみ便利帳』
  で紹介されている式です。 */

/*春分の日を返す関数*/
int Syunbun(int yy) {
  int dd;
  if (yy<=1947){
    dd=99;
  } else if (yy<=1979){
    dd=(int)(20.8357+(0.242194*(yy-1980))-(int)((yy-1983)/4));
  } else if (yy<=2099){
    dd=(int)(20.8431+(0.242194*(yy-1980))-(int)((yy-1980)/4));
  } else if (yy<=2150){
    dd=(int)(21.851+(0.242194*(yy-1980))-(int)((yy-1980)/4));
  } else {
    dd=99;
  }
  return dd;
}

/*秋分の日を返す関数*/
int Syubun(int yy) {
  int dd;
  if (yy<=1947){
    dd=99;
  } else if (yy<=1979){
    dd=(int)(23.2588+(0.242194*(yy-1980))-(int)((yy-1983)/4));
  } else if (yy<=2099){
    dd=(int)(23.2488+(0.242194*(yy-1980))-(int)((yy-1980)/4));
  } else if (yy<=2150){
    dd=(int)(24.2488+(0.242194*(yy-1980))-(int)((yy-1980)/4));
  } else {
    dd=99;
  }
  return dd;
}


time_t my_to_time_t(boost::posix_time::ptime t) {
    using namespace boost::posix_time;
    ptime epoch(boost::gregorian::date(1970,1,1));
    time_duration::sec_type x = (t - epoch).total_seconds();

    // ... check overflow here ...

    return time_t(x);
}
