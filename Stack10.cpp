#include <iostream>
#include <stack>
using namespace std;


stack<int> inStack;
stack<int> outStack;


void enQ(int value) {
    inStack.push(value);
}


void transfer() {
    while (!inStack.empty()) {
        outStack.push(inStack.top());
        inStack.pop();
    }
}


bool deQ() {
    if (outStack.empty()) {
        transfer();
    }
    if (outStack.empty()) {
        cout << "Очередь пустая" << endl;
        return false;
    }
    outStack.pop();
    return true;
}


int peek() {
    if (outStack.empty()) {
        transfer();
    }
    if (outStack.empty()) {
        cout << "Очередь пустая" << endl;
        return -1;
    }
    return outStack.top();
}


bool isEmpty() {
    return inStack.empty() && outStack.empty();
}
void printQ() {
    stack<int> temp1 = inStack;
    stack<int> temp2 = outStack;
    stack<int> tempQ;


    while (!temp2.empty()) {
        tempQ.push(temp2.top());
        temp2.pop();
    }


    while (!temp1.empty()) {
        temp2.push(temp1.top());
        temp1.pop();
    }


    while (!temp2.empty()) {
        tempQ.push(temp2.top());
        temp2.pop();
    }


    if (tempQ.empty()) {
        cout << "Очередь пустая" << endl;
        return;
    }

    cout << "Содержимое очереди: ";
    while (!tempQ.empty()) {
        cout << tempQ.top() << " ";
        tempQ.pop();
    }
    cout << endl;
}


int main() {
    setlocale(LC_ALL, "Russian");
    int choice, value;

    while (true) {
        cout << "\n1. Добавить элемент\n";
        cout << "2. Удалить элемент\n";
        cout << "3. Показать очередь\n";
        cout << "4. Проверить пустоту\n";
        cout << "5. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите значение для добавления: ";
            cin >> value;
            enQ(value);
            cout << "Элемент " << value << " добавлен в очередь\n";
            break;
        case 2:
            if (deQ()) {
                cout << "Элемент удален из очереди\n";
            }
            break;
        case 3:
            printQ();
            break;
        case 4:
            if (isEmpty()) {
                cout << "Очередь пустая\n";
            }
            else {
                cout << "Очередь не пустая\n";
            }
            break;
        case 5:
            cout << "Работа программы завершена\n";
            return 0;
        default:
            cout << "Неверный выбор\n";
        }
    }

    return 0;
}