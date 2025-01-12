main


#include "PositiveNegativeIterators.h"
#include "CustomException.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

void displayMenu() {
    cout << "\n--- Menu ---\n";
    cout << "1. Add element\n";
    cout << "2. Display positive elements\n";
    cout << "3. Display negative elements\n";
    cout << "4. Exit\n";
}

template <typename T>
void displayIterator(Iterator<T>& iterator) {
    try {
        while (iterator.hasNext()) {
            cout << iterator.current() << " ";
            iterator.next();
        }
        cout << endl;
    }
    catch (const CustomException& ex) {
        cerr << "Error: " << ex.what() << endl;
    }
}

template <typename T>
void processCollection() {
    vector<T> collection;
    int choice;
    T value;

    while (true) {
        displayMenu();
        cout << "Choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        try {
            switch (choice) {
            case 1:
                cout << "Enter value to add: ";
                cin >> value;
                collection.push_back(value);
                break;
            case 2: {
                PositiveIterator<T> posIt(collection);
                cout << "Positive elements: ";
                displayIterator(posIt);
                break;
            }
            case 3: {
                NegativeIterator<T> negIt(collection);
                cout << "Negative elements: ";
                displayIterator(negIt);
                break;
            }
            case 4:
                return;
            default:
                cout << "Invalid choice.\n";
            }
        }
        catch (const CustomException& ex) {
            cerr << "Error: " << ex.what() << endl;
        }
    }
}

int main() {
    int dataType;

    while (true) {
        cout << "\nSelect data type:\n";
        cout << "1. int\n";
        cout << "2. double\n";
        cout << "3. string\n";
        cout << "4. Exit\n";
        cout << "Your choice: ";
        cin >> dataType;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (dataType) {
        case 1:
            processCollection<int>();
            break;
        case 2:
            processCollection<double>();
            break;
        case 3:
            processCollection<string>();
            break;
        case 4:
            return 0;
        default:
            cout << "Choose between 1 and 4.\n";
        }
    }
}







CustomException.h


#ifndef CUSTOM_EXCEPTION_H
#define CUSTOM_EXCEPTION_H

#include <exception>
#include <string>

class CustomException : public std::exception {
private:
    std::string message;

public:
    explicit CustomException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // CUSTOM_EXCEPTION_H








Iterator.h


#ifndef ITERATOR_H
#define ITERATOR_H

template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;

    virtual void next() = 0;
    virtual bool hasNext() const = 0;
    virtual T current() const = 0;
};

#endif // ITERATOR_H

















PositiveNegativeIterators.h


#ifndef POSITIVE_NEGATIVE_ITERATORS_H
#define POSITIVE_NEGATIVE_ITERATORS_H

#include "Iterator.h"
#include "CustomException.h"
#include <vector>
#include <type_traits>

template <typename T>
class PositiveIterator : public Iterator<T> {
private:
    const std::vector<T>& collection;
    size_t currentIndex;

    bool isPositive(const T& value) const {
        if constexpr (std::is_arithmetic<T>::value) {
            return value > 0;
        }
        else if constexpr (std::is_same<T, std::string>::value) {
            return !value.empty();
        }
        return false;
    }

public:
    PositiveIterator(const std::vector<T>& collection)
        : collection(collection), currentIndex(0) {
        while (currentIndex < collection.size() && !isPositive(collection[currentIndex])) {
            ++currentIndex;
        }
    }

    void next() override {
        if (!hasNext()) {
            throw CustomException("No more positive elements.");
        }
        do {
            ++currentIndex;
        } while (currentIndex < collection.size() && !isPositive(collection[currentIndex]));
    }

    bool hasNext() const override {
        return currentIndex < collection.size();
    }

    T current() const override {
        if (!hasNext()) {
            throw CustomException("No current positive element.");
        }
        return collection[currentIndex];
    }
};

template <typename T>
class NegativeIterator : public Iterator<T> {
private:
    const std::vector<T>& collection;
    size_t currentIndex;

    bool isNegative(const T& value) const {
        if constexpr (std::is_arithmetic<T>::value) {
            return value < 0;
        }
        else if constexpr (std::is_same<T, std::string>::value) {
            return value.empty();
        }
        return false;
    }

public:
    NegativeIterator(const std::vector<T>& collection)
        : collection(collection), currentIndex(0) {
        while (currentIndex < collection.size() && !isNegative(collection[currentIndex])) {
            ++currentIndex;
        }
    }

    void next() override {
        if (!hasNext()) {
            throw CustomException("No more negative elements.");
        }
        do {
            ++currentIndex;
        } while (currentIndex < collection.size() && !isNegative(collection[currentIndex]));
    }

    bool hasNext() const override {
        return currentIndex < collection.size();
    }

    T current() const override {
        if (!hasNext()) {
            throw CustomException("No current negative element.");
        }
        return collection[currentIndex];
    }
};

#endif // POSITIVE_NEGATIVE_ITERATORS_H
