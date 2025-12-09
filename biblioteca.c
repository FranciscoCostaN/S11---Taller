#include "biblioteca.h"


void convertirMinusculas(const char *origen, char *destino) {
    int i = 0;
    while (origen[i] != '\0') {
        // En ASCII, 'A' es 65 y 'a' es 97. La diferencia es 32.
        if (origen[i] >= 'A' && origen[i] <= 'Z') {
            destino[i] = origen[i] + 32; //Convertir a minuscula
        } else {
            destino[i] = origen[i];// Dejar igual
        }
        i++;
    }
    destino[i] = '\0';
}

int leerEntero(const char* mensaje) {
    char buffer[100];
    int numero;
    int valido = 0;

    do {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0) continue;

        int esNumero = 1;
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] < '0' || buffer[i] > '9') {
                esNumero = 0;
                break;
            }
        }

        if (esNumero) {
            sscanf(buffer, "%d", &numero);
            valido = 1;
        } else {
            printf("[ERROR] Debe ingresar solo numeros enteros.\n");
        }
    } while (!valido);

    return numero;
}

void leerCadena(const char* mensaje, char* destino, int longitud, int permitirNumeros) {
    char buffer[200];
    int valido = 0;

    do {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0) continue;
        
        if (strlen(buffer) >= longitud) {
            printf("[ERROR] Texto muy largo. Maximo %d caracteres.\n", longitud - 1);
            continue;
        }

        int tieneNumeros = 0;
        if (!permitirNumeros) {
            for (int i = 0; buffer[i] != '\0'; i++) {
                if (buffer[i] >= '0' && buffer[i] <= '9') {
                    tieneNumeros = 1;
                    break;
                }
            }
        }

        if (tieneNumeros) {
            printf("[ERROR] Este campo no debe contener numeros.\n");
        } else {
            strcpy(destino, buffer);
            valido = 1;
        }
    } while (!valido);
}

void registrarLibro(Libro biblioteca[], int *cantidad) {
    if (*cantidad >= MAX_LIBROS) {
        printf("\n[ERROR] La biblioteca esta llena (Max 10 libros).\n");
        return;
    }

    Libro nuevoLibro;
    int idUnico = 0;

    printf("\n--- REGISTRAR NUEVO LIBRO ---\n");
    
    do {
        idUnico = 1;
        nuevoLibro.id = leerEntero("Ingrese ID del libro: ");

        for (int i = 0; i < *cantidad; i++) {
            if (biblioteca[i].id == nuevoLibro.id) {
                printf("[ERROR] Ya existe un libro con ese ID. Intente otro.\n");
                idUnico = 0;
                break;
            }
        }
    } while (idUnico == 0);

    leerCadena("Ingrese Titulo: ", nuevoLibro.titulo, 100, 1);
    leerCadena("Ingrese Autor: ", nuevoLibro.autor, 50, 0);

    do {
        nuevoLibro.anio = leerEntero("Ingrese Anio de publicacion (1000-2026): ");
        if (nuevoLibro.anio < 1000 || nuevoLibro.anio > 2026) {
            printf("[ERROR] Anio invalido. Debe estar entre 1000 y 2026.\n");
        }
    } while (nuevoLibro.anio < 1000 || nuevoLibro.anio > 2026);

    strcpy(nuevoLibro.estado, "Disponible");

    biblioteca[*cantidad] = nuevoLibro;
    (*cantidad)++; 

    printf("\n[EXITO] Libro registrado correctamente.\n");
}

void mostrarLibros(Libro biblioteca[], int cantidad) {
    if (cantidad == 0) {
        printf("\n[AVISO] No hay libros registrados.\n");
        return;
    }

    printf("\n--- LISTA DE LIBROS ---\n");
    printf("%-5s %-30s %-20s %-6s %-12s\n", "ID", "TITULO", "AUTOR", "ANIO", "ESTADO");
    printf("------------------------------------------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        printf("%-5d %-30s %-20s %-6d %-12s\n", 
            biblioteca[i].id, 
            biblioteca[i].titulo, 
            biblioteca[i].autor, 
            biblioteca[i].anio, 
            biblioteca[i].estado);
    }
}

void buscarLibro(Libro biblioteca[], int cantidad) {
    if (cantidad == 0) {
        printf("\n[AVISO] No hay libros para buscar.\n");
        return;
    }

    printf("\n--- BUSCAR LIBRO ---\n");
    printf("1. Buscar por ID\n");
    printf("2. Buscar por Titulo\n");
    
    int opcion = leerEntero("Seleccione una opcion: ");
    int encontrado = 0;

    if (opcion == 1) {
        int idBusq = leerEntero("Ingrese el ID a buscar: ");
        for (int i = 0; i < cantidad; i++) {
            if (biblioteca[i].id == idBusq) {
                printf("\n[ENCONTRADO] ID: %d | Titulo: %s | Autor: %s | Estado: %s\n", 
                    biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autor, biblioteca[i].estado);
                encontrado = 1;
                break;
            }
        }
    } else if (opcion == 2) {
        char tituloBusq[100];
        leerCadena("Ingrese el Titulo (o parte del titulo) a buscar: ", tituloBusq, 100, 1);

        char busquedaLower[100];
        char tituloLibroLower[100];

        convertirMinusculas(tituloBusq, busquedaLower);

        for (int i = 0; i < cantidad; i++) {
            convertirMinusculas(biblioteca[i].titulo, tituloLibroLower);

            if (strstr(tituloLibroLower, busquedaLower) != NULL) {
                printf("\n[ENCONTRADO] ID: %d | Titulo: %s | Autor: %s | Estado: %s\n", 
                    biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autor, biblioteca[i].estado);
                encontrado = 1;
            }
        }
    } else {
        printf("Opcion invalida.\n");
    }

    if (!encontrado && (opcion == 1 || opcion == 2)) {
        printf("\n[INFO] No se encontro ningun libro con esa informacion.\n");
    }
}

void actualizarEstado(Libro biblioteca[], int cantidad) {
    printf("\n--- ACTUALIZAR ESTADO ---\n");
    int idBusq = leerEntero("Ingrese el ID del libro: ");
    int encontrado = 0;

    for (int i = 0; i < cantidad; i++) {
        if (biblioteca[i].id == idBusq) {
            encontrado = 1;
            if (strcmp(biblioteca[i].estado, "Disponible") == 0) {
                strcpy(biblioteca[i].estado, "Prestado");
                printf("\n[ACTUALIZADO] Libro marcado como PRESTADO.\n");
            } else {
                strcpy(biblioteca[i].estado, "Disponible");
                printf("\n[ACTUALIZADO] Libro marcado como DISPONIBLE.\n");
            }
            break;
        }
    }

    if (!encontrado) {
        printf("[ERROR] Libro no encontrado.\n");
    }
}

void eliminarLibro(Libro biblioteca[], int *cantidad) {
    printf("\n--- ELIMINAR LIBRO ---\n");
    int idBusq = leerEntero("Ingrese el ID del libro a eliminar: ");
    int encontrado = 0;

    for (int i = 0; i < *cantidad; i++) {
        if (biblioteca[i].id == idBusq) {
            encontrado = 1;
            for (int j = i; j < *cantidad - 1; j++) {
                biblioteca[j] = biblioteca[j + 1];
            }
            (*cantidad)--; 
            printf("\n[EXITO] Libro eliminado correctamente.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("[ERROR] No se encontro el ID para eliminar.\n");
    }
}