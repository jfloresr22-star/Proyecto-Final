#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

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

class TablaHash {

private:

    Nodo** tabla;
    int tamanio;

public:

    int cantidad;
    int colisiones;

    TablaHash(int t) {

        tamanio = t;
        cantidad = 0;
        colisiones = 0;

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

    void insertar(Student e) {

        if (existe(e.student_id)) {

            cout << "Estudiante duplicado\n";

            return;
        }

        int indice = funcionHash(e.student_id);

        Nodo* nuevo = new Nodo;

        nuevo->dato = e;
        nuevo->siguiente = NULL;

        if (tabla[indice] != NULL) {

            colisiones++;
        }

        nuevo->siguiente = tabla[indice];

        tabla[indice] = nuevo;

        cantidad++;

        cout << "Estudiante insertado\n";
    }

    void buscar(int id) {

        int indice = funcionHash(id);

        Nodo* aux = tabla[indice];

        while (aux != NULL) {

            if (aux->dato.student_id == id) {

                cout << "\n===== ESTUDIANTE ENCONTRADO =====\n";

                cout << "ID: " << aux->dato.student_id << endl;
                cout << "Nombre: " << aux->dato.full_name << endl;
                cout << "Carrera: " << aux->dato.career << endl;
                cout << "Semestre: " << aux->dato.semester << endl;
                cout << "GPA: " << aux->dato.gpa << endl;
                cout << "Skill Score: " << aux->dato.skill_score << endl;

                return;
            }

            aux = aux->siguiente;
        }

        cout << "Estudiante no encontrado\n";
    }

    void eliminar(int id) {

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

                cout << "Estudiante eliminado\n";

                return;
            }

            anterior = aux;
            aux = aux->siguiente;
        }

        cout << "Estudiante no encontrado\n";
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

            cout << "NULL\n";
        }
    }

    void mostrarEstadisticas() {

        cout << "\n===== ESTADISTICAS HASH =====\n";

        cout << "Cantidad de estudiantes: " << cantidad << endl;

        cout << "Colisiones generadas: " << colisiones << endl;

        float factor = (float)cantidad / tamanio;

        cout << "Factor de carga: " << factor << endl;
    }

    void cargarCSV(string nombreArchivo) {

        ifstream archivo(nombreArchivo);

        if (!archivo) {

            cout << "Error al abrir archivo\n";

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

        cout << "Archivo CSV cargado correctamente\n";
    }

    void agregarProyecto(int id) {

        int indice = funcionHash(id);

        Nodo* aux = tabla[indice];

        while (aux != NULL) {

            if (aux->dato.student_id == id) {

                Proyecto* nuevo = new Proyecto;

                cout << "Project ID: ";
                cin >> nuevo->project_id;

                cin.ignore();

                cout << "Titulo: ";
                getline(cin, nuevo->title);

                cout << "Descripcion: ";
                getline(cin, nuevo->description);

                cout << "Anio: ";
                cin >> nuevo->completion_year;

                nuevo->siguiente = aux->dato.proyectos;

                aux->dato.proyectos = nuevo;

                cout << "Proyecto agregado\n";

                return;
            }

            aux = aux->siguiente;
        }

        cout << "Estudiante no encontrado\n";
    }

    void mostrarProyectos(int id) {

        int indice = funcionHash(id);

        Nodo* aux = tabla[indice];

        while (aux != NULL) {

            if (aux->dato.student_id == id) {

                Proyecto* p = aux->dato.proyectos;

                while (p != NULL) {

                    cout << "\nProject ID: " << p->project_id << endl;
                    cout << "Titulo: " << p->title << endl;
                    cout << "Descripcion: " << p->description << endl;
                    cout << "Anio: " << p->completion_year << endl;

                    p = p->siguiente;
                }

                return;
            }

            aux = aux->siguiente;
        }

        cout << "Estudiante no encontrado\n";
    }
};

struct NodoAVL {

    Student dato;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;
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

        return alturaNodo(n->izquierdo) - alturaNodo(n->derecho);
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

        y->altura = max(alturaNodo(y->izquierdo), alturaNodo(y->derecho)) + 1;
        x->altura = max(alturaNodo(x->izquierdo), alturaNodo(x->derecho)) + 1;

        return x;
    }

    NodoAVL* rotarIzquierda(NodoAVL* x) {

        NodoAVL* y = x->derecho;
        NodoAVL* t = y->izquierdo;

        y->izquierdo = x;
        x->derecho = t;

        x->altura = max(alturaNodo(x->izquierdo), alturaNodo(x->derecho)) + 1;
        y->altura = max(alturaNodo(y->izquierdo), alturaNodo(y->derecho)) + 1;

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

        raiz->altura = 1 + max(alturaNodo(raiz->izquierdo), alturaNodo(raiz->derecho));

        int b = balance(raiz);

        if (b > 1 && menor(e, raiz->izquierdo->dato))
            return rotarDerecha(raiz);

        if (b < -1 && menor(raiz->derecho->dato, e))
            return rotarIzquierda(raiz);

        if (b > 1 && menor(raiz->izquierdo->dato, e)) {

            raiz->izquierdo = rotarIzquierda(raiz->izquierdo);

            return rotarDerecha(raiz);
        }

        if (b < -1 && menor(e, raiz->derecho->dato)) {

            raiz->derecho = rotarDerecha(raiz->derecho);

            return rotarIzquierda(raiz);
        }

        return raiz;
    }

    void inOrden(NodoAVL* raiz, int &contador) {

        if (raiz != NULL) {

            inOrden(raiz->izquierdo, contador);

            cout << contador << ". "
                 << raiz->dato.full_name
                 << " - Score: "
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

    void mostrarRanking() {

        if (raiz == NULL) {

            cout << "Arbol vacio\n";
        }

        else {

            int contador = 1;

            cout << "\n===== RANKING ACADEMICO =====\n";

            inOrden(raiz, contador);
        }
    }

    void mostrarEstadisticas() {

        cout << "\n===== ESTADISTICAS AVL =====\n";

        cout << "Altura del arbol: " << alturaNodo(raiz) << endl;

        cout << "Cantidad de nodos insertados: " << cantidad << endl;
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

    int opcion;

    cout << "Nombre: Josue David Flores Roldan\n";
    cout << "Carnet: 9941 24 7857\n";

    do {

        cout << "\n===== MENU =====\n";

        cout << "1. Cargar archivo CSV\n";
        cout << "2. Registrar estudiante manualmente\n";
        cout << "3. Buscar estudiante por ID\n";
        cout << "4. Eliminar estudiante\n";
        cout << "5. Agregar proyecto a estudiante\n";
        cout << "6. Mostrar proyectos de estudiante\n";
        cout << "7. Mostrar tabla hash\n";
        cout << "8. Mostrar ranking academico\n";
        cout << "9. Mostrar estadisticas\n";
        cout << "10. Salir\n";

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 1: {

                string archivo;

                cout << "Ingrese nombre del archivo CSV: ";
                cin >> archivo;

                tabla.cargarCSV(archivo);

                break;
            }

            case 2: {

                Student e = crearStudent();

                tabla.insertar(e);

                avl.insertarEstudiante(e);

                break;
            }

            case 3: {

                int id;

                cout << "Ingrese student_id: ";
                cin >> id;

                tabla.buscar(id);

                break;
            }

            case 4: {

                int id;

                cout << "Ingrese student_id: ";
                cin >> id;

                tabla.eliminar(id);

                break;
            }

            case 5: {

                int id;

                cout << "Ingrese student_id: ";
                cin >> id;

                tabla.agregarProyecto(id);

                break;
            }

            case 6: {

                int id;

                cout << "Ingrese student_id: ";
                cin >> id;

                tabla.mostrarProyectos(id);

                break;
            }

            case 7:

                tabla.mostrarTabla();

                break;

            case 8:

                avl.mostrarRanking();

                break;

            case 9:

                tabla.mostrarEstadisticas();

                avl.mostrarEstadisticas();

                break;

            case 10:

                cout << "Saliendo...\n";

                break;

            default:

                cout << "Opcion invalida\n";
        }

    } while (opcion != 10);

    return 0;
}