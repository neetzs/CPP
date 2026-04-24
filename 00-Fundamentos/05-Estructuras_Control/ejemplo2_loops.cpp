#include <iostream>

using namespace std;

// ==========================================
// EJEMPLO: Loops - for, while
// ==========================================

int main()
{
    cout << "=== LOOP FOR: Contar del 1 al 10 ===" << endl;
    for (int i = 1; i <= 10; i++)
    {
        cout << i << " ";
    }
    cout << endl;

    cout << "\n=== LOOP FOR: Tabla de multiplicar del 5 ===" << endl;
    for (int i = 1; i <= 10; i++)
    {
        cout << "5 x " << i << " = " << (5 * i) << endl;
    }

    cout << "\n=== LOOP WHILE: Contar mientras ===" << endl;
    int contador = 1;
    while (contador <= 5)
    {
        cout << "Contador: " << contador << endl;
        contador++;
    }

    cout << "\n=== LOOP DO-WHILE: Menú ===" << endl;
    int opcion;
    do
    {
        cout << "\n1. Opción 1" << endl;
        cout << "2. Opción 2" << endl;
        cout << "3. Salir" << endl;
        cout << "Elige una opción: ";
        cin >> opcion;

        if (opcion == 1)
        {
            cout << "Elegiste opción 1" << endl;
        }
        else if (opcion == 2)
        {
            cout << "Elegiste opción 2" << endl;
        }
    } while (opcion != 3);

    cout << "\nHasta luego!" << endl;

    return 0;
}

// NOTAS:
// - for: Ideal cuando sabes cuántas veces iterar
// - while: Ideal cuando no sabes cuántas veces
// - do-while: Se ejecuta al menos una vez
