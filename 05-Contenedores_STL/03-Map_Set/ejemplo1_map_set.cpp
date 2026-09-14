#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

void mostrarMap(const map<string, int> &m, const string &nombre)
{
    cout << nombre << " (tamaño: " << m.size() << "):" << endl;
    for (const auto &par : m)
    {
        cout << "  " << par.first << " -> " << par.second << endl;
    }
}

void mostrarSet(const set<int> &s, const string &nombre)
{
    cout << nombre << " (tamaño: " << s.size() << "): ";
    for (int elemento : s)
    {
        cout << elemento << " ";
    }
    cout << endl;
}

int main()
{
    cout << "=== MAP Y SET EN C++ ===" << endl;

    // 1. Creación y operaciones básicas con Map
    cout << "\n--- MAP ---" << endl;

    map<string, int> edades;           // Map vacío
    map<string, int> calificaciones = {// Inicialización con lista
                                       {"Juan", 85},
                                       {"María", 92},
                                       {"Pedro", 78}};

    mostrarMap(edades, "edades (vacío)");
    mostrarMap(calificaciones, "calificaciones");

    // Insertar elementos
    edades["Ana"] = 28;
    edades["Carlos"] = 35;
    edades.insert({"Beatriz", 42});
    edades.insert(make_pair("David", 31));

    mostrarMap(edades, "edades después de inserciones");

    // Acceder a elementos
    cout << "Edad de Ana: " << edades["Ana"] << endl;
    cout << "Edad de Carlos (at): " << edades.at("Carlos") << endl;

    // Modificar valores
    edades["Ana"] = 29; // Modificar existente
    mostrarMap(edades, "edades después de modificar Ana");

    // Verificar existencia
    string nombre_buscar = "Elena";
    if (edades.find(nombre_buscar) != edades.end())
    {
        cout << nombre_buscar << " encontrado con edad: " << edades[nombre_buscar] << endl;
    }
    else
    {
        cout << nombre_buscar << " no encontrado" << endl;
    }

    // 2. Creación y operaciones básicas con Set
    cout << "\n--- SET ---" << endl;

    set<int> numeros;                            // Set vacío
    set<int> primos = {2, 3, 5, 7, 11};          // Inicialización con lista
    set<int> duplicados = {1, 2, 2, 3, 3, 3, 4}; // Duplicados se eliminan

    mostrarSet(numeros, "numeros (vacío)");
    mostrarSet(primos, "primos");
    mostrarSet(duplicados, "duplicados (sin duplicados)");

    // Insertar elementos
    numeros.insert(10);
    numeros.insert(20);
    numeros.insert(15);
    numeros.insert(10); // Duplicado - será ignorado

    mostrarSet(numeros, "numeros después de inserciones");

    // Buscar elementos
    int buscar = 15;
    if (numeros.count(buscar))
    {
        cout << buscar << " encontrado en el set" << endl;
    }
    else
    {
        cout << buscar << " no encontrado en el set" << endl;
    }

    // Eliminar elementos
    numeros.erase(20);
    mostrarSet(numeros, "numeros después de erase(20)");

    // 3. Operaciones avanzadas con Map
    cout << "\n--- OPERACIONES AVANZADAS CON MAP ---" << endl;

    map<string, int> inventario = {
        {"manzanas", 50},
        {"peras", 30},
        {"platanos", 20}};

    mostrarMap(inventario, "inventario inicial");

    // Usar operator[] para acceder/modificar (crea entrada si no existe)
    cout << "Accediendo a 'uvas' (no existe): " << inventario["uvas"] << endl;
    mostrarMap(inventario, "inventario después de acceder 'uvas'");

    // Usar insert con verificación
    auto resultado = inventario.insert({"manzanas", 100}); // Intento insertar clave existente
    if (!resultado.second)
    {
        cout << "La clave 'manzanas' ya existe con valor: " << resultado.first->second << endl;
    }

    // Modificar valor existente
    inventario["manzanas"] = 75;
    mostrarMap(inventario, "inventario después de modificar manzanas");

    // Iterar en orden inverso
    cout << "Inventario en orden inverso:" << endl;
    for (auto it = inventario.rbegin(); it != inventario.rend(); ++it)
    {
        cout << "  " << it->first << " -> " << it->second << endl;
    }

    // Encontrar elementos en rango
    cout << "Elementos con clave >= 'm':" << endl;
    auto it = inventario.lower_bound("m");
    for (; it != inventario.end(); ++it)
    {
        cout << "  " << it->first << " -> " << it->second << endl;
    }

    // 4. Operaciones avanzadas con Set
    cout << "\n--- OPERACIONES AVANZADAS CON SET ---" << endl;

    set<int> conjunto1 = {1, 3, 5, 7, 9};
    set<int> conjunto2 = {2, 3, 5, 7, 11};

    mostrarSet(conjunto1, "conjunto1");
    mostrarSet(conjunto2, "conjunto2");

    // Operaciones de conjunto
    set<int> interseccion;
    set_intersection(conjunto1.begin(), conjunto1.end(),
                     conjunto2.begin(), conjunto2.end(),
                     inserter(interseccion, interseccion.begin()));
    mostrarSet(interseccion, "intersección");

    set<int> union_set;
    set_union(conjunto1.begin(), conjunto1.end(),
              conjunto2.begin(), conjunto2.end(),
              inserter(union_set, union_set.begin()));
    mostrarSet(union_set, "unión");

    set<int> diferencia;
    set_difference(conjunto1.begin(), conjunto1.end(),
                   conjunto2.begin(), conjunto2.end(),
                   inserter(diferencia, diferencia.begin()));
    mostrarSet(diferencia, "diferencia (conjunto1 - conjunto2)");

    // 5. Map con tipos personalizados
    cout << "\n--- MAP CON TIPOS PERSONALIZADOS ---" << endl;

    struct Persona
    {
        string nombre;
        int edad;

        // Constructor
        Persona(string n = "", int e = 0) : nombre(n), edad(e) {}

        // Operador < para usar como clave en map
        bool operator<(const Persona &otra) const
        {
            return nombre < otra.nombre;
        }
    };

    map<Persona, string> personas_departamentos;
    personas_departamentos[{"Juan", 25}] = "Desarrollo";
    personas_departamentos[{"María", 30}] = "Diseño";
    personas_departamentos[{"Pedro", 35}] = "Gerencia";

    cout << "Personas y departamentos:" << endl;
    for (const auto &par : personas_departamentos)
    {
        cout << "  " << par.first.nombre << " (" << par.first.edad << " años) -> "
             << par.second << endl;
    }

    // 6. Set con tipos personalizados
    cout << "\n--- SET CON TIPOS PERSONALIZADOS ---" << endl;

    set<Persona> empleados;
    empleados.insert({"Ana", 28});
    empleados.insert({"Carlos", 32});
    empleados.insert({"Ana", 28}); // Duplicado - será ignorado

    cout << "Empleados únicos:" << endl;
    for (const auto &emp : empleados)
    {
        cout << "  " << emp.nombre << " (" << emp.edad << " años)" << endl;
    }

    // 7. Multimap (permite claves duplicadas)
    cout << "\n--- MULTIMAP ---" << endl;

    multimap<string, string> telefonos;
    telefonos.insert({"Juan", "555-0101"});
    telefonos.insert({"María", "555-0202"});
    telefonos.insert({"Juan", "555-0102"}); // Juan tiene dos teléfonos

    cout << "Teléfonos:" << endl;
    for (const auto &tel : telefonos)
    {
        cout << "  " << tel.first << ": " << tel.second << endl;
    }

    // Buscar todos los teléfonos de Juan
    cout << "Teléfonos de Juan:" << endl;
    auto rango = telefonos.equal_range("Juan");
    for (auto it = rango.first; it != rango.second; ++it)
    {
        cout << "  " << it->second << endl;
    }

    // 8. Multiset (permite elementos duplicados)
    cout << "\n--- MULTISET ---" << endl;

    multiset<int> multi_nums = {1, 2, 2, 3, 3, 3, 4};
    cout << "Multiset: ";
    for (int num : multi_nums)
    {
        cout << num << " ";
    }
    cout << endl;

    cout << "Número de veces que aparece 3: " << multi_nums.count(3) << endl;

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;

    return 0;
}