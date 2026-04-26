#include <iostream>
using namespace std;

// Por valor - no modifica original
void incrementarValor(int num)
{
    num++;
    cout << "Dentro de la función (valor): " << num << endl;
}

// Por referencia - modifica original
void incrementarReferencia(int &num)
{
    num++;
    cout << "Dentro de la función (referencia): " << num << endl;
}

// Por puntero - modifica original
void incrementarPuntero(int *num)
{
    (*num)++;
    cout << "Dentro de la función (puntero): " << *num << endl;
}

int main()
{
    int valor = 5;

    cout << "Valor original: " << valor << endl;

    incrementarValor(valor);
    cout << "Después de función por valor: " << valor << endl;

    incrementarReferencia(valor);
    cout << "Después de función por referencia: " << valor << endl;

    incrementarPuntero(&valor);
    cout << "Después de función por puntero: " << valor << endl;
}