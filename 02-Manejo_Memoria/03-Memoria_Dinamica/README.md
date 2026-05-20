# 03 - Memoria Dinámica

## Concepto Clave
La **memoria dinámica** permite asignar y liberar memoria en **tiempo de ejecución** usando el **heap**.

## Stack vs Heap

### Stack (Pila)
- Memoria automática
- Rápida asignación/liberación
- Tamaño limitado
- Variables locales, parámetros

### Heap (Montón)
- Memoria manual
- Más lenta pero flexible
- Tamaño limitado por sistema
- Control total del programador

## Operadores de Memoria Dinámica

### `new` - Asignar Memoria
```cpp
int* ptr = new int;        // Un entero
int* arr = new int[10];    // Array de 10 enteros
```

### `delete` - Liberar Memoria
```cpp
delete ptr;        // Liberar un elemento
delete[] arr;      // Liberar array
```

## Ejemplo Completo

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "=== MEMORIA DINÁMICA ===" << endl;

    // Asignar un entero
    int* ptrEntero = new int;
    *ptrEntero = 42;
    cout << "Entero dinámico: " << *ptrEntero << endl;

    // Asignar array dinámico
    int tamano;
    cout << "Tamaño del array: ";
    cin >> tamano;

    int* arrDinamico = new int[tamano];

    // Llenar array
    for (int i = 0; i < tamano; i++) {
        arrDinamico[i] = i * 10;
        cout << "arrDinamico[" << i << "] = " << arrDinamico[i] << endl;
    }

    // Liberar memoria
    delete ptrEntero;
    delete[] arrDinamico;

    cout << "\n=== ARRAYS DINÁMICOS MULTIDIMENSIONALES ===" << endl;

    // Matriz dinámica
    int filas = 3, columnas = 4;
    int** matriz = new int*[filas];

    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
    }

    // Llenar matriz
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = i * columnas + j;
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }

    // Liberar matriz
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    cout << "\n=== MEMORY LEAKS ===" << endl;
    cout << "¡Recuerda liberar toda memoria asignada!" << endl;
    cout << "Usa delete para new y delete[] para new[]" << endl;

}
```

## Problemas Comunes

### Memory Leaks
```cpp
void funcionProblematica() {
    int* ptr = new int(10);
    // Olvidé delete ptr;
    // Memory leak!
}
```

### Double Delete
```cpp
int* ptr = new int(5);
delete ptr;
// delete ptr;  // Error! Double delete
ptr = nullptr;  // Buena práctica
```

### Array vs Elemento Único
```cpp
int* arr = new int[10];
delete arr;     // ❌ Mal: debería ser delete[]
delete[] arr;   // ✅ Correcto
```

## Buenas Prácticas

### ✅ Recomendado
```cpp
// Siempre verificar asignación
int* ptr = new int;
if (ptr == nullptr) {
    // Error de memoria
}

// Liberar inmediatamente cuando no se use
delete ptr;
ptr = nullptr;

// Usar RAII (ver Smart Pointers)
```

### ❌ Evitar
```cpp
// No mezclar new/delete con malloc/free
int* ptr = (int*)malloc(sizeof(int));  // C style
// delete ptr;  // ❌ Incorrecto

// Liberar correctamente
free(ptr);  // ✅ Correcto
```

## Reglas Importantes

1. **Cada new necesita delete**: Para cada `new` un `delete`
2. **Arrays**: `new[]` requiere `delete[]`
3. **Nullptr**: Asigna `nullptr` después de `delete`
4. **Excepciones**: `new` puede lanzar `std::bad_alloc`
5. **Verificación**: Siempre verifica si la asignación fue exitosa
6. **Liberar**: Libera memoria lo antes posible