#include <iostream>

using namespace std;

// ==========================================
// EJEMPLO: if, else if, else
// ==========================================

int main()
{
    cout << "=== EJEMPLO 1: if, else if, else ===" << endl;

    int edad;
    cout << "¿Cuántos años tienes? ";
    cin >> edad;

    if (edad < 13)
    {
        cout << "Eres un niño" << endl;
    }
    else if (edad < 18)
    {
        cout << "Eres un adolescente" << endl;
    }
    else if (edad < 65)
    {
        cout << "Eres un adulto" << endl;
    }
    else
    {
        cout << "Eres un adulto mayor" << endl;
    }

    cout << "\n=== EJEMPLO 2: Números pares e impares ===" << endl;

    int numero;
    cout << "Introduce un número: ";
    cin >> numero;

    if (numero % 2 == 0)
    {
        cout << numero << " es PAR" << endl;
    }
    else
    {
        cout << numero << " es IMPAR" << endl;
    }

    cout << "\n=== EJEMPLO 3: Comparaciones ===" << endl;

    int a, b;
    cout << "Primer número: ";
    cin >> a;
    cout << "Segundo número: ";
    cin >> b;

    if (a > b)
    {
        cout << a << " es mayor que " << b << endl;
    }
    else if (a < b)
    {
        cout << a << " es menor que " << b << endl;
    }
    else
    {
        cout << a << " es igual a " << b << endl;
    }

}
