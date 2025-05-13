#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}
/*.Cree la función int is_valid(Node * n), para validar si un estado/nodo es válido (cumple con las restricciones del problema). Debe validar que:

No se repitan números en las filas
No se repitan números en las columnas
No se repitan números en las submatrices de 3x3
Si el estado es válido la función retorna 1, si no lo es retorna 0.

Para marcar los números que vayan apareciendo en una fila/columna/submatriz puede usar un arreglo de enteros de largo 10 inicializado con 0s. 
Cada vez que aparezca un número i, verifique que la casilla i del arreglo sea igual a 0, luego márquela con un '1'. Si la casilla es '1' quiere decir que 
el número ya estaba marcado por lo que la fla/columna/submatriz no es válida.*/
int is_valid(Node* n)
{
  //int i,j,k,p;
  return 1;
}

/*Recuerde que los nodos adyacentes son generados aplicando las acciones al estado actual.
Para el caso del ejemplo, la función debería retornar una lista con 9 nodos. Cada uno de ellos idéntico al nodo original pero cambiando el valor de la primera casilla vacía, es decir: sudo[0][2], por 1, 2, ..., 9.
Utilice la función Node* copy(Node* n) para copiar nodos.*/
List* get_adj_nodes(Node* n)
{
    List* list=createList();
    //int vacioJ = -1;
    int vacioI = -1;
    int i, j;
    for(i = 0; i < 9; i++)
    {
      for(j = 0; j < 9; j++)
      {
          if(n->sudo[i][j] == 0)
          {
            //vacioJ = j;
            vacioI = i;
          }
          if(vacioI != -1)break;
      }
      /*Otro por validacion*/
    }if(vacioI == 0)return list;
    
    return list;
}

/*4.Implemente la función int is_final(Node * n). Esta función retorna 1 si el nodo corresponde a un nodo final (es decir, todos los valores de la matriz son distintos a 0) y 0 en caso contrario.
Ya está listo el grafo implícito, ahora necesitamos construir un método de búsqueda que a partir del estado inicial sea capaz de explorar el grafo de manera sistemática hasta alcanzar un nodo final.*/
int is_final(Node* n)
{
    int i, j;
    for(i = 0; i < 9; i++)
    {
      for(j = 0; j < 9; j++)
      {
        //todos los valores de la matriz son distintos a 0
        if(n->sudo[i][j] == 0)return 0;
      }
    }
  return 1; // retorna 1 si el nodo corresponde a un nodo final
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/