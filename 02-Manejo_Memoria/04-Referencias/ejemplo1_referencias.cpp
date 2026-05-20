#include <iostream>
#include <string>
using namespace std;

class Persona
{
public:
    string nombre;
    int edad;

    Persona(string n, int e) : nombre(n), edad(e) {}
};

// Función que modifica por referencia
void envejecer(Persona &persona, int anos)
{
    persona.edad += anos;
    cout << persona.nombre << " ahora tiene " << persona.edad << " años" << endl;
}

// Función que no modifica (referencia constante)
void mostrarPersona(const Persona &persona)
{
    cout << "Nombre: " << persona.nombre << endl;
    cout << "Edad: " << persona.edad << endl;
}

// Retorno por referencia
int &obtenerElemento(int arr[], int indice)
{
    return arr[indice];
}

// Función con parámetros mixtos
void procesarDatos(int valor, int &referencia, const int &constante)
{
    cout << "Valor original: " << valor << endl;
    cout << "Referencia original: " << referencia << endl;
    cout << "Constante: " << constante << endl;

    valor = 100;      // Solo cambia la copia
    referencia = 200; // Cambia el original
    // constante = 300; // Error: no se puede modificar
}

int main()
{
    cout << "=== REFERENCIAS BÁSICAS ===" << endl;
    int x = 10;
    int &refX = x;

    cout << "x: " << x << ", refX: " << refX << endl;
    refX = 20;
    cout << "Después de cambiar refX: x = " << x << endl;

    cout << "\n=== REFERENCIAS CON OBJETOS ===" << endl;
    Persona juan("Juan", 25);
    envejecer(juan, 5);
    mostrarPersona(juan);

    cout << "\n=== RETORNO POR REFERENCIA ===" << endl;
    int arreglo[] = {1, 2, 3, 4, 5};
    obtenerElemento(arreglo, 2) = 99;
    cout << "Arreglo modificado: ";
    for (int i = 0; i < 5; i++)
    {
        cout << arreglo[i] << " ";
    }
    cout << endl;

    cout << "\n=== PARÁMETROS MIXTOS ===" << endl;
    int a = 1, b = 2, c = 3;
    procesarDatos(a, b, c);
    cout << "Después de procesarDatos:" << endl;
    cout << "a: " << a << " (copia, no cambió)" << endl;
    cout << "b: " << b << " (referencia, cambió)" << endl;
    cout << "c: " << c << " (constante)" << endl;

}