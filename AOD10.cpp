﻿#include <iostream>
using namespace std;

struct leaf {
private:
    leaf* parent = NULL;
    leaf* left = NULL;
    leaf* right = NULL;
    int number;
public:
    leaf(int number) { this->number = number; }
    int getNumber() { return this->number; }
    void setParent(leaf* parent) { this->parent = parent; }
    leaf* getParent() { return this->parent; }
    void setLeft(leaf* left) { this->left = left; }
    leaf* getLeft() { return this->left; }
    void setRight(leaf* right) { this->right = right; }
    leaf* getRight() { return this->right; }
    void addLeaf(leaf* node){
        if (this->number >= node->getNumber()) {
            if (this->left == NULL) { this->left = node; this->left->setParent(this); }
            else this->left->addLeaf(node); 
        }
        else {
            if (this->right == NULL) { this->right = node; this->right->setParent(this);}
            else this->right->addLeaf(node);
        }
    }
    leaf* findLeaf(int number) {
        if (this->number == number) return this;
        else if (this->number <= number) this->right->findLeaf(number);
        else this->left->findLeaf(number);
    }
    void deleteLeaf(int number) {
        leaf* buffer = findLeaf(number);
        if (buffer->getLeft() != NULL) {
            buffer->getLeft()->setParent(buffer->getParent());
            if (buffer->getParent()->getLeft() == buffer) buffer->getParent()->setLeft(buffer->getLeft());
            else buffer->getParent()->setRight(buffer->getLeft());
            if (buffer->getRight()!=NULL) buffer->getLeft()->addLeaf(buffer->getRight());
            delete buffer;
        }
        else if(buffer->getRight() != NULL){
            buffer->getRight()->setParent(buffer->getParent()); 
            if (buffer->getParent()->getLeft() == buffer) buffer->getParent()->setLeft(buffer->getRight());
            else buffer->getParent()->setRight(buffer->getRight());
            delete buffer;
        }
    }
};



int main() {
    leaf* root = new leaf(8);
    int mass[11] = {6, 10, 4, 7, 9, 15, 2, 5, 14, 16, 3};
    for (int i = 0; i < 11; i++) {
        leaf* node = new leaf(mass[i]);
        root->addLeaf(node);
    }
    leaf* check = root->findLeaf(14);
    root->deleteLeaf(4);
    int a = 6;
}
