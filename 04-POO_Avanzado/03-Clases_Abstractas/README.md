# 03 - Clases Abstractas

## Concepto Clave
Las **clases abstractas** son clases que no pueden ser instanciadas directamente y sirven como base para otras clases.

## ¿Qué es una Clase Abstracta?

- **No se puede instanciar**: `Figura f;` ❌
- **Contiene métodos virtuales puros**: `= 0`
- **Sirve como interfaz/contrato**
- **Permite polimorfismo**

## Sintaxis

```cpp
class Abstracta {
public:
    virtual void metodoPuro() = 0;  // Método puro
    virtual void metodoNormal() {   // Método normal
        // Implementación opcional
    }
};
```

## Interfaces Puras

```cpp
class Interfaz {
public:
    virtual void metodo1() = 0;
    virtual void metodo2() = 0;
    virtual ~Interfaz() = default;
};
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Interfaz para objetos que se pueden dibujar
class Dibujable {
public:
    virtual void dibujar() const = 0;
    virtual ~Dibujable() = default;
};

// Interfaz para objetos que se pueden serializar
class Serializable {
public:
    virtual string serializar() const = 0;
    virtual void deserializar(const string& datos) = 0;
    virtual ~Serializable() = default;
};

// Clase abstracta: Vehiculo
class Vehiculo : public Dibujable {
protected:
    string marca;
    string modelo;
    int ano;

public:
    Vehiculo(string m, string mod, int a) : marca(m), modelo(mod), ano(a) {}

    // Método puro - debe implementarse
    virtual void acelerar() = 0;
    virtual void frenar() = 0;

    // Método normal con implementación por defecto
    virtual void mostrarInfo() const {
        cout << marca << " " << modelo << " (" << ano << ")" << endl;
    }

    // Getter
    string obtenerMarca() const { return marca; }
};

// Clase abstracta: Empleado
class Empleado : public Serializable {
protected:
    string nombre;
    string id;
    double salarioBase;

public:
    Empleado(string n, string i, double s) : nombre(n), id(i), salarioBase(s) {}

    // Métodos puros
    virtual double calcularSalario() const = 0;
    virtual string obtenerTipo() const = 0;

    // Implementación de Serializable
    string serializar() const override {
        return nombre + "," + id + "," + to_string(salarioBase);
    }

    void deserializar(const string& datos) override {
        // Implementación simplificada
        size_t pos1 = datos.find(',');
        size_t pos2 = datos.find(',', pos1 + 1);

        if (pos1 != string::npos && pos2 != string::npos) {
            nombre = datos.substr(0, pos1);
            id = datos.substr(pos1 + 1, pos2 - pos1 - 1);
            salarioBase = stod(datos.substr(pos2 + 1));
        }
    }

    string obtenerNombre() const { return nombre; }
    string obtenerId() const { return id; }
};

// Implementación concreta: Coche
class Coche : public Vehiculo {
private:
    int puertas;
    string tipoMotor;

public:
    Coche(string m, string mod, int a, int p, string motor)
        : Vehiculo(m, mod, a), puertas(p), tipoMotor(motor) {}

    void acelerar() override {
        cout << "El coche " << marca << " está acelerando con motor " << tipoMotor << endl;
    }

    void frenar() override {
        cout << "El coche " << marca << " está frenando" << endl;
    }

    void dibujar() const override {
        cout << "Dibujando un coche: [🚗]" << endl;
    }

    void mostrarInfo() const override {
        Vehiculo::mostrarInfo();
        cout << "Puertas: " << puertas << ", Motor: " << tipoMotor << endl;
    }
};

// Implementación concreta: Motocicleta
class Motocicleta : public Vehiculo {
private:
    string tipo;
    bool tieneSidecar;

public:
    Motocicleta(string m, string mod, int a, string t, bool sidecar)
        : Vehiculo(m, mod, a), tipo(t), tieneSidecar(sidecar) {}

    void acelerar() override {
        cout << "La motocicleta " << marca << " está acelerando" << endl;
    }

    void frenar() override {
        cout << "La motocicleta " << marca << " está frenando" << endl;
    }

    void dibujar() const override {
        cout << "Dibujando una motocicleta: [🏍️]" << endl;
    }

    void mostrarInfo() const override {
        Vehiculo::mostrarInfo();
        cout << "Tipo: " << tipo;
        if (tieneSidecar) cout << " (con sidecar)";
        cout << endl;
    }
};

// Implementación concreta: Desarrollador
class Desarrollador : public Empleado {
private:
    string lenguajePrincipal;
    int anosExperiencia;

public:
    Desarrollador(string n, string i, double s, string leng, int exp)
        : Empleado(n, i, s), lenguajePrincipal(leng), anosExperiencia(exp) {}

    double calcularSalario() const override {
        return salarioBase + (anosExperiencia * 1000);
    }

    string obtenerTipo() const override {
        return "Desarrollador";
    }

    void programar() const {
        cout << nombre << " está programando en " << lenguajePrincipal << endl;
    }
};

// Implementación concreta: Gerente
class Gerente : public Empleado {
private:
    int numeroEmpleados;
    double bonoAnual;

public:
    Gerente(string n, string i, double s, int num, double bono)
        : Empleado(n, i, s), numeroEmpleados(num), bonoAnual(bono) {}

    double calcularSalario() const override {
        return salarioBase + bonoAnual;
    }

    string obtenerTipo() const override {
        return "Gerente";
    }

    void gestionar() const {
        cout << nombre << " está gestionando " << numeroEmpleados << " empleados" << endl;
    }
};

// Función que usa interfaz Dibujable
void dibujarTodos(const vector<Dibujable*>& objetos) {
    cout << "\n=== DIBUJANDO TODOS LOS OBJETOS ===" << endl;
    for (const auto& obj : objetos) {
        obj->dibujar();
    }
}

// Función que usa interfaz Serializable
void serializarEmpleados(const vector<Serializable*>& empleados) {
    cout << "\n=== SERIALIZANDO EMPLEADOS ===" << endl;
    for (const auto& emp : empleados) {
        cout << "Datos serializados: " << emp->serializar() << endl;
    }
}

int main() {
    cout << "=== SISTEMA CON CLASES ABSTRACTAS ===" << endl;

    // Crear vehículos (no podemos crear Vehiculo directamente)
    vector<Vehiculo*> vehiculos;
    vehiculos.push_back(new Coche("Toyota", "Corolla", 2020, 4, "Gasolina"));
    vehiculos.push_back(new Motocicleta("Honda", "CBR", 2019, "Deportiva", false));
    vehiculos.push_back(new Coche("Ford", "Mustang", 2021, 2, "Gasolina"));

    // Crear empleados
    vector<Empleado*> empleados;
    empleados.push_back(new Desarrollador("Juan", "DEV001", 50000, "C++", 5));
    empleados.push_back(new Gerente("María", "MGR001", 70000, 10, 15000));

    // Usar polimorfismo con vehículos
    cout << "\n=== VEHÍCULOS ===" << endl;
    for (const auto& veh : vehiculos) {
        veh->mostrarInfo();
        veh->acelerar();
        veh->frenar();
        cout << "---" << endl;
    }

    // Usar polimorfismo con empleados
    cout << "\n=== EMPLEADOS ===" << endl;
    for (const auto& emp : empleados) {
        cout << emp->obtenerTipo() << ": " << emp->obtenerNombre() << endl;
        cout << "Salario: $" << emp->calcularSalario() << endl;
        cout << "---" << endl;
    }

    // Usar interfaces
    vector<Dibujable*> dibujables = {vehiculos[0], vehiculos[1]};
    dibujarTodos(dibujables);

    vector<Serializable*> serializables = {empleados[0], empleados[1]};
    serializarEmpleados(serializables);

    // Demostrar serialización/deserialización
    cout << "\n=== SERIALIZACIÓN/ DESERIALIZACIÓN ===" << endl;
    Desarrollador devCopia("Temp", "TEMP", 0, "None", 0);
    string datos = empleados[0]->serializar();
    cout << "Datos originales: " << datos << endl;

    devCopia.deserializar(datos);
    cout << "Después de deserializar:" << endl;
    cout << "Nombre: " << devCopia.obtenerNombre() << endl;
    cout << "ID: " << devCopia.obtenerId() << endl;
    cout << "Salario base: $" << devCopia.calcularSalario() << endl;

    // Liberar memoria
    cout << "\n=== LIBERANDO MEMORIA ===" << endl;
    for (auto& veh : vehiculos) delete veh;
    for (auto& emp : empleados) delete emp;

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;

    return 0;
}
```

## Reglas Importantes

1. **Métodos puros**: `virtual tipo metodo() = 0;`
2. **No instanciables**: No puedes crear objetos de clases abstractas
3. **Herencia obligatoria**: Debes heredar e implementar todos los métodos puros
4. **Destructores virtuales**: Siempre virtuales en clases base
5. **Interfaces**: Clases con solo métodos puros
6. **Implementación parcial**: Puedes tener métodos con implementación

## Ventajas

### ✅ Contratos Claros
- Interfaces bien definidas
- Obliga implementación correcta

### ✅ Polimorfismo Seguro
- Garantiza que métodos existen
- Código más predecible

### ✅ Mantenibilidad
- Cambios en interfaz afectan todas las implementaciones
- Fácil detectar implementaciones faltantes

## Casos de Uso

### Interfaces
```cpp
class Logger {
public:
    virtual void log(const string& mensaje) = 0;
    virtual ~Logger() = default;
};
```

### Clases Base con Comportamiento Común
```cpp
class Animal {
public:
    virtual void hacerSonido() = 0;
    void respirar() { cout << "Respirando..." << endl; }
};
```

### Frameworks y Librerías
- Define contratos que usuarios deben seguir
- Permite extensión segura