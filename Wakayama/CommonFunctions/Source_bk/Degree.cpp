/*
 * Degree.cpp - 
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
 *  $Id: Degree.cpp 183 2016-05-19 15:33:28Z higepon $
 */

#include <iostream>

#include "Degree.h"

using namespace scheme;

Degree::Degree() {
  this -> degrees_ = 0;
  this -> minutes_ = 0;
  this -> seconds_ = 0;
}
Degree::Degree( const int degrees_, const int minutes_, const double seconds_ ) {
  this -> degrees_ = degrees_;
  this -> minutes_ = minutes_;
  this -> seconds_ = seconds_;
}
Degree::~Degree() {

}
int Degree::getDegrees() const {
  return degrees_;
}
void Degree::setDegrees( const int degrees_ ) {
  this -> degrees_ = degrees_;
}
int Degree::getMinutes() const {
  return minutes_;
}
void Degree::setMinutes( const int minutes_ ) {
  this -> minutes_ = minutes_;
}
double Degree::getSeconds() const {
  return seconds_;
}
void Degree::setSeconds( const double seconds_ ) {
  this -> seconds_ = seconds_;
}
void Degree::set( const int degrees_, const int minutes_, const double seconds_ ) {
  this -> degrees_ = degrees_;
  this -> minutes_ = minutes_;
  this -> seconds_ = seconds_;
}
void Degree::print() const {
  std::cout << "( 度, 分, 秒 ) = (" << this -> degrees_ << ", " << this -> minutes_ << ", " << this -> seconds_ << ")" <<std::endl;
}
