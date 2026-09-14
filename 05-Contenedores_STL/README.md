# 05 - Contenedores y STL (Standard Template Library)

La **STL** es la biblioteca estándar que proporciona contenedores, iteradores y algoritmos listos para usar.

## Temas a Cubrir

### 1. **Vector**
- Arrays dinámicos
- push_back, pop_back, size
- Acceso rápido por índice

### 2. **List y Deque**
- Lista enlazada (List)
- Cola doble (Deque)
- Inserción/eliminación eficiente

### 3. **Map y Set**
- Map: pares clave-valor
- Set: conjunto de valores únicos
- Búsqueda O(log n)

### 4. **Queue y Stack**
- Queue: FIFO (primero en entrar, primero en salir)
- Stack: LIFO (último en entrar, primero en salir)

### 5. **Algoritmos STL**
- `sort()`, `find()`, `transform()`
- Iteradores
- Functional programming

## Objetivos al Finalizar

- [ ] Elegir el contenedor correcto para cada situación
- [ ] Usar iteradores efectivamente
- [ ] Aplicar algoritmos STL
- [ ] Entender complejidad: O(1), O(n), O(log n)

## Elección de Contenedor

| Contenedor | Acceso | Inserción | Búsqueda | Uso |
|-----------|--------|-----------|----------|-----|
| Vector | O(1) | O(n) | O(n) | Acceso frecuente |
| List | O(n) | O(1) | O(n) | Inserción frecuente |
| Map | O(log n) | O(log n) | O(log n) | Búsquedas frecuentes |
| Set | - | O(log n) | O(log n) | Valores únicos |

## Iteradores

Los **iteradores** son como "punteros inteligentes" para recorrer contenedores.

```cpp
vector<int> v = {1, 2, 3};
for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << endl;
}
```
