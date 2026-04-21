#pragma execution_character_set("utf-8")//для символов вывода дерева
#include <iostream>
#include <windows.h>
#include "CalcTree6.h"
#include "CalcTree24.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice;
    while (true) {
        std::cout << "\n=== ЛАБОРАТОРНАЯ РАБОТА №17 ===\n";
        std::cout << "1. CalcTree6 (Префиксная форма)\n";
        std::cout << "2. CalcTree24 (Инфиксная форма)\n";//Сначала лк, потом пк = корень
        std::cout << "0. Выход\nВыбор: ";
        if (!(std::cin >> choice) || choice == 0) break;

        if (choice == 1) CalcTree6::run();
        else if (choice == 2) CalcTree24::run();
    }
}//3 4 4