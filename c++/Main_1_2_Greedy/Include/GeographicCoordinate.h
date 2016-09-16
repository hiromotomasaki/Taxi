/*
 * GeographicCoordinate.h - 
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
 *  $Id: GeographicCoordinate.h 261 2016-05-19 15:32:44Z higepon $
 */

#ifndef __SCHEME_GEOGRAPHICCOORDINATE__
#define __SCHEME_GEOGRAPHICCOORDINATE__

namespace scheme {
  //=============地理座標系による位置クラス(定義名:gCoor)=============//
  class GeographicCoordinate
  {
  public:
    GeographicCoordinate();       /* コンストラクタ */
    GeographicCoordinate( const double phi_, const double lambda_ ); /* コンストラクタ */
    ~GeographicCoordinate();         /* デストラクタ */
    double getPhi() const;           /* phi_を取得 */
    void setPhi( const double phi_ );       /* phi_を設定 */
    double getLambda() const;        /* lambda_を取得 */
    void setLambda( const double lambda_ ); /* lambda_を設定 */
    void set( const double phi_, const double lambda_ ); /* phi_, lambda_を設定 */
    void print() const;                    /* メンバ変数の表示 */
  private:
    double phi_;                  /* 緯度(latitude) */
    double lambda_;               /* 経度(longitude) */
  };

} // namespace scheme

#endif // __SCHEME_GEOGRAPHICCOORDINATE__

