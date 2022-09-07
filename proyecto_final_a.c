#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


                                      /*Funciones*/

/*[1]*/int menuAyuda();//Funcion que ejecuta el submenu de ayuda  
/*[2]*/void mostrarDatos();//Mostrara el nombre del sistema y los datos de los programadores 
/*[3]*/void eliminarDatos_programadores();//Eliminara TODA la informacion existente de los programadores
/*[4]*/void eliminarDatos_sistema();//Eliminara TODA la informacion existente del sistema
/*[5]*/void modificarDatos_programadores();//Modificara la informacion ya sea del nombre del sistema o de los programadores
/*[6]*/void modificarDatos_sistema();//Modificara la informacion ya sea del nombre del sistema o de los programadores
/*[7]*/void introducirDatos_programador();//Sirve para introducir nueva informacion (un nuevo programador  en caso de no existir)
/*[8]*/void introducirDatos_sistema();//  Sirve para introducir nueva informacion (el nombre del sistema en caso de no existir)

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


                             /*------------------------------*/



                                       /*Structs*/
typedef struct {
    char name[50];
    char id[9];
} programador;

typedef struct {
    char nombre_sistema[30];
    char ano_creacion[4];
    char semestre_creacion[30];
} sistema;

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


                                    /*----------------*/


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



                                         /*Funcion Main (Miguel-Menu Ayuda)*/
/*int main () { //Funcion main
  int decision=0;

do {
  decision=menuAyuda();

 switch (decision) {

        case 1:
        mostrarDatos();
            break;

        case 2:
        modificarDatos_programadores();
            break;

        case 3:
        modificarDatos_sistema();
            break;

        case 4:
        eliminarDatos_sistema();
            break;

        case 5:
        eliminarDatos_programadores();
            break;

        case 6:
        introducirDatos_sistema();
            break;

        case 7:
        introducirDatos_programador();
            break;
        
        default:
        printf("Hasta luego, vuelva pronto :)");
        break;
            
    }
    } while (decision!=0);
    
 return 0;
} */






}


                                       /*Funciones Adyacentes*/
/*[1]*/int menuAyuda() { //se encarga de darle las opciones al usuario para elegir que hacer con la informacion del sistema
    system("cls");
    int a=0;
    printf("\t\t\t\tBienvenido al Submenu de ayuda!\n\tIntroduzca el numero correspondiente a la opcion que desee activar:");
    printf("\n\t[0] Salir.");
    printf("\n\t[1] Mostrar la informacion del sistema y los datos de los programadores.");
    printf("\n\t[2] Modificar los datos de los programadores.") ;
    printf("\n\t[3] Modificar los datos del sistema.") ;
    printf("\n\t[4] Eliminar los datos del sistema.");
    printf("\n\t[5] Eliminar  los datos de los programadores.");
    printf("\n\t[6] Ingresar el nombre del sistema (en caso de no haber) ");
    printf("\n\t[7] Ingresar datos de los programadores (en caso de no haber)\n");
    printf("\t\t\t\t<<<");
    scanf("%d",&a);
    system("cls");
    
    return a;   
    

}

                            /*-------------------------------*/


/*[2]*/void mostrarDatos() {
    
    int a=0;
    programador programer;
    sistema sistem;
    FILE *dat_programadores;
    FILE *dat_sistema;
    dat_programadores = fopen("programadores.dat","rb"); //Abre el archivo para lectura de datos en binario
     dat_sistema = fopen("info_sistema.dat","rb");
    if (dat_programadores == NULL|| dat_sistema == NULL) {
    printf("Ha ocurrido un problema al abrir el archivo o el archivo esta vacio\n");
    } else {

        while (fread(&sistem, sizeof(sistem),1,dat_sistema)!=0) {
            printf("\t\tNombre del Sistema: %s\n\t\tAño de creacion: %s\n\t\tSemestre de Creacion: %s\n\n",sistem.nombre_sistema,sistem.ano_creacion,sistem.semestre_creacion);
        }

        while (fread(&programer, sizeof(programador),1,dat_programadores)!=0) {
            a+=1;
            printf("\t\tprogramador [%d]: \n\t\tNombre: %s\n\t\tCedula: %s\n\n",a,programer.name,programer.id);
        }        

    }
fclose(dat_programadores);
fclose( dat_sistema);
system("pause");
}


                            /*-------------------------------*/

/*[3]*/void eliminarDatos_programadores() {
     system("cls");
    FILE *dat_programadores;
        dat_programadores = fopen("programadores.dat","wb");  
    if (dat_programadores == NULL) {
    printf("\n\t\tHa ocurrido un problema al abrir el archivo\n");
    } else {
        system("cls");
        printf("\nLos datos se han borrado exitosamente.\n");
    }
fclose(dat_programadores);
system("pause");
}

                            /*-------------------------------*/

/*[4]*/void eliminarDatos_sistema() {
    FILE *dat_programadores;
        dat_programadores = fopen("info_sistema.dat","wb");  
    if (dat_programadores == NULL) {
    printf("Ha ocurrido un problema al abrir el archivo\n");
    } else {
        system("cls");
        printf("\n\t\tLos datos se han borrado exitosamente.\n");
    }
fclose(dat_programadores);
system("pause");
}

                            /*-------------------------------*/


/*[5]*/void modificarDatos_programadores() {
    system("cls");
    char continuar; int pos=0;
 FILE *dat_programadores;
  dat_programadores = fopen("programadores.dat","r+b");  
    if (dat_programadores == NULL) {
    printf("Ha ocurrido un problema al abrir el archivo\n");
    } else {
        do { 
            printf("\t\tInteroduzca el numero del programador que desea modificar (Ejemplo: [1] -> Primer programador): ");
            
            scanf("%d",&pos);
            int salto=(pos-1)*(sizeof(programador));
            fseek(dat_programadores, salto, 0);
            programador programer;
            printf("Introduzca la nueva informacion del programador a modificar (en caso de ser la misma, repita): \n");
            printf("Nombre:\t<<<");
            scanf("%s",&programer.name);
            printf("\nCedula:\t<<<");
            scanf("%s",&programer.id);
            fwrite(&programer, sizeof(programador), 1, dat_programadores);
            system("cls");
            printf("\n\t\tEl proceso ha sido exitoso :)\n");
            printf("\n\t\tDesea continuar modificando? [S/N]: ");
            scanf("%c",&continuar);
        } while (continuar=='S'||continuar=='s');
        
    }
    fclose(dat_programadores);
    system("pause");

}



                            /*-------------------------------*/

/*[6]*/void modificarDatos_sistema() {
     system("cls");
    char continuar; int pos=0;
 FILE *dat_sistema;
  dat_sistema = fopen("info_sistema.dat","r+b");  
    if (dat_sistema == NULL) {
    printf("Ha ocurrido un problema al abrir el archivo\n");
    } else {
        do { 
            printf("\t\tInteroduzca el numero del programador que desea modificar \n(Ejemplo: [1] -> Primer programador): ");
            scanf("[%d]",&pos);
            int salto=(pos-1)*(sizeof(programador));
            fseek(dat_sistema, salto, 0);
            sistema sistem;
            printf("Introduzca la nueva informacion del sistema (en caso de ser la misma, repita) ");
            printf("\nNombre del sistema:\t<<<");
            scanf("%s",&sistem.nombre_sistema);
            printf("\naño de creacion del sistema::\t<<<");
            scanf("%s",&sistem.ano_creacion);
            printf("\nSemestre de Creacion del sistema: \t<<<");
            scanf("%s",&sistem.semestre_creacion);
            fwrite(&sistem, sizeof(sistema), 1, dat_sistema);
            printf("\n\t\tDesea continuar modificando? [S/N]: ");
            scanf("%c",&continuar);

        } while (continuar=='S'||continuar=='s');
        
    }
    fclose(dat_sistema);
    system("pause");
}
 
                             /*-------------------------------*/


/*[7]*/void introducirDatos_programador() {
    system("cls");
    char continuar; int pos=0;
 FILE *dat_programadores;
  dat_programadores = fopen("programadores.dat","ab");  
    if (dat_programadores == NULL) {
    printf("Ha ocurrido un problema al abrir el archivo\n");
    } else {
        do { 
            programador programer;
            printf("Introduzca la informacion del programador a añadir: ");
            printf("\nNombre del programador: \t<<<");
            scanf("%s",&programer.name);
            printf("\nCedula del programador: \t<<<");
            scanf("%s",&programer.id);
            fwrite(&programer, sizeof(programador), 1, dat_programadores);
            printf("\n\t\tDesea continuar añadiendo a mas programadores? [S/N]: ");
            scanf("%c",&continuar);

        } while (continuar=='S'||continuar=='s');
            system("cls");
            printf("\n\t\tEl proceso ha sido exitoso :)\n");
    }
    fclose(dat_programadores);
    system("pause");
}

                             /*-------------------------------*/

/*[8]*/void introducirDatos_sistema() {
    system("cls");
     int pos=0;
 FILE *dat_sistema;
  dat_sistema = fopen("info_sistema.dat","rb");  
    if (dat_sistema == NULL) {
    printf("Ha ocurrido un problema al abrir el archivo\n");
    } else {
            sistema sistem;
            printf("Introduzca la  informacion del sistema: ");
            printf("\nNombre del sistema: \t<<<");
            scanf("%s",&sistem.nombre_sistema); 
            printf("\nAño de Creacion del sistema: \t<<<");
            scanf("%s",&sistem.ano_creacion);
            printf("\nSemestre de Creacion del sistema: \t<<<");
            scanf("%s",&sistem.semestre_creacion);
            fwrite(&sistem, sizeof(sistema), 1, dat_sistema);
            system("cls");
            printf("\n\t\tEl proceso ha sido exitoso :)\n");
           
        
    }
    fclose(dat_sistema);
    system("pause");
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