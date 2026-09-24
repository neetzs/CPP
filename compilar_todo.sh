#!/bin/bash

# Script para compilar todos los ejemplos de C++
# Uso: ./compilar_todo.sh

echo "======================================"
echo "Compilando ejemplos de C++"
echo "======================================"

# Colores
VERDE='\033[0;32m'
ROJO='\033[0;31m'
AMARILLO='\033[1;33m'
NC='\033[0m' # No Color

# Directorios con ejemplos
EJEMPLOS=(
    "00-Fundamentos/01-HolaMundo/ejemplo1_hola_mundo.cpp"
    "00-Fundamentos/01-HolaMundo/ejemplo2_multiples_salidas.cpp"
    "00-Fundamentos/02-Variables_y_TiposDatos/ejemplo1_tipos_basicos.cpp"
    "00-Fundamentos/02-Variables_y_TiposDatos/ejemplo2_constantes.cpp"
    "00-Fundamentos/03-Operadores/ejemplo1_operadores.cpp"
    "00-Fundamentos/04-Entrada_Salida/ejemplo1_entrada_basica.cpp"
    "00-Fundamentos/04-Entrada_Salida/ejemplo2_getline.cpp"
    "00-Fundamentos/05-Estructuras_Control/ejemplo1_if_else.cpp"
    "00-Fundamentos/05-Estructuras_Control/ejemplo2_loops.cpp"
    "01-Funciones_y_Modulares/01-Funciones_Basicas/ejemplo1_funciones_basicas.cpp"
)

# Compilar cada ejemplo
for ejemplo in "${EJEMPLOS[@]}"; do
    if [ -f "$ejemplo" ]; then
        nombre="${ejemplo%.*}"  # Elimina la extensión
        nombre="${nombre##*/}"   # Obtiene solo el nombre del archivo
        
        echo -e "${AMARILLO}Compilando: $ejemplo${NC}"
        g++ -std=c++23 -Wall -O2 "$ejemplo" -o "${nombre}" 2>/dev/null
        
        if [ $? -eq 0 ]; then
            echo -e "${VERDE}✓ $nombre compilado exitosamente${NC}"
        else
            echo -e "${ROJO}✗ Error compilando $nombre${NC}"
        fi
    fi
done

echo ""
echo "======================================"
echo "¡Compilación completada!"
echo "======================================"
