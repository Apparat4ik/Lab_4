#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include <iterator>

using namespace std;

random_device rd;

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& vc){
    for (T it : vc){
        os << it << ' ';
    }
    return os;
}

int InputArraySize() {  // ввод числа с проверкой
    int n;
    while (true) {
        cout << "Введите размер массива n (n >= 10): ";
        cin >> n;
        
        if (cin.fail()) {
            cout << "Ошибка: введите целое число!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        
        if (n < 10) {
            cout << "Ошибка: размер массива должен быть не менее 10!" << endl;
            continue;
        }
        
        cin.ignore(10000, '\n');
        cout << "Размер массива успешно установлен: " << n << endl << endl;
        return n;
    }
}


int ShuffleDigits(int number) {        // функция для случайной перестановки цифр в числе
    string numStr = to_string(number);
    shuffle(numStr.begin(), numStr.end(), rd);
    return stoi(numStr);
}

// Задача 1-3: Работа с массивом arr1 и arr2

void ProcessArraysWithMinMax(const int& n) {
    cout << "=== Задачи 1-3: Массивы arr1 и arr2 ===" << endl;
    
    vector<int> arr1(n);
    
    for (int& elem : arr1) {
        elem = rd() % 101;
    }
    
    cout << "Массив arr1: " << arr1 << endl;
    
    
    vector<int>::iterator minIt = min_element(arr1.begin(), arr1.end());
    vector<int>::iterator maxIt = max_element(arr1.begin(), arr1.end());
    
    int minIdx = distance(arr1.begin(), minIt);     // индекс наименьшего
    int maxIdx = distance(arr1.begin(), maxIt);     // индекс наибольшего
    
    cout << "Наименьший элемент: " << *minIt << " (индекс " << minIdx << ")" << endl;
    cout << "Наибольший элемент: " << *maxIt << " (индекс " << maxIdx << ")" << endl;
    
    // границы для суммы (между min и max)
    int startIdx = min(minIdx, maxIdx);
    int endIdx = max(minIdx, maxIdx);
    
    // сумма элементов между min и max
    int sum = 0;
    for (int i = startIdx + 1; i < endIdx; ++i) {
        sum += arr1[i];
    }
    
    cout << "Сумма элементов между наибольшим и наименьшим: " << sum << endl;
    
    vector<int> arr2;
    vector<int> betweenElements;
    
    
    for (int i = startIdx + 1; i < endIdx; ++i) {   // собираем элементы между min и max
        betweenElements.push_back(arr1[i]);
    }
    
    cout << "Элементы между min и max: " << betweenElements << endl;
    
    arr2 = betweenElements;
    
    while (arr2.size() < arr1.size()) {   // дополняем до размеров arr1
        int randomIdx = rd() % arr1.size();
        arr2.push_back(arr1[randomIdx]);
    }
    
    cout << "Массив arr2: " << arr2 << endl;
}

// Задача 4: Сортировка символов на четных местах
void SortCharactersAtEvenPositions(const int& n) {
    cout << "=== Задача 4: Сортировка символов на четных местах ===" << endl;

    vector<char> charArray(n);
    
    for (char& ch : charArray) {
        ch = 32 + rd() % 96;
    }
    
    cout << "Исходный массив символов: " << charArray << endl;
    
    
    vector<char> evenPositions;
    for (size_t i = 0; i < charArray.size(); i += 2) {    // извлекаем элементы на четных позициях
        evenPositions.push_back(charArray[i]);
    }

    sort(evenPositions.begin(), evenPositions.end());
    
    
    size_t evenIdx = 0;
    for (size_t i = 0; i < charArray.size(); i += 2) {    // возвращаем отсортированные элементы обратно на четные позиции
        charArray[i] = evenPositions[evenIdx++];
    }
    
    cout << "Массив после сортировки четных позиций: " << charArray << endl << endl;
}

// Задача 5: Работа с числами и перестановка цифр
void ShuffleDigitsAndCompare(const int& n) {
    cout << "=== Задача 5: Перестановка цифр в числах ===" << endl;
    
    vector<int> numbers(n);
    
    for (int& num : numbers) {
        num = 100 + rd() % 801;
    }
    
    cout << "Исходный массив: " << numbers << endl;
    
    sort(numbers.begin(), numbers.end());
    
    cout << "Отсортированный массив: " << numbers;
    
    vector<int> newArray;
    
    for (const int& originalNum : numbers) {
        int modifiedNum = ShuffleDigits(originalNum);
        
        if (modifiedNum > originalNum) {
            newArray.push_back(modifiedNum);
            cout << originalNum << " -> " << modifiedNum << " (больше, добавляем)" << endl;
        } else {
            cout << originalNum << " -> " << modifiedNum << " (меньше или равно, не добавляем)" << endl;
        }
    }
    
    cout << "Новый массив: " << newArray << endl;
}

int main() {
    cout << "Программа решения задач с массивами" << endl;
    cout << "====================================" << endl << endl;
    
    int n = InputArraySize();
    ProcessArraysWithMinMax(n);
    SortCharactersAtEvenPositions(n);
    ShuffleDigitsAndCompare(n);
    
    return 0;
}
