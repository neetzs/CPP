# 04 - Recursión

## Concepto Clave
La **recursión** es cuando una función se **llama a sí misma** para resolver un problema dividiéndolo en subproblemas más pequeños.

## Elementos de una Función Recursiva

### 1. **Caso Base**
Condición que detiene la recursión para evitar un loop infinito.

### 2. **Caso Recursivo**
Parte donde la función se llama a sí misma con un problema más pequeño.

### 3. **Convergencia**
Cada llamada recursiva debe acercarse al caso base.

## Ejemplos Clásicos

### Factorial
```cpp
int factorial(int n) {
    if (n <= 1) return 1;  // Caso base
    return n * factorial(n - 1);  // Caso recursivo
}
```

### Fibonacci
```cpp
int fibonacci(int n) {
    if (n <= 1) return n;  // Caso base
    return fibonacci(n - 1) + fibonacci(n - 2);  // Caso recursivo
}
```

### Suma de Array
```cpp
int sumaArray(int arr[], int n) {
    if (n <= 0) return 0;  // Caso base
    return arr[n-1] + sumaArray(arr, n-1);  // Caso recursivo
}
```

## Ejemplo Completo

```cpp
#include <iostream>
using namespace std;

// Factorial recursivo
int factorial(int n) {
    if (n <= 1) {
        cout << "Caso base: factorial(" << n << ") = 1" << endl;
        return 1;
    }
    cout << "Llamando factorial(" << n-1 << ")" << endl;
    int resultado = n * factorial(n - 1);
    cout << "Resultado factorial(" << n << ") = " << resultado << endl;
    return resultado;
}

// Fibonacci recursivo
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Potencia recursiva
int potencia(int base, int exponente) {
    if (exponente == 0) return 1;
    return base * potencia(base, exponente - 1);
}

int main() {
    cout << "=== FACTORIAL ===" << endl;
    cout << "5! = " << factorial(5) << endl;

    cout << "\n=== FIBONACCI ===" << endl;
    cout << "Fibonacci de 8: ";
    for (int i = 0; i <= 8; i++) {
        cout << fibonacci(i) << " ";
    }
    cout << endl;

    cout << "\n=== POTENCIA ===" << endl;
    cout << "2^5 = " << potencia(2, 5) << endl;

}
```

## Ventajas y Desventajas

### ✅ Ventajas
- Código más elegante y fácil de entender
- Divide problemas complejos en simples
- Útil para estructuras de datos recursivas (árboles, grafos)

### ❌ Desventajas
- Mayor uso de memoria (stack)
- Puede ser más lento que iterativo
- Riesgo de stack overflow para recursiones profundas
- A veces más difícil de debuggear

## Reglas Importantes

1. **Siempre un caso base** para evitar recursión infinita
2. **Convergencia**: Cada llamada debe acercarse al caso base
3. **Eficiencia**: Considera si la iteración es mejor para casos grandes
4. **Stack overflow**: Limita la profundidad de recursión
