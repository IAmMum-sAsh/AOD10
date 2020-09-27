#include <iostream>
using namespace std;

struct leaf {
private:
    leaf* parent = NULL;
    leaf* left = NULL;
    leaf* right = NULL;
    int number;
    int hight = 1;

public:
    leaf(int number) { this->number = number; }

    int getNumber() { return this->number; }

    void setParent(leaf* parent) { this->parent = parent; }
    void setLeft(leaf* left) { this->left = left; }
    void setRight(leaf* right) { this->right = right; }
    void setHight(int number) { this->hight = number; }

    leaf* getParent() { return this->parent; }
    leaf* getLeft() { return this->left; }
    leaf* getRight() { return this->right; }
    int Hight() { return this ? this->hight : 0; }
    int getHight(leaf* node) { return node ?node->Hight() : 0; }

    void addLeaf(leaf* node){ 
        if (this->number >= node->getNumber()) {
            if (this->left == NULL) { this->left = node; this->left->setParent(this); }
            else  this->left->addLeaf(node);
            balance(this);
        }
        else {
            if (this->right == NULL) { this->right = node; this->right->setParent(this);}
            else  this->right->addLeaf(node);
            balance(this);
        }
    }

    leaf* findRoot() {
        if (this->parent != NULL) this->parent->findRoot();
        else return this;
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
            if (buffer->getRight() != NULL) buffer->getLeft()->addLeaf(buffer->getRight());
            balance(this->left);
            delete buffer;
        }
        else if (buffer->getRight() != NULL) {
            buffer->getRight()->setParent(buffer->getParent());
            if (buffer->getParent()->getLeft() == buffer) buffer->getParent()->setLeft(buffer->getRight());
            else buffer->getParent()->setRight(buffer->getRight());
            balance(this->left);
            delete buffer;
        }
    }

    void printSort() {
        if (this != NULL) {
            this->getLeft()->printSort();
            cout << this->number << " ";
            this->getRight()->printSort();
        }
    }
   
    int checkBalance(leaf* node) {
        return getHight(node->getRight()) - getHight(node->getLeft());
    }
    
    void fixHight(leaf* node) {
        int hightLeft = getHight(node->getLeft());
        int hightRight = getHight(node->getRight());
        node->setHight((hightLeft > hightRight ? hightLeft : hightRight)+1);
    }
    leaf* rotateright(leaf* node) // правый поворот вокруг p
    {
        leaf* buff = node->getLeft();
        node->setLeft(buff->getRight());
        buff->setRight(node);
        fixHight(node);
        fixHight(buff);
        return buff;
    }

    leaf* rotateleft(leaf* node) // левый поворот вокруг q
    {
        leaf* buff =  node->getRight();
        node->setRight( buff->getLeft());
        buff->setLeft(node);
        fixHight(node);
        fixHight(buff);
        return buff;
    }

    leaf* balance(leaf* node) // балансировка узла p
    {   
        fixHight(node);
        if (checkBalance(node) == 2)
        {
            if (checkBalance(node->getRight()) < 0)
                node->setRight(rotateright(node->getRight()));
            return rotateleft(node);
        }
        else if ((checkBalance(node)) == -2)
        {
            if (checkBalance(node->getLeft()) > 0)
               node->setLeft(rotateleft(node->getLeft()));
            return rotateright(node);
        }
        return node; // балансировка не нужна
    }
};



int main() {
    int mass[12] = { 8, 6, 10, 4, 7, 9, 15, 2, 5, 14, 16, 3 };
    leaf* root = new leaf(mass[0]);

    for (int i = 1; i < 12; i++) {
        leaf* node = new leaf(mass[i]);
        root->addLeaf(node);
    }

    root->printSort();
    int a = 1;
    leaf* check = root->findLeaf(14);

    root->deleteLeaf(4); cout << endl;

    root->printSort();

    cout << endl << "The end";
}