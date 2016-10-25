//
//  NewtonForm.cpp
//  HPSCProject3
//
//  Created by Paul Herz on 10/18/16.
//  Copyright © 2016 Paul Herz. All rights reserved.
//

#ifndef _s
#define _s std::to_string
#endif

#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include "println.cpp"

using namespace PH;

double Newton_basis(const Vector& xnodes, size_t n, double x) {
	// Evaluate the Newton basis function ɸ_n+1(x) defined as:
	//     ɸ_n+1(x) = (x - x_0)(x - x_1) ... (x - x_n)
	double result = 1.0;
	
	for(int i = 0; i < n; i++) {
		result *= x - xnodes[i];
	}
	
	return result;
}

double Newton_nestedform(const Vector& a, const Vector& xnodes, double x) {
	// Evaluate the Newton form p_n(x) defined as:
	//     p_n(x) = a_0 + a_1(x-x_0) + a_2(x-x_0)(x-x_1) + ...
	//              ... + a_n+1(x-x_0)...(x-x_n)
	// using nested multiplication:
	//     p_n(x) = a_0 + (x-x_0)( a_1 + (x-x_1) ( ... a_n + (x-x_n)(a_n+1) ... ))
	
	#if _PH_VERBOSE
		println("\n\nNested form");
		println("x:", x);
		println("x_i:", xnodes);
		println("a_i:", a, "\n");
	#endif
	
	size_t n = a.size();
	double result = a[n+1];
	
	#if _PH_VERBOSE
		println("p_"+_s(n)+"(x)=");
		for(size_t i = n; i <= n; --i) {
			std::cout << "[";
		}
	#endif
	
	for(size_t i = n; i <= n; --i) {
		// fma(x,y,z) === x * y + z
		result = std::fma(result, (x - xnodes[i]), a[i]);
		#if _PH_VERBOSE
			println("(x - x_"+_s(i)+") + a_"+_s(i)+"]");
		#endif
	}
	
	return result;
}

Vector Newton_coefficients(const Vector& xnodes, const Vector& ynodes) {
	// construct the Newton form of an interpolating polynomial.
	// xnodes and ynodes collectively form a set of known (x_i,y_i) points.
	// Output should be coefficients a_0, a_1, ... a_n for Newton form.
	//
	//     a_n+1 = [y_n+1 - p_n(x_n+1)] / [(x_n+1 - x_0)...(x_n+1 - x_n)]
	//
	// Implement this recursion and use the prior two functions.
	
	// This is effectively a_n+1 = [y_n+1 - polynomial_n(x_n+1)]
	//                             / basis(x_0...x_n+1)
	
	#if _PH_VERBOSE
		println("\n\nNewton Coefficients Generation");
		println("xnodes:", xnodes);
		println("ynodes:", ynodes, "\n\n");
	#endif
	
	if(xnodes.size() != ynodes.size()) {
		throw new std::invalid_argument(
			"the vectors of x and y values are not the same length.");
	}
	
	auto n = xnodes.size();
	
	// NOOP if size is zero.
	if(n == 0) {
		return Vector(0);
	}
	
	auto a = Vector(n); // contains a_0 ... a_n-1
	
	// It is given that p_0(x) = a_0 = y_0.
	a[0] = ynodes[0];
	
	for(size_t i = 1; i < n; i++) {
		// calculate p_i(x) with Newton_nestedform
		auto aTrunc = a.range(0, i);
		
		double numerator = ynodes[i];
		numerator -= Newton_nestedform(aTrunc, xnodes, xnodes[i]);
		
		// the denominator is the basis = Prod[0...i](x-x_j)
		double denominator = Newton_basis(xnodes, i, xnodes[i]);
		
		a[i] = numerator / denominator;
	}
	
	return a;
}
