#include <iostream>
#include <string>

using namespace std; // Para no tener que escribir std:: antes de cada cosa
// Lo vamos a ver mas adelante, pero por ahora es suficiente con saber que esto nos permite usar cout, cin, string, etc. sin el prefijo std::

// ==========================================
// EJEMPLO: getline - Lectura de Línea Completa
// ==========================================

int main()
{
    cout << "=== DIFERENCIA ENTRE cin >> Y getline() ===" << endl;

    // Método 1: cin >> (hasta el primer espacio)
    cout << "\n1. Con cin >>" << endl;
    cout << "Escribe tu nombre completo: ";
    string nombre1;
    cin >> nombre1; // Solo lee hasta el espacio
    cout << "Leí: " << nombre1 << endl;

    // Limpiamos el buffer
    cin.ignore(); // Ignora el salto de línea

    // Método 2: getline (línea completa)
    cout << "\n2. Con getline()" << endl;
    cout << "Escribe tu nombre completo: ";
    string nombre2;
    getline(cin, nombre2); // Lee la línea completa
    cout << "Leí: " << nombre2 << endl;

    // Ejemplo práctico: descripción
    cin.ignore();
    cout << "\nEscribe una descripción sobre ti: ";
    string descripcion;
    getline(cin, descripcion);
    cout << "Tu descripción: " << descripcion << endl;
}

// IMPORTANTE:
// - cin >> nombre:  Lee hasta el PRIMER ESPACIO
// - getline(cin, nombre):  Lee la LÍNEA COMPLETA
// - cin.ignore():  Limpia el buffer del salto de línea anterior
