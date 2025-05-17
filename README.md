![Screenshot of a comment on a GitHub issue showing an image, added in the Markdown, of an Octocat smiling and raising a tentacle.](https://upload.wikimedia.org/wikipedia/commons/thumb/4/46/Logo_Banco_del_Bienestar.png/1200px-Logo_Banco_del_Bienestar.png)
# Proyecto: ATM – Cajero Automático

### Índice

1. Descripción general
2. Requisitos
3. Instalación
4. Guia de instalacion ATM
5. Guía de Usuario

   * Menú Principal
   * ¿Qué se puede y qué no se puede hacer?
6. Elemento “Estrella”: Cuentas

   * Características de la estructura `Cuenta`
   * Acciones disponibles
7. Exportar y Cargar Base de Datos

---


## Descripción general

Este proyecto implementa un **sistema de cajero automático** (ATM) en C, basado en estructuras y funciones que permiten:

* Iniciar sesión
* Consultar saldo y movimientos
* Realizar depósitos y retiros
* Crear nuevas cuentas
* Buscar cuentas por nombre
* Guardar/exportar y, opcionalmente, cargar la base de datos de clientes

---

## Requisitos

* Compilador de C (gcc, clang, etc.)
* Entorno Unix/Linux o Windows con soporte de consola
* Permisos de lectura/escritura en disco (para archivos de datos)

---

## Instalación

```bash
# Clonar repositorio
git clone https://github.com/tu_usuario/ATM.git
cd ATM

# Compilar
gcc -o atm ATM_Structv1.c ATM.h
```



## GUIA DE INSTALACION ATM
**Guía de Instalación, Compilación y Ejecución**  
**Proyecto:** Cajero Automático (ATM) en C  
**Requisitos**  
+ **Sistema operativo:**  
-Windows  
-Linux   
-macOS  
+ **Compilador de C, como:**  
-gcc (Linux/macOS o MinGW en Windows)  
-cualquier IDE que soporte C (Code::Blocks, Dev-C++, etc.)  
_ _ _  
**(Opcional cualquiera de las dos opciones)** git para clonar el repositorio  
1. **Descargar el código fuente**  
*Opción 1:* Clonar el repositorio  
git clone [link a github del repocitorio](https://github.com/JRecamier/ATM.git)cd ATM  
*Opción 2:* Descargar ZIP  
Ve a:[link a github del repocitorio](https://github.com/JRecamier/ATM)  
Haz clic en Code > Download ZIP ,extrae el contenido y entra a la carpeta ATM  
2. **Compilar el programa**  
El archivo principal se llama atm.c. Para compilarlo:  
*En Linux/macOS*  
gcc atm.c -o atm  
*En Windows (con MinGW o WSL)*  
gcc atm.c -o atm.exe  

`Nota: El programa no tiene dependencias externas, así que no necesitas instalar bibliotecas adicionales.`  

3. **Ejecutar el programa**  
*En Linux/macOS*  
./atm  
*En Windows*  
atm.exe  
_ _ _
![Picture of a computer with a code](https://t7m8e9c8.delivery.rocketcdn.me/wp-content/uploads/2020/05/windows-10-windows-terminal-microsoft-780x470.jpg)



---

## Guía de Usuario

### Menú Principal

Al ejecutar `./atm`, se muestra el siguiente menú:

1. **Login / Iniciar sesión**
2. **Búsqueda**
3. **Depósito**
4. **Crear Cuenta**
5. **Salir**
6. **Guardar / Exportar**

Cada opción se explica a continuación.

#### 1. Login / Iniciar sesión

* Solicita **Número de cuenta** y **NIP**.
* Verifica credenciales (máximo 3 intentos).
* Si es correcto, permite acceso a consultas y operaciones.

#### 2. Búsqueda

* Solicita **Nombre** y devuelve el **Número de cuenta** asociado (si existe).

#### 3. Depósito

* Pide **Número de cuenta** y **monto** a depositar.
* Valida que sea un entero positivo.
* Actualiza saldo y registra movimiento.

#### 4. Crear Cuenta

* Solicita:

  * Nombre
  * Apellido
  * NIP (4 dígitos)
  * Saldo inicial
* Genera automáticamente un **Número de cuenta** basándose en el número actual de clientes.
* Inicializa arreglo de últimos 10 movimientos en cero.

#### 5. Salir

* Cierra sesión o sale del programa.

#### 6. Guardar / Exportar

* Tras cada depósito o retiro, guarda todos los clientes en `clientes.txt` (formato plaintext).
* Requiere credenciales de “administrador” (hardcodeado).

---

### ¿Qué se puede y qué no se puede hacer?

**Se puede**

* Consultar saldo y ver histórico de hasta 10 movimientos.
* Realizar múltiples depósitos y retiros (respetando saldo disponible).
* Crear o buscar cuentas existentes.
* Guardar y exportar datos al disco.

**No se puede**

* Retirar más del saldo disponible.
* Registrar operaciones con montos negativos o cero.
* Acceder a funciones de administración (exportar) sin credenciales.

---

## Elemento “Estrella”: **Cuentas**

### Características de la estructura `Cuenta`

```c
#define MAX_MOVS 10

typedef struct {
    char nombre[50];             // nombre del cliente
    char apellido[50];           // apellido del cliente
    int  numeroCuenta;           // identificador único
    char NIP[5];                 // PIN de 4 dígitos + '\0'
    float saldo;                 // saldo actual
    int   movimientos[MAX_MOVS]; // últimos 10 movimientos: +depósitos, -retiros
} Cuenta;
```

* **nombre**, **apellido**: cadenas de hasta 49 caracteres.
* **numeroCuenta**: entero.
* **NIP**: arreglo de 5 chars (4 dígitos + terminador).
* **saldo**: punto flotante.
* **movimientos**: arreglo de 10 enteros (positivo → depósito, negativo → retiro).

### Acciones disponibles

| Función                                                      | Parámetros                                                               | Retorno                   | Descripción                                                   |
| ------------------------------------------------------------ | ------------------------------------------------------------------------ | ------------------------- | ------------------------------------------------------------- |
| `int login(int cuenta, char* NIP)`                           | `cuenta`: número de cuenta  <br>`NIP`: cadena PIN                        | 1 = éxito, 0 = fallo      | Verifica credenciales (hasta 3 intentos).                     |
| `float consultarSaldo(int idx)`                              | `idx`: índice en arreglo de `Cuenta`                                     | saldo actual (float)      | Muestra y retorna el saldo.                                   |
| `int verHistorico(int idx, int out[])`                       | `idx`: índice  <br>`out`: buffer de 10 ints                              | # movimientos registrados | Copia histórico al buffer.                                    |
| `float depositar(int idx, float Monto)`                      | `idx`: índice  <br>`Monto`: positivo                                     | monto depositado (float)  | Añade al saldo, registra movimiento y retorna el monto.       |
| `float retirar(int idx, float Monto)`                        | `idx`: índice  <br>`Monto`: positivo                                     | monto retirado (float)    | Si saldo ≥ monto, resta, registra movimiento y retorna monto. |
| `int buscarCuenta(const char* nombre)`                       | `nombre`: cadena a buscar                                                | número de cuenta o -1     | Retorna número de cuenta si existe, -1 si no.                 |
| `Cuenta* crearCuenta(datos...)`                              | campos de `Cuenta` menos `movimientos`                                   | puntero a nueva Cuenta    | Reserva memoria, inicializa campos y devuelve puntero.        |
| `int guardarClientes(Cuenta* lista, int n)`                  | `lista`: array  <br>`n`: cantidad clientes                               | 1 = éxito, 0 = falla      | Exporta toda la lista a `clientes.txt` (plaintext).           |
| `int cargarClientes(const char* ruta, Cuenta** out, int* n)` | `ruta`: fichero TXT  <br>`out`: puntero array  <br>`n`: puntero cantidad | 1 = éxito, 0 = falla      | Lee archivo y reconstruye array dinámico.                     |

---

## Exportar y Cargar Base de Datos

### Guardar (`guardarClientes`)

* Se invoca tras cada operación crítica.
* Pide credenciales “admin” (hardcodeadas).
* Escribe en `clientes.txt`, campos separados por comas.

### Cargar (`cargarClientes`) *(opcional)*

* Solicita ruta de archivo CSV/TXT.
* Reconstruye las estructuras en memoria usando `malloc`.

---
