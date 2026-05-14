# AstroLand

## Descripción General
AstroLand es un simulador de aterrizaje espacial desarrollado en C++ utilizando la librería gráfica SFML. El proyecto aborda el desafío de ingeniería de aterrizar una carga útil en diversos cuerpos celestes (como la Luna o Marte) considerando variables físicas reales como la gravedad diferencial, la densidad atmosférica y el manejo crítico de combustible.

El objetivo es proporcionar una experiencia educativa y técnica donde el usuario debe optimizar el uso de propulsores y gestionar la salud de los componentes de la nave para lograr un aterrizaje exitoso bajo condiciones de riesgo.

---

## Estructura
Para mantener una mejor organización, el repositorio se organiza de la siguiente manera:
*   `assets/`: Recursos multimedia (texturas de planetas, sprites de la nave y fuentes).
*   `docs/`: Documentación técnica y diagramas UML.
*   `include/`: Archivos de cabecera (`.h` / `.hpp`) con las definiciones de las clases.
*   `src/`: Archivos fuente (`.cpp`) con la implementación de la lógica.
*   `main.cpp`: Punto de entrada de la aplicación.
*   `.gitignore`: Configuración para excluir archivos temporales de compilación.

---

## Arquitectura General y Modelo POO
La solución está construida bajo un diseño PPOO que separa claramente las responsabilidades en capas para garantizar un sistema extensibley modular:

### 1. Datos Base y Herencia (Modelado de Mundos)
*   **CuerpoCeleste (Clase Base Abstracta):** Contiene la información física universal (masa, gravedad, nombre) y define el comportamiento polimórfico para el cálculo de atracción gravitatoria.
*   **Planeta y Luna (Clases Derivadas):** Heredan de `CuerpoCeleste`. Implementan propiedades específicas de su entorno, como la `densidadAtmosferica` para Planetas (permitiendo cálculos de arrastre) y `rugosidadTerreno` para Lunas.
*   **Juego (Agregación):** Funciona como el orquestador principal que carga y gestiona el `CuerpoCeleste` activo, vinculando el entorno con la lógica de la misión.

### 2. Entidades de Vuelo y Composición (Sistemas de la Nave)
*   **Componente (Clase Base Abstracta):** Define la estructura de salud, peso y costo para cualquier módulo instalable. Establece la interfaz polimórfica `aplicarFuncion()`.
*   **Propulsor (Herencia de Componente):** Implementa la lógica de empuje vectorial. Modificación clave: Su estructura permite transformar el combustible en fuerza aplicada a los ejes cartesianos mediante trigonometría.
*   **NaveEspacial (Composición):** Actúa como un contenedor dinámico que utiliza una lista de punteros a objetos `Componente`. Es capaz de integrar fuerzas y actualizar su estado cinemático en tiempo real.

### 3. Módulos de Servicio (Lógica de los Cálculos)
*   **Controlador Físico:** Contiene la lógica matemática para resolver las ecuaciones de movimiento dinámico mediante la integración de fuerzas (Empuje vs. Gravedad vs. Arrastre).
*   **Sistema de Telemetría:** Encargado de transformar las variables internas de la simulación (velocidad, altitud, rotación) en información visual interactiva mediante SFML.

---
