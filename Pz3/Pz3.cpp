// Pz3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <windows.h> 
#include <chrono>
#include "Part3.h" 
#include "Part6.h" 
#include "Part8.h" 
#include "Const.h"
#include <iomanip>
double f2(double x) {
	return 1 / (1 + x * x);
}
//a- нижня границя інтегрування,
//b- верхня,
//number- число рівних відрізків на які ділиться інтервал
double m(double a, double b, int number) {

	double sum = 0;
	double interval = (b - a) / number;

	auto start = std::chrono::high_resolution_clock::now(); // Початок вимірювання часу

	for (double i = a; i <= b; i += interval) {
		sum += f2(i) * interval;
	}

	auto finish = std::chrono::high_resolution_clock::now(); // Завершення вимірювання часу
	std::chrono::duration<double> elapsed = finish - start; // Обчислюємо час виконання в секундах
	std::cout << "Time elapsed: " << elapsed.count() << " seconds." << std::endl;

	return sum;
}
void Part2() {
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	std::cout << "    Windows cores: " << si.dwNumberOfProcessors << std::endl;
	auto cores = omp_get_max_threads();
	std::cout << "    omp cpu cores: " << cores << std::endl;
}
int main()
{
	//Part2();
//	// множимо на 4, бо інтеграл дорівнює пі/4
//#ifdef _OPENMP
//	printf("_OPENMP Defined\n");
//#else
//	printf("_OPENMP UnDefined\n");
//#endif
	
	std::cout << std::setprecision(16) <<m(0, 1, Const::num)*4<<"\n";
	//std::cout << n(0, 1, Const::num) * 4 << "\n";
	//std::cout << pi( Const::num)<< "\n";
	std::cout << std::setprecision(16);
	Part6 p;
	p.m_thread(0, 1, Const::num);
	Part8::m_thread(0, 1, Const::num);
	//std::cout << pi(50000);
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
