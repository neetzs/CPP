# 03 - Retorno de Valores

## Concepto Clave
Las funciones pueden **retornar valores** al código que las llama, permitiendo reutilizar resultados.

## Tipos de Retorno

### 1. **Tipos Primitivos**
```cpp
int sumar(int a, int b) {
    return a + b;
}

double dividir(double a, double b) {
    if (b != 0) return a / b;
    return 0;  // Error handling básico
}
```

### 2. **Retorno por Referencia**
```cpp
int& obtenerMayor(int& a, int& b) {
    return (a > b) ? a : b;
}
```

### 3. **Retorno Múltiple (usando structs/tuplas)**
```cpp
#include <tuple>

tuple<int, int> dividirYResto(int dividendo, int divisor) {
    int cociente = dividendo / divisor;
    int resto = dividendo % divisor;
    return make_tuple(cociente, resto);
}
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <tuple>
using namespace std;

// Retorno simple
int calcularCuadrado(int num) {
    return num * num;
}

// Retorno múltiple con tuple
tuple<int, int> dividirYResto(int dividendo, int divisor) {
    int cociente = dividendo / divisor;
    int resto = dividendo % divisor;
    return make_tuple(cociente, resto);
}

// Retorno por referencia (cuidado: puede ser peligroso)
int& obtenerElemento(int arr[], int indice) {
    return arr[indice];
}

int main() {
    // Retorno simple
    int numero = 5;
    int cuadrado = calcularCuadrado(numero);
    cout << numero << " al cuadrado es: " << cuadrado << endl;

    // Retorno múltiple
    auto [cociente, resto] = dividirYResto(17, 5);
    cout << "17 dividido por 5: cociente=" << cociente << ", resto=" << resto << endl;

    // Retorno por referencia
    int arreglo[] = {10, 20, 30};
    obtenerElemento(arreglo, 1) = 25;  // Modifica el arreglo
    cout << "Arreglo modificado: " << arreglo[0] << ", " << arreglo[1] << ", " << arreglo[2] << endl;

    return 0;
}
```

## Reglas Importantes

1. **Tipo de retorno**: Debe coincidir con lo que retorna la función
2. **void**: Para funciones que no retornan nada
3. **Retorno temprano**: Usa `return` para salir antes si es necesario
4. **Referencias**: Cuidado con retornar referencias a variables locales (undefined behavior)