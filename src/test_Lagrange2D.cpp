/* Daniel R. Reynolds
   SMU Mathematics
   Math 3316
   1 October 2015 */

// Inclusions
#include <iostream>
#include <cmath>
#include "Matrix.h"
#include "Lagrange2D.cpp"

using namespace std;
using namespace PH;

// This routine tests the function lagrange2D.cpp.
int main(int argc, char* argv[]) {

	// create Lambda function for f(x,y)
	auto f = [](const double x, const double y) -> double { 
		return (std::sinh(2.0*x)*cos(3.0*y));
	};

	
	// first, test with 11 nodes in each direction
	int m = 10;
	int n = 10;
	
	auto x = Vector::linSpace(-2.0, 2.0, m+1);
	auto y = Vector::linSpace(-2.0, 2.0, n+1);
	
	Matrix z(m+1,n+1);
	
	for (int j=0; j<=n; j++)  
		for (int i=0; i<=m; i++)
			z(i,j) = f(x[i], y[j]);               // fill data

	// set evaluation points (a,b) in a mesh over the domain
	auto a = Vector::linSpace(-2.0, 2.0, 75);
	auto b = Vector::linSpace(-2.0, 2.0, 75);

	// output evaluation points to disk
	a.saveTo("../data/a.txt");
	b.saveTo("../data/b.txt");

	// evaluate the polynomial at the points (a,b), storing in p
	Matrix p(75,75);
	for (int j=0; j<75; j++) 
		for (int i=0; i<75; i++)
			p(i,j) = Lagrange2D(x, y, z, a[i], b[j]);

	// output p to disk
	p.saveTo("../data/p10.txt");

	// evaluate the true function at the points (a,b), storing in ftrue
	Matrix ftrue(75,75);
	for (int j=0; j<75; j++) 
		for (int i=0; i<75; i++)
			ftrue(i,j) = f(a[i], b[j]);

	// output true function to disk
	ftrue.saveTo("ftrue.txt");

	
	// repeat test with 21 nodes in each direction
	m = 20; 
	n = 20;
	
	auto x2 = Vector::linSpace(-2.0, 2.0, m+1);
	auto y2 = Vector::linSpace(-2.0, 2.0, n+1);
	
	Matrix z2(m+1,n+1);
	
	for (int j=0; j<=n; j++)  
		for (int i=0; i<=m; i++)
			z2(i,j) = f(x2[i], y2[j]);

	// evaluate the polynomial at the points (a,b), storing back in p
	for (int j=0; j<75; j++) 
		for (int i=0; i<75; i++)
			p(i,j) = Lagrange2D(x2, y2, z2, a[i], b[j]);

	// output p to disk
	p.saveTo("../data/p20.txt");

} // end routine


