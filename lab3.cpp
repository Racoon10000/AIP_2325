main
#include <iostream>
#include <string>
#include "Deque.h"
#include "Exceptions.h"

using namespace std;

template<typename T>
void testDeque() {
    Deque<T> deque;

    int choice;
    T value;

    while (true) {
        cout << "\nМеню:\n"
            << "1. Добавить в начало (push_front)\n"
            << "2. Добавить в конец (push_back)\n"
            << "3. Удалить с начала (pop_front)\n"
            << "4. Удалить с конца (pop_back)\n"
            << "5. Показать первый элемент (front)\n"
            << "6. Показать последний элемент (back)\n"
            << "7. Проверить пустоту (empty)\n"
            << "8. Показать размер (size)\n"
            << "9. Очистить (clear)\n"
            << "0. Выйти\n"
            << "Выбор: ";
        cin >> choice;

        try {
            switch (choice) {
            case 1:
                cout << "Введите значение: ";
                cin >> value;
                deque.push_front(value);
                cout << "Добавлено в начало.\n";
                break;

            case 2:
                cout << "Введите значение: ";
                cin >> value;
                deque.push_back(value);
                cout << "Добавлено в конец.\n";
                break;

            case 3:
                deque.pop_front();
                cout << "Удалено с начала.\n";
                break;

            case 4:
                deque.pop_back();
                cout << "Удалено с конца.\n";
                break;

            case 5:
                cout << "Первый элемент: " << deque.front() << "\n";
                break;

            case 6:
                cout << "Последний элемент: " << deque.back() << "\n";
                break;

            case 7:
                cout << (deque.empty() ? "Deque пуст." : "Deque не пуст.") << "\n";
                break;

            case 8:
                cout << "Размер Deque: " << deque.size() << "\n";
                break;

            case 9:
                deque.clear();
                cout << "Deque очищен.\n";
                break;

            case 0:
                return;

            default:
                cout << "Некорректный выбор!\n";
                break;
            }
        }
        catch (const DequeException& e) {
            cerr << "Ошибка: " << e.what() << "\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    int choice;

    while (true) {
        cout << "\nВыберите тип данных для тестирования:\n"
            << "1. int\n"
            << "2. double\n"
            << "3. std::string\n"
            << "0. Выйти\n"
            << "Выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            testDeque<int>();
            break;
        case 2:
            testDeque<double>();
            break;
        case 3:
            testDeque<string>();
            break;
        case 0:
            cout << "Выход из программы.\n";
            return 0;
        default:
            cout << "Некорректный выбор!\n";
            break;
        }
    }
}

Deque
#ifndef DEQUE_H
#define DEQUE_H

#include <initializer_list>
#include <stdexcept>
#include "List.h"

using namespace std;

template<typename T>
class Deque {
private:
    List<T> list;  

public:
    Deque() = default;

    Deque(initializer_list<T> init) {
        for (const auto& item : init) {
            push_back(item);
        }
    }

    Deque(const Deque& other) : list(other.list) {}

    Deque& operator=(const Deque& other) {
        if (this != &other) {
            list = other.list;
        }
        return *this;
    }

    Deque(Deque&& other) noexcept : list(move(other.list)) {}

    Deque& operator=(Deque&& other) noexcept {
        if (this != &other) {
            list = move(other.list);
        }
        return *this;
    }

    void push_front(const T& value) { list.push_front(value); }
    void push_back(const T& value) { list.push_back(value); }

    void pop_front() { list.pop_front(); }
    void pop_back() { list.pop_back(); }

    T& front() { return list.front(); }
    T& back() { return list.back(); }
    const T& front() const { return list.front(); }
    const T& back() const { return list.back(); }

    bool empty() const { return list.empty(); }
    size_t size() const { return list.size(); }

    void clear() { list.clear(); }
};

#endif 

List
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        Node(const T& val, Node* p = nullptr, Node* n = nullptr)
            : value(val), prev(p), next(n) {}
    };

    Node* head;   
    Node* tail;   
    size_t count; 

    void clearList() {
        while (!empty()) {
            pop_front();
        }
    }

public:
    List() : head(nullptr), tail(nullptr), count(0) {}

    ~List() { clearList(); }

    List(const List& other) : head(nullptr), tail(nullptr), count(0) {
        for (Node* cur = other.head; cur != nullptr; cur = cur->next) {
            push_back(cur->value);
        }
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clearList();
            for (Node* cur = other.head; cur != nullptr; cur = cur->next) {
                push_back(cur->value);
            }
        }
        return *this;
    }

    List(List&& other) noexcept : head(other.head), tail(other.tail), count(other.count) {
        other.head = other.tail = nullptr;
        other.count = 0;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clearList();
            head = other.head;
            tail = other.tail;
            count = other.count;

            other.head = other.tail = nullptr;
            other.count = 0;
        }
        return *this;
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value, nullptr, head);
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = head;
        ++count;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value, tail, nullptr);
        if (tail) tail->next = newNode;
        tail = newNode;
        if (!head) head = tail;
        ++count;
    }

    void pop_front() {
        if (empty()) throw out_of_range("List is empty");
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        --count;
    }

    void pop_back() {
        if (empty()) throw out_of_range("List is empty");
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        --count;
    }

    T& front() {
        if (empty()) throw out_of_range("List is empty");
        return head->value;
    }

    const T& front() const {
        if (empty()) throw out_of_range("List is empty");
        return head->value;
    }

    T& back() {
        if (empty()) throw out_of_range("List is empty");
        return tail->value;
    }

    const T& back() const {
        if (empty()) throw out_of_range("List is empty");
        return tail->value;
    }

    bool empty() const { return count == 0; }

    size_t size() const { return count; }

    void clear() { clearList(); }
};

#endif 

SmartPointer
#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <iostream>

template<typename T>
class SmartPointer {
private:
    T* ptr;              
    size_t* ref_count;   

    void release() {
        if (ref_count && --(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
    }

public:
    SmartPointer(T* p = nullptr) : ptr(p), ref_count(new size_t(1)) {}

    SmartPointer(const SmartPointer& other)
        : ptr(other.ptr), ref_count(other.ref_count) {
        ++(*ref_count);
    }

    SmartPointer& operator=(const SmartPointer& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);
        }
        return *this;
    }

    SmartPointer(SmartPointer&& other) noexcept
        : ptr(other.ptr), ref_count(other.ref_count) {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    SmartPointer& operator=(SmartPointer&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    ~SmartPointer() { release(); }

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    bool isNull() const { return ptr == nullptr; }
};

#endif 

Exceptions
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include <iostream>

using namespace std;

class DequeException : public exception {
protected:
    string message;

public:
    explicit DequeException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class DequeEmptyException : public DequeException {
public:
    DequeEmptyException() : DequeException("Deque пуст.") {}
};

class OutOfBoundsException : public DequeException {
public:
    OutOfBoundsException(size_t index, size_t size)
        : DequeException("Индекс " + to_string(index) + " вне диапазона (размер: " + to_string(size) + ")") {}
};

class MemoryAllocationException : public DequeException {
public:
    MemoryAllocationException() : DequeException("Ошибка выделения памяти") {}
};

#endif 
