#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h> //Sirve para manejador de archivos locales
#include <string.h>


#define MAX 80

#define ARCHIVO_USUARIOS "usuarios.dat"

#define TECLA_ENTER 13

#define TECLA_BACKSPACE 8

#define LONGITUD 5

#define MAX_INTENTOS 3

#define VALOR_CENTINELA -1 //Valor usado para eliminar un registro en el archivo de usuarios y clientes


//>>>>>>Estructuras Y Funciones para clientes y usuarios<<<<<<<<<<<<<<<<

/* Estructura usuarios */
struct user {
	int cedula;
	char nombre[MAX];
	char apellido[MAX];
	char n_usuario[MAX];
	char password[MAX];
};
 
typedef struct user User;

/* Estructura cliente */
struct client {
	int cedula;
	char nombre[MAX];
	char apellido[MAX];
	int edad;
	int compras;
};
 
typedef struct client Client;

 
/* Opciones del Menu usuarios */
void menuUsuarios();
void menuIngresar_usuario();
void menuBuscar_usuario();
void menuModificar_usuario();
void menuEliminar_usuario();

/* Opciones del Menu Clientes */
void menuCliente();
void menuIngresar_cliente();
void menuBuscar_cliente();
void menuModificar_cliente();
void menuEliminar_cliente();
 
/* Funciones para manejar el archivo directamente */
User *obtenerUsuarios(int *n); /* Obtiene un vector dinamico de usuarios */
char existeUsuario(int ci, User *usuario); /* Busca si existe el usuarios en el archivo de usuarios */
char ingresarUsuario(User user); /* Inserta el usuarios al final del archivo */
char eliminarUsuario(int cedula); /* Eliminar el usuarios de placa placausuarios del archivo */
char eliminacionFisica_usuario(); /* Realiza la eliminacion fisica de registros invalidos del archivo de usuarios */

/* Funciones para manejar el archivo directamente  de clientes*/
Client *obtenerClientes(int *n); /* Obtiene un vector dinamico de clientes */
char existeCliente(int ci, Client *cliente); /* Busca si existe el cliente en el archivo de clientes */
char ingresarCliente(Client cliente); /* Inserta el clientes al final del archivo */
char eliminarCliente(int cedula); /* Eliminar el cliente  del archivo */
char eliminacionFisica_cliente(); /* Realiza la eliminacion fisica de registros invalidos del archivo de clientes */
 
/* Funcion de lectura de cadenas */
int leecad(char *cad, int n);

char linea[MAX];

//<<<<<<<<<<Fin Funciones Clientes y Usuarios>>>>>>>>>>>>>>>>>


int menu(); //FunciÃ³n correspondiente al menÃº principal

int menu_productos (int user); /*FunciÃ³n que ejecuta un sub-menÃº 
                                  dedicado al apartado de productos*/

void continuar();//FunciÃ³n que pausa la ejecuciÃ³n hasta que el usuario indique
void creaStock();//FunciÃ³n que genera un archivo con el stock de productos
void imprimeStock();//FunciÃ³n que imprime el stock de productos
void modificarPrecio();//FunciÃ³n que permite modificar el precio de un producto
void modificarCantidad();//FunciÃ³n que permite modificar la cantidad de existencais de un producto
void modificarNombre();//FunciÃ³n que permite modificar el nombre de un producto
void modificarCodigo();//FunciÃ³n que permite modificar el codigo de un producto
void vaciaStoctk();//FunciÃ³n que elimina el archivo correspondiente al Stock
void menuModificar();//FunciÃ³n que invoca un menu el cual se encarga de todas las funciones modificar

typedef struct datosUsuario //struct dedicado a los datos de cada usuario
{
  char nombre[20], apellido[20], tipoDeCuenta[10];
  int cedula, numeroDeCuenta;
} d_usuario;
typedef struct datosProducto //struct dedicado a los datos de cada productos
{
  /* Estructura de cuentas de usuario */

struct usuario {

char nombre[MAX];

char password[MAX];

};



typedef struct usuario Usuario;



/* Funciones de menú */

void menuInicial();

void menuListarUsuarios();

void menuRegistrarUsuario();

void menuIniciarSesion();

void menuSistema();



/* Funciones que manipulan el archivo de usuarios */

char insertarUsuario(Usuario usuario);

char existeUsuario(char nombreUsuario[], Usuario *usuario);

Usuario *obtenerUsuarios(int *);

char logear(char nombreUsuario[], char password[]);



int leerLinea(char *cad, int n);

void leerClave(char *password);



char linea[MAX];

int main() {

menuInicial();

return 0;

}



void menuInicial() {

char repite = 1;

int opcion = -1;



do {

system("cls");

printf("\n\t\t\tMENU INICIAL\n");

printf("\t\t\t============\n");

printf("\n\t\t[1]. Ver usuarios registrados\n");

printf("\t\t[2]. Registrar usuario nuevo\n");

printf("\t\t[3]. Ingresar al sistema\n");

printf("\t\t[0]. Salir\n");

printf("\n\t\tIngrese su opcion: [ ]\b\b");

leerLinea(linea, MAX);

sscanf(linea, "%d", &opcion);



switch (opcion) {

case 1:

menuListarUsuarios();

break;



case 2:

menuRegistrarUsuario();

break;



case 3:

menuIniciarSesion();

break;




 


case 0:

repite = 0;

break;

}



} while (repite == 1);

}



void menuRegistrarUsuario() {

Usuario usuario;

char nombreUsuario[MAX];

char respuesta[MAX];

char repite = 1;



do {

system("cls");

printf("\n\t\t\tREGISTRAR USUARIO\n");

printf("\t\t\t=================\n");

printf("\n\tIngrese nombre de usuario: ");

leerLinea(linea, MAX);

sscanf(linea, "%s", nombreUsuario);



/* Se verifica que el nombre de usuario no exista */

if (!existeUsuario(nombreUsuario, &usuario)) {

strcpy(usuario.nombre, nombreUsuario);



printf("\tIngrese la clave: ");

leerLinea(usuario.password, MAX);



/* Se inserta el usuario en el archivo de usuarios */

if (insertarUsuario(usuario)) {

printf("\n\tEl usuario fue registrado satisfactoriamente!\n");



} else {

printf("\n\tOcurrio un error al registrar el usuario\n");

printf("\nInténtelo mas tarde\n");

}

} else {

printf("\n\tEl usuario \"%s\" ya ha sido registrado previamente\n", usuario.nombre);

printf("\tNo puede registrar dos usuarios con el mismo nombre de usuario.\n");

}



printf("\n\tDesea seguir registrando usuarios? [S/N]: ");

leerLinea(respuesta, MAX);



if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {

repite = 0;

}



} while (repite == 1);

}



void menuListarUsuarios() {

int numeroUsuarios = 0;

Usuario *usuarios;

int i;



system("cls");

usuarios = obtenerUsuarios(&numeroUsuarios); /* Retorna un vector dinámico de usuarios */



if (numeroUsuarios == 0) {

printf("\n\tNo existe ningun usuario registrado!\n");



} else {

printf("\n\t\t ==> LISTADO DE USUARIOS REGISTRADOS <==\n");

printf(" ------------------------------------------------------------------------------\n");

printf("%10s%25s%25s\n", "#", "NOMBRE", "PASSWORD");

printf(" ------------------------------------------------------------------------------\n");



/* Se recorre el vector dinámico de productos */

for (i = 0; i < numeroUsuarios; i++) {

printf("%10d%25s%25s\n", (i + 1), usuarios[i].nombre, usuarios[i].password);

}

printf(" ------------------------------------------------------------------------------\n");

}



// Se libera la memoria asignada al vector dinámico

free(usuarios);

usuarios = NULL;

getchar();

}



void menuIniciarSesion() {

char nombreUsuario[MAX];

char password[MAX];

int intento = 0;

int loginExitoso = 0;



do {

system("cls");

printf("\n\t\t\tINGRESAR AL SISTEMA\n");

printf("\t\t\t===================\n");



printf("\n\t\tUSUARIO: ");

leerLinea(linea, MAX);

sscanf(linea, "%s", nombreUsuario);



printf("\t\tCLAVE: ");

leerClave(password);



if (logear(nombreUsuario, password)) {

loginExitoso = 1;

} else {

printf("\n\n\t\tUsuario y/o password incorrectos");

intento++;

getchar();

}

} while (intento < MAX_INTENTOS && loginExitoso == 0);



if (loginExitoso == 1) {

menuSistema();



} else {

printf("\n\tHa sobrepasado el numero maximo de intentos permitidos\n");

getchar();

}

}



void menuSistema() {

system("cls");

printf("\n ======================================================================\n");

printf("\t\t\t BIENVENIDO AL SISTEMA\n");

printf("\t\t Aqui va la descripcion de tu sistema\n");

printf("\t\t Copyright 2021 | Algoritmos y Algo mas\n");

printf(" ======================================================================\n");



printf("\n\t\tAqui va todo el contenido de tu sistema ;)");

/** 

* Escribe aquí el resto 

* de todo tu código

* ....

* ....

* ....

* ....

* ....

*/



getchar();

}



/* Retorna 1 si se registró el usuario en el archivo correctamente */

char insertarUsuario(Usuario usuario) {

FILE *archivo;

char insercion = 0;



/* Abre el archivo en modo de añadidura, para agregar datos al final. Si no existe es creado*/

archivo = fopen(ARCHIVO_USUARIOS, "ab");



if (archivo == NULL) {

insercion = 0;



} else {

/* Registra el struct usuario en el archivo */

fwrite(&usuario, sizeof(usuario), 1, archivo);

insercion = 1;



/* Cierra el archivo */

fclose(archivo);

}



return insercion;

}



/* Retorna 1 si existe el nombre de usuario. Retorna el usuario buscado si existe */

char existeUsuario(char nombreUsuario[], Usuario* usuario) {

FILE *archivo;

char existe;



/* Abre el archivo en modo de lectura */

archivo = fopen(ARCHIVO_USUARIOS, "rb");



if (archivo == NULL) {

existe = 0;



} else {

existe = 0;



/* Lee secuencialmente del archivo de usuarios */

fread(&(*usuario), sizeof(*usuario), 1, archivo);

while (!feof(archivo)) {

if (strcmp((*usuario).nombre, nombreUsuario) == 0) {

/* Encuentra un usuario del archivo con el nombre de usuario buscado */

existe = 1;

break;

}



fread(&(*usuario), sizeof(*usuario), 1, archivo);

}



/* Cierra el archivo*/

fclose(archivo);

}



return existe;

}



Usuario *obtenerUsuarios(int *n) {

FILE *archivo;

Usuario usuario;

Usuario *usuarios; /* Vector dinámico de usuarios */

int i;



/* Abre el archivo en modo lectura */

archivo = fopen(ARCHIVO_USUARIOS, "rb");



if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */

*n = 0; /* No se pudo abrir. Se considera n = 0 */

usuarios = NULL;



} else {



fseek(archivo, 0, SEEK_END); /* Posiciona el cursor al final del archivo */

*n = ftell(archivo) / sizeof(Usuario); /* # de usuarios almacenados en el archivo. (# de registros) */

usuarios = (Usuario *)malloc((*n) * sizeof(Usuario)); /* Se asigna memoria para todos los usuarios almacenados en el archivo */



/* Se recorre el archivo secuencialmente */

fseek(archivo, 0, SEEK_SET); /* Posiciona el cursor al principio del archivo */

fread(&usuario, sizeof(usuario), 1, archivo);

i = 0;

while (!feof(archivo)) {

usuarios[i++] = usuario;

fread(&usuario, sizeof(usuario), 1, archivo);

}



/* Cierra el archivo */

fclose(archivo);

}



return usuarios;

}



/* Retorna 1 o 0 si el usuario y password son correctos para un usuario en particular */

char logear(char nombreUsuario[], char password[]) {

FILE *archivo;

char logeoExitoso;

Usuario usuario;



/* Abre el archivo en modo de lectura */

archivo = fopen(ARCHIVO_USUARIOS, "rb");



if (archivo == NULL) {

logeoExitoso = 0;



} else {

logeoExitoso = 0;



/* Lee secuencialmente del archivo de usuarios */

fread(&usuario, sizeof(usuario), 1, archivo);

while (!feof(archivo)) {

if (strcmp(usuario.nombre, nombreUsuario) == 0 && strcmp(usuario.password, password) == 0) {

/* Encuentra un usuario del archivo con el nombre de usuario y password buscado */

logeoExitoso = 1;

break;

}



fread(&usuario, sizeof(usuario), 1, archivo);

}



/* Cierra el archivo*/

fclose(archivo);

}



return logeoExitoso;

}



int leerLinea(char *cad, int n)

//Chreez-V
//Funciones Cambio de Usuario y Contraseña:

    void ChangeUsername(); //Función Cambio de Usuario
    void ChangePassword(); //Función Cambio de contraseña.

      void NewUser(AdminUsers *pu); // Prototipo Subfunción para leer datos del nuevo usuario
      void NewPassword(); //Prototipo subfunción para leer nueva contraseña

    //funciones Extras:
    void Admins(); //Función para cargar los usuarios administradores
    void AllUsers_info(); //Función que mostrará la información de todos los usuarios registrados
    void ActiveUser_info(); //Función que mostrará la información del usuario con la sesión activa

//Funciones para el menú movimientos/facturas:

    int MenuMovimientos(); //Función Menú de movimientos.
      int ReadOption(int user); //Subfunción del menú de movimientos para leer opción del usuario o cliente.

    void NuevaFactura(); //Función para crear una nueva factura
      int ReadNewCode(); //Subfunción para leer el código único de la última factura registrada

    int UltimaFactura(); //Función para imprimir la última factura registrada.

    void ReportesFactura(); //Función para imprimir todas las facturas.

    void InaugurarArchivo(); //(temporal)Función que creará el archivo factura por primera vez.

typedef struct Administradores //Se guardaran los datos de los administradores del sistema.
{
	int ci; //número de cédula o identificación del usuario
	char user[30]; //Esta variable de usuario estará llena después del login.
	char password[70]; //Contraseña del usuario
	
} AdminUsers; 

typedef struct datosUsuario //struct dedicado a los datos de cada usuario
{
  char nombre[20], apellido[20], tipoDeCuenta[10];
  int cedula, numeroDeCuenta;
} d_usuario;
typedef struct datosProducto //struct dedicado a los datos de cada productos
====== 
main
{

int i, c;



/* 1 COMPROBACIÓN DE DATOS INICIALES EN EL BUFFER */

c = getchar();

if (c == EOF) {

cad[0] = '\0';

return 0;

}



if (c == '\n') {

i = 0;

} else {

cad[0] = c;

i = 1;

}



/* 2. LECTURA DE LA CADENA */

for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++) {

cad[i] = c;

}

cad[i] = '\0';



/*3. LIMPIEZA DEL BUFFER */ 

if (c != '\n' && c != EOF) /* es un caracter */

while ((c = getchar()) != '\n' && c != EOF);



return 1;

}



void leerClave(char *password) {

char caracter;

int i = 0;



while (caracter = getch()) {

if (caracter == TECLA_ENTER) {

password[i] = '\0';

break;



break;



} else if (caracter == TECLA_BACKSPACE) {

if (i > 0) {

i--;

printf("\b \b");

}



} else {

if (i < MAX) {

printf("*");

password[i] = caracter;

i++;

}

}

}

}  

  char nombre[100];
  int unidades, codigo;
  float precio;
} d_producto;

// Chreez-V
typedef struct Facturas
{
	char titulo[8]; //Siempre almacenará un string que señale "FACTURA"
	int code; //número único de la factura
	char d_emisor[50]; //datos del emisor o empresa
	d_usuario cliente; //Se anida la estructura de los datos del cliente que a su vez anida la estructura del dominio fiscal.
	a_productos producto[100]; //Se anida la estructura del carrito con una longitud de productos fija
	float amount; //monto total incluyendo el importe de IVA
	float IVA; //Se almacena el % del IVA actual.
	struct tm date; //Se almacena la hora actual de la computadora. 

}tfactura;

int main () {//Función principal
=======
int main () {//FunciÃ³n principal
// main
  int elect, op1;
  do
  {
    elect = menu_productos(1); //Llamada al sub-menÃº de productos
  switch (elect)
  {
  case 1:
    imprimeStock(); 
    break;
  
  case 2:
    creaStock();
    break;

  case 3:
    menuModificar();
    break;

  case 4:
    vaciaStock();
    break;
  
  case 5:
    break;

  default:
    printf("Opcion no existente");//Mensaje en caso de ingresar una respuesta no esperada
    break;
  }
  } while (elect != 5);/*Un bucle que no finalizarÃ¡ hasta 
                        que el usuario indique, por lo que 
                        el programa mostrarÃ¡ el menÃº constantemente*/
  
  return 0;
}

int menu_productos(int user)
{
  system("cls"); //Limpiar pantalla
  int election; 

  if(user == 1)
  {
    printf("\nBienvenido al sub-menu de productos para usuarios");
    printf("\nDigite segun sus necesidades:");
    printf("\n____________________________________________________");
    printf("\n1 - Si desea revisar el stock de productos");
    printf("\n2 - Si desea anadir productos al stock");
    printf("\n3 - Si desea modificar productos del stock");
    printf("\n4 - Si desea vaciar el stock");
    printf("\n5 - Si desea salir del sistema\n");
    scanf("%d", &election); //Guarda la elecciÃ³n del usuario
  }
  else if (user == 0)
  {
    printf("\nBienvenido al sub-menu de productos para clientes");
    printf("\nDigite segun sus necesidades:");
    printf("\n____________________________________________________");
    printf("\n1 - Si desea anadir productos al carro de compra");
    printf("\n2 - Si desea retirar producto del carro de compra");
    printf("\n3 - Si desea revisar su carro de compra");
    printf("\n4 - Si desea finalizar su compra");
    printf("\n5 - Si desea cancelar su compra\n");
    scanf("%d", &election); //Guarda la elecciÃ³n del usuario
  }
  else
  {
    printf("Ha ocurrido un error, no se le reconoce en el sistema");/*Mensaje de error en caso 
                                                                      de que la variable no coincida
                                                                      por lo cual no se le reconozca 
                                                                      ni como usuario o admin*/
  }
  return election;//Devuelve la elecciÃ³n
}
void continuar()
{
  printf("\n\n");/*Un mensaje para indicar a el usuario 
                                                          quÃ© hacer cuando se pause el programa*/
  system("pause");//Pausa el programa
}
void creaStock()
{
  system("cls");//Limpia pantalla

  int n = 0; 
  FILE *archivo; //Puntero para los archivos .db
  archivo=fopen("Stock.db", "ab"); /*Busca un archivo llamado Stock, debido a los atributos 
                                    en caso de no existir lo crea y en caso de que sÃ­, todo 
                                    lo que se escriba se aÃ±ade al archivo existente en binario*/

  d_producto control;//Struct para el control del stock

  if (archivo == NULL)
  {
    printf("\nError al crear stock");//Mensaje de error en caso de no poder abrir el archivo
  }
  else
  {
    do
    {
        puts("\nDigite el nombre del producto: ");
        fflush(stdin);
        gets(control.nombre);
        printf("\nDigite el codigo del producto:");
        scanf("%d", &control.codigo);
        printf("\nDigite las existencias del producto: ");
        scanf("%d", &control.unidades);
        printf("\nDigite el precio del producto: ");
        scanf("%f", &control.precio);
        
        printf("\n\nDigite segun corresponda: "); /*PequeÃ±o sub-menu que permite al usuario indicar el nÃºmero 
                                                    de veces que va a aÃ±adir un producto*/
        printf("\n1- Si desea agregar otro producto ");
        printf("\n2 - Si desea volver al menu anterior \n");
        scanf("%d", &n);

        if (n!= 1 && n!=2)//Condicional en caso de que el usuario digite una respuesta no esperada
        {
          printf("\n\nHa ocurrido un error"
          "\nPor favor digite un el valor correspondiente a las opciones del menu\n\n");
          continuar();
        }
        
        
        fwrite(&control, sizeof(d_producto), 1, archivo);//Escribe el input del usuario en Stock
    } while(n!=2);

  }
  fclose(archivo);//Cierra archivo
}
void imprimeStock()
{

    system("cls");
    int j = 0, itera = 0;
    FILE *archivo;

    archivo = fopen("Stock.db", "rb");//Abre el archivo Stock unicamente para lectura de datos en binario
    d_producto imp;
    
    if (archivo == NULL)
    {
      printf("Ha ocurrido un error en la apertura del stock");//Mensaje de error en caso de no existir el archivo
    }
    else
    {
      fread(&imp, sizeof(d_producto), 1, archivo);//Lee archivo
      
        while(!feof(archivo)&&!ferror(archivo))/*Un bucle que no va a terminar hasta que se encuentre 
                                                con el final del archivo o algÃºn tipo de error*/
        {
          printf("\nProducto: %s", imp.nombre);
          printf("\nCodigo: %d", imp.codigo);
          printf("\nExistencias: %d", imp.unidades);
          printf("\nPrecio: %.2f", imp.precio);
          printf("\n_________________________________");
          fread(&imp, sizeof(d_producto), 1, archivo);
        }
      fclose(archivo);//Cierra el archivo
    }
    continuar();
}
void modificarPrecio() 
{
  system("cls");
  int producto=0, existe=0;//Variable inicializadas en 0 para evitar problemas
  char a;
  FILE *archivo;
  d_producto modifx;
  archivo=fopen("Stock.db", "r+b");//Apertura que permite leer como escribir, en caso de no exister crea el archivo
  if(archivo==NULL)
  {
    printf("\nHa ocurrido un error al abrir el archivo Stock.db");//Mensaje de error
  }
  else
  {
    printf("\nCual es el codigo del producto a modificar?");//Mensaje para indicar al usuario que escribir
    scanf("%d", &producto);
    fread(&modifx, sizeof(d_producto), 1, archivo);//lectura del archivo en el struck anteriormente creado
      while(!feof(archivo))
      {
        if(producto==modifx.codigo)//Condicional en caso de que el codigo coincida con algun producto del stock
        {
          printf("\nProducto: %s", modifx.nombre);
          printf("\nCodigo: %d", modifx.codigo);
          printf("\nExistencias: %d", modifx.unidades);
          printf("\nPrecio: %.2f", modifx.precio);
          printf("\n_________________________________");
          printf("\nIngrese el nuevo precio del producto\n");
          scanf("%f", &modifx.precio); 
          int n = ftell(archivo) - sizeof(d_producto);//Obtengo la posicion en la que inicia todo el stuck correspondiente al codigo del producto
          fseek(archivo, n, SEEK_SET);//Me posiciono en el inicio del struck
          fwrite(&modifx, sizeof(d_producto), 1, archivo);//Lo reescribo
          existe = 1;//Altero una variable para evitar un mensaje de error
          break;
        }
        fread(&modifx, sizeof(d_producto), 1, archivo);//en caso de no coincidir el primer codigo, continue hasta que llegue al final del archivo
      }
    if(existe==0)//Condicional con mensaje de error
    {
      printf("\nNo se encontro ningun producto que conincida con el codigo ingresado");//Mensaje de error
    }  
    fclose(archivo);
    continuar();
  }
}
void modificarNombre()
{
  system("cls");
  int  codigo, existe=0;
  char a, producto[100];
  FILE *archivo;
  d_producto modifx;
  archivo=fopen("Stock.db", "r+b");
  if(archivo==NULL)
  {
    printf("\nHa ocurrido un error al abrir el archivo Stock.db");
  }
  else
  {
    printf("\nCual es el codigo del producto a modificar?");
    scanf("%d", &codigo);

    fread(&modifx, sizeof(d_producto), 1, archivo);
      while(!feof(archivo) && !ferror(archivo))
      {
        if(codigo==modifx.codigo)
        {
          printf("\nProducto: %s", modifx.nombre);
          printf("\nCodigo: %d", modifx.codigo);
          printf("\nExistencias: %d", modifx.unidades);
          printf("\nPrecio: %.2f", modifx.precio);
          printf("\n_________________________________");
          printf("\nIngres el el nuevo nombre del producto\n");
          fflush(stdin);//Limpia el buffer para evitar problemas con el gets
          gets(modifx.nombre);
          int n = ftell(archivo) - sizeof(d_producto);
          fseek(archivo, n, SEEK_SET);
          fwrite(&modifx, sizeof(d_producto), 1, archivo);
          existe=1;
          break; 
        }
        fread(&modifx, sizeof(d_producto), 1, archivo);
      }
    if(existe==0)
    {
      printf("\nNo se encontro ningun producto que conincida con el codigo ingresado");    
    }  
    fclose(archivo);
    continuar();
  }
  
}
void modificarCantidad()
{
  system("cls");
  int producto, existe = 0;
  char a;
  FILE *archivo;
  d_producto modifx;
  archivo=fopen("Stock.db", "r+b");
  if(archivo==NULL)
  {
    printf("\nHa ocurrido un error al abrir el archivo Stock.db");
  }
  else
  {
    printf("\nCual es el codigo del producto a modificar?");
    scanf("%d", &producto);
    fread(&modifx, sizeof(d_producto), 1, archivo);
      while(!feof(archivo) && !ferror(archivo))
      {
        if(producto==modifx.codigo)
        {
          printf("\nProducto: %s", modifx.nombre);
          printf("\nCodigo: %d", modifx.codigo);
          printf("\nExistencias: %d", modifx.unidades);
          printf("\nPrecio: %.2f", modifx.precio);
          printf("\n_________________________________");
          printf("\nIngrese la cantidad de existencias del producto?\n");
          scanf("%d", &producto); 
          modifx.unidades=producto;
          int n = ftell(archivo) - sizeof(d_producto);
          fseek(archivo, n, SEEK_SET);
          fwrite(&modifx, sizeof(d_producto), 1, archivo);
          printf("\nSe ha modificado con exito el producto."); 
          existe=1;
          break;     
        }
        fread(&modifx, sizeof(d_producto), 1, archivo);
      }
    if(existe==0)
    {
      printf("\nNo se encontro ningun producto que conincida con el codigo ingresado");   
    }  
    fclose(archivo);
    continuar();
  }
}
void modificarCodigo()
{
  system("cls");
  int producto=0, existe=0;
  char a;
  FILE *archivo;
  d_producto modifx;
  archivo=fopen("Stock.db", "r+b");
  if(archivo==NULL)
  {
    printf("\nHa ocurrido un error al abrir el archivo Stock.db");
  }
  else
  {
    printf("\nCual es el codigo del producto a modificar?");
    scanf("%d", &producto);
    fread(&modifx, sizeof(d_producto), 1, archivo);
      while(!feof(archivo) && !ferror(archivo))
      {
        if(producto==modifx.codigo)
        {
          printf("\nProducto: %s", modifx.nombre);
          printf("\nCodigo: %d", modifx.codigo);
          printf("\nExistencias: %d", modifx.unidades);
          printf("\nPrecio: %.2f", modifx.precio);
          printf("\n_________________________________");
          printf("\nIngrese el nuevo codigo del producto\n");
          scanf("%d", &producto); 
          modifx.codigo=producto;
          int n = ftell(archivo) - sizeof(d_producto);
          fseek(archivo, n, SEEK_SET);
          fwrite(&modifx, sizeof(d_producto), 1, archivo);
          printf("\nSe ha modificado con Ã©xito el producto.");  
          existe=1; 
          break;     
        }
        fread(&modifx, sizeof(d_producto), 1, archivo);
      }
      if(existe==0)
        {
          printf("\nNo se encontro ningun producto que conincida con el codigo ingresado");    
        }  
    fclose(archivo);
    continuar();
  }
}

void vaciaStock()
{
  system("cls");
  
  if (remove("Stock.db") == 0)//Elimina el archivo "Stock.db"
  {
    printf("\nSu Stock ha sido reestablecido");//Mensaje en caso de operacion exitosa
  }
  else
  {
    printf("\nNo se ha podido vaciar el stock");//Mensaje de error
  }
  continuar();
}

void menuModificar()
{
  system("cls");
  int op1;
   do
  {
    system("cls");
    printf("\nBienvenido al sub-menu de modificar productos");
    printf("\nDigite segun sus necesidades:");
    printf("\n____________________________________________________________________");
    printf("\n1 - Si desea modificar el precio de un producto");
    printf("\n2 - Si desea modificar el nombre de un producto");
    printf("\n3 - Si desea modificar la cantidad de existencias de un producto");
    printf("\n4 - Si desea modificar el codigo de un producto");
    printf("\n5 - Si desea volver al submenu de productos\n");
    scanf("%d", &op1);
    switch (op1)
    {
    case 1:
      modificarPrecio();
      break;
    
    case 2:
      modificarNombre();
      break;

    case 3:
      modificarCantidad();
      break;

    case 4:
      modificarCodigo();
      break;

    case 5:
      break;
    
    default:
      printf("\nDigite un valor correspondiente a las opciones brindadas");//Mensaje en caso de error con el input
      break;
    }
  } while (op1 != 5);
}

// Chreez-V
//Insturcciones de funciones para cambio de usuario y contraseña:

void Admins()
{
	FILE *fb;
	fb = fopen("administradores.db","ab");
	
	if (fb == NULL)
	{
		puts("\nHa ocurrido un error");
		exit(1);
	}
	// bug se registra el struct en el archivo cada vez que se ejecuta el programa: Solución:
	
	fseek(fb,0,SEEK_END); // Se posicionará el cursor hasta el final
    int p = ftell(fb); //Utilizará ftell para guardar el tamaño del archivo en bits en un entero
    printf("\nTamaño del archivo actual:%d\n",p); //Indicador para verificar que no ha aumentado o disminuido el tamaño
	fseek(fb,0,SEEK_SET); //Se posiconará el cursor al comienzo nuevamente
	
	if(p > 50) //Si el tamaño del archivo supera 50 bits, quiere decir que el registro de Usuarios ya se encuentra en el archivo.
	{			//Esto evita que se registre el struct en el archivo más de una vez
	
		puts("Ya se habían registrado los datos");
	}
	else
	{
		
		AdminUsers users[5];// se crea una lista o base de datos temporal para almacenar los datos del usuario.
		
		users[0].ci = 1;
		strcpy(users[0].user,"Jenfer Martínez"); //no podía asignarlos con "=" porque ese operador realiza una modificación, cosa que en matrices no se permite, por lo tanto se usa la función de la lib string
		strcpy(users[0].password,"3co1");
			users[1].ci = 2;
		strcpy(users[1].user, "Miguel Nuñez");
		strcpy(users[1].password,"3co1");
		
			users[2].ci = 3;
		strcpy(users[2].user, "José García");
		strcpy(users[2].password,"P2");
		
			users[3].ci = 4;
		strcpy(users[3].user, "Jesús Parra");
		strcpy(users[3].password,"6");
		
			users[4].ci = 5;
		strcpy(users[4].user, "Christian Vasquez");
		strcpy(users[4].password,"4");
		
		int total = fwrite(&users,sizeof(AdminUsers),5,fb); //se escribe el struct en el archivo 5 veces, necesarias para guardar todos los datos
		
		if (total != 5){ //notificación en caso de error
			printf("Ha ocurrido un error");
		}
		
		printf("\nSe han cargado los administradores con éxito \n");
	}
	fclose(fb);
	
}

void ChangeUsername(int num){ //se pide el número de identificación del usuario que inició sesión de la función respectiva
	
	FILE *fb; //creamos archivo
	fb = fopen ("administradores.db", "r+b"); //Se abre el archivo de forma lectura y escritura en binario
	if (fb == NULL)
	{
		puts("\nHa ocurrido un error en la apertura del archivo");
		exit(1);
	}
	AdminUsers u; //variable local para controlar el struct

	fread(&u,sizeof(AdminUsers),1,fb); //Se leen la información y se guarda en u una primera vez afuera del bucle.
	
	while(!feof(fb)&&!ferror(fb)) //mientras no haya un fin de archivo o error...
	{
		
		if (u.ci == num) //Si el número de identicación del usuario que se tomó del archivo es igual al que inició sesión (3 = José García...
		{
			printf("\nSe cambiará el usuario %s",u.user); //Se notifica el usuario que se cambiará

			memset(u.user,0,sizeof(u.user));//Se borra el usuario registrado anteriormente / todo el contenido de la cadena.
			
			NewUser(&u); //se aplica la subfunción lectura de usuario, se le otorga la dirección de memoria de la var struct.
			
			int loc = ftell(fb) -sizeof(AdminUsers); //Se almacenará el *VALOR* de la posición actual del cursor - del registro = el comienzo del número de identificación
			
			fseek(fb, loc, SEEK_SET); //Se asignará la posición del cursor con el valor previo almacenado.
			
			int vrify = fwrite(&u, sizeof(AdminUsers), 1,fb); //Se sobreescribirán los datos del usuario que inició sesión (el número 3)
			if (vrify != 1) //Notificación en caso de algún fallo
			{
				printf("\n Ocurrió un error en la escritura del nuevo usuario");
			}
			
			printf("\nSe ha modificado el Usuario");
			
			break;
		}
		fread(&u, sizeof(AdminUsers),1,fb); //Pasará al siguiente usuario si no se ha cumplido la condicional previa.
	}
	
	fclose(fb);
}

void ChangePassword(int ci)//Se pide el número de cédula del usuario que inició sesión para cambiar la contraseña
{
	FILE *fb; //se crea el archivo
	fb = fopen ("testfilo.db","r+b"); //se abre el archivo en forma lectura y escritura en binario
	
	if (fb == NULL)
	{
		puts("\nHa ocurrido un error en la apertura del archivo");
		exit(1);
	}

	AdminUsers c; //variable local para contrar el struct
	
	fread(&c,sizeof(AdminUsers),1,fb); //Se lee la información y se guarda en u una primera vez fuera del bucle
	
	while(!feof(fb)&&!ferror(fb)) //mientras no haya un fin de archivo o error...
	{
		if (c.ci == ci) //Si el número de cédula del usuario que se tomó del archivo es igual al de usuario activo -> se cambiarán los datos del usuario activo
		{
			printf("\n Se cambiará la contraseña del usuario %s",c.user);
			
			memset(c.password,0,sizeof(c.password));//Se borra la contraseña registrada anteriormente / todo el contenido de la cadena.
			
			NewPassword(&c); //Subfunción que guardará la nueva contraseña
			
			int lec = ftell(fb) -sizeof(AdminUsers); //se almacenará el valor de la posición actual del cursor y se resta con el tamaño del registro dará como resultado el comienzo del registro del usuario
			
			fseek(fb, lec, SEEK_SET); //Se asignará el cursor al comienzo del registro del usuario activo en el archivo
			
			int vrifo = fwrite(&c, sizeof(AdminUsers), 1, fb);//Se sobreescribe los datos anteriores por el nuevo registro del usuario activo
			if (vrifo != 1) //verificación si ocurre un error
			{
				printf("\n Ocurrió un error en la escritura de la nueva contraseña");
			}
			
			printf("\n Se ha modificado la contraseña del usuario");
			
			break; //rompe el bucle para que no lea más registros
		}
		fread(&c,sizeof(AdminUsers),1,fb); //Si no se cumple la condición, pasará al siguiente usuario registrado hasta encontrar el usuario activo
	}
	
	fclose(fb); //cierra el archivo
}

void AllUsers_info()
{

    FILE *fb;

    fb = fopen("testfilo.db", "rb");//Abre el archivo de usuarios unicamente para lectura de datos en binario
    AdminUsers a;
    
    if (fb == NULL)
    {
      printf("Ha ocurrido un error en la apertura del stock");//Mensaje de error en caso de no existir el archivo
    }
    else
    {

      fread(&a, sizeof(AdminUsers), 1, fb);//Lee archivo
      
        while(!feof(fb)&&!ferror(fb))/*Un bucle que no va a terminar hasta que se encuentre 
                                                con el final del archivo o algún tipo de error*/
        {
          printf("\nUsuario: %s", a.user);
          printf("\nCodigo: %d", a.ci);
          printf("\nContraseña: %s",a.password);
          printf("\n_________________________________");
          fread(&a, sizeof(AdminUsers), 1, fb);
        }
      fclose(fb);//Cierra el archivo
    }
}

void ActiveUser_info(int num) //Imprime los datos del usuario activo
{

    FILE *fb;

    fb = fopen("testfilo.db", "rb");//Abre el archivo base de datos unicamente para lectura de datos en binario
    AdminUsers a;
    
    if (fb == NULL)
    {
      printf("Ha ocurrido un error en la apertura del stock");//Mensaje de error en caso de no existir el archivo
    }
    else
    {
      fread(&a, sizeof(AdminUsers), 1, fb);//Lee archivo
      
        while(!feof(fb)&&!ferror(fb))/*Un bucle que no va a terminar hasta que se encuentre 
                                                con el final del archivo o algún tipo de error*/
        {
        	if (a.ci == num) //Si el número de cédula del usuario encontrado es igual al del usuario activo, se mostrarán los datos del usuario activo
        	{

        	printf("\nUsuario: %s", a.user);
          	printf("\nCodigo: %d", a.ci);
          	printf("\nContraseña: %s",a.password);
          	printf("\n_________________________________");
          	
          	break;
			}

          fread(&a, sizeof(AdminUsers), 1, fb); //Si no se cumple la condición, pasará al siguiente usuario registrado hasta encontrar los datos del usuario activo en el archivo
        }
      fclose(fb);//Cierra el archivo
    }
}

void NewPassword(AdminUsers *pu) //Subfunción de la función cambio de contraseña para leer una nueva
{
	char second; //Almacenará los caracteres de la nueva contraseña y posteriormente los caracteres sobrantes del buffer de entrada
	int j = 0; //Variable de control de iteración
	
	puts("\nIngrese la nueva contraseña\n");
	while (j < CMAX-1 && (second = getchar())!=EOF && second!='\n') //Itera si se cumple:la variable de control de iteración es menor que la longitud definida-1 y
																	//Si los caracteres obtenidos son indiferentes del fin de archivo o el backspace(enter)
																	//Controla mejor la entrada de datos cadenas que printf o gets sin desbordarse.
	{
		pu->password[j]=second;
		j++;
	}
	
	
	while(second!=EOF && second!='\n') /*Se almacenarán los caracteres sobrantes del buffer de entrada
									   para evitar que aparezcan en otros campos o variables por desbordamiento*/
	{
		second=getchar();
	}
	
	pu->password[j]='\0'; //Se cierra la cadena del campo contraseña.
	
}

void NewUser(AdminUsers *pu) //Subfunción de la función cambio de Usuario para leer uno nuevo
{
	char first; //Almacenará los caracteres del nuevo usuario y posteriormente los caracteres sobrantes del buffer de entrada
	int j = 0; //Variable de control de iteración
	
	puts("\nIngrese el primer nombre del usuario\n"); 

	while (j < CMAX-1 && (first = getchar())!=EOF && first!='\n')	//Itera si se cumple:la variable de control de iteración es menor que la longitud definida-1 y
																	//Si los caracteres obtenidos son indiferentes del fin de archivo o el backspace(enter)
																	//Controla mejor la entrada de datos cadenas que printf o gets sin desbordarse.
	{
		pu->user[j]=first;
		j++;

	}
	
	while(first!=EOF && first!='\n') /*Se almacenarán los caracteres sobrantes del buffer de entrada
									   para evitar que aparezcan en otros campos o variables por desbordamiento*/
	{
		first=getchar();
	}
	
	pu->user[j]='\0'; //Se cierra la cadena del campo contraseña.
}

//Instrucciones para el menu de movimientos:

int MenuMovimientos(int user) //Se necesita el tipo de cliente como argumento, (cliente o administrador)
{
	
	system("cls"); //limpia pantalla
	
	int option;
	do
	{
		option = ReadOption(user); //Almacena la función que se encarga de mostrar el menú cliente o administrador dependiendo del valor del futuro argumento
		switch(option)
		{
			case 1:
				
				if (user == 0) // Caso clientes
				{
					option = UltimaFactura(1);
					break;
				}
				else if (user == 1) //Caso Administradores
				{
					ReportesFactura();
					break;
				}
				else //Caso tipo de usuario no detectado
				{
					printf("\n Ha ocurrido un error, no existe un caso para este tipo de usuario");
					break;
				}
				
			case 2: //Sale del menú tanto cliente como administrador
					//menuClientes()?
				break;
				
			default:
				printf("\nDigite un valor correspondiente a las opciones dadas");
				break;
		}
	}while (option != 2);
	
}

void InaugurarArchivo() /*El propósito de esta función es crear el archivo facturas,
						y detectar si contiene una factura; esto último debido a que
						se tenía como idea crear una factura vacía con un código único
						y las próximas facturas del cliente tendrán ese código + 1;
						pero se solucionó con una condición en la función NuevaFactura para evitar este desastre xd */
{
	FILE *fb;
	fb = fopen ("facturas.db","ab");
	
	if (fb == NULL)
	{
		puts("\nHa ocurrido un error en la apertura del archivo de Inaugurar");
		exit(1);
	}
	
	time_t t = time(NULL);  //se crea variable tipo tiempo que contendrá la función del tiempo de la computadora
	
	fseek(fb,0,SEEK_END); //Detectar si contiene ya una factura el archivo si su tamaño es > 20 bits.
	int p = ftell(fb);
	printf("\ntamaño del archivo actual: %d\n",p);
	fseek(fb, 0,SEEK_SET);
	
	if (p > 20)
	{
		puts("Ya se habían registrado los datos");
	}
	else //Si no tiene contenido se creará una factura de prueba
	{
		puts("Se ha inaugurado con éxito");
	}
	fclose(fb);
}

void ReportesFactura(int n_prod) /*se pedirá la cantidad de productos que tiene el carrito
									Función que imprime todas las facturas. */
{
	FILE *fb;
	
	fb = fopen("facturas.db","rb"); //Abre archivo en modo lectura
	tfactura a;
	
	if (fb == NULL)
    {
      printf("Ha ocurrido un error en la apertura del stock");//Mensaje de error en caso de no existir el archivo
    }
    else
    {
    	
    	fread(&a,sizeof(tfactura),1,fb);
    	
    	while(!feof(fb)&&!ferror(fb))
    	
    	{
    		printf("\n_______________________");
    		printf("\n%s",a.titulo);
    		printf("\nCodigo: %d",a.code);
    		printf("\nFecha de emisión: %d-%02d-%02d \nHora: %02d:%02d"
			,a.date.tm_mday,a.date.tm_mon +1,a.date.tm_year + 1900,a.date.tm_hour,a.date.tm_min);
    		printf("\n_______________________");
    		printf("\nInformación del Cliente");
    		printf("\n_______________________");
    		printf("\nNombre del Cliente:"a.cliente.nombre_completo);
    		printf("\nCI:",a.cliente.ci);
    		printf("\n_______________________");
    		printf("\nProductos Adquiridos:");
    		for(int i = 0;i < n_prod;i++) //Itera hasta la cantidad de productos.
    		{
    			printf("\n%d |",a.producto[i].codigo); //Jenfer ¿los productos comenzarán almacenarse desde la posición 0 o 1?
    			printf(" %s |",a.producto[i].nombre);
    			printf("(%d)|",a.producto[i].unidades);
    			printf("Bs %f \n",a.producto[i].precio);
			}
			printf("\n_______________________");
    		printf("\nIVA:");
    		printf("\n_______________________");
    		printf("\nTOTAL:");
    		printf("\n\nGracias por su compra!");
    		printf("\n");
    		fread(&a,sizeof(tfactura),1,fb);
		}
		fclose(fb);//cierra el archivo
	}
}

void NuevaFactura(int n_prod) //Se pide el número de productos del carrito.
{
	FILE *fb;
	fb = fopen("facturas.db","r+b");
	
	time_t t = time(NULL); //Se crea una variable tipo tiempo y la función time devuelve los valores de la fecha del sistema.
	
	if (fb == NULL)
	{
		puts("\nHa ocurrido un error en la apertura del archivo");
		exit(1);
	}
	
	tfactura f; //control del struct tfacturas
	float sumaBs; //Variable que almacena la suma en Bs de todos los productos sin IVA
	f.IVA = 16 / 100; //El importe del IVA se encuentra en 16% en Venezuela 2022
	
	fseek(fb,0,SEEK_END); //Función para detectar si el archivo tiene alguna factura previa registrada
	int p = ftell(fb);
	printf("\nTamaño del archivo actual:%d\n",p);
	fseek(fb,0,SEEK_SET);
	
	if (p > 20) //si contiene una factura, se obtendrá el código único de la última factura y se le sumará 1 para generar un código único
	{
		f.code = ReadNewCode(fb) + 1;
	}
	else //Si no existen facturas previas en el archivo se le otorgará un código único directamente.
	{
		f.code = 1020500000;
	}
	strcpy(f.titulo ,"FACTURA");
	strcpy(f.d_emisor ,"NOMBRE DE LA EMPRESA");
	f.date = *localtime(&t); //Se le añade al campo fecha la hora actual en la que se procesa la última o presente factura.
	
	for (int i = 0; i < n_prod; i++) //Ciclo que almacenará la suma en Bs de todos los productos adquiridos(?
	{
		sumaBs = sumaBs + f.producto[i].precio;
	}
	
	f.amount = sumaBs * f.IVA; //Se almacena el monto total con IVA incluido
	
	fseek(fb,0,SEEK_END); //Se posiciona el cursor al final del archivo
	
	int vrify = fwrite(&f,sizeof(tfactura),1,fb); //se escribe una nueva factura
	if (vrify != 1)
	{
		printf("\n Ocurrio un error en el registro de la nueva factura en el archivo");
	}
	else
	{
		puts("Se ha grabado la factura correctamente");
	}
	
	//los otros campos como producto y datos del cliente se llenarán en sus respectivas funciones, no hace falta declararlas aquí.
	fclose(fb);
}

//Instrucciones de las subfunciones de menu movimientos

int ReadOption(int user) //Subfunción que leerá la opción del usuario
{
	int option;
	
	if (user == 0) //para clientes.
	{
		printf("\nSu compra ha sido realizada con éxito");
		printf("\n____________________________________________");
		printf("\n1 - Si desea ver su factura");
		printf("\n2 - Si desea volver al menú de clientes\n");
		scanf("%d",&option);
	}
	else 
	if (user == 1) //para administradores.
	{
		printf("\n Ha accedido al menú de facturas como administrador");
		printf("\n ___________________________________________________");
		printf("\n1 - Si desea ver el reporte de facturas");
		printf("\n2 - Si desea volver al menú de usuarios\n");
		scanf("%d",&option);
	}
	else
	{
		printf("\n Ha ocurrido un error, no se le reconoce en el sistema");
	}
	
	return option;
}

int ReadNewCode(FILE *fb) //Se pide como parámetro el archivo de la función NuevaFactura para acceder al código de la última factura
{
	tfactura o; //Una variable tfactura que almacenará temporalmente la última factura registrada.
	
	//Se comienza a buscar la última factura registrada 
	fseek(fb,0, SEEK_END);
	
	int lec = ftell(fb) -sizeof(tfactura);
	
	fseek(fb, lec, SEEK_SET);
	
	fread(&o,sizeof(tfactura),1,fb);
	
	return o.code;//regresa el código de la última factura
}

int UltimaFactura(int n_prod) //se pide el número de productos que el usuario compró
{
	FILE *fb;
	
	fb = fopen("facturas.db","rb");
	if(fb == NULL)
	{
		printf("\nHa ocurrido un error en la apertura del archivo");
	}
	else
	{
		tfactura a;	//se declara una variable que controle el struct para almacenar la última factura
		
		fseek(fb,0,SEEK_END); //Se posiciona el cursor al final del archivo donde termina la última factura
		
		int lec = ftell(fb) -sizeof(tfactura); //Se resta su posición con el tamaño de la estructura que almacena las facturas para obtener la posición donde comienza
		
		fseek(fb, lec, SEEK_SET); //se establece el cursor al comienzo del registro de la última factura
		
		int verfy = fread(&a, sizeof(tfactura),1,fb); //se lee la factura, se almacena en la variable iniciada anteriormente y se guarda el valor de repeticiones en vrify para verificar el número de veces de fread
		if (verfy != 1)
		{
			puts("Ocurrió un error en la lectura de la última factura");
		}
		else
		{
    		printf("\n_______________________");
    		printf("\nTitulo: %s",a.titulo);
    		printf("\nCodigo: %d",a.code);
    		printf("\nFecha de emisión: %d-%02d-%02d \nHora: %02d:%02d"
			,a.date.tm_mday,a.date.tm_mon +1,a.date.tm_year + 1900,a.date.tm_hour,a.date.tm_min);
    		printf("\n_______________________");
			printf("\nInformación del Cliente");
    		printf("\n_______________________");
    		printf("\nNombre del Cliente:");
    		printf("\nCI:");
    		printf("\n_______________________");
    		printf("\nProductos Adquiridos:");
    		for(int i = 0;i < n_prod;i++) //Itera hasta la cantidad de productos solicitados en el parámetro
    		{
    			printf("\n%d |",a.producto[i].codigo);
    			printf(" %s |",a.producto[i].nombre);
    			printf("(%d)|",a.producto[i].unidades);
    			printf("Bs %f \n",a.producto[i].precio);
			}
			printf("\n_______________________");
    		printf("\nIVA:");
    		printf("\n_______________________");
    		printf("\nTOTAL:");
    		printf("\n\nGracias por su compra!");
    		printf("\n");
		}
	}
	fclose(fb);
	
	return 2; //retorna la opción 2 del menú -> implica redirigir al cliente al menú anterior o salir del programa.

}

=======

// >>>>>>>> FUNCIONES USUARIOS <<<<<<<<<<<
void menuUsuarios()
{
	char repite = 1;
	int opcion = -1;
	/* Cuando el usuario ingresa texto en lugar de ingresar una opcion. El programa no modifica
	el valor de opcion. En ese caso, no se debe de ingresar a ninguno de los case, por eso se esta
	inicializando la variable opcion con un valor que no permita ejecutar ningun case. Simplemente,
	volver a interar y pedir nuevamente la opcion. */
 
	do {
 
		system( "COLOR 2" );//con esto solo cambiamos el color de nuestra fuente
		system("cls");
 
 
		printf("\n         MENU DE USUARIOS         \n");
		printf("\n[1] Registrar nuevo usuario \n");
		printf("\n[2] Buscar datos de usuario \n");
		printf("\n[3] Modificar informacion de un usuario \n");
		printf("\n[4] Eliminar un usuario \n");
		printf("\n[0] Salir\n");
		printf("\nQue deseas hacer?: [ ]\b\b");
 
		/* Lectura segura de un entero */
		leecad(linea, MAX);
		sscanf(linea, "%d", &opcion);
 
		switch (opcion) {
 
			case 1:
				menuIngresar_usuario();
				break;
 
			case 2:
				menuBuscar_usuario();
				break; 
 
			case 3:
				menuModificar_usuario();
				break;
 
			case 5:
				menuEliminar_usuario();
				break;
 
			case 0:
				repite = 0;
				break;
		}
 
	} while (repite);
}

void menuIngresar_usuario()
{
	User usuario;
	int cedula = 0;
	char repite = 1;
	char respuesta[MAX];
 
	do {
		system("cls");
		printf("SISTEMA DE INGRESO DE USUARIOS \n");
 
		/* Se pide la cedula del usuarios a ingresar */
		printf("\n\tCedula del usuario: ");
		leecad(linea, MAX);
		sscanf(linea, "%d", &cedula);
 
		/* Se verifica que el usuarios no haya sido almacenado anteriormente */
		
		if (cedula == 0){
			printf("\n\tDesea continuar? [S/N]: ");
			leecad(respuesta, MAX);
 
			if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
			}
		}
		else
		{
			if (!existeUsuario(cedula, &usuario)) {
 
				usuario.cedula = cedula;
	
				/* Se piden los demas datos del usuarios a ingresar */
				printf("\tNombre de usuario: ");
				leecad(usuario.n_usuario, MAX);
 
				printf("\tNombre: ");
				leecad(usuario.nombre, MAX);
 
				printf("\tApellido: ");
				leecad(usuario.apellido, MAX);
 
				printf("\tContrase�a: ");
				leecad(usuario.password, MAX);
 
					/* Se inserta el usuario en el archivo */
				if (ingresarUsuario(usuario)) {
				printf("\n\tEl usuario fue insertado correctamente\n");
 				}
			
				else {
					printf("\n\tOcurrio un error al intentar ingresar el usuario\n");
					printf("\tIntentelo mas tarde\n");
				}
			}

			else {
			/* El usuario ya existe, no puede ser insertado. */
			printf("\n\tEl usuario con la cedula %d ya existe.\n", cedula);
			printf("\tNo puede ingresar dos usuarios distintos con la misma cedula\n");
			}
 
			printf("\n\tDesea seguir ingresando usuarios? [S/N]: ");
			leecad(respuesta, MAX);
 
			if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
			}
 
		}
		
	} while (repite);
}

void menuBuscar_usuario()
 {
	User *usuarios;
	User usuario;
	int numeroUsuarios;
	int cedula;
	char repite = 1;
	char respuesta[MAX];
	
	system("cls");
	usuarios = obtenerUsuarios(&numeroUsuarios); /* Retorna un vector dinamico de usuarios */

 	if (numeroUsuarios == 0) {
		printf("\n\tEl archivo esta vacio!!\n");
		system("pause>nul");
	} 
	
	else {		
		do {
	
			system("cls");
			printf("\n\n\t\t\t BUSCAR USUARIO POR CEDULA \n");
 
			/* Se pide la ci del usuario a buscar */
			printf("\n\tCedula: ");
			leecad(linea, MAX);
			sscanf(linea,"%d", &cedula);
						
			if (cedula == 0){
				printf("\n\tDesea continuar? [S/N]: ");
				leecad(respuesta, MAX);
 
				if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
				repite = 0;
				}
			}

			else {
 
				/* Se verifica que el usuario a buscar, exista */
				if (existeUsuario(cedula, &usuario)) {

				/* Se muestran los datos del usuario */
				printf("\tUsuario: %s \n", usuario.n_usuario);
				printf("\tNombre: %s\n", usuario.nombre);		
				printf("\tApellido: %s\n", usuario.apellido);			

				} 
				else {
					/* El usuario no existe */
					printf("\n\tEl usuario con la cedula %d no existe.\n", cedula);
				};
 
				printf("\n\tDesea seguir buscando algun usuario? [S/N]: ");
				leecad(respuesta, MAX);
	
				if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
				{
					repite = 0;
				}
			}
		}	
		while (repite);
	}
}
 


void menuModificar_usuario()
{
	User *usuarios;
	int numeroUsuarios;
	FILE *archivo;
	User usuario;
	int cedula;
	int opcion = -1;
	char repite = 1;
	char existe;
	char respuesta[MAX];
	
	system("cls");
	usuarios = obtenerUsuarios(&numeroUsuarios); /* Retorna un vector dinamico de usuarios */

 	if (numeroUsuarios == 0) {
		printf("\n\tEl archivo esta vacio!!\n");
		system("pause>nul");
	} 
	
	else {		
 
	do {
		system("cls");
		printf("\n      MODIFICAR UN USUARIO   \n");

		printf("\t-----------------------------------\n");
		printf("\t", "OPCIONES PARA MODIFICAR");
		printf("\t-----------------------------------\n");
		printf("\t1. Modificar el nombre del usuario \n");
		printf("\t2. Modificar el apellido del usuario \n");
		printf("\t3. Modificar la cedula del usuario \n");	
 
		/* Se pide la cedula del usuario a modificar */
		printf("\n\tCedula del usuario: ");
		leecad(linea, MAX);
		sscanf(linea, "%d", &cedula);
								
			if (cedula == 0){
				printf("\n\tDesea continuar? [S/N]: ");
				leecad(respuesta, MAX);
 
				if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
				repite = 0;
				}
			}

			else {

		/* Se verifica que el usuario a buscar exista */
		if (existeUsuario(cedula, &usuario)) {
			
			/* Se muestran los datos del usuario */
			printf("\n\tNombre: %s\n", usuario.nombre);
			printf("\tApellido: %s\n", usuario.apellido);
			printf("\tCedula: %d\n", usuario.cedula);
			printf("\n\n        Elija que dato quiere modificar?: [ ]\b\b");
			leecad(linea, MAX);
			sscanf(linea, "%d", &opcion);

		/* Abre el archivo para lectura/escritura */
		archivo = fopen("usuarios.dat", "rb+");
 
		if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */} 
		else {

		switch (opcion){
		
			case 1:
				printf("\n Nombre del usuario actual: %s \n", usuario.nombre);
				printf("\tIngrese nuevo nombre: ");
				scanf("%s", &usuario.nombre);
				eliminarUsuario(cedula);
				eliminacionFisica_usuario();
  	            fwrite(&usuario, sizeof(User), 1, archivo);
    	        printf("\tSe modifico el nombre del usuario\n");
        	   break;

			case 2:
				printf("\n\tApellido del usuario actual: %s\n", usuario.apellido);
				printf("\n\tIngrese nuevo el nuevo apellido: ");
                scanf("%s",&usuario.apellido);
                eliminarUsuario(cedula);
				eliminacionFisica_usuario();
                fwrite(&usuario, sizeof(User), 1, archivo);
                printf("\tSe modifico el apellido del usuario\n");
				break;

			case 3:
				printf("\n\tNumero de cedula actual del usuario: %d\n", usuario.cedula);
				printf("\n\tIngrese la nueva cedula: ");
                scanf("%d",&usuario.cedula);
                eliminarUsuario(cedula);
				eliminacionFisica_usuario();
                fwrite(&usuario, sizeof(User), 1, archivo);
                printf("\tSe modifico la cedula del usuario\n");
				break;

			}

		}fclose(archivo); }

		else {
			/* El usuario no existe */
			printf("\n\tEl usuario de cedula %d no existe.\n", cedula);
		}
 
		printf("\n\tDesea modificar algun otro usuario? [S/N]: ");
		leecad(respuesta, MAX);
 
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
			}
			}
 		}while (repite);
	}
}
 
void menuEliminar_usuario()
{
	User *usuarios;
	User usuario;
	int cedula;
	char repite = 1;
	char respuesta[MAX];
	int numeroUsuarios;

	system("cls");
	usuarios = obtenerUsuarios(&numeroUsuarios); /* Retorna un vector dinamico de usuarios */

 	if (numeroUsuarios == 0) {
		printf("\n\tEl archivo esta vacio!!\n");
		system("pause>nul");
	} 
	
	else {		
	
	do {
		system("cls");
		printf("\n\t\t\t    ELIMINAR UN USUARIO POR CEDULA   \n");
 
		/* Se pide el placa del usuario a eliminar */
		printf("\n\tCEDULA DEL USUARIO: ");
		leecad(linea, MAX);
		sscanf(linea, "%d", &cedula);
								
			if (cedula == 0){
				printf("\n\tDesea continuar? [S/N]: ");
				leecad(respuesta, MAX);
 
				if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
				repite = 0;
				}
			}

			else {
 
		/* Se verifica que el usuario a buscar, exista */
		if (existeUsuario(cedula, &usuario)) {
 
			/* Se muestran los datos del usuario */
			printf("\n\tNombre del usuario: %s\n", usuario.n_usuario);
			printf("\n\tNombre del usuario: %s\n", usuario.nombre);
			printf("\tApellido del usuario: %s\n", usuario.apellido);
			printf("\tCedula: %d\n", usuario.cedula);
 
			printf("\n\tSeguro que desea eliminar el usuario? [S/N]: ");
			leecad(respuesta, MAX);
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				if (eliminarUsuario(cedula) && eliminacionFisica_usuario()) {
					printf("\n eliminado satisfactoriamente.\n");
				} else {
					printf("\n\tEl usuario no pudo ser eliminado\n");
				}
			}
 
		} else {
			/* El usuario no existe */
			printf("\n\tEl usuario de cedula %d no existe.\n", cedula);
		}
 
		printf("\n\tDesea eliminar otro usuario? [S/N]: ");
		leecad(respuesta, MAX);
 
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}
 
		}
		} while (repite);
	}
}
 
  
User *obtenerUsuarios(int *n)
{
	FILE *archivo;
	User usuario;
	User *usuarios; /* Vector dinamico de usuarios */
	int i;
 
	/* Abre el archivo en modo lectura */
	archivo = fopen("usuarios.dat", "rb");
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		*n = 0; /* No se pudo abrir. Se considera n  */
		usuarios = NULL;
 
	} else {
 
		fseek(archivo, 0, SEEK_END); /* Posiciona el cursor al final del archivo */
		*n = ftell(archivo) / sizeof(User); /* # de usuarios almacenados en el archivo. (# de registros) */
		usuarios = (User *)malloc((*n) * sizeof(User)); /* Se reserva memoria para todos los usuarios almacenados en el archivo */
 
		/* Se recorre el archivo secuencialmente */
		fseek(archivo, 0, SEEK_SET); /* Posiciona el cursor al principio del archivo */
		fread(&usuario, sizeof(usuario), 1, archivo);
		i = 0;
		while (!feof(archivo)) {
			usuarios[i++] = usuario;
			fread(&usuario, sizeof(usuario), 1, archivo);			
		}
 
		/* Cierra el archivo */
		fclose(archivo);
	}
 
	return usuarios;
}
 
char existeUsuario(int cedula, User *usuario)
{
	FILE *archivo;
	char existe;
 
	/* Abre el archivo en modo lectura */
	archivo = fopen("usuarios.dat", "rb");
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		existe = 0;
 
	} else {
		existe = 0;
 
		/* Se busca el usuario cuyo cedula coincida */
		fread(&(*usuario), sizeof(*usuario), 1, archivo);
		while (!feof(archivo)) {
			if ((*usuario).cedula == cedula) {
				existe = 1;
				break;
			}
			fread(&(*usuario), sizeof(*usuario), 1, archivo);
		}
 
		/* Cierra el archivo */
		fclose(archivo);
	}
 
	return existe;
}
 
 
char ingresarUsuario(User usuario)
{
	FILE *archivo;
	char insercion;
 
	/* Abre el archivo para agregar datos al final */
	archivo = fopen("usuarios.dat", "ab");	/* Añade datos al final. Si el archivo no existe, es creado */
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		insercion = 0;
 
	} else {
		fwrite(&usuario, sizeof(usuario), 1, archivo);
		insercion = 1;
 
		/* Cierra el archivo */
		fclose(archivo);
	}
 
	return insercion;
}
 
/* ELiminacion logica de un registro */
char eliminarUsuario(int cedula)
{
	FILE *archivo;
	FILE *auxiliar;
	User usuario;
	char elimina;
 
	/* Abre el archivo para leer */
	archivo = fopen("usuarios.dat", "r+b");	/* Modo lectura/escritura. Si el archivo no existe, es creado */
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		elimina = 0;
 
	} else {
		/* Se busca el registro que se quiere borrar. Cuando se encuentra, se situa en esa posicion mediante la 
		funcion fseek y luego se modifica el campo clave de ese registro mediante algun valor centinela, eso se logra 
		con fwrite. Hasta alli se ha logrado una eliminacion LOGICA. Porque el registro sigue ocupando espacio en el archivo fisico */
 
		elimina = 0;
		fread(&usuario, sizeof(usuario), 1, archivo);
		while (!feof(archivo)) {
			if (usuario.cedula == cedula) {
				fseek(archivo, ftell(archivo) - sizeof(usuario), SEEK_SET);
				usuario.cedula = VALOR_CENTINELA;
				fwrite(&usuario, sizeof(usuario), 1, archivo);
				elimina = 1;
				break;
			}
			fread(&usuario, sizeof(usuario), 1, archivo);
		}
 
		/* Cierra el archivo */
		fclose(archivo);
	}
 
	return elimina;
}
 
char eliminacionFisica_usuario()
{
	FILE *archivo;
	FILE *temporal;
	User usuario;
	char elimina = 0;
 
	archivo = fopen("usuarios.dat", "rb");
	temporal = fopen("temporal.dat", "wb");
 
	if (archivo == NULL || temporal == NULL) {
		elimina = 0;
	} else {
		/* Se copia en el archivo temporal los registros validos */
		fread(&usuario, sizeof(usuario), 1, archivo);
		while (!feof(archivo)) {
			if (usuario.cedula != VALOR_CENTINELA) {
				fwrite(&usuario, sizeof(usuario), 1, temporal);
			}
			fread(&usuario, sizeof(usuario), 1, archivo);
		}
		/* Se cierran los archivos antes de borrar y renombrar */
		fclose(archivo);
		fclose(temporal);
 
		remove("usuarios.dat");
		rename("temporal.dat", "usuarios.dat");
 
		elimina = 1;
	}
 
	return elimina;
}


// >>>>>>FUNCIONES PARA CLIENTES<<<<<<<<<<<<

void menuCliente()
{
	char repite = 1;
	int opcion = -1;
	/* Cuando el usuario ingresa texto en lugar de ingresar una opcion. El programa no modifica
	el valor de opcion. En ese caso, no se debe de ingresar a ninguno de los case, por eso se esta
	inicializando la variable opcion con un valor que no permita ejecutar ningun case. Simplemente,
	volver a interar y pedir nuevamente la opcion. */
 
	do {
 
		system( "COLOR 2" );//con esto solo cambiamos el color de nuestra fuente
		system("cls");
 
 
		printf("\n         MENU DE CLIENTES         \n");
		printf("\n[1] Registrar nuevo cliente \n");
		printf("\n[2] Buscar datos de cliente \n");
		printf("\n[3] Modificar informacion de un cliente \n");
		printf("\n[4] Eliminar datos de un cliente \n");
		printf("\n[0] Salir\n");
		printf("\nQue deseas hacer?: [ ]\b\b");
 
		/* Lectura segura de un entero */
		leecad(linea, MAX);
		sscanf(linea, "%d", &opcion);
 
		switch (opcion) {
 
			case 1:
				menuIngresar_cliente();
				break;
 
			case 2:
				menuBuscar_cliente();
				break; 
 
			case 3:
				menuModificar_cliente();
				break;
 
			case 4:
				menuEliminar_cliente();
				break;
 
			case 0:
				repite = 0;
				break;
		}
 
	} while (repite);
}

void menuIngresar_cliente()
{
	Client cliente;
	int cedula = 0;
	char repite = 1;
	char respuesta[MAX];
 
	do {
		system("cls");
		printf("SISTEMA DE INGRESO DE CLIENTES \n");
 
		/* Se pide la cedula del usuarios a ingresar */
		printf("\n\tCedula del cliente: ");
		leecad(linea, MAX);
		sscanf(linea, "%d", &cedula);
 
		/* Se verifica que el usuarios no haya sido almacenado anteriormente */
		
		if (cedula == 0){
			printf("\n\tDesea continuar? [S/N]: ");
			leecad(respuesta, MAX);
 
			if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
			}
		}
		else
		{
			if (!existeCliente(cedula, &cliente)) {
 
				cliente.cedula = cedula;
	
				/* Se piden los demas datos del cliente a ingresar */
				printf("\tNombre de cliente: ");
				leecad(cliente.nombre, MAX);
 
				printf("\tApellido: ");
				leecad(cliente.apellido, MAX);
 
				printf("\tEdad: ");
				leecad(linea, MAX);
				sscanf(linea, "%d", &cliente.edad);
				
				cliente.compras=0;
 
					/* Se inserta el cliente en el archivo */
				if (ingresarCliente(cliente)) {
				printf("\n\tEl cliente fue insertado correctamente\n");
 				}
			
				else {
					printf("\n\tOcurrio un error al intentar ingresar el cliente\n");
					printf("\tIntentelo mas tarde\n");
				}
			}

			else {
			/* El cliente ya existe, no puede ser insertado. */
			printf("\n\tEl cliente con la cedula %d ya existe.\n", cedula);
			printf("\tNo puede ingresar dos clientes distintos con la misma cedula\n");
			}
 
			printf("\n\tDesea seguir ingresando clientes? [S/N]: ");
			leecad(respuesta, MAX);
 
			if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
			}
 
		}
		
	} while (repite);
}

void menuBuscar_cliente()
 {
	Client *clientes;
	Client cliente;
	int numeroClientes;
	int cedula;
	char repite = 1;
	char respuesta[MAX];
	
	system("cls");
	clientes = obtenerClientes(&numeroClientes); /* Retorna un vector dinamico de CLIENTES */

 	if (numeroClientes == 0) {
		printf("\n\tEl archivo esta vacio!!\n");
		system("pause>nul");
	} 
	
	else {		
		do {
	
			system("cls");
			printf("\n\n\t\t\t BUSCAR CLIENTE POR CEDULA \n");
 
			/* Se pide la ci del cliente a buscar */
			printf("\n\tCedula: ");
			leecad(linea, MAX);
			sscanf(linea,"%d", &cedula);
						
			if (cedula == 0){
				printf("\n\tDesea continuar? [S/N]: ");
				leecad(respuesta, MAX);
 
				if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
				repite = 0;
				}
			}

			else {
 
				/* Se verifica que el cliente a buscar, exista */
				if (existeCliente(cedula, &cliente)) {

				/* Se muestran los datos del usuario */
				printf("\tNombre: %s \n", cliente.nombre);
				printf("\tApellido: %s\n", cliente.apellido);		
				printf("\tEdad: %d\n", cliente.edad);
				printf("\tNumero de compras: %d \n",cliente.compras);			

				} 
				else {
					/* El usuario no existe */
					printf("\n\tEl cliente con la cedula %d no existe.\n", cedula);
				};
 
				printf("\n\tDesea seguir buscando algun cliente? [S/N]: ");
				leecad(respuesta, MAX);
	
				if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
				{
					repite = 0;
				}
			}
		}	
		while (repite);
	}
}


void menuModificar_cliente()
{
	Client *clientes;
	int numeroClientes;
	FILE *archivo;
	Client cliente;
	int cedula;
	int opcion = -1;
	char repite = 1;
	char existe;
	char respuesta[MAX];
	
	system("cls");
	clientes = obtenerClientes(&numeroClientes); /* Retorna un vector dinamico de usuarios */

 	if (numeroClientes == 0) {
		printf("\n\tEl archivo esta vacio!!\n");
		system("pause>nul");
	} 
	
	else {		
 
	do {
		system("cls");
		printf("\n      MODIFICAR UN CLIENTE   \n");

		printf("\t-----------------------------------\n");
		printf("\t", "OPCIONES PARA MODIFICAR");
		printf("\t-----------------------------------\n");
		printf("\t1. Modificar el nombre del cliente\n");
		printf("\t2. Modificar el apellido del cliente\n");
		printf("\t3. Modificar la cedula del cliente\n");	
		printf("\t4. Modificar la edad del cliente\n");
 
		/* Se pide la cedula del usuario a modificar */
		printf("\n\tCedula del cliente: ");
		leecad(linea, MAX);
		sscanf(linea, "%d", &cedula);
								
			if (cedula == 0){
				printf("\n\tDesea continuar? [S/N]: ");
				leecad(respuesta, MAX);
 
				if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
				repite = 0;
				}
			}

			else {

		/* Se verifica que el usuario a buscar exista */
		if (existeCliente(cedula, &cliente)) {
			
			/* Se muestran los datos del usuario */
			printf("\n\tNombre: %s\n", cliente.nombre);
			printf("\tApellido: %s\n", cliente.apellido);
			printf("\tCedula: %d\n", cliente.cedula);
			printf("\tEdad: %d\n", cliente.edad);
			printf("\n\n        Elija que dato quiere modificar?: [ ]\b\b");
			leecad(linea, MAX);
			sscanf(linea, "%d", &opcion);

		/* Abre el archivo para lectura/escritura */
		archivo = fopen("clientes.dat", "rb+");
 
		if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */} 
		else {

		switch (opcion){
		
			case 1:
				printf("\n\tNombre del cliente actual: %s \n", cliente.nombre);
				printf("\tIngrese nuevo nombre: ");
				scanf("%s", &cliente.nombre);
  	            fwrite(&cliente, sizeof(Client), 1, archivo);
    	        printf("\tSe modifico el nombre del cliente\n");
        	   break;

			case 2:
				printf("\n\tApellido del cliente actual: %s\n", cliente.apellido);
				printf("\n\tIngrese nuevo el nuevo apellido: ");
                scanf("%s",&cliente.apellido);
                eliminarCliente(cedula);
                eliminacionFisica_cliente();
                fwrite(&cliente, sizeof(Client), 1, archivo);
                printf("\tSe modifico el apellido del cliente\n");
				break;

			case 3:
				printf("\n\tNumero de cedula actual del cliente: %d\n", cliente.cedula);
				printf("\n\tIngrese la nueva cedula: ");
                scanf("%d",&cliente.cedula);
                eliminarCliente(cedula);
                eliminacionFisica_cliente();
                fwrite(&cliente, sizeof(Client), 1, archivo);
                printf("\tSe modifico la cedula del cliente\n");
				break;
			
			case 4:
				printf("\n\tNumero de edad actual del cliente: %d\n", cliente.edad);
				printf("\n\tIngrese la nueva edad: ");
                scanf("%d",&cliente.edad);
                eliminarCliente(cedula);
                eliminacionFisica_cliente();
                fwrite(&cliente, sizeof(Client), 1, archivo);
                printf("\tSe modifico la edad del cliente\n");
				break;

			}

		}fclose(archivo); }

		else {
			/* El usuario no existe */
			printf("\n\tEl cliente de cedula %d no existe.\n", cedula);
		}
 
		printf("\n\tDesea modificar algun otro cliente? [S/N]: ");
		leecad(respuesta, MAX);
 
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
			}
			}
 		}while (repite);
	}
}
 
void menuEliminar_cliente()
{
	Client *clientes;
	Client cliente;
	int cedula;
	char repite = 1;
	char respuesta[MAX];
	int numeroClientes;

	system("cls");
	clientes = obtenerClientes(&numeroClientes); /* Retorna un vector dinamico de usuarios */

 	if (numeroClientes== 0) {
		printf("\n\tEl archivo esta vacio!!\n");
		system("pause>nul");
	} 
	
	else {		
	
	do {
		system("cls");
		printf("\n\t\t\t    ELIMINAR UN CLIENTE POR CEDULA   \n");
 
		/* Se pide el placa del usuario a eliminar */
		printf("\n\tCEDULA DEL CLIENTE: ");
		leecad(linea, MAX);
		sscanf(linea, "%d", &cedula);
								
			if (cedula == 0){
				printf("\n\tDesea continuar? [S/N]: ");
				leecad(respuesta, MAX);
 
				if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
				repite = 0;
				}
			}

			else {
 
		/* Se verifica que el usuario a buscar, exista */
		if (existeCliente(cedula, &cliente)) {
 
			/* Se muestran los datos del usuario */
			printf("\n\tNombre del cliente: %s\n", cliente.nombre);
			printf("\tApellido del cliente: %s\n", cliente.apellido);
			printf("\tEdad del cliente: %d\n", cliente.edad);
			printf("\tCedula: %d\n", cliente.cedula);
 
			printf("\n\tSeguro que desea eliminar los datos del cliente? [S/N]: ");
			leecad(respuesta, MAX);
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				if (eliminarCliente(cedula) && eliminacionFisica_cliente()) {
					printf("\n\teliminado satisfactoriamente.\n");
				} else {
					printf("\n\tEl cliente no pudo ser eliminado\n");
				}
			}
 
		} else {
			/* El usuario no existe */
			printf("\n\tEl cliente de cedula %d no existe.\n", cedula);
		}
 
		printf("\n\tDesea eliminar otro cliente? [S/N]: ");
		leecad(respuesta, MAX);
 
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}
 
		}
		} while (repite);
	}
}
 
  
Client *obtenerClientes(int *n)
{
	FILE *archivo;
	Client cliente;
	Client *clientes; /* Vector dinamico de usuarios */
	int i;
 
	/* Abre el archivo en modo lectura */
	archivo = fopen("clientes.dat", "rb");
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		*n = 0; /* No se pudo abrir. Se considera n  */
		clientes = NULL;
 
	} else {
 
		fseek(archivo, 0, SEEK_END); /* Posiciona el cursor al final del archivo */
		*n = ftell(archivo) / sizeof(Client); /* # de usuarios almacenados en el archivo. (# de registros) */
		clientes = (Client *)malloc((*n) * sizeof(Client)); /* Se reserva memoria para todos los usuarios almacenados en el archivo */
 
		/* Se recorre el archivo secuencialmente */
		fseek(archivo, 0, SEEK_SET); /* Posiciona el cursor al principio del archivo */
		fread(&cliente, sizeof(cliente), 1, archivo);
		i = 0;
		while (!feof(archivo)) {
			clientes[i++] = cliente;
			fread(&cliente, sizeof(cliente), 1, archivo);			
		}
 
		/* Cierra el archivo */
		fclose(archivo);
	}
 
	return clientes;
}
 
char existeCliente(int cedula, Client *cliente)
{
	FILE *archivo;
	char existe;
 
	/* Abre el archivo en modo lectura */
	archivo = fopen("clientes.dat", "rb");
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		existe = 0;
 
	} else {
		existe = 0;
 
		/* Se busca el usuario cuyo cedula coincida */
		fread(&(*cliente), sizeof(*cliente), 1, archivo);
		while (!feof(archivo)) {
			if ((*cliente).cedula == cedula) {
				existe = 1;
				break;
			}
			fread(&(*cliente), sizeof(*cliente), 1, archivo);
		}
 
		/* Cierra el archivo */
		fclose(archivo);
	}
 
	return existe;
}
 
 
char ingresarCliente(Client cliente)
{
	FILE *archivo;
	char insercion;
 
	/* Abre el archivo para agregar datos al final */
	archivo = fopen("clientes.dat", "ab");	/* Añade datos al final. Si el archivo no existe, es creado */
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		insercion = 0;
 
	} else {
		fwrite(&cliente, sizeof(cliente), 1, archivo);
		insercion = 1;
 
		/* Cierra el archivo */
		fclose(archivo);
	}
 
	return insercion;
}
 
/* ELiminacion logica de un registro */
char eliminarCliente(int cedula)
{
	FILE *archivo;
	FILE *auxiliar;
	Client cliente;
	char elimina;
 
	/* Abre el archivo para leer */
	archivo = fopen("clientes.dat", "r+b");	/* Modo lectura/escritura. Si el archivo no existe, es creado */
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		elimina = 0;
 
	} else {
		/* Se busca el registro que se quiere borrar. Cuando se encuentra, se situa en esa posicion mediante la 
		funcion fseek y luego se modifica el campo clave de ese registro mediante algun valor centinela, eso se logra 
		con fwrite. Hasta alli se ha logrado una eliminacion LOGICA. Porque el registro sigue ocupando espacio en el archivo fisico */
 
		elimina = 0;
		fread(&cliente, sizeof(cliente), 1, archivo);
		while (!feof(archivo)) {
			if (cliente.cedula == cedula) {
				fseek(archivo, ftell(archivo) - sizeof(cliente), SEEK_SET);
				cliente.cedula = VALOR_CENTINELA;
				fwrite(&cliente, sizeof(cliente), 1, archivo);
				elimina = 1;
				break;
			}
			fread(&cliente, sizeof(cliente), 1, archivo);
		}
 
		/* Cierra el archivo */
		fclose(archivo);
	}
 
	return elimina;
}
 
char eliminacionFisica_cliente()
{
	FILE *archivo;
	FILE *temporal;
	Client cliente;
	char elimina = 0;
 
	archivo = fopen("clientes.dat", "rb");
	temporal = fopen("temporal.dat", "wb");
 
	if (archivo == NULL || temporal == NULL) {
		elimina = 0;
	} else {
		/* Se copia en el archivo temporal los registros validos */
		fread(&cliente, sizeof(cliente), 1, archivo);
		while (!feof(archivo)) {
			if (cliente.cedula != VALOR_CENTINELA) {
				fwrite(&cliente, sizeof(cliente), 1, temporal);
			}
			fread(&cliente, sizeof(cliente), 1, archivo);
		}
		/* Se cierran los archivos antes de borrar y renombrar */
		fclose(archivo);
		fclose(temporal);
 
		remove("clientes.dat");
		rename("temporal.dat", "clientes.dat");
 
		elimina = 1;
	}
 
	return elimina;
}
 
int leecad(char *cad, int n)
{
	int i, c;
 
	/* Hay que verificar si el buffer esta limpio o si hay un '\n'
	  dejado por scanf y, en ese caso, limpiarlo:
	*/
 
	/* 1 COMPROBACION DE DATOS INICIALES EN EL BUFFER */
 
	/* Empezamos leyendo el primer caracter que haya en la entrada. Si es
	  EOF, significa que no hay nada por leer, asi que cerramos la cadena,
	  dejandola "vacia" y salimos de la funcion retornando un valor de 0
	  o falso, para indicar que hubo un error */
	c = getchar();
	if (c == EOF) {
		cad[0] = '\0';
		return 0;
	}
 
	/* Si el valor leido es '\n', significa que habia un caracter de nueva linea
	dejado por un scanf o funcion similar. Simplemente inicializamos i a 0,
	para indicar que los siguientes caracteres que leamos iremos asignando a
	partir del primer caracter de la cadena. */
	if (c == '\n') {
		i = 0;
	} else {
	/* Si no habia un '\n', significa que el caracter que leimos es el primer
	  caracter de la cadena introducida. En este caso, lo guardamos en la
	  posicion 0 de cad, e inicializamos i a 1, porque en este caso, como ya
	  tenemos el primer caracter de la cadena, continuaremos agregando 
	  caracteres a partir del segundo.
 
	*/
		cad[0] = c;
		i = 1;
	}
 
	/* 2. LECTURA DE LA CADENA */
 
	/* El for empieza con un ; porque estamos omitiendo la inicializacion del contador,
	ya que fue inicializado en el punto anterior.
	Este placa lee un caracter a la vez,lo agrega a cad, y se repite hasta que
	se encuentre un fin de linea, fin de archivo, o haya leido la cantidad maxima
	de caracteres que se le indico. Luego, cierra la cadena agregando un '\0'
	al final. Todo esto es muy similar a la forma en que los compiladores suelen
	implementar la funcion fgets, solo que en lugar de getchar usan getc o fgetc
	*/
	for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		cad[i] = c;
	}
	cad[i] = '\0';
 
	/*3. LIMPIEZA DEL BUFFER */
 
	/* Finalmente limpiamos el buffer si es necesario */
	if (c != '\n' && c != EOF) /* es un caracter */
		while ((c = getchar()) != '\n' && c != EOF);
 
	/* La variable c contiene el ultimo caracter leido. Recordemos que habia 3 formas
	de salir del for: que hayamos encontrando un '\n', un EOF, o que hayamos llegado
	al maximo de caracteres que debemos leer. Si se da cualquiera de los dos
	primeros casos, significa que leimos todo lo que habia en el buffer, por lo que
	no hay nada que limpiar. En el tercer caso, el usuario escribio mas caracteres
	de los debidos, que aun estan en el buffer, por lo que hay que quitarlos, para
	lo cual usamos el metodo que vimos poco mas arriba
	*/
 
	return 1;
}

// Fin Funciones de usuarios y clientes
 
// main
