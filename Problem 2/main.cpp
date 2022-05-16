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

    ~queue() {
        while (!empty()) {
            pop();
        }
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    int tests;
    cin >> tests;
    for (int i = 0; i < tests; ++i) {
        int ticketsRow, k, timer = 1;
        cin >> ticketsRow >> k;
        queue<int> tickets, index;
        for (int j = 0; j < ticketsRow; ++j) {
            int ticketsNo;
            cin >> ticketsNo;
            tickets.push(ticketsNo);
            index.push(j);
        }
        while (tickets.getFront() != 1 || index.getFront() != k) {
            if (tickets.getFront() > 1) {
                tickets.getFront() = tickets.getFront() - 1;
                tickets.push(tickets.getFront());
                tickets.pop();
                index.push(index.getFront());
                index.pop();
            } else {
                tickets.pop();
                index.pop();
            }
            timer++;
        }
        cout << "The " << k + 1 << "-th person in Row #" << i + 1 << " will buy all the tickets after " << timer
             << " seconds.\n";
    }

    return 0;
}