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
 #include <boost/date_time/posix_time/posix_time.hpp>/* 時刻の読み書き */
/* http://www.boost.org/doc/libs/1_61_0/doc/html/date_time/posix_time.html */
#include <boost/algorithm/string.hpp> /* boost::trim */
/* http://www.boost.org/doc/libs/1_61_0/boost/algorithm/string.hpp */

/* 自作関数やクラス */
#include "GeographicCoordinate.h" // 地理座標のクラス
#include "CartesianCoordinate.h" // デカルト座標のクラス
#include "Degree.h"             // 角度のクラス
#include "TotalStation.h"       // 測地線長と方位角のクラス
#include "coordinate.h"         /* 座標系や単位を変換する関数群 */
#include "myTime.h"         /* 座標系や単位を変換する関数群 */


namespace scheme {



} // namespace scheme


#endif // __SCHEME_MAIN__

