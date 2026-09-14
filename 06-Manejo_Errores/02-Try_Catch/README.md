# 02 - Try Catch

## Concepto Clave
Los bloques try-catch permiten capturar y manejar excepciones lanzadas durante la ejecución del código. El bloque try contiene el código que puede lanzar excepciones, y los bloques catch las capturan y manejan.

## Sintaxis Básica

```cpp
try {
    // Código que puede lanzar excepciones
    funcionQuePuedeFallar();
} catch (TipoExcepcion1& e) {
    // Manejar excepción específica
    cout << "Error TipoExcepcion1: " << e.what() << endl;
} catch (TipoExcepcion2& e) {
    // Manejar otra excepción específica
    cout << "Error TipoExcepcion2: " << e.what() << endl;
} catch (const exception& e) {
    // Capturar cualquier excepción derivada de std::exception
    cout << "Excepción estándar: " << e.what() << endl;
} catch (...) {
    // Capturar cualquier otro tipo de excepción (catch-all)
    cout << "Excepción desconocida" << endl;
}
```

## Orden de Captura

El orden de los bloques catch es importante:

```cpp
try {
    throw runtime_error("Error");
} catch (const exception& e) {  // Captura runtime_error (base)
    cout << "Exception: " << e.what() << endl;
} catch (const runtime_error& e) {  // Nunca se ejecuta
    cout << "Runtime error: " << e.what() << endl;
}
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <cmath>
using namespace std;

// Excepciones personalizadas
class ErrorMatematico : public runtime_error {
public:
    ErrorMatematico(const string& mensaje) : runtime_error(mensaje) {}
};

class ErrorArchivo : public runtime_error {
public:
    ErrorArchivo(const string& archivo, const string& mensaje)
        : runtime_error("Archivo '" + archivo + "': " + mensaje) {}
};

class ErrorValidacion : public invalid_argument {
private:
    string campo;

public:
    ErrorValidacion(const string& campo, const string& mensaje)
        : invalid_argument(mensaje), campo(campo) {}

    string obtenerCampo() const { return campo; }
};

// Funciones que pueden lanzar excepciones
double calcularRaizCuadrada(double x) {
    if (x < 0) {
        throw ErrorMatematico("No se puede calcular raíz cuadrada de número negativo");
    }
    if (isnan(x)) {
        throw invalid_argument("El argumento no puede ser NaN");
    }
    return sqrt(x);
}

double dividir(double a, double b) {
    if (b == 0) {
        throw ErrorMatematico("División por cero");
    }
    if (isinf(a) || isinf(b)) {
        throw domain_error("Los operandos no pueden ser infinitos");
    }
    return a / b;
}

void validarPersona(const string& nombre, int edad, double salario) {
    if (nombre.empty()) {
        throw ErrorValidacion("nombre", "El nombre no puede estar vacío");
    }
    if (edad < 0 || edad > 150) {
        throw out_of_range("La edad debe estar entre 0 y 150 años");
    }
    if (salario < 0) {
        throw ErrorValidacion("salario", "El salario no puede ser negativo");
    }
}

void procesarArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw ErrorArchivo(nombreArchivo, "No se pudo abrir el archivo");
    }

    string linea;
    getline(archivo, linea);
    if (linea.empty()) {
        throw ErrorArchivo(nombreArchivo, "El archivo está vacío");
    }

    // Simular procesamiento
    cout << "Procesando archivo: " << linea << endl;

    // Simular error durante procesamiento
    if (linea.find("error") != string::npos) {
        throw ErrorArchivo(nombreArchivo, "Error durante el procesamiento");
    }
}

void funcionQuePuedeFallar(int tipoError) {
    switch (tipoError) {
        case 1:
            throw runtime_error("Error de tiempo de ejecución");
        case 2:
            throw invalid_argument("Argumento inválido");
        case 3:
            throw out_of_range("Índice fuera de rango");
        case 4:
            throw bad_alloc();  // Error de memoria
        case 5:
            throw "Error como cadena C";  // Excepción no estándar
        default:
            throw ErrorMatematico("Error matemático personalizado");
    }
}

// Función que demuestra re-lanzamiento
void funcionConRelanzamiento(int valor) {
    try {
        if (valor < 0) {
            throw invalid_argument("Valor negativo no permitido");
        }
        funcionQuePuedeFallar(valor);
    } catch (const invalid_argument& e) {
        cout << "Capturado en funcionConRelanzamiento: " << e.what() << endl;
        throw;  // Re-lanzar la misma excepción
    } catch (const runtime_error& e) {
        cout << "Convirtiendo runtime_error a ErrorMatematico" << endl;
        throw ErrorMatematico(string("Error convertido: ") + e.what());
    }
}

// Clase que demuestra excepciones en destructor (¡CUIDADO!)
class ArchivoPeligroso {
private:
    string nombre;
    bool abierto;

public:
    ArchivoPeligroso(const string& nombreArchivo)
        : nombre(nombreArchivo), abierto(true) {
        cout << "Archivo '" << nombre << "' abierto" << endl;
    }

    ~ArchivoPeligroso() {
        if (abierto) {
            cout << "Cerrando archivo '" << nombre << "'..." << endl;
            // ¡NUNCA lanzar excepciones en destructores!
            // Esto puede causar terminate()
            // throw runtime_error("Error al cerrar archivo");
            cout << "Archivo '" << nombre << "' cerrado" << endl;
        }
    }

    void procesar() {
        if (!abierto) {
            throw runtime_error("Archivo no está abierto");
        }
        cout << "Procesando archivo '" << nombre << "'" << endl;
    }
};

int main() {
    cout << "=== TRY-CATCH EN C++ ===" << endl;

    // 1. Captura básica de excepciones
    cout << "\n--- CAPTURA BÁSICA ---" << endl;

    try {
        double resultado = calcularRaizCuadrada(-4);
        cout << "Raíz cuadrada: " << resultado << endl;
    } catch (const ErrorMatematico& e) {
        cout << "Error matemático: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "Otra excepción: " << e.what() << endl;
    }

    try {
        double resultado = calcularRaizCuadrada(16);
        cout << "Raíz cuadrada de 16: " << resultado << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    // 2. Múltiples tipos de excepciones
    cout << "\n--- MÚLTIPLES TIPOS DE EXCEPCIONES ---" << endl;

    vector<pair<string, function<void()>>> operaciones = {
        {"División por cero", []() { dividir(10, 0); }},
        {"División normal", []() { cout << "Resultado: " << dividir(10, 2) << endl; }},
        {"Raíz de negativo", []() { calcularRaizCuadrada(-1); }},
        {"Raíz normal", []() { cout << "Raíz: " << calcularRaizCuadrada(9) << endl; }}
    };

    for (const auto& [descripcion, operacion] : operaciones) {
        cout << "Ejecutando: " << descripcion << endl;
        try {
            operacion();
        } catch (const ErrorMatematico& e) {
            cout << "  ErrorMatematico: " << e.what() << endl;
        } catch (const domain_error& e) {
            cout << "  Domain error: " << e.what() << endl;
        } catch (const exception& e) {
            cout << "  Exception general: " << e.what() << endl;
        }
    }

    // 3. Validación con excepciones personalizadas
    cout << "\n--- VALIDACIÓN CON EXCEPCIONES PERSONALIZADAS ---" << endl;

    vector<tuple<string, int, double>> personas = {
        {"Juan", 25, 30000.0},
        {"", 30, 25000.0},
        {"María", -5, 35000.0},
        {"Pedro", 40, -1000.0},
        {"Ana", 28, 28000.0}
    };

    for (const auto& [nombre, edad, salario] : personas) {
        try {
            validarPersona(nombre, edad, salario);
            cout << "Persona válida: " << nombre << " (" << edad << " años, $" << salario << ")" << endl;
        } catch (const ErrorValidacion& e) {
            cout << "Error de validación en '" << e.obtenerCampo() << "': " << e.what() << endl;
        } catch (const out_of_range& e) {
            cout << "Error de rango: " << e.what() << endl;
        }
    }

    // 4. Manejo de archivos con excepciones
    cout << "\n--- MANEJO DE ARCHIVOS ---" << endl;

    vector<string> archivos = {"datos.txt", "archivo_inexistente.txt", "archivo_vacio.txt"};

    for (const string& archivo : archivos) {
        try {
            procesarArchivo(archivo);
            cout << "Archivo '" << archivo << "' procesado correctamente" << endl;
        } catch (const ErrorArchivo& e) {
            cout << "ErrorArchivo: " << e.what() << endl;
        } catch (const exception& e) {
            cout << "Error general al procesar '" << archivo << "': " << e.what() << endl;
        }
    }

    // 5. Diferentes tipos de excepciones
    cout << "\n--- DIFERENTES TIPOS DE EXCEPCIONES ---" << endl;

    for (int i = 1; i <= 6; i++) {
        cout << "Probando tipo de error " << i << ": ";
        try {
            funcionQuePuedeFallar(i);
            cout << "Sin error" << endl;
        } catch (const runtime_error& e) {
            cout << "Runtime error: " << e.what() << endl;
        } catch (const invalid_argument& e) {
            cout << "Invalid argument: " << e.what() << endl;
        } catch (const out_of_range& e) {
            cout << "Out of range: " << e.what() << endl;
        } catch (const bad_alloc& e) {
            cout << "Bad alloc: " << e.what() << endl;
        } catch (const char* str) {
            cout << "Cadena C: " << str << endl;
        } catch (const ErrorMatematico& e) {
            cout << "ErrorMatematico: " << e.what() << endl;
        } catch (...) {
            cout << "Excepción desconocida" << endl;
        }
    }

    // 6. Re-lanzamiento de excepciones
    cout << "\n--- RE-LANZAMIENTO DE EXCEPCIONES ---" << endl;

    for (int valor : {-1, 1, 2, 6}) {
        try {
            funcionConRelanzamiento(valor);
            cout << "Operación completada para valor " << valor << endl;
        } catch (const invalid_argument& e) {
            cout << "Re-capturado invalid_argument: " << e.what() << endl;
        } catch (const ErrorMatematico& e) {
            cout << "Capturado ErrorMatematico convertido: " << e.what() << endl;
        } catch (const exception& e) {
            cout << "Otra excepción: " << e.what() << endl;
        }
    }

    // 7. Orden de captura y catch-all
    cout << "\n--- ORDEN DE CAPTURA Y CATCH-ALL ---" << endl;

    try {
        throw runtime_error("Error de prueba");
    } catch (const exception& e) {
        cout << "Capturado como exception: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cout << "Esto nunca se ejecuta porque exception está primero" << endl;
    }

    // Correcto orden: específico antes que general
    try {
        throw runtime_error("Error de prueba 2");
    } catch (const runtime_error& e) {
        cout << "Capturado como runtime_error: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "Capturado como exception: " << e.what() << endl;
    }

    // Catch-all
    try {
        throw 42;  // int no derivado de exception
    } catch (int valor) {
        cout << "Capturado int: " << valor << endl;
    } catch (...) {
        cout << "Capturado con catch-all" << endl;
    }

    // 8. Excepciones en constructores y destructores
    cout << "\n--- EXCEPCIONES EN CONSTRUCTORES ---" << endl;

    try {
        ArchivoPeligroso archivo("test.txt");
        archivo.procesar();

        // Simular error
        throw runtime_error("Error durante procesamiento");

    } catch (const exception& e) {
        cout << "Error capturado: " << e.what() << endl;
        // El destructor de ArchivoPeligroso se ejecuta aquí
    }

    // 9. Try-catch anidados
    cout << "\n--- TRY-CATCH ANIDADOS ---" << endl;

    try {
        try {
            dividir(10, 0);
        } catch (const ErrorMatematico& e) {
            cout << "Capturado en try interno: " << e.what() << endl;
            throw runtime_error("Error propagado desde try interno");
        }
    } catch (const runtime_error& e) {
        cout << "Capturado en try externo: " << e.what() << endl;
    }

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;

    return 0;
}
```

## Tipos de Captura

### Captura por Valor (Incorrecto)
```cpp
try {
    throw runtime_error("Error");
} catch (exception e) {  // ❌ Problema de slicing
    cout << e.what() << endl;
}
```

### Captura por Referencia (Correcto)
```cpp
try {
    throw runtime_error("Error");
} catch (const exception& e) {  // ✅ Correcto
    cout << e.what() << endl;
}
```

### Captura por Puntero
```cpp
try {
    throw new runtime_error("Error");
} catch (const exception* e) {  // Para excepciones lanzadas como punteros
    cout << e->what() << endl;
    delete e;
}
```

## Orden de Captura Importante

```cpp
try {
    // código
} catch (const DerivedException& e) {  // Específico primero
    // manejar DerivedException
} catch (const BaseException& e) {     // Base después
    // manejar BaseException
} catch (...) {                        // Catch-all al final
    // manejar cualquier cosa
}
```

## Re-lanzamiento

### Re-lanzar la misma excepción
```cpp
catch (const exception& e) {
    // Hacer algo
    throw;  // Re-lanza la excepción original
}
```

### Convertir y re-lanzar
```cpp
catch (const exception& e) {
    // Convertir a otro tipo
    throw runtime_error(string("Error convertido: ") + e.what());
}
```

## Catch-All

```cpp
try {
    funcionQuePuedeFallar();
} catch (...) {
    // Captura cualquier excepción
    cout << "Ocurrió algún error" << endl;
}
```

## Mejores Prácticas

### ✅ Capturar por Referencia Constante
```cpp
catch (const exception& e)  // Correcto
catch (exception& e)       // Aceptable pero menos seguro
catch (exception e)        // Incorrecto - slicing
```

### ✅ Orden Específico → General
```cpp
catch (const runtime_error& e) { /* específico */ }
catch (const exception& e) {     /* general */ }
catch (...) {                    /* catch-all */ }
```

### ✅ Manejar Recursos con RAII
```cpp
class Archivo {
    FILE* handle;
public:
    Archivo(string nombre) : handle(fopen(nombre.c_str(), "r")) {
        if (!handle) throw runtime_error("No se pudo abrir");
    }
    ~Archivo() { if (handle) fclose(handle); }
    // Se cierra automáticamente si hay excepción
};
```

### ✅ No Lanzar en Destructores
```cpp
~MiClase() {
    try {
        guardarDatos();
    } catch (...) {
        // NO re-lanzar - usar logs o similar
        cerr << "Error al guardar en destructor" << endl;
    }
}
```

## Casos de Uso Comunes

### Manejo de Errores en APIs
```cpp
Usuario* cargarUsuario(int id) {
    try {
        return db.findUsuario(id);
    } catch (const DBException& e) {
        throw UserNotFoundException(id);
    }
}
```

### Logging de Errores
```cpp
try {
    procesarDatos();
} catch (const exception& e) {
    logger.error("Error procesando datos: " + string(e.what()));
    throw;  // Re-lanzar después de loggear
}
```

### Limpieza de Recursos
```cpp
void funcionCompleja() {
    Recurso* r = nullptr;
    try {
        r = new Recurso();
        r->usar();
        // más código...
    } catch (...) {
        delete r;  // Limpieza manual
        throw;
    }
    delete r;  // Limpieza normal
}
```

### Validación de Entrada
```cpp
void procesarEntrada(const string& entrada) {
    try {
        validarFormato(entrada);
        procesar(entrada);
    } catch (const FormatoInvalidoException& e) {
        mostrarMensajeError(e.what());
    } catch (const exception& e) {
        mostrarMensajeError("Error interno: " + string(e.what()));
    }
}
```