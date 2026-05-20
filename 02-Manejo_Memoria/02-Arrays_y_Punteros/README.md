# 02 - Arrays y Punteros

## Concepto Clave
Los **arrays** y **punteros** están estrechamente relacionados en C++. Un array es esencialmente un puntero constante al primer elemento.

## Relación Array-Puntero

```cpp
int arreglo[5] = {1, 2, 3, 4, 5};
int* ptr = arreglo;  // ptr apunta al primer elemento

// Equivalentes:
cout << arreglo[0];  // 1
cout << *ptr;        // 1

cout << arreglo[2];  // 3
cout << *(ptr + 2);  // 3
```

## Aritmética de Punteros

Los punteros permiten "navegar" por la memoria:

```cpp
int arr[] = {10, 20, 30, 40, 50};
int* ptr = arr;

ptr++;     // Ahora apunta a arr[1]
ptr += 2;  // Ahora apunta a arr[3]
ptr--;     // Ahora apunta a arr[2]
```

## Arrays como Parámetros de Función

```cpp
// Estas declaraciones son equivalentes:
void funcion(int arr[]);     // Array
void funcion(int* arr);      // Puntero

// Para evitar modificaciones accidentales:
void funcion(const int arr[]);  // Solo lectura
```

## Ejemplo Completo

```cpp
#include <iostream>
using namespace std;

void imprimirArray(int arr[], int tamano) {
    cout << "Array: ";
    for (int i = 0; i < tamano; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void imprimirConPunteros(int* ptr, int tamano) {
    cout << "Con punteros: ";
    for (int i = 0; i < tamano; i++) {
        cout << *(ptr + i) << " ";
    }
    cout << endl;
}

void modificarArray(int arr[], int indice, int nuevoValor) {
    arr[indice] = nuevoValor;
}

int main() {
    int arreglo[] = {10, 20, 30, 40, 50};
    int tamano = 5;

    cout << "=== ARRAY ORIGINAL ===" << endl;
    imprimirArray(arreglo, tamano);

    cout << "\n=== ACCESO CON PUNTEROS ===" << endl;
    int* ptr = arreglo;
    cout << "Primer elemento: " << *ptr << endl;
    cout << "Tercer elemento: " << *(ptr + 2) << endl;

    cout << "\n=== ARITMÉTICA DE PUNTEROS ===" << endl;
    cout << "ptr apunta a: " << *ptr << endl;
    ptr++;  // Avanza al siguiente elemento
    cout << "Después de ptr++: " << *ptr << endl;
    ptr += 2;  // Avanza 2 posiciones
    cout << "Después de ptr += 2: " << *ptr << endl;

    cout << "\n=== MODIFICACIÓN ===" << endl;
    ptr = arreglo;  // Reset al inicio
    modificarArray(arreglo, 1, 999);
    imprimirArray(arreglo, tamano);

    cout << "\n=== DIFERENTES FORMAS DE IMPRIMIR ===" << endl;
    imprimirArray(arreglo, tamano);
    imprimirConPunteros(arreglo, tamano);

    cout << "\n=== DIRECCIONES DE MEMORIA ===" << endl;
    for (int i = 0; i < tamano; i++) {
        cout << "&arreglo[" << i << "] = " << &arreglo[i] << endl;
    }

}
```

## Arrays Multidimensionales

```cpp
int matriz[3][4];
int (*ptrMatriz)[4] = matriz;  // Puntero a array de 4 ints

// Acceso:
matriz[1][2] = 42;
*(*(ptrMatriz + 1) + 2) = 42;  // Equivalente
```

## Reglas Importantes

1. **Nombre del array**: Es un puntero constante al primer elemento
2. **Aritmética**: `ptr + n` avanza `n * sizeof(tipo)` bytes
3. **Límites**: No hay verificación automática de límites
4. **sizeof**: `sizeof(arr)` da el tamaño total, `sizeof(ptr)` da tamaño del puntero
5. **Parámetros**: Arrays se pasan como punteros a funciones