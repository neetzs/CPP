# 03 - Operadores

## Concepto Clave
Los **operadores** son símbolos que realizan operaciones con valores.

## Tipos de Operadores

### 1. Operadores Aritméticos
| Operador | Significado | Ejemplo |
|----------|-------------|---------|
| `+` | Suma | `10 + 5 = 15` |
| `-` | Resta | `10 - 5 = 5` |
| `*` | Multiplicación | `10 * 5 = 50` |
| `/` | División | `10 / 5 = 2` |
| `%` | Módulo (residuo) | `10 % 3 = 1` |

### 2. Operadores de Comparación
| Operador | Significado |
|----------|-------------|
| `==` | Igual a |
| `!=` | Diferente a |
| `<` | Menor que |
| `>` | Mayor que |
| `<=` | Menor o igual |
| `>=` | Mayor o igual |

**Resultado:** `true` (1) o `false` (0)

### 3. Operadores Lógicos
| Operador | Significado | Ejemplo |
|----------|-------------|---------|
| `&&` | AND (y) | `a > 5 && b < 10` |
| `\|\|` | OR (o) | `a > 5 \|\| b < 10` |
| `!` | NOT (no) | `!(a > 5)` |

### 4. Operadores de Asignación
| Operador | Equivale a |
|----------|-----------|
| `=` | Asigna |
| `+=` | `a = a + b` |
| `-=` | `a = a - b` |
| `*=` | `a = a * b` |
| `/=` | `a = a / b` |
| `%=` | `a = a % b` |

### 5. Operadores de Incremento/Decremento
| Operador | Significado |
|----------|-------------|
| `++` | Suma 1 |
| `--` | Resta 1 |

```cpp
int x = 5;
x++;   // x ahora es 6
x--;   // x ahora es 5
```

## Precedencia de Operadores

1. `()` - Paréntesis
2. `++`, `--` - Incremento/Decremento
3. `*`, `/`, `%` - Multiplicación, División, Módulo
4. `+`, `-` - Suma, Resta
5. `<`, `>`, `<=`, `>=` - Comparación
6. `==`, `!=` - Igualdad
7. `&&` - AND lógico
8. `||` - OR lógico
9. `=`, `+=`, `-=`, etc. - Asignación

## Consejo
Usa paréntesis para evitar confusiones:
```cpp
// Mejor:
resultado = (a + b) * c;

// Que:
resultado = a + b * c;
```
