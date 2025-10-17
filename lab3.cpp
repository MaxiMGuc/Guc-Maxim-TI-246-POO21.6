#include <iostream>
#include <sstream>
#include <cassert>

class MyList {
private:
    class Node {
    public:
        int value;
        Node* next;
        Node* prev;
        Node(int v) : value(v), next(nullptr), prev(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size_ = 0;

    void append_node(Node* node) {
        if (!tail) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        ++size_;
    }

public:
    // Конструкторы / деструкторы
    MyList() = default;

    explicit MyList(size_t n) {
        for (size_t i = 0; i < n; ++i) append(0);
    }

    MyList(const int arr[], size_t n) {
        for (size_t i = 0; i < n; ++i) append(arr[i]);
    }

    MyList(const MyList& other) {
        for (Node* t = other.head; t; t = t->next) append(t->value);
    }

    MyList(MyList&& other) noexcept : head(other.head), tail(other.tail), size_(other.size_) {
        other.head = other.tail = nullptr;
        other.size_ = 0;
    }

    ~MyList() { clear(); }

    // Базовые операции
    void append(int v) {
        Node* newNode = new Node(v);
        append_node(newNode);
    }

    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        ++size_;
    }

    void pop_back() {
        if (!tail) return;
        Node* prevNode = tail->prev;
        delete tail;
        tail = prevNode;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        --size_;
    }

    void clear() {
        Node* cur = head;
        while (cur) {
            Node* nx = cur->next;
            delete cur;
            cur = nx;
        }
        head = tail = nullptr;
        size_ = 0;
    }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    // Операторы присваивания
    MyList &operator=(const MyList& rhs) {
        if (this == &rhs) return *this;
        MyList tmp(rhs);
        swap(tmp);
        return *this;
    }

    MyList &operator=(MyList&& rhs) noexcept {
        if (this == &rhs) return *this;
        clear();
        head = rhs.head;
        tail = rhs.tail;
        size_ = rhs.size_;
        rhs.head = rhs.tail = nullptr;
        rhs.size_ = 0;
        return *this;
    }

    // --- Доступ по индексу ---
    int &operator[](size_t pos) {
        Node* cur = head;
        for (size_t i = 0; i < pos; ++i) cur = cur->next;
        return cur->value;
    }

    const int &operator[](size_t pos) const {
        Node* cur = head;
        for (size_t i = 0; i < pos; ++i) cur = cur->next;
        return cur->value;
    }

    // --- Методы подсчёта и поиска ---
    size_t count(int v) const {
        size_t c = 0;
        for (Node* t = head; t; t = t->next) if (t->value == v) ++c;
        return c;
    }

    bool contains(int v) const {
        for (Node* t = head; t; t = t->next) if (t->value == v) return true;
        return false;
    }

    // --- Вспомогательная функция swap ---
    void swap(MyList& other) noexcept {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size_, other.size_);
    }

    // --- Операторы сравнения ---
    friend bool operator==(const MyList& a, const MyList& b) {
        if (a.size_ != b.size_) return false;
        Node* t1 = a.head;
        Node* t2 = b.head;
        while (t1 && t2) {
            if (t1->value != t2->value) return false;
            t1 = t1->next;
            t2 = t2->next;
        }
        return true;
    }

    friend bool operator!=(const MyList& a, const MyList& b) { return !(a == b); }

    friend bool operator<(const MyList& a, const MyList& b) {
        Node* t1 = a.head;
        Node* t2 = b.head;
        while (t1 && t2) {
            if (t1->value < t2->value) return true;
            if (t1->value > t2->value) return false;
            t1 = t1->next;
            t2 = t2->next;
        }
        if (!t1 && t2) return true;
        return false;
    }

    friend bool operator>(const MyList& a, const MyList& b) { return b < a; }
    friend bool operator<=(const MyList& a, const MyList& b) { return !(b < a); }
    friend bool operator>=(const MyList& a, const MyList& b) { return !(a < b); }

    // --- Ввод/вывод ---
    friend std::ostream &operator<<(std::ostream& os, const MyList& lst) {
        Node* cur = lst.head;
        bool first = true;
        while (cur) {
            if (!first) os << ' ';
            os << cur->value;
            first = false;
            cur = cur->next;
        }
        os << '\n';
        return os;
    }

    friend std::istream &operator>>(std::istream& is, MyList& lst) {
        if (lst.size_ > 0) {
            for (size_t i = 0; i < lst.size_; ++i) {
                int v;
                if (!(is >> v)) break;
                Node* cur = lst.head;
                for (size_t j = 0; j < i; ++j) cur = cur->next;
                cur->value = v;
            }
        } else {
            int v;
            while (is >> v) lst.append(v);
        }
        return is;
    }
};

// --- Тестирование ---
int main() {
    std::stringstream ss{"1 3 5 7 9"};
    MyList a(5);
    ss >> a;
    assert(5 == a.size());
    assert(1 == a[0]);
    assert(9 == a[4]);
    std::cout << a;
    MyList b{a};
    assert(a == b);
    assert(3 == b[1]);
    assert(7 == b[3]);
    b[4] = 0;
    assert(0 == b[4]);
    assert(!b.contains(9));
    assert(b < a);
    assert(a > b);
    std::cout << b;
    MyList c;
    assert(0 == c.size());
    c = b;
    assert(b == c);
    c[1] = c[2] = 7;
    assert(7 == c[1]);
    assert(7 == c[2]);
    assert(3 == c.count(7));
    std::cout << c;
    int arr[] = {1,3,5,7,9};
    b = MyList(arr,5);
    assert(5 == b.size());
    assert(1 == b[0]);
    assert(9 == b[4]);
    c = std::move(b);
    assert(9 == c[4]);
    assert(c.contains(7));
    assert(b.empty());
    assert(b < c);
}
