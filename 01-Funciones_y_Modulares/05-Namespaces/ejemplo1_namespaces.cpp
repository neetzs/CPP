#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Namespace para utilidades matemáticas
namespace matematicas
{
    const double PI = 3.14159;

    double areaCirculo(double radio)
    {
        return PI * radio * radio;
    }

    double perimetroCirculo(double radio)
    {
        return 2 * PI * radio;
    }
}

// Namespace para utilidades de texto
namespace texto
{
    void imprimirLinea(string mensaje)
    {
        cout << mensaje << endl;
    }

    string convertirMayusculas(string texto)
    {
        // Implementación simplificada
        for (char &c : texto)
        {
            c = toupper(c);
        }
        return texto;
    }
}

// Namespace anidado
namespace graficos
{
    namespace formas
    {
        void dibujarCuadrado()
        {
            cout << "Dibujando cuadrado..." << endl;
        }
    }

    namespace colores
    {
        string ROJO = "#FF0000";
        string AZUL = "#0000FF";
    }
}

int main()
{
    // Usando namespace específico
    cout << "Área del círculo: " << matematicas::areaCirculo(5) << endl;
    cout << "Perímetro del círculo: " << matematicas::perimetroCirculo(5) << endl;

    // Usando using namespace
    using namespace texto;
    imprimirLinea("Hola mundo");
    cout << convertirMayusculas("hola") << endl;

    // Namespace anidado
    graficos::formas::dibujarCuadrado();
    cout << "Color rojo: " << graficos::colores::ROJO << endl;
}