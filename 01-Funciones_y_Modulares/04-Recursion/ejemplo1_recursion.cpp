#include <iostream>
using namespace std;

// Factorial recursivo
int factorial(int n)
{
    if (n <= 1)
    {
        cout << "Caso base: factorial(" << n << ") = 1" << endl;
        return 1;
    }
    cout << "Llamando factorial(" << n - 1 << ")" << endl;
    int resultado = n * factorial(n - 1);
    cout << "Resultado factorial(" << n << ") = " << resultado << endl;
    return resultado;
}

// Fibonacci recursivo
int fibonacci(int n)
{
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Potencia recursiva
int potencia(int base, int exponente)
{
    if (exponente == 0)
        return 1;
    return base * potencia(base, exponente - 1);
}

int main()
{
    cout << "=== FACTORIAL ===" << endl;
    cout << "5! = " << factorial(5) << endl;

    cout << "\n=== FIBONACCI ===" << endl;
    cout << "Fibonacci de 8: ";
    for (int i = 0; i <= 8; i++)
    {
        cout << fibonacci(i) << " ";
    }
    cout << endl;

    cout << "\n=== POTENCIA ===" << endl;
    cout << "2^5 = " << potencia(2, 5) << endl;

    return 0;
}