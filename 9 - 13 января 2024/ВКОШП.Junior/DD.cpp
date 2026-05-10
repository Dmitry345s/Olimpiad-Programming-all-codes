#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include<tuple>
#include<cstdio>
#include <random>
using namespace std;

struct  Node {
    long long int x, y;
    Node* left, * right;
    Node() {}
    Node(long long int x) {
        this->x = x;
        this->y = rand();
        this->left = nullptr;
        this->right = nullptr;
    }
    ~Node() {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
    }
};


pair<Node*, Node*> split_tree(Node* root, long long int key) { // first <= x, second - > x
    if (root == nullptr) {
        return { nullptr, nullptr };
    }
    else if (root->x <= key) {
        pair <Node*, Node*> splitted = split_tree(root->right, key);
        root->right = splitted.first;
        return { root, splitted.second };
    }
    else {
        pair <Node*, Node*> splitted = split_tree(root->left, key);
        root->left = splitted.second;
        return { splitted.first, root };
    }
}

Node* merge(Node* root1, Node* root2) {
    if (root1 == nullptr) {
        return root2;
    }
    else if (root2 == nullptr) {
        return root1;
    }
    else if (root1->y > root2->y) {
        Node* mrg_right = merge(root1->right, root2);
        root1->right = mrg_right;
        return root1;
    }
    else {
        Node* mrg_left = merge(root1, root2->left);
        root2->left = mrg_left;
        return root2;
    }
}

Node* insert(Node* root, long long int val) {
    Node* root3, * root1;
    tie(root1, root3) = split_tree(root, val);
    Node* root2 = new Node(val);
    return merge(merge(root1, root2), root3);
}

bool find(Node* root, long long int key) {
    Node* root1, * root2;
    tie(root1, root2) = split_tree(root, key);
    Node* root_tmp, * root_ans;
    tie(root_tmp, root_ans) = split_tree(root1, key - 1);
    root = merge(merge(root_tmp, root_ans), root2);
    return root_ans;
}

Node* erase(Node* root, long long int val) {
    Node* root_tmp, * root3;
    tie(root_tmp, root3) = split_tree(root, val);
    Node* root1, * root2;
    tie(root1, root2) = split_tree(root_tmp, val - 1);
    delete root2;
    return merge(root1, root3);
}

Node* prev(Node*& root, long long int val) {
    Node* root1, * root2;
    tie(root1, root2) = split_tree(root, val - 1);
    Node* ans = root1;
    while (ans && ans->right) {
        ans = ans->right;
    }
    root = merge(root1, root2);
    return ans;
}

Node* next(Node* root, long long x) {
    Node* ans = nullptr;

    while (root != nullptr) {
        if (root->x > x) {
            ans = root;
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return ans;
}

int main() {
    freopen("bst.in", "r", stdin);
    freopen("bst.out", "w", stdout);
    string s;
    long long int n;
    Node* root = nullptr;
    while (cin >> s >> n) {
        if (s[0] == 'i') {
            //cout << 2 << '\n';
            root = insert(root, n);
        }
        else if (s[0] == 'd') {
            root = erase(root, n);
        }
        else if (s == "exists") {
            //cout << 1 << '\n';
            if (!find(root, n)) {
                cout << "false" << '\n';
            }
            else {
                cout << "true" << '\n';
            }
        }
        else if (s[0] == 'n') {
            Node* tmp = next(root, n);
            if (!tmp) {
                cout << "none" << '\n';
            }
            else {
                cout << tmp->x << '\n';
            }
        }
        else {
            Node* tmp = prev(root, n);
            if (!tmp) {
                cout << "none" << '\n';
            }
            else {
                cout << tmp->x << '\n';
            }
        }
    }
}
