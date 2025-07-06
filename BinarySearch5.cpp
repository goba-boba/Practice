#include <iostream>
#include <vector>
using namespace std;


vector<int> generateArray(int N, int step, int jumpIndex, int start = 0) {
    vector<int> arr(N);
    int value = start;
    for (int i = 0; i < N; ++i) {
        arr[i] = value;
        if (i == jumpIndex) {
            value += step * 2;
        }
        else {
            value += step;
        }
    }
    return arr;
}

int findMissing(const vector<int>& arr, int step, int start = 0) {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        int expected = start + mid * step;

        if (arr[mid] == expected) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return start + left * step;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int N, step, jumpIndex;

    cout << "Введите длину массива: ";
    cin >> N;
    cout << "Введите шаг: ";
    cin >> step;
    cout << "Введите индекс, на котором произойдёт скачок: ";
    cin >> jumpIndex;

    if (jumpIndex < 0 || jumpIndex > N - 1) {
        cout << "Неправильный индекс" << endl;
        return 1;
    }

    vector<int> sequence = generateArray(N, step, jumpIndex);

    cout << "\nМассив:\n";
    for (int num : sequence) {
        cout << num << " ";
    }
    cout << "\n";

    int missing = findMissing(sequence, step);
    cout << "\nНедостающий элемент: " << missing << endl;

    return 0;
}
