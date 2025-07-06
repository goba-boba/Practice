#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

void init(Node*& head, Node*& tail) {
    head = nullptr;
    tail = nullptr;
}
void enQ(Node*& head, Node*& tail, int value) {
    Node* newNode = new Node{ value, nullptr };
    if (tail == nullptr) { 
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

int deQ(Node*& head, Node*& tail) {
    if (head == nullptr) {
        cerr << "Очередь пустая" << endl;
        return -1; 
    }
    Node* temp = head;
    int value = temp->data;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
    return value;
}

bool isEmpty(Node* head) {
    return head == nullptr;
}

void clear(Node*& head, Node*& tail) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

void printQ(Node* head) {
    if (isEmpty(head)) {
        cout << "Очередь пустая" << endl;
        return;
    }
        cout << "Очередь: ";
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
        cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Node* head;
    Node* tail;
    init(head, tail);

    int choice, value;

    while (true) {
       cout << "1. Добавить элемент\n";
       cout << "2. Удалить элемент\n";
       cout << "3. Показать очередь\n";
       cout << "4. Проверить пустоту\n";
       cout << "5. Выход\n";
       cout << "Выберите действие: ";
       cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите число: ";
            cin >> value;
            enQ(head, tail, value);
            cout << "Элемент " << value << " добавлен в очередь\n";
            break;
        case 2:
            if (!isEmpty(head)) {
                value = deQ(head, tail);
                cout << "Удалён элемент: " << value << endl;
            }
            else {
                cout << "Очередь пустая\n";
            }
            break;
        case 3:
            printQ(head);
            break;
        case 4:
            cout << (isEmpty(head) ? "Очередь пустая\n" : "Очередь не пустая\n");
            break;
        case 5:
            clear(head, tail);
            cout << "Работа программы завершена\n";
            return 0;
        default:
            cout << "Неверный выбор\n";
        }
    }

    return 0;
}