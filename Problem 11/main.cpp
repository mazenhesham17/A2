# include <iostream>

using namespace std ;


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

    void insert(Node *&node, int value) {
        if (node == nullptr) {
            node = new Node(value);
        } else {
            if (value < node->data)
                insert(node->left, value);
            else
                insert(node->right, value);
        }
    }

public:
    BST() { root = nullptr; }

    void insert(int value) {
        insert(root, value);
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

int main(){

    return 0 ;
}