# 05 - Namespaces

## Concepto Clave
Los **namespaces** permiten **organizar el código** y evitar **conflictos de nombres** entre diferentes partes del programa.

## ¿Por qué Namespaces?

```cpp
// Sin namespaces - conflicto potencial
void imprimir() { cout << "Función global" << endl; }

// Con namespaces - organizado
namespace utilidades {
    void imprimir() { cout << "Utilidad" << endl; }
}

namespace matematicas {
    void imprimir() { cout << "Mates" << endl; }
}
```

## Sintaxis Básica

```cpp
// Declarar namespace
namespace miNamespace {
    int variable = 10;
    void funcion() { /* ... */ }
}

// Usar namespace
miNamespace::variable;
miNamespace::funcion();

// Usar namespace completo
using namespace miNamespace;
variable;  // Ahora accesible directamente
funcion();
```

## Ejemplo Completo

```cpp
#include <iostream>
using namespace std;

// Namespace para utilidades matemáticas
namespace matematicas {
    const double PI = 3.14159;

    double areaCirculo(double radio) {
        return PI * radio * radio;
    }

    double perimetroCirculo(double radio) {
        return 2 * PI * radio;
    }
}

// Namespace para utilidades de texto
namespace texto {
    void imprimirLinea(string mensaje) {
        cout << mensaje << endl;
    }

    string convertirMayusculas(string texto) {
        // Implementación simplificada
        for (char& c : texto) {
            c = toupper(c);
        }
        return texto;
    }
}

// Namespace anidado
namespace graficos {
    namespace formas {
        void dibujarCuadrado() {
            cout << "Dibujando cuadrado..." << endl;
        }
    }

    namespace colores {
        string ROJO = "#FF0000";
        string AZUL = "#0000FF";
    }
}

int main() {
    // Usando namespace específico
    cout << "Área del círculo: " << matematicas::areaCirculo(5) << endl;
    cout << "Perímetro del círculo: " << matematicas::perimetroCirculo(5) << endl;

    // Usando using namespace
    using namespace texto;
    imprimirLinea("Hola mundo");
    cout << convertirMayusculas("hola") << endl;

    // Namespace anidado
    graficos::formas::dibujarCuadrado();
    cout << "Color rojo: " << graficos::colores::ROJO << endl;

    return 0;
}
```

## Buenas Prácticas

### ✅ Recomendado
```cpp
// Usar using namespace solo en funciones pequeñas
void funcionPequena() {
    using namespace std;
    cout << "Hola" << endl;
}

// Preferir using específico
using std::cout;
using std::endl;

// Evitar using namespace en headers (.h)
```

### ❌ Evitar
```cpp
// No uses using namespace en archivos grandes
using namespace std;  // Puede causar conflictos

// No anides demasiado profundo
namespace a { namespace b { namespace c { /* ... */ } } }
```

## Reglas Importantes

1. **Alcance**: Los nombres dentro de un namespace no colisionan con globales
2. **Anidados**: Puedes tener namespaces dentro de otros
3. **Alias**: `namespace corto = namespace_largo;`
4. **Global**: El namespace global es el predeterminado
5. **using**: Importa nombres, pero úsalo con cuidado
6. **Headers**: Evita `using namespace` en archivos de cabecera
