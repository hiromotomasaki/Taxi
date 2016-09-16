/*
 * coordinate.h - 
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
 *  $Id: coordinate.h 261 2016-05-19 15:32:44Z higepon $
 */

#ifndef __SCHEME_COORDINATE__
#define __SCHEME_COORDINATE__

#include "GeographicCoordinate.h" // 地理座標のクラス
#include "CartesianCoordinate.h" // デカルト座標のクラス
#include "Degree.h"             // 角度のクラス
#include "TotalStation.h"       // 測地線長と方位角のクラス

extern double convertDegreeIntoDouble( const scheme::Degree &deg ); /* 60進数の角度を10進数に変換する */
extern scheme::Degree convertDoubleIntoDegree( const double &deg10 ); /* 10進数を60進数の角度に変換する */
/* 参考URL : http://vldb.gsi.go.jp/sokuchi/surveycalc/surveycalc/algorithm/bl2xy/bl2xy.htm */
/* 結果確認URL : http://vldb.gsi.go.jp/sokuchi/surveycalc/surveycalc/bl2xyf.html */
/* 6系(36, 136)を基準にチェックした */
extern scheme::CartesianCoordinate convertGCoorIntoCCoor( const scheme::GeographicCoordinate &gCoor, const scheme::GeographicCoordinate &gCoorCri ); /* 地理座標系をデカルト座標系に変換する */
/* 参考URL : http://vldb.gsi.go.jp/sokuchi/surveycalc/surveycalc/algorithm/xy2bl/xy2bl.htm */
/* 結果確認URL : http://vldb.gsi.go.jp/sokuchi/surveycalc/surveycalc/xy2blf.html */
/* 6系(36, 136)を基準にチェックした */
extern scheme::GeographicCoordinate convertCCoorIntoGCoor( const scheme::CartesianCoordinate &cCoor, const scheme::GeographicCoordinate &gCoorCri ); /* デカルト座標系を地理座標系に変換する */
/* 参考URL : http://vldb.gsi.go.jp/sokuchi/surveycalc/surveycalc/algorithm/bl2st/bl2st.htm */
/* 結果確認URL : http://vldb.gsi.go.jp/sokuchi/surveycalc/surveycalc/bl2stf.html */
extern scheme::TotalStation calculateTStationFromGCoor( const scheme::GeographicCoordinate &gCoorStart, const scheme::GeographicCoordinate &gCoorGoal ); /* 地理座標系の二点を入力すると測地線長と方位角を返す */
/* 参考URL : http://vldb.gsi.go.jp/sokuchi/surveycalc/surveycalc/algorithm/xy2st/xy2st.htm */
/* 結果確認URL : http://vldb.gsi.go.jp/sokuchi/surveycalc/surveycalc/xy2stf.html */
/* 6系(36, 136)を基準にチェックした */
extern scheme::TotalStation calculateTStationFromCCoor( const scheme::CartesianCoordinate &cCoorStart, const scheme::CartesianCoordinate &cCoorGoal, const scheme::GeographicCoordinate &gCoorCri ); /* デカルト座標系の二点と地理座標系で与えられた基準点を入力すると測地線長と方位角を返す */

extern int calculateRowFromLatitudes( const double phi, const double northPhi, const double southPhi, const double cellSizePhi ); /* 緯度を対応する行に変換する。ただし、営業領域外だと0を返す */
extern int calculateColFromLongitudes( const double lambda, const double westLambda, const double eastLambda, const double cellSizeLambda ); /* 経度を対応する列に変換する。ただし、営業領域外だと0を返す */
extern int calculateColFromIndex( const int index, const int numCol, const int numCell );
extern int calculateRowFromIndex( const int index, const int numCol, const int numCell );
extern int calculateIndexFromRowCol( const int row, const int col, const int numRow, const int numCol );

#endif // __SCHEME_COORDINATE__

