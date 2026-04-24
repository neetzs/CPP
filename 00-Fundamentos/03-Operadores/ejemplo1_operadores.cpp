#include <iostream>

using namespace std;

// ==========================================
// EJEMPLO: Operadores Aritméticos
// ==========================================

// En este ejemplo se muestran los operadores aritméticos básicos, de comparación, lógicos y de asignación en C++.
// NOTAS:
// - Los operadores aritméticos son: +, -, *, /, %
// - Los operadores de comparación son: ==, !=, >, <, >=, <=
// - Los operadores lógicos son: && (AND), || (OR), ! (NOT)
// - Los operadores de asignación son: =, +=, -=, *=, /=

// Acordate que la división entre enteros da un resultado entero (trunca los decimales).
// Si quieres obtener un resultado decimal, al menos uno de los operandos debe ser un número con punto decimal (float o double).
int main()
{
    int a = 10;
    int b = 3;

    cout << "=== OPERADORES ARITMÉTICOS ===" << endl;
    cout << a << " + " << b << " = " << (a + b) << endl;
    cout << a << " - " << b << " = " << (a - b) << endl;
    cout << a << " * " << b << " = " << (a * b) << endl;
    cout << a << " / " << b << " = " << (a / b) << endl; // División entera
    cout << a << " % " << b << " = " << (a % b) << endl; // Módulo (residuo)

    cout << "\n=== OPERADORES DE COMPARACIÓN ===" << endl;
    cout << a << " == " << b << " ? " << (a == b) << endl;
    cout << a << " != " << b << " ? " << (a != b) << endl;
    cout << a << " > " << b << " ? " << (a > b) << endl;
    cout << a << " < " << b << " ? " << (a < b) << endl;

    cout << "\n=== OPERADORES LÓGICOS ===" << endl;
    bool resultado1 = (a > 5) && (b < 5); // true && true = true
    bool resultado2 = (a > 5) || (b > 5); // true || false = true
    bool resultado3 = !(a > 5);           // !(true) = false

    cout << "(a > 5) && (b < 5) = " << resultado1 << endl;
    cout << "(a > 5) || (b > 5) = " << resultado2 << endl;
    cout << "!(a > 5) = " << resultado3 << endl;

    cout << "\n=== OPERADORES DE ASIGNACIÓN ===" << endl;
    int x = 10;
    cout << "x = " << x << endl;
    x += 5; // x = x + 5
    cout << "x += 5 => x = " << x << endl;
    x -= 3; // x = x - 3
    cout << "x -= 3 => x = " << x << endl;
    x *= 2; // x = x * 2
    cout << "x *= 2 => x = " << x << endl;
}

// NOTAS IMPORTANTES:
// - La división entre enteros (int / int) da resultado entero
// - 10 / 3 = 3 (NO 3.33)
// - Si quieres decimales: 10.0 / 3 = 3.333...
// - El módulo (%) solo funciona con enteros
