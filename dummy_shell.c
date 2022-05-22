#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include "leercadena.h"
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

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
  pid_t pids[10];
  int pidsIndex = 0;

  while (1)
  {
    pid_t pid;
    bool bg = false;
    printf("> ");
    leer_de_teclado(MAX, cadena);
    vector_cadenas = de_cadena_a_vector(cadena);
    if (strcmp("salir", vector_cadenas[0]) == 0)
    {
      int i = 0;
      while (i < pidsIndex)
      {
        kill(pids[i], SIGSEGV);
        i++;
      }
      break;
    }
    len = length(vector_cadenas);
    if (strcmp("&", vector_cadenas[len - 2]) == 0)
    {
      vector_cadenas[len - 2] = NULL;
      bg = true;
    }
    pid = fork();
    assert(pid >= 0);
    if (pid == 0)
    {
      if (strcmp("tareas", vector_cadenas[0]) == 0)
      {
        printf("procesos en background:\n");
        int i = 0;
        while (i < pidsIndex)
        {
          printf("%d\n", (int)pids[i]);
          i++;
        }
        kill(getpid(), SIGSEGV);
      }
      else
      {
        if (strcmp("detener", vector_cadenas[0]) == 0)
        {
          printf("%s se detuvo\n", vector_cadenas[1]);
          vector_cadenas[0] = "kill";
        }
        execvp(vector_cadenas[0], vector_cadenas);
      }
    }
    else
    {
      if (bg)
      {
        pids[pidsIndex] = pid;
        printf("%d\n", (int)pids[pidsIndex]);
        pidsIndex++;
        printf("ando en back ;-)\n");
      }
      else
      {
        wait(NULL);
      }
    }
  }
  printf("Gracias por usar mi dummy shell ;-)\n");
  return 0;
}
