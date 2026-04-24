#include <iostream>

using namespace std;

// ==========================================
// EJEMPLO 2: Múltiples Salidas
// ==========================================

int main()
{
    cout << "Línea 1" << endl;
    cout << "Línea 2" << endl;
    cout << "Línea 3" << endl;

    // También puedes hacerlo así:
    cout << "A" << endl
         << "B" << endl
         << "C" << endl;

    // O sin saltos de línea:
    cout << "Sin " << "saltos " << "de línea";
    cout << endl;

    return 0;
}

// TIPS:
// - endl: Salta de línea y limpia el buffer
// - \n: Salta de línea (más rápido que endl)
// - Puedes encadenar múltiples << en una línea
