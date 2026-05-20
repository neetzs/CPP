# 01 - Punteros Básicos

## Concepto Clave
Un **puntero** es una variable que almacena la **dirección de memoria** de otra variable.

## ¿Qué es la Memoria?

La memoria RAM se organiza en **bytes consecutivos**, cada uno con una dirección única.

```cpp
// Variable normal
int numero = 42;

// Puntero almacena la dirección de 'numero'
int* puntero = &numero;  // & obtiene la dirección
```

## Operadores de Punteros

### `&` - Operador de Dirección
Obtiene la dirección de memoria de una variable.

```cpp
int x = 10;
int* ptr = &x;  // ptr apunta a x
```

### `*` - Operador de Desreferencia
Accede al valor almacenado en la dirección apuntada.

```cpp
int x = 10;
int* ptr = &x;
cout << *ptr;  // Imprime 10 (el valor de x)
*ptr = 20;     // Cambia x a 20
```

## Declaración de Punteros

```cpp
int* ptr1;        // Puntero a int
double* ptr2;     // Puntero a double
char* ptr3;       // Puntero a char
void* ptr4;       // Puntero genérico (void*)
```

## Ejemplo Completo

```cpp
#include <iostream>
using namespace std;

int main() {
    // Variables normales
    int numero = 42;
    double decimal = 3.14;
    char letra = 'A';

    // Punteros
    int* ptrNumero = &numero;
    double* ptrDecimal = &decimal;
    char* ptrLetra = &letra;

    cout << "=== VALORES ===" << endl;
    cout << "numero: " << numero << endl;
    cout << "decimal: " << decimal << endl;
    cout << "letra: " << letra << endl;

    cout << "\n=== DIRECCIONES ===" << endl;
    cout << "&numero: " << &numero << endl;
    cout << "&decimal: " << &decimal << endl;
    cout << "&letra: " << &letra << endl;

    cout << "\n=== PUNTEROS ===" << endl;
    cout << "ptrNumero: " << ptrNumero << endl;
    cout << "ptrDecimal: " << ptrDecimal << endl;
    cout << "ptrLetra: " << ptrLetra << endl;

    cout << "\n=== DESREFERENCIA ===" << endl;
    cout << "*ptrNumero: " << *ptrNumero << endl;
    cout << "*ptrDecimal: " << *ptrDecimal << endl;
    cout << "*ptrLetra: " << *ptrLetra << endl;

    cout << "\n=== MODIFICACIÓN A TRAVÉS DE PUNTEROS ===" << endl;
    *ptrNumero = 100;
    *ptrDecimal = 2.71;
    *ptrLetra = 'Z';

    cout << "Después de modificar:" << endl;
    cout << "numero: " << numero << endl;
    cout << "decimal: " << decimal << endl;
    cout << "letra: " << letra << endl;

}
```

## Punteros NULL

```cpp
int* ptr = nullptr;  // Puntero que no apunta a nada
// o en C++ antiguo: int* ptr = NULL;

if (ptr != nullptr) {
    cout << *ptr << endl;  // Seguro
}
```

## Reglas Importantes

1. **Inicializar punteros**: Siempre inicializa punteros (nullptr si no apuntan a nada)
2. **Desreferencia segura**: Verifica que el puntero no sea nullptr antes de desreferenciar
3. **Tipos**: El tipo del puntero debe coincidir con el tipo de la variable apuntada
4. **Direcciones**: `&variable` obtiene la dirección, `*puntero` obtiene el valor
5. **Modificación**: `*puntero = nuevoValor` modifica la variable original