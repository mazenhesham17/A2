# include <iostream>
# include <vector>
# include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
                                                       right(right) {}
};

class BT {
private:
    TreeNode *root;

    bool isSameTree(TreeNode *p, TreeNode *q) {

        if (p == nullptr && q == nullptr)
            return true;
        if (p == nullptr && q != nullptr)
            return false;
        if (p != nullptr && q == nullptr)
            return false;
        if (p->val != q->val)
            return false;
        if (isSameTree(p->left, q->left) && isSameTree(p->right, q->right))
            return true;

        return false;
    }

public:
    BT() {
        root = nullptr;
    }

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
            root = new TreeNode(stoi(nodes.front()));
            queue<TreeNode *> q;
            q.push(root);
            n = (int) nodes.size();
            for (int i = 1; i < n && !q.empty(); ++i) {
                auto cur = q.front();
                q.pop();
                if (nodes[i] != "N") {
                    cur->left = new TreeNode(stoi(nodes[i]));
                    q.push(cur->left);
                }
                i++;
                if (i >= n) break;
                if (nodes[i] != "N") {
                    cur->right = new TreeNode(stoi(nodes[i]));
                    q.push(cur->right);
                }
            }

        }


    }

    bool isEmpty() {
        return root == nullptr;
    }

    bool isSameTree(BT &tree) {
        return isSameTree(root, tree.root);
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
        getline(cin, tree);
        BT bt2(tree);
        cout << "Tree #" << 2 * i + 1
             << (bt.isSameTree(bt2) ? " is same as Tree#" : " is different from Tree#") << 2 * i + 2 << ".\n";
    }
    return 0;
}
