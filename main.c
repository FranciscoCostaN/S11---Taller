#include "biblioteca.h"

int main() {
    Libro libros[MAX_LIBROS];
    int cantidadLibros = 0;
    int opcion;

    do {
        printf("\n=== GESTION DE BIBLIOTECA ===\n");
        printf("1. Registrar Libro\n");
        printf("2. Mostrar Lista de Libros\n");
        printf("3. Buscar Libro\n");
        printf("4. Actualizar Estado (Prestar/Devolver)\n");
        printf("5. Eliminar Libro\n");
        printf("6. Salir\n");
        
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1:
                registrarLibro(libros, &cantidadLibros);
                break;
            case 2:
                mostrarLibros(libros, cantidadLibros);
                break;
            case 3:
                buscarLibro(libros, cantidadLibros);
                break;
            case 4:
                actualizarEstado(libros, cantidadLibros);
                break;
            case 5:
                eliminarLibro(libros, &cantidadLibros);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }

    } while (opcion != 6);

    return 0;
}