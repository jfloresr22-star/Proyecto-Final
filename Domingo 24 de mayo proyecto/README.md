# Proyecto Final - Programación

## Descripción

El programa representa una red social académica universitaria
desarrollada en C++ utilizando estructuras de datos manuales.

El sistema permite administrar estudiantes,
rankings académicos, conexiones académicas
y proyectos asociados a cada usuario dentro
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
- publicaciones futuras dentro de la red social

El sistema actualmente permite:

- Cargar estudiantes desde un archivo CSV
- Registrar estudiantes manualmente
- Buscar estudiantes por student_id
- Eliminar estudiantes
- Agregar proyectos académicos
- Mostrar proyectos registrados
- Conectar estudiantes
- Mostrar conexiones entre estudiantes
- Mostrar ranking académico
- Mostrar estructura Hash
- Mostrar estadísticas de estructuras
- Mostrar historial de acciones

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

El sistema valida automáticamente:

- student_id duplicados
- conexiones duplicadas
- proyectos duplicados
- conexiones consigo mismo
- integridad básica de inserción

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

### Grafo

Utilizado para:

- conexiones entre estudiantes
- representación de relaciones académicas

Características:

- grafo no dirigido
- conexiones bidireccionales
- validación de conexiones duplicadas
- validación de auto conexión

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

## Opciones actuales del programa

1. Cargar archivo CSV  
2. Registrar estudiante manualmente  
3. Buscar estudiante por ID  
4. Eliminar estudiante  
5. Agregar proyecto a estudiante  
6. Mostrar proyectos de estudiante  
7. Conectar estudiantes  
8. Mostrar conexiones  
9. Mostrar tabla hash  
10. Mostrar ranking académico  
11. Mostrar estadísticas  
12. Mostrar historial  
13. Salir  

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

Conexion realizada correctamente

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

## Funcionalidades pendientes

Las siguientes funcionalidades serán integradas
en los siguientes avances del proyecto:

- BFS
- DFS
- Benchmark en C++
- Benchmark comparativo en Java
- Exportación automática de resultados CSV
- Persistencia de datos en archivos

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