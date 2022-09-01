#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

int menu(); //Función correspondiente al menú principal

int menu_productos (int user); /*Función que ejecuta un sub-menú 
                                  dedicado al apartado de productos*/

void continuar();//Función que pausa la ejecución hasta que el usuario indique
void creaStock();//Función que genera un archivo con el stock de productos
void imprimeStock();//Función que imprime el stock de productos
void modificarPrecio();//Función que permite modificar el precio de un producto
void modificarCantidad();//Función que permite modificar la cantidad de existencais de un producto
void modificarNombre();//Función que permite modificar el nombre de un producto
void modificarCodigo();//Función que permite modificar el codigo de un producto
void vaciaStoctk();//Función que elimina el archivo correspondiente al Stock
void menuModificar();//Función que invoca un menu el cual se encarga de todas las funciones modificar

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
{
  char nombre[100];
  int unidades, codigo;
  float precio;
} d_producto;

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
  int elect, op1;
  do
  {
    elect = menu_productos(1); //Llamada al sub-menú de productos
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
  } while (elect != 5);/*Un bucle que no finalizará hasta 
                        que el usuario indique, por lo que 
                        el programa mostrará el menú constantemente*/
  
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
    scanf("%d", &election); //Guarda la elección del usuario
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
    scanf("%d", &election); //Guarda la elección del usuario
  }
  else
  {
    printf("Ha ocurrido un error, no se le reconoce en el sistema");/*Mensaje de error en caso 
                                                                      de que la variable no coincida
                                                                      por lo cual no se le reconozca 
                                                                      ni como usuario o admin*/
  }
  return election;//Devuelve la elección
}
void continuar()
{
  printf("\n\n");/*Un mensaje para indicar a el usuario 
                                                          qué hacer cuando se pause el programa*/
  system("pause");//Pausa el programa
}
void creaStock()
{
  system("cls");//Limpia pantalla

  int n = 0; 
  FILE *archivo; //Puntero para los archivos .db
  archivo=fopen("Stock.db", "ab"); /*Busca un archivo llamado Stock, debido a los atributos 
                                    en caso de no existir lo crea y en caso de que sí, todo 
                                    lo que se escriba se añade al archivo existente en binario*/

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
        
        printf("\n\nDigite segun corresponda: "); /*Pequeño sub-menu que permite al usuario indicar el número 
                                                    de veces que va a añadir un producto*/
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
                                                con el final del archivo o algún tipo de error*/
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
          printf("\nSe ha modificado con éxito el producto.");  
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

