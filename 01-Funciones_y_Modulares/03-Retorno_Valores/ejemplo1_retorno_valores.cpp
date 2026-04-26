#include <iostream>
#include <tuple>
using namespace std;

// Retorno simple
int calcularCuadrado(int num)
{
    return num * num;
}

// Retorno múltiple con tuple
tuple<int, int> dividirYResto(int dividendo, int divisor)
{
    int cociente = dividendo / divisor;
    int resto = dividendo % divisor;
    return make_tuple(cociente, resto);
}

// Retorno por referencia (cuidado: puede ser peligroso)
int &obtenerElemento(int arr[], int indice)
{
    return arr[indice];
}

int main()
{
    // Retorno simple
    int numero = 5;
    int cuadrado = calcularCuadrado(numero);
    cout << numero << " al cuadrado es: " << cuadrado << endl;

    // Retorno múltiple
    auto [cociente, resto] = dividirYResto(17, 5);
    cout << "17 dividido por 5: cociente=" << cociente << ", resto=" << resto << endl;

    // Retorno por referencia
    int arreglo[] = {10, 20, 30};
    obtenerElemento(arreglo, 1) = 25; // Modifica el arreglo
    cout << "Arreglo modificado: " << arreglo[0] << ", " << arreglo[1] << ", " << arreglo[2] << endl;
}