# 02 - Manejo de Memoria

En esta sección aprenderemos uno de los conceptos **más importantes y poderosos de C++**: cómo funciona la memoria.

## 📌 Temas a Cubrir

### 1. **Punteros Básicos**
- Concepto de dirección de memoria
- Operadores `&` (dirección) y `*` (desreferencia)
- Declaración de punteros

### 2. **Arrays y Punteros**
- Relación entre arrays y punteros
- Aritmética de punteros

### 3. **Memoria Dinámica**
- `new` para asignar memoria
- `delete` para liberar memoria
- Prevenir memory leaks

### 4. **Referencias**
- Alternativa más segura a punteros
- Cuando usar referencias

### 5. **Smart Pointers**
- `unique_ptr` - propiedad exclusiva
- `shared_ptr` - propiedad compartida
- Gestión automática de memoria

## 🎯 Objetivos al Finalizar

- [ ] Entender qué es un puntero
- [ ] Usar memoria dinámica correctamente
- [ ] Conocer la diferencia entre stack y heap
- [ ] Prevenir memory leaks
- [ ] Usar smart pointers en C++ moderno

## ⚠️ Importancia

El manejo de memoria es lo que **diferencia a C++ de lenguajes de más alto nivel**. Es poderoso pero requiere responsabilidad.

## 📝 Estructura de Aprendizaje

```
Punteros Básicos
    ↓
Arrays y Punteros
    ↓
Memoria Dinámica
    ↓
Referencias
    ↓
Smart Pointers
```

## 💡 Regla de Oro

**Por cada `new` debe haber un `delete`**
- Si usas `new`, NO olvides `delete`
- O mejor aún, usa smart pointers
