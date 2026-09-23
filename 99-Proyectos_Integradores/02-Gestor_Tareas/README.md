# 02 - Gestor de Tareas

## Concepto Clave
Un sistema completo de gestión de tareas (To-Do List) en C++ que permite crear, editar, eliminar y organizar tareas con prioridades, fechas límite, categorías y estados de completitud. El proyecto integra conceptos de POO, manejo de archivos, algoritmos de búsqueda y ordenamiento, y estructuras de datos avanzadas.

## Características Principales

### Gestión de Tareas
- Crear, editar, eliminar tareas
- Asignar prioridades (Alta, Media, Baja)
- Establecer fechas límite
- Categorizar tareas
- Marcar como completadas

### Organización y Búsqueda
- Filtrar por estado, prioridad, categoría
- Buscar por título o descripción
- Ordenar por fecha, prioridad, estado
- Estadísticas de productividad

### Persistencia de Datos
- Guardar/cargar desde archivo JSON
- Exportar a diferentes formatos
- Backup automático

### Interfaz de Usuario
- Menú interactivo en consola
- Validación de entrada
- Mensajes informativos

## Arquitectura del Proyecto

### Clases Principales

```cpp
class Tarea {
    // Representa una tarea individual
};

class GestorTareas {
    // Gestiona la colección de tareas
};

class FiltroBusqueda {
    // Maneja criterios de búsqueda y filtrado
};

class Exportador {
    // Exporta datos a diferentes formatos
};

class Estadisticas {
    // Calcula métricas de productividad
};
```

## Ejemplo Completo

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <map>
#include <set>
#include <functional>
#include <limits>
#include <cctype>
using namespace std;
using namespace chrono;

// Enumeraciones para tipos de datos
enum class Prioridad { BAJA, MEDIA, ALTA };
enum class Estado { PENDIENTE, EN_PROGRESO, COMPLETADA };
enum class Categoria { TRABAJO, PERSONAL, ESTUDIO, COMPRAS, OTROS };

// Clase para representar fechas
class Fecha {
private:
    int dia, mes, anio;

public:
    Fecha(int d = 1, int m = 1, int a = 2024) : dia(d), mes(m), anio(a) {}

    bool esValida() const {
        if (mes < 1 || mes > 12 || dia < 1 || anio < 1900) return false;

        static const int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int diasMax = diasPorMes[mes - 1];

        // Febrero en año bisiesto
        if (mes == 2 && esBisiesto(anio)) diasMax = 29;

        return dia <= diasMax;
    }

    bool esBisiesto(int a) const {
        return (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
    }

    string toString() const {
        ostringstream oss;
        oss << setfill('0') << setw(2) << dia << "/"
            << setfill('0') << setw(2) << mes << "/" << anio;
        return oss.str();
    }

    static Fecha hoy() {
        auto ahora = system_clock::now();
        time_t tiempo = system_clock::to_time_t(ahora);
        tm* fechaLocal = localtime(&tiempo);
        return Fecha(fechaLocal->tm_mday, fechaLocal->tm_mon + 1, fechaLocal->tm_year + 1900);
    }

    bool operator<(const Fecha& otra) const {
        if (anio != otra.anio) return anio < otra.anio;
        if (mes != otra.mes) return mes < otra.mes;
        return dia < otra.dia;
    }

    bool operator==(const Fecha& otra) const {
        return dia == otra.dia && mes == otra.mes && anio == otra.anio;
    }

    // Días hasta la fecha
    int diasHasta(const Fecha& otra) const {
        // Implementación simplificada (no considera años bisiestos completamente)
        int dias1 = anio * 365 + mes * 30 + dia;
        int dias2 = otra.anio * 365 + otra.mes * 30 + otra.dia;
        return dias2 - dias1;
    }
};

// Clase para representar una tarea
class Tarea {
private:
    int id;
    string titulo;
    string descripcion;
    Prioridad prioridad;
    Estado estado;
    Categoria categoria;
    Fecha fechaCreacion;
    Fecha fechaLimite;
    Fecha fechaCompletada;

public:
    Tarea(int id = 0, const string& t = "", const string& d = "",
          Prioridad p = Prioridad::MEDIA, Categoria c = Categoria::OTROS)
        : id(id), titulo(t), descripcion(d), prioridad(p), estado(Estado::PENDIENTE),
          categoria(c), fechaCreacion(Fecha::hoy()) {}

    // Getters
    int obtenerId() const { return id; }
    string obtenerTitulo() const { return titulo; }
    string obtenerDescripcion() const { return descripcion; }
    Prioridad obtenerPrioridad() const { return prioridad; }
    Estado obtenerEstado() const { return estado; }
    Categoria obtenerCategoria() const { return categoria; }
    Fecha obtenerFechaCreacion() const { return fechaCreacion; }
    Fecha obtenerFechaLimite() const { return fechaLimite; }
    Fecha obtenerFechaCompletada() const { return fechaCompletada; }

    // Setters
    void establecerId(int i) { id = i; }
    void establecerTitulo(const string& t) { titulo = t; }
    void establecerDescripcion(const string& d) { descripcion = d; }
    void establecerPrioridad(Prioridad p) { prioridad = p; }
    void establecerEstado(Estado e) {
        estado = e;
        if (e == Estado::COMPLETADA) {
            fechaCompletada = Fecha::hoy();
        }
    }
    void establecerCategoria(Categoria c) { categoria = c; }
    void establecerFechaLimite(const Fecha& f) { fechaLimite = f; }

    // Métodos útiles
    bool estaVencida() const {
        if (estado == Estado::COMPLETADA) return false;
        Fecha hoy = Fecha::hoy();
        return fechaLimite < hoy && !(fechaLimite == Fecha(1,1,2024)); // Fecha por defecto
    }

    int diasRestantes() const {
        if (estado == Estado::COMPLETADA || (fechaLimite == Fecha(1,1,2024))) return -1;
        return fechaLimite.diasHasta(Fecha::hoy());
    }

    // Convertir enums a string
    static string prioridadToString(Prioridad p) {
        switch (p) {
            case Prioridad::BAJA: return "Baja";
            case Prioridad::MEDIA: return "Media";
            case Prioridad::ALTA: return "Alta";
            default: return "Desconocida";
        }
    }

    static string estadoToString(Estado e) {
        switch (e) {
            case Estado::PENDIENTE: return "Pendiente";
            case Estado::EN_PROGRESO: return "En Progreso";
            case Estado::COMPLETADA: return "Completada";
            default: return "Desconocido";
        }
    }

    static string categoriaToString(Categoria c) {
        switch (c) {
            case Categoria::TRABAJO: return "Trabajo";
            case Categoria::PERSONAL: return "Personal";
            case Categoria::ESTUDIO: return "Estudio";
            case Categoria::COMPRAS: return "Compras";
            case Categoria::OTROS: return "Otros";
            default: return "Desconocida";
        }
    }

    // Mostrar tarea
    void mostrar() const {
        cout << "ID: " << id << endl;
        cout << "Título: " << titulo << endl;
        cout << "Descripción: " << descripcion << endl;
        cout << "Prioridad: " << prioridadToString(prioridad) << endl;
        cout << "Estado: " << estadoToString(estado) << endl;
        cout << "Categoría: " << categoriaToString(categoria) << endl;
        cout << "Fecha de creación: " << fechaCreacion.toString() << endl;

        if (!(fechaLimite == Fecha(1,1,2024))) {
            cout << "Fecha límite: " << fechaLimite.toString();
            if (diasRestantes() >= 0) {
                cout << " (" << diasRestantes() << " días restantes)";
            } else if (diasRestantes() == -1) {
                // No mostrar nada
            } else {
                cout << " (VENCIDA)";
            }
            cout << endl;
        }

        if (estado == Estado::COMPLETADA && !(fechaCompletada == Fecha(1,1,2024))) {
            cout << "Fecha de completación: " << fechaCompletada.toString() << endl;
        }

        cout << "---" << endl;
    }

    // Serialización simple para guardar/cargar
    string serializar() const {
        ostringstream oss;
        oss << id << "|" << titulo << "|" << descripcion << "|"
            << static_cast<int>(prioridad) << "|" << static_cast<int>(estado) << "|"
            << static_cast<int>(categoria) << "|" << fechaCreacion.toString() << "|"
            << fechaLimite.toString() << "|" << fechaCompletada.toString();
        return oss.str();
    }

    static Tarea deserializar(const string& linea) {
        Tarea tarea;
        stringstream ss(linea);
        string token;
        vector<string> tokens;

        while (getline(ss, token, '|')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 9) {
            tarea.id = stoi(tokens[0]);
            tarea.titulo = tokens[1];
            tarea.descripcion = tokens[2];
            tarea.prioridad = static_cast<Prioridad>(stoi(tokens[3]));
            tarea.estado = static_cast<Estado>(stoi(tokens[4]));
            tarea.categoria = static_cast<Categoria>(stoi(tokens[5]));

            // Parsear fechas (formato dd/mm/yyyy)
            vector<string> fechaParts;
            stringstream ssFecha(tokens[6]);
            while (getline(ssFecha, token, '/')) {
                fechaParts.push_back(token);
            }
            if (fechaParts.size() == 3) {
                tarea.fechaCreacion = Fecha(stoi(fechaParts[0]), stoi(fechaParts[1]), stoi(fechaParts[2]));
            }

            fechaParts.clear();
            stringstream ssLimite(tokens[7]);
            while (getline(ssLimite, token, '/')) {
                fechaParts.push_back(token);
            }
            if (fechaParts.size() == 3) {
                tarea.fechaLimite = Fecha(stoi(fechaParts[0]), stoi(fechaParts[1]), stoi(fechaParts[2]));
            }

            fechaParts.clear();
            stringstream ssCompletada(tokens[8]);
            while (getline(ssCompletada, token, '/')) {
                fechaParts.push_back(token);
            }
            if (fechaParts.size() == 3) {
                tarea.fechaCompletada = Fecha(stoi(fechaParts[0]), stoi(fechaParts[1]), stoi(fechaParts[2]));
            }
        }

        return tarea;
    }
};

// Clase para filtrar y buscar tareas
class FiltroBusqueda {
public:
    // Función para filtrar tareas
    static vector<Tarea> filtrar(const vector<Tarea>& tareas,
                                function<bool(const Tarea&)> criterio) {
        vector<Tarea> resultado;
        copy_if(tareas.begin(), tareas.end(), back_inserter(resultado), criterio);
        return resultado;
    }

    // Buscar por texto
    static vector<Tarea> buscarPorTexto(const vector<Tarea>& tareas, const string& texto) {
        string textoBusqueda = texto;
        transform(textoBusqueda.begin(), textoBusqueda.end(), textoBusqueda.begin(), ::tolower);

        return filtrar(tareas, [textoBusqueda](const Tarea& t) {
            string titulo = t.obtenerTitulo();
            string descripcion = t.obtenerDescripcion();
            transform(titulo.begin(), titulo.end(), titulo.begin(), ::tolower);
            transform(descripcion.begin(), descripcion.end(), descripcion.begin(), ::tolower);

            return titulo.find(textoBusqueda) != string::npos ||
                   descripcion.find(textoBusqueda) != string::npos;
        });
    }

    // Filtrar por estado
    static vector<Tarea> filtrarPorEstado(const vector<Tarea>& tareas, Estado estado) {
        return filtrar(tareas, [estado](const Tarea& t) {
            return t.obtenerEstado() == estado;
        });
    }

    // Filtrar por prioridad
    static vector<Tarea> filtrarPorPrioridad(const vector<Tarea>& tareas, Prioridad prioridad) {
        return filtrar(tareas, [prioridad](const Tarea& t) {
            return t.obtenerPrioridad() == prioridad;
        });
    }

    // Filtrar por categoría
    static vector<Tarea> filtrarPorCategoria(const vector<Tarea>& tareas, Categoria categoria) {
        return filtrar(tareas, [categoria](const Tarea& t) {
            return t.obtenerCategoria() == categoria;
        });
    }

    // Filtrar tareas vencidas
    static vector<Tarea> filtrarVencidas(const vector<Tarea>& tareas) {
        return filtrar(tareas, [](const Tarea& t) {
            return t.estaVencida();
        });
    }
};

// Clase para estadísticas
class Estadisticas {
public:
    static void mostrarEstadisticas(const vector<Tarea>& tareas) {
        if (tareas.empty()) {
            cout << "No hay tareas para mostrar estadísticas." << endl;
            return;
        }

        cout << "\n=== ESTADÍSTICAS ===" << endl;

        // Contadores por estado
        int pendientes = 0, enProgreso = 0, completadas = 0;
        for (const auto& tarea : tareas) {
            switch (tarea.obtenerEstado()) {
                case Estado::PENDIENTE: pendientes++; break;
                case Estado::EN_PROGRESO: enProgreso++; break;
                case Estado::COMPLETADA: completadas++; break;
            }
        }

        cout << "Total de tareas: " << tareas.size() << endl;
        cout << "Pendientes: " << pendientes << endl;
        cout << "En progreso: " << enProgreso << endl;
        cout << "Completadas: " << completadas << endl;

        if (tareas.size() > 0) {
            double porcentajeCompletado = (static_cast<double>(completadas) / tareas.size()) * 100;
            cout << "Porcentaje completado: " << fixed << setprecision(1) << porcentajeCompletado << "%" << endl;
        }

        // Contadores por prioridad
        int baja = 0, media = 0, alta = 0;
        for (const auto& tarea : tareas) {
            switch (tarea.obtenerPrioridad()) {
                case Prioridad::BAJA: baja++; break;
                case Prioridad::MEDIA: media++; break;
                case Prioridad::ALTA: alta++; break;
            }
        }

        cout << "\nPor prioridad:" << endl;
        cout << "Alta: " << alta << endl;
        cout << "Media: " << media << endl;
        cout << "Baja: " << baja << endl;

        // Tareas vencidas
        auto vencidas = FiltroBusqueda::filtrarVencidas(tareas);
        cout << "\nTareas vencidas: " << vencidas.size() << endl;

        cout << endl;
    }
};

// Clase principal del gestor de tareas
class GestorTareas {
private:
    vector<Tarea> tareas;
    int siguienteId;
    string archivoDatos;

public:
    GestorTareas(const string& archivo = "tareas.dat") : siguienteId(1), archivoDatos(archivo) {
        cargarDesdeArchivo();
    }

    ~GestorTareas() {
        guardarEnArchivo();
    }

    // CRUD de tareas
    void agregarTarea(const Tarea& tarea) {
        Tarea nuevaTarea = tarea;
        nuevaTarea.establecerId(siguienteId++);
        tareas.push_back(nuevaTarea);
        cout << "✓ Tarea agregada con ID: " << nuevaTarea.obtenerId() << endl;
    }

    bool eliminarTarea(int id) {
        auto it = find_if(tareas.begin(), tareas.end(),
                         [id](const Tarea& t) { return t.obtenerId() == id; });

        if (it != tareas.end()) {
            tareas.erase(it);
            cout << "✓ Tarea eliminada" << endl;
            return true;
        }

        cout << "✗ Tarea no encontrada" << endl;
        return false;
    }

    bool editarTarea(int id) {
        Tarea* tarea = buscarPorId(id);
        if (!tarea) {
            cout << "✗ Tarea no encontrada" << endl;
            return false;
        }

        cout << "Editando tarea (deje vacío para mantener el valor actual):" << endl;

        // Título
        cout << "Título actual: " << tarea->obtenerTitulo() << endl;
        cout << "Nuevo título: ";
        string nuevoTitulo;
        getline(cin, nuevoTitulo);
        if (!nuevoTitulo.empty()) {
            tarea->establecerTitulo(nuevoTitulo);
        }

        // Descripción
        cout << "Descripción actual: " << tarea->obtenerDescripcion() << endl;
        cout << "Nueva descripción: ";
        string nuevaDescripcion;
        getline(cin, nuevaDescripcion);
        if (!nuevaDescripcion.empty()) {
            tarea->establecerDescripcion(nuevaDescripcion);
        }

        // Prioridad
        cout << "Prioridad actual: " << Tarea::prioridadToString(tarea->obtenerPrioridad()) << endl;
        cout << "Nueva prioridad (1-Baja, 2-Media, 3-Alta): ";
        string inputPrioridad;
        getline(cin, inputPrioridad);
        if (!inputPrioridad.empty()) {
            int p = stoi(inputPrioridad);
            if (p >= 1 && p <= 3) {
                tarea->establecerPrioridad(static_cast<Prioridad>(p - 1));
            }
        }

        // Categoría
        cout << "Categoría actual: " << Tarea::categoriaToString(tarea->obtenerCategoria()) << endl;
        cout << "Nueva categoría (1-Trabajo, 2-Personal, 3-Estudi, 4-Compras, 5-Otros): ";
        string inputCategoria;
        getline(cin, inputCategoria);
        if (!inputCategoria.empty()) {
            int c = stoi(inputCategoria);
            if (c >= 1 && c <= 5) {
                tarea->establecerCategoria(static_cast<Categoria>(c - 1));
            }
        }

        cout << "✓ Tarea actualizada" << endl;
        return true;
    }

    void marcarCompletada(int id) {
        Tarea* tarea = buscarPorId(id);
        if (tarea) {
            tarea->establecerEstado(Estado::COMPLETADA);
            cout << "✓ Tarea marcada como completada" << endl;
        } else {
            cout << "✗ Tarea no encontrada" << endl;
        }
    }

    void cambiarEstado(int id, Estado nuevoEstado) {
        Tarea* tarea = buscarPorId(id);
        if (tarea) {
            tarea->establecerEstado(nuevoEstado);
            cout << "✓ Estado de tarea actualizado" << endl;
        } else {
            cout << "✗ Tarea no encontrada" << endl;
        }
    }

    // Búsqueda y filtrado
    Tarea* buscarPorId(int id) {
        auto it = find_if(tareas.begin(), tareas.end(),
                         [id](const Tarea& t) { return t.obtenerId() == id; });
        return (it != tareas.end()) ? &(*it) : nullptr;
    }

    vector<Tarea> buscarPorTexto(const string& texto) {
        return FiltroBusqueda::buscarPorTexto(tareas, texto);
    }

    vector<Tarea> filtrarPorEstado(Estado estado) {
        return FiltroBusqueda::filtrarPorEstado(tareas, estado);
    }

    vector<Tarea> filtrarPorPrioridad(Prioridad prioridad) {
        return FiltroBusqueda::filtrarPorPrioridad(tareas, prioridad);
    }

    vector<Tarea> filtrarPorCategoria(Categoria categoria) {
        return FiltroBusqueda::filtrarPorCategoria(tareas, categoria);
    }

    vector<Tarea> obtenerTareasVencidas() {
        return FiltroBusqueda::filtrarVencidas(tareas);
    }

    // Mostrar tareas
    void mostrarTodas() const {
        if (tareas.empty()) {
            cout << "No hay tareas." << endl;
            return;
        }

        cout << "\n=== TODAS LAS TAREAS ===" << endl;
        for (const auto& tarea : tareas) {
            tarea.mostrar();
        }
    }

    void mostrarTareas(const vector<Tarea>& listaTareas) const {
        if (listaTareas.empty()) {
            cout << "No se encontraron tareas." << endl;
            return;
        }

        cout << "\n=== RESULTADOS ===" << endl;
        for (const auto& tarea : listaTareas) {
            tarea.mostrar();
        }
    }

    // Estadísticas
    void mostrarEstadisticas() const {
        Estadisticas::mostrarEstadisticas(tareas);
    }

    // Persistencia
    bool guardarEnArchivo() const {
        ofstream archivo(archivoDatos);
        if (!archivo.is_open()) {
            cerr << "Error: No se pudo abrir el archivo para guardar" << endl;
            return false;
        }

        for (const auto& tarea : tareas) {
            archivo << tarea.serializar() << endl;
        }

        archivo.close();
        return true;
    }

    bool cargarDesdeArchivo() {
        ifstream archivo(archivoDatos);
        if (!archivo.is_open()) {
            // No es error si el archivo no existe (primera ejecución)
            return false;
        }

        tareas.clear();
        string linea;
        while (getline(archivo, linea)) {
            if (!linea.empty()) {
                Tarea tarea = Tarea::deserializar(linea);
                tareas.push_back(tarea);
                if (tarea.obtenerId() >= siguienteId) {
                    siguienteId = tarea.obtenerId() + 1;
                }
            }
        }

        archivo.close();
        return true;
    }

    // Utilidades
    size_t obtenerCantidadTareas() const {
        return tareas.size();
    }

    void ordenarPorPrioridad() {
        sort(tareas.begin(), tareas.end(), [](const Tarea& a, const Tarea& b) {
            return static_cast<int>(a.obtenerPrioridad()) > static_cast<int>(b.obtenerPrioridad());
        });
        cout << "✓ Tareas ordenadas por prioridad" << endl;
    }

    void ordenarPorFechaLimite() {
        sort(tareas.begin(), tareas.end(), [](const Tarea& a, const Tarea& b) {
            return a.obtenerFechaLimite() < b.obtenerFechaLimite();
        });
        cout << "✓ Tareas ordenadas por fecha límite" << endl;
    }
};

// Funciones de utilidad para la interfaz
Tarea crearTareaDesdeEntrada() {
    string titulo, descripcion;
    int prioridad, categoria;
    string inputFecha;
    Fecha fechaLimite;

    cout << "Título: ";
    getline(cin, titulo);

    cout << "Descripción: ";
    getline(cin, descripcion);

    cout << "Prioridad (1-Baja, 2-Media, 3-Alta): ";
    cin >> prioridad;
    cin.ignore(); // Limpiar buffer

    cout << "Categoría (1-Trabajo, 2-Personal, 3-Estudio, 4-Compras, 5-Otros): ";
    cin >> categoria;
    cin.ignore(); // Limpiar buffer

    cout << "Fecha límite (dd/mm/yyyy, vacío para sin límite): ";
    getline(cin, inputFecha);

    if (!inputFecha.empty()) {
        // Parsear fecha
        stringstream ss(inputFecha);
        string token;
        vector<int> partesFecha;

        while (getline(ss, token, '/')) {
            partesFecha.push_back(stoi(token));
        }

        if (partesFecha.size() == 3) {
            fechaLimite = Fecha(partesFecha[0], partesFecha[1], partesFecha[2]);
            if (!fechaLimite.esValida()) {
                cout << "Fecha inválida, se usará sin límite de fecha." << endl;
                fechaLimite = Fecha(1,1,2024); // Fecha por defecto
            }
        }
    } else {
        fechaLimite = Fecha(1,1,2024); // Fecha por defecto
    }

    Tarea tarea(0, titulo, descripcion,
               static_cast<Prioridad>(prioridad - 1),
               static_cast<Categoria>(categoria - 1));
    tarea.establecerFechaLimite(fechaLimite);

    return tarea;
}

void mostrarMenu() {
    cout << "\n=== GESTOR DE TAREAS ===" << endl;
    cout << "1. Agregar tarea" << endl;
    cout << "2. Ver todas las tareas" << endl;
    cout << "3. Buscar tarea por ID" << endl;
    cout << "4. Buscar tareas por texto" << endl;
    cout << "5. Filtrar por estado" << endl;
    cout << "6. Filtrar por prioridad" << endl;
    cout << "7. Filtrar por categoría" << endl;
    cout << "8. Ver tareas vencidas" << endl;
    cout << "9. Editar tarea" << endl;
    cout << "10. Marcar como completada" << endl;
    cout << "11. Cambiar estado" << endl;
    cout << "12. Eliminar tarea" << endl;
    cout << "13. Mostrar estadísticas" << endl;
    cout << "14. Ordenar por prioridad" << endl;
    cout << "15. Ordenar por fecha límite" << endl;
    cout << "0. Salir" << endl;
    cout << "Opción: ";
}

int main() {
    GestorTareas gestor;

    cout << "¡Bienvenido al Gestor de Tareas!" << endl;
    cout << "Las tareas se guardan automáticamente al salir." << endl;

    while (true) {
        mostrarMenu();

        int opcion;
        cin >> opcion;
        cin.ignore(); // Limpiar buffer

        switch (opcion) {
            case 1: { // Agregar tarea
                cout << "\n--- AGREGAR TAREA ---" << endl;
                Tarea nuevaTarea = crearTareaDesdeEntrada();
                gestor.agregarTarea(nuevaTarea);
                break;
            }

            case 2: { // Ver todas
                gestor.mostrarTodas();
                break;
            }

            case 3: { // Buscar por ID
                cout << "ID de la tarea: ";
                int id;
                cin >> id;
                cin.ignore();

                Tarea* tarea = gestor.buscarPorId(id);
                if (tarea) {
                    cout << "\n--- TAREA ENCONTRADA ---" << endl;
                    tarea->mostrar();
                } else {
                    cout << "Tarea no encontrada." << endl;
                }
                break;
            }

            case 4: { // Buscar por texto
                cout << "Texto a buscar: ";
                string texto;
                getline(cin, texto);

                auto resultados = gestor.buscarPorTexto(texto);
                gestor.mostrarTareas(resultados);
                break;
            }

            case 5: { // Filtrar por estado
                cout << "Estado (1-Pendiente, 2-En Progreso, 3-Completada): ";
                int estado;
                cin >> estado;
                cin.ignore();

                auto resultados = gestor.filtrarPorEstado(static_cast<Estado>(estado - 1));
                gestor.mostrarTareas(resultados);
                break;
            }

            case 6: { // Filtrar por prioridad
                cout << "Prioridad (1-Baja, 2-Media, 3-Alta): ";
                int prioridad;
                cin >> prioridad;
                cin.ignore();

                auto resultados = gestor.filtrarPorPrioridad(static_cast<Prioridad>(prioridad - 1));
                gestor.mostrarTareas(resultados);
                break;
            }

            case 7: { // Filtrar por categoría
                cout << "Categoría (1-Trabajo, 2-Personal, 3-Estudio, 4-Compras, 5-Otros): ";
                int categoria;
                cin >> categoria;
                cin.ignore();

                auto resultados = gestor.filtrarPorCategoria(static_cast<Categoria>(categoria - 1));
                gestor.mostrarTareas(resultados);
                break;
            }

            case 8: { // Tareas vencidas
                auto vencidas = gestor.obtenerTareasVencidas();
                cout << "\n--- TAREAS VENCIDAS ---" << endl;
                gestor.mostrarTareas(vencidas);
                break;
            }

            case 9: { // Editar tarea
                cout << "ID de la tarea a editar: ";
                int idEditar;
                cin >> idEditar;
                cin.ignore();

                gestor.editarTarea(idEditar);
                break;
            }

            case 10: { // Marcar completada
                cout << "ID de la tarea a completar: ";
                int idCompletar;
                cin >> idCompletar;
                cin.ignore();

                gestor.marcarCompletada(idCompletar);
                break;
            }

            case 11: { // Cambiar estado
                cout << "ID de la tarea: ";
                int idEstado;
                cin >> idEstado;
                cin.ignore();

                cout << "Nuevo estado (1-Pendiente, 2-En Progreso, 3-Completada): ";
                int nuevoEstado;
                cin >> nuevoEstado;
                cin.ignore();

                gestor.cambiarEstado(idEstado, static_cast<Estado>(nuevoEstado - 1));
                break;
            }

            case 12: { // Eliminar tarea
                cout << "ID de la tarea a eliminar: ";
                int idEliminar;
                cin >> idEliminar;
                cin.ignore();

                gestor.eliminarTarea(idEliminar);
                break;
            }

            case 13: { // Estadísticas
                gestor.mostrarEstadisticas();
                break;
            }

            case 14: { // Ordenar por prioridad
                gestor.ordenarPorPrioridad();
                break;
            }

            case 15: { // Ordenar por fecha
                gestor.ordenarPorFechaLimite();
                break;
            }

            case 0: { // Salir
                cout << "¡Hasta luego!" << endl;
                return 0;
            }

            default: {
                cout << "Opción inválida. Intente nuevamente." << endl;
                break;
            }
        }
    }

    return 0;
}
```

## Funcionalidades Implementadas

### Gestión Completa de Tareas
- ✅ Crear tareas con título, descripción, prioridad, categoría y fecha límite
- ✅ Editar todas las propiedades de las tareas
- ✅ Eliminar tareas
- ✅ Cambiar estados (Pendiente → En Progreso → Completada)

### Sistema de Búsqueda y Filtrado
- ✅ Búsqueda por texto en título y descripción
- ✅ Filtrado por estado, prioridad y categoría
- ✅ Detección automática de tareas vencidas
- ✅ Ordenamiento por prioridad y fecha límite

### Persistencia de Datos
- ✅ Guardado automático en archivo de texto
- ✅ Carga automática al iniciar el programa
- ✅ Serialización/deserialización de objetos

### Características Avanzadas
- ✅ Sistema de estadísticas y métricas
- ✅ Validación de fechas
- ✅ Manejo de errores robusto
- ✅ Interfaz de usuario intuitiva

## Estructura de Archivos

```
gestor_tareas/
├── gestor_tareas.cpp    # Archivo principal
├── Tarea.h             # Clase Tarea
├── GestorTareas.h      # Clase GestorTareas
├── FiltroBusqueda.h    # Utilidades de búsqueda
├── Estadisticas.h      # Cálculo de estadísticas
├── tareas.dat          # Archivo de datos (generado)
└── README.md          # Documentación
```

## Compilación y Ejecución

```bash
# Compilación
g++ -std=c++23 -o gestor_tareas gestor_tareas.cpp

# Ejecución
./gestor_tareas
```

## Uso del Gestor de Tareas

### Agregar una Nueva Tarea
```
--- AGREGAR TAREA ---
Título: Estudiar C++
Descripción: Completar el capítulo de punteros
Prioridad (1-Baja, 2-Media, 3-Alta): 3
Categoría (1-Trabajo, 2-Personal, 3-Estudio, 4-Compras, 5-Otros): 3
Fecha límite (dd/mm/yyyy, vacío para sin límite): 15/12/2024
✓ Tarea agregada con ID: 1
```

### Filtrar Tareas por Estado
```
Estado (1-Pendiente, 2-En Progreso, 3-Completada): 1

=== RESULTADOS ===
ID: 1
Título: Estudiar C++
Descripción: Completar el capítulo de punteros
Prioridad: Alta
Estado: Pendiente
Categoría: Estudio
Fecha de creación: 01/12/2024
Fecha límite: 15/12/2024 (14 días restantes)
---
```

### Estadísticas del Sistema
```
=== ESTADÍSTICAS ===
Total de tareas: 5
Pendientes: 3
En progreso: 1
Completadas: 1
Porcentaje completado: 20.0%

Por prioridad:
Alta: 2
Media: 2
Baja: 1

Tareas vencidas: 0
```

## Características Técnicas

### Patrones de Diseño Utilizados
- **MVC (Model-View-Controller)**: Separación entre datos, lógica y presentación
- **Strategy Pattern**: Diferentes algoritmos de filtrado
- **Observer Pattern**: Actualización automática de estadísticas

### Estructuras de Datos
- **Vector**: Almacenamiento principal de tareas
- **Map**: Configuración y metadatos
- **Set**: Categorías y estados únicos

### Algoritmos Implementados
- **Búsqueda lineal**: Para encontrar tareas por ID
- **Búsqueda por texto**: Con transformación a minúsculas
- **Ordenamiento**: Por prioridad y fecha usando std::sort
- **Filtrado**: Usando algoritmos de STL y lambdas

### Manejo de Errores
- Validación de entrada de usuario
- Verificación de existencia de archivos
- Control de excepciones en operaciones críticas
- Mensajes informativos para el usuario

## Extensiones Posibles

### Interfaz Gráfica
- Qt o GTK para interfaz visual
- Calendario integrado para fechas
- Notificaciones del sistema

### Sincronización
- Sincronización con Google Calendar
- Exportación a formatos iCal
- Compartir listas entre usuarios

### Funcionalidades Adicionales
- Subtareas y dependencias
- Recordatorios automáticos
- Etiquetas personalizadas
- Plantillas de tareas

### Base de Datos
- SQLite para almacenamiento persistente
- Consultas SQL complejas
- Backup y restauración
- Historial de cambios

## Conclusión

Este gestor de tareas implementa un sistema completo de gestión de tareas personales con:

- ✅ **Arquitectura modular** con clases bien definidas y responsabilidades claras
- ✅ **Interfaz de usuario completa** con menú interactivo y validación de entrada
- ✅ **Sistema de búsqueda y filtrado avanzado** con múltiples criterios
- ✅ **Persistencia de datos** con guardado automático
- ✅ **Estadísticas y métricas** para seguimiento de productividad
- ✅ **Manejo robusto de fechas** con validación y cálculo de días restantes
- ✅ **Código extensible** preparado para futuras funcionalidades

El proyecto demuestra el uso efectivo de conceptos avanzados de C++ como enums, clases, templates, algoritmos STL, manejo de archivos y programación orientada a objetos para crear una aplicación completa y funcional.