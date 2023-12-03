#include <cmath>
#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <windows.h>  // Додайте цей заголовочний файл для доступу до функцій Windows API
double pi(int n) {
	double angleInRadians = 180.0 / n;
	double angleInDgs =  3.1415926535897931/n;
	//std::cout << "\nx = " << 2 * n * sin(angleInRadians) << "\n";

	return  2*n * sin(angleInDgs/2);
}
double f(double x) {

	return sqrt(1 - x * x);
}

//a- нижня границя інтегрування,
//b- верхня,
//number- число рівних відрізків на які ділиться інтервал
double n(double a, double b, int number) {
	double sum = 0;
	//int j = 0;
	double interval = (b - a) / number;
	for (double i = a; i <= b; i += interval) {
		sum += f(i) * interval;
		//  std::cout <<j<<", "<<i << "\n";
		//j++;
	}
	return sum;
}
