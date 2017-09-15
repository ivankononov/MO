// Lab1.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

double f(double, double);
double f1(double, double);
double f2(double, double);
double f3(double);
double gold(double, double, double, double);
void min2(double, double, double, double, double&, double&, double);
vector<double> f1_grad(double, double);

static double Z = 2 / (1 + sqrt(5)); //golden-section const
//static double e = 0.001; //accuracy
int counter = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	double x, y;
	double e = pow(10, -4);
	min2(-5, 5, -5, 5, x, y, e);
	printf("e = %.10f\niter count = %d\nx = %.10f\ny = %.10f\nmin = %.10f\n\n", e, counter, x, y, f(x, y));
	counter = 0;
	e = pow(10, -6);
	min2(-5, 5, -5, 5, x, y, e);
	printf("e = %.10f\niter count = %d\nx = %.10f\ny = %.10f\nmin = %.10f\n\n", e, counter, x, y, f(x, y));
	counter = 0;
	e = pow(10, -8);
	min2(-5, 5, -5, 5, x, y, e);
	printf("e = %.10f\niter count = %d\nx = %.10f\ny = %.10f\nmin = %.10f\n\n", e, counter, x, y, f(x, y));
	counter = 0;

	/*vector<double> v = f1_grad(1, 0);
	printf("[%f, %f]", v[0], v[1]);*/
	
	system("pause");
	return 0;
}

void min2(double ax, double bx, double ay, double by, double &x, double &y, double e){// вложенный тернарный поиск
	double x1, x2, y1, y2, z1, z2;
	x1 = bx - (bx - ax) * Z;
	x2 = ax + (bx - ax) * Z;
	y1 = gold(ay, by, x1, e);
	y2 = gold(ay, by, x2, e);
	z1 = f(x1, y1);
	z2 = f(x2, y2);
	while (true){
		if (z1 >= z2)
		{
			ax = x1;
			x1 = x2;
			z1 = z2;
			x2 = ax + (bx - ax) * Z;
			y2 = gold(ay, by, x2, e);
			z2 = f(x2, y2);
		}
		else
		{
			bx = x2;
			x2 = x1;
			z2 = z1;
			x1 = bx - (bx - ax) * Z;
			y1 = gold(ay, by, x1, e);
			z1 = f(x1, y1);
		}
		if (abs(bx - ax) < e)
		{
			x = (ax + bx) / 2;
			y = (y1 + y2) / 2;
			break;
		}
	}
}

double gold(double a, double b, double x, double e){ // golden-section search
	double x1, x2, y1, y2;
	x1 = b - (b - a) * Z;
	x2 = a + (b - a) * Z;
	y1 = f(x,x1);
	y2 = f(x,x2);
	while (true){
		if (y1 >= y2)
		{
			a = x1;
			x1 = x2;
			y1 = y2;
			x2 = a + (b - a) * Z;
			y2 = f(x,x2);
		}
		else
		{
			b = x2;
			x2 = x1;
			y2 = y1;
			x1 = b - (b - a) * Z;
			y1 = f(x,x1);
		}
		if (abs(b - a) < e)
			return (a + b) / 2;
	}
}


double f(double x, double y){
	counter++;
	return f2(x, y);
}

double f1(double x, double y){ // x^2-xy+y^2-2x
	return x*x - x*y + y*y - 2 * x;
}

double f2(double x, double y){
	return pow(x - y*y, 2) + 0.1*pow(x - 0.7, 2);
}

double f3(double x){
	counter++;
	return x*x - 5 * x;
}

vector<double> f1_grad(double x, double y){
	//vector<double> grad = { 2 * x - y - 2, -x + 2 * y };
	return vector <double> {2 * x - y - 2, -x + 2 * y};
}