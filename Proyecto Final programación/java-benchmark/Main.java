import java.util.Scanner;

public class Main {

  public static void main(String[] args) {

    BenchmarkJava sistema =
            new BenchmarkJava();

    Scanner entrada =
            new Scanner(System.in);

    int opcion;

    do {

      sistema.mostrarMenu();

      System.out.print(
              "\nSeleccione: ");

      opcion =
              entrada.nextInt();

      entrada.nextLine();

      switch (opcion) {

        case 1:

          System.out.print(
                  "Ruta CSV: ");

          String archivo =
                  entrada.nextLine();

          sistema.cargarCSV(
                  archivo);

          break;

        case 2:

          sistema.mostrarPrimerosRegistros();

          break;

        case 3:

          sistema.completarHasta10000();

          break;

        case 4:

          sistema.generarBenchmark();

          break;

        case 5:

          sistema.mostrarEstadisticas();

          break;

        case 6:

          sistema.guardarPersistencia();

          break;

        case 7:

          sistema.cargarPersistencia();

          break;

        case 8:

          System.out.println(
                  "\nSaliendo...");

          break;

        default:

          System.out.println(
                  "Opcion invalida");
      }

    } while (opcion != 8);
  }
}