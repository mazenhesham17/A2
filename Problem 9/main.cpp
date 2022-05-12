# include <iostream>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int _data = 0, Node *_left = nullptr, Node *_right = nullptr) : data(_data), left(_left), right(_right) {}
};

class BST {
private:
    Node *root;

    void dfs(Node *left, Node *right, bool &flag) {
        if (left == nullptr || right == nullptr) return;
        if (left->right == nullptr ^ right->left == nullptr) flag = false;
        if (left->left == nullptr ^ right->right == nullptr) flag = false;
        dfs(left->left, right->right, flag);
        dfs(right->left, left->right, flag);
    }

public:
    BST() { root = nullptr; }

    void insert(int value) {
        Node *node = new Node(value);
        Node *cur, *prev;
        if (root == nullptr) root = node;
        else {
            cur = root;
            while (cur != nullptr) {
                prev = cur;
                if (cur->data == value) return;
                if (cur->data > value) cur = cur->left;
                else cur = cur->right;
            }
            if (prev->data > value)
                prev->left = node;
            else
                prev->right = node;
        }
    }

    bool isFoldable() {
        bool flag = true;
        if (root == nullptr) return true;
        if (root->left == nullptr ^ root->right == nullptr) return false;
        if (root->left == nullptr && root->right == nullptr) return true;
        dfs(root->left, root->right, flag);
        return flag;
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    int tests;
    cin >> tests;
    for (int i = 0; i < tests; ++i) {
        int size;
        cin >> size;
        BST bst;
        for (int j = 0; j < size; ++j) {
            int value;
            cin >> value;
            bst.insert(value);
        }
        cout << "Tree #" << i + 1 << (bst.isFoldable() ? ": is foldable.\n" : ": is not foldable.\n");
    }
    return 0;
}

