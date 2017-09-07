// Lab1.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <math.h>

using namespace std;

double f(double, double);
double f1(double, double);
double f2(double, double);
double gold(double, double, double);
void min2(double, double, double, double, double&, double&);

static double Z = (1 + sqrt(5)) / 2; //golden-section const
static double e = 0.001; //accuracy

int _tmain(int argc, _TCHAR* argv[])
{
	double x, y;
	min2(-5, 5, -5, 5, x, y);
	printf("x = %f\ny = %f\nmin = %f\n", x, y, f(x, y));
	system("pause");
	return 0;
}

void min2(double ax, double bx, double ay, double by, double &x, double &y){
	double currX;
	x = currX = ax;
	y = gold(ay, by, currX);
	currX += e;
	while (currX < bx){
		double miny = gold(ay, by, currX);
		if (f(x,y) > f(currX,miny))
		{
			x = currX;
			y = miny;
		}
		currX += e;
	}
}

double gold(double a, double b, double x){ // golden-section search
	double x1, x2;
	while (true){
		x1 = b - (b - a) / Z;
		x2 = a + (b - a) / Z;
		if (f(x, x1) >= f(x, x2))
			a = x1;
		else
			b = x2;
		if (abs(b - a) < e)
			return (a + b) / 2;
	}
}

double f(double x, double y){
	return f1(x, y);
}

double f1(double x, double y){ // x^2-xy+y^2-2x
	return x*x - x*y + y*y - 2 * x;
}

double f2(double x, double y){
	return pow(x - y*y, 2) + 0.1*pow(x - 0.7, 2);
}