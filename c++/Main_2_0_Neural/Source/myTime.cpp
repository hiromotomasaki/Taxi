/*
 * myTime.cpp - 
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
 *  $Id: myTime.cpp 183 2016-05-19 15:33:28Z higepon $
 */

#include "myTime.h"
boost::posix_time::ptime roundPTime(const boost::posix_time::ptime &pTime, const int delta) {
  boost::posix_time::ptime ret(boost::gregorian::date(pTime.date().year(),pTime.date().month().as_number(),pTime.date().day()), boost::posix_time::time_duration(pTime.time_of_day().hours(),0,0));
  // f(秒) = 60(秒/分)*x(分)+y(秒)
  // 1cycle = z(秒) = 60(秒/分)*Δt(分)
  // f ≡ γ(mod z)
  // if γ >= z/2 then 繰り上げ
  // if γ <  z/2 then 切り捨て
  // y(秒)=0として
  // あとはx(分)だけ見れば良い
  // 繰り上げると x+Δt-x%Δt
  // 切り捨てると x    -x%Δt
  // (=X(分))になる.
  // この値を保持しておき, まずx=0としてその後pTime+Xをすればよい
  int z = 60 * delta;           // 時間幅
  int z_2 = 30 * delta;           // 時間幅の半分
  int x = pTime.time_of_day().minutes(); // 分
  int y = pTime.time_of_day().seconds(); // 秒
  int f = 60 * x + y;
  int gamma = f % z;
  int X = 0;                    // 丸め後の分
  if( gamma >= z_2) {
    X = x + delta - x % delta;
  }else{
    X = x - x % delta;
  }
  ret = ret + boost::posix_time::minutes(X);
  return ret;
}


