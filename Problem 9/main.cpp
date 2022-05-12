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
        if (root->left == nullptr ^ root->right == nullptr)
            return false;
        if (root->left == nullptr && root->right == nullptr)
            return true;
        dfs(root->left, root->right, flag);
        return flag;
    }
};

int main() {
    BST bst;
    // 5 3 4 7 6
    // 3 2 1 4 5
    bst.insert(3);
    bst.insert(2);
    bst.insert(1);
    bst.insert(4);
    bst.insert(5);
    cout << bst.isFoldable() << '\n';
    return 0;
}