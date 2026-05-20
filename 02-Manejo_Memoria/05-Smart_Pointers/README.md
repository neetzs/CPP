# 05 - Smart Pointers

## Concepto Clave
Los **Smart Pointers** son clases que **envuelven punteros** y gestionan automáticamente la memoria, previniendo leaks y errores.

## Tipos de Smart Pointers

### `unique_ptr` - Propiedad Exclusiva
```cpp
#include <memory>

std::unique_ptr<int> ptr = std::make_unique<int>(42);
// Solo un unique_ptr puede apuntar a ese int
// Se libera automáticamente cuando sale del scope
```

### `shared_ptr` - Propiedad Compartida
```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
std::shared_ptr<int> ptr2 = ptr1;  // Ambos apuntan al mismo int
// Se libera cuando el último shared_ptr se destruye
```

### `weak_ptr` - Referencia Débil
```cpp
std::weak_ptr<int> weak = sharedPtr;
// No mantiene vivo el objeto, solo observa
```

## Ventajas sobre Punteros Crudos

### ✅ Automático
- Liberación automática de memoria
- No memory leaks
- Excepciones seguras

### ✅ Seguro
- No dangling pointers
- No double delete
- Propiedad clara

### ✅ Moderno
- C++11 y superior
- Mejor rendimiento que GC
- RAII (Resource Acquisition Is Initialization)

## Ejemplo Completo

```cpp
#include <iostream>
#include <memory>
using namespace std;

class Objeto {
public:
    string nombre;
    Objeto(string n) : nombre(n) {
        cout << "Creando " << nombre << endl;
    }
    ~Objeto() {
        cout << "Destruyendo " << nombre << endl;
    }
    void saludar() {
        cout << "Hola, soy " << nombre << endl;
    }
};

void funcionConUniquePtr(unique_ptr<Objeto> obj) {
    obj->saludar();
    // obj se libera automáticamente al salir
}

void funcionConSharedPtr(shared_ptr<Objeto> obj) {
    cout << "Contador de referencias: " << obj.use_count() << endl;
    obj->saludar();
}

int main() {
    cout << "=== UNIQUE_PTR ===" << endl;
    {
        unique_ptr<Objeto> unico = make_unique<Objeto>("Único");
        unico->saludar();
        // Transferir propiedad
        funcionConUniquePtr(move(unico));
        // unico ahora es nullptr
    } // Objeto se libera aquí

    cout << "\n=== SHARED_PTR ===" << endl;
    {
        shared_ptr<Objeto> compartido1 = make_shared<Objeto>("Compartido");
        cout << "Contador inicial: " << compartido1.use_count() << endl;

        {
            shared_ptr<Objeto> compartido2 = compartido1;
            cout << "Después de copiar: " << compartido1.use_count() << endl;

            funcionConSharedPtr(compartido2);
        } // compartido2 se libera, contador baja

        cout << "Después del scope interno: " << compartido1.use_count() << endl;
    } // Objeto se libera aquí

    cout << "\n=== ARRAYS CON SMART POINTERS ===" << endl;
    {
        unique_ptr<int[]> arr = make_unique<int[]>(5);
        for (int i = 0; i < 5; i++) {
            arr[i] = i * 10;
            cout << "arr[" << i << "] = " << arr[i] << endl;
        }
    } // Array se libera automáticamente

    cout << "\n=== CUSTOM DELETER ===" << endl;
    {
        auto deleter = [](int* ptr) {
            cout << "Liberando memoria personalizada" << endl;
            delete ptr;
        };

        unique_ptr<int, decltype(deleter)> ptrPersonalizado(new int(100), deleter);
        cout << "Valor: " << *ptrPersonalizado << endl;
    } // Se llama al deleter personalizado

}
```

## Patrones de Uso

### Factory Functions
```cpp
class Producto {
public:
    static unique_ptr<Producto> crear() {
        return make_unique<Producto>();
    }
    static shared_ptr<Producto> crearCompartido() {
        return make_shared<Producto>();
    }
};
```

### Pimpl Idiom
```cpp
class Widget {
private:
    struct Impl;
    unique_ptr<Impl> pimpl;
};
```

### Contenedores
```cpp
vector<unique_ptr<Objeto>> objetos;
objetos.push_back(make_unique<Objeto>());
```

## Reglas Importantes

1. **Prefer unique_ptr**: Usa `unique_ptr` por defecto
2. **shared_ptr solo cuando necesario**: Para propiedad compartida real
3. **make_ functions**: Usa `make_unique` y `make_shared`
4. **No mezclar**: No mezcles smart pointers con punteros crudos
5. **Move semantics**: Usa `std::move` para transferir unique_ptr
6. **Ciclos**: Evita ciclos de referencias con shared_ptr (usa weak_ptr)

## Migración desde Punteros Crudos

### ❌ Antes (Problemático)
```cpp
void funcion() {
    Objeto* ptr = new Objeto();
    // ... usar ptr ...
    // Olvidé delete ptr;  // Memory leak!
}
```

### ✅ Después (Seguro)
```cpp
void funcion() {
    auto ptr = make_unique<Objeto>();
    // ... usar ptr ...
} // Se libera automáticamente
```
