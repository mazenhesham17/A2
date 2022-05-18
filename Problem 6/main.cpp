# include <iostream>
# include <vector>
# include <stack>
# include <algorithm>

using namespace std;

struct Node {
    string data;
    Node *left;
    Node *right;

    Node(string _data = "", Node *_left = nullptr, Node *_right = nullptr) : data(_data), left(_left), right(_right) {}
};


class BT {
private:
    Node *root;

    bool isOperator(string &s) {
        if (s == "+")
            return true;
        if (s == "-")
            return true;
        if (s == "*")
            return true;
        if (s == "/") {
            return true;
        }
        return false;
    }

    Node *build(vector<string> &prefix) {
        reverse(prefix.begin(), prefix.end());
        stack<Node *> stack;
        for (auto &node: prefix) {
            Node *cur = new Node(node);
            if (isOperator(node)) {
                cur->left = stack.top();
                stack.pop();
                cur->right = stack.top();
                stack.pop();
            }
            stack.push(cur);
        }
        return stack.top();
    }

    int calculate(string &s, int x, int y) {
        if (s == "+")
            return x + y;
        if (s == "-")
            return x - y;
        if (s == "*")
            return x * y;
        if (s == "/") {
            return x / y;
        }
    }

    int dfs(Node *cur) {
        if (cur == nullptr)
            return 0;
        if (cur->left == nullptr && cur->right == nullptr)
            return stoi(cur->data);
        int l = dfs(cur->left);
        int r = dfs(cur->right);
        return calculate(cur->data, l, r);
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

    BT(string &expression) {
        if (expression.empty()) {
            root = nullptr;
        } else {
            vector<string> nodes;
            string node;
            int n = (int) expression.size();
            for (int i = 0; i < n; ++i) {
                if (isspace(expression[i])) {
                    nodes.push_back(node);
                    node.clear();
                } else {
                    node.push_back(expression[i]);
                }
            }
            if (!node.empty()) nodes.push_back(node);

            root = build(nodes);
        }
    }

    bool empty() const {
        return root == nullptr;
    }

    int evaluate() {
        return dfs(root);
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
        string prefix;
        getline(cin, prefix);
        BT bt(prefix);
        cout << "Expression #" << i + 1 << " evaluated to " << bt.evaluate() << '\n';
    }
    return 0;
}