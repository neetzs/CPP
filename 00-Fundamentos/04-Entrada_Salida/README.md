# 04 - Entrada y Salida

## Concepto Clave
**Entrada**: Leer datos desde el teclado (usuario)
**Salida**: Mostrar datos en pantalla

## cout - Salida

```cpp
cout << "Texto";           // Escribe texto
cout << 42;                // Escribe número
cout << 3.14;              // Escribe decimal
cout << endl;              // Salta de línea
cout << "\n";              // También salta de línea
```

### Encadenamiento

```cpp
cout << "Hola " << nombre << ", tienes " << edad << " años" << endl;
```

## cin - Entrada

```cpp
int numero;
cin >> numero;             // Lee un entero

string nombre;
cin >> nombre;             // Lee una palabra (hasta espacio)

double precio;
cin >> precio;             // Lee un decimal
```

## getline() - Lectura de Línea Completa

```cpp
string frase;
getline(cin, frase);       // Lee la línea completa incluyendo espacios
```

## Diferencia: cin >> vs getline()

| `cin >> nombre` | `getline(cin, nombre)` |
|---|---|
| Lee hasta el primer espacio | Lee la línea completa |
| Ejemplo: "Juan Pérez" → lee "Juan" | Lee "Juan Pérez" |
| Mejor para números | Mejor para texto con espacios |

## Formatos de Salida

```cpp
#include <iomanip>

cout << fixed << setprecision(2) << 3.14159;  // 3.14
cout << setw(10) << numero;                   // Ancho de 10
```
