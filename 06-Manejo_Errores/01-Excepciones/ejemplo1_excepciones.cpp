#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
using namespace std;

// Clase de excepción personalizada
class DivisionPorCeroException : public runtime_error
{
public:
    DivisionPorCeroException() : runtime_error("Intento de división por cero") {}
    DivisionPorCeroException(const string &mensaje) : runtime_error(mensaje) {}
};

// Clase de excepción personalizada con información adicional
class ErrorDeValidacion : public invalid_argument
{
private:
    string campo;
    string valor;

public:
    ErrorDeValidacion(const string &campo, const string &valor, const string &mensaje)
        : invalid_argument(mensaje), campo(campo), valor(valor) {}

    string obtenerCampo() const { return campo; }
    string obtenerValor() const { return valor; }
};

// Función que puede lanzar excepciones
double dividir(double numerador, double denominador)
{
    if (denominador == 0)
    {
        throw DivisionPorCeroException("El denominador no puede ser cero");
    }

    if (isnan(numerador) || isnan(denominador))
    {
        throw invalid_argument("Los operandos no pueden ser NaN");
    }

    if (isinf(numerador) || isinf(denominador))
    {
        throw domain_error("Los operandos no pueden ser infinitos");
    }

    return numerador / denominador;
}

// Función que valida datos de usuario
void validarUsuario(const string &nombre, int edad, const string &email)
{
    if (nombre.empty())
    {
        throw ErrorDeValidacion("nombre", nombre, "El nombre no puede estar vacío");
    }

    if (edad < 0 || edad > 150)
    {
        throw out_of_range("La edad debe estar entre 0 y 150 años");
    }

    if (email.find('@') == string::npos)
    {
        throw ErrorDeValidacion("email", email, "El email debe contener '@'");
    }
}

// Clase que demuestra RAII con excepciones
class Archivo
{
private:
    string nombre;
    bool abierto;

public:
    Archivo(const string &nombreArchivo) : nombre(nombreArchivo), abierto(false)
    {
        // Simular apertura de archivo
        if (nombreArchivo.empty())
        {
            throw invalid_argument("Nombre de archivo vacío");
        }
        abierto = true;
        cout << "Archivo '" << nombre << "' abierto" << endl;
    }

    ~Archivo()
    {
        if (abierto)
        {
            // Cerrar archivo en destructor (RAII)
            cout << "Archivo '" << nombre << "' cerrado" << endl;
            abierto = false;
        }
    }

    void escribir(const string &datos)
    {
        if (!abierto)
        {
            throw runtime_error("Archivo no está abierto");
        }
        cout << "Escribiendo en '" << nombre << "': " << datos << endl;
    }

    string leer()
    {
        if (!abierto)
        {
            throw runtime_error("Archivo no está abierto");
        }
        return "Contenido del archivo " + nombre;
    }
};

// Función que demuestra manejo de excepciones anidadas
void funcionAnidada(int nivel)
{
    try
    {
        if (nivel == 1)
        {
            throw runtime_error("Error en nivel 1");
        }
        else if (nivel == 2)
        {
            // Llamar a función que puede fallar
            dividir(10, 0);
        }
        else if (nivel == 3)
        {
            vector<int> v;
            v.at(10); // Acceso fuera de rango
        }
    }
    catch (const DivisionPorCeroException &e)
    {
        cout << "Capturado en funcionAnidada: " << e.what() << endl;
        throw; // Re-lanzar
    }
    catch (const exception &e)
    {
        cout << "Capturado en funcionAnidada: " << e.what() << endl;
        // Agregar contexto y re-lanzar
        throw runtime_error(string("Error en nivel ") + to_string(nivel) + ": " + e.what());
    }
}

// Función con noexcept
double funcionSegura(double x) noexcept
{
    return x * x;
}

// Función que puede lanzar excepciones
double funcionPeligrosa(double x)
{
    if (x < 0)
    {
        throw domain_error("x debe ser no negativo");
    }
    return sqrt(x);
}

int main()
{
    cout << "=== MANEJO DE EXCEPCIONES EN C++ ===" << endl;

    // 1. Excepciones básicas
    cout << "\n--- EXCEPCIONES BÁSICAS ---" << endl;

    try
    {
        double resultado = dividir(10, 0);
        cout << "Resultado: " << resultado << endl;
    }
    catch (const DivisionPorCeroException &e)
    {
        cout << "Capturado DivisionPorCeroException: " << e.what() << endl;
    }
    catch (const exception &e)
    {
        cout << "Capturado exception general: " << e.what() << endl;
    }

    try
    {
        double resultado = dividir(10, 2);
        cout << "División exitosa: " << resultado << endl;
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    // 2. Validación de datos
    cout << "\n--- VALIDACIÓN DE DATOS ---" << endl;

    vector<tuple<string, int, string>> usuarios = {
        {"Juan", 25, "juan@email.com"},
        {"", 30, "maria@email.com"},
        {"Pedro", -5, "pedro@email.com"},
        {"Ana", 28, "ana.email.com"}};

    for (const auto &[nombre, edad, email] : usuarios)
    {
        try
        {
            validarUsuario(nombre, edad, email);
            cout << "Usuario válido: " << nombre << endl;
        }
        catch (const ErrorDeValidacion &e)
        {
            cout << "Error de validación en campo '" << e.obtenerCampo()
                 << "' con valor '" << e.obtenerValor() << "': " << e.what() << endl;
        }
        catch (const out_of_range &e)
        {
            cout << "Error de rango: " << e.what() << endl;
        }
        catch (const exception &e)
        {
            cout << "Error general: " << e.what() << endl;
        }
    }

    // 3. RAII con excepciones
    cout << "\n--- RAII CON EXCEPCIONES ---" << endl;

    try
    {
        Archivo archivo("datos.txt");
        archivo.escribir("Hola mundo");

        // Simular error
        throw runtime_error("Error simulado");

        archivo.escribir("Esto no se ejecutará");
    }
    catch (const exception &e)
    {
        cout << "Error durante operaciones de archivo: " << e.what() << endl;
        // El archivo se cierra automáticamente por RAII
    }

    // 4. Excepciones anidadas
    cout << "\n--- EXCEPCIONES ANIDADAS ---" << endl;

    for (int i = 1; i <= 3; i++)
    {
        try
        {
            funcionAnidada(i);
        }
        catch (const runtime_error &e)
        {
            cout << "Capturado en main: " << e.what() << endl;
        }
        catch (const exception &e)
        {
            cout << "Capturado otro tipo de excepción: " << e.what() << endl;
        }
    }

    // 5. Excepciones estándar del sistema
    cout << "\n--- EXCEPCIONES ESTÁNDAR ---" << endl;

    try
    {
        vector<int> v(5);
        cout << "Accediendo v[10]: " << v.at(10) << endl;
    }
    catch (const out_of_range &e)
    {
        cout << "out_of_range: " << e.what() << endl;
    }

    try
    {
        unique_ptr<int[]> ptr(new int[1000000000L]); // Intentar asignar mucha memoria
    }
    catch (const bad_alloc &e)
    {
        cout << "bad_alloc: " << e.what() << endl;
    }

    // 6. noexcept vs funciones que pueden lanzar
    cout << "\n--- NOEXCEPT VS FUNCIONES QUE PUEDEN LANZAR ---" << endl;

    cout << "funcionSegura(5.0): " << funcionSegura(5.0) << endl;

    try
    {
        double resultado = funcionPeligrosa(-1.0);
        cout << "Resultado: " << resultado << endl;
    }
    catch (const domain_error &e)
    {
        cout << "Error en funcionPeligrosa: " << e.what() << endl;
    }

    // 7. Catch-all y re-lanzamiento
    cout << "\n--- CATCH-ALL Y RE-LANZAMIENTO ---" << endl;

    try
    {
        try
        {
            throw string("Excepción de tipo string");
        }
        catch (const string &s)
        {
            cout << "Capturado string: " << s << endl;
            throw; // Re-lanzar la excepción
        }
    }
    catch (const string &s)
    {
        cout << "Re-capturado string: " << s << endl;
    }
    catch (...)
    {
        cout << "Capturado con catch-all" << endl;
    }

    // 8. Excepciones en constructores
    cout << "\n--- EXCEPCIONES EN CONSTRUCTORES ---" << endl;

    try
    {
        Archivo archivo2(""); // Nombre vacío causará excepción
        archivo2.escribir("Esto no se ejecutará");
    }
    catch (const invalid_argument &e)
    {
        cout << "Error en constructor: " << e.what() << endl;
        // El objeto nunca se creó completamente
    }

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;

    return 0;
}