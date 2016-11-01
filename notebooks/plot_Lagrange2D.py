#!/usr/bin/env python
#
# Lagrange2D testing script
#
# Daniel R. Reynolds
# SMU Mathematics
# Math 3316
# 1 October 2015

from pylab import *

# Load all data output by test_Lagrange2D.cpp routine:

a = loadtxt('a.txt')
b = loadtxt('b.txt')
f = loadtxt('ftrue.txt')
p10 = loadtxt('p10.txt')
p20 = loadtxt('p20.txt')

# Plot $f(x,y)$ first

from mpl_toolkits.mplot3d.axes3d import Axes3D
fig = figure()
ax = fig.add_subplot(111, projection='3d')
X, Y = meshgrid(b, a)
surf = ax.plot_surface(X, Y, f, rstride=1, cstride=1, linewidth=0, cmap=cm.jet)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$f(x,y)$')
savefig('Lagrange2D_f.png')

# Now plot both $p_{10}(x,y)$ and $p_{20}(x,y)$

fig = figure()
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(X, Y, p10, rstride=1, cstride=1, linewidth=0, cmap=cm.jet)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$p_{10}(x,y)$')
savefig('Lagrange2D_p10.png')

fig = figure()
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(X, Y, p20, rstride=1, cstride=1, linewidth=0, cmap=cm.jet)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$p_{20}(x,y)$')
savefig('Lagrange2D_p20.png')

# Now plot the error in p10

e10 = abs(f-p10)
fig = figure()
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(X, Y, e10, rstride=1, cstride=1, linewidth=0, cmap=cm.jet)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$|f(x,y) - p_{10}(x,y)|$')
savefig('Lagrange2D_e10.png')

e20 = abs(f-p20)
fig = figure()
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(X, Y, e20, rstride=1, cstride=1, linewidth=0, cmap=cm.jet)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$|f(x,y) - p_{20}(x,y)|$')
savefig('Lagrange2D_e20.png')

# Now check the max error for each, and compare against a known tolerance for
# these functions over these intervals with this many nodes 

e10tol = 0.058
e20tol = 3.7e-8
e10norm = sqrt(sum(sum(e10**2))/size(e10))
e20norm = sqrt(sum(sum(e20**2))/size(e20))
if (e10norm > e10tol):
    print 'p10 faulure!  ||e10|| = ', e10norm, ' is above tolerance of ',e10tol
else:
    print 'p10 success!  ||e10|| = ', e10norm, ' is below tolerance of ',e10tol
if (e20norm > e20tol):
    print 'p20 failure!  ||e20|| = ', e20norm, ' is above tolerance of ',e20tol
else:
    print 'p20 success!  ||e20|| = ', e20norm, ' is below tolerance of ',e20tol

