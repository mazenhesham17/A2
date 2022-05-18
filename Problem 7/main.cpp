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

    void inOrder(Node *cur) {
        if (cur == nullptr)
            return;
        inOrder(cur->left);
        cout << cur->data << ' ';
        inOrder(cur->right);
    }

    Node *mirror(Node *root) {
        // Base Case
        if (root == nullptr)
            return root;
        Node *t = root->left;
        root->left = root->right;
        root->right = t;

        if (root->left)
            mirror(root->left);
        if (root->right)
            mirror(root->right);

        return root;
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

    void inOrder() {
        inOrder(root);
    }

    Node *mirror() {
        return mirror(root);
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
        cout << "Tree #" << i + 1 << " :\n";
        cout << "In-Order Before Mirroring : ";
        bt.inOrder();
        bt.mirror();
        cout << "In-Order Before Mirroring : ";
        bt.inOrder();
        cout << '\n';
    }
    return 0;
}

