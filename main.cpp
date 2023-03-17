#include <iostream>
// se declara el número de nodos
const int size = 6;
const int Ns[size] = {1, 2, 3, 4, 5, 6};
// vease en inarray() y remove_from_array() para entender mejor
int ele = 0;
int vector_dir_i;
int vector_dir_j;
int vector_dir[2] = {0, 1};
// Se crea la estructua del Nodo
typedef struct Nodo {
  // val es el valor del nodo al que se le apunta.
  int val;
  // vector_i y vector_j son las componentes del vector del nodo al que se le
  // apunta.
  int vector_i;
  int vector_j;
  // se le apunta a otro nodo diferente.
  Nodo *next_Node;
} Nodo;

// creo que in_array, append_array y remove_from_array funcionan casi igual que
// en python.
// No se les puede meter 0 como elemento.
bool in_array(int e, int array[], int array_size) {

  for (int i = 0; i < size; i++) {
    if (e == array[i]) {
      ele = i;
      return true;
    }
  }
  return false;
}
void remove_from_array(int e, int array[]) {
  if (in_array(e, array, size) == true) {
    int *ptr;
    // std::cout<<ele << "\n";
    for (int i = ele; i < size; i++) {
      if (i != size - 1) {
        ptr = &array[i];
        *ptr = array[i + 1];
      } else {
        ptr = &array[i];
        *ptr = NULL;
      }
    }
  }
}
void append_array(int e, int array[], int size) {
  bool t_ele = false;
  for (int i = 0; i < size; i++) {
    if (array[i] == 0 && t_ele == false) {
      array[i] = e;
      t_ele = true;
    }
  }
}
void rotacion_izquierda(int vect[]) {

  vector_dir[0] = 0 * vect[0] - 1 * vect[1];
  vector_dir[1] = 1 * vect[0] + 0 * vect[1];
}
void rotacion_derecha(int vect[]) {
  vector_dir[0] = 0 * vect[0] + 1 * vect[1];
  vector_dir[1] = -1 * vect[0] + 0 * vect[1];
}
int rotacion(int vect1[], int vect2[]) {
  int cross_product = vect1[0] * vect2[1] - vect1[1] * vect2[0];
  if (cross_product > 0) {
    rotacion_izquierda(vector_dir);
  } else if (cross_product < 0) {
    rotacion_derecha(vector_dir);
  }
  return cross_product;
}
// se crea la clase grafo
class Graph {
public:
  // se declara un array de los nodos. Cada elemento de el array, contiene las
  // conexiones de un nodo
  Nodo *nodos[size];
  // Se guarda los nodos que hay que tomar para llegar al destino.
  int path[size];
  // Se guarda en paths[x-1] el nodo de origen del nodo "x"
  // ve al metodo "camino_mas_corto" para entender mejor
  int paths[size][size];
  // se guarda la información de los vectores que hay que tomar para llegar al
  // destino
  int instruc[size][2];
  bool path_true = false;
  // se inicializa el grafo
  void init_grafo(void) {
    for (int i = 0; i < size; i++) {
      // se inicializan todos los nodos
      Nodo *nodo = new Nodo;
      // Los valores iniciales del nodo son 0, por eso no se puede utilizar el
      // 0 en las funciones in_array, append_array y remove_from_array
      nodo->val = 0;
      nodo->vector_i = 0;
      nodo->vector_j = 0;
      nodo->next_Node = 0;
      // El nodo "n" se guarda como el elemento "n-1" en el array nodos
      nodos[i] = nodo;
    }
  }
  // Se crean las conexiones entre nodos
  void nuevo_vertice(int n1, int n2, int v_i, int v_j) {
    // n1 es el nodo de origen y n2 el nodo de destino.

    Nodo *start = nodos[n1 - 1];
    // Se guarda la información de la conexiones del nodo de origen a otros
    // nodos en una lista.
    Nodo *end = new Nodo;
    // se agrega la infromación al final de la lista
    while (start->next_Node != NULL) {
      start = start->next_Node;
    }

    start->val = n2;
    start->vector_i = v_i;
    start->vector_j = v_j;
    // Se declara una futura posible nueva conexión
    start->next_Node = end;
  }
  // es el algoritmos breath depth search
  void camino_mas_corto(int end, int start) {
    int initial_node = start;
    int frontier[size];
    int explored_set[size];
    for (int i = 0; i < size; i++) {
      frontier[i] = 0;
      explored_set[i] = 0;
      path[i] = 0;
      instruc[i][0] = 0;
      instruc[i][1] = 0;
      for (int j = 0; j < size; j++) {
        paths[i][j] = 0;
      }
    }
    int v;
    bool condition = true;
    Nodo *n;
    frontier[0] = start;

    while (start != end) {
      if (condition == true) {
        if (start == end) {
          condition = false;
          path_true = true;
        }
        if (in_array(Ns[5], explored_set, size)) {
          condition = false;
        }
      }

      if (in_array(start, frontier, size) == true) {
        remove_from_array(start, frontier);
        /*for(int j=0;j<size;j++){
          std::cout << frontier[j]<<",";
        }
        std::cout <<"after remove\n\n";*/
      }
      if (in_array(start, explored_set, size) == false) {
        append_array(start, explored_set, size);
      }
      n = nodos[start - 1];
      // std::cout << start<<"start\n";
      while (n->next_Node != NULL) {
        v = n->val;
        // std::cout << v<<"\n";
        if (in_array(v, frontier, size) == false &&
            in_array(v, explored_set, size) == false) {
          append_array(v, frontier, size);
          // std::cout <<"pass"<<"\n";
          if (in_array(start, paths[v - 1], size) == false) {
            // Se guarda en paths[x-1] el nodo de origen del nodo "x"
            append_array(start, paths[v - 1], size);
            /*std::cout <<start<<",";
            std::cout <<v<<"\n";
            for(int j=0;j<size;j++){
              std::cout << paths[v-1][j]<<",";
            }
            std::cout <<"\n\n";*/
          }
        }
        n = n->next_Node;
      }
      start = frontier[0];
      /*for(int j=0;j<size;j++){
        std::cout << frontier[j]<<",";
      }
      std::cout <<"after while cycle\n\n";*/
    }
    // se hace un back tracking de los nodos que se tomaron para llegar al nodo
    // final al final se guarda los nodos de fin a inicio en path. Me dio hueva
    // hacer una funcion reversed como en python.
    // Hice que nodos que esten conectados se apunten entre si. Por eso, cuando
    // llamo a esta función, el nodo incial es el nodo de final, y viceversa.
    v = end;
    append_array(v, path, size);
    while (v != initial_node) {
      v = paths[v - 1][0];
      append_array(v, path, size);
    }
  }
  // se encuentra los vectores entre los nodos del array path.

  void instrucciones_camino_corto(void) {
    Nodo *h;
    int start = path[0];
    int next_node;
    int end;
    int i = 0;
    h = nodos[start - 1];

    for (int i = 0; i < size; i++) {
      if (path[i + 1] == 0) {
        end = path[i];
        // std::cout <<path[i]<<"\n";
        break;
      }
    }
    while (path[i] != end) {
      while (h->val != path[i + 1]) {
        h = h->next_Node;
      }
      instruc[i][0] = h->vector_i;
      instruc[i][1] = h->vector_j;
      i++;
      h = nodos[h->val - 1];
    }
  }
};

int main() {
  std::cout << "Hello World!\n";
  Graph grafo;

  // Los vectores le ayudarn al qbot a orientarse. El vector incial del qbot
  // sera [-1,0]
  int relaciones[10][4] = {{1, 5, 1, 0},     {1, 2, -1, 0}, {5, 6, 0, 1},
                           {5, 4, 1, 0},     {4, 6, -1, 0}, {6, 2, 0, -1},
                           {6, 3, 1 - 1, 0}, {3, 2, -1, 0}};

  grafo.init_grafo();
  for (int i = 0; i < 8; i++) {
    grafo.nuevo_vertice(relaciones[i][0], relaciones[i][1], relaciones[i][2],
                        relaciones[i][3]);
    grafo.nuevo_vertice(relaciones[i][1], relaciones[i][0],
                        -1 * relaciones[i][2], -1 * relaciones[i][3]);
  }

  //INGRESE CAMINO
  
  grafo.camino_mas_corto(6, 1);
  if (grafo.path_true == true) {
    grafo.instrucciones_camino_corto();
  }

  Nodo *n;
  for (int i = 0; i < size; i++) {
    n = grafo.nodos[i];
    std::cout << i + 1 << ": ";
    while (n->next_Node != NULL) {
      std::cout << n->val << ",";
      n = n->next_Node;
    }
    std::cout << "\n\n";
  }
  /*for(int i = 0; i<size;i++){
    for(int j=0;j<size;j++){
      std::cout << grafo.paths[i][j]<<",";
    }
    std::cout << "\n";

  }*/
  std::cout << "\n";

  for (int i = 0; i < size; i++) {
    std::cout << grafo.path[i] << ",";
  }
  std::cout << "\n\n";

}

/*grafo.init_grafo();
grafo.nuevo_vertice(1, 2, vector);
grafo.nuevo_vertice(1, 3, vector);
grafo.nuevo_vertice(1, 4, vector);
grafo.nuevo_vertice(2, 4, vector);
std::cout << grafo.nodos[0]->val;*/
