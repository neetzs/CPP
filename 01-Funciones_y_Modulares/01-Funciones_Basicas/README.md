# 01 - Funciones Básicas

## Concepto Clave
Una **función** es un bloque de código reutilizable que realiza una tarea específica.

## Estructura de una Función

```cpp
tipoRetorno nombreFuncion(parametro1, parametro2) {
    // Cuerpo de la función
    return valor;  // Si tipoRetorno no es void
}
```

## Tipos de Retorno

```cpp
void miFunc();           // No retorna nada
int miFunc();            // Retorna un entero
double miFunc();         // Retorna un decimal
string miFunc();         // Retorna texto
bool miFunc();           // Retorna true/false
```

## Parámetros

```cpp
void saludar(string nombre);           // Un parámetro
void sumar(int a, int b);              // Dos parámetros
void procesar(int x, double y, bool z); // Múltiples parámetros
void hacer();                           // Sin parámetros
```

## Ejemplo Completo

```cpp
// Declaración (prototipo)
int sumar(int a, int b);

int main() {
    int resultado = sumar(5, 3);  // Llamada
    cout << resultado << endl;     // 8
    return 0;
}

// Definición
int sumar(int a, int b) {
    return a + b;
}
```

## Reglas Importantes

1. **Declarar antes de usar**: O define antes de main(), o usa un prototipo
2. **Tipo de retorno**: Coincide con lo que retorna
3. **Nombres descriptivos**: `calcularPromedio()` no `calc()`
4. **DRY**: Don't Repeat Yourself - si repites código, hazlo función
