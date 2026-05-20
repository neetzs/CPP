#include <iostream>
using namespace std;

int main()
{
    cout << "=== MEMORIA DINÁMICA ===" << endl;

    // Asignar un entero
    int *ptrEntero = new int;
    *ptrEntero = 42;
    cout << "Entero dinámico: " << *ptrEntero << endl;

    // Asignar array dinámico
    int tamano;
    cout << "Tamaño del array: ";
    cin >> tamano;

    int *arrDinamico = new int[tamano];

    // Llenar array
    for (int i = 0; i < tamano; i++)
    {
        arrDinamico[i] = i * 10;
        cout << "arrDinamico[" << i << "] = " << arrDinamico[i] << endl;
    }

    // Liberar memoria
    delete ptrEntero;
    delete[] arrDinamico;

    cout << "\n=== ARRAYS DINÁMICOS MULTIDIMENSIONALES ===" << endl;

    // Matriz dinámica
    int filas = 3, columnas = 4;
    int **matriz = new int *[filas];

    for (int i = 0; i < filas; i++)
    {
        matriz[i] = new int[columnas];
    }

    // Llenar matriz
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            matriz[i][j] = i * columnas + j;
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }

    // Liberar matriz
    for (int i = 0; i < filas; i++)
    {
        delete[] matriz[i];
    }
    delete[] matriz;

    cout << "\n=== MEMORY LEAKS ===" << endl;
    cout << "¡Recuerda liberar toda memoria asignada!" << endl;
    cout << "Usa delete para new y delete[] para new[]" << endl;
}