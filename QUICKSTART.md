# GUÍA DE INICIO RÁPIDO

## 1️⃣ Primera Vez - Compilar tu Primer Programa

```bash
# Navega a la carpeta
cd /home/neetzs/Neetzs/CPP/00-Fundamentos/01-HolaMundo/

# Compila el primer ejemplo
g++ -std=c++23 ejemplo1_hola_mundo.cpp -o hola_mundo

# Ejecuta el programa
./hola_mundo

# Resultado esperado:
# Hola Mundo
```

## 2️⃣ Compilar Todos los Ejemplos

```bash
cd /home/neetzs/Neetzs/CPP/

# Dale permisos al script
chmod +x compilar_todo.sh

# Ejecuta el script
./compilar_todo.sh

# Verás algo como:
# ✓ ejemplo1_hola_mundo compilado exitosamente
# ✓ ejemplo2_multiples_salidas compilado exitosamente
# ... etc
```

## 3️⃣ Estructura de Carpetas

```
CPP/
├── README.md ..................... Índice principal
├── CHECKLIST.md .................. Estado de creación
├── QUICKSTART.md ................. Este archivo
├── compilar_todo.sh .............. Script para compilar
│
├── 00-Fundamentos/ ............... EMPIEZA AQUÍ
│   ├── README.md ................. Explicaciones
│   ├── 01-HolaMundo/ ............. Primer programa
│   ├── 02-Variables_y_TiposDatos/ Variables e int/float/etc
│   ├── 03-Operadores/ ............ +, -, *, /, ==, &&, etc
│   ├── 04-Entrada_Salida/ ........ cin, cout, getline
│   └── 05-Estructuras_Control/ .. if, for, while, switch
│
├── 01-Funciones_y_Modulares/ .... Código organizado
│
├── 02-Manejo_Memoria/ ........... Punteros, new, delete
│
├── 03-POO_Basico/ ............... Clases y Objetos
│
├── 04-POO_Avanzado/ ............. Herencia, Polimorfismo
│
├── 05-Contenedores_STL/ ......... Vector, Map, Set, etc
│
├── 06-Manejo_Errores/ ........... Try-Catch, Excepciones
│
├── 07-Temas_Avanzados/ .......... Templates, Lambda, etc
│
├── 08-Librerias_Populares/ ...... Archivos, JSON, Threads
│
└── 99-Proyectos_Integradores/ .. Proyectos prácticos
```

## 4️⃣ Plan de Estudio Sugerido (30 días)

### Semana 1: Fundamentos
- [ ] Día 1: Hola Mundo + Variables
- [ ] Día 2: Tipos de Datos + Constantes
- [ ] Día 3: Operadores
- [ ] Día 4: Entrada/Salida
- [ ] Día 5: if/else
- [ ] Día 6: for/while
- [ ] Día 7: Ejercicios y repaso

### Semana 2: Funciones y Lógica
- [ ] Día 8: Funciones básicas
- [ ] Día 9: Parámetros y retorno
- [ ] Día 10: Recursión
- [ ] Día 11: Namespaces
- [ ] Día 12-14: Mini proyectos

### Semana 3: Memoria y POO Básico
- [ ] Día 15: Punteros
- [ ] Día 16: Memoria dinámica
- [ ] Día 17: Clases y objetos
- [ ] Día 18: Constructores
- [ ] Día 19: Encapsulamiento
- [ ] Día 20: Getters/Setters
- [ ] Día 21: Ejercicios

### Semana 4: POO Avanzado y STL
- [ ] Día 22: Herencia
- [ ] Día 23: Polimorfismo
- [ ] Día 24: Vector y containers
- [ ] Día 25: Algoritmos STL
- [ ] Día 26: Excepciones
- [ ] Día 27: Proyecto pequeño
- [ ] Día 28-30: Proyecto mayor

## 5️⃣ Comandos Útiles

### Compilación básica
```bash
# Compilar un archivo
g++ -std=c++23 archivo.cpp -o programa

# Compilar con optimizaciones
g++ -std=c++23 -O2 archivo.cpp -o programa

# Compilar con warnings
g++ -std=c++23 -Wall archivo.cpp -o programa

# Compilar múltiples archivos
g++ -std=c++23 archivo1.cpp archivo2.cpp -o programa
```

### Ejecutar programas
```bash
# Ejecutar desde la terminal
./programa

# Con entrada interactiva
./programa < input.txt

# Guardar salida a archivo
./programa > output.txt

# Tanto entrada como salida
./programa < input.txt > output.txt
```

### Depuración
```bash
# Compilar con símbolos de debug
g++ -std=c++23 -g archivo.cpp -o programa

# Ejecutar con gdb
gdb ./programa
```

## 6️⃣ Archivos de Configuración para tu Editor

### Si usas VS Code, agrega esto a `.vscode/c_cpp_properties.json`:
```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": ["/usr/include"],
            "defines": [],
            "compilerPath": "/usr/bin/g++",
            "cStandard": "c23",
            "cppStandard": "c++23",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}
```

## 7️⃣ Recursos Online

- [cppreference.com](https://en.cppreference.com/) - Referencia oficial
- [cplusplus.com](http://www.cplusplus.com/) - Tutoriales
- [Compiler Explorer](https://godbolt.org/) - Visualizar compilación
- [GeeksforGeeks C++](https://www.geeksforgeeks.org/c-plus-plus/) - Tutoriales

## 8️⃣ Tips Importantes

✅ **DO (Haz esto):**
- Compila y ejecuta cada ejemplo
- Modifica el código para experimentar
- Lee los comentarios en los .cpp
- Toma notas
- Practica regularmente

❌ **DON'T (No hagas esto):**
- No memorices, entiende
- No saltes secciones
- No ignores los errores
- No copies sin entender
- No dejes de practicar

## 9️⃣ ¿Tienes Errores?

### Error: "g++: command not found"
```bash
# Instala g++
sudo dnf install g++

# Verifica la versión
g++ --version
```

### Error: "No such file or directory"
- Verifica que el archivo existe
- Verifica que estás en la carpeta correcta
- Usa rutas absolutas si es necesario

### Error de compilación en el código
- Lee el mensaje de error cuidadosamente
- Busca la línea indicada
- Verifica sintaxis (puntos y comas, paréntesis, llaves)

## 🔟 Siguiente Paso

1. Lee el [README.md](./README.md) principal
2. Abre la carpeta `00-Fundamentos`
3. Lee el README.md de esa sección
4. Compila el primer ejemplo
5. ¡Comienza tu viaje en C++! 🎉

---

**¿Preguntas?** Consulta el README.md de cada sección o la documentación oficial.

**¡Éxito!**
