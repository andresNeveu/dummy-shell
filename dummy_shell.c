#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include "leercadena.h"
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100
/**
 * @brief encuentra el tamaño de vector de listas de caracteres que tienen como último elemento un null
 * 
 * @param vector vector de listas de caracteres
 * @return int representa el tamaño de la lista
 */
int length(char **vector)
{
  bool cond = true;
  int len = 1;
  while (cond)
  {
    if (vector[len] == NULL)
    {
      cond = false;
    }
    len++;
  }
  return len;
}

int main(int argc, char *argv[])
{
  int len = 0;
  char **vector_cadenas;
  char cadena[MAX];
  pid_t pids[10]; // lista de procesos en backgrpund
  int pidsIndex = 0;

  while (1)
  {
    pid_t pid;
    bool bg = false; //señal para los procesos en background
    printf("> ");
    leer_de_teclado(MAX, cadena);
    vector_cadenas = de_cadena_a_vector(cadena);
    if (strcmp("salir", vector_cadenas[0]) == 0)
    {
      for (int i = 0; i < pidsIndex; i++)
      {
        kill(pids[i], SIGSEGV); //mata los procesos que hayan quedado en background
      };
      break;
    }
    len = length(vector_cadenas);
    if (strcmp("&", vector_cadenas[len - 2]) == 0) // reconocer un proceso de background
    {
      vector_cadenas[len - 2] = NULL; //elimina el elemento & 
      bg = true;
    }
    pid = fork();
    assert(pid >= 0);
    if (pid == 0)
    {
      if (strcmp("tareas", vector_cadenas[0]) == 0)
      {
        printf("procesos en background:\n");
        for (int i = 0; i < pidsIndex; i++)
        {
          printf("%d\n", (int)pids[i]);
        };
        kill(getpid(), SIGSEGV); //mata el proceso para evitar doble while
      }
      else
      {
        if (strcmp("detener", vector_cadenas[0]) == 0)
        {
          vector_cadenas[0] = "kill"; // matar el proceso al cambiar detener por kill
        }
        execvp(vector_cadenas[0], vector_cadenas);
      }
    }
    else
    {
      if (bg)
      {
        pids[pidsIndex] = pid; //agrega el pid a la lista de procesos en background
        printf("%d\n", (int)pids[pidsIndex]);
        pidsIndex++;
      }
      else
      {
        if (strcmp("detener", vector_cadenas[0]) == 0)
        {
          for (int i = 0; i < pidsIndex; i++)
          {
            if (pids[i] == atoi(vector_cadenas[1]))
            {
              for (int j = i; j < pidsIndex; j++) //eliminar de la lista el proceso detenido
              {
                pids[j] = pids[j + 1]; 
              }
              pidsIndex--;
              printf("%s se detuvo\n", vector_cadenas[1]);
              break;
            }
          }
        }
        wait(NULL);
      }
    }
  }
  printf("Gracias por usar mi dummy shell ;-)\n");
  return 0;
}
