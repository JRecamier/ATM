#ifndef ATM_H_INCLUDED
#define ATM_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//struct
struct ATM{
    char Nombre[50];
    char Apellido[50];
    char NIP[5];
    float Saldo;
    int Nocuenta;
    float Movimiento[10];
} ;
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

void clear_screen() {
    int i;
    #ifdef _WIN32
        for (i = 2; i >= 1; i--) {
        printf("%d...", i);
        sleep(1);}
        system("cls");  // For Windows
    #else
        for (i = 2; i >= 1; i--) {
        printf("%d...", i);
        sleep(1);}
        system("clear"); // For Linux and macOS
    #endif
}


void menu()
{
    struct ATM Personas[100]={
    {"Emmanuel" ,"Esqueda","9823", 1000, 1,{1000}},
    {"Jesus" ,"Recamier", "2005", 1000000.24, 2, {1000000.24} },
    {"Oscar" ,"Estrada", "1234", 100.5, 3,{100.5}}
    };
    float accion;
    int i, j, opc, opc2, pin[3];
    char name[50], password[20]={"hardcodear"}, user[10]={"admin"}, password2[20], user2[10];

    do{
    //MENU DE OPCIONES//
    printf("\n----Cajero Automatico----\n");
    printf("1. Login \n");
    printf("2. Depositar.\n");
    printf("3. Buscar No de Cuenta.\n");
    printf("4. Crear Cuenta\n");
    printf("5. Salir del programa\n");
    printf("6. Guardar o Exportar\n");
    printf("Porfavor seleccione una opcion :)\n");
    scanf("%d", &opc);
    switch(opc)
    {
    case 1:
        security(Personas);
        do{
        printf("\n--Login--\n");
        printf("1. Consulta\n");
        printf("2. Retirar\n");
        printf("3. Salir\n");
        scanf("%d", &opc2);
        while (getchar() != '\n');
        switch (opc2)
        {
        case 1:
        clear_screen();
        balance(Personas[i].Saldo, Personas[i].Movimiento); //Llama a la función balance para checar el saldo y el historial
        break;
        case 2:
            clear_screen();
            do{
        accion= retirar(accion);
        if (Personas[i].Saldo>=accion)
        {

        Personas[i].Saldo= Personas[i].Saldo - accion;
        if(accion!=0){ //Esta condicion es por si el usuario se le ocurre retirar "$0" para que no de el mensaje de cantidad retirada valida
        printf("La cantidad retirada es valida...\n");}
        printf("Haz retirado %.2f \n", accion);
        printf("Tu nuevo saldo es %.2f \n", Personas[i].Saldo);
        historial(Personas[i].Movimiento, -accion);
        guardar_saldo(Personas);
        }
        else
        {
            printf("Error!! No puede retirar mas de lo que tiene en su cuenta.\n"); //En caso de que el usuario quiera retirar mas de lo permitido va amandar este "Error"
        }
        }while(Personas[i].Saldo < Personas[i].Saldo - accion);
        break;
        case 3:
        clear_screen();
            printf("¿Estas seguro de regresar?\n");
            printf("1. Si\n");
            printf("2. No\n");
            scanf("%d", &opc2);
            if(opc2==1)
            {
                menu();
            }
            break;
        default:
            printf("Por favor selecciona una opción valida");
            break;
        }
        }
        while(opc2!=3);

    case 2:
        clear_screen();
        accion= depositar(accion, Personas);
        Personas[i].Saldo= Personas[i].Saldo + accion; //Se asigna el valor de saldo despues de mandar a llamar a la funcion
        printf("Tu nuevo saldo es %.2f \n", Personas[i].Saldo); //imprime el saldo
        historial(Personas[i].Movimiento, accion);
        guardar_saldo(Personas);
        clear_screen();
        break;

    case 3:
        clear_screen();
        printf("Escribe tu nombre por favor (Empezando con mayuscula)\n");
        while (getchar() != '\n');
        gets(name);
        j=buscarCuenta(Personas, 100 ,name);
        if(j!=-1){
        printf("Tu numero de Cuenta es: %d\n", j);}
        else
        {
            printf("Por favor escribe bien el Nombre\n");
        }
        clear_screen();
        break;

    case 4:
        clear_screen();
        for(j=0; ;j++)
        {
            if(Personas[j].Nocuenta==0)
                break;
        }
        crear_cuenta(Personas, j);
        break;
    case 5:
        clear_screen();
        printf("Hasta luego!!\n");
        exit(0); //Esto cierra el programa si el usuario quiere salir
        break;
    case 6:
        clear_screen();
        printf("Por favor ingrese el usuario\n");
        while ((getchar()) != '\n');
        gets(user2);
        if(strcmp(user, user2)==0)
        {
            printf("Bienvenido Admin\n");
            do
            {
                printf("Ingrese la contrasena\n");
                gets(password2);
                if(strcmp(password, password2)==0)
                {
                    printf("Contrasena Correcta\n");
                    guardar_clientes(Personas);
                }
                else
                {
                    printf("Contrasena incorrecta\n");
                }
            } while(strcmp(password, password2)!=0);
        }
        else
        {
            printf("No existe tal usuario");
        }
        break;


    default:
        clear_screen();
        printf("Porfavor selecciona una opcion valida\n");
        break;
    }
    }while(opc=4);
}
int cuenta(int a)
{
    printf("Selecciona la cuenta por favor\n");
    printf("Cuenta 1.\nCuenta 2.\nCuenta 3.\n");
    scanf("%d", &a);
    a=a-1;
    while (getchar() != '\n'); //Aquí limpiamos el buffer para que no tengamos problemas con el gets() de char security(char nip[])
    return a;

}

float guardar_saldo(struct ATM Personas[]) //Funcion que lee el saldo
{
    int i, j;
    FILE*fp;
    fp=fopen("Clientes.txt", "w"); //Se abre en w para reescribir el saldo
    if(fp!= NULL)
    {

        for(i=0; i<=100; i++)
        {
            if(Personas[i].Nocuenta!=0)
            {
                fprintf(fp,"%s,", Personas[i].Nombre);
                fprintf(fp,"%s,", Personas[i].Apellido);
                fprintf(fp,"%d,", Personas[i].Nocuenta);
                fprintf(fp,"%s,", Personas[i].NIP);
                fprintf(fp,"%.2f,", Personas[i].Saldo);
                for(j=0; j<10; j++)
                {
                    fprintf(fp,"%.2f;", Personas[i].Movimiento[j]);
                }
            }
            else if(Personas[i].Nocuenta==0)
            {
                break;
            }
        }
        fclose(fp);
    }
    else
    {
        printf("ERROR!! El archivo no se pudo abrir\n");

    }



}
void guardar_clientes(struct ATM Personas[])
{
    int i, j;
    FILE*fp;
    fp=fopen("Clientes.txt", "w"); //Se abre en w para reescribir el saldo
    if(fp!= NULL)
    {

        for(i=0; i<=100; i++)
        {
            if(Personas[i].Nocuenta!=0)
            {
                fprintf(fp,"%s,", Personas[i].Nombre);
                fprintf(fp,"%s,", Personas[i].Apellido);
                fprintf(fp,"%d,", Personas[i].Nocuenta);
                fprintf(fp,"%s,", Personas[i].NIP);
                fprintf(fp,"%.2f,", Personas[i].Saldo);
                for(j=0; j<10; j++)
                {
                    fprintf(fp,"%.2f;", Personas[i].Movimiento[j]);
                }
            }
                else if(Personas[i].Nocuenta==0)
            {
                break;
            }
            }

        printf("Clientes guardado exitosamente...\n");
        fclose(fp);
    }

    else
    {
        printf("ERROR!! El archivo no se pudo abrir\n");

    }

}
char PIN(char nip[]) //Funcion que crea el PIN
{
    int i;
    printf("\nCreacion de Pin\n");
    printf("Porfavor crea tu NIP este debe tener 4 digitos\n");
    gets(nip);
    for(i=0; i<5; i++){
        if(nip[i]!= 1 && 2 && 3 && 4 && 5 && 6 && 7 && 8 && 9 && 0)
        {
            printf("Por Favor, Escriba bien su NIP");
        }
    }
        return(nip);


}
void security(struct ATM Personas[])
{

    int i, cuenta2, attemp=2; //los intentos son dos porque uso un do-while
    char nip[5], nip2[5];
    do
    {
        printf("Ingresa tu Numero de cuenta\n");
        scanf("%d", &cuenta2);
         while (getchar() != '\n'); //limpiar el buffer

        for(i=0; i<=cuenta2; i++)
        {
            if(cuenta2==Personas[i].Nocuenta)
            {
                strcpy(nip,Personas[i].NIP);
                break;

            }
        }

    }while(cuenta2!=Personas[i].Nocuenta);
    do{
    printf("ingresa tu NIP\n");
    gets(nip2);
    if(strcmp(nip2,nip)==0) //Si el pin es el mismo que el usuario creó entonces va a acceder al menu de operaciones
    {
        printf("Accediendo...");
        clear_screen(); //toque minimalista
    }
    else if(attemp==0)
    {
        printf("Numero de intentos excedido porfavor comunique esto a su banco mas cercano\n"); //aqui cierra el programa
        exit(0);
    }
    else
    {
        printf("NIP incorrecto\nNumero de intentos restantes %d\n", attemp); //Se da la advertencia al usuario
    }
    attemp--; //cada vez que el usuario falla al escribir su PIN la variable attemp (intentos) va disminuyendo
    }
    while(strcmp(nip2,nip)!=0); //Esta condicion está para que el usuario ingrese correctamente el PIN
}
float balance(float B, float Mov[]) //Funcion que dice el saldo
{
    int opc, i;
    printf("\n---Consulta---\n");
    printf("1. Saldo\n");
    printf("2. Historial\n");
    scanf("%d", &opc);
    if(opc==1){
    printf("Tu saldo es de %.2f\n",B);
    return B;}
    else
    {
        printf("Tu Historial es:\n");
        for(i=0; i<10; i++)
        {
            printf("%.2f\n", Mov[i]);
        }



    return 0;
    }
}

float depositar(float D, struct ATM Personas[]) //Funcion que permite depositar
{
    int verifica, nocuenta;
    do
    {
        printf("A que numero de cuenta quieres depositar");
        scanf("%d", &nocuenta);
        while (getchar() != '\n');
        if(nocuenta==0 || Personas[nocuenta-1].Nocuenta==0)
        {
            printf("Por favor digite un numero de cuenta verdadero");
        }

    }while(nocuenta==0 || Personas[nocuenta-1].Nocuenta==0);


    do{
        printf("Cuanto quieres depositar?\n");
        scanf("%f", &D);
        verifica=valida(D); //Nos dirige a la funcion valida() y comprueba en binario si la cantidad depositada es correcta
        if(verifica==1)
        {
            printf("La cantidad depositada es valida...\n");
            printf("Haz depositado %.2f \n", D);
            return(D);
        }
        else if(verifica==0)
        {
            printf("La cantidad depositada es 0...  ._.\n"); //un mensaje especial por si deposita 0
        }
        else
        {
            printf("La cantidad depositada es negativa.\n por favor ingrese una cantidad entera ++...\n");
        }

       }
        while(verifica!=1); //Esta condición nos ayuda a que el usuario deposite cantidaes positivas
}
int valida(int X) //funcion que valida si una cantidad es positiva, negativa o cero
/*
Estas condiciones asignan valores a x dependiendo el valor de la cantidad
Positiva++, Negativa -- e incluso 0. Funciona para depositar y retirar.
*/

{
    if(X > 0)
    {
        X=1;
    }
    if(X == 0)
    {
        X=0;
    }
    if(X<0)
    {
        X=-1;
    }
    return X;
}
float retirar(float R) //Esta funcion retira dinero del saldo
{
    int verifica;
    do
    {
        printf("Cuanto quieres retirar?\n");
        scanf("%f", &R);
        verifica=valida(R); //Nos lleva a la variable valida para comprobar la cantidad
        if(verifica==1)
        {
            return(R); //si es positiva la retorna

        }
        else if(verifica==0) //si es 0 añade el mensaje especial del 0
        {
            printf("La cantidad retirada es 0...  ._.\n");
        }
        else
        {
            printf("La cantidad a retirar es negativa.\n por favor retire una cantidad entera ++...\n");
        }

    } while(verifica!=1 && verifica!=0); //condicion para retirar cantidades positivas y que al tener 0 en el saldo no de error al retirar 0
}
int buscarCuenta(struct ATM personas[], int tam, char nombre[]) {
    for (int i = 0; i < tam; i++) {
        if (strcmp(personas[i].Nombre, nombre) == 0) {
            return personas[i].Nocuenta;
        }
    }
    return -1;
}
float historial(float Mov[], float accion)
{
    int i;
    for (i=0; i<10; i++)
    {
        if (Mov[i]==0)
        {
            Mov[i] = accion;
            return (Mov[i]);
        }
    }
       for(i=0; i<9; i++)
       {
           Mov[i]=Mov[i+1]; //Se recorre hacia la izquierda los valores

       }
       Mov[9]=accion;
       return(Mov[9]);

}
void crear_cuenta(struct ATM Personas[], int cantidad)
{
    int i;
    printf("\nBIENVENID@ \nSIGUE LOS PASOS PARA CREAR TU CUENTA\n\n");
    printf("Escribe tu nombre (Empezando con mayuscula)\n");
    while (getchar() != '\n');
    gets(Personas[cantidad].Nombre);
    printf("Escribe tu Apeliido (Empezando con mayuscula)\n");
    gets(Personas[cantidad].Apellido);
    PIN(Personas[cantidad].NIP);
    Personas[cantidad].Nocuenta=cantidad+1;
    printf("Tu numero de cuenta es %d\n", Personas[cantidad].Nocuenta);
    printf("Deposita tu saldo inicial\n");
    do
    {
        printf("Cuanto quieres Depositar?\n");
        scanf("%d", &i);
        if(i<0 || i==0)
        {
            printf("Por favor escoja valores correctos\n");
        }

    } while(i<0 || i==0);
    Personas[cantidad].Saldo=i;
    printf("Tu nuevo saldo es: %.2f\n", Personas[cantidad].Saldo);
    clear_screen();
}


#endif // ATM_H_INCLUDED
