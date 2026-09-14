# 05 - Algoritmos STL

## Concepto Clave
Los algoritmos STL son funciones genéricas que operan sobre rangos de elementos definidos por iteradores. Proporcionan operaciones comunes como búsqueda, ordenamiento, transformación, etc.

## Categorías de Algoritmos

### Algoritmos No Modificadores
- No alteran los elementos del rango
- `find`, `count`, `equal`, `search`

### Algoritmos Modificadores
- Pueden alterar elementos o su orden
- `copy`, `fill`, `transform`, `replace`

### Algoritmos de Ordenamiento
- Ordenan elementos en rangos
- `sort`, `stable_sort`, `partial_sort`

### Algoritmos Numéricos
- Operaciones matemáticas
- `accumulate`, `inner_product`, `adjacent_difference`

## Sintaxis Básica

```cpp
#include <algorithm>
#include <numeric>  // Para algoritmos numéricos

vector<int> v = {3, 1, 4, 1, 5};

// Algoritmos no modificadores
auto it = find(v.begin(), v.end(), 4);        // Buscar elemento
int count = count(v.begin(), v.end(), 1);     // Contar ocurrencias

// Algoritmos modificadores
sort(v.begin(), v.end());                     // Ordenar
reverse(v.begin(), v.end());                  // Invertir orden

// Algoritmos numéricos
int suma = accumulate(v.begin(), v.end(), 0); // Suma de elementos
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>
using namespace std;

template<typename T>
void mostrarContenedor(const T& cont, const string& nombre) {
    cout << nombre << ": ";
    for (const auto& elemento : cont) {
        cout << elemento << " ";
    }
    cout << endl;
}

bool esPar(int n) { return n % 2 == 0; }
bool esImpar(int n) { return n % 2 != 0; }

int main() {
    cout << "=== ALGORITMOS STL EN C++ ===" << endl;

    vector<int> v1 = {64, 12, 89, 23, 45, 67, 1, 78, 34, 56};
    vector<int> v2 = {10, 20, 30, 40, 50};
    vector<int> v3;

    mostrarContenedor(v1, "v1 original");
    mostrarContenedor(v2, "v2 original");

    // 1. ALGORITMOS NO MODIFICADORES
    cout << "\n--- ALGORITMOS NO MODIFICADORES ---" << endl;

    // find - Buscar elemento
    auto it = find(v1.begin(), v1.end(), 45);
    if (it != v1.end()) {
        cout << "45 encontrado en posición: " << (it - v1.begin()) << endl;
    } else {
        cout << "45 no encontrado" << endl;
    }

    // find_if - Buscar con condición
    auto it_par = find_if(v1.begin(), v1.end(), esPar);
    if (it_par != v1.end()) {
        cout << "Primer número par encontrado: " << *it_par << endl;
    }

    // count - Contar ocurrencias
    int count_1 = count(v1.begin(), v1.end(), 1);
    cout << "Número de veces que aparece 1: " << count_1 << endl;

    // count_if - Contar con condición
    int count_pares = count_if(v1.begin(), v1.end(), esPar);
    cout << "Número de elementos pares: " << count_pares << endl;

    // equal - Comparar rangos
    vector<int> v1_primeros = {64, 12, 89};
    vector<int> v2_comparar = {64, 12, 89};
    bool son_iguales = equal(v1_primeros.begin(), v1_primeros.end(), v2_comparar.begin());
    cout << "Los primeros 3 elementos de v1 y v2_comparar son " <<
         (son_iguales ? "iguales" : "diferentes") << endl;

    // search - Buscar subsecuencia
    vector<int> patron = {23, 45, 67};
    auto it_sub = search(v1.begin(), v1.end(), patron.begin(), patron.end());
    if (it_sub != v1.end()) {
        cout << "Patrón {23, 45, 67} encontrado empezando en posición: " <<
             (it_sub - v1.begin()) << endl;
    }

    // 2. ALGORITMOS MODIFICADORES
    cout << "\n--- ALGORITMOS MODIFICADORES ---" << endl;

    // copy - Copiar elementos
    copy(v1.begin(), v1.end(), back_inserter(v3));
    mostrarContenedor(v3, "v3 después de copy desde v1");

    // fill - Llenar con valor
    fill(v3.begin(), v3.end(), 99);
    mostrarContenedor(v3, "v3 después de fill(99)");

    // transform - Transformar elementos
    vector<int> v4(v1.size());
    transform(v1.begin(), v1.end(), v4.begin(), [](int x) { return x * 2; });
    mostrarContenedor(v4, "v4 (v1 multiplicado por 2)");

    // replace - Reemplazar valores
    vector<int> v5 = v1;
    replace(v5.begin(), v5.end(), 1, 100);
    mostrarContenedor(v5, "v5 (1 reemplazado por 100)");

    // replace_if - Reemplazar con condición
    vector<int> v6 = v1;
    replace_if(v6.begin(), v6.end(), esPar, 0);
    mostrarContenedor(v6, "v6 (pares reemplazados por 0)");

    // remove - Eliminar elementos (no cambia tamaño)
    vector<int> v7 = v1;
    auto new_end = remove(v7.begin(), v7.end(), 1);
    v7.erase(new_end, v7.end());  // Necesario para cambiar tamaño
    mostrarContenedor(v7, "v7 después de remove(1) y erase");

    // unique - Eliminar duplicados consecutivos
    vector<int> v8 = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    mostrarContenedor(v8, "v8 con duplicados");
    auto unique_end = unique(v8.begin(), v8.end());
    v8.erase(unique_end, v8.end());
    mostrarContenedor(v8, "v8 después de unique");

    // 3. ALGORITMOS DE ORDENAMIENTO
    cout << "\n--- ALGORITMOS DE ORDENAMIENTO ---" << endl;

    vector<int> v9 = v1;  // Copia para no modificar original
    mostrarContenedor(v9, "v9 antes de ordenar");

    // sort - Ordenar ascendente
    sort(v9.begin(), v9.end());
    mostrarContenedor(v9, "v9 ordenado ascendente");

    // sort con orden descendente
    sort(v9.rbegin(), v9.rend());
    mostrarContenedor(v9, "v9 ordenado descendente");

    // stable_sort - Ordenar manteniendo orden relativo
    vector<pair<int, int>> v10 = {{3, 1}, {1, 2}, {3, 3}, {1, 4}};
    cout << "v10 antes de stable_sort: ";
    for (auto& p : v10) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;

    stable_sort(v10.begin(), v10.end());
    cout << "v10 después de stable_sort: ";
    for (auto& p : v10) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;

    // partial_sort - Ordenar parcialmente
    vector<int> v11 = v1;
    partial_sort(v11.begin(), v11.begin() + 3, v11.end());
    mostrarContenedor(v11, "v11 partial_sort (primeros 3 ordenados)");

    // nth_element - Poner n-ésimo elemento en su posición correcta
    vector<int> v12 = v1;
    nth_element(v12.begin(), v12.begin() + 2, v12.end());
    cout << "v12 después de nth_element (posición 2): ";
    for (size_t i = 0; i < v12.size(); i++) {
        if (i == 2) cout << "[" << v12[i] << "] ";
        else cout << v12[i] << " ";
    }
    cout << endl;

    // 4. ALGORITMOS NUMÉRICOS (<numeric>)
    cout << "\n--- ALGORITMOS NUMÉRICOS ---" << endl;

    // accumulate - Suma de elementos
    int suma = accumulate(v1.begin(), v1.end(), 0);
    cout << "Suma de elementos de v1: " << suma << endl;

    // accumulate con multiplicación
    int producto = accumulate(v1.begin(), v1.end(), 1, multiplies<int>());
    cout << "Producto de elementos de v1: " << producto << endl;

    // inner_product - Producto interno
    vector<int> a = {1, 2, 3};
    vector<int> b = {4, 5, 6};
    int producto_interno = inner_product(a.begin(), a.end(), b.begin(), 0);
    cout << "Producto interno de {1,2,3} y {4,5,6}: " << producto_interno << endl;

    // adjacent_difference - Diferencias adyacentes
    vector<int> v13 = {1, 3, 6, 10, 15};
    vector<int> diferencias(v13.size());
    adjacent_difference(v13.begin(), v13.end(), diferencias.begin());
    mostrarContenedor(diferencias, "Diferencias adyacentes de v13");

    // partial_sum - Sumas parciales
    vector<int> sumas_parciales(v13.size());
    partial_sum(v13.begin(), v13.end(), sumas_parciales.begin());
    mostrarContenedor(sumas_parciales, "Sumas parciales de v13");

    // 5. ALGORITMOS CON FUNCIONES PERSONALIZADAS
    cout << "\n--- ALGORITMOS CON FUNCIONES PERSONALIZADAS ---" << endl;

    // sort con función de comparación personalizada
    vector<int> v14 = v1;
    sort(v14.begin(), v14.end(), greater<int>());
    mostrarContenedor(v14, "v14 ordenado descendente con greater<>");

    // find_if con lambda
    auto it_lambda = find_if(v1.begin(), v1.end(), [](int x) { return x > 50; });
    if (it_lambda != v1.end()) {
        cout << "Primer elemento > 50: " << *it_lambda << endl;
    }

    // transform con lambda
    vector<int> v15(v1.size());
    transform(v1.begin(), v1.end(), v15.begin(), [](int x) { return x * x; });
    mostrarContenedor(v15, "v15 (cuadrados de v1)");

    // 6. ALGORITMOS DE PARTICIÓN
    cout << "\n--- ALGORITMOS DE PARTICIÓN ---" << endl;

    vector<int> v16 = v1;
    mostrarContenedor(v16, "v16 antes de partición");

    // partition - Particionar según condición
    auto particion = partition(v16.begin(), v16.end(), esPar);
    cout << "v16 después de partition (pares primero): ";
    for (auto it = v16.begin(); it != particion; ++it) cout << *it << " ";
    cout << "| ";
    for (auto it = particion; it != v16.end(); ++it) cout << *it << " ";
    cout << endl;

    // stable_partition - Partición estable
    vector<int> v17 = v1;
    stable_partition(v17.begin(), v17.end(), esImpar);
    mostrarContenedor(v17, "v17 stable_partition (impares primero, orden estable)");

    // 7. ALGORITMOS DE BÚSQUEDA AVANZADA
    cout << "\n--- ALGORITMOS DE BÚSQUEDA AVANZADA ---" << endl;

    vector<int> v18 = {1, 2, 3, 4, 5, 2, 3, 6};
    vector<int> patron2 = {2, 3};

    // search con predicado
    auto it_search = search(v18.begin(), v18.end(), patron2.begin(), patron2.end());
    if (it_search != v18.end()) {
        cout << "Patrón {2, 3} encontrado en v18 en posición: " <<
             (it_search - v18.begin()) << endl;
    }

    // find_first_of - Buscar cualquiera de un conjunto
    vector<int> buscar = {1, 3, 5};
    auto it_first_of = find_first_of(v18.begin(), v18.end(), buscar.begin(), buscar.end());
    if (it_first_of != v18.end()) {
        cout << "Primer elemento de {1,3,5} encontrado en v18: " << *it_first_of <<
             " en posición " << (it_first_of - v18.begin()) << endl;
    }

    // find_end - Última ocurrencia de subsecuencia
    auto it_end = find_end(v18.begin(), v18.end(), patron2.begin(), patron2.end());
    if (it_end != v18.end()) {
        cout << "Última ocurrencia de {2, 3} en v18 en posición: " <<
             (it_end - v18.begin()) << endl;
    }

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;

    return 0;
}
```

## Algoritmos No Modificadores

### Búsqueda
- `find(first, last, value)`: Busca elemento
- `find_if(first, last, pred)`: Busca con predicado
- `find_first_of(first, last, s_first, s_last)`: Busca cualquiera de un conjunto
- `adjacent_find(first, last)`: Busca elementos adyacentes iguales

### Conteo
- `count(first, last, value)`: Cuenta ocurrencias
- `count_if(first, last, pred)`: Cuenta con condición

### Comparación
- `equal(first, last, other_first)`: Compara rangos
- `mismatch(first, last, other_first)`: Encuentra primera diferencia

### Búsqueda de Subsecuencias
- `search(first, last, s_first, s_last)`: Busca subsecuencia
- `find_end(first, last, s_first, s_last)`: Última ocurrencia
- `search_n(first, last, count, value)`: Busca n ocurrencias consecutivas

## Algoritmos Modificadores

### Copia y Movimiento
- `copy(first, last, result)`: Copia elementos
- `copy_if(first, last, result, pred)`: Copia con condición
- `move(first, last, result)`: Mueve elementos
- `swap_ranges(first, last, other_first)`: Intercambia rangos

### Relleno
- `fill(first, last, value)`: Llena con valor
- `fill_n(first, n, value)`: Llena n elementos
- `generate(first, last, gen)`: Llena con generador

### Reemplazo
- `replace(first, last, old_val, new_val)`: Reemplaza valores
- `replace_if(first, last, pred, new_val)`: Reemplaza con condición
- `replace_copy(first, last, result, old_val, new_val)`: Reemplaza copiando

### Eliminación
- `remove(first, last, value)`: Elimina elementos
- `remove_if(first, last, pred)`: Elimina con condición
- `unique(first, last)`: Elimina duplicados consecutivos

### Transformación
- `transform(first, last, result, op)`: Transforma elementos
- `transform(first1, last1, first2, result, op)`: Transforma dos rangos

## Algoritmos de Ordenamiento

### Ordenamiento Completo
- `sort(first, last)`: Ordena rápido
- `stable_sort(first, last)`: Ordena manteniendo estabilidad
- `partial_sort(first, middle, last)`: Ordena parcialmente

### Otras Operaciones de Orden
- `nth_element(first, nth, last)`: Posiciona n-ésimo elemento
- `partition(first, last, pred)`: Particiona según predicado
- `stable_partition(first, last, pred)`: Partición estable

## Algoritmos Numéricos

### Acumuladores
- `accumulate(first, last, init)`: Suma elementos
- `accumulate(first, last, init, op)`: Acumulador con operación

### Productos
- `inner_product(first1, last1, first2, init)`: Producto interno
- `partial_sum(first, last, result)`: Sumas parciales
- `adjacent_difference(first, last, result)`: Diferencias adyacentes

## Funciones de Ayuda

### Iteradores de Inserción
```cpp
back_inserter(contenedor)  // Inserta al final
front_inserter(contenedor) // Inserta al inicio
inserter(contenedor, pos)  // Inserta en posición
```

### Funciones de Comparación
```cpp
less<T>()      // <
greater<T>()   // >
equal_to<T>()  // ==
not_equal_to<T>() // !=
```

## Casos de Uso

### Procesamiento de Datos
```cpp
vector<int> datos = {3, 1, 4, 1, 5};

// Encontrar máximo
auto max_it = max_element(datos.begin(), datos.end());

// Filtrar y transformar
vector<int> pares;
copy_if(datos.begin(), datos.end(), back_inserter(pares), esPar);
transform(pares.begin(), pares.end(), pares.begin(), [](int x) { return x * 2; });
```

### Análisis Estadístico
```cpp
vector<double> valores = {1.5, 2.3, 4.7, 3.1, 2.8};

// Calcular promedio
double suma = accumulate(valores.begin(), valores.end(), 0.0);
double promedio = suma / valores.size();

// Encontrar mediana
vector<double> temp = valores;
nth_element(temp.begin(), temp.begin() + temp.size()/2, temp.end());
double mediana = temp[temp.size()/2];
```

### Manipulación de Texto
```cpp
string texto = "Hola Mundo Cruel";

// Convertir a mayúsculas
transform(texto.begin(), texto.end(), texto.begin(), ::toupper);

// Contar palabras
auto espacios = count(texto.begin(), texto.end(), ' ');
int num_palabras = espacios + 1;
```