# 02 - Constructores y Destructores

## Concepto Clave
Los **constructores** inicializan objetos cuando se crean. Los **destructores** limpian recursos cuando se destruyen.

## Tipos de Constructores

### Constructor por Defecto
```cpp
class Clase {
public:
    Clase() {  // Sin parámetros
        // Inicialización
    }
};
```

### Constructor con Parámetros
```cpp
class Clase {
public:
    Clase(int x, string s) {
        // Inicialización con parámetros
    }
};
```

### Constructor de Copia
```cpp
class Clase {
public:
    Clase(const Clase& otra) {
        // Copiar desde otra instancia
    }
};
```

### Constructor de Movimiento (C++11)
```cpp
class Clase {
public:
    Clase(Clase&& otra) noexcept {
        // Mover recursos desde otra instancia
    }
};
```

## Destructor

```cpp
class Clase {
public:
    ~Clase() {
        // Liberar recursos
        // Llamado automáticamente
    }
};
```

## Lista de Inicialización

```cpp
class Persona {
private:
    string nombre;
    int edad;
public:
    // Mejor que asignar en el cuerpo
    Persona(string n, int e) : nombre(n), edad(e) {
        // Cuerpo opcional
    }
};
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <string>
using namespace std;

class Archivo {
private:
    string nombre;
    bool abierto;

public:
    // Constructor por defecto
    Archivo() {
        nombre = "sin_nombre.txt";
        abierto = false;
        cout << "Archivo creado (defecto): " << nombre << endl;
    }

    // Constructor con parámetros
    Archivo(string n) {
        nombre = n;
        abierto = false;
        cout << "Archivo creado: " << nombre << endl;
    }

    // Constructor de copia
    Archivo(const Archivo& otro) {
        nombre = otro.nombre + "_copia";
        abierto = false;
        cout << "Archivo copiado: " << nombre << endl;
    }

    // Destructor
    ~Archivo() {
        if (abierto) {
            cerrar();
        }
        cout << "Archivo destruido: " << nombre << endl;
    }

    void abrir() {
        if (!abierto) {
            abierto = true;
            cout << "Abriendo archivo: " << nombre << endl;
        }
    }

    void cerrar() {
        if (abierto) {
            abierto = false;
            cout << "Cerrando archivo: " << nombre << endl;
        }
    }

    void escribir(string texto) {
        if (abierto) {
            cout << "Escribiendo en " << nombre << ": " << texto << endl;
        } else {
            cout << "Error: archivo no abierto" << endl;
        }
    }
};

class Contador {
private:
    static int totalObjetos;
    int id;

public:
    // Constructor
    Contador() {
        totalObjetos++;
        id = totalObjetos;
        cout << "Objeto " << id << " creado. Total: " << totalObjetos << endl;
    }

    // Constructor de copia
    Contador(const Contador& otro) {
        totalObjetos++;
        id = totalObjetos;
        cout << "Objeto " << id << " creado por copia. Total: " << totalObjetos << endl;
    }

    // Destructor
    ~Contador() {
        totalObjetos--;
        cout << "Objeto " << id << " destruido. Total: " << totalObjetos << endl;
    }

    static int obtenerTotal() {
        return totalObjetos;
    }
};

// Inicializar variable estática
int Contador::totalObjetos = 0;

void funcionConObjetos() {
    cout << "\n=== DENTRO DE FUNCIÓN ===" << endl;
    Contador c1;
    Contador c2;
    cout << "Total en función: " << Contador::obtenerTotal() << endl;
    cout << "=== SALIENDO DE FUNCIÓN ===" << endl;
}

int main() {
    cout << "=== INICIO DEL PROGRAMA ===" << endl;

    // Constructor por defecto
    Archivo archivo1;
    archivo1.abrir();
    archivo1.escribir("Hola mundo");

    // Constructor con parámetros
    Archivo archivo2("datos.txt");
    archivo2.abrir();
    archivo2.escribir("Información importante");

    // Constructor de copia
    Archivo archivo3 = archivo2;  // Copia
    archivo3.escribir("Copia de datos");

    cout << "\n=== CONTADOR DE OBJETOS ===" << endl;
    Contador contador1;
    {
        Contador contador2;
        Contador contador3;
        cout << "En el scope interno: " << Contador::obtenerTotal() << endl;
    }
    cout << "Después del scope interno: " << Contador::obtenerTotal() << endl;

    funcionConObjetos();

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;
    cout << "Los destructores se llamarán automáticamente..." << endl;

    return 0;
}
```

## Orden de Construcción/Destrucción

### Construcción
1. Clases base
2. Miembros (en orden de declaración)
3. Clase derivada

### Destrucción
1. Clase derivada
2. Miembros (orden inverso)
3. Clases base

## Reglas Importantes

1. **Constructor**: Se llama automáticamente al crear objeto
2. **Destructor**: Se llama automáticamente al destruir objeto
3. **No heredado**: Constructores/destructores no se heredan
4. **Lista de inicialización**: Preferible para inicializar miembros
5. **Excepciones**: Si constructor lanza excepción, destructor no se llama
6. **Virtual**: Destructores de clases base deben ser virtual si hay herencia

## Problemas Comunes

### Constructor que no Inicializa
```cpp
class MalaClase {
    int* ptr;
public:
    MalaClase() {
        // ptr no inicializado - undefined behavior
    }
};
```

### Destructor que no Limpia
```cpp
class MalaClase {
    int* ptr;
public:
    MalaClase() { ptr = new int(42); }
    ~MalaClase() {
        // Olvidó delete ptr - memory leak
    }
};
```