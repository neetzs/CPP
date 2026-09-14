# 01 - Vector

## Concepto Clave
`std::vector` es un contenedor dinámico que puede cambiar de tamaño automáticamente. Es como un array inteligente que crece según sea necesario.

## Sintaxis Básica

```cpp
#include <vector>

std::vector<int> numeros;              // Vector vacío
std::vector<double> precios(10);       // 10 elementos, valor por defecto 0.0
std::vector<string> nombres(5, "vacio"); // 5 elementos con valor inicial
std::vector<int> copia = otro_vector;  // Copia de otro vector
```

## Operaciones Básicas

```cpp
vector<int> v;

// Agregar elementos
v.push_back(10);     // Agrega al final
v.push_back(20);
v.push_back(30);

// Acceder elementos
int primero = v[0];        // Sin verificación de límites
int ultimo = v.back();     // Último elemento
int penultimo = v[v.size() - 2]; // Penúltimo

// Tamaño y capacidad
size_t tamano = v.size();      // Número de elementos
size_t capacidad = v.capacity(); // Espacio reservado

// Modificar
v[0] = 100;        // Cambiar primer elemento
v.pop_back();      // Remover último elemento

// Iterar
for(size_t i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
}
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void mostrarVector(const vector<int>& v, const string& nombre) {
    cout << nombre << " (tamaño: " << v.size()
         << ", capacidad: " << v.capacity() << "): ";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i < v.size() - 1) cout << ", ";
    }
    cout << endl;
}

int main() {
    cout << "=== VECTOR EN C++ ===" << endl;

    // 1. Creación de vectores
    cout << "\n--- CREACIÓN DE VECTORES ---" << endl;

    vector<int> v1;                    // Vector vacío
    vector<int> v2(5);                 // 5 elementos, inicializados en 0
    vector<int> v3(3, 42);             // 3 elementos con valor 42
    vector<int> v4 = {1, 2, 3, 4, 5}; // Inicialización con lista

    mostrarVector(v1, "v1 (vacío)");
    mostrarVector(v2, "v2 (5 ceros)");
    mostrarVector(v3, "v3 (3 cuarentas)");
    mostrarVector(v4, "v4 (lista)");

    // 2. Agregar elementos
    cout << "\n--- AGREGAR ELEMENTOS ---" << endl;

    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    mostrarVector(v1, "v1 después de push_back");

    // Insertar en posiciones específicas
    v1.insert(v1.begin() + 1, 15);  // Insertar 15 en posición 1
    mostrarVector(v1, "v1 después de insert");

    // 3. Acceder a elementos
    cout << "\n--- ACCEDER A ELEMENTOS ---" << endl;

    cout << "Primer elemento: " << v1.front() << endl;
    cout << "Último elemento: " << v1.back() << endl;
    cout << "Elemento en posición 2: " << v1[2] << endl;
    cout << "Elemento en posición 2 (con at()): " << v1.at(2) << endl;

    // 4. Modificar elementos
    cout << "\n--- MODIFICAR ELEMENTOS ---" << endl;

    v1[0] = 100;
    mostrarVector(v1, "v1 después de modificar v1[0]");

    // 5. Eliminar elementos
    cout << "\n--- ELIMINAR ELEMENTOS ---" << endl;

    v1.pop_back();  // Eliminar último
    mostrarVector(v1, "v1 después de pop_back");

    v1.erase(v1.begin() + 1);  // Eliminar elemento en posición 1
    mostrarVector(v1, "v1 después de erase posición 1");

    // 6. Iteradores
    cout << "\n--- ITERADORES ---" << endl;

    vector<int> v5 = {10, 20, 30, 40, 50};
    mostrarVector(v5, "v5");

    // Iterador básico
    cout << "Usando iteradores: ";
    for (auto it = v5.begin(); it != v5.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Iterador inverso
    cout << "Iterador inverso: ";
    for (auto it = v5.rbegin(); it != v5.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 7. Algoritmos de la STL
    cout << "\n--- ALGORITMOS STL ---" << endl;

    vector<int> v6 = {64, 12, 89, 23, 45, 67, 1, 78};
    mostrarVector(v6, "v6 desordenado");

    // Ordenar
    sort(v6.begin(), v6.end());
    mostrarVector(v6, "v6 ordenado");

    // Buscar
    auto it = find(v6.begin(), v6.end(), 45);
    if (it != v6.end()) {
        cout << "45 encontrado en posición: " << (it - v6.begin()) << endl;
    }

    // Contar elementos
    int count_45 = count(v6.begin(), v6.end(), 45);
    cout << "Número de veces que aparece 45: " << count_45 << endl;

    // 8. Operaciones avanzadas
    cout << "\n--- OPERACIONES AVANZADAS ---" << endl;

    vector<int> v7 = {1, 2, 3};
    vector<int> v8 = {4, 5, 6};

    // Concatenar vectores
    v7.insert(v7.end(), v8.begin(), v8.end());
    mostrarVector(v7, "v7 + v8");

    // Redimensionar
    v7.resize(10, 99);  // Nuevo tamaño 10, rellenar con 99
    mostrarVector(v7, "v7 redimensionado");

    // Limpiar vector
    v7.clear();
    mostrarVector(v7, "v7 después de clear");

    // 9. Vectores multidimensionales
    cout << "\n--- VECTORES MULTIDIMENSIONALES ---" << endl;

    vector<vector<int>> matriz(3, vector<int>(4, 0));  // 3x4 inicializada en 0

    // Llenar matriz
    for (size_t i = 0; i < matriz.size(); i++) {
        for (size_t j = 0; j < matriz[i].size(); j++) {
            matriz[i][j] = (i + 1) * (j + 1);
        }
    }

    // Mostrar matriz
    cout << "Matriz 3x4:" << endl;
    for (const auto& fila : matriz) {
        for (int elemento : fila) {
            cout << elemento << "\t";
        }
        cout << endl;
    }

    // 10. Vectores con objetos personalizados
    cout << "\n--- VECTORES CON OBJETOS ---" << endl;

    struct Persona {
        string nombre;
        int edad;

        Persona(string n, int e) : nombre(n), edad(e) {}
    };

    vector<Persona> personas;
    personas.emplace_back("Juan", 25);
    personas.emplace_back("María", 30);
    personas.emplace_back("Pedro", 35);

    cout << "Personas:" << endl;
    for (const auto& p : personas) {
        cout << "- " << p.nombre << " (" << p.edad << " años)" << endl;
    }

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;

    return 0;
}
```

## Métodos Importantes

### Agregar Elementos
- `push_back(value)`: Agrega al final
- `insert(pos, value)`: Inserta en posición específica
- `emplace_back(args...)`: Construye elemento in-place al final
- `emplace(pos, args...)`: Construye elemento in-place en posición

### Eliminar Elementos
- `pop_back()`: Elimina el último
- `erase(pos)`: Elimina elemento en posición
- `erase(first, last)`: Elimina rango de elementos
- `clear()`: Elimina todos los elementos

### Acceso a Elementos
- `operator[]`: Acceso sin verificación
- `at(index)`: Acceso con verificación de límites
- `front()`: Primer elemento
- `back()`: Último elemento

### Información del Vector
- `size()`: Número de elementos
- `capacity()`: Espacio reservado
- `empty()`: ¿Está vacío?
- `max_size()`: Tamaño máximo posible

### Modificar Tamaño
- `resize(n)`: Cambia tamaño a n
- `resize(n, value)`: Cambia tamaño con valor por defecto
- `reserve(n)`: Reserva espacio para n elementos
- `shrink_to_fit()`: Reduce capacidad al tamaño actual

## Ventajas de Vector

### ✅ Acceso Aleatorio O(1)
- Acceso directo por índice

### ✅ Tamaño Dinámico
- Crece automáticamente según necesidad

### ✅ Eficiencia
- Almacenamiento contiguo en memoria

### ✅ Compatibilidad
- Funciona con algoritmos STL

## Desventajas

### ❌ Inserciones/Eliminaciones en Medio O(n)
- Elementos deben desplazarse

### ❌ Reubicación
- Puede requerir copias cuando crece

## Casos de Uso

### Arrays Dinámicos
```cpp
vector<int> datos;
for(int i = 0; i < 100; i++) {
    datos.push_back(i * i);
}
```

### Buffers de Datos
```cpp
vector<char> buffer;
buffer.reserve(1024);  // Reservar espacio
```

### Listas de Objetos
```cpp
vector<Persona> empleados;
empleados.emplace_back("Juan", 25);
```