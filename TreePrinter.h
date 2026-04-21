#pragma once
#include "BinaryTree.h"
#include <iostream>
#include <string>

class TreePrinter {
public:
    static void print(Node* root, const std::string& title = "Дерево") {
        std::cout << "\n=== " << title << " ===\n";
        if (!root) {
            std::cout << "  (пусто)\n";
            return;
        }
        if (root->right) recPrint(root->right, "    ", false);
        std::cout << "─── " << getDataString(root->data) << '\n';
        if (root->left) recPrint(root->left, "    ", true);
        std::cout << "========================\n\n";
    }

private:
    static std::string getDataString(int data) {
        if (data == -100) return "x";
        if (data == -1) return "+";
        if (data == -2) return "-";
        if (data == -3) return "*";
        if (data == -4) return "/";
        if (data == -5) return "%";
        if (data == -6) return "^";
        return std::to_string(data);
    }

    static void recPrint(Node* q, std::string prefix, bool is_left) {
        if (!q) return;
        recPrint(q->right, prefix + (is_left ? "│    " : "     "), false);
        std::cout << prefix << (is_left ? "└── " : "┌── ") << getDataString(q->data) << '\n';
        recPrint(q->left, prefix + (is_left ? "    " : "│    "), true);
    }
};