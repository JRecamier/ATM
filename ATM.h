#ifndef ATM_H_INCLUDED
#define ATM_H_INCLUDED

void clear_screen() {
    int i;
    #ifdef _WIN32
        for (i = 3; i >= 1; i--) {
        printf("%d...", i);
        sleep(1);}
        system("cls");  // For Windows
    #else
        for (i = 3; i >= 1; i--) {
        printf("%d...", i);
        sleep(1);}
        system("clear"); // For Linux and macOS
    #endif
}

int pin(int p){
    int contra, contra2[4]={0, 1234, 4321, 2005};
    int i = 0, j = 0;

    for(i=1;i<=3;i++){
    printf("selecciona una cuenta 1 2 o 3: ");
    scanf("%d",&p);
    printf("Escribe tu Password: ");
    scanf("%d",&contra);
    if(contra == contra2[p]){
    printf("\nPASSWORD CORRECTA ENTRANDO A LA CUENTA %d\n\n", p);
    clear_screen();
    return p;
    } else {
            printf("\nPASSWORD INCORRECTA: %d Intento de 3\n\n",i);
            clear_screen();
            }
        }
    printf("\n\nTARJETA BLOQUEADA, INTENTA LUEGO MAS TARDE\n\n");
    exit(0);
    return p;
}

int valida(float x) {
    if(x > 0) {
        printf("la cantidad es valida\n");
        clear_screen();
        return 1;
    } else {
    printf("la cantidad ingresada es NEGATIVA O CERO\n\nINGRESE UN NUMERO POSITIVO\n\n");
    }
    return 0;
}

int menu(){
float saldo[4]= {0, 1000, 2000, 10000}, cantidad;
    int opcion, v;
    int cuenta=pin(cuenta);
        do{
        printf("\n  ----CAJERO AUTOMATICO----\n");
        printf("1- CONSULTAR SALDO\n");
        printf("2- DEPOSTIAR DINERO\n");
        printf("3- RETIRAR DINERO\n");
        printf("4- SALIR\n");
        printf("seleccione una opcion: ");
        scanf("%d", &opcion);
    clear_screen();

        switch (opcion) {
    case 1:
        printf("Tu saldo es de: %.2f\n\n", saldo[cuenta]);
        break;
        case 2:
            while (v != 1)
            {
            printf("\n\nIngrese la cantidad a Depositar: ");
                scanf("%f",&cantidad);
                v = valida(cantidad);
            }
            saldo[cuenta] = cantidad + saldo[cuenta];
            printf("su saldo actualizado es de: %.2f\n\n", saldo[cuenta]);
            break;
            case 3:
                while (v != 1)
                {
                printf("\n\nIngrese la cantidad a Retirar: ");
                    scanf("%f",&cantidad);
                    if(cantidad>saldo[cuenta]){
                            printf("NO PUEDES RETIRAR MAS DINERO DEL QUE TIENES... L BOZZO XDDDDDDD\n\n");
                            break;
                    } else {
                        v = valida(cantidad);
                        saldo[cuenta] = saldo[cuenta] - cantidad;
                        printf("su saldo actualizado es de: %.2f\n\n", saldo[cuenta]);
                        }
                }
                break;
                case 4:
                    printf("\nVUELVA PRONTO CON MAS DINERO :)\n\n");
                    return 0;
                    break;
        }
    }
    while(1);
}





#endif // ATM_H_INCLUDED
