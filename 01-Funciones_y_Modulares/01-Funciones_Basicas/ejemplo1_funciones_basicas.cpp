#include <iostream>

using namespace std;

// ==========================================
// PROTOTIPO DE FUNCIONES (Declaración)
// ==========================================
int sumar(int a, int b);
void saludar(string nombre);
bool esPositivo(int numero);

// ==========================================
// MAIN
// ==========================================
int main()
{
    cout << "=== EJEMPLO: FUNCIONES BÁSICAS ===" << endl;

    // Llamar función sumar
    int resultado = sumar(10, 5);
    cout << "10 + 5 = " << resultado << endl;

    // Llamar función saludar
    saludar("Thomas");
    saludar("Dara");

    // Llamar función que retorna bool
    if (esPositivo(10))
    {
        cout << "10 es positivo" << endl;
    }

    if (!esPositivo(-5))
    {
        cout << "-5 no es positivo" << endl;
    }
}

// ==========================================
// DEFINICIÓN DE FUNCIONES
// ==========================================

int sumar(int a, int b)
{
    return a + b;
}

void saludar(string nombre)
{
    cout << "¡Hola " << nombre << "!" << endl;
}

bool esPositivo(int numero)
{
    return numero > 0;
}

// ESTRUCTURA:
// - Prototipo al inicio (declara que existe)
// - main() en el medio
// - Definiciones al final
