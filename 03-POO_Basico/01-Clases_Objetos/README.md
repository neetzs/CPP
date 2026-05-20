# 01 - Clases y Objetos

## Concepto Clave
Una **clase** es una plantilla para crear **objetos**. Los objetos son instancias de clases con **estado** (atributos) y **comportamiento** (métodos).

## Definición de Clase

```cpp
class NombreClase {
private:    // Acceso solo desde la clase
    // Atributos (datos)
    tipo atributo1;
    tipo atributo2;

public:     // Acceso desde cualquier lugar
    // Métodos (funciones)
    tipo metodo1();
    tipo metodo2();
};
```

## Creación de Objetos

```cpp
// Declaración
NombreClase objeto1;

// Con constructor
NombreClase objeto2(parametros);

// En heap
NombreClase* ptrObjeto = new NombreClase();
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <string>
using namespace std;

class Persona {
private:
    string nombre;
    int edad;
    string profesion;

public:
    // Constructor
    Persona(string n, int e, string p) {
        nombre = n;
        edad = e;
        profesion = p;
    }

    // Métodos
    void presentarse() {
        cout << "Hola, soy " << nombre << ", tengo " << edad
             << " años y soy " << profesion << endl;
    }

    void cumplirAnios() {
        edad++;
        cout << nombre << " ahora tiene " << edad << " años" << endl;
    }

    void cambiarProfesion(string nuevaProfesion) {
        profesion = nuevaProfesion;
        cout << nombre << " ahora es " << profesion << endl;
    }

    // Getters
    string obtenerNombre() {
        return nombre;
    }

    int obtenerEdad() {
        return edad;
    }
};

class Coche {
private:
    string marca;
    string modelo;
    int ano;
    bool encendido;

public:
    Coche(string m, string mod, int a) {
        marca = m;
        modelo = mod;
        ano = a;
        encendido = false;
    }

    void encender() {
        if (!encendido) {
            encendido = true;
            cout << marca << " " << modelo << " encendido" << endl;
        } else {
            cout << "El coche ya está encendido" << endl;
        }
    }

    void apagar() {
        if (encendido) {
            encendido = false;
            cout << marca << " " << modelo << " apagado" << endl;
        } else {
            cout << "El coche ya está apagado" << endl;
        }
    }

    void tocarBocina() {
        if (encendido) {
            cout << "¡BIP BIP!" << endl;
        } else {
            cout << "El coche está apagado, no se puede tocar la bocina" << endl;
        }
    }

    void mostrarInfo() {
        cout << "Coche: " << marca << " " << modelo << " (" << ano << ")" << endl;
        cout << "Estado: " << (encendido ? "Encendido" : "Apagado") << endl;
    }
};

int main() {
    cout << "=== OBJETOS PERSONA ===" << endl;

    // Crear objetos Persona
    Persona juan("Juan", 25, "Ingeniero");
    Persona maria("María", 30, "Doctora");

    juan.presentarse();
    maria.presentarse();

    juan.cumplirAnios();
    maria.cambiarProfesion("Cirujana");

    cout << "\n=== OBJETOS COCHE ===" << endl;

    // Crear objetos Coche
    Coche miCoche("Toyota", "Corolla", 2020);
    Coche cocheAmigo("Honda", "Civic", 2019);

    miCoche.mostrarInfo();
    miCoche.encender();
    miCoche.tocarBocina();
    miCoche.apagar();

    cout << "\nIntentando tocar bocina con coche apagado:" << endl;
    miCoche.tocarBocina();

    cocheAmigo.mostrarInfo();

    cout << "\n=== MÚLTIPLES OBJETOS ===" << endl;
    Persona personas[] = {
        Persona("Ana", 22, "Estudiante"),
        Persona("Carlos", 35, "Profesor"),
        Persona("Laura", 28, "Arquitecta")
    };

    for (auto& persona : personas) {
        persona.presentarse();
    }

    return 0;
}
```

## Miembros de Clase

### Atributos (Propiedades)
- Variables que almacenan el estado del objeto
- Pueden ser `private`, `public`, o `protected`

### Métodos (Comportamiento)
- Funciones que definen qué puede hacer el objeto
- Tienen acceso a los atributos de la instancia

## Reglas Importantes

1. **Clase vs Objeto**: La clase es la plantilla, el objeto es la instancia
2. **Encapsulamiento**: Usa `private` para datos internos
3. **Constructores**: Inicializan los objetos correctamente
4. **this**: Puntero implícito al objeto actual
5. **Destrucción**: Los objetos se destruyen automáticamente
6. **Independencia**: Cada objeto tiene su propio estado