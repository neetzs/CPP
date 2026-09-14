# 06 - Manejo de Errores

Una aplicación robusta debe **anticipar y manejar errores gracefully**.

## Temas a Cubrir

### 1. **Excepciones**
- Concepto de excepción
- Tipos de excepciones
- Lanzar excepciones con `throw`

### 2. **Try-Catch**
- Capturar excepciones
- Múltiples catch
- Manejo de diferentes tipos de errores

### 3. **Excepciones Personalizadas**
- Crear clases de excepción
- Jerarquía de excepciones
- Información detallada de error

## Objetivos al Finalizar

- [ ] Entender cuándo usar excepciones
- [ ] Escribir try-catch correctamente
- [ ] Crear excepciones personalizadas
- [ ] Hacer código más robusto

## Estructura

```
try {
    // Código que puede fallar
    if (error) throw MiException("mensaje");
} catch (MiException& e) {
    cout << e.what() << endl;
} catch (exception& e) {
    cout << "Error: " << e.what() << endl;
}
```

## Importante

- No uses excepciones para flujo normal
- Usa excepciones para situaciones excepcionales
- Siempre limpia recursos (usa RAII)

## Alternativas

En C++ moderno, también existe `std::optional` y `std::expected` para casos donde la excepción no es necesaria.
