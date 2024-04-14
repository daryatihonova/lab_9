#include <iostream>
#include "App.h"
using namespace std;

class BinaryTree {
private:
    struct Node {
        App app;        // Структура узла содержит объект типа App
        Node* left;     // Указатель на левый дочерний узел
        Node* right;    // Указатель на правый дочерний узел
    };
    Node* root; // Указатель на корневой узел дерева


public:
    BinaryTree();
    ~BinaryTree();

    void addElement(const App& app);  // Метод добавления элемента в дерево
    void removeElement(int diskSize, const string& name);  // Метод удаления элемента из дерева
    bool elementExists(int diskSize, const string& name);  // Метод проверки наличия элемента в дереве
    void getAllElements(Node* node, App* arr, int& index);  // Метод получения всех элементов дерева
    void getAllDescriptions(App* arr, int& size);  // Метод получения всех описаний элементов дерева

};

BinaryTree::BinaryTree() {
    root = nullptr;// Инициализация корня дерева как пустого узла
}

BinaryTree::~BinaryTree() {}

void BinaryTree::addElement(const App& app) {
    Node* newNode = new Node{ app, nullptr, nullptr };// Создание нового узла с переданным объектом

    if (root == nullptr) {
        root = newNode;// Если дерево пустое, новый узел становится корневым
    }
    else {
        Node* current = root; // Указатель на текущий узел, начиная с корня
        while (true) {
            if ((app.diskSize < current->app.diskSize)
                || (app.diskSize == current->app.diskSize && app.name < current->app.name)) {

                if (current->left == nullptr) {
                    current->left = newNode;// Если нет левого дочернего узла, новый узел становится левым дочерним
                    break;
                }
                else {
                    current = current->left;// Переход к левому дочернему узлу
                }
            }
            else {
                if (current->right == nullptr) {
                    current->right = newNode;// Если нет правого дочернего узла, новый узел становится правым дочерним
                    break;
                }
                else {
                    current = current->right;// Переход к правому дочернему узлу
                }
            }
        }
    }
}
void BinaryTree::removeElement(int diskSize, const string& name) {
    Node* parent = nullptr;
    Node* current = root;

    while (current != nullptr) {
        if (diskSize == current->app.diskSize && name == current->app.name) {
            // Найден элемент для удаления
            if (current->left == nullptr && current->right == nullptr) {
                // Удаляемый узел является листом
                if (parent == nullptr) {
                    root = nullptr; // Специальный случай, удаляем корень дерева
                }
                else if (parent->left == current) {
                    parent->left = nullptr;
                }
                else {
                    parent->right = nullptr;
                }
                delete current;
            }
            else if (current->left != nullptr && current->right == nullptr) {
                // Удаляемый узел имеет только левое поддерево
                if (parent == nullptr) {
                    root = current->left; // Специальный случай, удаляем корень дерева
                }
                else if (parent->left == current) {
                    parent->left = current->left;
                }
                else {
                    parent->right = current->left;
                }
                delete current;
            }
            else if (current->left == nullptr && current->right != nullptr) {
                // Удаляемый узел имеет только правое поддерево
                if (parent == nullptr) {
                    root = current->right; // Специальный случай, удаляем корень дерева
                }
                else if (parent->left == current) {
                    parent->left = current->right;
                }
                else {
                    parent->right = current->right;
                }
                delete current;
            }
            else {
                // Удаляемый узел имеет оба поддерева
                Node* successor = current->right;
                Node* successorParent = current;
                while (successor->left != nullptr) {
                    successorParent = successor;
                    successor = successor->left;
                }
                if (successorParent != current) {
                    successorParent->left = successor->right;
                    successor->right = current->right;
                }
                successor->left = current->left;
                if (parent == nullptr) {
                    root = successor; // Специальный случай, удаляем корень дерева
                }
                else if (parent->left == current) {
                    parent->left = successor;
                }
                else {
                    parent->right = successor;
                }
                delete current;
            }
            return; // Успешно удалили элемент, выходим из метода
        }
        else if ((diskSize < current->app.diskSize) ||
            (diskSize == current->app.diskSize && name < current->app.name)) {

            parent = current;
            current = current->left;
        }
        else {
            parent = current;
            current = current->right;
        }
    }
    // Если мы дошли до этой строки, значит элемент не найден в дереве
    cout << "Элемент с размером диска " << diskSize << " и имя " << name << " не найден на дереве!" << endl;
}

bool BinaryTree::elementExists(int diskSize, const string& name) {
    Node* current = root;

    while (current != nullptr) {
        if (diskSize == current->app.diskSize && name == current->app.name) {
            return true; // Найден элемент с заданным сочетанием ключевых полей
        }
        else if (diskSize < current->app.diskSize ||
            (diskSize == current->app.diskSize && name < current->app.name)) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    return false; // Элемент с заданным сочетанием ключевых полей не найден
}



void BinaryTree::getAllDescriptions(App* arr, int& size) {
    int index = 0;  // Инициализация переменной index, которая будет использоваться для отслеживания текущей позиции в массиве arr
    getAllElements(root, arr, index);  // Вызов рекурсивной функции getAllElements для получения всех элементов дерева
    size = index;  // Присвоение переменной size значения index, т.е. количества элементов, найденных в дереве
}

void BinaryTree::getAllElements(Node* node, App* arr, int& index) {
    if (node == nullptr) {
        return;  // Возврат из функции, если текущий узел равен nullptr (то есть достигнут конец ветки)
    }
    getAllElements(node->left, arr, index);  // Рекурсивный вызов для левого поддерева
    arr[index++] = node->app;  // Присваивание элемента массива arr на позицию index элементу в текущем узле, затем инкрементация index
    getAllElements(node->right, arr, index);  // Рекурсивный вызов для правого поддерева
}




int main()
{
    setlocale(LC_ALL, "Russian");
    BinaryTree tree;
    int choice;
    do {
        cout << "Выберите действие:" << endl;
        cout << "1. добавление элемента" << endl;
        cout << "2. удаление элемента по сочетанию значений полей, являющихся ключевыми" << endl;
        cout << "3. проверка наличия в списке элемента с заданным сочетанием одного или двух ключевых полей" << endl;
        cout << "4. получение описаний всех структур, хранящихся в дереве, в виде массива" << endl;
        cout << "5. выход" << endl;
        cout << "Введите свой выбор: ";
        cin >> choice;

        if (choice == 1) {
            string appName;
            string producer;
            int diskSize;
            double price;

            cout << "Введите название приложения: ";
            cin >> appName;

            cout << "Введите имя производителя: ";
            cin >> producer;

            cout << "Введите размер диска: ";
            cin >> diskSize;

            cout << "Введите цену: ";
            cin >> price;

            App newApp = { appName, producer, diskSize, price };
            tree.addElement(newApp);

        }

        else if (choice == 2) {
            int diskSize;
            string name;

            cout << "Введите размер диска приложения для удаления: ";
            cin >> diskSize;

            cout << "Введите название приложения, которое вы хотите удалить: ";
            cin >> name;

            tree.removeElement(diskSize, name);
        }
        else if (choice == 3) {
            int diskSize;
            string name;

            cout << "Введите размер диска приложения для удаления: ";
            cin >> diskSize;

            cout << "Введите название приложения, которое вы хотите удалить: ";
            cin >> name;
            if (tree.elementExists(diskSize, name)) {
                cout << "Элемент существует в дереве." << endl;
            }
            else {
                cout << "Этот элемент не существует в дереве." << endl;
            }
        }
        else if (choice == 4) {
            App arr[100]; // Определяем массив для хранения описаний
            int size = 0;
            tree.getAllDescriptions(arr, size);
            for (int i = 0; i < size; i++) {
                cout << "Название приложения: " << arr[i].name << " Производитель: " << arr[i].producer
                    << " Размер диска: " << arr[i].diskSize << " Цена: " << arr[i].price << endl;
            }
        }



    } while (choice != 5);
    {}

    return 0;


}