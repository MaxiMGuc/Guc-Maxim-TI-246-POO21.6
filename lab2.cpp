
#include <iostream>
#include <cassert>
//using namespace std;

class Node {
public:
    int value;
    Node* next;
    Node* prev;
    Node(int v) : value(v), next(nullptr), prev(nullptr) {}
};

class Deque {
private:
    Node* head;
    Node* tail;
    size_t size_;

public:
    // Конструктор по умолчанию
    Deque() : head(nullptr), tail(nullptr), size_(0) {}

    // Конструктор с массивом
    Deque(const int arr[], size_t n) : head(nullptr), tail(nullptr), size_(0) {
        for (size_t i = 0; i < n; ++i) append(arr[i]);
    }

    // Конструктор копирования (deep copy)
    Deque(const Deque& other) : head(nullptr), tail(nullptr), size_(0) {
        Node* temp = other.head;
        while (temp) {
            append(temp->value);
            temp = temp->next;
        }
    }

    // Конструктор перемещения
    Deque(Deque&& other) noexcept : head(other.head), tail(other.tail), size_(other.size_) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0;
    }

    // Деструктор
    ~Deque() { clear(); }

    // Добавление элемента в конец
    void append(int v) {
        Node* newNode = new Node(v);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++size_;
    }

    // Очистка
    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size_ = 0;
    }

    // Доступ к элементу
    int at(int idx) {
        if (size_ == 0) throw std::out_of_range("Deque is empty");

        if (idx < 0) idx = static_cast<int>(size_) + idx;
        if (idx < 0) idx = 0;
        if (static_cast<size_t>(idx) >= size_) idx = size_ - 1;

        Node* temp = head;
        for (int i = 0; i < idx; ++i) temp = temp->next;
        return temp->value;
    }

    // Размер
    size_t size() const { return size_; }

    // Проверка на пустоту
    bool empty() const { return size_ == 0; }

    // Swap
    void swap(Deque& other) {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size_, other.size_);
    }

    // Статическая проверка на равенство
    static bool is_equal(const Deque& a, const Deque& b) {
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

    // Метод добавления элемента в начало
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

    // Метод удаления элемента с конца
    void pop_back() {
        if (!tail) return;
        Node* prevNode = tail->prev;
        delete tail;
        tail = prevNode;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        --size_;
    }
};

// Тестирование
int main() {
    int arr[] = {1, 4, 7, 9};
    Deque a(arr, 4);
    assert(a.size() == 4);
    assert(a.at(0) == 1);
    assert(a.at(10) == 9);

    Deque b(a); // копия
    assert(Deque::is_equal(a, b));

    b.clear();
    assert(b.empty());

    Deque c;
    assert(c.empty());
    c.push_front(5);
    assert(c.at(0) == 5);

    Deque d(std::move(a));
    assert(d.size() == 4);
    assert(a.empty());

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
