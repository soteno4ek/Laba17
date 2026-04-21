#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
protected:
    Node* root;

    void clearRec(Node* node) {
        if (!node) return;
        clearRec(node->left);
        clearRec(node->right);
        delete node;
    }

    void printRecursive(Node* node, std::string prefix, bool isLeft, std::ostream& out) const {
        if (!node) return;

        if (node->right) {
            printRecursive(node->right, prefix + (isLeft ? "│    " : "     "), false, out);
        }

        out << prefix << (isLeft ? "└── " : "┌── ");

        if (node->data == -100) out << "x";
        else if (node->data == -1) out << "+";
        else if (node->data == -2) out << "-";
        else if (node->data == -3) out << "*";
        else if (node->data == -4) out << "/";
        else if (node->data == -5) out << "%";
        else if (node->data == -6) out << "^";
        else out << node->data;
        out << "\n";

        if (node->left) {
            printRecursive(node->left, prefix + (isLeft ? "    " : "│    "), true, out);
        }
    }

public:
    BinaryTree() : root(nullptr) {}
    virtual ~BinaryTree() { clear(); }

    void clear() {
        clearRec(root);
        root = nullptr;
    }

    Node* getRoot() const { return root; }
    void setRoot(Node* newRoot) { root = newRoot; }

    void printGraphic(std::ostream& out = std::cout) const {
        if (!root) {
            out << "Дерево пусто\n";
            return;
        }
        printRecursive(root, "", true, out);
    }
};