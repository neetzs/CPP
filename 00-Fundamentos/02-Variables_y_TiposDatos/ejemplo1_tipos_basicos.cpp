#include <iostream>

using namespace std;

// ==========================================
// EJEMPLO: Tipos de Datos Básicos
// ==========================================

int main()
{
    // Enteros (4 bytes)
    int edad = 25;
    int numero = -100;

    // Decimales (4 bytes para float, 8 bytes para double)
    // Nota: En C++, los literales decimales son de tipo double por defecto, así que es buena práctica usar 'f' para indicar que es un float.
    float altura = 1.75f; // Nota la 'f' al final
    double pi = 3.14159;  // Más preciso que float

    // Caracteres (1 byte)
    char inicial = 'J';

    // Booleanos (1 byte)
    bool esEstudiante = true;

    // Texto (string necesita <string>)
    string nombre = "Juan";

    // Mostrar valores
    cout << "Edad: " << edad << endl;
    cout << "Altura: " << altura << endl;
    cout << "Pi: " << pi << endl;
    cout << "Inicial: " << inicial << endl;
    cout << "¿Es estudiante? " << esEstudiante << endl; // Muestra 1 (true) o 0 (false)
    cout << "Nombre: " << nombre << endl;
}

// NOTAS RESUMEN:
// - int: números enteros
// - float: decimales de precisión simple (4 bytes)
// - double: decimales de precisión doble (8 bytes)
// - char: UN solo carácter entre comillas simples
// - bool: true o false (se imprime como 1 o 0)
// - string: texto, entre comillas dobles
