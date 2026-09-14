# 01 - Excepciones

## Concepto Clave
Las excepciones son un mecanismo para manejar errores en tiempo de ejecución de manera estructurada. Permiten separar el código de manejo de errores del código normal.

## Sintaxis Básica

```cpp
try {
    // Código que puede lanzar excepciones
    if (error_condition) {
        throw runtime_error("Mensaje de error");
    }
} catch (const runtime_error& e) {
    // Manejar error específico
    cout << "Error: " << e.what() << endl;
} catch (const exception& e) {
    // Manejar cualquier excepción derivada de std::exception
    cout << "Excepción general: " << e.what() << endl;
} catch (...) {
    // Manejar cualquier otro tipo de excepción
    cout << "Excepción desconocida" << endl;
}
```

## Jerarquía de Excepciones Estándar

```
std::exception
├── std::logic_error
│   ├── std::invalid_argument
│   ├── std::domain_error
│   ├── std::length_error
│   ├── std::out_of_range
│   └── std::future_error
├── std::runtime_error
│   ├── std::range_error
│   ├── std::overflow_error
│   ├── std::underflow_error
│   └── std::system_error
└── std::bad_alloc
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <memory>
using namespace std;

// Clase de excepción personalizada
class DivisionPorCeroException : public runtime_error {
public:
    DivisionPorCeroException() : runtime_error("Intento de división por cero") {}
    DivisionPorCeroException(const string& mensaje) : runtime_error(mensaje) {}
};

// Clase de excepción personalizada con información adicional
class ErrorDeValidacion : public invalid_argument {
private:
    string campo;
    string valor;

public:
    ErrorDeValidacion(const string& campo, const string& valor, const string& mensaje)
        : invalid_argument(mensaje), campo(campo), valor(valor) {}

    string obtenerCampo() const { return campo; }
    string obtenerValor() const { return valor; }
};

// Función que puede lanzar excepciones
double dividir(double numerador, double denominador) {
    if (denominador == 0) {
        throw DivisionPorCeroException("El denominador no puede ser cero");
    }

    if (isnan(numerador) || isnan(denominador)) {
        throw invalid_argument("Los operandos no pueden ser NaN");
    }

    if (isinf(numerador) || isinf(denominador)) {
        throw domain_error("Los operandos no pueden ser infinitos");
    }

    return numerador / denominador;
}

// Función que valida datos de usuario
void validarUsuario(const string& nombre, int edad, const string& email) {
    if (nombre.empty()) {
        throw ErrorDeValidacion("nombre", nombre, "El nombre no puede estar vacío");
    }

    if (edad < 0 || edad > 150) {
        throw out_of_range("La edad debe estar entre 0 y 150 años");
    }

    if (email.find('@') == string::npos) {
        throw ErrorDeValidacion("email", email, "El email debe contener '@'");
    }
}

// Clase que demuestra RAII con excepciones
class Archivo {
private:
    string nombre;
    bool abierto;

public:
    Archivo(const string& nombreArchivo) : nombre(nombreArchivo), abierto(false) {
        // Simular apertura de archivo
        if (nombreArchivo.empty()) {
            throw invalid_argument("Nombre de archivo vacío");
        }
        abierto = true;
        cout << "Archivo '" << nombre << "' abierto" << endl;
    }

    ~Archivo() {
        if (abierto) {
            // Cerrar archivo en destructor (RAII)
            cout << "Archivo '" << nombre << "' cerrado" << endl;
            abierto = false;
        }
    }

    void escribir(const string& datos) {
        if (!abierto) {
            throw runtime_error("Archivo no está abierto");
        }
        cout << "Escribiendo en '" << nombre << "': " << datos << endl;
    }

    string leer() {
        if (!abierto) {
            throw runtime_error("Archivo no está abierto");
        }
        return "Contenido del archivo " + nombre;
    }
};

// Función que demuestra manejo de excepciones anidadas
void funcionAnidada(int nivel) {
    try {
        if (nivel == 1) {
            throw runtime_error("Error en nivel 1");
        } else if (nivel == 2) {
            // Llamar a función que puede fallar
            dividir(10, 0);
        } else if (nivel == 3) {
            vector<int> v;
            v.at(10);  // Acceso fuera de rango
        }
    } catch (const DivisionPorCeroException& e) {
        cout << "Capturado en funcionAnidada: " << e.what() << endl;
        throw;  // Re-lanzar
    } catch (const exception& e) {
        cout << "Capturado en funcionAnidada: " << e.what() << endl;
        // Agregar contexto y re-lanzar
        throw runtime_error(string("Error en nivel ") + to_string(nivel) + ": " + e.what());
    }
}

// Función con noexcept
double funcionSegura(double x) noexcept {
    return x * x;
}

// Función que puede lanzar excepciones
double funcionPeligrosa(double x) {
    if (x < 0) {
        throw domain_error("x debe ser no negativo");
    }
    return sqrt(x);
}

int main() {
    cout << "=== MANEJO DE EXCEPCIONES EN C++ ===" << endl;

    // 1. Excepciones básicas
    cout << "\n--- EXCEPCIONES BÁSICAS ---" << endl;

    try {
        double resultado = dividir(10, 0);
        cout << "Resultado: " << resultado << endl;
    } catch (const DivisionPorCeroException& e) {
        cout << "Capturado DivisionPorCeroException: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "Capturado exception general: " << e.what() << endl;
    }

    try {
        double resultado = dividir(10, 2);
        cout << "División exitosa: " << resultado << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    // 2. Validación de datos
    cout << "\n--- VALIDACIÓN DE DATOS ---" << endl;

    vector<tuple<string, int, string>> usuarios = {
        {"Juan", 25, "juan@email.com"},
        {"", 30, "maria@email.com"},
        {"Pedro", -5, "pedro@email.com"},
        {"Ana", 28, "ana.email.com"}
    };

    for (const auto& [nombre, edad, email] : usuarios) {
        try {
            validarUsuario(nombre, edad, email);
            cout << "Usuario válido: " << nombre << endl;
        } catch (const ErrorDeValidacion& e) {
            cout << "Error de validación en campo '" << e.obtenerCampo()
                 << "' con valor '" << e.obtenerValor() << "': " << e.what() << endl;
        } catch (const out_of_range& e) {
            cout << "Error de rango: " << e.what() << endl;
        } catch (const exception& e) {
            cout << "Error general: " << e.what() << endl;
        }
    }

    // 3. RAII con excepciones
    cout << "\n--- RAII CON EXCEPCIONES ---" << endl;

    try {
        Archivo archivo("datos.txt");
        archivo.escribir("Hola mundo");

        // Simular error
        throw runtime_error("Error simulado");

        archivo.escribir("Esto no se ejecutará");

    } catch (const exception& e) {
        cout << "Error durante operaciones de archivo: " << e.what() << endl;
        // El archivo se cierra automáticamente por RAII
    }

    // 4. Excepciones anidadas
    cout << "\n--- EXCEPCIONES ANIDADAS ---" << endl;

    for (int i = 1; i <= 3; i++) {
        try {
            funcionAnidada(i);
        } catch (const runtime_error& e) {
            cout << "Capturado en main: " << e.what() << endl;
        } catch (const exception& e) {
            cout << "Capturado otro tipo de excepción: " << e.what() << endl;
        }
    }

    // 5. Excepciones estándar del sistema
    cout << "\n--- EXCEPCIONES ESTÁNDAR ---" << endl;

    try {
        vector<int> v(5);
        cout << "Accediendo v[10]: " << v.at(10) << endl;
    } catch (const out_of_range& e) {
        cout << "out_of_range: " << e.what() << endl;
    }

    try {
        unique_ptr<int[]> ptr(new int[1000000000L]);  // Intentar asignar mucha memoria
    } catch (const bad_alloc& e) {
        cout << "bad_alloc: " << e.what() << endl;
    }

    // 6. noexcept vs funciones que pueden lanzar
    cout << "\n--- NOEXCEPT VS FUNCIONES QUE PUEDEN LANZAR ---" << endl;

    cout << "funcionSegura(5.0): " << funcionSegura(5.0) << endl;

    try {
        double resultado = funcionPeligrosa(-1.0);
        cout << "Resultado: " << resultado << endl;
    } catch (const domain_error& e) {
        cout << "Error en funcionPeligrosa: " << e.what() << endl;
    }

    // 7. Catch-all y re-lanzamiento
    cout << "\n--- CATCH-ALL Y RE-LANZAMIENTO ---" << endl;

    try {
        try {
            throw string("Excepción de tipo string");
        } catch (const string& s) {
            cout << "Capturado string: " << s << endl;
            throw;  // Re-lanzar la excepción
        }
    } catch (const string& s) {
        cout << "Re-capturado string: " << s << endl;
    } catch (...) {
        cout << "Capturado con catch-all" << endl;
    }

    // 8. Excepciones en constructores
    cout << "\n--- EXCEPCIONES EN CONSTRUCTORES ---" << endl;

    try {
        Archivo archivo2("");  // Nombre vacío causará excepción
        archivo2.escribir("Esto no se ejecutará");
    } catch (const invalid_argument& e) {
        cout << "Error en constructor: " << e.what() << endl;
        // El objeto nunca se creó completamente
    }

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;

    return 0;
}
```

## Tipos de Excepciones Estándar

### Logic Errors (Errores Lógicos)
- `invalid_argument`: Argumento inválido
- `domain_error`: Valor fuera del dominio matemático
- `length_error`: Longitud inválida
- `out_of_range`: Índice fuera de rango
- `future_error`: Error en operaciones futuras

### Runtime Errors (Errores en Tiempo de Ejecución)
- `range_error`: Resultado fuera del rango representable
- `overflow_error`: Desbordamiento aritmético
- `underflow_error`: Subdesbordamiento aritmético
- `system_error`: Error del sistema operativo
- `bad_alloc`: Fallo en asignación de memoria

## Mejores Prácticas

### ✅ Usar Excepciones para Errores Excepcionales
```cpp
// Bueno: usar excepciones para errores raros
File* abrirArchivo(string nombre) {
    if (!existeArchivo(nombre)) {
        throw runtime_error("Archivo no encontrado");
    }
    return new File(nombre);
}

// Mal: usar excepciones para control de flujo normal
int buscarElemento(vector<int>& v, int valor) {
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] == valor) return i;
    }
    throw not_found_error();  // No hacer esto
}
```

### ✅ Jerarquía de Excepciones
```cpp
class MiExcepcion : public exception {
public:
    const char* what() const noexcept override {
        return "Mi mensaje de error";
    }
};
```

### ✅ RAII (Resource Acquisition Is Initialization)
```cpp
class Archivo {
    FILE* handle;
public:
    Archivo(string nombre) : handle(fopen(nombre.c_str(), "r")) {
        if (!handle) throw runtime_error("No se pudo abrir archivo");
    }
    ~Archivo() { if (handle) fclose(handle); }
    // Recursos se liberan automáticamente
};
```

### ✅ Catch por Referencia Constante
```cpp
try {
    funcionQuePuedeFallar();
} catch (const exception& e) {  // Correcto
    cout << e.what() << endl;
} catch (exception e) {         // Incorrecto - slicing
    cout << e.what() << endl;
}
```

## Manejo de Excepciones en Funciones

### noexcept
```cpp
void funcionSegura() noexcept {
    // Garantiza que no lanza excepciones
}

void funcionQuePuedeLanzar() noexcept(false) {  // Por defecto
    throw runtime_error("Error");
}
```

### Especificadores de Excepción (Obsoletos en C++11)
```cpp
void funcion() throw(runtime_error) {  // Obsoleto
    throw runtime_error("Error");
}
```

## Ventajas de las Excepciones

### ✅ Separación de Código
- Código normal separado del manejo de errores
- Mejor legibilidad

### ✅ Propagación Automática
- Excepciones suben por la pila de llamadas
- No necesitan verificación manual en cada nivel

### ✅ Información Detallada
- Objetos de excepción pueden contener información rica
- Mensajes descriptivos y contexto

### ✅ RAII
- Recursos se liberan automáticamente durante el stack unwinding

## Desventajas

### ❌ Rendimiento
- Lanzar excepciones es costoso
- Stack unwinding puede ser lento

### ❌ Debugging Difícil
- Flujo de ejecución no lineal
- Puntos de captura pueden estar lejos del origen

### ❌ Interfaces Inconsistentes
- Algunas funciones usan códigos de error
- Otras usan excepciones

## Casos de Uso

### Manejo de Errores en APIs
```cpp
class Database {
public:
    void connect(string connectionString) {
        if (connectionString.empty()) {
            throw invalid_argument("Connection string vacía");
        }
        // Intentar conexión...
        if (/*conexión falló*/) {
            throw runtime_error("No se pudo conectar a la base de datos");
        }
    }
};
```

### Validación de Entrada
```cpp
Usuario crearUsuario(string nombre, string email, int edad) {
    if (nombre.empty()) {
        throw invalid_argument("Nombre requerido");
    }
    if (email.find('@') == string::npos) {
        throw invalid_argument("Email inválido");
    }
    if (edad < 18) {
        throw out_of_range("Usuario debe ser mayor de edad");
    }
    return Usuario(nombre, email, edad);
}
```

### Operaciones con Recursos
```cpp
void procesarArchivo(string nombre) {
    Archivo archivo(nombre);  // Puede lanzar
    archivo.procesar();       // Puede lanzar
    archivo.guardar();        // Puede lanzar
    // Archivo se cierra automáticamente si hay error
}
```