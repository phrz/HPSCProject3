//
//  Runge_Chebyshev.cpp
//  HPSCProject3
//
//  Created by Paul Herz on 11/1/16.
//  Copyright © 2016 Paul Herz. All rights reserved.
//

#include "Runge_common.cpp"

using namespace PH;

Vector chebyshevNodes(double L, size_t n) {
	Vector nodes(n);
	size_t m = n-1; // assuming m+1 nodes
	nodes.mapElements([&](double& x_i, size_t i) {
		x_i = L * std::cos( (2*i+1)*M_PI/(2*m+2) );
	});
	return nodes;
}

int main() {
	
	std::string prefix = "../data/d/";
	
	// Create an array of 201 evenly-spaced evaluation points `a` over [-4,4].
	auto a = Vector::linSpace(-4, 4, 201);
	
	// Create an array of 101 evenly-spaced evaluation points `b` over [-4,4].
	auto b = Vector::linSpace(-4, 4, 101);
	
	// Repeat (a) and (b) from #3 where now `x` and `y` are Chebyshev nodes
	// over [-4,4]:
	
	// (a) Using n = m = 6, [...]
	int m1 = 6, n1 = 6;
	auto x1 = chebyshevNodes(4, m1+1);
	auto y1 = chebyshevNodes(4, n1+1);
	interpolateOverMatrix(6, 6, a, b, x1, y1, prefix + "p6_Cheb.txt");
	
	// (b) Repeat using n = m = 24, [...]
	int m2 = 24, n2 = 24;
	auto x2 = chebyshevNodes(4, m2+1);
	auto y2 = chebyshevNodes(4, n2+1);
	interpolateOverMatrix(24, 24, a, b, x2, y2, prefix + "p24_Cheb.txt");
	
	return 0;
}
