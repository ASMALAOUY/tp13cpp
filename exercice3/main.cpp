#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
using namespace std;

template<typename T>
class Stack {
private:
    unique_ptr<T[]> data;
    size_t capacity;
    size_t topIndex;

public:
    class StackOverflow : public runtime_error {
    public:
        StackOverflow() : runtime_error("Erreur : Depassement de capacite (StackOverflow)") {}
    };

    class StackUnderflow : public runtime_error {
    public:
        StackUnderflow() : runtime_error("Erreur : Pile vide (StackUnderflow)") {}
    };

    Stack(size_t cap = 10)
        : data(make_unique<T[]>(cap)), capacity(cap), topIndex(0) {}

    template<typename It>
    Stack(It begin, It end)
        : data(make_unique<T[]>(distance(begin, end))),
          capacity(distance(begin, end)), topIndex(0)
    {
        for (auto it = begin; it != end; ++it)
            data[topIndex++] = *it;
    }

    void push(const T& value) {
        if (topIndex >= capacity)
            throw StackOverflow();
        data[topIndex++] = value;
    }

    void pop() {
        if (empty())
            throw StackUnderflow();
        --topIndex;
    }

    const T& peek() const {
        if (empty())
            throw StackUnderflow();
        return data[topIndex - 1];
    }

    bool empty() const { return topIndex == 0; }
    size_t size() const { return topIndex; }
    size_t max_size() const { return capacity; }
};

int main() {
    try {
        Stack<int> s(5);
        s.push(10);
        s.push(20);
        s.push(30);
        cout << "Sommet : " << s.peek() << endl;
        s.pop();
        cout << "Après pop, sommet : " << s.peek() << endl;

        vector<int> v = {1, 2, 3, 4};
        Stack<int> s2(v.begin(), v.end());
        cout << "Pile s2 construite depuis vecteur (taille = " << s2.size() << ")" << endl;
        while (!s2.empty()) {
            cout << s2.peek() << " ";
            s2.pop();
        }
        cout << endl;

        Stack<int> s3(2);
        s3.push(1);
        s3.push(2);
        s3.push(3);

    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
