//
//  test_NewtonForm.cpp
//  HPSCProject3
//
//  Created by Paul Herz on 10/18/16.
//  Copyright © 2016 Paul Herz. All rights reserved.
//

#define _PH_VERBOSE false

#include <iostream>
#include <cmath>
#include <string>

#include "Vector.h"
#include "NewtonForm.cpp"
#include "println.cpp"

using namespace PH;

double evaluatePolynomial(const Vector& a, double x) {
	size_t n = a.size() - 1; // zero indexing
	double result = a[n];
	for(size_t i = n-1; i < n; --i) {
		result = std::fma(result, x, a[i]); // (result * x) + a_i
	}
	return result;
}

int main(int argc, const char * argv[]) {
	
	auto f = [](const double x) -> double {
		return (3.1 * std::pow(x,4) + 2.3 * std::pow(x,3) - 6.6 * std::pow(x,2)
			  + 8.7 * x + 7.9);
	};
	
	// x nodes are -2, -1, 0, 1, 2
	auto xnodes = Vector({-2, -1, 0, 1, 2});
	
	// y nodes are f(x nodes)
	auto ynodes = xnodes;
	ynodes.mapElements([&](double& e, size_t i) {
		e = f(e);
	});
	
	// 1. Build a fourth-degree Newton polynomial p_4(x)
	auto p4 = Newton_coefficients(xnodes, ynodes);
	
	// 2. Test the polynomial with a linear span [-3,3] of size 201.
	auto x_tests = Vector::linSpace(-3, 3, 201);
	auto y_result = Vector(x_tests.size());
	auto y_true = Vector(x_tests.size());
	auto y_error = Vector(x_tests.size());
	
	for(size_t i = 0; i < x_tests.size(); ++i) {
		y_result[i] = evaluatePolynomial(p4, x_tests[i]);
		y_true[i] = f(x_tests[i]);
		y_error[i] = std::abs(y_true[i] - y_result[i]);
	}
	
	try {
		std::string prefix = "../data/a/";
		y_result.saveTo(prefix + "newton_y.txt");
		y_true.saveTo(prefix + "true_y.txt");
		y_error.saveTo(prefix + "newton_error_y.txt");
	} catch(std::runtime_error e) {
		println(e.what());
		return 1;
	}
	
    return 0;
}
