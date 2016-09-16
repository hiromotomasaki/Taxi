/*
 * CartesianCoordinate.cpp - 
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
 *  $Id: CartesianCoordinate.cpp 183 2016-05-19 15:33:28Z higepon $
 */

#include <iostream>

#include "CartesianCoordinate.h"

using namespace scheme;

CartesianCoordinate::CartesianCoordinate() {
  this -> x_ = 0;
  this -> y_ = 0;
}
CartesianCoordinate::CartesianCoordinate( const double x_, const double y_ ) {
  this -> x_ = x_;
  this -> y_ = y_;
}
CartesianCoordinate::~CartesianCoordinate() {

}
double CartesianCoordinate::getX() const {
  return x_;
}
void CartesianCoordinate::setX( const double x_ ) {
  this -> x_ = x_;
}
double CartesianCoordinate::getY() const {
  return y_;
}
void CartesianCoordinate::setY( const double y_ ) {
  this -> y_ = y_;
}
void CartesianCoordinate::set( const double x_, const double y_ ) {
  this -> x_ = x_;
  this -> y_ = y_;
}
void CartesianCoordinate::print() const {
  std::cout << "( X, Y ) = (" << this -> x_ << ", " << this -> y_ << ")" <<std::endl;
}

