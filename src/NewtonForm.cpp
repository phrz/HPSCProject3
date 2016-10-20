//
//  NewtonForm.cpp
//  HPSCProject3
//
//  Created by Paul Herz on 10/18/16.
//  Copyright © 2016 Paul Herz. All rights reserved.
//

#include <iostream>
#include "Matrix.h"
#include "Vector.h"

using namespace PH;

double Newton_basis(Vector& xnodes, int n, double x) {
	// Evaluate the Newton basis function ɸ_n+1(x) defined as:
	//     ɸ_n+1(x) = (x - x_0)(x - x_1) ... (x - x_n)
	double result = 1.0;
	
	for(int i = 0; i < n; i++) {
		result *= x - xnodes[i];
	}
	
	return result;
}

double Newton_nestedform(Vector& a, Vector& xnodes, double x) {
	// Evaluate the Newton form p_n(x) defined as:
	//     p_n(x) = a_0 + a_1(x-x_0) + a_2(x-x_0)(x-x_1) + ...
	//              ... + a_n+1(x-x_0)...(x-x_n)
	// using nested multiplication:
	//     p_n(x) = a_0 + (x-x_0)( a_1 + (x-x_1) ( ... a_n + (x-x_n)(a_n+1) ... ))
	
	size_t n = a.size() - 2;
	double result = a[n+1];
	
	for(size_t i = n; i <= n; --i) {
		// fma(x,y,z) === x * y + z
		result = std::fma(result, (x - xnodes[i]), a[i]);
	}
	
	return result;
}

Vector Newton_coefficients(Vector& xnodes, Vector& ynodes) {
	// construct the Newton form of an interpolating polynomial.
	// xnodes and ynodes collectively form a set of known (x_i,y_i) points.
	// Output should be coefficients a_0, a_1, ... for Newton form.
	//
	//     a_n+1 = [y_n+1 - p_n(x_n+1)] / [(x_n+1 - x_0)...(x_n+1 - x_n)]
	//
	// Implement this recursion and use the prior two functions.
	
	if(xnodes.size() != ynodes.size()) {
		throw new std::invalid_argument(
			"the vectors of x and y values are not the same length.");
	}
	
	auto n = xnodes.size();
	
	auto a = Vector(xnodes.size());
	
	// It is given that p_0(x) = a_0 = y_0.
	a[0] = ynodes[0];
	
	for(size_t i = 1; i < n; i++) {
		// TODO: when should this stop?
		std::cout << "nothing" << std::endl;
	}
	
	return a;
}
