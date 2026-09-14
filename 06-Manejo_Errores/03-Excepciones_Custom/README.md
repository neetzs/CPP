# 03 - Excepciones Custom

## Concepto Clave
Las excepciones personalizadas permiten crear tipos de error específicos para tu aplicación, proporcionando información detallada sobre qué salió mal y dónde. Heredan de las clases de excepción estándar de C++.

## Sintaxis Básica

```cpp
#include <stdexcept>
#include <string>

class MiExcepcion : public std::runtime_error {
private:
    int codigoError;
    std::string contexto;

public:
    MiExcepcion(int codigo, const std::string& mensaje, const std::string& ctx = "")
        : std::runtime_error(mensaje), codigoError(codigo), contexto(ctx) {}

    int obtenerCodigo() const { return codigoError; }
    std::string obtenerContexto() const { return contexto; }
};
```

## Jerarquía de Excepciones Personalizadas

```
std::exception
├── MiExcepcionBase
│   ├── ErrorValidacion
│   │   ├── CampoRequeridoException
│   │   ├── FormatoInvalidoException
│   │   └── RangoInvalidoException
│   ├── ErrorBaseDatos
│   │   ├── ConexionException
│   │   ├── QueryException
│   │   └── TransaccionException
│   └── ErrorArchivo
│       ├── ArchivoNoEncontradoException
│       ├── PermisosException
│       └── FormatoArchivoException
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <sstream>
using namespace std;

// Clase base para excepciones personalizadas
class MiExcepcionBase : public exception {
protected:
    string mensaje;
    string archivo;
    int linea;
    chrono::system_clock::time_point timestamp;

public:
    MiExcepcionBase(const string& msg, const string& file = "", int line = 0)
        : mensaje(msg), archivo(file), linea(line), timestamp(chrono::system_clock::now()) {}

    const char* what() const noexcept override {
        return mensaje.c_str();
    }

    string obtenerArchivo() const { return archivo; }
    int obtenerLinea() const { return linea; }
    string obtenerTimestamp() const {
        auto time_t = chrono::system_clock::to_time_t(timestamp);
        return string(ctime(&time_t));
    }

    virtual string obtenerTipo() const = 0;
    virtual int obtenerCodigoError() const = 0;
};

// Excepciones de validación
class ErrorValidacion : public MiExcepcionBase {
private:
    string campo;
    string valorInvalido;

public:
    ErrorValidacion(const string& campo, const string& valor, const string& msg,
                   const string& file = "", int line = 0)
        : MiExcepcionBase(msg, file, line), campo(campo), valorInvalido(valor) {}

    string obtenerCampo() const { return campo; }
    string obtenerValorInvalido() const { return valorInvalido; }
    string obtenerTipo() const override { return "ErrorValidacion"; }
    int obtenerCodigoError() const override { return 1000; }

    string obtenerDetalles() const {
        ostringstream oss;
        oss << obtenerTipo() << " en campo '" << campo << "' con valor '" << valorInvalido
            << "': " << mensaje;
        if (!archivo.empty()) {
            oss << " (archivo: " << archivo << ", línea: " << linea << ")";
        }
        return oss.str();
    }
};

class CampoRequeridoException : public ErrorValidacion {
public:
    CampoRequeridoException(const string& campo, const string& file = "", int line = 0)
        : ErrorValidacion(campo, "", "Campo requerido no proporcionado", file, line) {}

    string obtenerTipo() const override { return "CampoRequeridoException"; }
    int obtenerCodigoError() const override { return 1001; }
};

class FormatoInvalidoException : public ErrorValidacion {
private:
    string formatoEsperado;

public:
    FormatoInvalidoException(const string& campo, const string& valor, const string& formato,
                           const string& file = "", int line = 0)
        : ErrorValidacion(campo, valor, "Formato inválido. Esperado: " + formato, file, line),
          formatoEsperado(formato) {}

    string obtenerFormatoEsperado() const { return formatoEsperado; }
    string obtenerTipo() const override { return "FormatoInvalidoException"; }
    int obtenerCodigoError() const override { return 1002; }
};

class RangoInvalidoException : public ErrorValidacion {
private:
    double valorMinimo;
    double valorMaximo;

public:
    RangoInvalidoException(const string& campo, const string& valor, double min, double max,
                          const string& file = "", int line = 0)
        : ErrorValidacion(campo, valor, "Valor fuera de rango [" + to_string(min) + ", " + to_string(max) + "]", file, line),
          valorMinimo(min), valorMaximo(max) {}

    double obtenerMinimo() const { return valorMinimo; }
    double obtenerMaximo() const { return valorMaximo; }
    string obtenerTipo() const override { return "RangoInvalidoException"; }
    int obtenerCodigoError() const override { return 1003; }
};

// Excepciones de base de datos
class ErrorBaseDatos : public MiExcepcionBase {
private:
    string consultaSQL;
    int codigoBD;

public:
    ErrorBaseDatos(const string& msg, const string& sql = "", int codigo = 0,
                  const string& file = "", int line = 0)
        : MiExcepcionBase(msg, file, line), consultaSQL(sql), codigoBD(codigo) {}

    string obtenerConsultaSQL() const { return consultaSQL; }
    int obtenerCodigoBD() const { return codigoBD; }
    string obtenerTipo() const override { return "ErrorBaseDatos"; }
    int obtenerCodigoError() const override { return 2000; }
};

class ConexionException : public ErrorBaseDatos {
private:
    string servidor;
    int puerto;

public:
    ConexionException(const string& servidor, int puerto, const string& msg = "",
                     const string& file = "", int line = 0)
        : ErrorBaseDatos("Error de conexión a " + servidor + ":" + to_string(puerto) + " - " + msg,
                        "", 0, file, line), servidor(servidor), puerto(puerto) {}

    string obtenerServidor() const { return servidor; }
    int obtenerPuerto() const { return puerto; }
    string obtenerTipo() const override { return "ConexionException"; }
    int obtenerCodigoError() const override { return 2001; }
};

class QueryException : public ErrorBaseDatos {
private:
    string tabla;

public:
    QueryException(const string& sql, const string& tabla, const string& msg,
                  const string& file = "", int line = 0)
        : ErrorBaseDatos(msg, sql, 0, file, line), tabla(tabla) {}

    string obtenerTabla() const { return tabla; }
    string obtenerTipo() const override { return "QueryException"; }
    int obtenerCodigoError() const override { return 2002; }
};

// Excepciones de archivo
class ErrorArchivo : public MiExcepcionBase {
private:
    string nombreArchivo;
    string operacion;

public:
    ErrorArchivo(const string& archivo, const string& operacion, const string& msg,
                const string& file = "", int line = 0)
        : MiExcepcionBase(msg, file, line), nombreArchivo(archivo), operacion(operacion) {}

    string obtenerNombreArchivo() const { return nombreArchivo; }
    string obtenerOperacion() const { return operacion; }
    string obtenerTipo() const override { return "ErrorArchivo"; }
    int obtenerCodigoError() const override { return 3000; }
};

class ArchivoNoEncontradoException : public ErrorArchivo {
public:
    ArchivoNoEncontradoException(const string& archivo, const string& file = "", int line = 0)
        : ErrorArchivo(archivo, "lectura", "Archivo no encontrado", file, line) {}

    string obtenerTipo() const override { return "ArchivoNoEncontradoException"; }
    int obtenerCodigoError() const override { return 3001; }
};

class PermisosException : public ErrorArchivo {
private:
    string permisosRequeridos;

public:
    PermisosException(const string& archivo, const string& operacion, const string& permisos,
                     const string& file = "", int line = 0)
        : ErrorArchivo(archivo, operacion, "Permisos insuficientes. Requeridos: " + permisos, file, line),
          permisosRequeridos(permisos) {}

    string obtenerPermisosRequeridos() const { return permisosRequeridos; }
    string obtenerTipo() const override { return "PermisosException"; }
    int obtenerCodigoError() const override { return 3002; }
};

// Macros para facilitar el lanzamiento de excepciones con información de archivo y línea
#define LANZAR_EXCEPCION(tipo, ...) tipo(__VA_ARGS__, __FILE__, __LINE__)

// Funciones que usan las excepciones personalizadas
void validarUsuario(const string& nombre, int edad, double salario) {
    if (nombre.empty()) {
        LANZAR_EXCEPCION(CampoRequeridoException, "nombre");
    }

    if (edad < 18 || edad > 65) {
        LANZAR_EXCEPCION(RangoInvalidoException, "edad", to_string(edad), 18.0, 65.0);
    }

    if (salario < 0) {
        LANZAR_EXCEPCION(RangoInvalidoException, "salario", to_string(salario), 0.0, 999999.0);
    }

    // Validar formato de nombre (solo letras y espacios)
    for (char c : nombre) {
        if (!isalpha(c) && !isspace(c)) {
            LANZAR_EXCEPCION(FormatoInvalidoException, "nombre", nombre, "solo letras y espacios");
        }
    }
}

void conectarBaseDatos(const string& servidor, int puerto) {
    // Simular conexión fallida
    if (servidor == "servidor_fallido") {
        LANZAR_EXCEPCION(ConexionException, servidor, puerto, "Servidor no responde");
    }

    if (puerto <= 0 || puerto > 65535) {
        LANZAR_EXCEPCION(ConexionException, servidor, puerto, "Puerto inválido");
    }

    cout << "Conectado a " << servidor << ":" << puerto << endl;
}

void ejecutarConsulta(const string& sql, const string& tabla) {
    // Simular errores de consulta
    if (sql.find("SELECT") == 0 && tabla == "usuarios_inexistentes") {
        LANZAR_EXCEPCION(QueryException, sql, tabla, "Tabla no existe");
    }

    if (sql.find("INSERT") == 0 && sql.find("NULL") != string::npos) {
        LANZAR_EXCEPCION(QueryException, sql, tabla, "No se permiten valores NULL");
    }

    cout << "Consulta ejecutada: " << sql << endl;
}

void procesarArchivo(const string& nombreArchivo) {
    // Simular errores de archivo
    if (nombreArchivo == "archivo_inexistente.txt") {
        LANZAR_EXCEPCION(ArchivoNoEncontradoException, nombreArchivo);
    }

    if (nombreArchivo == "archivo_sin_permisos.txt") {
        LANZAR_EXCEPCION(PermisosException, nombreArchivo, "lectura", "lectura");
    }

    cout << "Archivo '" << nombreArchivo << "' procesado correctamente" << endl;
}

// Función que demuestra el manejo de múltiples tipos de excepciones
void procesarDatosUsuario(const string& nombre, int edad, double salario,
                         const string& servidor, int puerto, const string& archivo) {
    try {
        // Validar datos del usuario
        validarUsuario(nombre, edad, salario);
        cout << "✓ Usuario validado: " << nombre << endl;

        // Conectar a base de datos
        conectarBaseDatos(servidor, puerto);

        // Ejecutar consulta
        string sql = "INSERT INTO usuarios VALUES ('" + nombre + "', " + to_string(edad) + ", " + to_string(salario) + ")";
        ejecutarConsulta(sql, "usuarios");

        // Procesar archivo
        procesarArchivo(archivo);

        cout << "✓ Todos los pasos completados exitosamente" << endl;

    } catch (const CampoRequeridoException& e) {
        cerr << "❌ Campo requerido faltante: " << e.obtenerDetalles() << endl;
        throw; // Re-lanzar
    } catch (const FormatoInvalidoException& e) {
        cerr << "❌ Formato inválido: " << e.obtenerDetalles() <<
             " (esperado: " << e.obtenerFormatoEsperado() << ")" << endl;
        throw;
    } catch (const RangoInvalidoException& e) {
        cerr << "❌ Valor fuera de rango: " << e.obtenerDetalles() <<
             " (rango: " << e.obtenerMinimo() << " - " << e.obtenerMaximo() << ")" << endl;
        throw;
    } catch (const ConexionException& e) {
        cerr << "❌ Error de conexión: " << e.what() <<
             " (servidor: " << e.obtenerServidor() << ", puerto: " << e.obtenerPuerto() << ")" << endl;
        throw;
    } catch (const QueryException& e) {
        cerr << "❌ Error de consulta: " << e.what() <<
             " (tabla: " << e.obtenerTabla() << ")" << endl;
        if (!e.obtenerConsultaSQL().empty()) {
            cerr << "   SQL: " << e.obtenerConsultaSQL() << endl;
        }
        throw;
    } catch (const ArchivoNoEncontradoException& e) {
        cerr << "❌ Archivo no encontrado: " << e.what() <<
             " (operación: " << e.obtenerOperacion() << ")" << endl;
        throw;
    } catch (const PermisosException& e) {
        cerr << "❌ Error de permisos: " << e.what() <<
             " (requeridos: " << e.obtenerPermisosRequeridos() << ")" << endl;
        throw;
    } catch (const MiExcepcionBase& e) {
        cerr << "❌ Error personalizado: [" << e.obtenerCodigoError() << "] " << e.what() << endl;
        if (!e.obtenerArchivo().empty()) {
            cerr << "   Ubicación: " << e.obtenerArchivo() << ":" << e.obtenerLinea() << endl;
        }
        throw;
    } catch (const exception& e) {
        cerr << "❌ Error estándar: " << e.what() << endl;
        throw;
    }
}

int main() {
    cout << "=== EXCEPCIONES PERSONALIZADAS EN C++ ===" << endl;

    // Casos de prueba
    vector<tuple<string, int, double, string, int, string>> casosPrueba = {
        // Caso válido
        {"Juan Pérez", 30, 50000.0, "localhost", 5432, "datos.txt"},

        // Errores de validación
        {"", 30, 50000.0, "localhost", 5432, "datos.txt"},                           // Nombre vacío
        {"Juan123", 30, 50000.0, "localhost", 5432, "datos.txt"},                   // Nombre con números
        {"María García", 15, 50000.0, "localhost", 5432, "datos.txt"},              // Edad muy baja
        {"Pedro López", 70, 50000.0, "localhost", 5432, "datos.txt"},               // Edad muy alta
        {"Ana Ruiz", 25, -1000.0, "localhost", 5432, "datos.txt"},                  // Salario negativo

        // Errores de conexión
        {"Carlos Díaz", 35, 40000.0, "servidor_fallido", 5432, "datos.txt"},        // Servidor fallido
        {"Luis Martín", 28, 45000.0, "localhost", -1, "datos.txt"},                 // Puerto inválido

        // Errores de archivo
        {"Sofia Hernández", 32, 55000.0, "localhost", 5432, "archivo_inexistente.txt"}, // Archivo no existe
        {"Miguel Torres", 40, 60000.0, "localhost", 5432, "archivo_sin_permisos.txt"}   // Sin permisos
    };

    for (size_t i = 0; i < casosPrueba.size(); i++) {
        auto [nombre, edad, salario, servidor, puerto, archivo] = casosPrueba[i];

        cout << "\n--- PRUEBA " << (i + 1) << " ---" << endl;
        cout << "Datos: " << nombre << ", " << edad << " años, $" << salario
             << ", servidor: " << servidor << ":" << puerto
             << ", archivo: " << archivo << endl;

        try {
            procesarDatosUsuario(nombre, edad, salario, servidor, puerto, archivo);
        } catch (const MiExcepcionBase& e) {
            cout << "Timestamp: " << e.obtenerTimestamp();
            // Error ya fue mostrado en procesarDatosUsuario
        } catch (const exception& e) {
            cout << "Error no personalizado capturado: " << e.what() << endl;
        }
    }

    // Demostración de jerarquía de excepciones
    cout << "\n--- JERARQUÍA DE EXCEPCIONES ---" << endl;

    vector<reference_wrapper<MiExcepcionBase>> excepciones;

    try { validarUsuario("", 25, 30000); }
    catch (const CampoRequeridoException& e) { excepciones.push_back(ref(e)); }

    try { validarUsuario("Juan", 100, 30000); }
    catch (const RangoInvalidoException& e) { excepciones.push_back(ref(e)); }

    try { conectarBaseDatos("bad_server", 3306); }
    catch (const ConexionException& e) { excepciones.push_back(ref(e)); }

    try { procesarArchivo("missing.txt"); }
    catch (const ArchivoNoEncontradoException& e) { excepciones.push_back(ref(e)); }

    for (const auto& exc : excepciones) {
        cout << "Tipo: " << exc.get().obtenerTipo()
             << " (código: " << exc.get().obtenerCodigoError() << ")" << endl;
        cout << "Mensaje: " << exc.get().what() << endl;
        cout << "---" << endl;
    }

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;

    return 0;
}
```

## Ventajas de Excepciones Personalizadas

### ✅ Información Específica
- Mensajes de error detallados
- Información contextual (archivo, línea, timestamp)
- Códigos de error únicos

### ✅ Jerarquía Organizada
- Herencia permite captura por categorías
- Polimorfismo para manejo genérico
- Extensibilidad fácil

### ✅ Debugging Mejorado
- Información de ubicación del error
- Contexto adicional (campos, valores, operaciones)
- Códigos de error para lookup

## Mejores Prácticas

### ✅ Herencia Consistente
```cpp
class MiExcepcion : public std::runtime_error {
    // Para errores de ejecución
};

class ErrorValidacion : public std::logic_error {
    // Para errores de lógica/invalid arguments
};
```

### ✅ Constructores Informativos
```cpp
class MiExcepcion {
public:
    MiExcepcion(const std::string& mensaje, const std::string& contexto = "",
               const char* archivo = "", int linea = 0);
};
```

### ✅ Métodos de Acceso
```cpp
class MiExcepcion {
public:
    std::string obtenerTipo() const;
    int obtenerCodigo() const;
    std::string obtenerContexto() const;
    std::string obtenerArchivo() const;
    int obtenerLinea() const;
};
```

### ✅ Macros para Debugging
```cpp
#define LANZAR_EXCEPCION(tipo, ...) tipo(__VA_ARGS__, __FILE__, __LINE__)
```

## Casos de Uso

### Sistema de Logging
```cpp
class Logger {
public:
    void logException(const MiExcepcionBase& e) {
        cout << "[" << e.obtenerTimestamp() << "] "
             << e.obtenerTipo() << "(" << e.obtenerCodigoError() << "): "
             << e.what() << endl;

        if (!e.obtenerArchivo().empty()) {
            cout << "  Ubicación: " << e.obtenerArchivo() << ":" << e.obtenerLinea() << endl;
        }
    }
};
```

### API con Códigos de Error
```cpp
enum class CodigosError {
    VALIDACION_NOMBRE = 1001,
    VALIDACION_EDAD = 1002,
    CONEXION_BD = 2001,
    ARCHIVO_NO_ENCONTRADO = 3001
};

int obtenerCodigoHttp(const MiExcepcionBase& e) {
    switch (e.obtenerCodigoError()) {
        case 1000 ... 1999: return 400;  // Bad Request
        case 2000 ... 2999: return 503;  // Service Unavailable
        case 3000 ... 3999: return 404;  // Not Found
        default: return 500;             // Internal Server Error
    }
}
```

### Serialización de Errores
```cpp
std::string serializarExcepcion(const MiExcepcionBase& e) {
    return "{"
        "\"tipo\": \"" + e.obtenerTipo() + "\","
        "\"codigo\": " + std::to_string(e.obtenerCodigoError()) + ","
        "\"mensaje\": \"" + e.what() + "\","
        "\"archivo\": \"" + e.obtenerArchivo() + "\","
        "\"linea\": " + std::to_string(e.obtenerLinea()) +
    "}";
}
```