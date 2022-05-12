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

    void dfs(Node *cur) {
        if (cur == nullptr) return;
        dfs(cur->left);
        cout << cur->data << '\n';
        dfs(cur->right);
    }

    void DFS(Node *cur, int &k, int &ans) {
        if (cur == nullptr) return;
        DFS(cur->left, k, ans);
        if (k) ans += cur->data, k--;
        DFS(cur->right, k, ans);
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

    void inorder() {
        dfs(root);
    }

    int kth(int k) {
        int ans = 0;
        DFS(root, k, ans);
        return ans;
    }

};

int main() {
    freopen("input.txt", "r", stdin);
    int tests;
    cin >> tests;
    for (int i = 0; i < tests; ++i) {
        int size, k;
        cin >> size >> k;
        BST bst;
        for (int j = 0; j < size; ++j) {
            int value;
            cin >> value;
            bst.insert(value);
        }
        cout << "The summation of the " << k << "-th smallest elements is " << bst.kth(k) << ".\n";
    }
    return 0;
}