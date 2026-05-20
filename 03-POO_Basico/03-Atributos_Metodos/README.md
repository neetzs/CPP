# 03 - Atributos y Métodos

## Concepto Clave
Los **atributos** son las propiedades de un objeto. Los **métodos** son las acciones que puede realizar.

## Tipos de Atributos

### Atributos de Instancia
```cpp
class Clase {
private:
    int atributoInstancia;  // Cada objeto tiene su copia
};
```

### Atributos Estáticos
```cpp
class Clase {
private:
    static int atributoEstatico;  // Compartido por todas las instancias
};
```

### Atributos Constantes
```cpp
class Clase {
private:
    const int atributoConstante;  // No se puede modificar
};
```

## Tipos de Métodos

### Métodos de Instancia
```cpp
class Clase {
public:
    void metodoInstancia() {
        // Accede a atributos de instancia
    }
};
```

### Métodos Estáticos
```cpp
class Clase {
public:
    static void metodoEstatico() {
        // No accede a atributos de instancia
    }
};
```

### Métodos Constantes
```cpp
class Clase {
public:
    void metodoConstante() const {
        // No modifica el objeto
    }
};
```

## El Puntero `this`

```cpp
class Clase {
private:
    int valor;
public:
    void setValor(int valor) {
        this->valor = valor;  // this->valor es el atributo
                              // valor es el parámetro
    }

    Clase* obtenerDireccion() {
        return this;  // Retorna puntero al objeto actual
    }
};
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <string>
using namespace std;

class Banco {
private:
    string nombre;
    double saldo;
    static int totalCuentas;  // Atributo estático
    const string numeroCuenta;  // Atributo constante

public:
    // Constructor
    Banco(string n, string numCuenta)
        : nombre(n), numeroCuenta(numCuenta), saldo(0.0) {
        totalCuentas++;
        cout << "Cuenta creada para " << nombre << " (" << numeroCuenta << ")" << endl;
    }

    // Destructor
    ~Banco() {
        totalCuentas--;
        cout << "Cuenta cerrada: " << numeroCuenta << endl;
    }

    // Métodos de instancia
    void depositar(double cantidad) {
        if (cantidad > 0) {
            saldo += cantidad;
            cout << "Depósito: $" << cantidad << " en cuenta " << numeroCuenta << endl;
            mostrarSaldo();
        }
    }

    bool retirar(double cantidad) {
        if (cantidad > 0 && cantidad <= saldo) {
            saldo -= cantidad;
            cout << "Retiro: $" << cantidad << " de cuenta " << numeroCuenta << endl;
            mostrarSaldo();
            return true;
        } else {
            cout << "Fondos insuficientes en cuenta " << numeroCuenta << endl;
            return false;
        }
    }

    void mostrarSaldo() const {
        cout << "Saldo actual (" << numeroCuenta << "): $" << saldo << endl;
    }

    // Método que usa this
    Banco& agregarInteres(double tasa) {
        double interes = saldo * tasa / 100;
        saldo += interes;
        cout << "Interés agregado: $" << interes << " (" << tasa << "%)" << endl;
        return *this;  // Retorna referencia al objeto actual
    }

    // Método estático
    static int obtenerTotalCuentas() {
        return totalCuentas;
    }

    // Getters
    string obtenerNombre() const {
        return nombre;
    }

    string obtenerNumeroCuenta() const {
        return numeroCuenta;
    }

    double obtenerSaldo() const {
        return saldo;
    }
};

// Inicializar atributo estático
int Banco::totalCuentas = 0;

class Calculadora {
private:
    double memoria;

public:
    Calculadora() : memoria(0.0) {}

    // Métodos que retornan this para encadenamiento
    Calculadora& sumar(double valor) {
        memoria += valor;
        cout << "Sumar " << valor << " = " << memoria << endl;
        return *this;
    }

    Calculadora& restar(double valor) {
        memoria -= valor;
        cout << "Restar " << valor << " = " << memoria << endl;
        return *this;
    }

    Calculadora& multiplicar(double valor) {
        memoria *= valor;
        cout << "Multiplicar por " << valor << " = " << memoria << endl;
        return *this;
    }

    Calculadora& dividir(double valor) {
        if (valor != 0) {
            memoria /= valor;
            cout << "Dividir por " << valor << " = " << memoria << endl;
        } else {
            cout << "Error: división por cero" << endl;
        }
        return *this;
    }

    void limpiar() {
        memoria = 0.0;
        cout << "Memoria limpiada" << endl;
    }

    double obtenerResultado() const {
        return memoria;
    }
};

int main() {
    cout << "=== SISTEMA BANCARIO ===" << endl;

    Banco cuenta1("Juan Pérez", "001");
    Banco cuenta2("María García", "002");

    cout << "Total de cuentas: " << Banco::obtenerTotalCuentas() << endl;

    cuenta1.depositar(1000);
    cuenta1.retirar(200);
    cuenta1.agregarInteres(5.0).mostrarSaldo();  // Encadenamiento

    cuenta2.depositar(500);
    cuenta2.retirar(100);

    cout << "\n=== CALCULADORA ===" << endl;

    Calculadora calc;

    // Encadenamiento de métodos
    calc.sumar(10)
        .multiplicar(2)
        .restar(5)
        .dividir(3);

    cout << "Resultado final: " << calc.obtenerResultado() << endl;

    calc.limpiar();
    cout << "Después de limpiar: " << calc.obtenerResultado() << endl;

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;
    cout << "Total de cuentas al final: " << Banco::obtenerTotalCuentas() << endl;

    return 0;
}
```

## Reglas Importantes

1. **Atributos**: Normalmente `private`, accedidos vía métodos
2. **Métodos**: `public` para interfaz, `private` para implementación
3. **this**: Puntero al objeto actual, útil para desambiguar
4. **Estáticos**: Compartidos, no necesitan instancia
5. **Constantes**: Métodos `const` no modifican el objeto
6. **Encadenamiento**: Retornar `*this` permite `obj.metodo1().metodo2()`

## Convenciones de Nombres

### Atributos
```cpp
private:
    string nombre;        // minúscula
    string nombreCompleto; // camelCase
    int numeroCuenta;     // descriptivo
```

### Métodos
```cpp
public:
    void obtenerNombre();     // verbo + sustantivo
    void establecerNombre();
    bool esValido();
```