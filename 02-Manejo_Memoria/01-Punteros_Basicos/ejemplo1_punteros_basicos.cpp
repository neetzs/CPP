#include <iostream>
using namespace std;

int main()
{
    // Variables normales
    int numero = 42;
    double decimal = 3.14;
    char letra = 'A';

    // Punteros
    int *ptrNumero = &numero;
    double *ptrDecimal = &decimal;
    char *ptrLetra = &letra;

    cout << "=== VALORES ===" << endl;
    cout << "numero: " << numero << endl;
    cout << "decimal: " << decimal << endl;
    cout << "letra: " << letra << endl;

    cout << "\n=== DIRECCIONES ===" << endl;
    cout << "&numero: " << &numero << endl;
    cout << "&decimal: " << &decimal << endl;
    cout << "&letra: " << &letra << endl;

    cout << "\n=== PUNTEROS ===" << endl;
    cout << "ptrNumero: " << ptrNumero << endl;
    cout << "ptrDecimal: " << ptrDecimal << endl;
    cout << "ptrLetra: " << ptrLetra << endl;

    cout << "\n=== DESREFERENCIA ===" << endl;
    cout << "*ptrNumero: " << *ptrNumero << endl;
    cout << "*ptrDecimal: " << *ptrDecimal << endl;
    cout << "*ptrLetra: " << *ptrLetra << endl;

    cout << "\n=== MODIFICACIÓN A TRAVÉS DE PUNTEROS ===" << endl;
    *ptrNumero = 100;
    *ptrDecimal = 2.71;
    *ptrLetra = 'Z';

    cout << "Después de modificar:" << endl;
    cout << "numero: " << numero << endl;
    cout << "decimal: " << decimal << endl;
    cout << "letra: " << letra << endl;

}