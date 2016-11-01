//
//  Runge_common.cpp
//  HPSCProject3
//
//  Created by Paul Herz on 11/1/16.
//  Copyright © 2016 Paul Herz. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <string>

#include "Vector.h"
#include "Matrix.h"
#include "println.cpp"
#include "Lagrange2D.cpp"

using namespace PH;

double f(double x, double y) {
	// Two dimensional Runge function f(x,y) = (1+x^2+y^2)^-1
	return 1.0/(1+ std::pow(x,2) + std::pow(y,2));
}

void interpolateOverMatrix(int m, int n, const Vector& a, const Vector& b,
						   const Vector& x, const Vector& y, std::string filename) {
	
	// Create a matrix F(m+1, n+1) that contains function values f(x_i, y_j)
	Matrix F(m+1, n+1);
	F.mapElements([&](double& e, size_t i, size_t j){
		e = f(x[i], y[j]);
	});
	
	// Use Lagrange2D to evaluate the polynomial interpolant p(a_i, b_j) at the
	// 201 * 101 evaluation points, storing the results in matrix P(201,101).
	// Output this to disk as p*_uni.txt.
	Matrix P(201, 101);
	P.mapElements([&](double& e, size_t i, size_t j) {
		e = Lagrange2D(x, y, F, a[i], b[j]);
	});
	
	println(a.size() * b.size());
	println(P.size());
	P.saveTo(filename);
}
