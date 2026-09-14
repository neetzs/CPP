# 02 - Polimorfismo

## Concepto Clave
El **polimorfismo** permite que objetos de diferentes clases respondan de manera diferente al mismo mensaje (método).

## Tipos de Polimorfismo

### 1. **Polimorfismo en Tiempo de Compilación**
- Sobrecarga de funciones
- Sobrecarga de operadores
- Templates

### 2. **Polimorfismo en Tiempo de Ejecución**
- Métodos virtuales
- Herencia
- Punteros/referencias a clases base

## Métodos Virtuales

```cpp
class Base {
public:
    virtual void metodo() {  // Puede ser sobrescrito
        cout << "Base" << endl;
    }
};

class Derivada : public Base {
public:
    void metodo() override {  // Sobrescribe
        cout << "Derivada" << endl;
    }
};
```

## Polimorfismo con Punteros

```cpp
Base* ptr = new Derivada();
ptr->metodo();  // Llama a Derivada::metodo()
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Clase base abstracta: Figura
class Figura {
protected:
    string nombre;

public:
    Figura(string n) : nombre(n) {}
    virtual ~Figura() {
        cout << "Destruyendo figura: " << nombre << endl;
    }

    // Método virtual puro - debe ser implementado por clases derivadas
    virtual double calcularArea() const = 0;

    // Método virtual con implementación por defecto
    virtual void dibujar() const {
        cout << "Dibujando una figura genérica" << endl;
    }

    // Método no virtual
    string obtenerNombre() const {
        return nombre;
    }
};

// Clase derivada: Circulo
class Circulo : public Figura {
private:
    double radio;

public:
    Circulo(string n, double r) : Figura(n), radio(r) {}

    double calcularArea() const override {
        return 3.14159 * radio * radio;
    }

    void dibujar() const override {
        cout << "Dibujando un círculo de radio " << radio << endl;
    }

    double obtenerRadio() const {
        return radio;
    }
};

// Clase derivada: Rectangulo
class Rectangulo : public Figura {
private:
    double ancho;
    double alto;

public:
    Rectangulo(string n, double a, double h) : Figura(n), ancho(a), alto(h) {}

    double calcularArea() const override {
        return ancho * alto;
    }

    void dibujar() const override {
        cout << "Dibujando un rectángulo de " << ancho << "x" << alto << endl;
    }

    double obtenerAncho() const { return ancho; }
    double obtenerAlto() const { return alto; }
};

// Clase derivada: Triangulo
class Triangulo : public Figura {
private:
    double base;
    double altura;

public:
    Triangulo(string n, double b, double h) : Figura(n), base(b), altura(h) {}

    double calcularArea() const override {
        return (base * altura) / 2;
    }

    void dibujar() const override {
        cout << "Dibujando un triángulo de base " << base << " y altura " << altura << endl;
    }
};

// Función que demuestra polimorfismo
void procesarFiguras(const vector<Figura*>& figuras) {
    cout << "\n=== PROCESANDO FIGURAS ===" << endl;
    double areaTotal = 0;

    for (const auto& figura : figuras) {
        cout << "Figura: " << figura->obtenerNombre() << endl;
        figura->dibujar();
        double area = figura->calcularArea();
        cout << "Área: " << area << endl;
        areaTotal += area;
        cout << "------------------------" << endl;
    }

    cout << "Área total de todas las figuras: " << areaTotal << endl;
}

// Función que filtra círculos (downcasting)
void procesarCirculos(const vector<Figura*>& figuras) {
    cout << "\n=== PROCESANDO SÓLO CÍRCULOS ===" << endl;

    for (const auto& figura : figuras) {
        // Verificar si es un círculo usando dynamic_cast
        const Circulo* circulo = dynamic_cast<const Circulo*>(figura);
        if (circulo != nullptr) {
            cout << "Círculo encontrado: " << circulo->obtenerNombre() << endl;
            cout << "Radio: " << circulo->obtenerRadio() << endl;
            cout << "Área: " << circulo->calcularArea() << endl;
        }
    }
}

// Clase que demuestra polimorfismo con smart pointers
class Pintor {
public:
    void pintarFigura(const Figura* figura) {
        cout << "El pintor está pintando: ";
        figura->dibujar();
    }

    void mostrarArea(const Figura* figura) {
        cout << "Área calculada: " << figura->calcularArea() << endl;
    }
};

int main() {
    cout << "=== SISTEMA DE FIGURAS GEOMÉTRICAS ===" << endl;

    // Crear figuras usando polimorfismo
    vector<Figura*> figuras;

    figuras.push_back(new Circulo("Círculo Grande", 5.0));
    figuras.push_back(new Rectangulo("Rectángulo Pequeño", 3.0, 4.0));
    figuras.push_back(new Triangulo("Triángulo Equilátero", 6.0, 4.0));
    figuras.push_back(new Circulo("Círculo Pequeño", 2.5));
    figuras.push_back(new Rectangulo("Cuadrado", 5.0, 5.0));

    // Procesar todas las figuras (polimorfismo)
    procesarFiguras(figuras);

    // Procesar solo círculos
    procesarCirculos(figuras);

    // Usar clase Pintor
    cout << "\n=== CLASE PINTOR ===" << endl;
    Pintor pintor;

    for (const auto& figura : figuras) {
        pintor.pintarFigura(figura);
        pintor.mostrarArea(figura);
        cout << "---" << endl;
    }

    // Demostrar polimorfismo con referencias
    cout << "\n=== POLIMORFISMO CON REFERENCIAS ===" << endl;
    Circulo circuloRef("Círculo de Referencia", 3.0);
    Rectangulo rectRef("Rectángulo de Referencia", 4.0, 6.0);

    // Función que acepta referencia a Figura
    auto mostrarInfo = [](const Figura& fig) {
        cout << fig.obtenerNombre() << " - Área: " << fig.calcularArea() << endl;
    };

    mostrarInfo(circuloRef);  // Polimorfismo con referencias
    mostrarInfo(rectRef);

    // Liberar memoria
    cout << "\n=== LIBERANDO MEMORIA ===" << endl;
    for (auto& figura : figuras) {
        delete figura;
    }
    figuras.clear();

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;

    return 0;
}
```

## Palabras Clave Importantes

### `virtual`
- Declara método que puede ser sobrescrito
- Obligatorio para polimorfismo en tiempo de ejecución

### `override`
- Indica que método sobrescribe uno virtual
- Ayuda a detectar errores de compilación

### `final`
- Evita que método sea sobrescrito más
- `class Clase final` evita herencia

### `dynamic_cast`
- Convierte punteros/referencias polimórficas
- Verifica tipo en tiempo de ejecución

## Ventajas del Polimorfismo

### ✅ Flexibilidad
- Código genérico que funciona con múltiples tipos
- Extensibilidad fácil

### ✅ Mantenibilidad
- Cambios en clases derivadas no afectan código base
- Interfaces consistentes

### ✅ Reutilización
- Funciones que aceptan clases base
- Contenedores heterogéneos

## Reglas Importantes

1. **Métodos virtuales**: Declara `virtual` en clase base
2. **Destructores virtuales**: Siempre virtual si hay herencia
3. **override**: Usa para sobrescribir métodos virtuales
4. **Punteros/referencias**: Usa para polimorfismo en tiempo de ejecución
5. **Clases abstractas**: No se pueden instanciar directamente
6. **Métodos puros**: `= 0` fuerza implementación en derivadas

## Antipatrones

### ❌ No Usar Virtual Incorrectamente
```cpp
class Base {
    void metodo();  // No virtual - no polimorfismo
};

class Derivada : public Base {
    void metodo();  // No sobrescribe realmente
};
```

### ❌ Slicing
```cpp
vector<Figura> figuras;  // ❌ Pierde polimorfismo
figuras.push_back(Circulo("test", 1.0));

vector<Figura*> figuras;  // ✅ Correcto
```