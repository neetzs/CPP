#include <iostream>
#include <list>
#include <deque>
#include <algorithm>
#include <iterator>
using namespace std;

template <typename T>
void mostrarContenedor(const T &cont, const string &nombre)
{
    cout << nombre << " (tamaño: " << cont.size() << "): ";
    for (const auto &elemento : cont)
    {
        cout << elemento << " ";
    }
    cout << endl;
}

int main()
{
    cout << "=== LIST Y DEQUE EN C++ ===" << endl;

    // 1. Creación y operaciones básicas con List
    cout << "\n--- LIST ---" << endl;

    list<int> lst1;                   // Lista vacía
    list<int> lst2(3, 100);           // 3 elementos con valor 100
    list<int> lst3 = {1, 2, 3, 4, 5}; // Inicialización con lista

    mostrarContenedor(lst1, "lst1 (vacía)");
    mostrarContenedor(lst2, "lst2 (3 elementos)");
    mostrarContenedor(lst3, "lst3 (lista)");

    // Operaciones de lista
    lst1.push_back(10);
    lst1.push_back(20);
    lst1.push_front(5);
    mostrarContenedor(lst1, "lst1 después de push_back/front");

    lst1.pop_back();
    lst1.pop_front();
    mostrarContenedor(lst1, "lst1 después de pop_back/front");

    // Insertar en posiciones específicas
    auto it = lst3.begin();
    advance(it, 2); // Avanzar 2 posiciones
    lst3.insert(it, 99);
    mostrarContenedor(lst3, "lst3 después de insert(99) en posición 2");

    // Eliminar elementos específicos
    lst3.remove(99); // Eliminar todas las ocurrencias de 99
    mostrarContenedor(lst3, "lst3 después de remove(99)");

    // 2. Creación y operaciones básicas con Deque
    cout << "\n--- DEQUE ---" << endl;

    deque<int> dq1;                    // Deque vacío
    deque<int> dq2(4, 50);             // 4 elementos con valor 50
    deque<int> dq3 = {10, 20, 30, 40}; // Inicialización con lista

    mostrarContenedor(dq1, "dq1 (vacío)");
    mostrarContenedor(dq2, "dq2 (4 elementos)");
    mostrarContenedor(dq3, "dq3 (lista)");

    // Operaciones de deque
    dq1.push_back(100);
    dq1.push_front(200);
    dq1.push_back(300);
    mostrarContenedor(dq1, "dq1 después de operaciones");

    cout << "Frente: " << dq1.front() << ", Atrás: " << dq1.back() << endl;

    dq1.pop_front();
    dq1.pop_back();
    mostrarContenedor(dq1, "dq1 después de pop_front/back");

    // Acceso aleatorio (único en deque entre list y deque)
    dq3[0] = 999;
    dq3.at(2) = 888;
    mostrarContenedor(dq3, "dq3 después de acceso aleatorio");

    // 3. Operaciones avanzadas con List
    cout << "\n--- OPERACIONES AVANZADAS CON LIST ---" << endl;

    list<int> lst4 = {1, 2, 3, 4, 5};
    list<int> lst5 = {10, 20, 30};

    // Fusionar listas ordenadas
    list<int> lst6 = {1, 3, 5, 7};
    list<int> lst7 = {2, 4, 6, 8};
    lst6.merge(lst7); // Fusiona lst7 en lst6 (ambas deben estar ordenadas)
    mostrarContenedor(lst6, "lst6 después de merge con lst7");
    mostrarContenedor(lst7, "lst7 después de merge (vacía)");

    // Ordenar lista
    list<int> lst8 = {64, 12, 89, 23, 45};
    mostrarContenedor(lst8, "lst8 desordenada");
    lst8.sort();
    mostrarContenedor(lst8, "lst8 ordenada");

    // Eliminar duplicados
    list<int> lst9 = {1, 2, 2, 3, 3, 3, 4, 5, 5};
    mostrarContenedor(lst9, "lst9 con duplicados");
    lst9.unique();
    mostrarContenedor(lst9, "lst9 sin duplicados");

    // Invertir lista
    list<int> lst10 = {1, 2, 3, 4, 5};
    mostrarContenedor(lst10, "lst10 original");
    lst10.reverse();
    mostrarContenedor(lst10, "lst10 invertida");

    // 4. Operaciones avanzadas con Deque
    cout << "\n--- OPERACIONES AVANZADAS CON DEQUE ---" << endl;

    deque<int> dq4 = {1, 2, 3, 4, 5};

    // Insertar en posiciones específicas
    dq4.insert(dq4.begin() + 2, 99);
    mostrarContenedor(dq4, "dq4 después de insert en posición 2");

    // Eliminar rango
    dq4.erase(dq4.begin() + 1, dq4.begin() + 4);
    mostrarContenedor(dq4, "dq4 después de erase rango [1,4)");

    // 5. Comparación de rendimiento conceptual
    cout << "\n--- COMPARACIÓN DE RENDIMIENTO ---" << endl;

    cout << "Vector: Bueno para acceso aleatorio, inserciones al final" << endl;
    cout << "List: Bueno para inserciones/eliminaciones frecuentes en cualquier posición" << endl;
    cout << "Deque: Bueno para acceso aleatorio y operaciones en ambos extremos" << endl;

    // 6. Uso de iteradores
    cout << "\n--- USO DE ITERADORES ---" << endl;

    list<int> lst_iter = {10, 20, 30, 40, 50};

    // Iterador normal
    cout << "Iterador normal: ";
    for (auto it = lst_iter.begin(); it != lst_iter.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    // Iterador inverso
    cout << "Iterador inverso: ";
    for (auto it = lst_iter.rbegin(); it != lst_iter.rend(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    // 7. Algoritmos STL con list y deque
    cout << "\n--- ALGORITMOS STL ---" << endl;

    list<int> lst_algo = {5, 2, 8, 1, 9, 3};
    deque<int> dq_algo = {15, 12, 18, 11, 19, 13};

    mostrarContenedor(lst_algo, "lst_algo original");
    mostrarContenedor(dq_algo, "dq_algo original");

    // Ordenar
    lst_algo.sort();
    sort(dq_algo.begin(), dq_algo.end());

    mostrarContenedor(lst_algo, "lst_algo ordenada");
    mostrarContenedor(dq_algo, "dq_algo ordenada");

    // Buscar elementos
    auto it_lst = find(lst_algo.begin(), lst_algo.end(), 8);
    auto it_dq = find(dq_algo.begin(), dq_algo.end(), 18);

    if (it_lst != lst_algo.end())
    {
        cout << "8 encontrado en list en posición: "
             << distance(lst_algo.begin(), it_lst) << endl;
    }
    if (it_dq != dq_algo.end())
    {
        cout << "18 encontrado en deque en posición: "
             << (it_dq - dq_algo.begin()) << endl;
    }

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;

    return 0;
}