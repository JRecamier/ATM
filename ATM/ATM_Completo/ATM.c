#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "ATM.h"

//prototipos de funciones
void menu();
float depositar(float D, struct ATM Personas[]);
float balance(float B, float Mov[]);
float retirar(float R);
int cuenta(int a);
char PIN(char nip[]);
void security(struct ATM Personas[]);
int valida(int X);
int buscarCuenta(struct ATM personas[], int tam, char nombre[]);
float historial(float Mov[], float accion);
float guardar_saldo(struct ATM Personas[]);
void guardar_clientes(struct ATM Personas[]);




//funcion principal
int main()
{
    printf("Bienvenid@ a Banco NoavaCash\n");
    menu();
    return 0;
}
