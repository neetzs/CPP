#include <iostream>

using namespace std;

// ==========================================
// EJEMPLO: Entrada y Salida Básica
// ==========================================

// En este ejemplo se muestra cómo usar cin para leer datos desde el teclado y cout para mostrar resultados en la consola.
// NOTAS:
// - cin: se usa para entrada de datos (input)(lee desde el teclado)
// - cout: se usa para salida de datos (output)(muestra en la consola)
// - endl: se usa para saltos de línea (end line)(también limpia el buffer, pero es más lento que '\n')

int main()
{
    cout << "=== ENTRADA Y SALIDA ===" << endl;

    // Pedir un nombre
    cout << "¿Cuál es tu nombre? ";
    string nombre;
    cin >> nombre; // Nota: solo lee hasta el primer espacio

    // Pedir edad
    cout << "¿Cuántos años tienes? ";
    int edad;
    cin >> edad;

    // Mostrar información
    cout << "\nHola " << nombre << ", tienes " << edad << " años." << endl;

    // Cálculos simples
    int anioNacimiento = 2026 - edad;
    cout << "Naciste aproximadamente en: " << anioNacimiento << endl;

    // - Para leer texto con espacios, se puede usar getline(cin, variable) en lugar de cin >> variable
    //  Ejemplo con getline:
    string nombreCompleto;
    cout << "¿Cuál es tu nombre completo? ";
    getline(cin, nombreCompleto); // Lee toda la línea, incluyendo espacios
}

// CÓMO USAR:
// g++ -std=c++23 ejemplo1_entrada_salida.cpp -o programa
// ./programa
// Sigue las instrucciones interactivas
