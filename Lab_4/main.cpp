#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

// Исходная функция
double f(double x) {
    return 2*x + cos(x);
}

// Производная функции
double df(double x) {
    return 2 - sin(x);
}

// Функция для метода простых итераций для положительного корня
double phi_positive(double x) {
    return cos(x) / 2;
}

// Функция для метода простых итераций для отрицательного корня
double phi_negative(double x) {
    return -(cos(x) / 2);
}

// Метод половинного деления
void bisection_method(double a, double b, double epsilon, const string& root_name) {
    cout << "\nМетод половинного деления для " << root_name << " на интервале [" << a << ", " << b << "]\n";
    cout << "N\t a\t\t\t b\t\t\t (b - a)\n";
    cout << "------------------------------------------------\n";
    
    int k = 0;
    double c;
    
    while (fabs(b - a) > epsilon) {
        c = (a + b) / 2;
        cout << k << "\t " << fixed << setprecision(6) << a << "\t " << b << "\t " << (b - a) << endl;
        
        if (f(a) * f(c) < 0) {
            b = c;
        } else {
            a = c;
        }
        k++;
    }
    
    double root = (a + b) / 2;
    cout << "------------------------------------------------\n";
    cout << "Найденный корень: " << root << endl;
    cout << "Значение функции в корне: " << f(root) << endl;
    cout << "Количество итераций: " << k << endl;
}

// Метод Ньютона
void newton_method(double x0, double epsilon, const string& root_name) {
    cout << "\nМетод Ньютона для " << root_name << " с начальным приближением x0 = " << x0 << "\n";
    cout << "N\t x_n\t\t x_{n+1}\t |x_{n+1} - x_n|\n";
    cout << "------------------------------------------------\n";
    
    int k = 0;
    double x_prev = x0;
    double x_next = x_prev - f(x_prev)/df(x_prev);
    
    while (fabs(x_next - x_prev) > epsilon) {
        cout << k << "\t " << fixed << setprecision(6) << x_prev << "\t " << x_next << "\t " << fabs(x_next - x_prev) << endl;
        
        x_prev = x_next;
        x_next = x_prev - f(x_prev)/df(x_prev);
        k++;
    }
    
    cout << "------------------------------------------------\n";
    cout << "Найденный корень: " << x_next << endl;
    cout << "Значение функции в корне: " << f(x_next) << endl;
    cout << "Количество итераций: " << k << endl;
}


// Метод простых итераций
void simple_iteration(double x0, double epsilon, double (*phi)(double), const string& root_name) {
    cout << "\nМетод простых итераций для " << root_name << " с начальным приближением x0 = " << x0 << "\n";
    cout << "N\t x_n\t\t x_{n+1}\t |x_{n+1} - x_n|\n";
    cout << "------------------------------------------------\n";
    
    int k = 0;
    double x_prev = x0;
    double x_next = phi(x_prev);
    
    while (fabs(x_next - x_prev) > epsilon) {
        cout << k << "\t " << fixed << setprecision(6) << x_prev << "\t " << x_next << "\t " << fabs(x_next - x_prev) << endl;
        
        x_prev = x_next;
        x_next = phi(x_prev);
        k++;
    }
    
    cout << "------------------------------------------------\n";
    cout << "Найденный корень: " << x_next << endl;
    cout << "Значение функции в корне: " << f(x_next) << endl;
    cout << "Количество итераций: " << k << endl;
}

int main() {
    cout << fixed << setprecision(6);   // установка точности вывода
    
    
    const double epsilon = 1e-4;   // точность вычислений
    

    // поиск положительного корня (вблизи 0.4)
    bisection_method(0.4, 0.5, epsilon, "положительного корня");
    newton_method(0.4, epsilon, "положительного корня");
    simple_iteration(0.4, epsilon, phi_positive, "положительного корня");
    
    // поиск отрицательного корня (вблизи -0.4)
    bisection_method(-0.5, 0, epsilon, "отрицательного корня");
    newton_method(-0.4, epsilon, "отрицательного корня");
    simple_iteration(-0.4, epsilon, phi_negative, "отрицательного корня");
    
    return 0;
}
