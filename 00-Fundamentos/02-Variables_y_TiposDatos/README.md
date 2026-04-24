# 02 - Variables y Tipos de Datos

## Concepto Clave
Las **variables** son espacios en memoria donde guardamos valores. Los **tipos de datos** definen qué tipo de valor pueden almacenar.

## Tipos de Datos Básicos

| Tipo | Tamaño | Rango | Ejemplo |
|------|--------|-------|---------|
| `int` | 4 bytes | -2,147,483,648 a 2,147,483,647 | `42` |
| `float` | 4 bytes | ~10⁻³⁸ a ~10³⁸ | `3.14f` |
| `double` | 8 bytes | ~10⁻³⁰⁸ a ~10³⁰⁸ | `3.14159` |
| `char` | 1 byte | -128 a 127 | `'A'` |
| `bool` | 1 byte | true/false | `true` |
| `string` | Variable | Texto | `"Hola"` |

## Declaración de Variables

```cpp
// Sintaxis básica
tipo nombre;

// Con inicialización
tipo nombre = valor;

// Múltiples variables
int a, b, c;
int x = 10, y = 20;
```

## Nombres de Variables (Reglas)

✅ **Permitido:**
- Letras (a-z, A-Z)
- Números (pero no al inicio)
- Guión bajo (_)

❌ **No permitido:**
- Espacios
- Caracteres especiales (@, #, %, etc.)
- Palabras clave (int, while, if, etc.)

## Constantes

```cpp
const tipo NOMBRE = valor;  // No se puede cambiar
```

## Scope (Alcance)

```cpp
int x = 10;  // Scope global

{
    int x = 20;  // Scope local, sombrea la global
}

// Aquí x vuelve a ser 10
```
