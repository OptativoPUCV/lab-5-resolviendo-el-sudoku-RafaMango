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
  int i,j,k,p;
  //para verificar filas
  for(i = 0; i< 9; i++)
  {
    int row[10] = {0};
    for(j= 0; j < 9;j++)
    {
      if(n->sudo[i][j]!= 0){
        if(row[n->sudo[i][j]]== 1)
        {
          return 0; //no es valido
        }
        row[n->sudo[i][j]] = 1;
      }
    }
  }

  //Para verificar columnas
  for(i = 0; i < 9;i++)
  {
    int col[10]= {0};
    for(j = 0; j < 9;j++)
    {
      if(n->sudo[j][i]!= 0)
      {
        if(col[n->sudo[j][i]]== 1)
        {
          return 0; //no es valido
        }
        col[n->sudo[j][i]] = 1;
      }
    }
  }

  //Para verificar submatrices
  for(k = 0; k < 9;k++)
  {
    int sub[10]= {0};
    for(p = 0; p< 9;p++)
    {
      int i = 3*(k/3)+(p/3);
      int j = 3*(k%3)+(p%3);
      if(n->sudo[i][j]!= 0)
      {
        if(sub[n->sudo[i][j]]== 1)
        {
          return 0; //no es valido
        }
        sub[n->sudo[i][j]] = 1;
      }
    }
  }
  return 1;


}

/*Recuerde que los nodos adyacentes son generados aplicando las acciones al estado actual.
Para el caso del ejemplo, la función debería retornar una lista con 9 nodos. Cada uno de ellos idéntico al nodo original pero cambiando el valor de la primera casilla vacía, es decir: sudo[0][2], por 1, 2, ..., 9.
Utilice la función Node* copy(Node* n) para copiar nodos.*/
List* get_adj_nodes(Node* n)
{
  List* list=createList();
  int fila = -1;
  int col = -1;
  int i,j;
  for(i = 0; i < 9 && fila == -1; i++)
  {
    for(j = 0; j < 9 && fila == -1; j++)
    {
      if(n->sudo[i][j]== 0)
      {
        fila = i;
        col = j;
      }
    }
  }
  if(fila == 1 && col == -1)
  {
    return list; //no hay nodos adyacentes
  }
  for(int num = 1; num <= 9; num++)
  {
    Node * new = copy(n);
    new->sudo[fila][col] = num;
    if(is_valid(new))
    {
      pushBack(list,new);
    }
    else
    {
      free(new);
    }
  }

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

/*
Cree un stack S (pila) e inserte el nodo.
Mientras el stack S no se encuentre vacío:
a) Saque y elimine el primer nodo de S.
b) Verifique si corresponde a un estado final, si es así retorne el nodo.
c) Obtenga la lista de nodos adyacentes al nodo.
d) Agregue los nodos de la lista (uno por uno) al stack S.
e) Libere la memoria usada por el nodo.
Si terminó de recorre el grafo sin encontrar una solución, retorne NULL.
Almacene en la variable contador, la cantidad de iteraciones que realiza el algoritmo.
*/
Node* DFS(Node* initial, int* contador)
{
  Stack * pila = createStack();
  pushBack(pila, initial);
  Node* current;

  while(!is_empty(pila))
  {
    current = front(pila);
    popFront(pila);
    (*contador)++;

    if(is_final(current)== 1)
    {
      clean(pila);
      return current;
    }
    List* adj = get_adj_nodes(current);
    Node* nodeAdj = first(adj);
    while(!is_empty(adj))
    {
      push(pila, nodeAdj);
      nodeAdj = nex(adj);
    }
    clean(adj);
    free(current);

  }
  clean(pila);

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