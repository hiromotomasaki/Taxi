/*
 * Degree.h - 
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
 *  $Id: Degree.h 261 2016-05-19 15:32:44Z higepon $
 */

#ifndef __SCHEME_DEGREE__
#define __SCHEME_DEGREE__

namespace scheme {
  //=============度分秒が10, 60, 60進数の角度クラス(定義名:deg)=============//
class Degree
{
public:
  Degree();                     /* コンストラクタ */
  Degree( const int degrees_, const int minutes_, const double seconds_ ); /* コンストラクタ */
  ~Degree();                         /* デストラクタ */
  int getDegrees() const;            /* degrees_を取得 */
  void setDegrees( const int degrees_ );    /* degrees_を設定 */
  int getMinutes() const;            /* minutes_を取得 */
  void setMinutes( const int minutes_ );    /* minutes_を設定 */
  double getSeconds() const;         /* seconds_を取得 */
  void setSeconds( const double seconds_ ); /* seconds_を設定 */
  void set( const int degrees_, const int minutes_, const double seconds_ ); /* degrees_, minutes_, seconds_を設定 */
  void print() const;                /* メンバ変数の表示 */
 private:
  int degrees_;                 /* 度 */
  int minutes_;                 /* 分 */
  double seconds_;              /* 秒 */
};

} // namespace scheme

#endif // __SCHEME_DEGREE__

