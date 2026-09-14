# 04 - Sobrecarga

## Concepto Clave
La **sobrecarga** permite definir múltiples versiones de funciones u operadores con el mismo nombre pero diferentes parámetros.

## Sobrecarga de Funciones

```cpp
void imprimir(int x) {
    cout << "Entero: " << x << endl;
}

void imprimir(double x) {
    cout << "Decimal: " << x << endl;
}

void imprimir(string s) {
    cout << "Texto: " << s << endl;
}
```

## Sobrecarga de Operadores

```cpp
class Complejo {
private:
    double real, imag;
public:
    Complejo(double r = 0, double i = 0) : real(r), imag(i) {}

    // Sobrecarga del operador +
    Complejo operator+(const Complejo& otro) const {
        return Complejo(real + otro.real, imag + otro.imag);
    }

    void mostrar() const {
        cout << real << " + " << imag << "i" << endl;
    }
};
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Clase que demuestra sobrecarga de operadores
class NumeroComplejo {
private:
    double real;
    double imaginario;

public:
    // Constructores
    NumeroComplejo(double r = 0, double i = 0) : real(r), imaginario(i) {}

    // Sobrecarga de operadores aritméticos
    NumeroComplejo operator+(const NumeroComplejo& otro) const {
        return NumeroComplejo(real + otro.real, imaginario + otro.imaginario);
    }

    NumeroComplejo operator-(const NumeroComplejo& otro) const {
        return NumeroComplejo(real - otro.real, imaginario - otro.imaginario);
    }

    NumeroComplejo operator*(const NumeroComplejo& otro) const {
        return NumeroComplejo(
            real * otro.real - imaginario * otro.imaginario,
            real * otro.imaginario + imaginario * otro.real
        );
    }

    NumeroComplejo operator/(double escalar) const {
        if (escalar != 0) {
            return NumeroComplejo(real / escalar, imaginario / escalar);
        }
        throw invalid_argument("División por cero");
    }

    // Sobrecarga de operadores de comparación
    bool operator==(const NumeroComplejo& otro) const {
        return (real == otro.real) && (imaginario == otro.imaginario);
    }

    bool operator!=(const NumeroComplejo& otro) const {
        return !(*this == otro);
    }

    // Sobrecarga de operadores de asignación
    NumeroComplejo& operator+=(const NumeroComplejo& otro) {
        real += otro.real;
        imaginario += otro.imaginario;
        return *this;
    }

    NumeroComplejo& operator-=(const NumeroComplejo& otro) {
        real -= otro.real;
        imaginario -= otro.imaginario;
        return *this;
    }

    // Sobrecarga del operador de inserción (friend para acceder a private)
    friend ostream& operator<<(ostream& os, const NumeroComplejo& c) {
        os << c.real;
        if (c.imaginario >= 0) os << " + ";
        else os << " - ";
        os << abs(c.imaginario) << "i";
        return os;
    }

    // Sobrecarga del operador de extracción
    friend istream& operator>>(istream& is, NumeroComplejo& c) {
        cout << "Parte real: ";
        is >> c.real;
        cout << "Parte imaginaria: ";
        is >> c.imaginario;
        return is;
    }

    // Getters
    double obtenerReal() const { return real; }
    double obtenerImaginario() const { return imaginario; }
};

// Clase Vector con sobrecarga de operadores
class Vector2D {
private:
    double x, y;

public:
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    // Operadores aritméticos
    Vector2D operator+(const Vector2D& otro) const {
        return Vector2D(x + otro.x, y + otro.y);
    }

    Vector2D operator*(double escalar) const {
        return Vector2D(x * escalar, y * escalar);
    }

    // Operador de índice []
    double& operator[](int indice) {
        if (indice == 0) return x;
        if (indice == 1) return y;
        throw out_of_range("Índice inválido");
    }

    const double& operator[](int indice) const {
        if (indice == 0) return x;
        if (indice == 1) return y;
        throw out_of_range("Índice inválido");
    }

    // Operador de función ()
    double operator()(int componente) const {
        switch (componente) {
            case 0: return x;
            case 1: return y;
            default: throw out_of_range("Componente inválido");
        }
    }

    // Operador de comparación
    bool operator==(const Vector2D& otro) const {
        return (x == otro.x) && (y == otro.y);
    }

    // Operador de salida
    friend ostream& operator<<(ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }

    double obtenerX() const { return x; }
    double obtenerY() const { return y; }
};

// Sobrecarga de funciones (no métodos de clase)
NumeroComplejo sumar(const NumeroComplejo& a, const NumeroComplejo& b) {
    return a + b;
}

Vector2D escalarPorVector(double escalar, const Vector2D& vector) {
    return vector * escalar;
}

// Función con múltiples sobrecargas
void imprimir(const NumeroComplejo& c) {
    cout << "Número complejo: " << c << endl;
}

void imprimir(const Vector2D& v) {
    cout << "Vector: " << v << endl;
}

void imprimir(double d) {
    cout << "Número real: " << d << endl;
}

void imprimir(const string& s) {
    cout << "Texto: " << s << endl;
}

int main() {
    cout << "=== NÚMEROS COMPLEJOS ===" << endl;

    NumeroComplejo c1(3, 4);    // 3 + 4i
    NumeroComplejo c2(1, -2);   // 1 - 2i

    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;

    NumeroComplejo suma = c1 + c2;
    NumeroComplejo resta = c1 - c2;
    NumeroComplejo producto = c1 * c2;

    cout << "c1 + c2 = " << suma << endl;
    cout << "c1 - c2 = " << resta << endl;
    cout << "c1 * c2 = " << producto << endl;

    // Operadores de asignación
    NumeroComplejo c3 = c1;
    c3 += c2;
    cout << "c1 += c2: " << c3 << endl;

    // Comparación
    cout << "c1 == c2: " << (c1 == c2 ? "Sí" : "No") << endl;

    cout << "\n=== VECTORES 2D ===" << endl;

    Vector2D v1(3, 4);
    Vector2D v2(1, 2);

    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;

    Vector2D sumaVec = v1 + v2;
    Vector2D escalarVec = v1 * 2;

    cout << "v1 + v2 = " << sumaVec << endl;
    cout << "v1 * 2 = " << escalarVec << endl;

    // Operador de índice
    cout << "v1[0] = " << v1[0] << ", v1[1] = " << v1[1] << endl;
    v1[0] = 10;
    cout << "Después de v1[0] = 10: " << v1 << endl;

    // Operador de función
    cout << "v1(0) = " << v1(0) << ", v1(1) = " << v1(1) << endl;

    cout << "\n=== SOBRECARGA DE FUNCIONES ===" << endl;

    NumeroComplejo c4(2, 3);
    Vector2D v3(5, 6);

    imprimir(c4);
    imprimir(v3);
    imprimir(3.14);
    imprimir("Hola mundo");

    cout << "\n=== FUNCIONES SOBRECARGADAS ===" << endl;

    NumeroComplejo resultado = sumar(c1, c2);
    cout << "Función sumar: " << resultado << endl;

    Vector2D resultadoVec = escalarPorVector(3, v1);
    cout << "Función escalarPorVector: " << resultadoVec << endl;

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;

    return 0;
}
```

## Operadores que se Pueden Sobrecargar

### ✅ Aritméticos
`+`, `-`, `*`, `/`, `%`, `+=`, `-=`, `*=`, `/=`, `%=`

### ✅ Comparación
`==`, `!=`, `<`, `>`, `<=`, `>=`

### ✅ Lógicos
`!`, `&&`, `||`

### ✅ Acceso
`[]`, `()`, `->`, `->*`

### ✅ Asignación
`=`, otros operadores de asignación compuesta

### ✅ E/S
`<<`, `>>`

### ❌ No se pueden sobrecargar
- `.` (acceso a miembro)
- `::` (resolución de ámbito)
- `?:` (operador ternario)
- `sizeof`
- `typeid`

## Reglas Importantes

1. **Al menos un operando debe ser de tipo definido por el usuario**
2. **No se puede cambiar la precedencia o asociatividad**
3. **No se puede cambiar el número de operandos**
4. **Los operadores `=`, `[]`, `()` y `->` deben ser métodos de clase**
5. **Los operadores de E/S (`<<`, `>>`) suelen ser funciones friend**
6. **Retornar referencias para operadores de asignación**

## Buenas Prácticas

### ✅ Sobrecarga Intuitiva
```cpp
Complejo c1, c2;
Complejo suma = c1 + c2;  // Intuitivo
```

### ❌ Sobrecarga Confusa
```cpp
Vector v;
v + 5;  // ¿Qué significa sumar un vector y un número?
```

### ✅ Consistencia
- Si sobrecargas `+`, considera `+=`
- Si sobrecargas `==`, sobrecarga `!=`
- Si sobrecargas `<`, considera los otros operadores de comparación