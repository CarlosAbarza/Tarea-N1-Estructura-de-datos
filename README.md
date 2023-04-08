# Guía de compilación y ejecución del programa: Tarea 1  STALKER



## Pasos para compilar y ejecutar el programa

Para compilar y ejecutar el programa, sigue estos pasos:

1. Clona el repositorio desde GitHub ejecutando el siguiente comando en tu terminal:
    ```
    git clone https://github.com/ignacio-ave/Tarea-N1-Estructura-de-datos.git
    ```
2. Abre una terminal en el directorio en el que se encuentran los archivos `main.c`, `list.c` y `list.h`.

3. Escribe el comando `make -s` para compilar el programa:
    ```
    make -s
    ```
4. Escribe el comando `./main` para ejecutar el programa:
    ```
    ./main.c
    ```


## Opciones que funcionan:

1. Registrar Paciente:
    - Tiene las funciones "limpiar paciente" que libera el espacio guardado para el struct "paciente" y para todas sus variables.
    - "Leer validar" Guarda memoria para cada variable, por cada variable pide ingresar datos manualmente y comprueba que no traspasen el largo máximo de caracteres.
    - "Ingresar pacientes" crea una variable auxiliar en la que guarda los datos llamando a leer "leer validar"; si se ingresan datos los devuelve y los guarda en una lista Pacientes.
    - "Esta" comprueba si el médico ingresado se encuentra en la lista de médicos.
    - "Médicos ingresados" revisa si el paciente tiene un médico asignado, si no tiene sigue con el siguiente paciente en la lista, si tiene revisa si está en la lista de médicos. Se accede apretando 1 en el menú, se ingresan los datos manualmente y se asignan médicos hasta hacer un doble salto de línea. 

2. Mostrar datos de pacientes:
    - Tiene las funciones "mostrar dat pac" que va imprimiendo las variables del struct paciente, y si tiene o no médicos asignados.
    - "Buscar dat paciente" que ingresando el nombre y apellido del paciente, lo busca en los pacientes ya guardados; si no está registrado imprime un mensaje declarándolo.
    - "Nombre buscar paciente" funciona tanto para buscar un paciente e imprimir sus datos con mostrar dat pac, como para buscar un paciente y eliminarlo de la base de datos; Borra o busca según la opción elegida en el índice. Se accede apretando 2 en el índice. 

3. Eliminar paciente (Integrado en nombre buscar paciente). Se accede apretando 3 en el índice.

4. Mostrar pacientes: con la función del mismo nombre, recorre la lista y va imprimiendo los nombres y apellidos por orden. Si no hay pacientes imprime un mensaje expresándolo. Se accede apretando el número 4 en el índice.

5. Mostrar pacientes sin médico asignado: 
    - Con la función mostrar_pac_sin_med, y siempre que hayan pacientes ingresados, va imprimiendo los nombres y apellidos de los pacientes en que la variable tiene_med sea igual a false. 
    - Si todos los tienen al menos un médico asignado, expresa esto. Se accede a esta función escribiendo 5 en el índice. 

6. Asignar médico a paciente: 
    - Utilizando la función asignar médico, que sirve tanto para asignar un médico a un paciente como para eliminar un médico asignado. 
    - Crea variables locales para el nombre y apellido de paciente y un tipo medico "med" y les guarda memoria. 
    - Luego,se pide ingresar el nombre del medico, y si está en la lista de medicos, se agrega a la lista de medicos asignados del paciente llamando a la funcion buscar_dat_pac.
    - Para asignarlo se presiona 6 en el menu, y para eliminarlo se presiona 7.

7. Desasignar médico:
    - (Integrada en la funcion asignar medico)
8. Importar pacientes desde CSV:
    - Con la funcion "transformar_csv", guarda memoria para un struct tipo paciente local, y para cada una de sus variables.
    - Recibe la linea completa del archivo, distingue la separacion por comas y va guardando Nombre, Apellido, Edad, Teléfono, Dirección, Num Seguridad Social, Médicos
    -  Cuando hay mas de un medico distingue la separación con un punto y coma.
    -  Si no hay medicos guardados en la variable meds del struct paciente, se guarda false en la variable tiene_med, y true en el caso contrario
    -  Con la funcion "importar_pac" crea una variable local en la que se guardará el nombre del archivo que se desea abrir, ingresado por el usuario.
    -  Para importar los pacientes se presiona 8 en el indice.

### Herramientas usadas para el desarrollo:
  - replit (Para desarrollar el programa en conjunto)
  - Visual Studio Code (Para desarrollar el programa individualmente)
  - Github (Para guardar un backup del programa en caso de falla en replit)
  - GPT (Para redactar parcialmente el archivo readme)

## Coevaluación equipo
- Participación activa y equitativa: 20 
- Resolución de conflictos: 20
- Colaboración: 20 
- Responsabilidad: 20 
- Comunicación: 15
- Puntaje total: 95

## Coevaluación del aporte individual
| Integrante | Participación | Responsabilidad | Comunicación | Calidad del trabajo | Trabajo en equipo | Pje Total |
|------------|--------------|----------------|--------------|------------------|------------------|------------------|
| Ignacio    | 20           | 15             |  20          | 20               | 20               | 95               |
| Vicente    | 20           | 20             |  15          | 20               | 20               | 95               |
| Antonia    | 20           | 20             |  15          | 20               | 20               | 95               |
| Carlos     | 20           | 20             |  15          | 20               | 20               | 95               |

