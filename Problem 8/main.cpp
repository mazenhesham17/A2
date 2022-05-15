# include <iostream>
# include <vector>
# include <queue>

using namespace std;


struct Node {
    char data;
    Node *left;
    Node *right;

    Node(char _data = '0', Node *_left = nullptr, Node *_right = nullptr) : data(_data), left(_left), right(_right) {}
};


class BT {
private:
    Node *root;

    // pre -> V L R
    // in -> L V R
    Node *build(string preorder, string inorder) {
        if (preorder.empty()) return nullptr;
        Node *cur = new Node(preorder.front());
        int n = (int) inorder.size();
        for (int i = 0; i < n; ++i) {
            if (preorder.front() == inorder[i]) {
                cur->left = build(preorder.substr(1, i), inorder.substr(0, i));
                cur->right = build(preorder.substr(i + 1), inorder.substr(i + 1));
                break;
            }
        }
        return cur;
    }

    void dfs(Node *cur, string &s) {
        if (cur == nullptr) return;
        dfs(cur->left, s);
        dfs(cur->right, s);
        s.push_back(cur->data);
    }

public:
    BT() { root = nullptr; }

    bool empty() {
        return root == nullptr;
    }

    BT(string &preorder, string &inorder) {
        root = build(preorder, inorder);
    }

    string postOrder() {
        string tree;
        dfs(root, tree);
        return tree;
    }

};

int main() {
    freopen("input.txt", "r", stdin);
    int tests;
    cin >> tests;
    for (int i = 0; i < tests; ++i) {
        string preorder, inorder;
        cin >> preorder >> inorder;
        BT bt(preorder, inorder);
        cout << "Tree#" << i + 1 << ":\n";
        cout << "Pre-Order : " << preorder << " In-Order : " << inorder << " Post-Order : " << bt.postOrder() << '\n';
    }
    return 0;
}