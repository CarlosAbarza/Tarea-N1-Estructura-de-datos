#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#include "arraylist.h"
#define MAX 31

typedef struct ArrayList {
    void **data;
    int capacity;
    int size;
} ArrayList;

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

typedef struct {
  char *nombre;
} Medico;

typedef struct {
  char *nombre;
  char *apellido;
  int edad;
  char *telefono;
  char *direccion;
  char *n_seg_soc;
  List *meds;
  bool tiene_med;
} Paciente;

/*1. Registrar paciente (char* nombre, char* apellido, int edad, char* teléfono, char* dirección, char* num_seguridad_social, char** medicos): El usuario ingresa los datos del paciente y la aplicación los almacena. Además, se le pueden asignar uno o varios médicos al paciente. Debe validarse que ningún campo de tipo char* tenga un largo mayor a 30 caracteres y que la edad sea mayor a 0.*/
void limp_pac(Paciente *limpiar) {
  free(limpiar->nombre);
  free(limpiar->apellido);
  free(limpiar->telefono);
  free(limpiar->direccion);
  free(limpiar->n_seg_soc);
  free(limpiar->meds);
}

Paciente* leer_validar(bool *quedan) {
  Paciente *local = (Paciente*) calloc(1, sizeof(Paciente));
  size_t max = 31;
  local->nombre = (char *) malloc(31* sizeof(char));
  local->apellido = (char *) malloc(31* sizeof(char));
  local->telefono = (char *) malloc(31* sizeof(char));
  local->direccion = (char *) malloc(31* sizeof(char));
  local->n_seg_soc = (char *) malloc(31* sizeof(char));
  printf("Hola, ingresa el nombre\n");
  size_t leidos = getline(&local->nombre, &max, stdin);
  if (leidos > 31) {
    limp_pac(local);
    printf("Excede el largo maximo\n");
    return NULL;
  }
  else if (leidos < 2){
    (*quedan) = false;
    printf("No quedan pacientes\n");
    limp_pac(local);
    return NULL;
  }
  printf("Ingresa el apellido\n");
  leidos = getline(&local->apellido, &max, stdin);
  if (leidos > 31) {
    limp_pac(local);
    printf("Excede el largo maximo\n");
    return NULL;
  }
  printf("Ingresa tu edad\n");
  scanf("%i", &local->edad);
  getchar();
  if (local->edad < 1) {
    limp_pac(local);
    printf("Edad invalida\n");
    return NULL;
  }
  printf("Ingresa tu telefono\n");
  leidos = getline(&local->telefono, &max, stdin);
  if (leidos > 31) {
    limp_pac(local);
    printf("Excede el largo maximo\n");
    return NULL;
  }
  printf("Ingresa tu direccion\n");
  leidos = getline(&local->direccion, &max, stdin);
  if (leidos > 31) {
    limp_pac(local);
    printf("Excede el largo maximo\n");
    return NULL;
  }
  printf("Ingresa tu numero de seguridad social\n");
  leidos = getline(&local->n_seg_soc, &max, stdin);
  if (leidos > 31) {
    limp_pac(local);
    printf("Excede el largo maximo\n");
    return NULL;
  }
  local->meds = createList();
  Medico* aux;
  while (true){
    aux = (Medico*) calloc(1, sizeof(Medico));
    if (aux == NULL) {
      printf("Error al reservar memoria\n");
      return NULL;
    }
    printf("Ingresa un medico asignado\n");
    leidos = getline(&aux->nombre, &max, stdin);
    if (leidos > 31) {
      printf("Excede el largo maximo\n");
      limp_pac(local);
      free(aux);
      free(local->meds);
      return NULL;
    }
    else if (leidos < 2){
      if (!firstList(local->meds)) 
        local->tiene_med = false;
      else
        local->tiene_med = true;
      /*for (int i = 0; i < local->meds->size; i++) {
        aux = get(local->meds, i);
        printf("%d.- %s\n",i + 1,  aux->nombre);
      }*/
      return local;
    }
    pushBack(local->meds, aux);
  }
  return local;
}

void ingresar_pacientes(List *pacientes) {
  Paciente *aux = NULL;
  bool quedan_datos = true;
  while (quedan_datos == true) {
    aux = leer_validar(&quedan_datos);
    if (aux) 
      pushBack(pacientes, aux);
  }
  return;
}

bool esta(Medico* nombre, List *medico) {
  Medico *aux = firstList(medico);
  while (aux) {
    if (strcmp(aux->nombre, nombre->nombre) == 0) {
      return true;
    }
    aux = nextList(medico);
  }
  return false;
}

void medicos_ingresados(List *medico, List *paciente) {
  Paciente *local = firstList(paciente);
  Medico *aux;
  while (local) {
    if (!local->tiene_med) {
      local = nextList(paciente);
      continue;
    }
    aux = firstList(local->meds);
    while (aux){
      if (!esta(aux, medico))
        pushBack(medico, aux);
      aux = nextList(local->meds);
    }
    local = nextList(paciente);
  }
  return;
}


/*2. Mostrar datos de paciente (char* nombre, char* apellido): El usuario ingresa el nombre y apellido de un paciente y la aplicación muestra sus datos y los médicos asignados. Si el paciente no existe, se debe mostrar un aviso.*/


void mostrar_dat_pac(Paciente* paciente) {
  printf("Nombre : %s", paciente->nombre);
  printf("Apellido : %s", paciente->apellido);
  printf("Edad : %d\n", paciente->edad);
  printf("Telefono : %s", paciente->telefono);
  printf("Direccion : %s", paciente->direccion);
  printf("Numero de seguridad social : %s", paciente->n_seg_soc);
  if (!paciente->tiene_med) {
    printf("No tiene medicos registrados\n");
  }
  else {
    Medico *aux = (Medico*) firstList(paciente->meds);
    printf("Sus medicos son :\n");
    while (aux) {
      printf("%s", aux->nombre);
      aux = nextList(paciente->meds);
    }
  }
  return;
}

void buscar_dat_pac(List *pacientes, char* nombre, char* apellido) {
  printf("Entra aqui\n");
  Paciente *local = firstList(pacientes);//pacientes->head->data;
  printf("Aqui no\n");
  while (local) {
    if (strcmp(local->nombre, nombre) == 0 && strcmp(local->apellido, apellido) == 0) {
      mostrar_dat_pac(local);
      return;
    }
    local = nextList(pacientes);
  }
  printf("El paciente buscado no esta registrado\n");
  return;
}

void buscar_pacientes(List *ingresos) {
  char *nombre = (char *) malloc(31* sizeof(char));
  char *apellido = (char *) malloc(31* sizeof(char));
  size_t max = 31;
  printf("Ingrese el nombre\n");
  size_t leidos = getline(&nombre, &max, stdin);
  if (leidos > max) {
    printf("Excede el largo maximo de caracteres\n");
    free(nombre);
    return;
  }
  printf("Ingrese el apellido\n");
  leidos = getline(&apellido, &max, stdin);
  if (leidos > max) {
    printf("Excede el largo maximo de caracteres\n");
    free(nombre);
    free(apellido);
    return;
  }
  buscar_dat_pac(ingresos, nombre, apellido);
}

/*3. Eliminar paciente (char* nombre, char* apellido): El usuario ingresa el nombre y apellido de un paciente y la aplicación lo elimina de la lista de pacientes. Si el paciente no existe, se debe mostrar un aviso.*/



/*4. Mostrar todos los pacientes (): La aplicación muestra por pantalla los nombres y apellidos de todos los pacientes registrados.*/



void mostrar_pacientes(List *pacientes) {
  Paciente *local = firstList(pacientes);
  while (local) {
    printf("Nombre : %s", local->nombre);
    printf("Apellido : %s", local->apellido);
    local = nextList(pacientes);
  }
  return;
}

/*5. Mostrar pacientes sin médico asignado (): La aplicación muestra por pantalla los nombres y apellidos de todos los pacientes que no tienen médicos asignados.*/



void mostrar_pac_sin_med(List *pacientes) {
  Paciente *local = firstList(pacientes);
  while (local != NULL){
    if (local->tiene_med == false) {
      printf("Nombre : %s", local->nombre);
      printf("Apellido : %s", local->apellido);
    }
    local = nextList(pacientes);
  }
}



/*6. Asignar médico a paciente (char* nombre_paciente, char* apellido_paciente, char* nombre_medico): El usuario ingresa el nombre y apellido del paciente y el nombre del médico que se le quiere asignar. La aplicación agrega al médico a la lista de médicos del paciente. Si el paciente o el médico no existen, se debe mostrar un aviso.*/





/*7. Desasignar médico de paciente (char* nombre_paciente, char* apellido_paciente, char* nombre_medico): El usuario ingresa el nombre y apellido del paciente y el nombre del médico que se le quiere desasignar. La aplicación elimina al médico de la lista de médicos del paciente. Si el paciente o el médico no existen, se debe mostrar un aviso.*/



/*8. Importar pacientes desde un archivo CSV (char* nombre_archivo): El usuario ingresa el nombre del archivo y la aplicación carga todos los pacientes y sus datos.*/



/*9. Exportar pacientes a un archivo CSV (char* nombre_archivo): La aplicación exporta todos los pacientes y sus datos a un archivo csv indicado por el usuario.*/





int main() {
  List *ingresos = createList();
  List *meds_asignados = createList();
  ingresar_pacientes(ingresos);
  /*
  Paciente *local = firstList(ingresos);
  Medico* aux;
  int cont;
  while (local) {
    printf("%s",local->nombre);
    printf("\n");
    aux = firstList(local->meds);
    cont = 0;
    while (aux) {
      cont++;
        printf("%d.- %s\n", cont,  aux->nombre);
        aux = nextList(local->meds);
      }
    local = nextList(ingresos);
  }
  */
  //mostrar_pacientes(ingresos); 
  
  //mostrar_pac_sin_med(ingresos); 

  
  medicos_ingresados(meds_asignados, ingresos);
  
  buscar_pacientes(ingresos);
  
  printf("Termino");

  return 0;
}
