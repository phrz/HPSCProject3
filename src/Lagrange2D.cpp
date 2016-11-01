//
//  Lagrange2D.cpp
//  HPSCProject3
//
//  Created by Paul Herz on 10/25/16.
//  Copyright © 2016 Paul Herz. All rights reserved.
//

#include <iostream>

#include "Matrix.h"
#include "Vector.h"
#include "Lagrange.cpp"

using namespace PH;

double Lagrange2D(const Vector& x, const Vector& y, const Matrix& f, double a, double b) {
	
	double sum = 0.0;
	f.forEach([&](const double& e, size_t i, size_t j) {
		sum += e * Lagrange_basis(x, i, a) * Lagrange_basis(y, j, b);
	});
	
	return sum;
}
