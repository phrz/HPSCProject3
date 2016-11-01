//
//  Runge_uniform.cpp
//  HPSCProject3
//
//  Created by Paul Herz on 11/1/16.
//  Copyright © 2016 Paul Herz. All rights reserved.
//

#include "Runge_common.cpp"

using namespace PH;

int main() {
	
	std::string prefix = "../data/c/";
	
	// Create an array of 201 evenly-spaced evaluation points `a` over [-4,4].
	// Output this to disk as avals.txt.
	auto a = Vector::linSpace(-4, 4, 201);
	a.saveTo(prefix + "avals.txt");
	
	// Create an array of 101 evenly-spaced evaluation points `b` over [-4,4].
	// Output this to disk as bvals.txt.
	auto b = Vector::linSpace(-4, 4, 101);
	b.saveTo(prefix + "bvals.txt");
	
	// (a) Using n = m = 6, [...]
	int m1 = 6, n1 = 6;
	auto x1 = Vector::linSpace(-4, 4, m1+1);
	auto y1 = Vector::linSpace(-4, 4, n1+1);
	interpolateOverMatrix(6, 6, a, b, x1, y1, prefix + "p6_uni.txt");
	
	// (b) Repeat using n = m = 24, [...]
	int m2 = 24, n2 = 24;
	auto x2 = Vector::linSpace(-4, 4, m2+1);
	auto y2 = Vector::linSpace(-4, 4, n2+1);
	interpolateOverMatrix(24, 24, a, b, x2, y2, prefix + "p24_uni.txt");
	
	// (c) Fill a matrix runge(201, 101) with the correct values of f(a_i, b_j)
	// and output this to disk as Runge.txt.
	Matrix runge(201, 101);
	runge.mapElements([&](double& e, size_t i, size_t j) {
		e = f(a[i], b[j]);
	});
	runge.saveTo(prefix + "Runge.txt");
	
	return 0;
}

