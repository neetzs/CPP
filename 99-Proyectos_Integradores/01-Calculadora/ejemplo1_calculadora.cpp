#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <map>
#include <cctype>
#include <limits>
using namespace std;

// Clase para representar una operación matemática
class OperacionMatematica
{
private:
    string expresion;
    double resultado;
    string descripcion;
    bool exitosa;

public:
    OperacionMatematica(const string &expr = "", double res = 0.0,
                        const string &desc = "", bool exito = false)
        : expresion(expr), resultado(res), descripcion(desc), exitosa(exito) {}

    string obtenerExpresion() const { return expresion; }
    double obtenerResultado() const { return resultado; }
    string obtenerDescripcion() const { return descripcion; }
    bool fueExitosa() const { return exitosa; }

    void mostrar() const
    {
        cout << "Expresión: " << expresion << endl;
        cout << "Resultado: " << fixed << setprecision(6) << resultado << endl;
        cout << "Descripción: " << descripcion << endl;
        cout << "Estado: " << (exitosa ? "Exitosa" : "Fallida") << endl;
        cout << "---" << endl;
    }
};

// Clase para manejar el historial de operaciones
class Historial
{
private:
    vector<OperacionMatematica> operaciones;
    size_t capacidadMaxima;

public:
    Historial(size_t capacidad = 100) : capacidadMaxima(capacidad) {}

    void agregarOperacion(const OperacionMatematica &operacion)
    {
        operaciones.push_back(operacion);

        // Mantener solo las últimas N operaciones
        if (operaciones.size() > capacidadMaxima)
        {
            operaciones.erase(operaciones.begin());
        }
    }

    void mostrarHistorial() const
    {
        if (operaciones.empty())
        {
            cout << "No hay operaciones en el historial." << endl;
            return;
        }

        cout << "\n=== HISTORIAL DE OPERACIONES ===" << endl;
        for (size_t i = 0; i < operaciones.size(); ++i)
        {
            cout << "\nOperación " << (i + 1) << ":" << endl;
            operaciones[i].mostrar();
        }
    }

    OperacionMatematica obtenerUltimaOperacion() const
    {
        if (operaciones.empty())
        {
            return OperacionMatematica("", 0.0, "No hay operaciones previas", false);
        }
        return operaciones.back();
    }

    void limpiarHistorial()
    {
        operaciones.clear();
        cout << "Historial limpiado." << endl;
    }

    size_t obtenerTamanio() const
    {
        return operaciones.size();
    }
};

// Clase para evaluar expresiones matemáticas
class EvaluadorExpresiones
{
private:
    // Funciones matemáticas disponibles
    map<string, function<double(double)>> funcionesUnarias = {
        {"sin", [](double x)
         { return sin(x); }},
        {"cos", [](double x)
         { return cos(x); }},
        {"tan", [](double x)
         { return tan(x); }},
        {"asin", [](double x)
         { return asin(x); }},
        {"acos", [](double x)
         { return acos(x); }},
        {"atan", [](double x)
         { return atan(x); }},
        {"ln", [](double x)
         { return log(x); }},
        {"log", [](double x)
         { return log10(x); }},
        {"exp", [](double x)
         { return exp(x); }},
        {"sqrt", [](double x)
         { return sqrt(x); }},
        {"abs", [](double x)
         { return abs(x); }},
        {"floor", [](double x)
         { return floor(x); }},
        {"ceil", [](double x)
         { return ceil(x); }}};

    // Operadores binarios con su precedencia
    map<char, pair<int, function<double(double, double)>>> operadoresBinarios = {
        {'+', {1, [](double a, double b)
               { return a + b; }}},
        {'-', {1, [](double a, double b)
               { return a - b; }}},
        {'*', {2, [](double a, double b)
               { return a * b; }}},
        {'/', {2, [](double a, double b)
               { return a / b; }}},
        {'^', {3, [](double a, double b)
               { return pow(a, b); }}},
        {'%', {2, [](double a, double b)
               { return fmod(a, b); }}}};

    // Convertir expresión infija a postfija (notación polaca inversa)
    queue<string> convertirAPostfija(const string &expresion)
    {
        queue<string> salida;
        stack<char> operadores;
        string numero = "";

        for (size_t i = 0; i < expresion.length(); ++i)
        {
            char c = expresion[i];

            if (isdigit(c) || c == '.' || (c == '-' && (i == 0 || expresion[i - 1] == '(' || esOperador(expresion[i - 1]))))
            {
                numero += c;
            }
            else
            {
                if (!numero.empty())
                {
                    salida.push(numero);
                    numero = "";
                }

                if (c == '(')
                {
                    operadores.push(c);
                }
                else if (c == ')')
                {
                    while (!operadores.empty() && operadores.top() != '(')
                    {
                        salida.push(string(1, operadores.top()));
                        operadores.pop();
                    }
                    if (!operadores.empty())
                        operadores.pop(); // Remover '('
                }
                else if (esOperador(c))
                {
                    while (!operadores.empty() && operadores.top() != '(' &&
                           obtenerPrecedencia(operadores.top()) >= obtenerPrecedencia(c))
                    {
                        salida.push(string(1, operadores.top()));
                        operadores.pop();
                    }
                    operadores.push(c);
                }
            }
        }

        if (!numero.empty())
        {
            salida.push(numero);
        }

        while (!operadores.empty())
        {
            salida.push(string(1, operadores.top()));
            operadores.pop();
        }

        return salida;
    }

    // Evaluar expresión en notación postfija
    double evaluarPostfija(queue<string> expresionPostfija)
    {
        stack<double> pila;

        while (!expresionPostfija.empty())
        {
            string token = expresionPostfija.front();
            expresionPostfija.pop();

            if (esNumero(token))
            {
                pila.push(stod(token));
            }
            else if (esFuncion(token))
            {
                if (pila.empty())
                    throw runtime_error("Faltan operandos para función");
                double operando = pila.top();
                pila.pop();
                pila.push(funcionesUnarias[token](operando));
            }
            else if (esOperador(token[0]))
            {
                if (pila.size() < 2)
                    throw runtime_error("Faltan operandos para operador");
                double b = pila.top();
                pila.pop();
                double a = pila.top();
                pila.pop();
                pila.push(operadoresBinarios[token[0]].second(a, b));
            }
        }

        if (pila.size() != 1)
            throw runtime_error("Expresión mal formada");
        return pila.top();
    }

    bool esNumero(const string &s)
    {
        if (s.empty())
            return false;
        size_t i = 0;
        if (s[0] == '-')
            i = 1;
        bool puntoEncontrado = false;
        for (; i < s.length(); ++i)
        {
            if (s[i] == '.')
            {
                if (puntoEncontrado)
                    return false;
                puntoEncontrado = true;
            }
            else if (!isdigit(s[i]))
            {
                return false;
            }
        }
        return true;
    }

    bool esOperador(char c)
    {
        return operadoresBinarios.find(c) != operadoresBinarios.end();
    }

    bool esFuncion(const string &s)
    {
        return funcionesUnarias.find(s) != funcionesUnarias.end();
    }

    int obtenerPrecedencia(char op)
    {
        auto it = operadoresBinarios.find(op);
        return (it != operadoresBinarios.end()) ? it->second.first : 0;
    }

    // Preprocesar expresión para manejar funciones
    string preprocesarExpresion(string expresion)
    {
        // Convertir funciones a tokens separados
        map<string, string> reemplazos = {
            {"sin(", "sin ("}, {"cos(", "cos ("}, {"tan(", "tan ("}, {"asin(", "asin ("}, {"acos(", "acos ("}, {"atan(", "atan ("}, {"ln(", "ln ("}, {"log(", "log ("}, {"exp(", "exp ("}, {"sqrt(", "sqrt ("}, {"abs(", "abs ("}, {"floor(", "floor ("}, {"ceil(", "ceil ("}};

        for (const auto &par : reemplazos)
        {
            size_t pos = 0;
            while ((pos = expresion.find(par.first, pos)) != string::npos)
            {
                expresion.replace(pos, par.first.length(), par.second);
                pos += par.second.length();
            }
        }

        return expresion;
    }

public:
    double evaluar(const string &expresionOriginal)
    {
        try
        {
            string expresion = preprocesarExpresion(expresionOriginal);

            // Remover espacios
            expresion.erase(remove_if(expresion.begin(), expresion.end(), ::isspace), expresion.end());

            if (expresion.empty())
            {
                throw invalid_argument("Expresión vacía");
            }

            queue<string> postfija = convertirAPostfija(expresion);
            return evaluarPostfija(postfija);
        }
        catch (const exception &e)
        {
            throw runtime_error("Error al evaluar expresión '" + expresionOriginal + "': " + e.what());
        }
    }

    vector<string> obtenerFuncionesDisponibles() const
    {
        vector<string> funciones;
        for (const auto &par : funcionesUnarias)
        {
            funciones.push_back(par.first);
        }
        return funciones;
    }

    vector<char> obtenerOperadoresDisponibles() const
    {
        vector<char> operadores;
        for (const auto &par : operadoresBinarios)
        {
            operadores.push_back(par.first);
        }
        return operadores;
    }
};

// Clase principal de la calculadora
class Calculadora
{
private:
    EvaluadorExpresiones evaluador;
    Historial historial;
    bool modoAvanzado;

public:
    Calculadora() : modoAvanzado(false) {}

    void ejecutar()
    {
        cout << "=== CALCULADORA AVANZADA EN C++ ===" << endl;
        cout << "Escribe 'ayuda' para ver comandos disponibles" << endl;
        cout << "Escribe 'salir' para terminar" << endl
             << endl;

        while (true)
        {
            cout << (modoAvanzado ? "[AVANZADO] " : "[BÁSICO] ") << "> ";
            string entrada;
            getline(cin, entrada);

            if (entrada.empty())
                continue;

            // Convertir a minúsculas para comandos
            string comando = entrada;
            transform(comando.begin(), comando.end(), comando.begin(), ::tolower);

            if (comando == "salir" || comando == "exit")
            {
                cout << "¡Hasta luego!" << endl;
                break;
            }
            else if (comando == "ayuda" || comando == "help")
            {
                mostrarAyuda();
            }
            else if (comando == "historial" || comando == "history")
            {
                historial.mostrarHistorial();
            }
            else if (comando == "limpiar" || comando == "clear")
            {
                historial.limpiarHistorial();
            }
            else if (comando == "ultimo" || comando == "last")
            {
                OperacionMatematica ultima = historial.obtenerUltimaOperacion();
                if (ultima.fueExitosa())
                {
                    cout << "Última operación: " << ultima.obtenerResultado() << endl;
                }
                else
                {
                    cout << "No hay operaciones exitosas previas." << endl;
                }
            }
            else if (comando == "modo")
            {
                cambiarModo();
            }
            else
            {
                procesarExpresion(entrada);
            }
        }
    }

private:
    void mostrarAyuda()
    {
        cout << "\n=== AYUDA ===" << endl;
        cout << "COMANDOS:" << endl;
        cout << "  ayuda     - Mostrar esta ayuda" << endl;
        cout << "  salir     - Salir de la calculadora" << endl;
        cout << "  historial - Ver historial de operaciones" << endl;
        cout << "  limpiar   - Limpiar historial" << endl;
        cout << "  ultimo    - Ver último resultado" << endl;
        cout << "  modo      - Cambiar entre modo básico y avanzado" << endl;

        cout << "\nOPERADORES DISPONIBLES:" << endl;
        auto operadores = evaluador.obtenerOperadoresDisponibles();
        for (char op : operadores)
        {
            cout << "  " << op;
        }
        cout << endl;

        if (modoAvanzado)
        {
            cout << "\nFUNCIONES DISPONIBLES:" << endl;
            auto funciones = evaluador.obtenerFuncionesDisponibles();
            for (size_t i = 0; i < funciones.size(); ++i)
            {
                cout << "  " << funciones[i];
                if ((i + 1) % 6 == 0)
                    cout << endl;
            }
            cout << endl;

            cout << "\nEJEMPLOS DE EXPRESIONES:" << endl;
            cout << "  2 + 3 * 4" << endl;
            cout << "  sin(3.14159/2)" << endl;
            cout << "  sqrt(16) + log(100)" << endl;
            cout << "  (2 + 3) * 4 / 2" << endl;
            cout << "  2^3 + exp(1)" << endl;
        }
        else
        {
            cout << "\nMODO BÁSICO - Solo operaciones aritméticas simples" << endl;
            cout << "Ejemplos: 2+3, 5*4, 10/2, 2^3" << endl;
        }
        cout << endl;
    }

    void cambiarModo()
    {
        modoAvanzado = !modoAvanzado;
        cout << "Modo cambiado a: " << (modoAvanzado ? "AVANZADO" : "BÁSICO") << endl;
        if (modoAvanzado)
        {
            cout << "Ahora puedes usar funciones matemáticas y expresiones complejas." << endl;
        }
        else
        {
            cout << "Ahora solo puedes usar operaciones aritméticas básicas." << endl;
        }
    }

    void procesarExpresion(const string &expresion)
    {
        try
        {
            double resultado = evaluador.evaluar(expresion);

            cout << fixed << setprecision(6) << resultado << endl;

            // Agregar al historial
            string descripcion = "Evaluación de expresión";
            if (!modoAvanzado)
            {
                descripcion += " (modo básico)";
            }

            historial.agregarOperacion(OperacionMatematica(expresion, resultado, descripcion, true));
        }
        catch (const exception &e)
        {
            string mensajeError = e.what();
            cout << "Error: " << mensajeError << endl;

            // Agregar error al historial
            historial.agregarOperacion(OperacionMatematica(expresion, 0.0, mensajeError, false));
        }
    }
};

int main()
{
    try
    {
        Calculadora calc;
        calc.ejecutar();
    }
    catch (const exception &e)
    {
        cerr << "Error fatal: " << e.what() << endl;
        return 1;
    }

    return 0;
}