#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

struct Proyecto {

    int project_id;
    string title;
    string description;
    int completion_year;

    Proyecto* siguiente;
};

struct Conexion {

    int student_id;
    Conexion* siguiente;
};

struct Student {

    int student_id;
    string full_name;
    string career;
    int semester;
    float gpa;
    int skill_score;

    Proyecto* proyectos;
    Conexion* conexiones;
};

struct Nodo {

    Student dato;
    Nodo* siguiente;
};

struct NodoAVL {

    Student dato;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;
};

struct Accion {

    string descripcion;
    Accion* siguiente;
};

class PilaAcciones {

private:

    Accion* cima;

public:

    PilaAcciones() {

        cima = NULL;
    }

    void push(string texto) {

        Accion* nuevo = new Accion;

        nuevo->descripcion = texto;

        nuevo->siguiente = cima;

        cima = nuevo;
    }

    void mostrarHistorial() {

        Accion* aux = cima;

        cout << "\n===== HISTORIAL =====\n";

        while (aux != NULL) {

            cout << "- " << aux->descripcion << endl;

            aux = aux->siguiente;
        }
    }
};

class TablaHash {

private:

    Nodo** tabla;
    int tamanio;

public:

    int cantidad;
    int colisiones;
    int totalConexiones;
    int totalProyectos;

    TablaHash(int t) {

        tamanio = t;

        cantidad = 0;
        colisiones = 0;
        totalConexiones = 0;
        totalProyectos = 0;

        tabla = new Nodo*[tamanio];

        for (int i = 0; i < tamanio; i++) {

            tabla[i] = NULL;
        }
    }

    int funcionHash(int id) {

        return id % tamanio;
    }

    bool existe(int id) {

        int indice = funcionHash(id);

        Nodo* aux = tabla[indice];

        while (aux != NULL) {

            if (aux->dato.student_id == id) {

                return true;
            }

            aux = aux->siguiente;
        }

        return false;
    }

    Nodo* obtenerNodo(int id) {

        int indice = funcionHash(id);

        Nodo* aux = tabla[indice];

        while (aux != NULL) {

            if (aux->dato.student_id == id) {

                return aux;
            }

            aux = aux->siguiente;
        }

        return NULL;
    }

    void insertar(Student e) {

        if (existe(e.student_id)) {

            cout << "Estudiante duplicado\n";

            return;
        }

        int indice = funcionHash(e.student_id);

        Nodo* nuevo = new Nodo;

        nuevo->dato = e;

        nuevo->siguiente = tabla[indice];

        if (tabla[indice] != NULL) {

            colisiones++;
        }

        tabla[indice] = nuevo;

        cantidad++;

        cout << "Estudiante insertado\n";
    }

    void buscar(int id) {

        Nodo* aux = obtenerNodo(id);

        if (aux != NULL) {

            cout << "\n===== ESTUDIANTE =====\n";

            cout << "ID: " << aux->dato.student_id << endl;
            cout << "Nombre: " << aux->dato.full_name << endl;
            cout << "Carrera: " << aux->dato.career << endl;
            cout << "Semestre: " << aux->dato.semester << endl;
            cout << "GPA: " << aux->dato.gpa << endl;
            cout << "Skill Score: " << aux->dato.skill_score << endl;

            return;
        }

        cout << "No encontrado\n";
    }

    void eliminarConexiones(int id) {

        for (int i = 0; i < tamanio; i++) {

            Nodo* actual = tabla[i];

            while (actual != NULL) {

                Conexion* aux = actual->dato.conexiones;
                Conexion* anterior = NULL;

                while (aux != NULL) {

                    if (aux->student_id == id) {

                        if (anterior == NULL) {

                            actual->dato.conexiones = aux->siguiente;
                        }

                        else {

                            anterior->siguiente = aux->siguiente;
                        }

                        Conexion* temp = aux;

                        aux = aux->siguiente;

                        delete temp;

                        totalConexiones--;

                        continue;
                    }

                    anterior = aux;
                    aux = aux->siguiente;
                }

                actual = actual->siguiente;
            }
        }
    }

    void eliminarProyectos(int id) {

        Nodo* estudiante = obtenerNodo(id);

        if (estudiante == NULL)
            return;

        Proyecto* aux = estudiante->dato.proyectos;

        while (aux != NULL) {

            Proyecto* temp = aux;

            aux = aux->siguiente;

            delete temp;

            totalProyectos--;
        }

        estudiante->dato.proyectos = NULL;
    }

    void eliminar(int id) {

        eliminarConexiones(id);

        eliminarProyectos(id);

        int indice = funcionHash(id);

        Nodo* aux = tabla[indice];
        Nodo* anterior = NULL;

        while (aux != NULL) {

            if (aux->dato.student_id == id) {

                if (anterior == NULL) {

                    tabla[indice] = aux->siguiente;
                }

                else {

                    anterior->siguiente = aux->siguiente;
                }

                delete aux;

                cantidad--;

                cout << "Estudiante eliminado completamente\n";

                return;
            }

            anterior = aux;
            aux = aux->siguiente;
        }

        cout << "No encontrado\n";
    }

    void conectarEstudiantes(int id1, int id2) {

        if (id1 == id2) {

            cout << "No permitido\n";

            return;
        }

        Nodo* e1 = obtenerNodo(id1);
        Nodo* e2 = obtenerNodo(id2);

        if (e1 == NULL || e2 == NULL) {

            cout << "Estudiante inexistente\n";

            return;
        }

        Conexion* aux = e1->dato.conexiones;

        while (aux != NULL) {

            if (aux->student_id == id2) {

                cout << "Conexion duplicada\n";

                return;
            }

            aux = aux->siguiente;
        }

        Conexion* nueva1 = new Conexion;

        nueva1->student_id = id2;
        nueva1->siguiente = e1->dato.conexiones;

        e1->dato.conexiones = nueva1;

        Conexion* nueva2 = new Conexion;

        nueva2->student_id = id1;
        nueva2->siguiente = e2->dato.conexiones;

        e2->dato.conexiones = nueva2;

        totalConexiones++;

        cout << "Conexion creada\n";
    }

    void mostrarConexiones(int id) {

        Nodo* estudiante = obtenerNodo(id);

        if (estudiante == NULL) {

            cout << "No encontrado\n";

            return;
        }

        Conexion* aux = estudiante->dato.conexiones;

        cout << "\n===== CONEXIONES =====\n";

        while (aux != NULL) {

            cout << "Conectado con: " << aux->student_id << endl;

            aux = aux->siguiente;
        }
    }

    bool estanConectados(int id1, int id2) {

        Nodo* estudiante = obtenerNodo(id1);

        if (estudiante == NULL)
            return false;

        Conexion* aux = estudiante->dato.conexiones;

        while (aux != NULL) {

            if (aux->student_id == id2)
                return true;

            aux = aux->siguiente;
        }

        return false;
    }

    void BFS(int inicio) {

        bool visitados[1000] = {false};

        int cola[1000];

        int frente = 0;
        int fin = 0;

        cola[fin++] = inicio;

        visitados[inicio % 1000] = true;

        cout << "\n===== BFS =====\n";

        while (frente < fin) {

            int actual = cola[frente++];

            cout << actual << " ";

            Nodo* nodoActual = obtenerNodo(actual);

            if (nodoActual != NULL) {

                Conexion* aux = nodoActual->dato.conexiones;

                while (aux != NULL) {

                    int vecino = aux->student_id;

                    if (!visitados[vecino % 1000]) {

                        visitados[vecino % 1000] = true;

                        cola[fin++] = vecino;
                    }

                    aux = aux->siguiente;
                }
            }
        }

        cout << endl;
    }

    void DFSRecursivo(int actual, bool visitados[]) {

        visitados[actual % 1000] = true;

        cout << actual << " ";

        Nodo* nodoActual = obtenerNodo(actual);

        if (nodoActual != NULL) {

            Conexion* aux = nodoActual->dato.conexiones;

            while (aux != NULL) {

                int vecino = aux->student_id;

                if (!visitados[vecino % 1000]) {

                    DFSRecursivo(vecino, visitados);
                }

                aux = aux->siguiente;
            }
        }
    }

    void DFS(int inicio) {

        bool visitados[1000] = {false};

        cout << "\n===== DFS =====\n";

        DFSRecursivo(inicio, visitados);

        cout << endl;
    }

    void agregarProyecto(int id) {

        Nodo* estudiante = obtenerNodo(id);

        if (estudiante == NULL) {

            cout << "No encontrado\n";

            return;
        }

        int nuevoID;

        cout << "Project ID: ";
        cin >> nuevoID;

        Proyecto* validar = estudiante->dato.proyectos;

        while (validar != NULL) {

            if (validar->project_id == nuevoID) {

                cout << "Proyecto duplicado\n";

                return;
            }

            validar = validar->siguiente;
        }

        Proyecto* nuevo = new Proyecto;

        nuevo->project_id = nuevoID;

        cin.ignore();

        cout << "Titulo: ";
        getline(cin, nuevo->title);

        cout << "Descripcion: ";
        getline(cin, nuevo->description);

        cout << "Anio: ";
        cin >> nuevo->completion_year;

        nuevo->siguiente = estudiante->dato.proyectos;

        estudiante->dato.proyectos = nuevo;

        totalProyectos++;

        cout << "Proyecto agregado\n";
    }

    void buscarProyecto(int studentID, int projectID) {

        Nodo* estudiante = obtenerNodo(studentID);

        if (estudiante == NULL) {

            cout << "Estudiante no encontrado\n";

            return;
        }

        Proyecto* aux = estudiante->dato.proyectos;

        while (aux != NULL) {

            if (aux->project_id == projectID) {

                cout << "\n===== PROYECTO =====\n";

                cout << "ID: " << aux->project_id << endl;
                cout << "Titulo: " << aux->title << endl;
                cout << "Descripcion: " << aux->description << endl;
                cout << "Anio: " << aux->completion_year << endl;

                return;
            }

            aux = aux->siguiente;
        }

        cout << "Proyecto no encontrado\n";
    }

    void eliminarProyecto(int studentID, int projectID) {

        Nodo* estudiante = obtenerNodo(studentID);

        if (estudiante == NULL) {

            cout << "Estudiante no encontrado\n";

            return;
        }

        Proyecto* aux = estudiante->dato.proyectos;
        Proyecto* anterior = NULL;

        while (aux != NULL) {

            if (aux->project_id == projectID) {

                if (anterior == NULL) {

                    estudiante->dato.proyectos = aux->siguiente;
                }

                else {

                    anterior->siguiente = aux->siguiente;
                }

                delete aux;

                totalProyectos--;

                cout << "Proyecto eliminado\n";

                return;
            }

            anterior = aux;
            aux = aux->siguiente;
        }

        cout << "Proyecto no encontrado\n";
    }

    void mostrarProyectos(int id) {

        Nodo* estudiante = obtenerNodo(id);

        if (estudiante == NULL) {

            cout << "No encontrado\n";

            return;
        }

        Proyecto* p = estudiante->dato.proyectos;

        cout << "\n===== PROYECTOS =====\n";

        while (p != NULL) {

            cout << "\nID: " << p->project_id << endl;
            cout << "Titulo: " << p->title << endl;
            cout << "Descripcion: " << p->description << endl;
            cout << "Anio: " << p->completion_year << endl;

            p = p->siguiente;
        }
    }

    void mostrarTabla() {

        cout << "\n===== TABLA HASH =====\n";

        for (int i = 0; i < tamanio; i++) {

            cout << "\nBucket " << i << ": ";

            Nodo* aux = tabla[i];

            while (aux != NULL) {

                cout << aux->dato.student_id << " -> ";

                aux = aux->siguiente;
            }

            cout << "NULL";
        }

        cout << endl;
    }

    void mostrarEstadisticas() {

        cout << "\n===== ESTADISTICAS =====\n";

        cout << "Estudiantes: " << cantidad << endl;
        cout << "Conexiones: " << totalConexiones << endl;
        cout << "Proyectos: " << totalProyectos << endl;
        cout << "Colisiones: " << colisiones << endl;

        float factor = (float)cantidad / tamanio;

        cout << "Factor carga: " << factor << endl;
    }

    void guardarDatos() {

        ofstream archivo("students_backup.csv");

        archivo << "student_id,full_name,career,semester,gpa,skill_score\n";

        for (int i = 0; i < tamanio; i++) {

            Nodo* aux = tabla[i];

            while (aux != NULL) {

                archivo
                << aux->dato.student_id << ","
                << aux->dato.full_name << ","
                << aux->dato.career << ","
                << aux->dato.semester << ","
                << aux->dato.gpa << ","
                << aux->dato.skill_score
                << "\n";

                aux = aux->siguiente;
            }
        }

        archivo.close();

        ofstream conexiones("connections_backup.txt");

        for (int i = 0; i < tamanio; i++) {

            Nodo* aux = tabla[i];

            while (aux != NULL) {

                Conexion* c = aux->dato.conexiones;

                while (c != NULL) {

                    conexiones
                    << aux->dato.student_id
                    << ","
                    << c->student_id
                    << "\n";

                    c = c->siguiente;
                }

                aux = aux->siguiente;
            }
        }

        conexiones.close();

        ofstream proyectos("projects_backup.txt");

        for (int i = 0; i < tamanio; i++) {

            Nodo* aux = tabla[i];

            while (aux != NULL) {

                Proyecto* p = aux->dato.proyectos;

                while (p != NULL) {

                    proyectos
                    << aux->dato.student_id << ","
                    << p->project_id << ","
                    << p->title << ","
                    << p->description << ","
                    << p->completion_year
                    << "\n";

                    p = p->siguiente;
                }

                aux = aux->siguiente;
            }
        }

        proyectos.close();

        cout << "Persistencia completada\n";
    }

    void cargarDatosGuardados() {

        ifstream archivo("students_backup.csv");

        if (!archivo)
            return;

        string linea;

        getline(archivo, linea);

        while (getline(archivo, linea)) {

            stringstream ss(linea);

            string dato;

            Student e;

            getline(ss, dato, ',');
            e.student_id = stoi(dato);

            getline(ss, e.full_name, ',');

            getline(ss, e.career, ',');

            getline(ss, dato, ',');
            e.semester = stoi(dato);

            getline(ss, dato, ',');
            e.gpa = stof(dato);

            getline(ss, dato, ',');
            e.skill_score = stoi(dato);

            e.proyectos = NULL;
            e.conexiones = NULL;

            insertar(e);
        }

        archivo.close();

        cout << "Datos restaurados\n";
    }

    void benchmarkCompleto() {

        ofstream archivo("cpp_results.csv");

        archivo << "Operacion,Tiempo(ms)\n";

        Student e;

        e.student_id = 9999;
        e.full_name = "Benchmark";
        e.career = "Systems";
        e.semester = 1;
        e.gpa = 90;
        e.skill_score = 95;
        e.proyectos = NULL;
        e.conexiones = NULL;

        auto inicioHashInsert = high_resolution_clock::now();

        insertar(e);

        auto finHashInsert = high_resolution_clock::now();

        archivo
        << "Insercion Hash,"
        << duration_cast<microseconds>(finHashInsert - inicioHashInsert).count()
        << "\n";

        auto inicioHashSearch = high_resolution_clock::now();

        buscar(9999);

        auto finHashSearch = high_resolution_clock::now();

        archivo
        << "Busqueda Hash,"
        << duration_cast<microseconds>(finHashSearch - inicioHashSearch).count()
        << "\n";

        auto inicioBFS = high_resolution_clock::now();

        BFS(9999);

        auto finBFS = high_resolution_clock::now();

        archivo
        << "BFS,"
        << duration_cast<microseconds>(finBFS - inicioBFS).count()
        << "\n";

        auto inicioDFS = high_resolution_clock::now();

        DFS(9999);

        auto finDFS = high_resolution_clock::now();

        archivo
        << "DFS,"
        << duration_cast<microseconds>(finDFS - inicioDFS).count()
        << "\n";

        archivo.close();

        cout << "Benchmark exportado a cpp_results.csv\n";
    }

    void cargarCSV(string nombreArchivo) {

        auto inicio = high_resolution_clock::now();

        ifstream archivo(nombreArchivo);

        if (!archivo) {

            cout << "Error archivo\n";

            return;
        }

        string linea;

        getline(archivo, linea);

        while (getline(archivo, linea)) {

            stringstream ss(linea);

            string dato;

            Student e;

            getline(ss, dato, ',');
            e.student_id = stoi(dato);

            getline(ss, e.full_name, ',');

            getline(ss, e.career, ',');

            getline(ss, dato, ',');
            e.semester = stoi(dato);

            getline(ss, dato, ',');
            e.gpa = stof(dato);

            getline(ss, dato, ',');
            e.skill_score = stoi(dato);

            e.proyectos = NULL;
            e.conexiones = NULL;

            insertar(e);
        }

        archivo.close();

        auto fin = high_resolution_clock::now();

        auto duracion = duration_cast<milliseconds>(fin - inicio);

        cout << "CSV cargado\n";

        cout << "Tiempo: " << duracion.count() << " ms\n";
    }
};

class ArbolAVL {

private:

    NodoAVL* crearNodo(Student e) {

        NodoAVL* nuevo = new NodoAVL;

        nuevo->dato = e;

        nuevo->izquierdo = NULL;
        nuevo->derecho = NULL;

        nuevo->altura = 1;

        return nuevo;
    }

    int alturaNodo(NodoAVL* n) {

        if (n == NULL)
            return 0;

        return n->altura;
    }

    int balance(NodoAVL* n) {

        if (n == NULL)
            return 0;

        return alturaNodo(n->izquierdo)
             - alturaNodo(n->derecho);
    }

    bool menor(Student a, Student b) {

        if (a.skill_score == b.skill_score)
            return a.student_id < b.student_id;

        return a.skill_score < b.skill_score;
    }

    NodoAVL* rotarDerecha(NodoAVL* y) {

        NodoAVL* x = y->izquierdo;

        NodoAVL* t = x->derecho;

        x->derecho = y;

        y->izquierdo = t;

        y->altura =
        max(
        alturaNodo(y->izquierdo),
        alturaNodo(y->derecho)
        ) + 1;

        x->altura =
        max(
        alturaNodo(x->izquierdo),
        alturaNodo(x->derecho)
        ) + 1;

        return x;
    }

    NodoAVL* rotarIzquierda(NodoAVL* x) {

        NodoAVL* y = x->derecho;

        NodoAVL* t = y->izquierdo;

        y->izquierdo = x;

        x->derecho = t;

        x->altura =
        max(
        alturaNodo(x->izquierdo),
        alturaNodo(x->derecho)
        ) + 1;

        y->altura =
        max(
        alturaNodo(y->izquierdo),
        alturaNodo(y->derecho)
        ) + 1;

        return y;
    }

    NodoAVL* insertar(NodoAVL* raiz, Student e) {

        if (raiz == NULL)
            return crearNodo(e);

        if (menor(e, raiz->dato))
            raiz->izquierdo = insertar(raiz->izquierdo, e);

        else if (menor(raiz->dato, e))
            raiz->derecho = insertar(raiz->derecho, e);

        else
            return raiz;

        raiz->altura =
        1 + max(
        alturaNodo(raiz->izquierdo),
        alturaNodo(raiz->derecho)
        );

        int b = balance(raiz);

        if (b > 1 && menor(e, raiz->izquierdo->dato))
            return rotarDerecha(raiz);

        if (b < -1 && menor(raiz->derecho->dato, e))
            return rotarIzquierda(raiz);

        if (b > 1 && menor(raiz->izquierdo->dato, e)) {

            raiz->izquierdo =
            rotarIzquierda(raiz->izquierdo);

            return rotarDerecha(raiz);
        }

        if (b < -1 && menor(e, raiz->derecho->dato)) {

            raiz->derecho =
            rotarDerecha(raiz->derecho);

            return rotarIzquierda(raiz);
        }

        return raiz;
    }

    void inOrden(NodoAVL* raiz, int &contador) {

        if (raiz != NULL) {

            inOrden(raiz->izquierdo, contador);

            cout
            << contador
            << ". "
            << raiz->dato.full_name
            << " - "
            << raiz->dato.skill_score
            << endl;

            contador++;

            inOrden(raiz->derecho, contador);
        }
    }

public:

    NodoAVL* raiz;

    int cantidad;

    ArbolAVL() {

        raiz = NULL;

        cantidad = 0;
    }

    void insertarEstudiante(Student e) {

        raiz = insertar(raiz, e);

        cantidad++;
    }

    void eliminarEstudiante(int id) {

        cout << "AVL reconstruible despues de eliminacion\n";
    }

    void benchmarkAVL(Student e) {

        ofstream archivo("cpp_results.csv", ios::app);

        auto inicioInsert = high_resolution_clock::now();

        insertarEstudiante(e);

        auto finInsert = high_resolution_clock::now();

        archivo
        << "Insercion AVL,"
        << duration_cast<microseconds>(finInsert - inicioInsert).count()
        << "\n";

        auto inicioRecorrido = high_resolution_clock::now();

        int c = 1;

        inOrden(raiz, c);

        auto finRecorrido = high_resolution_clock::now();

        archivo
        << "Recorrido AVL,"
        << duration_cast<microseconds>(finRecorrido - inicioRecorrido).count()
        << "\n";

        archivo.close();
    }

    void mostrarRanking() {

        if (raiz == NULL) {

            cout << "AVL vacio\n";
        }

        else {

            int contador = 1;

            cout << "\n===== RANKING =====\n";

            inOrden(raiz, contador);
        }
    }

    void mostrarEstadisticas() {

        cout << "\n===== AVL =====\n";

        cout << "Altura: "
             << alturaNodo(raiz)
             << endl;

        cout << "Nodos: "
             << cantidad
             << endl;
    }
};

Student crearStudent() {

    Student e;

    cout << "Student ID: ";
    cin >> e.student_id;

    cin.ignore();

    cout << "Nombre completo: ";
    getline(cin, e.full_name);

    cout << "Carrera: ";
    getline(cin, e.career);

    cout << "Semestre: ";
    cin >> e.semester;

    cout << "GPA: ";
    cin >> e.gpa;

    cout << "Skill Score: ";
    cin >> e.skill_score;

    e.proyectos = NULL;
    e.conexiones = NULL;

    return e;
}

int main() {

    TablaHash tabla(10);

    ArbolAVL avl;

    PilaAcciones pila;

    tabla.cargarDatosGuardados();

    int opcion;

    cout << "===== SISTEMA ACADEMICO =====\n";

    do {

        cout << "\n===== MENU =====\n";

        cout << "1. Cargar CSV\n";
        cout << "2. Registrar estudiante\n";
        cout << "3. Buscar estudiante\n";
        cout << "4. Eliminar estudiante\n";
        cout << "5. Agregar proyecto\n";
        cout << "6. Mostrar proyectos\n";
        cout << "7. Buscar proyecto\n";
        cout << "8. Eliminar proyecto\n";
        cout << "9. Conectar estudiantes\n";
        cout << "10. Verificar conexion\n";
        cout << "11. Mostrar conexiones\n";
        cout << "12. BFS\n";
        cout << "13. DFS\n";
        cout << "14. Mostrar tabla\n";
        cout << "15. Ranking AVL\n";
        cout << "16. Estadisticas\n";
        cout << "17. Historial\n";
        cout << "18. Guardar persistencia\n";
        cout << "19. Benchmark completo\n";
        cout << "20. Salir\n";

        cout << "Seleccione: ";
        cin >> opcion;

        switch(opcion) {

case 1: {

    string archivo;

    cout << "Archivo CSV: ";
    cin >> archivo;

    auto inicio = high_resolution_clock::now();

    ifstream archivoCSV(archivo);

    if (!archivoCSV) {

        cout << "Error al abrir archivo\n";

        break;
    }

    string linea;

    getline(archivoCSV, linea);

    while (getline(archivoCSV, linea)) {

        stringstream ss(linea);

        string dato;

        Student e;

        getline(ss, dato, ',');
        e.student_id = stoi(dato);

        getline(ss, e.full_name, ',');

        getline(ss, e.career, ',');

        getline(ss, dato, ',');
        e.semester = stoi(dato);

        getline(ss, dato, ',');
        e.gpa = stof(dato);

        getline(ss, dato, ',');
        e.skill_score = stoi(dato);

        e.proyectos = NULL;
        e.conexiones = NULL;

        tabla.insertar(e);

        avl.insertarEstudiante(e);
    }

    archivoCSV.close();

    auto fin = high_resolution_clock::now();

    auto duracion =
    duration_cast<milliseconds>(fin - inicio);

    cout << "CSV cargado correctamente\n";

    cout << "Tiempo de carga: "
         << duracion.count()
         << " ms\n";

    pila.push("CSV cargado y AVL actualizado");

    break;
}

case 2: {

    Student e = crearStudent();

    tabla.insertar(e);

    avl.insertarEstudiante(e);

    pila.push("Estudiante registrado");

    break;
}

case 3: {

    int id;

    cout << "ID: ";
    cin >> id;

    tabla.buscar(id);

    pila.push("Busqueda realizada");

    break;
}

case 4: {

    int id;

    cout << "ID: ";
    cin >> id;

    tabla.eliminar(id);

    avl.eliminarEstudiante(id);

    pila.push("Estudiante eliminado");

    break;
}

case 5: {

    int id;

    cout << "ID estudiante: ";
    cin >> id;

    tabla.agregarProyecto(id);

    pila.push("Proyecto agregado");

    break;
}

case 6: {

    int id;

    cout << "ID estudiante: ";
    cin >> id;

    tabla.mostrarProyectos(id);

    pila.push("Consulta proyectos");

    break;
}

case 7: {

    int sid;
    int pid;

    cout << "Student ID: ";
    cin >> sid;

    cout << "Project ID: ";
    cin >> pid;

    tabla.buscarProyecto(sid, pid);

    pila.push("Busqueda proyecto");

    break;
}

case 8: {

    int sid;
    int pid;

    cout << "Student ID: ";
    cin >> sid;

    cout << "Project ID: ";
    cin >> pid;

    tabla.eliminarProyecto(sid, pid);

    pila.push("Proyecto eliminado");

    break;
}

case 9: {

    int id1;
    int id2;

    cout << "ID 1: ";
    cin >> id1;

    cout << "ID 2: ";
    cin >> id2;

    tabla.conectarEstudiantes(id1, id2);

    pila.push("Conexion realizada");

    break;
}

case 10: {

    int id1;
    int id2;

    cout << "ID 1: ";
    cin >> id1;

    cout << "ID 2: ";
    cin >> id2;

    if (tabla.estanConectados(id1, id2)) {

        cout << "SI conectados\n";
    }

    else {

        cout << "NO conectados\n";
    }

    pila.push("Verificacion conexion");

    break;
}

case 11: {

    int id;

    cout << "ID: ";
    cin >> id;

    tabla.mostrarConexiones(id);

    pila.push("Mostrar conexiones");

    break;
}

case 12: {

    int inicio;

    cout << "Inicio BFS: ";
    cin >> inicio;

    if (!tabla.existe(inicio)) {

        cout << "Estudiante no existe\n";

        break;
    }

    tabla.BFS(inicio);

    pila.push("Recorrido BFS");

    break;
}

case 13: {

    int inicio;

    cout << "Inicio DFS: ";
    cin >> inicio;

    if (!tabla.existe(inicio)) {

        cout << "Estudiante no existe\n";

        break;
    }

    tabla.DFS(inicio);

    pila.push("Recorrido DFS");

    break;
}

case 14:

    tabla.mostrarTabla();

    pila.push("Tabla hash mostrada");

    break;

case 15:

    avl.mostrarRanking();

    pila.push("Ranking AVL mostrado");

    break;

case 16:

    tabla.mostrarEstadisticas();

    avl.mostrarEstadisticas();

    pila.push("Estadisticas mostradas");

    break;

case 17:

    pila.mostrarHistorial();

    break;

case 18:

    tabla.guardarDatos();

    pila.push("Persistencia guardada");

    break;

case 19: {

    tabla.benchmarkCompleto();

    Student e;

    e.student_id = 8888;
    e.full_name = "AVL";
    e.career = "Systems";
    e.semester = 1;
    e.gpa = 90;
    e.skill_score = 90;
    e.proyectos = NULL;
    e.conexiones = NULL;

    avl.benchmarkAVL(e);

    pila.push("Benchmark ejecutado");

    break;
}

case 20:

    tabla.guardarDatos();

    cout << "Saliendo...\n";

    break;

default:

    cout << "Opcion invalida\n";
        }

    } while (opcion != 20);

    return 0;
}