#include <iostream>
#include <string>

using namespace std;

// ==========================================
// EJEMPLO: Constantes
// ==========================================

int main()
{
    // Variables (pueden cambiar)
    int numero = 10;
    numero = 20; // Permitido

    // Constantes (NO pueden cambiar)
    const double PI = 3.14159;
    const string INSTITUCION = "UTN FRBA";
    const int ANIO_ACTUAL = 2026;

    // PI = 3.14;  // ERROR: No se puede modificar una constante

    cout << "PI: " << PI << endl;
    cout << "Institución: " << INSTITUCION << endl;
    cout << "Año actual: " << ANIO_ACTUAL << endl;

    // Calcular área de un círculo
    double radio = 5.0;
    double area = PI * radio * radio;
    cout << "Área de círculo con radio 5: " << area << endl;
}

// VENTAJAS DE USAR const:
// 1. Evita cambios accidentales
// 2. Código más seguro
// 3. El compilador puede hacer optimizaciones
// 4. Comunica intención: "esto no cambia"
// Una buena práctica es usar mayúsculas para constantes, aunque no es obligatorio.