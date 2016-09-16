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

// vectorからindex番目の要素を削除する
template<typename T>
void remove(std::vector<T>& vector, unsigned int index)
{
    vector.erase(vector.begin() + index);
}

int main(void)
{

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
  // 時間幅, 予測ステップ数の取得
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
  // NeuralCurentInfo.xmlから情報を取る
  boost::posix_time::ptime cTimeRound;
  double maxTemp = 0;
  double minTemp = 0;
  double dayW = 0;
  double nightW = 0;
  {
    boost::property_tree::ptree tree;
    // ----------- 読込ファイル名 ----------- //
    const std::string fileName = "NeuralCurrentInfo.xml";
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
      boost::posix_time::ptime cTime = boost::posix_time::time_from_string(timeStr);
      // cTimeの値をdiscreteTimeWidthで丸める.
      cTimeRound = roundPTime(cTime, discreteTimeWidth);
    }
    maxTemp = tree.get<double>("table.data.maxTemp");
    minTemp = tree.get<double>("table.data.minTemp");
    dayW = (double)tree.get<int>("table.data.dayW");
    nightW = (double)tree.get<int>("table.data.nightW");
  }
  std::vector<boost::posix_time::ptime> vecPTimeRound(2+timeHorizon, cTimeRound);
  vecPTimeRound[0] -= boost::posix_time::seconds( discreteTimeWidth * 60 );
  for (int i = 0; i < timeHorizon; i++) {
    vecPTimeRound[i] += boost::posix_time::seconds( discreteTimeWidth * 60 * ( i + 1 ) );
  }
  // 構造体Xの作成
  std::vector<X> vecX(2+timeHorizon);
  // 要素の確保
  // 720+10=730
  for (int i = 0; i < (int)vecX.size(); i++) {
    vecX[i].x.reserve(730);
    vecX[i].x.resize(730, 0);
  }
  for (int i = 0; i < (int)vecX.size(); i++) {
    boost::posix_time::ptime pTimeRound = vecPTimeRound[i];
    int step = 0;
    int day_5_10_20_lastDay = 0;
    int holiday = 0;
    int month12to2 = 0;
    int month3to5 = 0;
    int month6to8 = 0;
    int month9to11 = 0;
    {
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
    vecX[i].x[step-1] = 1;
    vecX[i].x[720] = day_5_10_20_lastDay;
    vecX[i].x[721] = holiday;
    vecX[i].x[722] = month12to2;
    vecX[i].x[723] = month3to5;
    vecX[i].x[724] = month6to8;
    vecX[i].x[725] = month9to11;
    vecX[i].x[726] = dayW;
    vecX[i].x[727] = nightW;
    vecX[i].x[728] = maxTemp; // 後で正規化
    vecX[i].x[729] = minTemp; // 後で正規化
  }

  // 正規化する
  {
    std::vector<double> vecXMin(2, DBL_MAX);
    std::vector<double> vecXMax(2, -DBL_MAX);
    // 正規化パラメータの取得
    {
      boost::property_tree::ptree tree;
      {
	// ----------- 読込ファイル名 ----------- //
	const std::string fileName = "MaxAndMin.xml";
	// -------------------------------------- //
	const std::string fileDire = "./../../Data/OtherData/OtherData/Neural";
	const std::string file = fileDire + "/" + fileName;
	const int flag = boost::property_tree::xml_parser::no_comments;
	boost::property_tree::read_xml(file, tree, flag);
      }
      boost::property_tree::ptree::iterator itr_first, itr_last, it;
      itr_first = tree.get_child( "table" ).begin();
      itr_last = tree.get_child( "table" ).end();
      for(it = itr_first; it != itr_last; it++) {
	std::size_t index = std::distance(itr_first, it);
	vecXMax[(int)index] = it->second.get<double>("max");
	vecXMin[(int)index] = it->second.get<double>("min");
      }
    }
    // x=(x-x_min) / (x_max - x_min)
    for (int i = 0; i < (int)vecX.size(); i++) {
      vecX[i].x[728] = (vecX[i].x[728] - vecXMin[0]) / (double) (vecXMax[0] - vecXMin[0]);
      vecX[i].x[729] = (vecX[i].x[729] - vecXMin[1]) / (double) (vecXMax[1] - vecXMin[1]);
    }
  }
  // ニューラルネットワークを((int)vecX.size())回使用する
  // 出力を保存する領域を確保
  std::vector<OutputData> demands( (int)vecX.size() );
  for (int i = 0; i < (int)vecX.size(); i++) {
    demands[i].demand.resize(numCell + 1);
    demands[i].allDemand = 0;
  }
  for (int i = 0; i < (int)vecX.size(); i++) {
    // 入力はvecX[i], 出力はdemands[i]に保存する
    // 保存データを利用して予測してみる
    // Netを取得する
    // caffe::Net<float> net_test("train_test.prototxt", caffe::TEST);
    caffe::Net<double> testNet("Source/train_test.prototxt", caffe::TEST);
    // 訓練されたネットを取得する
    testNet.CopyTrainedLayersFrom("./../../Data/OtherData/OtherData/Neural/Neural_iter_50000.caffemodel");

    // // 予測する
    const boost::shared_ptr<caffe::MemoryDataLayer<double> > input_test_layer = boost::dynamic_pointer_cast<caffe::MemoryDataLayer<double>>( testNet.layer_by_name("input") );
    const boost::shared_ptr<caffe::MemoryDataLayer<double> > target_test_layer = boost::dynamic_pointer_cast<caffe::MemoryDataLayer<double>>( testNet.layer_by_name("target") );
    // ミニバッチの変更
    // batchSize = 10 -> batchSize = 1
    int batchSize = 1;
    input_test_layer->set_batch_size(batchSize);
    target_test_layer->set_batch_size(batchSize);

    int numData = 1 * batchSize;
    int numInputVar = 730;
    int numOutPutVar = numCell + 1;
    std::vector<double> input_test_data( numInputVar * numData );
    std::vector<double> target_test_data( numOutPutVar * numData, 0 );
    std::vector<double> dummy_test_data( numData, 0 );
    // input_test_dataにデータを詰める
    for(int j = 0; j < numInputVar; j++) {
      input_test_data[j] = vecX[i].x[j];
    }

    // 層のリセット
    input_test_layer -> caffe::MemoryDataLayer<double>::Reset( &input_test_data[0], &dummy_test_data[0], numData);
    target_test_layer -> caffe::MemoryDataLayer<double>::Reset( &target_test_data[0], &dummy_test_data[0], numData);

    // 順伝播計算
    testNet.Forward();

    // demands[i]に計算結果を詰める
    demands[i].allDemand = testNet.blob_by_name("ip2")->cpu_data()[0];
    for(int j = 1; j <= numCell; j++) {
      demands[i].demand[j-1] = testNet.blob_by_name("ip2")->cpu_data()[j];
    }
  }

   // 値の確認
  for (int i = 0; i < (int)vecX.size(); i++) {
     std::cout << "[総需要]" << demands[i].allDemand << std::endl;
     for(int j = 1; j <= numCell; j++) {
       std::cout << "[" <<demands[i].demand[j-1] << "]";
     }
     std::cout << std::endl;
   }

  // 閾値やパラメータを取得する
  int threshold = 0;
  double gamma = 0;
  {
    boost::property_tree::ptree tree;
    // ----------- 読込ファイル名 ----------- //
    const std::string fileName = "Threshold.xml";
    // -------------------------------------- //
    const std::string fileDire = "./../../Data/OtherData/ProcessedInitialData";
    const std::string file = fileDire + "/" + fileName;
    const int flag = boost::property_tree::xml_parser::no_comments;
    boost::property_tree::read_xml(file, tree, flag);
    {
      // 取得
      threshold= tree.get<int>("table.threshold");
      gamma = tree.get<double>("table.gamma");
    }
  }

  // 需要が集中しているセル番号を求める
  {
    double sumDemand = 0;
    std::vector<double> demand( numCell, 0);
    for (int i = 0; i < (int)vecX.size(); i++) {
      sumDemand += demands[i].allDemand;
      for (int j = 0; j < numCell; j++) {
  	demand[j] += demands[i].demand[j];
      }
    }
    // sumDemandの小数切り上げをする
    sumDemand = ceil(sumDemand);
    // demandの最大値を求める
    double maxDemand = *std::max_element( demand.begin(), demand.end() );
    if( sumDemand == 0 || maxDemand == 0) {
      // 需要が集中しているセルはない
      // コピー元
      const std::string fileRela_read = "./../../Data/OtherData/OtherData/EmptyNeuralCirclePositions.xml";
      // コピー先
      const std::string fileRela_write = "./../../Data/OtherData/Result/NeuralCirclePositions.xml";
      // std::cout << fileRela_read << "をコピーします" << std::endl;
      try {
    	boost::filesystem::copy_file(fileRela_read, fileRela_write, boost::filesystem::copy_option::overwrite_if_exists);
      }
      catch (boost::filesystem::filesystem_error& ex) {
    	std::cout << ex.what() << std::endl;
    	throw;
      }
    }else{
      std::vector<int> countDemand(numCell, 0);
      // demandを正規化する
      double sumCellDemand = std::accumulate(demand.begin(), demand.end(), 0.0);
      for (int j = 0; j < numCell; j++) {
    	demand[j] /= sumCellDemand;
      }
      if( maxDemand * gamma > 1 ) {
    	gamma = 1.0 / (maxDemand + 1.0);
      }
      // sumDemandとdemandとgammaとthresholdを用いて需要が集中しているCellを求める
      std::vector<double>::iterator it, itr_first;
      itr_first = demand.begin();
      while( sumDemand > 0 ){
    	// 最大要素のイテレータを取得
    	it = std::max_element(demand.begin(), demand.end());
    	*it -= gamma;
    	std::size_t index = std::distance(itr_first, it); // std::distance(itr_first, itr_first) == 0
    	countDemand[(int)index]++;
    	sumDemand--;
      }
      // countDemandの中でthreshold以上の値を持つindexをさがす。(index+1)が求めたい需要が集中しているセルである。複数ある可能性あり。
      if( *std::max_element( countDemand.begin(), countDemand.end() ) < threshold ) {
      	// 需要が集中しているセルはない
      	// コピー元
      	const std::string fileRela_read = "./../../Data/OtherData/OtherData/EmptyNeuralCirclePositions.xml";
      	// コピー先
      	const std::string fileRela_write = "./../../Data/OtherData/Result/NeuralCirclePositions.xml";
      	// std::cout << fileRela_read << "をコピーします" << std::endl;
      	try {
      	  boost::filesystem::copy_file(fileRela_read, fileRela_write, boost::filesystem::copy_option::overwrite_if_exists);
      	}
      	catch (boost::filesystem::filesystem_error& ex) {
      	  std::cout << ex.what() << std::endl;
      	  throw;
      	}
      }else{
      	// 少なくとも1箇所需要が集中しているセルがある
      	// 代表点のtreeを取得
      	// 代表点ベクトルの読込み
      	std::vector<GeographicCoordinate> vRepresentativePoint(numCell);
      	{
      	  const std::string fileName_read_3 = "MapRepresentativePoints.xml";
      	  const std::string fileDire_read_3 = "./../../Data/OtherData/OtherData";
      	  // 読込先
      	  const std::string fileRela_read = fileDire_read_3 + "/" + fileName_read_3;
      	  // xmlのtreeの新規作成
      	  boost::property_tree::ptree tree;
      	  const int flag = boost::property_tree::xml_parser::no_comments; // コメントは読み込まない
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
      	// xmlのtreeの新規作成
      	boost::property_tree::ptree tree;
      	for(int j = 0; j < numCell; j++) {
      	  if( countDemand[j] >= threshold ) {
      	    // index j の代表点を取得
      	    boost::property_tree::ptree childTree;
      	    std::vector<std::string> str(2, "-1");
      	    str[0] = boost::lexical_cast<std::string>( vRepresentativePoint[j].getPhi() );
      	    str[1] = boost::lexical_cast<std::string>( vRepresentativePoint[j].getLambda() );
      	    std::string strPoint = boost::algorithm::join(str , "," );
      	    childTree.put("position", strPoint);
      	    tree.add_child("table.data", childTree);
      	  }
      	}
	const std::string fileRela = "./../../Data/OtherData/Result/NeuralCirclePositions.xml";
	// 保存
	{
	  const std::locale loc = std::locale();
	  const boost::property_tree::xml_writer_settings<std::string> settings = boost::property_tree::xml_writer_settings<std::string>( ' ', 2 );
	  boost::property_tree::xml_parser::write_xml( fileRela, tree, loc, settings );
	}
      }
    }
  }

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

