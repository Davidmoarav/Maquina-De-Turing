#include <stdio.h>
#include <stdlib.h>

#define MAX_ESTADOS 10
#define MAX_SIMBOLOS 10

struct maquina_turing {
  int estados[MAX_ESTADOS];
  char simbolos[MAX_SIMBOLOS];
  char cinta[1000];
  int estado_inicial;
  struct transicion {
    int estado_siguiente;
    char simbolo_siguiente;
    int movimiento;
  } delta[MAX_ESTADOS][MAX_SIMBOLOS];
};

struct transicion get_transicion(struct maquina_turing *m, int estado, char simbolo) {
  return m->delta[estado][simbolo];
}

void ejecutar_maquina(struct maquina_turing *m) {
  int estado = m->estado_inicial;
  int cabeza = 0;

  while (1) {
    char simbolo = m->cinta[cabeza];
    struct transicion transicion = get_transicion(m, estado, simbolo);

    m->cinta[cabeza] = transicion.simbolo_siguiente;
    cabeza += transicion.movimiento;
    estado = transicion.estado_siguiente;

    if (estado == -1) {
      break;
    }
  }
}

int main() {
  FILE *archivo = fopen("entrada.txt", "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return 1;
  }

  struct maquina_turing maquina;
  fscanf(archivo, "%d", &maquina.estado_inicial);

  fscanf(archivo, "%s", maquina.simbolos);

  int numero_casos;
  fscanf(archivo, "%d", &numero_casos);

  fscanf(archivo, "%s", maquina.cinta);

  // Simular el procesamiento de los datos y ejecutar la máquina de Turing
  ejecutar_maquina(&maquina);

  // Imprimir resultados por consola
  printf("Cinta después de la ejecución: %s\n", maquina.cinta);

  fclose(archivo);
  return 0;
}
