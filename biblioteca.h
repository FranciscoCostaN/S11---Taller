#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <string.h>

#define MAX_LIBROS 10

typedef struct {
    int id;
    char titulo[100];
    char autor[50];
    int anio;
    char estado[15];
} Libro;

// Funciones principales
void registrarLibro(Libro biblioteca[], int *cantidad);
void mostrarLibros(Libro biblioteca[], int cantidad);
void buscarLibro(Libro biblioteca[], int cantidad);
void actualizarEstado(Libro biblioteca[], int cantidad);
void eliminarLibro(Libro biblioteca[], int *cantidad);

// Funciones auxiliares
int leerEntero(const char* mensaje);
void leerCadena(const char* mensaje, char* destino, int longitud, int permitirNumeros);

#endif