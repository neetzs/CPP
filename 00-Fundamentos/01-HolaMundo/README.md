# 01 - Hola Mundo

## Objetivos
- Crear tu primer programa C++
- Entender la estructura básica
- Compilar y ejecutar

## Concepto Clave
`main()` es la función por donde SIEMPRE comienza la ejecución de un programa C++.

## Estructura Básica

```cpp
#include <iostream>  // Librería para entrada/salida

using namespace std; // Para no escribir std:: todo el tiempo

int main() {         // Función principal, OBLIGATORIA
    cout << "Hola Mundo"; // Salida
    return 0;        // El programa termina exitosamente
}
```

## Explicación Línea por Línea

| Línea | Significado |
|-------|-------------|
| `#include <iostream>` | Incluye la librería para cin/cout |
| `using namespace std;` | Usa el namespace estándar |
| `int main()` | Función principal, retorna entero |
| `cout << "texto"` | Envía texto a la salida |
| `return 0;` | Termina el programa con éxito |

## 📝 Notas Importantes

1. Los saltos de línea puedes hacerlos con `\n` o `endl`
2. `cout` siempre va después de `<<`
3. Las comillas deben ser rectas: `"texto"` no `"texto"`
