#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int menu();
int menu_productos (int user);
int menu_usuario_productos1();

int main () {
  int init=0;
  menu;
  init=menu;
  switch (init)
  {
    case 1:
    /* code */
    break;  

    case 2:
    /* code */
    break;

    case 3:
    /* code */
    break;

    case 4:
    /* code */
    break;

    case 5:
    /* code */
    break;

    default:
    /* code */
    break;
  }
  return 0;
}

int menu_productos(int user)
{
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
    printf("\n5 - Si desea salir del sistema");
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
    printf("\n5 - Si desea cancelar su compra");
    scanf("%d", &election);
  }
  else
  {
    printf("Ha ocurrido un error, no se le reconoce en el sistema");
  }
  return election;
}
