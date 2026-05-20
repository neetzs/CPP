#include <iostream>
using namespace std;

void imprimirArray(int arr[], int tamano)
{
    cout << "Array: ";
    for (int i = 0; i < tamano; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void imprimirConPunteros(int *ptr, int tamano)
{
    cout << "Con punteros: ";
    for (int i = 0; i < tamano; i++)
    {
        cout << *(ptr + i) << " ";
    }
    cout << endl;
}

void modificarArray(int arr[], int indice, int nuevoValor)
{
    arr[indice] = nuevoValor;
}

int main()
{
    int arreglo[] = {10, 20, 30, 40, 50};
    int tamano = 5;

    cout << "=== ARRAY ORIGINAL ===" << endl;
    imprimirArray(arreglo, tamano);

    cout << "\n=== ACCESO CON PUNTEROS ===" << endl;
    int *ptr = arreglo;
    cout << "Primer elemento: " << *ptr << endl;
    cout << "Tercer elemento: " << *(ptr + 2) << endl;

    cout << "\n=== ARITMÉTICA DE PUNTEROS ===" << endl;
    cout << "ptr apunta a: " << *ptr << endl;
    ptr++; // Avanza al siguiente elemento
    cout << "Después de ptr++: " << *ptr << endl;
    ptr += 2; // Avanza 2 posiciones
    cout << "Después de ptr += 2: " << *ptr << endl;

    cout << "\n=== MODIFICACIÓN ===" << endl;
    ptr = arreglo; // Reset al inicio
    modificarArray(arreglo, 1, 999);
    imprimirArray(arreglo, tamano);

    cout << "\n=== DIFERENTES FORMAS DE IMPRIMIR ===" << endl;
    imprimirArray(arreglo, tamano);
    imprimirConPunteros(arreglo, tamano);

    cout << "\n=== DIRECCIONES DE MEMORIA ===" << endl;
    for (int i = 0; i < tamano; i++)
    {
        cout << "&arreglo[" << i << "] = " << &arreglo[i] << endl;
    }
}