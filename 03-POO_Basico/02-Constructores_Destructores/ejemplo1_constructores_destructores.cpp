#include <iostream>
#include <string>
using namespace std;

class Archivo
{
private:
    string nombre;
    bool abierto;

public:
    // Constructor por defecto
    Archivo()
    {
        nombre = "sin_nombre.txt";
        abierto = false;
        cout << "Archivo creado (defecto): " << nombre << endl;
    }

    // Constructor con parámetros
    Archivo(string n)
    {
        nombre = n;
        abierto = false;
        cout << "Archivo creado: " << nombre << endl;
    }

    // Constructor de copia
    Archivo(const Archivo &otro)
    {
        nombre = otro.nombre + "_copia";
        abierto = false;
        cout << "Archivo copiado: " << nombre << endl;
    }

    // Destructor
    ~Archivo()
    {
        if (abierto)
        {
            cerrar();
        }
        cout << "Archivo destruido: " << nombre << endl;
    }

    void abrir()
    {
        if (!abierto)
        {
            abierto = true;
            cout << "Abriendo archivo: " << nombre << endl;
        }
    }

    void cerrar()
    {
        if (abierto)
        {
            abierto = false;
            cout << "Cerrando archivo: " << nombre << endl;
        }
    }

    void escribir(string texto)
    {
        if (abierto)
        {
            cout << "Escribiendo en " << nombre << ": " << texto << endl;
        }
        else
        {
            cout << "Error: archivo no abierto" << endl;
        }
    }
};

class Contador
{
private:
    static int totalObjetos;
    int id;

public:
    // Constructor
    Contador()
    {
        totalObjetos++;
        id = totalObjetos;
        cout << "Objeto " << id << " creado. Total: " << totalObjetos << endl;
    }

    // Constructor de copia
    Contador(const Contador &otro)
    {
        totalObjetos++;
        id = totalObjetos;
        cout << "Objeto " << id << " creado por copia. Total: " << totalObjetos << endl;
    }

    // Destructor
    ~Contador()
    {
        totalObjetos--;
        cout << "Objeto " << id << " destruido. Total: " << totalObjetos << endl;
    }

    static int obtenerTotal()
    {
        return totalObjetos;
    }
};

// Inicializar variable estática
int Contador::totalObjetos = 0;

void funcionConObjetos()
{
    cout << "\n=== DENTRO DE FUNCIÓN ===" << endl;
    Contador c1;
    Contador c2;
    cout << "Total en función: " << Contador::obtenerTotal() << endl;
    cout << "=== SALIENDO DE FUNCIÓN ===" << endl;
}

int main()
{
    cout << "=== INICIO DEL PROGRAMA ===" << endl;

    // Constructor por defecto
    Archivo archivo1;
    archivo1.abrir();
    archivo1.escribir("Hola mundo");

    // Constructor con parámetros
    Archivo archivo2("datos.txt");
    archivo2.abrir();
    archivo2.escribir("Información importante");

    // Constructor de copia
    Archivo archivo3 = archivo2; // Copia
    archivo3.escribir("Copia de datos");

    cout << "\n=== CONTADOR DE OBJETOS ===" << endl;
    Contador contador1;
    {
        Contador contador2;
        Contador contador3;
        cout << "En el scope interno: " << Contador::obtenerTotal() << endl;
    }
    cout << "Después del scope interno: " << Contador::obtenerTotal() << endl;

    funcionConObjetos();

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;
    cout << "Los destructores se llamarán automáticamente..." << endl;
}