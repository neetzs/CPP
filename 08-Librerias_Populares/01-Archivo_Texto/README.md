# 01 - Archivo Texto

## Concepto Clave
El manejo de archivos de texto en C++ se realiza principalmente con las clases `ifstream` (lectura), `ofstream` (escritura) y `fstream` (lectura/escritura) de la biblioteca estándar. Estas clases heredan de `istream` y `ostream`, permitiendo usar los operadores `>>` y `<<`.

## Sintaxis Básica

### Escritura en Archivo
```cpp
#include <fstream>

ofstream archivo("archivo.txt");
if (archivo.is_open()) {
    archivo << "Hola mundo" << endl;
    archivo.close();
}
```

### Lectura de Archivo
```cpp
#include <fstream>
#include <string>

ifstream archivo("archivo.txt");
if (archivo.is_open()) {
    string linea;
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }
    archivo.close();
}
```

### Modos de Apertura
```cpp
ios::in      // Lectura
ios::out     // Escritura (borra contenido existente)
ios::app     // Añadir al final
ios::trunc   // Borrar contenido (por defecto con out)
ios::binary  // Modo binario
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

// Estructura para representar una persona
struct Persona {
    string nombre;
    int edad;
    double salario;
    string email;

    // Constructor
    Persona(const string& n = "", int e = 0, double s = 0.0, const string& em = "")
        : nombre(n), edad(e), salario(s), email(em) {}

    // Método para convertir a string (para escritura)
    string toString() const {
        ostringstream oss;
        oss << nombre << "," << edad << "," << fixed << setprecision(2) << salario << "," << email;
        return oss.str();
    }

    // Método para cargar desde string (para lectura)
    static Persona fromString(const string& linea) {
        Persona p;
        stringstream ss(linea);
        string token;

        getline(ss, p.nombre, ',');
        getline(ss, token, ',');
        p.edad = stoi(token);
        getline(ss, token, ',');
        p.salario = stod(token);
        getline(ss, p.email, ',');

        return p;
    }

    // Método para mostrar
    void mostrar() const {
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << " años" << endl;
        cout << "Salario: $" << fixed << setprecision(2) << salario << endl;
        cout << "Email: " << email << endl;
        cout << "---" << endl;
    }
};

// Clase para manejar archivos CSV de personas
class GestorPersonas {
private:
    string nombreArchivo;

public:
    GestorPersonas(const string& archivo) : nombreArchivo(archivo) {}

    // Guardar lista de personas en archivo CSV
    bool guardarPersonas(const vector<Persona>& personas) {
        ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cerr << "Error: No se pudo abrir el archivo para escritura: " << nombreArchivo << endl;
            return false;
        }

        // Escribir encabezado
        archivo << "Nombre,Edad,Salario,Email" << endl;

        // Escribir cada persona
        for (const auto& persona : personas) {
            archivo << persona.toString() << endl;
        }

        archivo.close();
        cout << "✓ " << personas.size() << " personas guardadas en " << nombreArchivo << endl;
        return true;
    }

    // Cargar personas desde archivo CSV
    vector<Persona> cargarPersonas() {
        vector<Persona> personas;
        ifstream archivo(nombreArchivo);

        if (!archivo.is_open()) {
            cerr << "Error: No se pudo abrir el archivo para lectura: " << nombreArchivo << endl;
            return personas;
        }

        string linea;
        bool primeraLinea = true;

        while (getline(archivo, linea)) {
            if (primeraLinea) {
                primeraLinea = false;  // Saltar encabezado
                continue;
            }

            if (!linea.empty()) {
                try {
                    Persona p = Persona::fromString(linea);
                    personas.push_back(p);
                } catch (const exception& e) {
                    cerr << "Error al parsear línea: " << linea << " - " << e.what() << endl;
                }
            }
        }

        archivo.close();
        cout << "✓ " << personas.size() << " personas cargadas desde " << nombreArchivo << endl;
        return personas;
    }

    // Añadir una persona al final del archivo
    bool aniadirPersona(const Persona& persona) {
        ofstream archivo(nombreArchivo, ios::app);
        if (!archivo.is_open()) {
            cerr << "Error: No se pudo abrir el archivo para añadir: " << nombreArchivo << endl;
            return false;
        }

        archivo << persona.toString() << endl;
        archivo.close();
        cout << "✓ Persona añadida a " << nombreArchivo << endl;
        return true;
    }
};

// Funciones de utilidad para manejo de archivos
class UtilidadesArchivo {
public:
    // Verificar si un archivo existe
    static bool archivoExiste(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        return archivo.good();
    }

    // Obtener el tamaño de un archivo en bytes
    static long long obtenerTamanioArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo, ios::binary | ios::ate);
        if (!archivo.is_open()) return -1;
        return archivo.tellg();
    }

    // Contar líneas en un archivo
    static int contarLineas(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) return -1;

        int lineas = 0;
        string linea;
        while (getline(archivo, linea)) {
            lineas++;
        }
        return lineas;
    }

    // Copiar un archivo
    static bool copiarArchivo(const string& origen, const string& destino) {
        ifstream archivoOrigen(origen, ios::binary);
        ofstream archivoDestino(destino, ios::binary);

        if (!archivoOrigen.is_open() || !archivoDestino.is_open()) {
            return false;
        }

        archivoDestino << archivoOrigen.rdbuf();
        return true;
    }

    // Leer archivo completo como string
    static string leerArchivoCompleto(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            return "";
        }

        ostringstream oss;
        oss << archivo.rdbuf();
        return oss.str();
    }

    // Escribir string a archivo
    static bool escribirArchivo(const string& nombreArchivo, const string& contenido) {
        ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            return false;
        }

        archivo << contenido;
        return archivo.good();
    }

    // Buscar texto en archivo
    static vector<int> buscarEnArchivo(const string& nombreArchivo, const string& textoBuscar) {
        vector<int> lineasEncontradas;
        ifstream archivo(nombreArchivo);

        if (!archivo.is_open()) {
            return lineasEncontradas;
        }

        string linea;
        int numeroLinea = 1;

        while (getline(archivo, linea)) {
            if (linea.find(textoBuscar) != string::npos) {
                lineasEncontradas.push_back(numeroLinea);
            }
            numeroLinea++;
        }

        return lineasEncontradas;
    }
};

// Función para demostrar escritura básica
void demostrarEscrituraBasica() {
    cout << "\n=== ESCRITURA BÁSICA ===" << endl;

    // Escritura simple
    ofstream archivo1("archivo_simple.txt");
    if (archivo1.is_open()) {
        archivo1 << "Hola mundo!" << endl;
        archivo1 << "Esta es una línea de texto." << endl;
        archivo1 << "Número: " << 42 << endl;
        archivo1.close();
        cout << "✓ Archivo 'archivo_simple.txt' creado" << endl;
    }

    // Escritura con formato
    ofstream archivo2("archivo_formato.txt");
    if (archivo2.is_open()) {
        archivo2 << left << setw(10) << "Nombre" << setw(5) << "Edad" << "Ciudad" << endl;
        archivo2 << left << setw(10) << "Juan" << setw(5) << 25 << "Madrid" << endl;
        archivo2 << left << setw(10) << "María" << setw(5) << 30 << "Barcelona" << endl;
        archivo2.close();
        cout << "✓ Archivo 'archivo_formato.txt' creado con formato" << endl;
    }
}

// Función para demostrar lectura básica
void demostrarLecturaBasica() {
    cout << "\n=== LECTURA BÁSICA ===" << endl;

    // Crear archivo para leer
    ofstream crearArchivo("archivo_lectura.txt");
    crearArchivo << "Línea 1: Hola" << endl;
    crearArchivo << "Línea 2: Mundo" << endl;
    crearArchivo << "Línea 3: C++" << endl;
    crearArchivo.close();

    // Lectura línea por línea
    ifstream archivo("archivo_lectura.txt");
    if (archivo.is_open()) {
        string linea;
        int numeroLinea = 1;

        cout << "Contenido del archivo:" << endl;
        while (getline(archivo, linea)) {
            cout << numeroLinea << ": " << linea << endl;
            numeroLinea++;
        }
        archivo.close();
    }

    // Lectura palabra por palabra
    archivo.open("archivo_lectura.txt");
    if (archivo.is_open()) {
        string palabra;
        cout << "\nPalabras encontradas: ";
        while (archivo >> palabra) {
            cout << "'" << palabra << "' ";
        }
        cout << endl;
        archivo.close();
    }
}

// Función para demostrar modo append
void demostrarModoAppend() {
    cout << "\n=== MODO APPEND ===" << endl;

    // Crear archivo inicial
    ofstream archivo("archivo_append.txt");
    archivo << "Línea inicial" << endl;
    archivo.close();

    // Añadir contenido
    ofstream archivoAppend("archivo_append.txt", ios::app);
    if (archivoAppend.is_open()) {
        archivoAppend << "Línea añadida 1" << endl;
        archivoAppend << "Línea añadida 2" << endl;
        archivoAppend.close();
        cout << "✓ Contenido añadido a 'archivo_append.txt'" << endl;
    }

    // Leer para verificar
    ifstream verificar("archivo_append.txt");
    if (verificar.is_open()) {
        string linea;
        cout << "Contenido final:" << endl;
        while (getline(verificar, linea)) {
            cout << linea << endl;
        }
        verificar.close();
    }
}

// Función para demostrar el gestor de personas
void demostrarGestorPersonas() {
    cout << "\n=== GESTOR DE PERSONAS (CSV) ===" << endl;

    GestorPersonas gestor("personas.csv");

    // Crear algunas personas
    vector<Persona> personas = {
        Persona("Juan Pérez", 25, 50000.50, "juan@email.com"),
        Persona("María García", 30, 60000.75, "maria@email.com"),
        Persona("Carlos López", 35, 55000.25, "carlos@email.com")
    };

    // Guardar personas
    if (gestor.guardarPersonas(personas)) {
        // Cargar personas
        vector<Persona> personasCargadas = gestor.cargarPersonas();

        cout << "\nPersonas cargadas:" << endl;
        for (const auto& p : personasCargadas) {
            p.mostrar();
        }

        // Añadir una persona más
        Persona nuevaPersona("Ana Ruiz", 28, 52000.00, "ana@email.com");
        gestor.aniadirPersona(nuevaPersona);

        // Recargar para verificar
        personasCargadas = gestor.cargarPersonas();
        cout << "Después de añadir: " << personasCargadas.size() << " personas" << endl;
    }
}

// Función para demostrar utilidades de archivo
void demostrarUtilidadesArchivo() {
    cout << "\n=== UTILIDADES DE ARCHIVO ===" << endl;

    // Crear archivo de prueba
    ofstream archivoPrueba("archivo_prueba.txt");
    archivoPrueba << "Línea 1: Hola mundo" << endl;
    archivoPrueba << "Línea 2: Programación en C++" << endl;
    archivoPrueba << "Línea 3: Manejo de archivos" << endl;
    archivoPrueba << "Línea 4: Hola de nuevo" << endl;
    archivoPrueba.close();

    // Verificar existencia
    cout << "¿Existe 'archivo_prueba.txt'? " <<
         (UtilidadesArchivo::archivoExiste("archivo_prueba.txt") ? "Sí" : "No") << endl;

    // Obtener tamaño
    long long tamanio = UtilidadesArchivo::obtenerTamanioArchivo("archivo_prueba.txt");
    cout << "Tamaño del archivo: " << tamanio << " bytes" << endl;

    // Contar líneas
    int lineas = UtilidadesArchivo::contarLineas("archivo_prueba.txt");
    cout << "Número de líneas: " << lineas << endl;

    // Buscar texto
    vector<int> lineasEncontradas = UtilidadesArchivo::buscarEnArchivo("archivo_prueba.txt", "Hola");
    cout << "'Hola' encontrado en líneas: ";
    for (int linea : lineasEncontradas) {
        cout << linea << " ";
    }
    cout << endl;

    // Copiar archivo
    if (UtilidadesArchivo::copiarArchivo("archivo_prueba.txt", "archivo_copia.txt")) {
        cout << "✓ Archivo copiado exitosamente" << endl;
    }

    // Leer archivo completo
    string contenido = UtilidadesArchivo::leerArchivoCompleto("archivo_prueba.txt");
    cout << "\nContenido completo:" << endl << contenido << endl;
}

// Función para demostrar manejo de errores
void demostrarManejoErrores() {
    cout << "\n=== MANEJO DE ERRORES ===" << endl;

    // Intentar abrir archivo inexistente para lectura
    ifstream archivoInexistente("archivo_inexistente.txt");
    if (!archivoInexistente.is_open()) {
        cout << "Error: No se pudo abrir 'archivo_inexistente.txt' para lectura" << endl;
    }

    // Intentar escribir en directorio sin permisos (simulado)
    ofstream archivoSoloLectura("/archivo_solo_lectura.txt");
    if (!archivoSoloLectura.is_open()) {
        cout << "Error: No se pudo abrir archivo para escritura (posible falta de permisos)" << endl;
    }

    // Verificar estado del stream
    ofstream archivo("archivo_estado.txt");
    archivo << "Hola";
    cout << "¿El archivo está en buen estado? " << (archivo.good() ? "Sí" : "No") << endl;
    cout << "¿Error de escritura? " << (archivo.fail() ? "Sí" : "No") << endl;
    archivo.close();
}

int main() {
    cout << "=== MANEJO DE ARCHIVOS DE TEXTO EN C++ ===" << endl;

    demostrarEscrituraBasica();
    demostrarLecturaBasica();
    demostrarModoAppend();
    demostrarGestorPersonas();
    demostrarUtilidadesArchivo();
    demostrarManejoErrores();

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;

    return 0;
}
```

## Modos de Apertura

### Combinaciones Comunes
```cpp
// Lectura
ifstream archivo("file.txt", ios::in);

// Escritura (sobrescribe)
ofstream archivo("file.txt", ios::out);

// Añadir al final
ofstream archivo("file.txt", ios::out | ios::app);

// Lectura y escritura
fstream archivo("file.txt", ios::in | ios::out);

// Crear si no existe, añadir si existe
fstream archivo("file.txt", ios::in | ios::out | ios::app);
```

## Estados de los Streams

### Verificar Estado
```cpp
if (archivo.good()) { /* Todo bien */ }
if (archivo.fail()) { /* Error lógico */ }
if (archivo.bad())  { /* Error grave */ }
if (archivo.eof())  { /* Fin de archivo */ }
```

### Limpiar Estado
```cpp
archivo.clear();  // Limpiar flags de error
archivo.seekg(0); // Ir al inicio para reintentar
```

## Lectura de Archivos

### Línea por Línea
```cpp
string linea;
while (getline(archivo, linea)) {
    // Procesar linea
}
```

### Palabra por Palabra
```cpp
string palabra;
while (archivo >> palabra) {
    // Procesar palabra
}
```

### Carácter por Carácter
```cpp
char c;
while (archivo.get(c)) {
    // Procesar carácter
}
```

## Escritura en Archivos

### Texto Formateado
```cpp
archivo << left << setw(10) << "Nombre" << "Edad" << endl;
archivo << left << setw(10) << nombre << edad << endl;
```

### Números con Precisión
```cpp
archivo << fixed << setprecision(2) << precio << endl;
```

## Manejo de Errores

### Verificar Apertura
```cpp
ifstream archivo("file.txt");
if (!archivo.is_open()) {
    cerr << "Error al abrir archivo" << endl;
    return false;
}
```

### Verificar Operaciones
```cpp
archivo << datos;
if (!archivo) {
    cerr << "Error al escribir" << endl;
}
```

## Mejores Prácticas

### ✅ RAII (Resource Acquisition Is Initialization)
```cpp
void funcion() {
    ofstream archivo("file.txt");
    // Se cierra automáticamente al salir del scope
    archivo << "datos";
} // archivo.close() automático
```

### ✅ Verificar Estado Después de Operaciones
```cpp
archivo << datos;
if (!archivo.good()) {
    // Manejar error
}
```

### ✅ Usar Paths Absolutos Cuando Sea Necesario
```cpp
string ruta = "/home/usuario/archivo.txt";
ofstream archivo(ruta);
```

### ✅ Manejar Excepciones
```cpp
try {
    ifstream archivo("file.txt");
    archivo.exceptions(ifstream::failbit | ifstream::badbit);
    // Ahora lanza excepciones automáticamente
} catch (const ios_base::failure& e) {
    cout << "Error de I/O: " << e.what() << endl;
}
```

## Casos de Uso Comunes

### Archivo de Configuración
```cpp
class Configuracion {
public:
    bool cargarDesdeArchivo(const string& archivo) {
        ifstream file(archivo);
        if (!file.is_open()) return false;

        string linea;
        while (getline(file, linea)) {
            // Parsear configuración
            size_t pos = linea.find('=');
            if (pos != string::npos) {
                string clave = linea.substr(0, pos);
                string valor = linea.substr(pos + 1);
                // Procesar clave-valor
            }
        }
        return true;
    }
};
```

### Log de Aplicación
```cpp
class Logger {
private:
    ofstream archivoLog;
public:
    Logger(const string& archivo) : archivoLog(archivo, ios::app) {}

    void log(const string& mensaje) {
        if (archivoLog.is_open()) {
            auto ahora = chrono::system_clock::now();
            auto tiempo = chrono::system_clock::to_time_t(ahora);
            archivoLog << put_time(gmtime(&tiempo), "%Y-%m-%d %H:%M:%S") << " - " << mensaje << endl;
        }
    }
};
```

### Procesamiento de CSV
```cpp
vector<vector<string>> leerCSV(const string& archivo) {
    vector<vector<string>> datos;
    ifstream file(archivo);

    string linea;
    while (getline(file, linea)) {
        vector<string> fila;
        stringstream ss(linea);
        string campo;

        while (getline(ss, campo, ',')) {
            fila.push_back(campo);
        }
        datos.push_back(fila);
    }

    return datos;
}
```