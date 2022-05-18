# include <iostream>

using namespace std;

template<class T>
class Stack {
private:
    T *arr;
    int last;
    int capacity;

    void initialize() {
        last = -1;
        arr = new T[capacity];
    }

public:
    Stack() {
        capacity = 10;
        initialize();
    }

    Stack(const T value, int size) {
        capacity = size;
        initialize();
        for (int i = 0; i < size; ++i) {
            arr[++last] = value;
        }
    }

    bool empty() const {
        return last == -1;
    }

    T &top() {
        return arr[last];
    }

    T &pop() {
        return arr[last--];
    }

    void push(const T &element) {
        if (last == capacity - 1) {
            capacity *= 2;
            T *temp = new T[capacity];
            for (int i = 0; i < size(); ++i) {
                temp[i] = arr[i];
            }
            delete arr;
            arr = temp;
        }
        arr[++last] = element;
    }

    int size() const {
        return last + 1;
    }

    ~Stack() {
        delete[] arr;
        arr = nullptr;
    }
};


string transfer(string &path) {
    string simplify = "/", file;
    Stack<string> st;
    int n = (int) path.size(), dot = 0;
    for (int i = 0; i < n; ++i) {
        if (path[i] == '/') {
            if (file.empty()) continue;
            if (file == "..") {
                if (!st.empty()) st.pop();
            } else {
                if (file != ".")
                    st.push(file);
            }
            file.clear();
        } else if (path[i] == '.') {
            while (i < n && path[i] == '.')
                dot++, i++;
            if (dot) i--;
            while (dot--) {
                file.push_back('.');
            }
            dot = 0;
        } else {
            file.push_back(path[i]);
        }
    }
    if (!file.empty()) {
        if (file == "..") {
            if (!st.empty()) st.pop();
        } else {
            if (file != ".")
                st.push(file);
        }
    }
    Stack<string> temp;
    while (!st.empty()) {
        string cur = st.top();
        st.pop();
        temp.push(cur);
    }
    while (!temp.empty()) {
        string cur = temp.top();
        temp.pop();
        simplify += cur;
        if (!temp.empty()) {
            simplify.push_back('/');
        }
    }
    return simplify;
}

int main() {
    freopen("input.txt","r",stdin) ;
    int tests;
    cin >> tests;
    for (int i = 0; i < tests; ++i) {
        string absolute;
        cin >> absolute;
        cout << "Test case #" << i + 1 << ":\n";
        cout << "absolute path : " << absolute << '\n';
        cout << "canonical path : " << transfer(absolute) << "\n\n";
    }
    return 0;
}