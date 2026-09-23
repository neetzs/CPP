#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <ctime>
#include <chrono>
#include <map>
#include <set>
#include <functional>
#include <limits>
#include <cctype>
#include <regex>
using namespace std;
using namespace chrono;

// Enumeraciones
enum class TipoPersona
{
    EMPLEADO,
    ESTUDIANTE,
    CLIENTE
};
enum class Departamento
{
    VENTAS,
    MARKETING,
    IT,
    RRHH,
    FINANZAS,
    PRODUCCION
};
enum class Carrera
{
    INGENIERIA,
    MEDICINA,
    DERECHO,
    ADMINISTRACION,
    ARQUITECTURA,
    OTROS
};

// Clase base abstracta Persona
class Persona
{
protected:
    int id;
    string nombre;
    string apellido;
    string email;
    string telefono;
    string fechaNacimiento; // formato dd/mm/yyyy
    TipoPersona tipo;
    string fechaRegistro;

public:
    Persona(int id = 0, const string &n = "", const string &a = "",
            const string &e = "", const string &t = "", const string &fn = "",
            TipoPersona tp = TipoPersona::EMPLEADO)
        : id(id), nombre(n), apellido(a), email(e), telefono(t),
          fechaNacimiento(fn), tipo(tp)
    {
        // Fecha de registro automática
        auto ahora = system_clock::now();
        time_t tiempo = system_clock::to_time_t(ahora);
        tm *fechaLocal = localtime(&tiempo);
        ostringstream oss;
        oss << setfill('0') << setw(2) << fechaLocal->tm_mday << "/"
            << setfill('0') << setw(2) << (fechaLocal->tm_mon + 1) << "/"
            << (fechaLocal->tm_year + 1900);
        fechaRegistro = oss.str();
    }

    virtual ~Persona() = default;

    // Getters
    int obtenerId() const { return id; }
    string obtenerNombre() const { return nombre; }
    string obtenerApellido() const { return apellido; }
    string obtenerNombreCompleto() const { return nombre + " " + apellido; }
    string obtenerEmail() const { return email; }
    string obtenerTelefono() const { return telefono; }
    string obtenerFechaNacimiento() const { return fechaNacimiento; }
    TipoPersona obtenerTipo() const { return tipo; }
    string obtenerFechaRegistro() const { return fechaRegistro; }

    // Setters
    void establecerId(int i) { id = i; }
    void establecerNombre(const string &n) { nombre = n; }
    void establecerApellido(const string &a) { apellido = a; }
    void establecerEmail(const string &e) { email = e; }
    void establecerTelefono(const string &t) { telefono = t; }
    void establecerFechaNacimiento(const string &fn) { fechaNacimiento = fn; }

    // Métodos virtuales puros
    virtual void mostrarInformacion() const = 0;
    virtual string obtenerTipoString() const = 0;
    virtual string serializar() const = 0;
    virtual void deserializar(const string &datos) = 0;

    // Métodos comunes
    int calcularEdad() const
    {
        if (fechaNacimiento.empty())
            return 0;

        // Parsear fecha de nacimiento
        vector<int> partes;
        stringstream ss(fechaNacimiento);
        string token;
        while (getline(ss, token, '/'))
        {
            partes.push_back(stoi(token));
        }

        if (partes.size() != 3)
            return 0;

        // Fecha actual
        auto ahora = system_clock::now();
        time_t tiempo = system_clock::to_time_t(ahora);
        tm *fechaActual = localtime(&tiempo);

        int edad = fechaActual->tm_year + 1900 - partes[2];

        // Ajustar si no ha cumplido años este año
        if (fechaActual->tm_mon + 1 < partes[1] ||
            (fechaActual->tm_mon + 1 == partes[1] && fechaActual->tm_mday < partes[0]))
        {
            edad--;
        }

        return edad;
    }

    bool validarEmail() const
    {
        regex patronEmail(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return regex_match(email, patronEmail);
    }

    bool validarTelefono() const
    {
        // Teléfono chileno: +569XXXXXXXX o 9XXXXXXXX
        regex patronTelefono(R"((?:\+569|9)\d{8})");
        return regex_match(telefono, patronTelefono);
    }

    // Método para mostrar información básica
    void mostrarBasica() const
    {
        cout << "ID: " << id << endl;
        cout << "Nombre: " << obtenerNombreCompleto() << endl;
        cout << "Tipo: " << obtenerTipoString() << endl;
        cout << "Email: " << email << endl;
        cout << "Teléfono: " << telefono << endl;
        if (!fechaNacimiento.empty())
        {
            cout << "Edad: " << calcularEdad() << " años" << endl;
        }
        cout << "Fecha de registro: " << fechaRegistro << endl;
    }
};

// Clase Empleado
class Empleado : public Persona
{
private:
    double salario;
    string puesto;
    Departamento departamento;
    string fechaContratacion;

public:
    Empleado(int id = 0, const string &n = "", const string &a = "",
             const string &e = "", const string &t = "", const string &fn = "",
             double s = 0.0, const string &p = "", Departamento d = Departamento::IT)
        : Persona(id, n, a, e, t, fn, TipoPersona::EMPLEADO),
          salario(s), puesto(p), departamento(d)
    {
        fechaContratacion = fechaRegistro; // Contratado hoy
    }

    // Getters específicos
    double obtenerSalario() const { return salario; }
    string obtenerPuesto() const { return puesto; }
    Departamento obtenerDepartamento() const { return departamento; }
    string obtenerFechaContratacion() const { return fechaContratacion; }

    // Setters específicos
    void establecerSalario(double s) { salario = s; }
    void establecerPuesto(const string &p) { puesto = p; }
    void establecerDepartamento(Departamento d) { departamento = d; }

    // Implementación de métodos virtuales
    void mostrarInformacion() const override
    {
        cout << "\n=== EMPLEADO ===" << endl;
        mostrarBasica();
        cout << "Puesto: " << puesto << endl;
        cout << "Departamento: " << departamentoToString(departamento) << endl;
        cout << "Salario: $" << fixed << setprecision(0) << salario << endl;
        cout << "Fecha de contratación: " << fechaContratacion << endl;
        cout << "Antigüedad: " << calcularAntiguedad() << " días" << endl;
    }

    string obtenerTipoString() const override
    {
        return "Empleado";
    }

    string serializar() const override
    {
        ostringstream oss;
        oss << "EMPLEADO|" << id << "|" << nombre << "|" << apellido << "|"
            << email << "|" << telefono << "|" << fechaNacimiento << "|"
            << fixed << setprecision(2) << salario << "|" << puesto << "|"
            << static_cast<int>(departamento) << "|" << fechaContratacion;
        return oss.str();
    }

    void deserializar(const string &datos) override
    {
        vector<string> partes = dividirString(datos, '|');
        if (partes.size() >= 11)
        {
            id = stoi(partes[1]);
            nombre = partes[2];
            apellido = partes[3];
            email = partes[4];
            telefono = partes[5];
            fechaNacimiento = partes[6];
            salario = stod(partes[7]);
            puesto = partes[8];
            departamento = static_cast<Departamento>(stoi(partes[9]));
            fechaContratacion = partes[10];
        }
    }

private:
    string departamentoToString(Departamento d) const
    {
        switch (d)
        {
        case Departamento::VENTAS:
            return "Ventas";
        case Departamento::MARKETING:
            return "Marketing";
        case Departamento::IT:
            return "IT";
        case Departamento::RRHH:
            return "RRHH";
        case Departamento::FINANZAS:
            return "Finanzas";
        case Departamento::PRODUCCION:
            return "Producción";
        default:
            return "Desconocido";
        }
    }

    int calcularAntiguedad() const
    {
        // Implementación simplificada
        auto ahora = system_clock::now();
        time_t tiempo = system_clock::to_time_t(ahora);
        tm *fechaActual = localtime(&tiempo);

        // Parsear fecha de contratación
        vector<int> partes;
        stringstream ss(fechaContratacion);
        string token;
        while (getline(ss, token, '/'))
        {
            partes.push_back(stoi(token));
        }

        if (partes.size() != 3)
            return 0;

        // Cálculo simplificado de días
        int diasActual = fechaActual->tm_year * 365 + fechaActual->tm_mon * 30 + fechaActual->tm_mday;
        int diasContratacion = partes[2] * 365 + partes[1] * 30 + partes[0];

        return max(0, diasActual - diasContratacion);
    }

    vector<string> dividirString(const string &str, char delimitador) const
    {
        vector<string> partes;
        stringstream ss(str);
        string token;
        while (getline(ss, token, delimitador))
        {
            partes.push_back(token);
        }
        return partes;
    }
};

// Clase Estudiante
class Estudiante : public Persona
{
private:
    Carrera carrera;
    int semestre;
    double promedio;
    string universidad;

public:
    Estudiante(int id = 0, const string &n = "", const string &a = "",
               const string &e = "", const string &t = "", const string &fn = "",
               Carrera c = Carrera::INGENIERIA, int s = 1, double p = 0.0,
               const string &u = "")
        : Persona(id, n, a, e, t, fn, TipoPersona::ESTUDIANTE),
          carrera(c), semestre(s), promedio(p), universidad(u) {}

    // Getters específicos
    Carrera obtenerCarrera() const { return carrera; }
    int obtenerSemestre() const { return semestre; }
    double obtenerPromedio() const { return promedio; }
    string obtenerUniversidad() const { return universidad; }

    // Setters específicos
    void establecerCarrera(Carrera c) { carrera = c; }
    void establecerSemestre(int s) { semestre = s; }
    void establecerPromedio(double p) { promedio = p; }
    void establecerUniversidad(const string &u) { universidad = u; }

    // Implementación de métodos virtuales
    void mostrarInformacion() const override
    {
        cout << "\n=== ESTUDIANTE ===" << endl;
        mostrarBasica();
        cout << "Universidad: " << universidad << endl;
        cout << "Carrera: " << carreraToString(carrera) << endl;
        cout << "Semestre: " << semestre << endl;
        cout << "Promedio: " << fixed << setprecision(1) << promedio << endl;
        cout << "Estado académico: " << obtenerEstadoAcademico() << endl;
    }

    string obtenerTipoString() const override
    {
        return "Estudiante";
    }

    string serializar() const override
    {
        ostringstream oss;
        oss << "ESTUDIANTE|" << id << "|" << nombre << "|" << apellido << "|"
            << email << "|" << telefono << "|" << fechaNacimiento << "|"
            << static_cast<int>(carrera) << "|" << semestre << "|"
            << fixed << setprecision(2) << promedio << "|" << universidad;
        return oss.str();
    }

    void deserializar(const string &datos) override
    {
        vector<string> partes = dividirString(datos, '|');
        if (partes.size() >= 11)
        {
            id = stoi(partes[1]);
            nombre = partes[2];
            apellido = partes[3];
            email = partes[4];
            telefono = partes[5];
            fechaNacimiento = partes[6];
            carrera = static_cast<Carrera>(stoi(partes[7]));
            semestre = stoi(partes[8]);
            promedio = stod(partes[9]);
            universidad = partes[10];
        }
    }

private:
    string carreraToString(Carrera c) const
    {
        switch (c)
        {
        case Carrera::INGENIERIA:
            return "Ingeniería";
        case Carrera::MEDICINA:
            return "Medicina";
        case Carrera::DERECHO:
            return "Derecho";
        case Carrera::ADMINISTRACION:
            return "Administración";
        case Carrera::ARQUITECTURA:
            return "Arquitectura";
        case Carrera::OTROS:
            return "Otros";
        default:
            return "Desconocida";
        }
    }

    string obtenerEstadoAcademico() const
    {
        if (promedio >= 6.0)
            return "Excelente";
        if (promedio >= 5.0)
            return "Bueno";
        if (promedio >= 4.0)
            return "Regular";
        return "Deficiente";
    }

    vector<string> dividirString(const string &str, char delimitador) const
    {
        vector<string> partes;
        stringstream ss(str);
        string token;
        while (getline(ss, token, delimitador))
        {
            partes.push_back(token);
        }
        return partes;
    }
};

// Clase Cliente
class Cliente : public Persona
{
private:
    string empresa;
    double presupuesto;
    string intereses;
    string contactoPreferido;

public:
    Cliente(int id = 0, const string &n = "", const string &a = "",
            const string &e = "", const string &t = "", const string &fn = "",
            const string &emp = "", double pres = 0.0, const string &inte = "",
            const string &cont = "")
        : Persona(id, n, a, e, t, fn, TipoPersona::CLIENTE),
          empresa(emp), presupuesto(pres), intereses(inte), contactoPreferido(cont) {}

    // Getters específicos
    string obtenerEmpresa() const { return empresa; }
    double obtenerPresupuesto() const { return presupuesto; }
    string obtenerIntereses() const { return intereses; }
    string obtenerContactoPreferido() const { return contactoPreferido; }

    // Setters específicos
    void establecerEmpresa(const string &emp) { empresa = emp; }
    void establecerPresupuesto(double pres) { presupuesto = pres; }
    void establecerIntereses(const string &inte) { intereses = inte; }
    void establecerContactoPreferido(const string &cont) { contactoPreferido = cont; }

    // Implementación de métodos virtuales
    void mostrarInformacion() const override
    {
        cout << "\n=== CLIENTE ===" << endl;
        mostrarBasica();
        cout << "Empresa: " << empresa << endl;
        cout << "Presupuesto: $" << fixed << setprecision(0) << presupuesto << endl;
        cout << "Intereses: " << intereses << endl;
        cout << "Contacto preferido: " << contactoPreferido << endl;
        cout << "Categoría: " << obtenerCategoriaCliente() << endl;
    }

    string obtenerTipoString() const override
    {
        return "Cliente";
    }

    string serializar() const override
    {
        ostringstream oss;
        oss << "CLIENTE|" << id << "|" << nombre << "|" << apellido << "|"
            << email << "|" << telefono << "|" << fechaNacimiento << "|"
            << empresa << "|" << fixed << setprecision(2) << presupuesto << "|"
            << intereses << "|" << contactoPreferido;
        return oss.str();
    }

    void deserializar(const string &datos) override
    {
        vector<string> partes = dividirString(datos, '|');
        if (partes.size() >= 11)
        {
            id = stoi(partes[1]);
            nombre = partes[2];
            apellido = partes[3];
            email = partes[4];
            telefono = partes[5];
            fechaNacimiento = partes[6];
            empresa = partes[7];
            presupuesto = stod(partes[8]);
            intereses = partes[9];
            contactoPreferido = partes[10];
        }
    }

private:
    string obtenerCategoriaCliente() const
    {
        if (presupuesto >= 1000000)
            return "Premium";
        if (presupuesto >= 500000)
            return "Gold";
        if (presupuesto >= 100000)
            return "Silver";
        return "Bronze";
    }

    vector<string> dividirString(const string &str, char delimitador) const
    {
        vector<string> partes;
        stringstream ss(str);
        string token;
        while (getline(ss, token, delimitador))
        {
            partes.push_back(token);
        }
        return partes;
    }
};

// Clase para estadísticas
class EstadisticasPersonas
{
public:
    static void mostrarEstadisticas(const vector<unique_ptr<Persona>> &personas)
    {
        if (personas.empty())
        {
            cout << "No hay personas para mostrar estadísticas." << endl;
            return;
        }

        cout << "\n=== ESTADÍSTICAS ===" << endl;

        // Contadores por tipo
        int empleados = 0, estudiantes = 0, clientes = 0;
        double sumaSalarios = 0.0;
        double sumaPresupuestos = 0.0;
        int sumaEdades = 0;
        int contadorEdades = 0;

        for (const auto &persona : personas)
        {
            switch (persona->obtenerTipo())
            {
            case TipoPersona::EMPLEADO:
            {
                empleados++;
                const Empleado *emp = dynamic_cast<const Empleado *>(persona.get());
                if (emp)
                    sumaSalarios += emp->obtenerSalario();
                break;
            }
            case TipoPersona::ESTUDIANTE:
            {
                estudiantes++;
                break;
            }
            case TipoPersona::CLIENTE:
            {
                clientes++;
                const Cliente *cli = dynamic_cast<const Cliente *>(persona.get());
                if (cli)
                    sumaPresupuestos += cli->obtenerPresupuesto();
                break;
            }
            }

            int edad = persona->calcularEdad();
            if (edad > 0)
            {
                sumaEdades += edad;
                contadorEdades++;
            }
        }

        cout << "Total de personas: " << personas.size() << endl;
        cout << "Empleados: " << empleados << endl;
        cout << "Estudiantes: " << estudiantes << endl;
        cout << "Clientes: " << clientes << endl;

        if (empleados > 0)
        {
            cout << "Salario promedio empleados: $" << fixed << setprecision(0)
                 << (sumaSalarios / empleados) << endl;
        }

        if (clientes > 0)
        {
            cout << "Presupuesto promedio clientes: $" << fixed << setprecision(0)
                 << (sumaPresupuestos / clientes) << endl;
        }

        if (contadorEdades > 0)
        {
            cout << "Edad promedio: " << fixed << setprecision(1)
                 << (static_cast<double>(sumaEdades) / contadorEdades) << " años" << endl;
        }

        cout << endl;
    }
};

// Clase principal del gestor
class GestorPersonas
{
private:
    vector<unique_ptr<Persona>> personas;
    int siguienteId;
    string archivoDatos;

public:
    GestorPersonas(const string &archivo = "personas.dat")
        : siguienteId(1), archivoDatos(archivo)
    {
        cargarDesdeArchivo();
    }

    ~GestorPersonas()
    {
        guardarEnArchivo();
    }

    // CRUD
    void agregarPersona(unique_ptr<Persona> persona)
    {
        persona->establecerId(siguienteId++);
        personas.push_back(move(persona));
        cout << "✓ Persona agregada con ID: " << personas.back()->obtenerId() << endl;
    }

    bool eliminarPersona(int id)
    {
        auto it = find_if(personas.begin(), personas.end(),
                          [id](const unique_ptr<Persona> &p)
                          { return p->obtenerId() == id; });

        if (it != personas.end())
        {
            personas.erase(it);
            cout << "✓ Persona eliminada" << endl;
            return true;
        }

        cout << "✗ Persona no encontrada" << endl;
        return false;
    }

    bool editarPersona(int id)
    {
        Persona *persona = buscarPorId(id);
        if (!persona)
        {
            cout << "✗ Persona no encontrada" << endl;
            return false;
        }

        cout << "Editando persona (deje vacío para mantener el valor actual):" << endl;

        // Nombre
        cout << "Nombre actual: " << persona->obtenerNombre() << endl;
        cout << "Nuevo nombre: ";
        string nuevoNombre;
        getline(cin, nuevoNombre);
        if (!nuevoNombre.empty())
        {
            persona->establecerNombre(nuevoNombre);
        }

        // Apellido
        cout << "Apellido actual: " << persona->obtenerApellido() << endl;
        cout << "Nuevo apellido: ";
        string nuevoApellido;
        getline(cin, nuevoApellido);
        if (!nuevoApellido.empty())
        {
            persona->establecerApellido(nuevoApellido);
        }

        // Email
        cout << "Email actual: " << persona->obtenerEmail() << endl;
        cout << "Nuevo email: ";
        string nuevoEmail;
        getline(cin, nuevoEmail);
        if (!nuevoEmail.empty())
        {
            persona->establecerEmail(nuevoEmail);
        }

        // Teléfono
        cout << "Teléfono actual: " << persona->obtenerTelefono() << endl;
        cout << "Nuevo teléfono: ";
        string nuevoTelefono;
        getline(cin, nuevoTelefono);
        if (!nuevoTelefono.empty())
        {
            persona->establecerTelefono(nuevoTelefono);
        }

        // Editar campos específicos según el tipo
        editarCamposEspecificos(persona);

        cout << "✓ Persona actualizada" << endl;
        return true;
    }

    // Búsqueda
    Persona *buscarPorId(int id)
    {
        auto it = find_if(personas.begin(), personas.end(),
                          [id](const unique_ptr<Persona> &p)
                          { return p->obtenerId() == id; });
        return (it != personas.end()) ? it->get() : nullptr;
    }

    vector<Persona *> buscarPorNombre(const string &nombre)
    {
        vector<Persona *> resultados;
        string nombreBusqueda = nombre;
        transform(nombreBusqueda.begin(), nombreBusqueda.end(), nombreBusqueda.begin(), ::tolower);

        for (const auto &persona : personas)
        {
            string nombreCompleto = persona->obtenerNombreCompleto();
            transform(nombreCompleto.begin(), nombreCompleto.end(), nombreCompleto.begin(), ::tolower);

            if (nombreCompleto.find(nombreBusqueda) != string::npos)
            {
                resultados.push_back(persona.get());
            }
        }

        return resultados;
    }

    vector<Persona *> filtrarPorTipo(TipoPersona tipo)
    {
        vector<Persona *> resultados;
        for (const auto &persona : personas)
        {
            if (persona->obtenerTipo() == tipo)
            {
                resultados.push_back(persona.get());
            }
        }
        return resultados;
    }

    // Mostrar
    void mostrarTodas() const
    {
        if (personas.empty())
        {
            cout << "No hay personas registradas." << endl;
            return;
        }

        cout << "\n=== TODAS LAS PERSONAS ===" << endl;
        for (const auto &persona : personas)
        {
            persona->mostrarInformacion();
        }
    }

    void mostrarPersonas(const vector<Persona *> &lista) const
    {
        if (lista.empty())
        {
            cout << "No se encontraron personas." << endl;
            return;
        }

        cout << "\n=== RESULTADOS ===" << endl;
        for (Persona *persona : lista)
        {
            persona->mostrarInformacion();
        }
    }

    // Estadísticas
    void mostrarEstadisticas() const
    {
        EstadisticasPersonas::mostrarEstadisticas(personas);
    }

    // Persistencia
    bool guardarEnArchivo() const
    {
        ofstream archivo(archivoDatos);
        if (!archivo.is_open())
        {
            cerr << "Error: No se pudo abrir el archivo para guardar" << endl;
            return false;
        }

        for (const auto &persona : personas)
        {
            archivo << persona->serializar() << endl;
        }

        archivo.close();
        return true;
    }

    bool cargarDesdeArchivo()
    {
        ifstream archivo(archivoDatos);
        if (!archivo.is_open())
        {
            return false;
        }

        personas.clear();
        string linea;
        while (getline(archivo, linea))
        {
            if (!linea.empty())
            {
                unique_ptr<Persona> persona = crearPersonaDesdeString(linea);
                if (persona)
                {
                    personas.push_back(move(persona));
                    if (personas.back()->obtenerId() >= siguienteId)
                    {
                        siguienteId = personas.back()->obtenerId() + 1;
                    }
                }
            }
        }

        archivo.close();
        return true;
    }

    // Utilidades
    size_t obtenerCantidadPersonas() const
    {
        return personas.size();
    }

    void ordenarPorNombre()
    {
        sort(personas.begin(), personas.end(),
             [](const unique_ptr<Persona> &a, const unique_ptr<Persona> &b)
             {
                 return a->obtenerNombreCompleto() < b->obtenerNombreCompleto();
             });
        cout << "✓ Personas ordenadas por nombre" << endl;
    }

    void ordenarPorTipo()
    {
        sort(personas.begin(), personas.end(),
             [](const unique_ptr<Persona> &a, const unique_ptr<Persona> &b)
             {
                 return static_cast<int>(a->obtenerTipo()) < static_cast<int>(b->obtenerTipo());
             });
        cout << "✓ Personas ordenadas por tipo" << endl;
    }

private:
    unique_ptr<Persona> crearPersonaDesdeString(const string &linea)
    {
        vector<string> partes = dividirString(linea, '|');
        if (partes.empty())
            return nullptr;

        string tipo = partes[0];
        unique_ptr<Persona> persona;

        if (tipo == "EMPLEADO")
        {
            persona = make_unique<Empleado>();
        }
        else if (tipo == "ESTUDIANTE")
        {
            persona = make_unique<Estudiante>();
        }
        else if (tipo == "CLIENTE")
        {
            persona = make_unique<Cliente>();
        }

        if (persona)
        {
            persona->deserializar(linea);
        }

        return persona;
    }

    vector<string> dividirString(const string &str, char delimitador) const
    {
        vector<string> partes;
        stringstream ss(str);
        string token;
        while (getline(ss, token, delimitador))
        {
            partes.push_back(token);
        }
        return partes;
    }

    void editarCamposEspecificos(Persona *persona)
    {
        switch (persona->obtenerTipo())
        {
        case TipoPersona::EMPLEADO:
        {
            Empleado *emp = dynamic_cast<Empleado *>(persona);
            if (emp)
            {
                // Salario
                cout << "Salario actual: $" << emp->obtenerSalario() << endl;
                cout << "Nuevo salario: ";
                string inputSalario;
                getline(cin, inputSalario);
                if (!inputSalario.empty())
                {
                    emp->establecerSalario(stod(inputSalario));
                }

                // Puesto
                cout << "Puesto actual: " << emp->obtenerPuesto() << endl;
                cout << "Nuevo puesto: ";
                string nuevoPuesto;
                getline(cin, nuevoPuesto);
                if (!nuevoPuesto.empty())
                {
                    emp->establecerPuesto(nuevoPuesto);
                }
            }
            break;
        }

        case TipoPersona::ESTUDIANTE:
        {
            Estudiante *est = dynamic_cast<Estudiante *>(persona);
            if (est)
            {
                // Universidad
                cout << "Universidad actual: " << est->obtenerUniversidad() << endl;
                cout << "Nueva universidad: ";
                string nuevaUniversidad;
                getline(cin, nuevaUniversidad);
                if (!nuevaUniversidad.empty())
                {
                    est->establecerUniversidad(nuevaUniversidad);
                }

                // Semestre
                cout << "Semestre actual: " << est->obtenerSemestre() << endl;
                cout << "Nuevo semestre: ";
                string inputSemestre;
                getline(cin, inputSemestre);
                if (!inputSemestre.empty())
                {
                    est->establecerSemestre(stoi(inputSemestre));
                }
            }
            break;
        }

        case TipoPersona::CLIENTE:
        {
            Cliente *cli = dynamic_cast<Cliente *>(persona);
            if (cli)
            {
                // Empresa
                cout << "Empresa actual: " << cli->obtenerEmpresa() << endl;
                cout << "Nueva empresa: ";
                string nuevaEmpresa;
                getline(cin, nuevaEmpresa);
                if (!nuevaEmpresa.empty())
                {
                    cli->establecerEmpresa(nuevaEmpresa);
                }

                // Presupuesto
                cout << "Presupuesto actual: $" << cli->obtenerPresupuesto() << endl;
                cout << "Nuevo presupuesto: ";
                string inputPresupuesto;
                getline(cin, inputPresupuesto);
                if (!inputPresupuesto.empty())
                {
                    cli->establecerPresupuesto(stod(inputPresupuesto));
                }
            }
            break;
        }
        }
    }
};

// Funciones de utilidad para la interfaz
unique_ptr<Persona> crearPersonaDesdeEntrada()
{
    cout << "Tipo de persona (1-Empleado, 2-Estudiante, 3-Cliente): ";
    int tipo;
    cin >> tipo;
    cin.ignore(); // Limpiar buffer

    // Datos básicos
    string nombre, apellido, email, telefono, fechaNacimiento;

    cout << "Nombre: ";
    getline(cin, nombre);

    cout << "Apellido: ";
    getline(cin, apellido);

    cout << "Email: ";
    getline(cin, email);

    cout << "Teléfono: ";
    getline(cin, telefono);

    cout << "Fecha de nacimiento (dd/mm/yyyy): ";
    getline(cin, fechaNacimiento);

    unique_ptr<Persona> persona;

    switch (tipo)
    {
    case 1:
    { // Empleado
        double salario;
        string puesto;
        int departamento;

        cout << "Salario: ";
        cin >> salario;
        cin.ignore();

        cout << "Puesto: ";
        getline(cin, puesto);

        cout << "Departamento (1-Ventas, 2-Marketing, 3-IT, 4-RRHH, 5-Finanzas, 6-Producción): ";
        cin >> departamento;
        cin.ignore();

        persona = make_unique<Empleado>(0, nombre, apellido, email, telefono,
                                        fechaNacimiento, salario, puesto,
                                        static_cast<Departamento>(departamento - 1));
        break;
    }

    case 2:
    { // Estudiante
        int carrera, semestre;
        double promedio;
        string universidad;

        cout << "Universidad: ";
        getline(cin, universidad);

        cout << "Carrera (1-Ingeniería, 2-Medicina, 3-Derecho, 4-Administración, 5-Arquitectura, 6-Otros): ";
        cin >> carrera;
        cin.ignore();

        cout << "Semestre: ";
        cin >> semestre;
        cin.ignore();

        cout << "Promedio: ";
        cin >> promedio;
        cin.ignore();

        persona = make_unique<Estudiante>(0, nombre, apellido, email, telefono,
                                          fechaNacimiento, static_cast<Carrera>(carrera - 1),
                                          semestre, promedio, universidad);
        break;
    }

    case 3:
    { // Cliente
        string empresa, intereses, contactoPreferido;
        double presupuesto;

        cout << "Empresa: ";
        getline(cin, empresa);

        cout << "Presupuesto: ";
        cin >> presupuesto;
        cin.ignore();

        cout << "Intereses: ";
        getline(cin, intereses);

        cout << "Contacto preferido: ";
        getline(cin, contactoPreferido);

        persona = make_unique<Cliente>(0, nombre, apellido, email, telefono,
                                       fechaNacimiento, empresa, presupuesto,
                                       intereses, contactoPreferido);
        break;
    }

    default:
    {
        cout << "Tipo inválido" << endl;
        return nullptr;
    }
    }

    return persona;
}

void mostrarMenu()
{
    cout << "\n=== SISTEMA DE GESTIÓN DE PERSONAS ===" << endl;
    cout << "1. Agregar persona" << endl;
    cout << "2. Ver todas las personas" << endl;
    cout << "3. Buscar persona por ID" << endl;
    cout << "4. Buscar personas por nombre" << endl;
    cout << "5. Filtrar por tipo" << endl;
    cout << "6. Editar persona" << endl;
    cout << "7. Eliminar persona" << endl;
    cout << "8. Mostrar estadísticas" << endl;
    cout << "9. Ordenar por nombre" << endl;
    cout << "10. Ordenar por tipo" << endl;
    cout << "0. Salir" << endl;
    cout << "Opción: ";
}

int main()
{
    GestorPersonas gestor;

    cout << "¡Bienvenido al Sistema de Gestión de Personas!" << endl;
    cout << "Los datos se guardan automáticamente al salir." << endl;

    while (true)
    {
        mostrarMenu();

        int opcion;
        cin >> opcion;
        cin.ignore(); // Limpiar buffer

        switch (opcion)
        {
        case 1:
        { // Agregar persona
            cout << "\n--- AGREGAR PERSONA ---" << endl;
            auto nuevaPersona = crearPersonaDesdeEntrada();
            if (nuevaPersona)
            {
                gestor.agregarPersona(move(nuevaPersona));
            }
            break;
        }

        case 2:
        { // Ver todas
            gestor.mostrarTodas();
            break;
        }

        case 3:
        { // Buscar por ID
            cout << "ID de la persona: ";
            int id;
            cin >> id;
            cin.ignore();

            Persona *persona = gestor.buscarPorId(id);
            if (persona)
            {
                cout << "\n--- PERSONA ENCONTRADA ---" << endl;
                persona->mostrarInformacion();
            }
            else
            {
                cout << "Persona no encontrada." << endl;
            }
            break;
        }

        case 4:
        { // Buscar por nombre
            cout << "Nombre a buscar: ";
            string nombre;
            getline(cin, nombre);

            auto resultados = gestor.buscarPorNombre(nombre);
            gestor.mostrarPersonas(resultados);
            break;
        }

        case 5:
        { // Filtrar por tipo
            cout << "Tipo (1-Empleado, 2-Estudiante, 3-Cliente): ";
            int tipo;
            cin >> tipo;
            cin.ignore();

            auto resultados = gestor.filtrarPorTipo(static_cast<TipoPersona>(tipo - 1));
            gestor.mostrarPersonas(resultados);
            break;
        }

        case 6:
        { // Editar persona
            cout << "ID de la persona a editar: ";
            int idEditar;
            cin >> idEditar;
            cin.ignore();

            gestor.editarPersona(idEditar);
            break;
        }

        case 7:
        { // Eliminar persona
            cout << "ID de la persona a eliminar: ";
            int idEliminar;
            cin >> idEliminar;
            cin.ignore();

            gestor.eliminarPersona(idEliminar);
            break;
        }

        case 8:
        { // Estadísticas
            gestor.mostrarEstadisticas();
            break;
        }

        case 9:
        { // Ordenar por nombre
            gestor.ordenarPorNombre();
            break;
        }

        case 10:
        { // Ordenar por tipo
            gestor.ordenarPorTipo();
            break;
        }

        case 0:
        { // Salir
            cout << "¡Hasta luego!" << endl;
            return 0;
        }

        default:
        {
            cout << "Opción inválida. Intente nuevamente." << endl;
            break;
        }
        }
    }

    return 0;
}