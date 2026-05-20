# 04 - Referencias

## Concepto Clave
Una **referencia** es un **alias** para una variable existente. Es más segura y fácil de usar que los punteros.

## ¿Qué es una Referencia?

```cpp
int x = 10;
int& ref = x;  // ref es un alias de x

ref = 20;      // Cambia x a 20
cout << x;     // Imprime 20
```

## Diferencias con Punteros

| Aspecto | Referencia | Puntero |
|---------|------------|---------|
| Sintaxis | `int& ref = x;` | `int* ptr = &x;` |
| Acceso | `ref` | `*ptr` |
| Reasignación | ❌ No se puede | ✅ Sí |
| Null | ❌ No puede ser null | ✅ Puede ser nullptr |
| Inicialización | ✅ Obligatoria | ❌ Opcional |

## Tipos de Referencias

### Referencias Lvalue
```cpp
int x = 10;
int& ref = x;  // Referencia a variable
```

### Referencias Rvalue (C++11)
```cpp
int&& rref = 10;  // Referencia a temporal
```

### Referencias Constantes
```cpp
const int& ref = 10;  // No se puede modificar
```

## Parámetros por Referencia

```cpp
// Por valor - copia (lento para objetos grandes)
void funcionPorValor(ObjetoGrande obj) {
    // Modifica copia
}

// Por referencia - modifica original
void funcionPorReferencia(ObjetoGrande& obj) {
    obj.modificar();  // Modifica original
}

// Por referencia constante - solo lectura
void funcionPorRefConst(const ObjetoGrande& obj) {
    // Solo puede leer, no modificar
}
```

## Retorno por Referencia

```cpp
int& obtenerMayor(int& a, int& b) {
    return (a > b) ? a : b;
}

// Uso:
int x = 10, y = 20;
obtenerMayor(x, y) = 30;  // Cambia y a 30
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <string>
using namespace std;

class Persona {
public:
    string nombre;
    int edad;

    Persona(string n, int e) : nombre(n), edad(e) {}
};

// Función que modifica por referencia
void envejecer(Persona& persona, int anos) {
    persona.edad += anos;
    cout << persona.nombre << " ahora tiene " << persona.edad << " años" << endl;
}

// Función que no modifica (referencia constante)
void mostrarPersona(const Persona& persona) {
    cout << "Nombre: " << persona.nombre << endl;
    cout << "Edad: " << persona.edad << endl;
}

// Retorno por referencia
int& obtenerElemento(int arr[], int indice) {
    return arr[indice];
}

// Función con parámetros mixtos
void procesarDatos(int valor, int& referencia, const int& constante) {
    cout << "Valor original: " << valor << endl;
    cout << "Referencia original: " << referencia << endl;
    cout << "Constante: " << constante << endl;

    valor = 100;      // Solo cambia la copia
    referencia = 200; // Cambia el original
    // constante = 300; // Error: no se puede modificar
}

int main() {
    cout << "=== REFERENCIAS BÁSICAS ===" << endl;
    int x = 10;
    int& refX = x;

    cout << "x: " << x << ", refX: " << refX << endl;
    refX = 20;
    cout << "Después de cambiar refX: x = " << x << endl;

    cout << "\n=== REFERENCIAS CON OBJETOS ===" << endl;
    Persona juan("Juan", 25);
    envejecer(juan, 5);
    mostrarPersona(juan);

    cout << "\n=== RETORNO POR REFERENCIA ===" << endl;
    int arreglo[] = {1, 2, 3, 4, 5};
    obtenerElemento(arreglo, 2) = 99;
    cout << "Arreglo modificado: ";
    for (int i = 0; i < 5; i++) {
        cout << arreglo[i] << " ";
    }
    cout << endl;

    cout << "\n=== PARÁMETROS MIXTOS ===" << endl;
    int a = 1, b = 2, c = 3;
    procesarDatos(a, b, c);
    cout << "Después de procesarDatos:" << endl;
    cout << "a: " << a << " (copia, no cambió)" << endl;
    cout << "b: " << b << " (referencia, cambió)" << endl;
    cout << "c: " << c << " (constante)" << endl;

}
```

## Ventajas de las Referencias

### ✅ Ventajas
- Sintaxis más simple que punteros
- No pueden ser null (más seguras)
- No requieren desreferencia explícita
- Más eficientes para objetos grandes

### ❌ Limitaciones
- No se pueden reasignar
- Deben inicializarse al declarar
- No pueden apuntar a null

## Reglas Importantes

1. **Inicialización**: Siempre se deben inicializar
2. **No null**: No pueden ser nullptr
3. **No reasignar**: Una vez asignadas, no cambian
4. **Parámetros**: Usa `const T&` para evitar modificaciones accidentales
5. **Retorno**: Cuidado con referencias a locales (undefined behavior)
6. **Eficiencia**: Mejor que punteros para parámetros de función