import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.TreeMap;

public class BenchmarkJava {

    private ArrayList<Student> estudiantes;

    private double tiempoHashInsert;
    private double tiempoHashSearch;

    private double tiempoTreeInsert;
    private double tiempoTreeTraversal;

    public BenchmarkJava() {

        estudiantes = new ArrayList<>();

        tiempoHashInsert = 0;
        tiempoHashSearch = 0;

        tiempoTreeInsert = 0;
        tiempoTreeTraversal = 0;
    }

    public int totalEstudiantes() {

        return estudiantes.size();
    }

    public void cargarCSV(String archivoCSV) {

        try {

            BufferedReader archivo =
                    new BufferedReader(
                            new FileReader(archivoCSV));

            String linea;

            archivo.readLine();

            int cargados = 0;

            while ((linea = archivo.readLine()) != null) {

                String[] datos = linea.split(",");

                if (datos.length < 6) {
                    continue;
                }

                Student e = new Student(

                        Integer.parseInt(datos[0].trim()),
                        datos[1].trim(),
                        datos[2].trim(),
                        Integer.parseInt(datos[3].trim()),
                        Double.parseDouble(datos[4].trim()),
                        Integer.parseInt(datos[5].trim())
                );

                estudiantes.add(e);

                cargados++;
            }

            archivo.close();

            System.out.println();
            System.out.println("CSV cargado correctamente");
            System.out.println("Registros cargados: " + cargados);

        }

        catch (Exception e) {

            System.out.println("Error cargando CSV");
            e.printStackTrace();
        }
    }

    public void mostrarPrimerosRegistros() {

        if (estudiantes.isEmpty()) {

            System.out.println("No hay estudiantes cargados");
            return;
        }

        int limite = Math.min(10, estudiantes.size());

        System.out.println();
        System.out.println("===== MUESTRA DE ESTUDIANTES =====");

        for (int i = 0; i < limite; i++) {

            System.out.println(estudiantes.get(i));
        }
    }

    public void guardarPersistencia() {

        try {

            PrintWriter archivo =
                    new PrintWriter(
                            new FileWriter(
                                    "students_backup.csv"));

            archivo.println(
                    "student_id,full_name,career,semester,gpa,skill_score");

            for (Student e : estudiantes) {

                archivo.println(

                        e.student_id + "," +
                                e.full_name + "," +
                                e.career + "," +
                                e.semester + "," +
                                e.gpa + "," +
                                e.skill_score
                );
            }

            archivo.close();

            System.out.println();
            System.out.println("Persistencia guardada");
            System.out.println("Archivo: students_backup.csv");
        }

        catch (Exception e) {

            System.out.println("Error guardando persistencia");
        }
    }

    public void cargarPersistencia() {

        estudiantes.clear();

        try {

            BufferedReader archivo =
                    new BufferedReader(
                            new FileReader(
                                    "students_backup.csv"));

            String linea;

            archivo.readLine();

            while ((linea = archivo.readLine()) != null) {

                String[] datos = linea.split(",");

                Student e = new Student(

                        Integer.parseInt(datos[0]),
                        datos[1],
                        datos[2],
                        Integer.parseInt(datos[3]),
                        Double.parseDouble(datos[4]),
                        Integer.parseInt(datos[5])
                );

                estudiantes.add(e);
            }

            archivo.close();

            System.out.println();
            System.out.println("Persistencia restaurada");
            System.out.println(
                    "Registros restaurados: "
                            + estudiantes.size());
        }

        catch (Exception e) {

            System.out.println("No existe students_backup.csv");
        }
    }

    public void completarHasta10000() {

        if (estudiantes.isEmpty()) {

            System.out.println("Primero cargue el CSV");
            return;
        }

        int actual = estudiantes.size();

        int nuevoID = 500000;

        while (estudiantes.size() < 10000) {

            Student base =
                    estudiantes.get(
                            estudiantes.size() % actual);

            Student copia = new Student(

                    nuevoID++,

                    base.full_name,

                    base.career,

                    base.semester,

                    base.gpa,

                    base.skill_score
            );

            estudiantes.add(copia);
        }

        System.out.println();
        System.out.println(
                "Dataset preparado con "
                        + estudiantes.size()
                        + " registros");
    }
    public void mostrarEstadisticas() {

        System.out.println();
        System.out.println("===== ESTADISTICAS =====");

        System.out.println(
                "Total estudiantes: "
                        + estudiantes.size());

        System.out.println(
                "HashMap Insert: "
                        + tiempoHashInsert
                        + " ms");

        System.out.println(
                "HashMap Search: "
                        + tiempoHashSearch
                        + " ms");

        System.out.println(
                "TreeMap Insert: "
                        + tiempoTreeInsert
                        + " ms");

        System.out.println(
                "TreeMap Traversal: "
                        + tiempoTreeTraversal
                        + " ms");
    }

    public void generarBenchmark() {

        if (estudiantes.isEmpty()) {

            System.out.println(
                    "Primero cargue estudiantes");

            return;
        }

        try {

            HashMap<Integer, Student> hash =
                    new HashMap<>();

            long inicioHashInsert =
                    System.nanoTime();

            for (Student e : estudiantes) {

                hash.put(
                        e.student_id,
                        e
                );
            }

            long finHashInsert =
                    System.nanoTime();

            tiempoHashInsert =

                    (finHashInsert
                            - inicioHashInsert)

                            / 1000000.0;

            long inicioHashSearch =
                    System.nanoTime();

            for (Student e : estudiantes) {

                hash.get(
                        e.student_id
                );
            }

            long finHashSearch =
                    System.nanoTime();

            tiempoHashSearch =

                    (finHashSearch
                            - inicioHashSearch)

                            / 1000000.0;

            TreeMap<Integer, Student> tree =
                    new TreeMap<>();

            long inicioTreeInsert =
                    System.nanoTime();

            for (Student e : estudiantes) {

                tree.put(
                        e.student_id,
                        e
                );
            }

            long finTreeInsert =
                    System.nanoTime();

            tiempoTreeInsert =

                    (finTreeInsert
                            - inicioTreeInsert)

                            / 1000000.0;

            long inicioTraversal =
                    System.nanoTime();

            for (Student e : tree.values()) {

                int temporal =
                        e.student_id;
            }

            long finTraversal =
                    System.nanoTime();

            tiempoTreeTraversal =

                    (finTraversal
                            - inicioTraversal)

                            / 1000000.0;

            generarCSV();

            System.out.println();
            System.out.println(
                    "Benchmark ejecutado correctamente");
        }

        catch (Exception e) {

            System.out.println(
                    "Error ejecutando benchmark");

            e.printStackTrace();
        }
    }

    private void generarCSV() {

        try {

            PrintWriter archivo =
                    new PrintWriter(
                            new FileWriter(
                                    "java_results.csv"));

            archivo.println(
                    "language,operation,structure,records,time_ms");

            archivo.println(

                    "Java,insert,HashMap,"
                            + estudiantes.size()
                            + ","
                            + tiempoHashInsert
            );

            archivo.println(

                    "Java,search,HashMap,"
                            + estudiantes.size()
                            + ","
                            + tiempoHashSearch
            );

            archivo.println(

                    "Java,insert,TreeMap,"
                            + estudiantes.size()
                            + ","
                            + tiempoTreeInsert
            );

            archivo.println(

                    "Java,traversal,TreeMap,"
                            + estudiantes.size()
                            + ","
                            + tiempoTreeTraversal
            );

            archivo.close();

            System.out.println();
            System.out.println(
                    "Archivo java_results.csv generado");
        }

        catch (Exception e) {

            System.out.println(
                    "Error generando CSV");
        }
    }

    public void mostrarMenu() {

        System.out.println();
        System.out.println(
                "===== BENCHMARK JAVA =====");

        System.out.println(
                "1. Cargar CSV");

        System.out.println(
                "2. Mostrar estudiantes");

        System.out.println(
                "3. Completar hasta 10000 registros");

        System.out.println(
                "4. Ejecutar benchmark");

        System.out.println(
                "5. Mostrar estadisticas");

        System.out.println(
                "6. Guardar persistencia");

        System.out.println(
                "7. Restaurar persistencia");

        System.out.println(
                "8. Salir");
    }
}