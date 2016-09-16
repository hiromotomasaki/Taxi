/*
 * TotalStation.cpp - 
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
 *  $Id: TotalStation.cpp 183 2016-05-19 15:33:28Z higepon $
 */

#include <iostream>
#include "TotalStation.h"

using namespace scheme;


TotalStation::TotalStation() {
  this -> length_ = 0;
  this -> azimuth_ = 0;
}
TotalStation::TotalStation( const double length_, const double azimuth_ ) {
  this -> length_ = length_;
  this -> azimuth_ = azimuth_;
}
TotalStation::~TotalStation() {
  
}
double TotalStation::getLength() const {
  return length_;
}
void TotalStation::setLength( const double length_ ) {
  this -> length_ = length_;
}
double TotalStation::getAzimuth() const {
  return azimuth_;
}
void TotalStation::setAzimuth( const double azimuth_ ) {
  this -> azimuth_ = azimuth_;
}
void TotalStation::set( const double length_, const double azimuth_ ) {
  this -> length_ = length_;
  this -> azimuth_ = azimuth_;
}
void TotalStation::print() const {
  std::cout << "( 測地線長, 方位角 ) = (" << this -> length_ << ", " << this -> azimuth_ << ")" << std::endl;
}

bool LessTotalStation::operator()(const TotalStation& tStation_a, const TotalStation& tStation_b) {
  if( tStation_a.getLength() == tStation_b.getLength() ) {
    return tStation_a.getAzimuth() < tStation_b.getAzimuth();
  }else{
    return tStation_a.getLength() < tStation_b.getLength();
  }
}
