# include <iostream>
# include <vector>
# include <queue>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int _data = 0, Node *_left = nullptr, Node *_right = nullptr) : data(_data), left(_left), right(_right) {}
};


class BT {
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
    BT() { root = nullptr; }

    BT(string &tree) {
        if (tree.empty() || tree.front() == 'N') {
            root = nullptr;
        } else {
            vector<string> nodes;
            string node;
            int n = (int) tree.size();
            for (int i = 0; i < n; ++i) {
                if (isspace(tree[i])) {
                    nodes.push_back(node);
                    node.clear();
                } else {
                    node.push_back(tree[i]);
                }
            }
            if (!node.empty()) nodes.push_back(node);
            root = new Node(stoi(nodes.front()));
            queue<Node *> q;
            q.push(root);
            n = (int) nodes.size();
            for (int i = 1; i < n && !q.empty(); ++i) {
                auto cur = q.front();
                q.pop();
                if (nodes[i] != "N") {
                    cur->left = new Node(stoi(nodes[i]));
                    q.push(cur->left);
                }
                i++;
                if (i >= n) break;
                if (nodes[i] != "N") {
                    cur->right = new Node(stoi(nodes[i]));
                    q.push(cur->right);
                }
            }

        }


    }

    bool empty() {
        return root == nullptr;
    }

    bool isFoldable() {
        bool flag = true;
        if (empty()) return true;
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
    cin.ignore();
    for (int i = 0; i < tests; ++i) {
        string tree;
        getline(cin, tree);
        BT bt(tree);
        cout << "Tree #" << i + 1 << (bt.isFoldable() ? ": is foldable.\n" : ": is not foldable.\n");
    }
    return 0;
}

