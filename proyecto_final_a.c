#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int menu();
int menu_productos (int user);

void continuar();
int creaStock();
void imprimeStock();

typedef struct datosUsuario
{
  char nombre[20], apellido[20], tipoDeCuenta[10];
  int cedula, numeroDeCuenta;
} d_usuario;
typedef struct datosProducto
{
  char nombre[15];
  int unidades;
  float precio;
} d_producto;
typedef struct datosTemporales
{
  int itera;
} temporal;

int main () {
  int elect;
  do
  {
    elect = menu_productos(1);
  switch (elect)
  {
  case 1:
    imprimeStock();
    break;
  
  case 2:
    creaStock();
    break;

  case 3:
    break;

  default:
    printf("Opcion no existente");
    break;
  }
  } while (elect != 3);
  
  return 0;
}

int menu_productos(int user)
{
  system("cls");
  int election; 

  if(user == 1)
  {
    printf("\nBienvenido al sub-menu de productos para usuarios");
    printf("\nDigite según sus necesidades:");
    printf("\n____________________________________________________");
    printf("\n1 - Si desea revisar el stock de productos");
    printf("\n2 - Si desea retirar productos del stock");
    printf("\n3 - Si desea añadir productos al stock");
    printf("\n4 - Si desea vaciar el stock");
    printf("\n5 - Si desea salir del sistema\n");
    scanf("%d", &election);
  }
  else if (user == 0)
  {
    printf("\nBienvenido al sub-menu de productos para clientes");
    printf("\nDigite según sus necesidades:");
    printf("\n____________________________________________________");
    printf("\n1 - Si desea añadir productos al carro de compra");
    printf("\n2 - Si desea retirar producto del carro de compra");
    printf("\n3 - Si desea revisar su carro de compra");
    printf("\n4 - Si desea finalizar su compra");
    printf("\n5 - Si desea cancelar su compra\n");
    scanf("%d", &election);
  }
  else
  {
    printf("Ha ocurrido un error, no se le reconoce en el sistema");
  }
  return election;
}

void continuar()
{
  printf("\n\npresione cualquier tecla para continuar");
  system("pause");
}
int creaStock()
{
  system("cls");

  int i = 0, n = 0, burbuja;
  FILE *archivo, *tempoFile;
  archivo=fopen("Stock.db", "ab");
  d_producto control;
  temporal temp;

  if (archivo == NULL)
  {
    printf("\nError al crear stock");
  }
  else
  {
    do
    {
        printf("\nDigite el nombre del producto: ");
        scanf("%s", &control.nombre);
        printf("\nDigite las existencias del producto: ");
        scanf("%d", &control.unidades);
        printf("\nDigite el precio del producto: ");
        scanf("%f", &control.precio);
        
        printf("\n\nDigite segun corresponda: ");
        printf("\n1- Si desea agregar otro producto ");
        printf("\n2 - Si desea volver al menu anterior \n");
    
        scanf("%d", &n);

        i++;
        fwrite(&control, sizeof(d_producto), i, archivo);
    } while(n!=2);

  }
  
  fclose(archivo);


  tempoFile = fopen("temporal.db", "r+b");

  if (tempoFile == NULL)
  {
    printf("Nulll tempoFile");
  }
  else
  {
  fclose(tempoFile);
  burbuja+=i;
  temp.itera=burbuja;
  tempoFile = fopen("temporal.db", "w+b");
  fwrite(&temp, sizeof(temporal), 1, tempoFile);    
  printf("temp.itera: %d", temp.itera);
  }
  
  
  fclose(tempoFile);
  return burbuja;
  continuar();
}
void imprimeStock()
{

    system("cls");
    int j = 0, itera = 0;
    FILE *archivo, *tempoFile;
    temporal tempo;

    tempoFile = fopen("temporal.db", "rb");
    if (tempoFile == NULL)
    {
      printf("Ha ocurrido un error en la apertura del stock\nCodigo de error: itera");
    }
    else
    {
      fread(&tempo, sizeof(temporal), 1, tempoFile);

      itera += tempo.itera;
      printf("itera+= %d ", tempo.itera);
    }
    fclose(tempoFile);

    archivo = fopen("Stock.db", "rb");
    d_producto imp;
    
    if (archivo == NULL)
    {
      printf("Ha ocurrido un error en la apertura del stock");
    }
    else
    {
      ferror(archivo);
      
        printf("itera: %d", itera);
        fread(&imp, sizeof(d_producto), itera, archivo);

          printf("\nProducto: %s", imp.nombre);
          printf("\nExistencias: %d", imp.unidades);
          printf("\nPrecio: %f", imp.precio);
          printf("\n\n_________________________________");

      fclose(archivo);
    }
    continuar();
}
