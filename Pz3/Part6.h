#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <Windows.h>
#include "Const.h"
class Part6 {
public:
    double sum = 0;
    static const int numberOfThreads = 4;  // Змініть на бажану кількість потоків
    HANDLE mutex = CreateMutex(NULL, FALSE, NULL);

    double f3(double x) {
        return 1 / (1 + x * x);
    }

    static DWORD WINAPI ThreadProc(LPVOID lpParameter) {
        auto params = reinterpret_cast<std::pair<Part6*, std::pair<double, double>>*>(lpParameter);
        Part6* instance = params->first;
        double startInterval = params->second.first;
        double endInterval = params->second.second;

        int numberOfInterval = Const::num/ numberOfThreads; // Замініть на реальні значення

        double interval = (endInterval - startInterval) / static_cast<double>(numberOfInterval);
        double TreadRes = 0.0;
        for (double currentX = startInterval; currentX < endInterval; currentX += interval) {
           // std::cout << "f3 = " << instance->f3(currentX) << "\n";
          //  std::cout << "interval = " << interval << "\n";
            double result = instance->f3(currentX) * interval;

            // Блокуємо м'ютекс перед зміною спільної змінної
          //  std::cout << "result = " << result << "\n";
            TreadRes += result;
           
            // Розблокуємо м'ютекс після зміни спільної змінної
        }
       // std::cout << "TreadRes = " << TreadRes  << "\n";
        instance->sum += TreadRes;
       //
        if (instance->sum * 4 > 3)
            std::cout << "sumWind = " << instance->sum * 4 << "\n";
        return 0;
    }

    static double m_thread(double a, double b, int number) {
        double interval = (b - a) / number;

        auto start = std::chrono::high_resolution_clock::now(); // Початок вимірювання часу
        Part6* instance = new Part6();
        // Створюємо та запускаємо потоки
        std::vector<std::thread> threads;
        std::vector<std::pair<Part6*, std::pair<double, double>>> threadParams;

        double threadInterval = (b - a) / number / numberOfThreads;
       // std::cout << "threadInterval = " << threadInterval << "~~~~~~~~\n";
        for (int i = 0; i < numberOfThreads; ++i) {
            double startInterval = a + i * threadInterval* number;
            double endInterval = startInterval + threadInterval* number;
           // std::cout << "startInterval = " << startInterval << "~~~~~~~~\n";
           // std::cout << "endInterval = " << endInterval << "~~~~~~~~~~~~~\n";
            threadParams.emplace_back(instance, std::make_pair(startInterval, endInterval));
            threads.emplace_back(ThreadProc, &threadParams[i]);
        }
      //  std::cout << "sum = " << instance->sum * 4 << "\n";
        // З'єднуємо потоки
        for (auto& thread : threads) {
            thread.join();
        }

        auto finish = std::chrono::high_resolution_clock::now(); // Завершення вимірювання часу
        std::chrono::duration<double> elapsed = finish - start; // Обчислюємо час виконання в секундах
        std::cout << "Time elapsedWindows: " << elapsed.count() << " seconds." << std::endl;

        // Припускаючи, що sum - це член класу
       // return instance->sum;
        return 0;
    }
};