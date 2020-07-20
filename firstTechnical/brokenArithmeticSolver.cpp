#include <bits/stdc++.h>
//#include <iostream>

using namespace std;

//------------------------------Consts------------------------------
const int eol = 10;
const int chk = 33;
const int spce = 32;
const int lparen = 40;
const int rparen = 41;
const int mult = 42;
const int add = 43;

//------------------------------Utils------------------------------

bool isNum(char val) {
    if (int(val) >= 48 && int(val) <= 57) {
        return true;
    }
    return false;
}

bool isSym(char val) {
    if (int(val) > 39 && int(val) < 44) {
        return true;
    }
    return false;
}

bool isParen(int val) {
    if (val == lparen || val == rparen) {
        return true;
    }
    return false;
}

int parseNum(int nchar) {
    return nchar - '0';
}

//------------------------------Node Class------------------------------
class Node {
        Node* parent = NULL;
        Node* left = NULL;
        Node* right = NULL;
        int val;
        bool hasP = false;
    public:
        Node() {
            this->val = chk;
        }
        Node(int val) {
            this->val = val;
        }
        Node(Node* left, Node* right) {
            this->val = chk;
            this->left = left;
            this->right = right;
        }
        Node(Node* left, int val) {
            this->val = val;
            this->left = left;
        }
        void setVal(int val) {
            this->val = val;
        }
        void setParent(Node* val) {
            this->parent = val;
            this->hasP = true;
        }
        void setLeft(Node* val) {
            this->left = val;
            this->left->setParentBool();
        }
        void setRight(Node* val) {
            this->right = val;
            this->right->setParentBool();
        }
        int getVal() {
            if(isNum(this->val)) {
                return parseNum(this->val);
            }else {
                return this->val;

            }
        }
        bool hasParent() {
            //cerr << this << " object" << endl;
            return this->hasP;
        }
        void setParentBool() {
            this->hasP = true;
        }
        Node* getParent() {
            //if (this->parent == NULL) {
                //return NULL;
            //}
            return this->parent;
        }
        Node* getLeft() {
            return this->left;
        }
        Node* getRight() {
            return this->right;
        }
    //private:
};


Node* makeTree() {
    char input[20];
    cin.getline(input, 20);
    Node* current = NULL;
    int nchar;
    for(char c:input) {
        nchar = int(c);
        if(nchar == spce){
            continue;
        }
        if(isSym(c)) {
            //cout << "in sym" << endl;
            if(nchar == lparen) {
                current = new Node();
                cout << "Left Parenthesis found. Creating empty parent node with default value " << char(current->getVal()) << endl;
            } else if(!isParen(nchar)) {
                if(!current->hasParent()) {
                    current->setParent(new Node(current, nchar));
                    current = current->getParent();
                    cout << "Found non parenthesis symbol. Creating parent node with value " << char(current->getVal()) << endl;
                }else if (current->getParent()->getVal() == chk){
                    current = current->getParent();
                    current->setVal(nchar);
                }
            } else if (isParen(nchar)) {
                current = current->getParent();
            }
        } else if (isNum(c)) {
            //cout << "in num" << endl;
            if (current == NULL) {
                //current->setLeft(new Node(parseNum(nchar)));
                current = new Node(parseNum(nchar));
                cout << "Current is not defined. Defining current with value " << current->getVal() << endl;
            }else if (current->getLeft() == NULL) {
                current->setLeft(new Node(parseNum(nchar)));
                cout << "Left node undefined. Defining with value " << current->getLeft()->getVal() << endl;
            }else if (current->getRight() == NULL) {
                current->setRight(new Node(parseNum(nchar)));
                cout << "Right node undefined. Defining with value " << current->getRight()->getVal() << endl;
            }
        }
    }
    return current;
}
int solve(Node* node){
    if(isNum(node->getVal())) {
        return node->getVal()
    }else if (node->getVal() == add) {
        return solve(node->getLeft()) + solve(node->getRight())
    }else if (node->getVal() == mult) {
        return solve(node->getLeft()) * solve(node->getRight())
    }

}

Node* findRoot(Node* node){
    //can't check for parents that don't exist
        while(node->hasParent()) {
            node = node->getParent();
        }
        return node
}

int main() {
    solve(findRoot(makeTree()))
}

