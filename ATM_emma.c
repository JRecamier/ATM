#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//prototipos de funciones
float depositar(float D);
float balance(float B);
float retirar(float R);
int cuenta(int a);
int PIN(int P);
int security(S);
int valida(int X);

//funcion principal
void menu()
{
    float accion, saldo[3]={1000, 2000, 10000};
    int i, opc, pin[3];
    i=cuenta(i);
    if (pin[i]<1000){
    pin[i]=PIN(pin[i]);} //Llamamos a esta funcion para crear el PIN
    do{
    security(pin[i]); //Esta funcion es para corroborar el PIN cada que se hace una accion
    //MENU DE OPCIONES//
    printf("\n----Cajero Automatico----\n");
    printf("1. Consultar Saldo.\n");
    printf("2. Depositar Dinero.\n");
    printf("3. Retirar Dinero.\n");
    printf("4. Cambiar de cuenta\n");
    printf("5. Salir del programa\n");
    printf("Porfavor seleccione una opcion :)\n");
    scanf("%d", &opc);
    switch(opc)
    {
    case 1:
        balance(saldo[i]); //Llama a la función balance para checar el saldo
        break;
    case 2:
        accion= depositar(accion);
        saldo[i]= saldo[i] + accion; //Se asigna el valor de saldo despues de mandar a llamar a la funcion
        printf("Tu nuevo saldo es %.2f \n", saldo[i]); //imprime el saldo
        break;

    case 3:
        do{
        accion= retirar(accion);
        if (saldo[i]>=accion)
        {

        saldo[i]= saldo[i] - accion;
        if(accion!=0){ //Esta condicion es por si el usuario se le ocurre retirar "$0" para que no de el mensaje de cantidad retirada valida
        printf("La cantidad retirada es valida...\n");}
        printf("Haz retirado %.2f \n", accion);
        printf("Tu nuevo saldo es %.2f \n", saldo[i]);
        }
        else
        {
            printf("Error!! No puede retirar mas de lo que tiene en su cuenta.\n"); //En caso de que el usuario quiera retirar mas de lo permitido va amandar este "Error"
        }
        }while(saldo[i]<saldo[i]-accion);
        break;

    case 4:
    menu();
    case 5:
        printf("Hasta luego!!\n");
        exit(0); //Esto cierra el programa si el usuario quiere salir
        break;


    default:
        printf("Porfavor selecciona una opcion valida\n");
        break;
    }
    }while(opc!=4);
}
int cuenta(int a)
{
    printf("Selecciona la cuenta por favor\n");
    printf("Cuenta 1.\nCuenta 2.\nCuenta 3.\n");
    scanf("%d", &a);
    a=a-1;
    return a;

}

float leer_saldo(float L) //Funcion que lee el saldo
{
    FILE*fp;
    fp=fopen("saldo.txt", "r"); //se abre en r para asignar los 1000 iniciales si es la primera vez que ejecuta el código
    if(fp==NULL)
    {
        fclose(fp);
        return 1000;
    }
    else
    {
        fscanf(fp,"%f", &L); //Si existe el archivo entonces solo va a leer el saldo del documento y asignarlo a la variable saldo de menu()
        fclose(fp);
        return(L);
    }

}
void guardar_saldo(float G)
{
    FILE*fp;
    fp=fopen("saldo.txt", "w"); //Se abre en w para reescribir el saldo
    if(fp!= NULL)
    {
        printf("Saldo guardado exitosamente...\n");
        fprintf(fp,"%.2f", G);
        fclose(fp);
    }
    else
    {
        printf("ERROR!! El archivo no se pudo abrir\n");

    }

}
int PIN(int P) //Funcion que crea el PIN
{
    printf("\nCreacion de Pin\n");
    do{
        printf("Porfavor crea tu PIN este debe tener 4 digitos\n");
        scanf("%d", &P);
        if(P<1000 || P>9999) //Esta condicion es para que al crear el pin este tenga 4 digitos (No incluye a "0000")
        {
            printf("Valores incorrectos, Porfavor vuelva intentarlo\n");
        }
        else
        {
           printf("Tu PIN es %d\n", P);
        }
    }while(P<1000 || P>9999); //Si el usuario es negligente al crear el PIN este cbucle ayuda
    return (P); //retorna P que sera asignada a pin en menu()

}
int security(S)
{
    int pin, attemp=2; //los intentos son dos porque uso un do-while
    do{
    printf("ingresa tu PIN\n");
    scanf("%d", &pin);
    if(pin==S) //Si el pin es el mismo que el usuario creó entonces va a acceder al menu de operaciones
    {
        printf("Accediendo...");
        sleep(1); //toque minimalista
    }
    else
    {
        printf("PIN incorrecto\nNumero de intentos restantes %d\n", attemp); //Se da la advertencia al usuario
    }
    if(attemp==0)
    {
        printf("Numero de intentos excedido porfavor comunique esto a su banco mas cercano\n"); //aqui cierra el programa
        exit(0);
    }
    attemp--; //cada vez que el usuario falla al escribir su PIN la variable attemp (intentos) va disminuyendo
    }
    while(pin!=S); //Esta condicion está para que el usuario ingrese correctamente el PIN
}
float balance(float B) //Funcion que dice el saldo
{
    printf("Tu saldo es de %.2f\n",B);
    return 0;
}

float depositar(float D) //Funcion que permite depositar
{
    int verifica;
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
int main()
{
    printf("Bienvenid@ a Banco NoavaCash\n");
    menu();
    return 0;
}
