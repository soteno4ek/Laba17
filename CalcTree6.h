#pragma once
#include "BinaryTree.h"
#include "TreePrinter.h"
#include "Tester.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <string>

class CalcTree6 : public BinaryTree {
public:
    static void run() {
        srand((unsigned int)time(0));
        int choice;
        do {
            std::cout << "\nCalcTree6. В текстовом файле с именем filename дано арифметическое выражение в\n"
                "префиксной форме. Операндами в выражении являются целые числа из промежутка от 0 до 9.\n"
                "Используемые операции: сложение (+), вычитание (-), умножение (*), деление нацело (/),\n"
                "целочисленный остаток от деления (%) и возведение в степень (^). Постройте дерево,\n"
                "соответствующее данному выражению. Знаки операций кодируйте числами: сложение(-1),\n"
                "вычитание(-2), умножение(-3), деление(-4), остаток от деления(-5), возведение в степень (-6).\n"
                "Преобразуйте дерево так, чтобы в нем не было операций возведения в степень (замените\n"
                "поддеревья, в которых есть возведение в степень, значением данного поддерева).\n"
                "Выведите указатель на корень полученного дерева.\n\n";

            std::cout << "1. Ввести числа вручную\n"
                "2. Прочитать из файла filename.txt\n"
                "3. Сгенерировать случайный набор\n"
                "0. Назад\n";
            choice = Tester::getInt("Выберите способ: ");

            if (choice == 0) break;

            CalcTree6 task;
            if (choice == 3) {
                int n = Tester::getInt("Введите количество элементов: ");
                int maxD = n;
                int curN = 0;
                bool hasPower = false;
                task.root = task.generateWithPower(maxD, n, curN, hasPower);
            }
            else {
                std::vector<int> tokens;
                if (choice == 1) {
                    int n = Tester::getInt("Введите количество элементов: ");
                    std::cout << "Введите коды (через пробел): ";
                    for (int i = 0; i < n; i++) tokens.push_back(Tester::getInt(""));
                }
                else if (choice == 2) {
                    std::ifstream f("filename.txt");
                    if (!f.is_open()) { std::cout << "Файл не найден!\n"; continue; }
                    int v; while (f >> v) tokens.push_back(v);
                }
                int idx = 0;
                task.root = task.buildFromPrefix(tokens, idx);
            }

            if (!task.root) continue;

            TreePrinter::print(task.root, "Структура до");

            std::string exprBefore = task.toInfix(task.root);
            std::cout << "\nИсходное выражение: " << exprBefore << " = " << task.semiTree(task.root) << "\n";

            task.replacePower(task.root);

            TreePrinter::print(task.root, "Структура после (степени вычислены)");

            std::cout << "После замены степеней: " << task.toInfix(task.root) << "\n";
            std::cout << "Указатель на корень итогового дерева: " << (void*)task.root << "\n";

            std::cout << "\n>^•w•^<\n";

        } while (choice != 0);
    }

private:
    std::string toInfix(Node* n) {
        if (!n) return "";
        if (!Tester::isOperator(n->data)) return std::to_string(n->data);
        return "(" + toInfix(n->left) + " " + getSym(n->data) + " " + toInfix(n->right) + ")";
    }

    std::string getSym(int d) {
        switch (d) {
        case -1: return "+"; case -2: return "-"; case -3: return "*";
        case -4: return "/"; case -5: return "%"; case -6: return "^";
        default: return std::to_string(d);
        }
    }

    Node* generateWithPower(int depth, int maxNodes, int& currentNodes, bool& hasPower) {
        if (depth <= 1 || currentNodes >= maxNodes - 1) {
            currentNodes++;
            return new Node(rand() % 10);
        }
        currentNodes++;
        int op = -(1 + rand() % 6);
        if (currentNodes == 1 && rand() % 2 == 0) op = -6;
        if (op == -6) hasPower = true;

        Node* node = new Node(op);
        node->left = generateWithPower(depth - 1, maxNodes, currentNodes, hasPower);
        node->right = generateWithPower(depth - 1, maxNodes, currentNodes, hasPower);

        if (currentNodes >= maxNodes - 3 && !hasPower) {
            node->data = -6;
            hasPower = true;
        }
        return node;
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

    int semiTree(Node* n) {
        if (!n) return 0;
        if (!Tester::isOperator(n->data)) return n->data;
        int L = semiTree(n->left);
        int R = semiTree(n->right);
        switch (n->data) {
        case -1: return L + R; case -2: return L - R;
        case -3: return L * R; case -4: return R ? L / R : 0;
        case -5: return R ? L % R : 0;
        case -6: return (int)std::pow(L, R);
        default: return 0;
        }
    }

    void clearRec(Node* n) {
        if (!n) return;
        clearRec(n->left);
        clearRec(n->right);
        delete n;
    }

    void replacePower(Node*& n) {
        if (!n) return;
        replacePower(n->left);
        replacePower(n->right);
        if (n->data == -6) {
            int val = semiTree(n);
            clearRec(n->left);
            clearRec(n->right);
            n->left = n->right = nullptr;
            n->data = val;
        }
    }
};