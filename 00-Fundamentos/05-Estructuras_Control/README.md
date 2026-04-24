# 05 - Estructuras de Control

## Concepto Clave
Las **estructuras de control** permiten que tu programa tome decisiones (if/else) y repita acciones (loops).

## 1. Decisiones: if, else if, else

```cpp
if (condición) {
    // Código si es VERDADERO
}
```

```cpp
if (condición) {
    // Si es verdadero
} else {
    // Si es falso
}
```

```cpp
if (condición1) {
    // Si condición1 es verdadera
} else if (condición2) {
    // Si condición1 es falsa pero condición2 es verdadera
} else {
    // Si ambas son falsas
}
```

## 2. Switch (Múltiples opciones)

```cpp
switch (variable) {
    case valor1:
        // Código si variable == valor1
        break;
    case valor2:
        // Código si variable == valor2
        break;
    default:
        // Si no coincide con ninguno
        break;
}
```

## 3. Loops: while

```cpp
while (condición) {
    // Se repite mientras la condición sea verdadera
}
```

## 4. Loops: for

```cpp
for (inicialización; condición; incremento) {
    // Se ejecuta repetidamente
}
```

### Ejemplo: Contar del 1 al 10
```cpp
for (int i = 1; i <= 10; i++) {
    cout << i << endl;
}
```

## 5. do-while (Al menos una vez)

```cpp
do {
    // Se ejecuta al menos una vez
} while (condición);
```

## Palabras Clave: break y continue

- **break**: Sale del loop inmediatamente
- **continue**: Salta a la siguiente iteración

## Comparación de Loops

| Loop | Uso |
|------|-----|
| `while` | Cuando no sabes cuántas veces se ejecutará |
| `do-while` | Cuando debe ejecutarse al menos una vez |
| `for` | Cuando sabes exactamente cuántas veces |

## Operador Ternario (if comprimido)

```cpp
int resultado = (edad >= 18) ? "Adulto" : "Menor";
```
