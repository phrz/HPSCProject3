/* Daniel R. Reynolds
   SMU Mathematics
   Math 3316
   1 October 2015 */

// Inclusions
#include <iostream>
#include <cmath>
#include <string>

#include "Matrix.h"
#include "Lagrange2D.cpp"

using namespace PH;

// This routine tests the function lagrange2D.cpp.
int main(int argc, char* argv[]) {

	// create Lambda function for f(x,y)
	auto f = [](const double x, const double y) -> double { 
		return (std::sinh(2.0*x) * std::cos(3.0*y));
	};
	
	// set evaluation points (a,b) in a mesh over the domain
	auto a = Vector::linSpace(-2.0, 2.0, 75);
	auto b = Vector::linSpace(-2.0, 2.0, 75);
	
	// *************************************
	// TEST ONE - 11 nodes in each direction
	// *************************************
	int m = 10;
	int n = 10;
	
	auto x = Vector::linSpace(-2.0, 2.0, m+1);
	auto y = Vector::linSpace(-2.0, 2.0, n+1);
	
	// z - the known points input to the Lagrange function
	Matrix z(m+1,n+1);
	z.mapElements([&](double& e, size_t r, size_t c){
		e = f(x[r], y[c]);
	});

	// p - evaluate the polynomial at (a,b)
	Matrix p10(75,75);
	p10.mapElements([&](double& e, size_t r, size_t c){
		e = Lagrange2D(x, y, z, a[r], b[c]);
	});

	// ftrue - evaluate the true function at (r,c)
	Matrix ftrue(75,75);
	ftrue.mapElements([&](double& e, size_t r, size_t c){
		e = f(a[r], b[c]);
	});
	
	// *************************************
	// TEST TWO - 21 nodes in each direction
	// *************************************
	m = 20; 
	n = 20;
	
	auto x2 = Vector::linSpace(-2.0, 2.0, m+1);
	auto y2 = Vector::linSpace(-2.0, 2.0, n+1);
	
	Matrix z2(m+1,n+1);
	z2.mapElements([&](double& e, size_t r, size_t c){
		e = f(x2[r], y2[c]);
	});
	
	Matrix p20(75,75);
	p20.mapElements([&](double& e, size_t r, size_t c){
		e = Lagrange2D(x2, y2, z2, a[r], b[c]);
	});
	
	std::string prefix = "../data/b/";
	a.saveTo(prefix + "a.txt");
	b.saveTo(prefix + "b.txt");
	ftrue.saveTo(prefix + "ftrue.txt");
	p10.saveTo(prefix + "p10.txt");
	p20.saveTo(prefix + "p20.txt");

} // end routine


