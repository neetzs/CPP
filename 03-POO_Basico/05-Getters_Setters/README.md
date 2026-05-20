# 05 - Getters y Setters

## Concepto Clave
Los **getters** y **setters** son métodos que permiten acceder y modificar atributos privados de forma controlada.

## ¿Por qué Getters y Setters?

### ❌ Sin Encapsulamiento
```cpp
class MalaClase {
public:
    int edad;  // Acceso directo - peligroso
};

obj.edad = -5;  // Valor inválido posible
```

### ✅ Con Encapsulamiento
```cpp
class BuenaClase {
private:
    int edad;
public:
    int obtenerEdad() const {
        return edad;
    }

    void establecerEdad(int nuevaEdad) {
        if (nuevaEdad >= 0 && nuevaEdad <= 150) {
            edad = nuevaEdad;
        }
    }
};
```

## Tipos de Getters

### Getter Simple
```cpp
int obtenerEdad() const {
    return edad;
}
```

### Getter con Cálculo
```cpp
int obtenerEdadEnMeses() const {
    return edad * 12;
}
```

### Getter que Retorna Referencia
```cpp
const string& obtenerNombre() const {
    return nombre;  // Retorna referencia constante
}
```

## Tipos de Setters

### Setter Simple
```cpp
void establecerEdad(int nuevaEdad) {
    edad = nuevaEdad;
}
```

### Setter con Validación
```cpp
void establecerEdad(int nuevaEdad) {
    if (nuevaEdad >= 0 && nuevaEdad <= 150) {
        edad = nuevaEdad;
    } else {
        cout << "Edad inválida" << endl;
    }
}
```

### Setter con Lógica Adicional
```cpp
void establecerNombre(string nuevoNombre) {
    // Capitalizar primera letra
    if (!nuevoNombre.empty()) {
        nuevoNombre[0] = toupper(nuevoNombre[0]);
    }
    nombre = nuevoNombre;
    // Podría guardar en base de datos, etc.
}
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Persona {
private:
    string nombre;
    int edad;
    string email;
    double salario;

public:
    // Constructor
    Persona(string n, int e, string em, double s)
        : nombre(n), edad(e), email(em), salario(s) {}

    // Getters
    string obtenerNombre() const {
        return nombre;
    }

    int obtenerEdad() const {
        return edad;
    }

    string obtenerEmail() const {
        return email;
    }

    double obtenerSalario() const {
        return salario;
    }

    // Getter calculado
    string obtenerNombreCompleto() const {
        return nombre + " (Edad: " + to_string(edad) + ")";
    }

    // Getter que indica si es mayor de edad
    bool esMayorDeEdad() const {
        return edad >= 18;
    }

    // Setters con validación
    void establecerNombre(string nuevoNombre) {
        if (!nuevoNombre.empty() && nuevoNombre.length() <= 50) {
            // Capitalizar primera letra
            nuevoNombre[0] = toupper(nuevoNombre[0]);
            for (size_t i = 1; i < nuevoNombre.length(); i++) {
                nuevoNombre[i] = tolower(nuevoNombre[i]);
            }
            nombre = nuevoNombre;
            cout << "Nombre establecido: " << nombre << endl;
        } else {
            cout << "Nombre inválido (vacío o muy largo)" << endl;
        }
    }

    void establecerEdad(int nuevaEdad) {
        if (nuevaEdad >= 0 && nuevaEdad <= 150) {
            edad = nuevaEdad;
            cout << "Edad establecida: " << edad << endl;
        } else {
            cout << "Edad inválida (debe ser entre 0 y 150)" << endl;
        }
    }

    void establecerEmail(string nuevoEmail) {
        // Validación simple de email
        if (nuevoEmail.find('@') != string::npos &&
            nuevoEmail.find('.') != string::npos) {
            email = nuevoEmail;
            cout << "Email establecido: " << email << endl;
        } else {
            cout << "Email inválido (debe contener @ y .)" << endl;
        }
    }

    void establecerSalario(double nuevoSalario) {
        if (nuevoSalario >= 0) {
            double diferencia = nuevoSalario - salario;
            salario = nuevoSalario;
            cout << "Salario establecido: $" << salario;
            if (diferencia > 0) {
                cout << " (aumento de $" << diferencia << ")";
            } else if (diferencia < 0) {
                cout << " (disminución de $" << -diferencia << ")";
            }
            cout << endl;
        } else {
            cout << "Salario inválido (no puede ser negativo)" << endl;
        }
    }

    // Método que combina getters y setters
    void aumentarSalario(double porcentaje) {
        if (porcentaje > 0 && porcentaje <= 100) {
            double nuevoSalario = obtenerSalario() * (1 + porcentaje / 100);
            establecerSalario(nuevoSalario);
        } else {
            cout << "Porcentaje inválido" << endl;
        }
    }

    // Mostrar información completa
    void mostrarInformacion() const {
        cout << "\n--- Información de Persona ---" << endl;
        cout << "Nombre: " << obtenerNombre() << endl;
        cout << "Edad: " << obtenerEdad() << " años" << endl;
        cout << "Email: " << obtenerEmail() << endl;
        cout << "Salario: $" << obtenerSalario() << endl;
        cout << "Mayor de edad: " << (esMayorDeEdad() ? "Sí" : "No") << endl;
        cout << "Nombre completo: " << obtenerNombreCompleto() << endl;
    }
};

class Producto {
private:
    string nombre;
    double precio;
    int cantidad;
    string categoria;

public:
    Producto(string n, double p, int c, string cat)
        : nombre(n), precio(p), cantidad(c), categoria(cat) {}

    // Getters
    string obtenerNombre() const { return nombre; }
    double obtenerPrecio() const { return precio; }
    int obtenerCantidad() const { return cantidad; }
    string obtenerCategoria() const { return categoria; }

    // Getter calculado
    double obtenerValorTotal() const {
        return precio * cantidad;
    }

    // Setters
    void establecerPrecio(double nuevoPrecio) {
        if (nuevoPrecio > 0) {
            precio = nuevoPrecio;
        }
    }

    void establecerCantidad(int nuevaCantidad) {
        if (nuevaCantidad >= 0) {
            cantidad = nuevaCantidad;
        }
    }

    void vender(int cantidadVendida) {
        if (cantidadVendida > 0 && cantidadVendida <= cantidad) {
            cantidad -= cantidadVendida;
            cout << "Vendidos " << cantidadVendida << " unidades de " << nombre << endl;
        }
    }

    void mostrarProducto() const {
        cout << nombre << " - $" << precio << " x " << cantidad
             << " = $" << obtenerValorTotal() << " (" << categoria << ")" << endl;
    }
};

int main() {
    cout << "=== SISTEMA DE PERSONAS ===" << endl;

    Persona persona("juan perez", 25, "juan@email", 30000);

    persona.mostrarInformacion();

    // Probar setters con validación
    cout << "\n=== PROBANDO SETTERS ===" << endl;

    persona.establecerNombre("maria garcia");  // Se capitalizará
    persona.establecerEdad(30);
    persona.establecerEmail("maria@empresa.com");
    persona.establecerSalario(45000);

    // Intentar valores inválidos
    persona.establecerEdad(-5);      // Inválido
    persona.establecerEmail("email-invalido");  // Inválido
    persona.establecerSalario(-1000); // Inválido

    persona.aumentarSalario(15);  // 15% de aumento

    persona.mostrarInformacion();

    cout << "\n=== SISTEMA DE PRODUCTOS ===" << endl;

    Producto laptop("Laptop Gaming", 1200, 5, "Electrónicos");
    Producto mouse("Mouse Óptico", 25, 20, "Accesorios");

    laptop.mostrarProducto();
    mouse.mostrarProducto();

    laptop.vender(2);
    mouse.establecerPrecio(30);  // Aumentar precio

    cout << "\nDespués de cambios:" << endl;
    laptop.mostrarProducto();
    mouse.mostrarProducto();

    cout << "\nValor total del inventario: $"
         << (laptop.obtenerValorTotal() + mouse.obtenerValorTotal()) << endl;

    return 0;
}
```

## Convenciones de Nombres

### Getters
```cpp
// Preferido
int obtenerEdad() const;
string obtenerNombre() const;

// También válido
int getEdad() const;
string getNombre() const;
```

### Setters
```cpp
// Preferido
void establecerEdad(int edad);
void establecerNombre(string nombre);

// También válido
void setEdad(int edad);
void setNombre(string nombre);
```

## Reglas Importantes

1. **Atributos privados**: Siempre usa getters/setters para acceso
2. **Validación**: Incluye validación en setters cuando sea necesario
3. **const**: Getters deben ser `const` si no modifican el objeto
4. **Referencias**: Getters pueden retornar `const T&` para eficiencia
5. **Consistencia**: Usa la misma convención en todo el proyecto
6. **Documentación**: Documenta qué validaciones hacen los setters

## Antipatrones

### ❌ Getters/Setters Automáticos
```cpp
class MalaClase {
private:
    int dato;
public:
    int getDato() { return dato; }      // Sin encapsulamiento real
    void setDato(int d) { dato = d; }   // Sin validación
};
```

### ❌ Exposición de Datos Internos
```cpp
const vector<int>& obtenerDatosInternos() const {
    return datosInternos;  // Rompe encapsulamiento
}
```