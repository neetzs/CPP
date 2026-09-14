#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Clase que cuenta instancias usando miembros estáticos
class ContadorObjetos
{
private:
    static int contadorTotal;      // Cuenta todas las instancias
    static int contadorActivos;    // Cuenta instancias activas
    static vector<string> nombres; // Lista de nombres de objetos

    string nombre;

public:
    // Constructor
    ContadorObjetos(string n) : nombre(n)
    {
        contadorTotal++;
        contadorActivos++;
        nombres.push_back(n);
        cout << "Creando objeto '" << nombre << "'" << endl;
    }

    // Destructor
    ~ContadorObjetos()
    {
        contadorActivos--;
        cout << "Destruyendo objeto '" << nombre << "'" << endl;
    }

    // Métodos estáticos
    static int obtenerContadorTotal()
    {
        return contadorTotal;
    }

    static int obtenerContadorActivos()
    {
        return contadorActivos;
    }

    static void mostrarEstadisticas()
    {
        cout << "=== ESTADÍSTICAS ===" << endl;
        cout << "Total de objetos creados: " << contadorTotal << endl;
        cout << "Objetos activos: " << contadorActivos << endl;
        cout << "Nombres registrados: ";
        for (const auto &nom : nombres)
        {
            cout << nom << " ";
        }
        cout << endl;
    }

    static void reiniciarContadores()
    {
        contadorTotal = 0;
        contadorActivos = 0;
        nombres.clear();
        cout << "Contadores reiniciados" << endl;
    }

    // Método de instancia
    void mostrarInfo() const
    {
        cout << "Objeto '" << nombre << "' - ID: " << this << endl;
    }
};

// Definición de miembros estáticos
int ContadorObjetos::contadorTotal = 0;
int ContadorObjetos::contadorActivos = 0;
vector<string> ContadorObjetos::nombres;

// Clase con constantes estáticas
class Matematicas
{
public:
    static constexpr double PI = 3.141592653589793;
    static constexpr double E = 2.718281828459045;

    static double calcularAreaCirculo(double radio)
    {
        return PI * radio * radio;
    }

    static double calcularPerimetroCirculo(double radio)
    {
        return 2 * PI * radio;
    }

    static double calcularExponencial(double base, int exponente)
    {
        double resultado = 1;
        for (int i = 0; i < exponente; i++)
        {
            resultado *= base;
        }
        return resultado;
    }
};

// Clase Singleton usando miembros estáticos
class Logger
{
private:
    static Logger *instancia;
    static int contadorMensajes;

    string nombreArchivo;
    vector<string> mensajes;

    // Constructor privado
    Logger(string archivo = "log.txt") : nombreArchivo(archivo)
    {
        cout << "Logger inicializado con archivo: " << nombreArchivo << endl;
    }

public:
    // Destructor
    ~Logger()
    {
        cout << "Logger destruido" << endl;
    }

    // Método estático para obtener instancia (Singleton)
    static Logger *obtenerInstancia()
    {
        if (instancia == nullptr)
        {
            instancia = new Logger();
        }
        return instancia;
    }

    // Método estático para liberar instancia
    static void liberarInstancia()
    {
        if (instancia != nullptr)
        {
            delete instancia;
            instancia = nullptr;
        }
    }

    // Métodos de instancia
    void registrarMensaje(const string &mensaje)
    {
        contadorMensajes++;
        mensajes.push_back(mensaje);
        cout << "[LOG] " << mensaje << endl;
    }

    void mostrarHistorial() const
    {
        cout << "=== HISTORIAL DE LOGS ===" << endl;
        for (const auto &msg : mensajes)
        {
            cout << "- " << msg << endl;
        }
    }

    // Métodos estáticos
    static int obtenerContadorMensajes()
    {
        return contadorMensajes;
    }

    static void reiniciarContador()
    {
        contadorMensajes = 0;
    }
};

// Definición de miembros estáticos del Logger
Logger *Logger::instancia = nullptr;
int Logger::contadorMensajes = 0;

// Clase con método estático que modifica estado estático
class Configuracion
{
private:
    static string idioma;
    static bool modoOscuro;
    static int tamanoFuente;

public:
    // Métodos estáticos para configuración
    static void establecerIdioma(const string &nuevoIdioma)
    {
        idioma = nuevoIdioma;
        cout << "Idioma establecido a: " << idioma << endl;
    }

    static void alternarModoOscuro()
    {
        modoOscuro = !modoOscuro;
        cout << "Modo oscuro: " << (modoOscuro ? "Activado" : "Desactivado") << endl;
    }

    static void establecerTamanoFuente(int tamano)
    {
        if (tamano >= 8 && tamano <= 24)
        {
            tamanoFuente = tamano;
            cout << "Tamaño de fuente establecido a: " << tamanoFuente << endl;
        }
        else
        {
            cout << "Tamaño de fuente inválido (8-24)" << endl;
        }
    }

    static void mostrarConfiguracion()
    {
        cout << "=== CONFIGURACIÓN ACTUAL ===" << endl;
        cout << "Idioma: " << idioma << endl;
        cout << "Modo oscuro: " << (modoOscuro ? "Sí" : "No") << endl;
        cout << "Tamaño fuente: " << tamanoFuente << endl;
    }
};

// Definición de miembros estáticos
string Configuracion::idioma = "es";
bool Configuracion::modoOscuro = false;
int Configuracion::tamanoFuente = 12;

int main()
{
    cout << "=== DEMOSTRACIÓN DE MIEMBROS ESTÁTICOS ===" << endl;

    // Contador de objetos
    cout << "\n--- CONTADOR DE OBJETOS ---" << endl;
    ContadorObjetos::mostrarEstadisticas();

    ContadorObjetos *obj1 = new ContadorObjetos("Objeto1");
    ContadorObjetos *obj2 = new ContadorObjetos("Objeto2");

    ContadorObjetos::mostrarEstadisticas();

    obj1->mostrarInfo();
    obj2->mostrarInfo();

    delete obj1;
    ContadorObjetos::mostrarEstadisticas();

    // Crear objetos en el stack
    {
        ContadorObjetos obj3("Objeto3");
        ContadorObjetos obj4("Objeto4");
        ContadorObjetos::mostrarEstadisticas();
    } // obj3 y obj4 se destruyen aquí

    ContadorObjetos::mostrarEstadisticas();

    // Matemáticas con constantes estáticas
    cout << "\n--- MATEMÁTICAS ---" << endl;
    cout << "PI: " << Matematicas::PI << endl;
    cout << "E: " << Matematicas::E << endl;

    double radio = 5.0;
    cout << "Área del círculo (radio=" << radio << "): "
         << Matematicas::calcularAreaCirculo(radio) << endl;
    cout << "Perímetro del círculo: "
         << Matematicas::calcularPerimetroCirculo(radio) << endl;

    cout << "2^3 = " << Matematicas::calcularExponencial(2, 3) << endl;

    // Logger (Singleton)
    cout << "\n--- LOGGER (SINGLETON) ---" << endl;
    Logger *log = Logger::obtenerInstancia();
    log->registrarMensaje("Aplicación iniciada");
    log->registrarMensaje("Procesando datos");
    log->registrarMensaje("Operación completada");

    cout << "Mensajes registrados: " << Logger::obtenerContadorMensajes() << endl;
    log->mostrarHistorial();

    // Configuración
    cout << "\n--- CONFIGURACIÓN ---" << endl;
    Configuracion::mostrarConfiguracion();

    Configuracion::establecerIdioma("en");
    Configuracion::alternarModoOscuro();
    Configuracion::establecerTamanoFuente(16);
    Configuracion::establecerTamanoFuente(30); // Inválido

    Configuracion::mostrarConfiguracion();

    // Limpiar
    Logger::liberarInstancia();
    delete obj2;

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;

    return 0;
}