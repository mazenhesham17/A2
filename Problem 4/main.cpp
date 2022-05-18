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

    void clear(TreeNode *cur) {
        if (cur == nullptr) {
            return;
        }
        clear(cur->left);
        clear(cur->right);
        delete cur;
        cur = nullptr;
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

    bool isSymmetric() {
        if (root == nullptr || check(root->left, root->right))
            return true;
    }

    bool check(TreeNode *subleft, TreeNode *subright) {
        if (!subleft && !subright)
            return true;
        else if (subleft != nullptr && subright != nullptr)
            return (subright->val == subleft->val && check(subleft->left, subright->right) &&
                    check(subleft->right, subright->left));
        return false;
    }

    ~BT() {
        clear(root);
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
        cout << "Tree #" << i + 1 << (bt.isSymmetric() ? ": is symmetric.\n" : ": is not symmetric.\n");
    }
    return 0;
}