#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
class Part8 {
public:
	double sum = 0;

	double f3(double x) {
		return 1 / (1 + x * x);
	}


	static double m_thread(double a, double b, int number) {

		
		double interval = (b - a) / number;
		Part6* instance = new Part6();

		auto start = std::chrono::high_resolution_clock::now(); // Початок вимірювання часу
		omp_set_num_threads(4);
#pragma omp parallel
		{
			double localSum = 0.0;
			//std::cout << "Number of threads: " << omp_get_num_threads() << std::endl;

#pragma omp for
			for (int i = 0; i < number; ++i) {
				double startInterval = a + i * interval;
				double endInterval = startInterval + interval;
				double threadResult = 0.0;

				for (double currentX = startInterval; currentX < endInterval; currentX += interval) {
					threadResult += instance->f3(currentX) * interval;
				}

				localSum += threadResult;
			}

#pragma omp critical
			{
				instance->sum += localSum;
				if(instance->sum * 4>3)
					std::cout << "sumOpenMP = " << instance->sum*4<<"\n";
			}
		}

		auto finish = std::chrono::high_resolution_clock::now(); // Завершення вимірювання часу
		std::chrono::duration<double> elapsed = finish - start; // Обчислюємо час виконання в секундах
		std::cout << "Time elapsedOpenMP: " << elapsed.count() << " seconds." << std::endl;

		return instance->sum * 4;
	}
};
