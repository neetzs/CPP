#include <iostream>
#include <string>
using namespace std;

class Empleado
{
private:
    string nombre;
    string puesto;
    double salario;
    int idEmpleado;
    static int contadorEmpleados;

public:
    // Constructor
    Empleado(string n, string p, double s)
        : nombre(n), puesto(p), salario(s)
    {
        idEmpleado = ++contadorEmpleados;
        cout << "Empleado creado: " << nombre << " (ID: " << idEmpleado << ")" << endl;
    }

    // Destructor
    ~Empleado()
    {
        cout << "Empleado destruido: " << nombre << endl;
    }

    // Getters - acceso controlado a datos privados
    string obtenerNombre() const
    {
        return nombre;
    }

    string obtenerPuesto() const
    {
        return puesto;
    }

    double obtenerSalario() const
    {
        return salario;
    }

    int obtenerId() const
    {
        return idEmpleado;
    }

    // Setters - modificación controlada
    void cambiarPuesto(string nuevoPuesto)
    {
        if (!nuevoPuesto.empty())
        {
            cout << nombre << " cambió de puesto: " << puesto << " -> " << nuevoPuesto << endl;
            puesto = nuevoPuesto;
        }
    }

    void aumentarSalario(double porcentaje)
    {
        if (porcentaje > 0 && porcentaje <= 50)
        { // Máximo 50%
            double aumento = salario * porcentaje / 100;
            salario += aumento;
            cout << nombre << " recibió aumento de $" << aumento
                 << " (" << porcentaje << "%)" << endl;
        }
        else
        {
            cout << "Porcentaje de aumento inválido" << endl;
        }
    }

    // Método público que usa datos privados
    void mostrarInformacion() const
    {
        cout << "\n--- Información del Empleado ---" << endl;
        cout << "ID: " << idEmpleado << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Puesto: " << puesto << endl;
        cout << "Salario: $" << salario << endl;
    }

    // Método estático
    static int obtenerTotalEmpleados()
    {
        return contadorEmpleados;
    }
};

// Inicializar contador estático
int Empleado::contadorEmpleados = 0;

class SistemaSeguridad
{
private:
    string contrasenaMaestra;
    bool sistemaActivado;

public:
    SistemaSeguridad(string contrasena)
        : contrasenaMaestra(contrasena), sistemaActivado(false) {}

    // Método público que valida acceso
    bool activarSistema(string contrasena)
    {
        if (verificarContrasena(contrasena))
        {
            sistemaActivado = true;
            cout << "Sistema de seguridad activado" << endl;
            return true;
        }
        else
        {
            cout << "Contraseña incorrecta - acceso denegado" << endl;
            return false;
        }
    }

    void desactivarSistema()
    {
        sistemaActivado = false;
        cout << "Sistema de seguridad desactivado" << endl;
    }

    bool estaActivado() const
    {
        return sistemaActivado;
    }

private:
    // Método privado - detalle de implementación
    bool verificarContrasena(string contrasena) const
    {
        return contrasena == contrasenaMaestra;
    }
};

class Tienda
{
private:
    string nombre;
    double ingresos;
    bool abierta;

    // Método privado auxiliar
    void registrarTransaccion(double monto)
    {
        ingresos += monto;
        cout << "Transacción registrada: $" << monto << endl;
    }

public:
    Tienda(string n) : nombre(n), ingresos(0.0), abierta(false) {}

    void abrirTienda()
    {
        abierta = true;
        cout << nombre << " está ahora abierta" << endl;
    }

    void cerrarTienda()
    {
        abierta = false;
        cout << nombre << " está ahora cerrada" << endl;
    }

    bool venderProducto(string producto, double precio)
    {
        if (!abierta)
        {
            cout << "La tienda está cerrada" << endl;
            return false;
        }

        if (precio <= 0)
        {
            cout << "Precio inválido" << endl;
            return false;
        }

        registrarTransaccion(precio); // Usa método privado
        cout << "Vendido: " << producto << " por $" << precio << endl;
        return true;
    }

    void mostrarEstado() const
    {
        cout << "\n--- Estado de " << nombre << " ---" << endl;
        cout << "Estado: " << (abierta ? "Abierta" : "Cerrada") << endl;
        cout << "Ingresos totales: $" << ingresos << endl;
    }
};

int main()
{
    cout << "=== SISTEMA DE EMPLEADOS ===" << endl;

    Empleado emp1("Juan Pérez", "Desarrollador", 50000);
    Empleado emp2("María García", "Diseñadora", 45000);

    emp1.mostrarInformacion();
    emp2.mostrarInformacion();

    emp1.aumentarSalario(10); // 10% de aumento
    emp1.cambiarPuesto("Senior Developer");

    cout << "\nTotal de empleados: " << Empleado::obtenerTotalEmpleados() << endl;

    cout << "\n=== SISTEMA DE SEGURIDAD ===" << endl;

    SistemaSeguridad seguridad("admin123");

    seguridad.activarSistema("wrong");    // Fallará
    seguridad.activarSistema("admin123"); // Correcto

    cout << "Sistema activado: " << (seguridad.estaActivado() ? "Sí" : "No") << endl;

    cout << "\n=== TIENDA ===" << endl;

    Tienda tienda("Mi Tienda");
    tienda.abrirTienda();

    tienda.venderProducto("Laptop", 1200);
    tienda.venderProducto("Mouse", 25);
    tienda.venderProducto("Teclado", 75);

    tienda.mostrarEstado();

    tienda.cerrarTienda();
    tienda.venderProducto("Monitor", 300); // Debería fallar

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;
}