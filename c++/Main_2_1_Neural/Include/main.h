/*
 * main.h - 
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
 *  $Id: main.h 261 2016-05-19 15:32:44Z higepon $
 */

#ifndef __SCHEME_MAIN__
#define __SCHEME_MAIN__

#include <iostream>             /* std::cout, std::endl */
/* http://cpprefjp.github.io/reference/iostream.html */
#include <cstdlib>              /* EXIT_SUCCESS, EXIT_FAILURE */
/* http://cpprefjp.github.io/reference/cstdlib.html */
#include <boost/property_tree/xml_parser.hpp> /* boost::property_tree::xml_parser::write_xml, boost::property_tree::xml_parser::read_xml */
/* http://www.boost.org/doc/libs/1_61_0/doc/html/boost/property_tree/xml_parser/write_xml_idp197174048.html */
#include <boost/filesystem.hpp> /* boost::filesystem::create_directories, -lboost_system -lboost_filesystemが必要 */
/* http://boostjp.github.io/tips/filesystem.html */
#include <boost/lexical_cast.hpp> /* boost::lexical_cast<型> */
/* http://www.kmonos.net/alang/boost/classes/lexical_cast.html */
#include <cmath>       /* ceil, fabs*/
/* http://www.cplusplus.com/reference/cmath/ */
#include <boost/algorithm/string.hpp> /* boost::trim */
/* http://www.boost.org/doc/libs/1_61_0/boost/algorithm/string.hpp */
 #include <boost/date_time/posix_time/posix_time.hpp>/* 時刻の読み書き */
/* http://www.boost.org/doc/libs/1_61_0/doc/html/date_time/posix_time.html */

/* 自作関数やクラス */
#include "GeographicCoordinate.h" // 地理座標のクラス
#include "CartesianCoordinate.h" // デカルト座標のクラス
#include "Degree.h"             // 角度のクラス
#include "TotalStation.h"       // 測地線長と方位角のクラス
#include "coordinate.h"         /* 座標系や単位を変換する関数群 */
#include "myTime.h"         /* 時刻を丸める関数 */

#include <boost/random.hpp>

#include <glog/logging.h>

#include <caffe/caffe.hpp>
#include <caffe/layers/memory_data_layer.hpp>


namespace scheme {



} // namespace scheme

// is leap or not
bool IsLeapYear(int year);
// get the last day of month
int GetLastDay(int year, int month);

/* 土日祝日かどうかを返す関数　
        返り値:平日=0、土曜=1、日曜=2、休日=3、振休=4、祝日=5 */
/*  この関数(含むint Syunbun()、int Syubun())は、
    http://www.h3.dion.ne.jp/~sakatsu/
  の祝日判定ロジック(ＶＢＡ版)を利用して作ったものです。*/

/*
_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
_/
_/　CopyRight(C) K.Tsunoda(AddinBox) 2001 All Rights Reserved.
_/　( http://www.h3.dion.ne.jp/~sakatsu/index.htm )
_/
_/　　この祝日マクロは『kt関数アドイン』で使用しているものです。
_/　　このロジックは、レスポンスを第一義として、可能な限り少ない
_/　  【条件判定の実行】で結果を出せるように設計してあります。
_/　　この関数では、２０１６年施行の改正祝日法(山の日)までを
_/　  サポートしています。
_/
_/　(*1)このマクロを引用するに当たっては、必ずこのコメントも
_/　　　一緒に引用する事とします。
_/　(*2)他サイト上で本マクロを直接引用する事は、ご遠慮願います。
_/　　　【 http://www.h3.dion.ne.jp/~sakatsu/holiday_logic.htm 】
_/　　　へのリンクによる紹介で対応して下さい。
_/　(*3)[ktHolidayName]という関数名そのものは、各自の環境に
_/　　　おける命名規則に沿って変更しても構いません。
_/　
_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
*/

int Holiday(const time_t t);

int Syunbun(int yy); /*春分の日を返す関数*/
int Syubun(int yy); /*秋分の日を返す関数*/

time_t my_to_time_t(boost::posix_time::ptime t);

#endif // __SCHEME_MAIN__

