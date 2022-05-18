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

    void balance(Node *cur, int &mn, int &mx, int d) {
        if (cur == nullptr) return;
        balance(cur->left, mn, mx, d + 1);
        balance(cur->right, mn, mx, d + 1);
        if (cur->left == nullptr || cur->right == nullptr) {
            mn = min(mn, d);
            mx = max(mx, d);
        }
    }

    Node *search(Node *cur, int value) {
        if (cur == nullptr) return nullptr;
        if (cur->data < value) return search(cur->right, value);
        else if (cur->data > value) return search(cur->left, value);
        else return cur;
    }

    void isSame(Node *first, Node *second, bool &flag) {
        if (first == nullptr && second == nullptr) return;
        if (first == nullptr || second == nullptr) {
            flag = false;
            return;
        }
        if (first->data != second->data) {
            flag = false;
            return;
        }
        isSame(first->left, second->left, flag);
        isSame(first->right, second->right, flag);
    }

    void range(Node *cur, int l, int r) {
        if (cur == nullptr) return;
        if (cur->data > l)
            range(cur->left, l, r);
        if (cur->data <= r && cur->data >= l)
            cout << cur->data << ' ';
        if (cur->data < r)
            range(cur->right, l, r);
    }

    void clear(Node *cur) {
        if (cur == nullptr) {
            return;
        }
        clear(cur->left);
        clear(cur->right);
        delete cur;
        cur = nullptr;
    }

public:
    BST() { root = nullptr; }

    void insert(int value) {
        insert(root, value);
    }

    void inorder() {
        dfs(root);
    }

    bool isBalanced() {
        int mn = 1000, mx = -1;
        balance(root, mn, mx, 0);
        return (mx - mn <= 1);
    }

    Node *search(int value) {
        return search(root, value);
    }

    bool isSubtree(BST &tree) {
        auto cur = search(tree.root->data);
        if (cur == nullptr) return false;
        bool flag = true;
        isSame(cur, tree.root, flag);
        return flag;
    }

    void printRange(int l, int r) {
        range(root, l, r);
        cout << '\n';
    }

    bool empty() {
        return root == nullptr;
    }

    ~BST() {
        clear(root);
    }

};

bool isSubtree(BST &first, BST &second) {
    if (first.empty() || second.empty()) return true;
    return first.isSubtree(second);
}

int main() {
    freopen("input.txt", "r", stdin);
    int tests;
    cin >> tests;
    cout << "Check Balance : \n";
    for (int i = 0; i < tests; ++i) {
        int size;
        cin >> size;
        BST bst;
        for (int j = 0; j < size; ++j) {
            int value;
            cin >> value;
            bst.insert(value);
        }
        cout << "Tree #" << i + 1 << (bst.isBalanced() ? ": is balanced.\n" : ": is unbalanced.\n");
    }
    cout << "\nCheck SubTree : \n";
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
        cin >> size;
        BST bst2;
        for (int j = 0; j < size; ++j) {
            int value;
            cin >> value;
            bst2.insert(value);
        }
        cout << "Tree #" << 2 * i + 2
             << (isSubtree(bst, bst2) ? " is a subtree of Tree#" : " is not a subtree of Tree#") << 2 * i + 1 << ".\n";
    }
    cout << "\nPrint Range :\n";
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
        int queries;
        cin >> queries;
        cout << "Tree #" << i + 1 << " :\n";
        for (int j = 0; j < queries; ++j) {
            int l, r;
            cin >> l >> r;
            cout << "Numbers in range [" << l << ',' << r << "] ";
            bst.printRange(l, r);
        }
    }
    return 0;
}