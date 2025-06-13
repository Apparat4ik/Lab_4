#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;


enum Operation {
    ADD = 1,
    SUB = 2,
    MUL = 3,
    XOR = 4
};


int InputInteger(const string& prompt, int min = 1, int max = numeric_limits<int>::max()) {   // безопасный ввод чисел
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cout << "Ошибка: введите целое число!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        
        if (value < min || value > max) {
            cout << "Ошибка: значение должно быть не менее " << min << " и не больше " << max << endl;
            continue;
        }
        
        cin.ignore(10000, '\n');
        return value;
    }
}



vector<int> GenerateFibonacciInitialValues(int k, int m) {   // вычисление S0, S1... как последовательность Фибоначи
    vector<int> fib(k);
    fib[0] = 0;
    if (k > 1) fib[1] = 1;
    
    for (int i = 2; i < k; ++i) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % m;
    }
    
    return fib;
}


Operation SelectOperation() {
    cout << "=== Выбор операции ===" << endl;
    cout << "1 - Сложение (+)" << endl;
    cout << "2 - Вычитание (-)" << endl;
    cout << "3 - Умножение (*)" << endl;
    cout << "4 - Исключающее ИЛИ (XOR)" << endl;
    
    int choice = InputInteger("Выберите операцию (1-4): ", 1, 4);
    while (choice > 4) {
        cout << "Ошибка: выберите число от 1 до 4!" << endl;
        choice = InputInteger("Выберите операцию (1-4): ", 1, 4);
    }
    
    return static_cast<Operation>(choice);
}


int PerformOperation(int a, int b, Operation op, int m) {
    int result;
    switch (op) {
        case ADD:
            result = (a + b) % m;
            break;
        case SUB:
            result = (a - b) % m;
            break;
        case MUL:
            result = (a * b) % m;
            break;
        case XOR:
            result = (a ^ b) % m;
            break;
        default:
            result = 0;
    }
    return result;
}


char GetOperationSymbol(Operation op) {
    switch (op) {
        case ADD: return '+';
        case SUB: return '-';
        case MUL: return '*';
        case XOR: return '^';
        default: return '?';
    }
}

// Основная функция генерации последовательности Фибоначчи с запаздыванием
void GenerateFibonacciSequence(int& j, int& k, int& m, Operation& op, int& count) {
    
    vector<int> sequence = GenerateFibonacciInitialValues(k, m);
    
    cout << "\n=== Генерация последовательности ===" << endl;
    cout << "Формула: Sn = S(n-" << j << ") " << GetOperationSymbol(op)
         << " S(n-" << k << ") (mod " << m << ")" << endl << endl;
    
    cout << "Начальные значения:" << endl;
    for (int i = 0; i < k; ++i) {
        cout << "S" << i << " = " << sequence[i] << endl;
    }
    cout << endl;
    
    cout << "Генерируемая последовательность:" << endl;
    for (int i = 0; i < count; ++i) {
        int n = k + i; // текущий индекс
        int prevJ = sequence[sequence.size() - j]; // S(n-j)
        int prevK = sequence[sequence.size() - k]; // S(n-k)
        
        int newValue = PerformOperation(prevJ, prevK, op, m);
        sequence.push_back(newValue);
        
        cout << "S" << n << " = S" << (n-j) << " " << GetOperationSymbol(op)
             << " S" << (n-k) << " = " << prevJ << " " << GetOperationSymbol(op)
             << " " << prevK << " = " << newValue << " (mod " << m << ")" << endl;
    }
    
    cout << "Итоговая последовательность из " << count << " сгенерированных чисел:" << endl;
    for (int i = k; i < sequence.size(); ++i) {
        cout << sequence[i];
        if (i < sequence.size() - 1) cout << " ";
    }
    cout << endl << endl;
}



int main() {
    cout << "=== ГЕНЕРАТОР ФИБОНАЧЧИ С ЗАПАЗДЫВАНИЕМ ===" << endl;
    cout << "Формула: Sn = S(n-j) & S(n-k) (mod m), где 0 < j < k" << endl;
    cout << "& - операция (+, -, *, XOR)" << endl << endl;
    cout << "=== Ввод параметров генератора Фибоначчи с запаздыванием ===" << endl;
    cout << "Условие: 0 < j < k" << endl << endl;
    
    int j, k, m;
    
    
    while (true) {
        j = InputInteger("Введите параметр j (j > 0): ");
        k = InputInteger("Введите параметр k (k > j): ", j + 1);
        
        if (j < k) {
            break;
        } else {
            cout << "Ошибка: должно выполняться условие 0 < j < k!" << endl;
        }
    }
    
    cout << "Для модуля m рекомендуется использовать степень 2" << endl;
    m = InputInteger("Введите модуль m (m > 0): ");
    
    cout << "Параметры установлены: j=" << j << ", k=" << k << ", m=" << m << endl << endl;
    
    
    cout << "=== Выбор операции ===" << endl;
    cout << "1 - Сложение (+)" << endl;
    cout << "2 - Вычитание (-)" << endl;
    cout << "3 - Умножение (*)" << endl;
    cout << "4 - Исключающее ИЛИ (XOR)" << endl;
    
    int choice = InputInteger("Выберите операцию (1-4): ", 1, 4);
    while (choice > 4) {
        cout << "Ошибка: выберите число от 1 до 4!" << endl;
        choice = InputInteger("Выберите операцию (1-4): ", 1, 4);
    }
    Operation op = static_cast<Operation>(choice);
    
    int count = InputInteger("Введите количество генерируемых чисел: ");
    

    GenerateFibonacciSequence(j, k, m, op, count);
    
    return 0;
}
