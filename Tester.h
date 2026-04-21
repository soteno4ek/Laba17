#pragma once
#include <iostream>
#include <limits>
#include <string>

class Tester {
public:
    template <typename T>//функция для работы с любым типом данных
    static T getValidInput(std::istream& in) {
        T value;
        while (!(in >> value)) {
            in.clear();
            in.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
        return value;
    }

    static int getInt(std::string msg) {
        std::cout << msg;
        return getValidInput<int>(std::cin);
    }

    static long long getLong(std::string msg) {
        std::cout << msg;
        return getValidInput<long long>(std::cin);
    }

    static bool isOperator(int val) {
        return val <= -1 && val >= -6;
    }
};