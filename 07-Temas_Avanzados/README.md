# 07 - Temas Avanzados

Aquí exploramos características poderosas que hacen a C++ verdaderamente versátil.

## Temas a Cubrir

### 1. **Templates**
- Templates de funciones
- Templates de clases
- Especialización de templates

### 2. **Programación Genérica**
- Metaprogramación
- Type traits
- SFINAE (Substitution Failure Is Not An Error)

### 3. **Traits y SFINAE**
- Verificación de tipos en compilación
- Selección de función por tipo
- Enable_if

### 4. **Move Semantics**
- R-values y L-values
- Move constructors
- Move assignment
- Perfect forwarding

### 5. **Expresiones Lambda**
- Funciones anónimas
- Captura de variables
- Uso con algoritmos STL

## Objetivos al Finalizar

- [ ] Escribir templates genéricos
- [ ] Entender move semantics
- [ ] Usar lambdas efectivamente
- [ ] Aplicar metaprogramación básica

## Ejemplo: Lambda

```cpp
vector<int> nums = {1, 2, 3, 4, 5};
auto pares = [](int x) { return x % 2 == 0; };
auto it = find_if(nums.begin(), nums.end(), pares);
```

## Temas Avanzados = Gran Poder

Estos temas permiten:
- Código altamente eficiente
- Abstracción sin costo en rendimiento
- Reutilización de código
- Type-safety en compilación

⚠️ **Con gran poder viene gran responsabilidad** - úsalos cuando sea necesario, no siempre.
