# Proyecto Final - Programación

## Descripción

El programa representa una red social académica universitaria
desarrollada en C++ utilizando estructuras de datos manuales.

El sistema permite administrar estudiantes,
rankings académicos, conexiones académicas,
proyectos asociados, persistencia de datos
y benchmarks de rendimiento dentro
de la plataforma.

La implementación utiliza:

- Tabla Hash manual
- Árbol AVL
- Grafo no dirigido
- Listas enlazadas
- Pila de acciones

La Tabla Hash utiliza resolución de colisiones
mediante Separate Chaining utilizando
listas enlazadas.

El Árbol AVL permite mantener ordenados
los estudiantes según su skill_score
para generar rankings académicos.

El Grafo representa las conexiones académicas
entre estudiantes dentro de la red social.

La Pila almacena el historial de acciones
realizadas dentro del sistema.

Cada estudiante almacena:

- student_id
- full_name
- career
- semester
- gpa
- skill_score

Además cada estudiante puede almacenar:

- proyectos académicos
- conexiones con otros estudiantes
- historial dentro de la red social

El sistema actualmente permite:

- Cargar estudiantes desde un archivo CSV
- Registrar estudiantes manualmente
- Buscar estudiantes por student_id
- Eliminar estudiantes
- Agregar proyectos académicos
- Buscar proyectos académicos
- Eliminar proyectos académicos
- Mostrar proyectos registrados
- Conectar estudiantes
- Verificar conexiones
- Mostrar conexiones entre estudiantes
- Ejecutar BFS
- Ejecutar DFS
- Mostrar ranking académico
- Mostrar estructura Hash
- Mostrar estadísticas de estructuras
- Mostrar historial de acciones
- Guardar persistencia de datos
- Restaurar persistencia automáticamente
- Ejecutar benchmark completo
- Exportar resultados CSV

## Funcionamiento

El usuario puede cargar estudiantes
desde un archivo CSV o registrarlos
manualmente desde el menú principal.

Cada estudiante es almacenado automáticamente
dentro de la Tabla Hash utilizando
su student_id como clave principal.

La Tabla Hash organiza los estudiantes
dentro de buckets utilizando listas enlazadas
para resolver colisiones.

El sistema también inserta estudiantes
dentro del Árbol AVL para mantener
el ranking académico ordenado automáticamente.

Las conexiones académicas entre estudiantes
son almacenadas mediante listas enlazadas
representando un grafo no dirigido.

Cada estudiante puede almacenar múltiples proyectos
utilizando listas enlazadas simples.

La pila de acciones almacena un historial básico
de operaciones realizadas dentro del sistema.

El sistema implementa recorridos BFS y DFS
para explorar las conexiones académicas
entre estudiantes dentro del grafo.

El sistema valida automáticamente:

- student_id duplicados
- conexiones duplicadas
- proyectos duplicados
- conexiones consigo mismo
- integridad básica de inserción

Además el sistema realiza:

- eliminación sincronizada
- persistencia automática
- exportación de benchmarks

## Estructuras implementadas

### Tabla Hash

Utilizada para:

- almacenamiento de estudiantes
- búsqueda rápida por ID
- eliminación de estudiantes
- manejo de colisiones

Características:

- implementación manual
- Separate Chaining
- cálculo de factor de carga
- conteo de colisiones
- persistencia de estudiantes

### Árbol AVL

Utilizado para:

- ranking académico
- organización por skill_score
- recorridos ordenados

Características:

- balanceo automático
- rotaciones simples y dobles
- recorrido InOrden
- cálculo de altura
- benchmark AVL

### Grafo

Utilizado para:

- conexiones entre estudiantes
- representación de relaciones académicas
- BFS
- DFS

Características:

- grafo no dirigido
- conexiones bidireccionales
- validación de conexiones duplicadas
- validación de auto conexión
- recorrido BFS
- recorrido DFS

### Lista Enlazada

Utilizada para:

- almacenamiento de proyectos académicos
- manejo de colisiones Hash
- conexiones entre estudiantes

Cada proyecto almacena:

- project_id
- title
- description
- completion_year

### Pila

Utilizada para:

- historial de acciones del sistema

Características:

- registro de operaciones realizadas
- implementación manual sin STL

## Persistencia de datos

El sistema implementa persistencia completa
de información mediante archivos.

Archivos utilizados:

- students_backup.csv
- connections_backup.txt
- projects_backup.txt

La persistencia permite:

- guardar estudiantes
- guardar conexiones
- guardar proyectos
- restaurar datos automáticamente

## Benchmark

El sistema implementa benchmark completo
utilizando la librería chrono de C++.

Operaciones medidas:

- inserción Hash
- búsqueda Hash
- inserción AVL
- recorrido AVL
- BFS
- DFS

Los resultados son exportados automáticamente
al archivo:

cpp_results.csv

## Analisis Comparativo C++ vs Java

La plataforma presenta dos enfoques arquitectónicos distintos.
La versión Java utiliza contenedores estándar de la biblioteca de utilidades.
La versión C++ requiere la gestión manual de memoria y punteros.

### Tabla Hash vs HashMap

La versión Java utiliza la estructura estándar HashMap.
El contenedor aplica redimensionamiento dinámico al alcanzar el 75% de capacidad.
La resolución de colisiones escala automáticamente de listas enlazadas a árboles.

La versión C++ implementa una Tabla Hash de asignación estática.
La inicialización en el sistema base asigna 10 posiciones de memoria.
La resolución de colisiones utiliza Separate Chaining mediante listas enlazadas.

### Arbol de Busqueda Auto-balanceado

La versión Java implementa un TreeMap basado en un Árbol Rojo-Negro.
La estructura permite un balanceo flexible con menor frecuencia de rotaciones.

La versión C++ implementa un Árbol AVL manual.
La estructura mantiene un balance estricto garantizando la diferencia de alturas.
El árbol mantiene ordenados los estudiantes según su skill_score.

### Grafos y Listas Secuenciales

La versión Java utiliza ArrayList para el almacenamiento en lote del dataset.

La versión C++ prescinde de contenedores secuenciales independientes.
El sistema C++ utiliza un Grafo no dirigido para las conexiones académicas.
Las aristas del grafo se representan mediante listas de adyacencia dentro de cada nodo.

## Tabla Comparativa de Benchmark

La rutina de evaluación presenta asimetrías operativas entre ambos lenguajes.
Las métricas generadas no pueden analizarse mediante comparación directa.

- Volumen de Carga: Procesa 1 operación aislada en C++ frente a 10000 operaciones en lote en Java.
- Inserción Hash: Inserta 1 nodo de prueba en C++ frente al dataset completo en Java.
- Búsqueda Hash: Localiza 1 identificador único en C++ frente a iterar todos los identificadores en Java.
- Inserción Árbol: Registra rotaciones de 1 nodo en C++ frente a construir el árbol completo en Java.
- Recorrido Árbol: Ejecuta impresión en consola en C++ frente a asignar referencias en memoria en Java.
- Unidades de Tiempo: Captura métricas en microsegundos en C++ frente a milisegundos en Java.

## Conclusiones Tecnicas

### Degradacion del Rendimiento Hash

La Tabla Hash en C++ con asignación de 10 índices presenta un cuello de botella.
El procesamiento de 10000 registros genera un promedio de 1000 colisiones por índice.
La estructura degrada su eficiencia de acceso hacia una búsqueda lineal.
Se requiere la asignación de un arreglo proporcional al dataset para garantizar el rendimiento.

### Inconsistencia en los Archivos de Resultados

El sistema en C++ registra la variable de tiempo en microsegundos bajo la columna time_ms.
El benchmark de C++ no acumula el costo de la carga estructural del archivo fuente.
El programa de Java incluye la saturación de recolección de basura en sus tiempos totales.
Se requiere unificar el volumen de iteraciones y las unidades métricas para estandarizar el benchmark.

### Gestion de Recursos y Latencia

El motor de Java aplica picos de procesamiento durante la limpieza del Recolector de Basura.
El código en C++ mantiene un consumo de recursos estable y predecible.
El sistema manual exige la desasignación individual de los punteros en los destructores del programa.

## Formato del archivo CSV

El archivo CSV debe contener
la siguiente estructura:

student_id,full_name,career,semester,gpa,skill_score

1001,Juan Perez,Ingenieria en Sistemas,5,85.50,120

1002,Ana Lopez,Ingenieria Industrial,7,91.20,200

1003,Carlos Ruiz,Ingenieria Civil,3,78.30,95

## Reglas de inserción

1. El student_id se utiliza como clave principal
2. No se permiten estudiantes duplicados
3. Las colisiones se resuelven mediante Separate Chaining
4. Cada bucket puede almacenar múltiples estudiantes enlazados
5. Cada estudiante puede almacenar múltiples proyectos
6. El ranking académico se ordena mediante skill_score
7. No se permiten conexiones duplicadas
8. No se permite conectar un estudiante consigo mismo
9. No se permiten proyectos duplicados dentro de un mismo estudiante
10. La eliminación elimina conexiones asociadas automáticamente
11. La persistencia guarda automáticamente la información

## Opciones actuales del programa

1. Cargar CSV
2. Registrar estudiante
3. Buscar estudiante
4. Eliminar estudiante
5. Agregar proyecto
6. Mostrar proyectos
7. Buscar proyecto
8. Eliminar proyecto
9. Conectar estudiantes
10. Verificar conexion
11. Mostrar conexiones
12. BFS
13. DFS
14. Mostrar tabla
15. Ranking AVL
16. Estadisticas
17. Historial
18. Guardar persistencia
19. Benchmark completo
20. Salir

## Ejemplo

### Carga CSV

estudiantes.csv

### Registro manual

Student ID: 1005

Nombre: Maria Lopez

Carrera: Ingenieria en Sistemas

### Búsqueda

student_id: 1002

Resultado:

ID: 1002

Nombre: Ana Lopez

Carrera: Ingenieria Industrial

### Proyecto

Project ID: 10

Titulo: Sistema Web

Anio: 2026

### Conexión

ID estudiante 1: 1001

ID estudiante 2: 1002

Resultado:

Conexion creada

### BFS

Inicio BFS: 1001

Resultado:

1001 1002 1005

### DFS

Inicio DFS: 1001

Resultado:

1001 1005 1002

## Estadísticas

Cantidad de estudiantes cargados: 10

Total de conexiones: 5

Total de proyectos: 7

Colisiones generadas: 3

Factor de carga: 1.0

Altura del AVL: 4

## Arquitectura

El código fue diseñado utilizando
estructuras manuales sin utilizar
colecciones avanzadas de STL.

La implementación encapsula las estructuras
principales dentro de clases independientes.

Actualmente el sistema incluye:

- TablaHash
- ArbolAVL
- PilaAcciones

Las listas enlazadas se utilizan
como soporte para:

- manejo de colisiones
- proyectos académicos
- conexiones entre estudiantes

## Funcionalidades implementadas

Actualmente el sistema incluye:

- BFS
- DFS
- Benchmark completo en C++
- Exportación automática de resultados CSV
- Persistencia de datos en archivos
- Eliminación sincronizada
- Buscar proyecto
- Eliminar proyecto

## Restricciones respetadas

El proyecto fue desarrollado respetando
las restricciones establecidas.

No se utilizó:

- map
- unordered_map
- set
- queue
- stack
- list
- colecciones STL equivalentes

Todas las estructuras fueron implementadas manualmente.

## Ejecutar programa en C++

### Compilar

g++ main.cpp -o programa

### Ejecutar

programa.exe

o

./programa

## Autor

Josue David Flores Roldan

Carnet: 9941 24 7857