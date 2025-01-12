#include <iostream>
#include <initializer_list>
#include <string>
#include <limits>

using namespace std;

namespace containers {
    template <typename Key, typename Value>
    class Map {
    public:
        struct Node {
            Key key;
            Value value;
        private:
            Node* left;
            Node* right;

            Node(const Key& k, const Value& v) : key(k), value(v), left(nullptr), right(nullptr) {}
            friend class Map;
        };

        Map() : root(nullptr), size(0) {}

        Map(initializer_list<pair<Key, Value>> initList) : root(nullptr), size(0) {
            for (const auto& p : initList) {
                insert(p.first, p.second);
            }
        }

        Map(const Map& other) { copy(other.root); }
        Map(Map&& other) noexcept : root(other.root), size(other.size) {
            other.root = nullptr;
            other.size = 0;
        }

        Map& operator=(const Map& other) {
            if (this != &other) {
                clear();
                copy(other.root);
            }
            return *this;
        }

        Map& operator=(Map&& other) noexcept {
            if (this != &other) {
                clear();
                root = other.root;
                size = other.size;
                other.root = nullptr;
                other.size = 0;
            }
            return *this;
        }

        ~Map() { clear(); }

        void insert(const Key& key, const Value& value) {
            root = insert(root, key, value);
        }

        void remove(const Key& key) {
            root = remove(root, key);
        }

        void display() const { displayInOrder(root); }

        Value* find(const Key& key) {
            Node* node = findNode(root, key);
            return node ? &node->value : nullptr;
        }

    private:
        Node* root;
        int size;

        Node* insert(Node* node, const Key& key, const Value& value) {
            if (!node) {
                ++size;
                return new Node(key, value);
            }
            if (key < node->key) node->left = insert(node->left, key, value);
            else if (key > node->key) node->right = insert(node->right, key, value);
            else node->value = value; // обновление значения, если ключ уже существует
            return node;
        }

        Node* remove(Node* node, const Key& key) {
            if (!node) return node;
            if (key < node->key) node->left = remove(node->left, key);
            else if (key > node->key) node->right = remove(node->right, key);
            else {
                if (!node->left) return node->right;
                if (!node->right) return node->left;
                Node* temp = minValueNode(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = remove(node->right, temp->key);
            }
            return node;
        }

        Node* minValueNode(Node* node) {
            Node* current = node;
            while (current && current->left) current = current->left;
            return current;
        }

        Node* findNode(Node* node, const Key& key) const {
            if (!node || node->key == key) return node;
            if (key < node->key) return findNode(node->left, key);
            return findNode(node->right, key);
        }

        void displayInOrder(Node* node) const {
            if (!node) return;
            displayInOrder(node->left);
            cout << node->key << ": " << node->value << " ";
            displayInOrder(node->right);
        }

        void clear() { clear(root); root = nullptr; size = 0; }

        void clear(Node* node) {
            if (!node) return;
            clear(node->left);
            clear(node->right);
            delete node;
        }

        void copy(Node* node) {
            if (node) {
                insert(node->key, node->value);
                copy(node->left);
                copy(node->right);
            }
        }
    };
}


void displayMenu() {
    cout << "\n--- Меню ---\n";
    cout << "1. Добавить элемент\n";
    cout << "2. Удалить элемент\n";
    cout << "3. Показать словарь\n";
    cout << "4. Изменить тип данных\n";
    cout << "5. Выход\n";
}

template <typename Key, typename Value>
void processMap(containers::Map<Key, Value>& map) {
    int choice;
    Key key;
    Value value;

    while (true) {
        displayMenu();
        cout << "Выбор: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Только числа\n";
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Введите ключ и значение: ";
            cin >> key >> value;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Неправильный ввод.\n";
            }
            else {
                map.insert(key, value);
            }
            break;
        case 2:
            cout << "Введите ключ для удаления: ";
            cin >> key;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Неправильный ввод.\n";
            }
            else {
                map.remove(key);
            }
            break;
        case 3:
            map.display();
            cout << "\n";
            break;
        case 4:
            return;
        case 5:
            exit(0);
        default:
            cout << "Неправильный выбор.\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    int dataType;

    while (true) {
        cout << "\nВыберите тип ключа (int) и значения:\n";
        cout << "1. int\n";
        cout << "2. double\n";
        cout << "3. string\n";
        cout << "4. Выход\n";
        cout << "Ваш выбор: ";
        cin >> dataType;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Пожалуйста, введите число.\n";
            continue;
        }

        switch (dataType) {
        case 1: {
            containers::Map<int, int> map;
            processMap(map);
            break;
        }
        case 2: {
            containers::Map<int, double> map;
            processMap(map);
            break;
        }
        case 3: {
            containers::Map<int, string> map;
            processMap(map);
            break;
        }
        case 4:
            return 0;
        default:
            cout << "Выберите от 1 до 4.\n";
        }
    }
}
