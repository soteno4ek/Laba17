#pragma once
#include "BinaryTree.h"
#include "TreePrinter.h"
#include "Tester.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <climits>

class CalcTree24 : public BinaryTree {
public:
    static void run() {
        srand((unsigned int)time(0));
        int choice;
        do {
            std::cout << "\nCalcTree24.В текстовом файле с именем FN1 дано арифметическое выражение в инфиксной форме.\n"
                "В выражении могут использоваться операции: сложение(+), вычитание(-), умножение(*),\n"
                "деление нацело(/), остаток от деления(%), возведение в степень(^), а также целые числа\n"
                "из промежутка [1; 30] и переменная x. Для операции возведения в степень показатель\n"
                "степени неотрицательное целое число. Постройте дерево выражения.\n"
                "После этого вычислите значение выражения при заданном значении переменной x и выведите\n"
                "результат в текстовый файл с именем FN2. Преобразуйте дерево, заменив все поддеревья\n"
                "вида x*A на A*x, где A - некоторое поддерево, а x - переменная.\n"
                "Распечатайте дерево после преобразования в файл FN2 используя многострочный формат,\n"
                "в котором дерево положено на бок. Каждый уровень дерева выводите в 4-х позициях\n"
                "и используйте выравнивание по правому краю.\n\n";

            std::cout << "1. Ввести коды вручную (префикс)\n"
                "2. Прочитать из файла FN1.txt\n"
                "3. Сгенерировать случайное дерево\n"
                "0. Назад\n";

            choice = Tester::getInt("Выберите способ: ");
            if (choice == 0) break;

            CalcTree24 task;
            if (choice == 3) {
                int n = Tester::getInt("Введите количество элементов: ");
                n += 1;
                int maxD = n;
                int curN = 0;
                task.root = task.generateRandom(maxD, n, curN);
            }
            else {
                std::vector<int> tokens;
                if (choice == 1) {
                    int n = Tester::getInt("Кол-во элементов: ");
                    std::cout << "Введите коды (x = -100): ";
                    for (int i = 0; i < n; ++i) tokens.push_back(Tester::getInt(""));
                }
                else {
                    std::ifstream f("FN1.txt");
                    if (!f.is_open()) { std::cout << "Файл FN1.txt не найден\n"; continue; }
                    int val;
                    while (f >> val) tokens.push_back(val);
                }
                int idx = 0;
                task.root = task.buildFromPrefix(tokens, idx);
            }

            if (!task.root) continue;

            TreePrinter::print(task.root, "Исходное дерево (с 'x')");

            long long xVal = Tester::getLong("Введите значение x для расчета: ");

            long long result = task.calcX(task.root, xVal);

            task.transformX(task.root);

            task.replaceXWithVal(task.root, xVal);

            std::ofstream out("FN2.txt");
            if (out.is_open()) {
                out << "Значение x: " << xVal << "\n";
                out << "Результат вычисления: " << result << "\n";
                out << "Префиксная форма после трансформации и подстановки: ";
                task.printPrefix(task.root, out);
                out << "\n\nДерево после трансформации:\n";
                task.filePrintSide(task.root, 0, out);
                out.close();
                std::cout << "\nРезультат " << result << " записан в FN2.txt\n";
            }

            TreePrinter::print(task.root, "Трансформированное дерево (x заменен на число)");

            std::cout << "\n>^•w•^<\n";

        } while (choice != 0);
    }

private:
    void replaceXWithVal(Node* n, long long xVal) {
        if (!n) return;
        if (n->data == -100) n->data = (int)xVal;
        replaceXWithVal(n->left, xVal);
        replaceXWithVal(n->right, xVal);
    }

    void transformX(Node* n) {
        if (!n) return;
        transformX(n->left);
        transformX(n->right);

        if (n->data == -3 && n->left && n->left->data == -100) {
            std::swap(n->left, n->right);
        }
    }

    long long calcX(Node* n, long long x) {
        if (!n) return 0;
        if (n->data == -100) return x;
        if (!Tester::isOperator(n->data)) return (long long)n->data;

        long long L = calcX(n->left, x);
        long long R = calcX(n->right, x);

        switch (n->data) {
        case -1: return L + R;
        case -2: return L - R;
        case -3: return L * R;
        case -4: return (R != 0) ? (L / R) : 0;
        case -5: return (R != 0) ? (L % R) : 0;
        case -6: {
            if (R < 0) return 0;
            if (R == 0) return 1;
            if (L == 0) return 0;
            if (L == 1) return 1;
            long long res = 1;
            for (int i = 0; i < R; ++i) {
                if (res > LLONG_MAX / std::abs(L)) return (L > 0) ? LLONG_MAX : 0;
                res *= L;
            }
            return res;
        }
        default: return 0;
        }
    }

    void filePrintSide(Node* q, int level, std::ofstream& out) {
        if (!q) return;
        filePrintSide(q->right, level + 1, out);
        out << std::setw(level * 4) << "" << std::setw(4) << std::right << getSym(q->data) << "\n";
        filePrintSide(q->left, level + 1, out);
    }

    void printPrefix(Node* n, std::ofstream& out) {
        if (!n) return;
        out << getSym(n->data) << " ";
        printPrefix(n->left, out);
        printPrefix(n->right, out);
    }

    std::string getSym(int d) {
        if (d == -100) return "x";
        switch (d) {
        case -1: return "+"; case -2: return "-"; case -3: return "*";
        case -4: return "/"; case -5: return "%"; case -6: return "^";
        default: return std::to_string(d);
        }
    }

    Node* generateRandom(int depth, int maxNodes, int& currentNodes) {
        if (depth > 1 && currentNodes < maxNodes - 2) {
            currentNodes++;
            Node* node = new Node(-(1 + rand() % 6));
            node->left = generateRandom(depth - 1, maxNodes, currentNodes);
            node->right = generateRandom(depth - 1, maxNodes, currentNodes);
            return node;
        }
        currentNodes++;
        if (rand() % 10 < 3) return new Node(-100);
        return new Node(1 + rand() % 30);
    }

    Node* buildFromPrefix(const std::vector<int>& tokens, int& idx) {
        if (idx >= (int)tokens.size()) return nullptr;
        int val = tokens[idx++];
        Node* node = new Node(val);
        if (Tester::isOperator(val)) {
            node->left = buildFromPrefix(tokens, idx);
            node->right = buildFromPrefix(tokens, idx);
        }
        return node;
    }
};