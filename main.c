#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

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

Paciente* leer_validar() {
  Paciente *local = (Paciente*) calloc(1, sizeof(Paciente));
  size_t max = 31;
  local->nombre = (char *) malloc(31* sizeof(char));
  local->apellido = (char *) malloc(31* sizeof(char));
  local->edad = 0;
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
    printf("No quedan pacientes\n\n\n");
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
    getline(&local->nombre, &max, stdin);
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
      
      return local;
    }
    pushBack(local->meds, aux);
  }
  return local;
}

void ingresar_pacientes(List *pacientes) {
  Paciente *aux = NULL;
  aux = leer_validar();
  if (aux)
    pushBack(pacientes, aux);
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
  free(aux);
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
  free(aux);
  free(local);
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
    printf("No tiene medicos registrados");
  }
  else {
    Medico *aux = (Medico*) firstList(paciente->meds);
    printf("Sus medicos son :\n");
    while (aux) {
      printf("- %s", aux->nombre);
      aux = nextList(paciente->meds);
    }
    free(aux);
  }
  printf("\n\n");
  return;
}

Paciente* buscar_dat_pac(List *pacientes, char* nombre, char* apellido) {
  Paciente *local = firstList(pacientes);
  while (local) {
    if (strcmp(local->nombre, nombre) == 0 && strcmp(local->apellido, apellido) == 0) {
      return local;
    }
    local = nextList(pacientes);
  }
  printf("El paciente buscado no esta registrado\n\n\n");
  free(local);
  return NULL; 
}

void nombre_buscar_pacientes(List *ingresos, int tipo) {
  char *nombre = (char *) malloc(31* sizeof(char));
  char *apellido = (char *) malloc(31* sizeof(char));
  size_t max = 31;
  if (tipo == 1)
    printf("Buscar Paciente\n");
  else 
    printf("Paciente a eliminar\n");
  printf("Nombre : ");
  size_t leidos = getline(&nombre, &max, stdin);
  if (leidos > max) {
    printf("Excede el largo maximo de caracteres\n");
    free(nombre);
    free(apellido);
    return;
  }
  printf("Apellido : ");
  leidos = getline(&apellido, &max, stdin);
  if (leidos > max) {
    printf("Excede el largo maximo de caracteres\n");
    free(nombre);
    free(apellido);
    return;
  }
  printf("\n");
  Paciente *local = buscar_dat_pac(ingresos, nombre, apellido);
  if (local) {
    if (tipo == 1)
      mostrar_dat_pac(local);
    else {
      popCurrent(ingresos);
      printf("Paciente eliminado con exito\n\n");
    }
  }
  free(nombre);
  free(apellido);
}

/*3. Eliminar paciente (char* nombre, char* apellido): El usuario ingresa el nombre y apellido de un paciente y la aplicación lo elimina de la lista de pacientes. Si el paciente no existe, se debe mostrar un aviso.*/

//Integrado junto con la funcion de nombre_buscar_pacientes


/*4. Mostrar todos los pacientes (): La aplicación muestra por pantalla los nombres y apellidos de todos los pacientes registrados.*/



void mostrar_pacientes(List *pacientes) {
  Paciente *local = firstList(pacientes);
  if (local) 
    printf("Lista de Pacientes ingresados :\n\n");
  else 
    printf("No hay pacientes ingresados\n\n");
  while (local) {
    printf("Nombre : %s", local->nombre);
    printf("Apellido : %s\n\n", local->apellido);
    local = nextList(pacientes);
  }
  free(local);
  return;
}

/*5. Mostrar pacientes sin médico asignado (): La aplicación muestra por pantalla los nombres y apellidos de todos los pacientes que no tienen médicos asignados.*/



void mostrar_pac_sin_med(List *pacientes) {
  Paciente *local = firstList(pacientes);
  if (!local) {
    printf("No hay pacientes ingresados\n\n\n");
    return;
  }
  int cont = 0;
  while (local != NULL){
    if (local->tiene_med == false) {
      if (cont == 0)
        printf("Pacientes sin medico asignado :\n");
      printf("Nombre : %s", local->nombre);
      printf("Apellido : %s\n", local->apellido);
      cont += 1;
    }
    local = nextList(pacientes);
  }
  if (cont == 0)
    printf("Todos los pacientes tienen al menos un medico asignado\n");
  printf("\n\n");
  free(local);
}



/*6. Asignar médico a paciente (char* nombre_paciente, char* apellido_paciente, char* nombre_medico): El usuario ingresa el nombre y apellido del paciente y el nombre del médico que se le quiere asignar. La aplicación agrega al médico a la lista de médicos del paciente. Si el paciente o el médico no existen, se debe mostrar un aviso.*/

void asignar_med(List *ingresos, List *medicos, int tipo) {
  char *nombre_pac = (char*) malloc(31*sizeof(char));
  char *apellido_pac = (char*) malloc(31*sizeof(char));
  Medico *med = (Medico*) malloc(sizeof(Medico));
  med->nombre = (char*) malloc(31*sizeof(char));
  size_t max = 31;
  if (tipo == 1) 
    printf("Asignar un medico a un paciente\n");
  else
    printf("Eliminar un medico de un paciente\n");
  printf("Ingrese el nombre del paciente : ");
  size_t leido = getline(&nombre_pac, &max, stdin);
  if (leido > max) {
    printf("Excede el largo maximo de caracteres\n");
    free(nombre_pac);
    free(apellido_pac);
    free(med->nombre);
    return;
  }
  printf("Apellido : ");
  leido = getline(&apellido_pac, &max, stdin);
  if (leido > max) {
    printf("Excede el largo maximo de caracteres\n\n");
    free(nombre_pac);
    free(apellido_pac);
    free(med->nombre);
    return;
  }
  printf("Nombre del medico : ");
  leido = getline(&med->nombre, &max, stdin);
  if (leido > max) {
    printf("Excede el largo maximo de caracteres\n\n");
    free(nombre_pac);
    free(apellido_pac);
    free(med->nombre);
    return;
  }
  if (esta(med, medicos)){
    Paciente *local = buscar_dat_pac(ingresos, nombre_pac, apellido_pac);
    if (local) {
      if (tipo == 1) {
        pushBack(local->meds, med);
        printf("Medico resgistrado con exito\n\n");
        if (!local->tiene_med)
          local->tiene_med = true;
      }
      else {
        Medico *aux = firstList(local->meds);
        while (aux) {
          if (strcmp(aux->nombre, med->nombre) == 0) {
            popCurrent(local->meds);
            printf("Medico eliminado con exito\n\n");
            if (!firstList(local->meds))
              local->tiene_med = false;
            return;
          }
          aux = nextList(local->meds);
        }
        printf("El paciente no tenia registrado el medico\n\n");
      }
    }
  }
  else {
    printf("El medico ingresado no esta registrado\n\n");
  }
  free(nombre_pac);
  free(apellido_pac);
}



/*7. Desasignar médico de paciente (char* nombre_paciente, char* apellido_paciente, char* nombre_medico): El usuario ingresa el nombre y apellido del paciente y el nombre del médico que se le quiere desasignar. La aplicación elimina al médico de la lista de médicos del paciente. Si el paciente o el médico no existen, se debe mostrar un aviso.*/

// Incluido dentro de la funcion asignar medico


/*8. Importar pacientes desde un archivo CSV (char* nombre_archivo): El usuario ingresa el nombre del archivo y la aplicación carga todos los pacientes y sus datos.*/

Paciente* transformar_csv(char *linea){
  Paciente *local = malloc(sizeof(Paciente));
  local->nombre = (char *) malloc(31* sizeof(char));
  local->apellido = (char *) malloc(31* sizeof(char));
  local->telefono = (char *) malloc(31* sizeof(char));
  local->direccion = (char *) malloc(31* sizeof(char));
  local->n_seg_soc = (char *) malloc(31* sizeof(char));
  
  char *aux = (char*) malloc(31*sizeof(char));
  char delim[] = ",";
  
  aux = strtok(linea, delim);
  strcpy(local->nombre, aux);
  local->nombre = strcat(local->nombre, "\n");
  
  aux = strtok(NULL, delim);
  strcpy(local->apellido, aux);
  local->apellido = strcat(local->apellido, "\n");
  
  local->edad = atoi(strtok(NULL, delim));
  
  aux = strtok(NULL, delim);
  strcpy(local->telefono, aux);
  local->telefono = strcat(local->telefono, "\n");
  
  aux = strtok(NULL, delim);
  strcpy(local->direccion, aux);
  local->direccion = strcat(local->direccion, "\n");
  
  aux = strtok(NULL, delim);
  strcpy(local->n_seg_soc, aux);
  local->n_seg_soc = strcat(local->n_seg_soc, "\n");  
  
  Medico *med_local;
  local->meds = createList();
  aux = strtok(NULL, ";");
  while (aux) {
    med_local = (Medico*) malloc(sizeof(Medico));
    med_local->nombre = (char*) malloc(31*sizeof(char));
    strcpy(med_local->nombre, aux);
    if (med_local->nombre[strlen(med_local->nombre)-1] != '\n')
      med_local->nombre = strcat(med_local->nombre, "\n");
    pushBack(local->meds, med_local);
    aux = strtok(NULL, ";");
  }
  if (!firstList(local->meds)) 
    local->tiene_med = false;
  else
    local->tiene_med = true;
  return local;  
}

void importar_pac(List *ingresos) {
  char *nombre_archivo = (char*) malloc(20*sizeof(char));
  size_t max = 31;
  printf("Introducir nombre del archivo que desea abrir : \n");
  getline(&nombre_archivo, &max, stdin);
  nombre_archivo[strlen(nombre_archivo) - 1] = '\0';
  FILE *archivo = fopen(nombre_archivo, "r");
  if (!archivo) {
    printf("No se pudo abrir el archivo de pacientes\n");
    free(nombre_archivo);
    return;
  }

  printf("Pacientes importados con exito!");
  
  char *aux;
  max = 310;
  size_t leido;
  int saltar_primero = 0;
  while (true) {
    aux = (char*) malloc(310*sizeof(char));
    leido = getline(&aux, &max, archivo);
    if (saltar_primero == 0) {
      saltar_primero++;
      continue;
    }
    if (aux[0] == '\0') {
      fclose(archivo);
      free(aux);
      return;
    }
    Paciente *local = transformar_csv(aux);
    pushBack(ingresos, local);
    saltar_primero++;
  }
}


/*9. Exportar pacientes a un archivo CSV (char* nombre_archivo): La aplicación exporta todos los pacientes y sus datos a un archivo csv indicado por el usuario.*/


void desnficador(Paciente *local){

  
  char *delim = "\n";
    strtok(local->nombre, delim);
    strtok(local->apellido, delim);
    strtok(local->telefono, delim);
    strtok(local->direccion, delim);
    strtok(local->n_seg_soc, delim);

    List *medicos = local->meds;
    Medico *aux = firstList(medicos);
    while (aux != NULL) {
        strtok(aux->nombre, delim);
        aux = nextList(medicos);
    }
}




void imprimir_paciente(FILE *archivo, Paciente *local){
  fprintf(archivo, "%s,%s,%d,%s,%s,%s",local->nombre, local->apellido, local->edad, local->telefono, local->direccion, local->n_seg_soc);
  
  List *localMeds=local->meds;
  Medico *aux=firstList(localMeds);
  int cont = 0;
  while(aux !=NULL)
  {
    if (cont == 0) 
      fprintf(archivo,",%s",aux->nombre);
    else
      fprintf(archivo,";%s",aux->nombre);
    cont++;
    aux = nextList(localMeds);
  }
  fprintf(archivo, "\n");
  free(aux);
  free(localMeds);
}

void exportar_pacientes(List* ingresos) {
  char *nombre_archivo = (char*) malloc(20*sizeof(char));
  size_t max = 20;
  printf("Ingrese el nombre del archivo donde desea exportar los datos : ");
  getline(&nombre_archivo, &max, stdin);
  nombre_archivo[strlen(nombre_archivo) - 1] = '\0';
  FILE *archivo = fopen(nombre_archivo, "w");
  if (!archivo){
    printf("No se pudo abrir el archivo\n");
    free(nombre_archivo);
    return;
  }
  Paciente *local = firstList(ingresos);
  fputs("Nombre,Apellido,Edad,Teléfono,Dirección,Num Seguridad Social,Médicos\n", archivo);
  while (local) {
    desnficador(local);
    imprimir_paciente(archivo, local);
    local=nextList(ingresos);
  }
  fclose(archivo);
  free(nombre_archivo);
  free(local);
}



int main() {
  List *ingresos = createList();
  List *meds_asignados = createList();
  int accion;

  while (true) {
    printf("\n\n");
    printf("╭──────────────────────────────────────────────────────────╮\n");
    printf("│                     MENU PRINCIPAL                       │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ 1. Ingresar pacientes                                    │\n");
    printf("│ 2. Buscar un paciente                                    │\n");
    printf("│ 3. Eliminar un paciente                                  │\n");
    printf("│ 4. Mostrar todos los pacientes                           │\n");
    printf("│ 5. Mostrar pacientes sin médico asignado                 │\n");
    printf("│ 6. Asignar médico a un paciente                          │\n");
    printf("│ 7. Eliminar médico asignado a un paciente                │\n");
    printf("│ 8. Importar pacientes                                    │\n");
    printf("│ 9. Exportar pacientes                                    │\n");
    printf("│ 0. Terminar                                              │\n");
    printf("╰──────────────────────────────────────────────────────────╯\n");
    printf("Seleccione una opción: ");
    scanf("%d", &accion);
    getchar();
    
    printf("\n\n");
    
    switch (accion) {
      case 1 : 
        ingresar_pacientes(ingresos);
        medicos_ingresados(meds_asignados , ingresos);
        break;
      case 2 :
        nombre_buscar_pacientes(ingresos, 1);
        break;
      case 3 :
        nombre_buscar_pacientes(ingresos, 0);
        break;
      case 4:
        mostrar_pacientes(ingresos);
        break;
      case 5 :
        mostrar_pac_sin_med(ingresos);
        break;
      case 6 :
        asignar_med(ingresos, meds_asignados, 1 );
        break;
      case 7:
        asignar_med(ingresos, meds_asignados, 0);
        break;
      case 8:
        importar_pac(ingresos);
        medicos_ingresados(meds_asignados, ingresos);
        break;
      case 9:
        exportar_pacientes(ingresos);
        break;
      case 0 :
        printf("¡Hasta luego!\n");
        break;
      default:
        printf("Opción inválida. Por favor, seleccione una opción válida.\n");
        break;
    }
    if(accion == 0) {
      break;
    }
    accion = 10;
  }
}