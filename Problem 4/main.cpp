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
    bool empty;
public:
    BT() {
        root = nullptr;
        empty = true;
    }

    BT(string &tree) {
        if (tree.empty() || tree.front() == 'N') {
            empty = true;
        } else {
            empty = false;
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
        return empty;
    }

    bool isSymmetric() {
        return true;
    }

    bool isSameTree() {
        return true;
    }

};


int main() {
    // 1 2 3 N N 4 6 N 5 N N 7 N
    string s;
    getline(cin, s);
    BT bt(s);
    bt.isEmpty();
    bt.isSameTree();
    bt.isSymmetric();
    return 0;
}