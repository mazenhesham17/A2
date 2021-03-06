#include <iostream>

using namespace std;

template<class T>
struct Node {
    T data;
    Node *next;

    Node(T _data = T(), Node<T> *_next = nullptr) : data(_data), next(_next) {}
};

template<class T>
class queue {
private:
    Node<T> *front;
    Node<T> *rear;
    int size;
public:
    queue() {
        size = 0;
        front = rear = nullptr;
    }

    bool empty() {
        return front == nullptr;
    }

    void push(T &item) {
        Node<T> *cur = new Node<T>(item);
        if (empty())
            front = rear = cur;
        else {
            rear->next = cur;
            rear = cur;
        }
        size++;
    }


    void pop() {
        if (empty())
            cout << "The queue is empty \n";
        else if (front == rear) {
            delete front;
            front = rear = nullptr;
            size--;
        } else {
            Node<T> *cur = front;
            front = front->next;
            delete cur;
            size--;
        }
    }

    T &getFront() {
        return front->data;
    }

    int getSize() {
        return size;
    }

    ~queue() {
        while (!empty()) {
            pop();
        }
    }
};

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
            return q.getFront();
    }

    void push(int value) {
        int s = q.getSize();
        q.push(value);
        for (int i = 0; i < s; i++) {
            int x = q.getFront();
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
