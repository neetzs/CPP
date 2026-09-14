#include <iostream>
#include <queue>
#include <stack>
#include <deque>
#include <list>
using namespace std;

void mostrarQueue(queue<int> q, const string &nombre)
{
    cout << nombre << " (tamaño: " << q.size() << "): ";
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

void mostrarStack(stack<int> s, const string &nombre)
{
    cout << nombre << " (tamaño: " << s.size() << "): ";
    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

int main()
{
    cout << "=== QUEUE Y STACK EN C++ ===" << endl;

    // 1. Creación y operaciones básicas con Queue
    cout << "\n--- QUEUE (COLA) ---" << endl;

    queue<int> cola;                   // Cola vacía
    queue<int, deque<int>> cola_deque; // Cola con deque subyacente
    queue<int, list<int>> cola_list;   // Cola con list subyacente

    cout << "Cola inicial - tamaño: " << cola.size() << endl;

    // Agregar elementos (push)
    cola.push(10);
    cola.push(20);
    cola.push(30);
    cola.push(40);

    cout << "Después de push - tamaño: " << cola.size() << endl;
    cout << "Frente de la cola: " << cola.front() << endl;
    cout << "Final de la cola: " << cola.back() << endl;

    // Mostrar cola sin destruirla
    mostrarQueue(cola, "Contenido de la cola");

    // Remover elementos (pop)
    cout << "Removiendo elementos..." << endl;
    cola.pop(); // Remueve 10
    mostrarQueue(cola, "Después de pop");

    cola.pop(); // Remueve 20
    mostrarQueue(cola, "Después de otro pop");

    // 2. Creación y operaciones básicas con Stack
    cout << "\n--- STACK (PILA) ---" << endl;

    stack<int> pila;                     // Pila vacía
    stack<int, deque<int>> pila_deque;   // Pila con deque subyacente
    stack<int, vector<int>> pila_vector; // Pila con vector subyacente

    cout << "Pila inicial - tamaño: " << pila.size() << endl;

    // Agregar elementos (push)
    pila.push(100);
    pila.push(200);
    pila.push(300);
    pila.push(400);

    cout << "Después de push - tamaño: " << pila.size() << endl;
    cout << "Cima de la pila: " << pila.top() << endl;

    // Mostrar pila sin destruirla
    mostrarStack(pila, "Contenido de la pila");

    // Remover elementos (pop)
    cout << "Removiendo elementos..." << endl;
    pila.pop(); // Remueve 400
    mostrarStack(pila, "Después de pop");

    pila.pop(); // Remueve 300
    mostrarStack(pila, "Después de otro pop");

    // 3. Ejemplos prácticos con Queue
    cout << "\n--- EJEMPLOS PRÁCTICOS CON QUEUE ---" << endl;

    // Simulación de fila de banco
    queue<string> fila_banco;

    fila_banco.push("Cliente 1");
    fila_banco.push("Cliente 2");
    fila_banco.push("Cliente 3");
    fila_banco.push("Cliente 4");

    cout << "Procesando fila del banco:" << endl;
    while (!fila_banco.empty())
    {
        cout << "Atendiendo a: " << fila_banco.front() << endl;
        fila_banco.pop();
        cout << "Clientes restantes en fila: " << fila_banco.size() << endl;
    }

    // Cola de impresión
    queue<string> cola_impresion;
    cola_impresion.push("documento1.pdf");
    cola_impresion.push("presentacion.pptx");
    cola_impresion.push("reporte.docx");

    cout << "\nCola de impresión:" << endl;
    cout << "Próximo documento a imprimir: " << cola_impresion.front() << endl;

    // 4. Ejemplos prácticos con Stack
    cout << "\n--- EJEMPLOS PRÁCTICOS CON STACK ---" << endl;

    // Simulación de historial de navegación web
    stack<string> historial;

    historial.push("google.com");
    historial.push("stackoverflow.com");
    historial.push("cppreference.com");
    historial.push("github.com");

    cout << "Historial de navegación:" << endl;
    cout << "Página actual: " << historial.top() << endl;

    cout << "Retrocediendo en el historial:" << endl;
    while (!historial.empty())
    {
        cout << "Página: " << historial.top() << endl;
        historial.pop();
        if (!historial.empty())
        {
            cout << "Retrocediendo a: " << historial.top() << endl;
        }
    }

    // Verificación de paréntesis balanceados
    cout << "\nVerificación de paréntesis:" << endl;
    string expresion = "((a + b) * (c - d))";

    stack<char> parentesis;
    bool balanceado = true;

    for (char c : expresion)
    {
        if (c == '(')
        {
            parentesis.push(c);
        }
        else if (c == ')')
        {
            if (parentesis.empty())
            {
                balanceado = false;
                break;
            }
            parentesis.pop();
        }
    }

    if (balanceado && parentesis.empty())
    {
        cout << "La expresión '" << expresion << "' tiene paréntesis balanceados" << endl;
    }
    else
    {
        cout << "La expresión '" << expresion << "' tiene paréntesis desbalanceados" << endl;
    }

    // 5. Queue y Stack con tipos personalizados
    cout << "\n--- QUEUE Y STACK CON TIPOS PERSONALIZADOS ---" << endl;

    struct Tarea
    {
        string descripcion;
        int prioridad;

        Tarea(string desc, int pri) : descripcion(desc), prioridad(pri) {}
    };

    // Cola de tareas por orden de llegada
    queue<Tarea> tareas_cola;
    tareas_cola.push(Tarea("Limpiar habitación", 1));
    tareas_cola.push(Tarea("Hacer tarea", 2));
    tareas_cola.push(Tarea("Ir al gimnasio", 3));

    cout << "Procesando tareas en orden de llegada:" << endl;
    while (!tareas_cola.empty())
    {
        Tarea t = tareas_cola.front();
        cout << "- " << t.descripcion << " (prioridad: " << t.prioridad << ")" << endl;
        tareas_cola.pop();
    }

    // Pila de acciones (deshacer)
    stack<string> acciones;
    acciones.push("Escribir 'Hola'");
    acciones.push("Agregar negrita");
    acciones.push("Cambiar color a rojo");

    cout << "\nDeshaciendo acciones:" << endl;
    while (!acciones.empty())
    {
        cout << "Deshaciendo: " << acciones.top() << endl;
        acciones.pop();
    }

    // 6. Priority Queue (cola de prioridad)
    cout << "\n--- PRIORITY QUEUE ---" << endl;

// Nota: priority_queue no es exactamente queue, pero está relacionado
#include <queue>
    priority_queue<int> pq; // Máximo primero

    pq.push(10);
    pq.push(30);
    pq.push(20);
    pq.push(5);

    cout << "Priority Queue (máximo primero):" << endl;
    while (!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;

    // Priority queue con mínimo primero
    priority_queue<int, vector<int>, greater<int>> pq_min;

    pq_min.push(10);
    pq_min.push(30);
    pq_min.push(20);
    pq_min.push(5);

    cout << "Priority Queue (mínimo primero):" << endl;
    while (!pq_min.empty())
    {
        cout << pq_min.top() << " ";
        pq_min.pop();
    }
    cout << endl;

    // 7. Comparación de contenedores
    cout << "\n--- COMPARACIÓN DE CONTENEDORES ---" << endl;

    cout << "Queue: FIFO - Primero en entrar, primero en salir" << endl;
    cout << "Stack: LIFO - Último en entrar, primero en salir" << endl;
    cout << "Ambos son adaptadores de contenedores subyacentes" << endl;
    cout << "Por defecto usan deque, pero pueden usar otros contenedores" << endl;

    cout << "\n=== FIN DEL PROGRAMA ===" << endl;

    return 0;
}