#include <iostream>
#include <queue>

using namespace std;

class Stack {
private :
    queue<int> q;
public :
    Stack() {}

    bool empty() {
        return (q.empty());
    }

    void pop() {
        q.pop();
    }

    int top() {
        if (q.empty()) {
            cout << "The Stack is Empty\n";
        } else
            return q.front();
    }

    void push(int value) {
        int s = q.size();
        q.push(value);
        for (int i = 0; i < s; i++) {
            int x = q.front();
            q.pop();
            q.push(x);
        }
    }
};


int main() {
    Stack st;
    st.push(5);
    st.push(8);
    st.push(7);
    st.push(3);
    st.push(2);
    while (!st.empty()) {
        cout << st.top() << '\n';
        st.pop();
    }
    return 0;
}
