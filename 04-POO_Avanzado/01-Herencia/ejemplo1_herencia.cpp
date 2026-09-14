#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Clase base: Empleado
class Empleado
{
protected:
    string nombre;
    string id;
    double salarioBase;

public:
    Empleado(string n, string i, double s)
        : nombre(n), id(i), salarioBase(s) {}

    virtual ~Empleado()
    {
        cout << "Destructor de Empleado: " << nombre << endl;
    }

    // Métodos comunes
    string obtenerNombre() const { return nombre; }
    string obtenerId() const { return id; }

    // Método virtual - puede ser sobrescrito
    virtual double calcularSalario() const
    {
        return salarioBase;
    }

    virtual void mostrarInformacion() const
    {
        cout << "Empleado: " << nombre << " (ID: " << id << ")" << endl;
        cout << "Salario base: $" << salarioBase << endl;
    }
};

// Clase derivada: Desarrollador
class Desarrollador : public Empleado
{
private:
    string lenguajePrincipal;
    int anosExperiencia;

public:
    Desarrollador(string n, string i, double s, string leng, int exp)
        : Empleado(n, i, s), lenguajePrincipal(leng), anosExperiencia(exp) {}

    ~Desarrollador()
    {
        cout << "Destructor de Desarrollador: " << nombre << endl;
    }

    // Sobrescribir método virtual
    double calcularSalario() const override
    {
        double bono = anosExperiencia * 1000;
        return salarioBase + bono;
    }

    void mostrarInformacion() const override
    {
        Empleado::mostrarInformacion();
        cout << "Lenguaje principal: " << lenguajePrincipal << endl;
        cout << "Años de experiencia: " << anosExperiencia << endl;
        cout << "Salario total: $" << calcularSalario() << endl;
    }

    void programar() const
    {
        cout << nombre << " está programando en " << lenguajePrincipal << endl;
    }
};

// Clase derivada: Gerente
class Gerente : public Empleado
{
private:
    int numeroEmpleados;
    double bonoAnual;

public:
    Gerente(string n, string i, double s, int numEmp, double bono)
        : Empleado(n, i, s), numeroEmpleados(numEmp), bonoAnual(bono) {}

    ~Gerente()
    {
        cout << "Destructor de Gerente: " << nombre << endl;
    }

    double calcularSalario() const override
    {
        return salarioBase + bonoAnual;
    }

    void mostrarInformacion() const override
    {
        Empleado::mostrarInformacion();
        cout << "Empleados a cargo: " << numeroEmpleados << endl;
        cout << "Bono anual: $" << bonoAnual << endl;
        cout << "Salario total: $" << calcularSalario() << endl;
    }

    void gestionar() const
    {
        cout << nombre << " está gestionando " << numeroEmpleados << " empleados" << endl;
    }
};

// Clase derivada de Desarrollador: Arquitecto
class Arquitecto : public Desarrollador
{
private:
    vector<string> tecnologias;
    int proyectosCompletados;

public:
    Arquitecto(string n, string i, double s, string leng, int exp, vector<string> tech, int proy)
        : Desarrollador(n, i, s, leng, exp), tecnologias(tech), proyectosCompletados(proy) {}

    double calcularSalario() const override
    {
        double bonoBase = Desarrollador::calcularSalario() - salarioBase;
        double bonoArquitecto = proyectosCompletados * 2000;
        return salarioBase + bonoBase + bonoArquitecto;
    }

    void mostrarInformacion() const override
    {
        Desarrollador::mostrarInformacion();
        cout << "Tecnologías: ";
        for (const auto &tech : tecnologias)
        {
            cout << tech << " ";
        }
        cout << endl;
        cout << "Proyectos completados: " << proyectosCompletados << endl;
        cout << "Salario total (con bono arquitecto): $" << calcularSalario() << endl;
    }

    void disenharArquitectura() const
    {
        cout << nombre << " está diseñando arquitectura del sistema" << endl;
    }
};

// Función que demuestra polimorfismo
void procesarEmpleados(const vector<Empleado *> &empleados)
{
    cout << "\n=== PROCESANDO EMPLEADOS ===" << endl;
    for (const auto &emp : empleados)
    {
        emp->mostrarInformacion();
        cout << "------------------------" << endl;
    }
}

int main()
{
    cout << "=== SISTEMA DE EMPLEADOS ===" << endl;

    // Crear empleados de diferentes tipos
    Desarrollador dev("Juan Pérez", "DEV001", 50000, "C++", 5);
    Gerente mgr("María García", "MGR001", 70000, 10, 15000);

    vector<string> tecnologias = {"Microservicios", "Docker", "AWS", "Kubernetes"};
    Arquitecto arch("Carlos López", "ARCH001", 80000, "Java", 8, tecnologias, 15);

    // Vector polimórfico
    vector<Empleado *> empleados = {&dev, &mgr, &arch};

    // Procesar todos los empleados (polimorfismo)
    procesarEmpleados(empleados);

    // Usar métodos específicos
    cout << "\n=== ACCIONES ESPECÍFICAS ===" << endl;
    dev.programar();
    mgr.gestionar();
    arch.disenharArquitectura();

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;
    cout << "Los destructores se llamarán en orden inverso..." << endl;

    return 0;
}