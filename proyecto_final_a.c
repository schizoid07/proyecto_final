#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int menu(); //Función correspondiente al menú principal

int menu_productos (int user); /*Función que ejecuta un sub-menú 
                                  dedicado al apartado de productos*/

void continuar();//Función que pausa la ejecución hasta que el usuario indique
void creaStock();//Función que genera un archivo con el stock de productos
void imprimeStock();//Función que imprime el stock de productos
void modificarPrecio();
void modificarCantidad();
void modificarNombre();
void modificarCodigo();
void vaciaStoctk();
void menuModificar();

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
    printf("Opcion no existente"); //Mensaje en caso de ingresar una respuesta no esperada
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
      while(!feof(archivo))
      {
        if(producto==modifx.codigo)
        {
          printf("\nProducto: %s", modifx.nombre);
          printf("\nCodigo: %d", modifx.codigo);
          printf("\nExistencias: %d", modifx.unidades);
          printf("\nPrecio: %.2f", modifx.precio);
          printf("\n_________________________________");
          printf("\nIngrese el nuevo precio del producto\n");
          scanf("%f", &modifx.precio); 
          int n = ftell(archivo) - sizeof(d_producto);
          fseek(archivo, n, SEEK_SET);
          fwrite(&modifx, sizeof(d_producto), 1, archivo);
          existe = 1;
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
void modificarNombre()
{
  system("cls");
  int  codigo, existe=0;
  char a, producto[30];
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
          fflush(stdin);
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
  
  if (remove("Stock.db") == 0)
  {
    printf("\nSu Stock ha sido reestablecido");
  }
  else
  {
    printf("\nNo se ha podido vaciar el stock");
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
      printf("\nDigite un valor correspondiente a las opciones brindadas");
      break;
    }
  } while (op1 != 5);

  printf("\nreturn %d",op1);
  
  
}