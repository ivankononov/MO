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
double f4(double, double);
double f5(double, double);
double gold(double, double, double, double);
void min2(double, double, double, double, double&, double&, double);
int gradient_method(double&, double&, double);
double find_lamb(double, double, vector<double>, double);
vector<double> f1_grad(double, double);
vector<double> f2_grad(double, double);
vector<double> f4_grad(double, double);
vector<double> f5_grad(double, double);
vector<double> gradient(double, double);
void print1(double, double, double, double, double);
void print2(double, double, double, double, double);

static double Z = 2 / (1 + sqrt(5)); //golden-section const
//static double e = 0.001; //accuracy
int counter = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	double ax = -5, ay = 5, bx = -5, by = 5;
	double e = pow(10, -4);
	print2(ax, ay, bx, by, pow(10, -6));

	
	
	system("pause");
	return 0;
}

void print1(double ax, double ay, double bx, double by, double e){//вывод вложенный тернарный поиск
	double x, y;
	min2(ax, ay, bx, by, x, y, e);
	printf("\ne = %.10f\niter count = %d\nx = %.10f\ny = %.10f\nmin = %.10f\n", e, counter, x, y, f(x, y));
	counter = 0;
}

void print2(double ax, double ay, double bx, double by, double e){//вывод вложенный тернарный поиск
	double x=1, y=1;
	int i = gradient_method(x, y, e);
	printf("\ne = %.10f\niter count = %d\nx = %.10f\ny = %.10f\nmin = %.10f\n", e, i, x, y, f(x, y));
	counter = 0;
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

int gradient_method(double &x, double &y, double e){
	double lamb, x1, y1;
	vector<double> grad;
	int i = 0;
	do{
		x1 = x; y1 = y;
		grad = gradient(x, y);
		lamb = find_lamb(x, y, grad, e);
		x = x - lamb * grad[0];
		y = y - lamb * grad[1];
		i++;
		//printf("x = %.10f  y = %.10f\n", x, y);
	} while (sqrt(pow(x-x1,2)+pow(y-y1,2)) >= e && i < 999999);
	return i;
}

double find_lamb(double x, double y, vector<double> grad, double e){
	double y1, y2;
	double a = 0, b = 1;
	double lamb1, lamb2;
	e = pow(10, -10);
	lamb1 = b - (b - a) * Z;
	lamb2 = a + (b - a) * Z;
	y1 = f(x - lamb1 * grad[0], y - lamb1 * grad[1]);
	y2 = f(x - lamb2 * grad[0], y - lamb2 * grad[1]);

	while (true){
		if (y1 >= y2)
		{
			a = lamb1;
			lamb1 = lamb2;
			y1 = y2;
			lamb2 = a + (b - a) * Z;
			y2 = f(x - lamb2 * grad[0], y - lamb2 * grad[1]);
		}
		else
		{
			b = lamb2;
			lamb2 = lamb1;
			y2 = y1;
			lamb1 = b - (b - a) * Z;
			y1 = f(x - lamb1 * grad[0], y - lamb1 * grad[1]);
		}
		if (abs(b - a) < e)
			return (a + b) / 2;
	}
}

double f(double x, double y){
	counter++;
	return f4(x, y);
}

vector<double> gradient(double x, double y){
	return f4_grad(x, y);
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

double f4(double x, double y){
	return pow(x - 3, 2) + pow(y - 4, 2);
}
double f5(double x, double y){
	return pow(x - 3, 2) + 2*pow(y - 4, 2);
}


vector<double> f1_grad(double x, double y){
	//vector<double> grad = { 2 * x - y - 2, -x + 2 * y };
	return vector <double> {2 * x - y - 2, -x + 2 * y};
}
vector<double> f2_grad(double x, double y){
	//vector<double> grad = { 2 * x - y - 2, -x + 2 * y };
	return vector <double> {2.2*x-2*y*y-0.14, 4*x*y+4*y*y*y};
}

vector<double> f4_grad(double x, double y){
	return vector < double > {2 * x - 6, 2 * y - 8};
}
vector<double> f5_grad(double x, double y){
	return vector < double > {2 * x - 6, 4 * y - 16};
}

