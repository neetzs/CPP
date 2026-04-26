# 02 - Paso de Parámetros

## Concepto Clave
El **paso de parámetros** determina cómo se pasan los valores a las funciones y si se pueden modificar.

## Tipos de Paso de Parámetros

### 1. **Por Valor** (Copia)
```cpp
void funcionPorValor(int x) {
    x = x + 10;  // Modifica la copia, no el original
}
```

### 2. **Por Referencia** (&)
```cpp
void funcionPorReferencia(int& x) {
    x = x + 10;  // Modifica el original
}
```

### 3. **Por Puntero** (*)
```cpp
void funcionPorPuntero(int* x) {
    *x = *x + 10;  // Modifica el original a través del puntero
}
```

## Ejemplo Completo

```cpp
#include <iostream>
using namespace std;

// Por valor - no modifica original
void incrementarValor(int num) {
    num++;
    cout << "Dentro de la función (valor): " << num << endl;
}

// Por referencia - modifica original
void incrementarReferencia(int& num) {
    num++;
    cout << "Dentro de la función (referencia): " << num << endl;
}

// Por puntero - modifica original
void incrementarPuntero(int* num) {
    (*num)++;
    cout << "Dentro de la función (puntero): " << *num << endl;
}

int main() {
    int valor = 5;
    
    cout << "Valor original: " << valor << endl;
    
    incrementarValor(valor);
    cout << "Después de función por valor: " << valor << endl;
    
    incrementarReferencia(valor);
    cout << "Después de función por referencia: " << valor << endl;
    
    incrementarPuntero(&valor);
    cout << "Después de función por puntero: " << valor << endl;
    
    return 0;
}
```

## Reglas Importantes

1. **Por valor**: Seguro, pero ineficiente para objetos grandes
2. **Por referencia**: Eficiente, permite modificación
3. **Por puntero**: Similar a referencia, pero más explícito
4. **const**: Usa `const int&` para evitar modificaciones accidentales