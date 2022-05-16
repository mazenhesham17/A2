#include <iostream>
#include <string>

using namespace std;

class express {
public:
    string info;
    express *left = NULL, *right = NULL;

    express(string come) {
        info = come;
    }

private:
    int transToIntegr(string x);

    int evaluationNode(express *root);
};

int transToIntegr(string x) {
    int num = 0;
    if (x[0] != '-')
        for (int i = 0; i < x.length(); i++)
            num = num * 10 + (int(x[i]) - 48);
    else {
        for (int i = 1; i < x.length(); i++)
            num = num * 10 + (int(x[i]) - 48);
        num = num * -1;
    }
    return num;
}

int evaluationNode(express *root) {
    if (!root)
        return 0;

    if (!root->left && !root->right)
        return transToIntegr(root->info);

    int left = evaluationNode(root->left);
    int right = evaluationNode(root->right);

    if (root->info == "+")
        return left + right;

    if (root->info == "-")
        return left - right;

    if (root->info == "*")
        return left * right;

    return left / right;
}

int main() {
    express *root1 = new express("+");
    root1->left = new express("5");
    root1->right = new express("-");
    root1->right->left = new express("12");
    root1->right->right = new express("*");
    root1->right->right->left = new express("3");
    root1->right->right->right = new express("2");
    cout << evaluationNode(root1) << endl;
    express *root2 = new express("*");
    root2->left = new express("+");
    root2->right = new express("/");
    root2->left->left = new express("3");
    root2->left->right = new express("2");
    root2->right->left = new express("12");
    root2->right->right = new express("-");
    root2->right->right->left = new express("9");
    root2->right->right->right = new express("3");
    cout << evaluationNode(root2) << endl;
    return 0;
}
