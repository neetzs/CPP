#include <iostream>
#include <memory>
using namespace std;

class Objeto
{
public:
    string nombre;
    Objeto(string n) : nombre(n)
    {
        cout << "Creando " << nombre << endl;
    }
    ~Objeto()
    {
        cout << "Destruyendo " << nombre << endl;
    }
    void saludar()
    {
        cout << "Hola, soy " << nombre << endl;
    }
};

void funcionConUniquePtr(unique_ptr<Objeto> obj)
{
    obj->saludar();
    // obj se libera automáticamente al salir
}

void funcionConSharedPtr(shared_ptr<Objeto> obj)
{
    cout << "Contador de referencias: " << obj.use_count() << endl;
    obj->saludar();
}

int main()
{
    cout << "=== UNIQUE_PTR ===" << endl;
    {
        unique_ptr<Objeto> unico = make_unique<Objeto>("Único");
        unico->saludar();
        // Transferir propiedad
        funcionConUniquePtr(move(unico));
        // unico ahora es nullptr
    } // Objeto se libera aquí

    cout << "\n=== SHARED_PTR ===" << endl;
    {
        shared_ptr<Objeto> compartido1 = make_shared<Objeto>("Compartido");
        cout << "Contador inicial: " << compartido1.use_count() << endl;

        {
            shared_ptr<Objeto> compartido2 = compartido1;
            cout << "Después de copiar: " << compartido1.use_count() << endl;

            funcionConSharedPtr(compartido2);
        } // compartido2 se libera, contador baja

        cout << "Después del scope interno: " << compartido1.use_count() << endl;
    } // Objeto se libera aquí

    cout << "\n=== ARRAYS CON SMART POINTERS ===" << endl;
    {
        unique_ptr<int[]> arr = make_unique<int[]>(5);
        for (int i = 0; i < 5; i++)
        {
            arr[i] = i * 10;
            cout << "arr[" << i << "] = " << arr[i] << endl;
        }
    } // Array se libera automáticamente

    cout << "\n=== CUSTOM DELETER ===" << endl;
    {
        auto deleter = [](int *ptr)
        {
            cout << "Liberando memoria personalizada" << endl;
            delete ptr;
        };

        unique_ptr<int, decltype(deleter)> ptrPersonalizado(new int(100), deleter);
        cout << "Valor: " << *ptrPersonalizado << endl;
    } // Se llama al deleter personalizado

}