#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <type_traits>
using namespace std;

// 1. FUNCTION TEMPLATES
template <typename T>
T maximo(const T &a, const T &b)
{
    cout << "maximo<T> llamado con tipo: " << typeid(T).name() << endl;
    return (a > b) ? a : b;
}

// Sobrecarga para punteros
template <typename T>
T *maximo(T *a, T *b)
{
    cout << "maximo<T*> llamado con tipo: " << typeid(T).name() << endl;
    return (*a > *b) ? a : b;
}

// Template con múltiples parámetros
template <typename T, typename U>
bool sonIguales(const T &a, const U &b)
{
    cout << "sonIguales<T, U> llamado con tipos: " << typeid(T).name()
         << " y " << typeid(U).name() << endl;
    return static_cast<double>(a) == static_cast<double>(b);
}

// Template con parámetro no-tipo
template <typename T, int TAMANIO>
class ArregloFijo
{
private:
    T datos[TAMANIO];

public:
    ArregloFijo()
    {
        cout << "ArregloFijo<" << typeid(T).name() << ", " << TAMANIO << "> creado" << endl;
        for (int i = 0; i < TAMANIO; i++)
        {
            datos[i] = T(); // Valor por defecto
        }
    }

    T &operator[](int indice)
    {
        if (indice < 0 || indice >= TAMANIO)
        {
            throw out_of_range("Índice fuera de rango");
        }
        return datos[indice];
    }

    int obtenerTamanio() const { return TAMANIO; }
};

// 2. CLASS TEMPLATES
template <typename T>
class Pila
{
private:
    vector<T> elementos;

public:
    Pila()
    {
        cout << "Pila<" << typeid(T).name() << "> creada" << endl;
    }

    void push(const T &elemento)
    {
        elementos.push_back(elemento);
        cout << "Elemento agregado a Pila<" << typeid(T).name() << ">" << endl;
    }

    T pop()
    {
        if (elementos.empty())
        {
            throw runtime_error("Pila vacía");
        }
        T elemento = elementos.back();
        elementos.pop_back();
        return elemento;
    }

    bool estaVacia() const
    {
        return elementos.empty();
    }

    size_t tamanio() const
    {
        return elementos.size();
    }
};

// Template con especialización parcial
template <typename T>
class Contenedor
{
private:
    T *dato;

public:
    Contenedor(T val) : dato(new T(val))
    {
        cout << "Contenedor<T> creado con valor" << endl;
    }

    ~Contenedor()
    {
        delete dato;
        cout << "Contenedor<T> destruido" << endl;
    }

    T obtener() const { return *dato; }
    void establecer(T val) { *dato = val; }
};

// Especialización para punteros
template <typename T>
class Contenedor<T *>
{
private:
    T *dato;

public:
    Contenedor(T *val) : dato(val)
    {
        cout << "Contenedor<T*> creado con puntero" << endl;
    }

    ~Contenedor()
    {
        // No eliminamos el puntero, solo lo contenemos
        cout << "Contenedor<T*> destruido (puntero no eliminado)" << endl;
    }

    T *obtener() const { return dato; }
};

// Especialización completa para char*
template <>
class Contenedor<char *>
{
private:
    string dato;

public:
    Contenedor(char *val) : dato(val ? val : "")
    {
        cout << "Contenedor<char*> especializado creado" << endl;
    }

    ~Contenedor()
    {
        cout << "Contenedor<char*> especializado destruido" << endl;
    }

    const char *obtener() const { return dato.c_str(); }
    void establecer(const char *val) { dato = val ? val : ""; }
};

// 3. TEMPLATES AVANZADOS

// Template con variadic arguments (C++11)
template <typename... Tipos>
class Tupla
{
private:
    tuple<Tipos...> datos;

public:
    Tupla(Tipos... args) : datos(args...)
    {
        cout << "Tupla creada con " << sizeof...(Tipos) << " tipos" << endl;
    }

    template <size_t Indice>
    auto obtener() const
    {
        return get<Indice>(datos);
    }
};

// Template metaprogramming - Factorial en tiempo de compilación
template <int N>
struct Factorial
{
    static const int valor = N * Factorial<N - 1>::valor;
};

template <>
struct Factorial<0>
{
    static const int valor = 1;
};

// Template para determinar si un tipo es un puntero
template <typename T>
struct EsPuntero
{
    static const bool valor = false;
};

template <typename T>
struct EsPuntero<T *>
{
    static const bool valor = true;
};

// Función template con SFINAE (Substitution Failure is Not An Error)
template <typename T>
typename enable_if<is_arithmetic<T>::value, T>::type
cuadrado(T x)
{
    cout << "Cuadrado de tipo aritmético: " << typeid(T).name() << endl;
    return x * x;
}

template <typename T>
typename enable_if<!is_arithmetic<T>::value, string>::type
cuadrado(T x)
{
    cout << "Cuadrado de tipo no aritmético: " << typeid(T).name() << endl;
    return "Operación no soportada";
}

// 4. DEMOSTRACIÓN DE USO
void demostrarFunctionTemplates()
{
    cout << "\n=== FUNCTION TEMPLATES ===" << endl;

    // Deducción automática de tipos
    cout << "maximo(5, 3) = " << maximo(5, 3) << endl;
    cout << "maximo(5.5, 3.2) = " << maximo(5.5, 3.2) << endl;
    cout << "maximo('a', 'z') = " << maximo('a', 'z') << endl;

    // Instanciación explícita
    cout << "maximo<string>(\"Hola\", \"Mundo\") = " << maximo<string>("Hola", "Mundo") << endl;

    // Punteros
    int a = 10, b = 20;
    int *ptr_max = maximo(&a, &b);
    cout << "*maximo(&a, &b) = " << *ptr_max << endl;

    // Múltiples parámetros de template
    cout << "sonIguales(5, 5.0) = " << (sonIguales(5, 5.0) ? "true" : "false") << endl;
    cout << "sonIguales(5, 3.14) = " << (sonIguales(5, 3.14) ? "true" : "false") << endl;
}

void demostrarClassTemplates()
{
    cout << "\n=== CLASS TEMPLATES ===" << endl;

    // Arreglo fijo con parámetro no-tipo
    ArregloFijo<int, 5> arr_int;
    arr_int[0] = 10;
    arr_int[1] = 20;
    cout << "arr_int[0] = " << arr_int[0] << endl;

    ArregloFijo<double, 3> arr_double;
    arr_double[0] = 3.14;
    cout << "arr_double[0] = " << arr_double[0] << endl;

    // Pila genérica
    Pila<int> pila_int;
    pila_int.push(1);
    pila_int.push(2);
    pila_int.push(3);
    cout << "Elemento desapilado: " << pila_int.pop() << endl;
    cout << "Tamaño de la pila: " << pila_int.tamanio() << endl;

    Pila<string> pila_str;
    pila_str.push("Hola");
    pila_str.push("Mundo");
    cout << "Elemento desapilado: " << pila_str.pop() << endl;
}

void demostrarEspecializaciones()
{
    cout << "\n=== ESPECIALIZACIONES ===" << endl;

    // Contenedor normal
    Contenedor<int> cont_int(42);
    cout << "cont_int.obtener() = " << cont_int.obtener() << endl;

    // Contenedor de puntero
    int *ptr = new int(100);
    Contenedor<int *> cont_ptr(ptr);
    cout << "*cont_ptr.obtener() = " << *cont_ptr.obtener() << endl;
    delete ptr; // Liberar memoria

    // Contenedor especializado para char*
    Contenedor<char *> cont_char("Hola mundo");
    cout << "cont_char.obtener() = " << cont_char.obtener() << endl;
}

void demostrarTemplatesAvanzados()
{
    cout << "\n=== TEMPLATES AVANZADOS ===" << endl;

    // Variadic templates
    Tupla<int, double, string> tupla(42, 3.14, "Hola");
    cout << "tupla.obtener<0>() = " << tupla.obtener<0>() << endl;
    cout << "tupla.obtener<1>() = " << tupla.obtener<1>() << endl;
    cout << "tupla.obtener<2>() = " << tupla.obtener<2>() << endl;

    // Metaprogramming - Factorial en tiempo de compilación
    cout << "Factorial<5>::valor = " << Factorial<5>::valor << endl;
    cout << "Factorial<0>::valor = " << Factorial<0>::valor << endl;

    // Traits
    cout << "EsPuntero<int>::valor = " << (EsPuntero<int>::valor ? "true" : "false") << endl;
    cout << "EsPuntero<int*>::valor = " << (EsPuntero<int *>::valor ? "true" : "false") << endl;

    // SFINAE
    cout << "cuadrado(5) = " << cuadrado(5) << endl;
    cout << "cuadrado(3.14) = " << cuadrado(3.14) << endl;
    cout << "cuadrado(string(\"test\")) = " << cuadrado(string("test")) << endl;
}

int main()
{
    cout << "=== TEMPLATES EN C++ ===" << endl;

    demostrarFunctionTemplates();
    demostrarClassTemplates();
    demostrarEspecializaciones();
    demostrarTemplatesAvanzados();

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;

    return 0;
}