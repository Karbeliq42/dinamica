#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STRING_T 60

typedef struct {
  int id;
  char nome[STRING_T];
  char email[STRING_T];
  double Altura;
  char End[STRING_T];
} Registro;

typedef struct {
  Registro *registros;
  int tamanho;
} ListaRegistros;

int proximoID = 1;

ListaRegistros *inicializarLista() {
  ListaRegistros *lista = (ListaRegistros *)malloc(sizeof(ListaRegistros));
  lista->registros = NULL;
  lista->tamanho = 0;
  return lista;
}
int gerarID() {
  return proximoID++;
}

void adicionarRegistro(ListaRegistros *lista) {
  Registro registro;

  registro.id = gerarID();
  printf("ID: %d \n", registro.id);

  printf("Digite o nome: ");
  fgets(registro.nome, STRING_T, stdin);
  registro.nome[strcspn(registro.nome, "\n")] = '\0';

  int verificar = 0;
  do {
    printf("Digite seu email: ");
    fgets(registro.email, STRING_T, stdin);
    fflush(stdin);

    if (strstr(registro.email, "@") == NULL) {
      printf("E-mail invalido.\n");

    } else {
      verificar = 1;
    }

  } while (!verificar);

  printf("Digite o endereco: ");
  fgets(registro.End, STRING_T, stdin);
  registro.End[strcspn(registro.End, "\n")] = '\0';

  do {
    printf("Digite a altura: ");
    scanf("%lf", &registro.Altura);
    getchar();

    if (registro.Altura < 1 || registro.Altura > 2)
      printf("Altura invalida \n");

  } while (registro.Altura < 1 || registro.Altura > 2);

  lista->registros = (Registro *)realloc(
      lista->registros, (lista->tamanho + 1) * sizeof(Registro));
  lista->registros[lista->tamanho] = registro;
  lista->tamanho++;
}


void exibirRegistros(ListaRegistros *lista) {
  printf("Registros:\n");

  for (int i = 0; i < lista->tamanho; i++) {
    Registro registro = lista->registros[i];
    printf("ID: %d\n", registro.id);
    printf("Nome: %s\n", registro.nome);
    printf("Email: %s\n", registro.email);
    printf("Altura: %lf\n", registro.Altura);
    printf("Endereco: %s\n", registro.End);
    printf("\n");
  }
}

void liberarLista(ListaRegistros *lista) {
  free(lista->registros);
  free(lista);
}

int main() {
  ListaRegistros *lista = inicializarLista();
  char opcao;

  do {
    printf("=== Agora Vai ===\n");
    printf("1. Incluir registro\n");
    printf("2. Listar registros\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
    scanf(" %c", &opcao);
    getchar();

    switch (opcao) {
    case '1':
      adicionarRegistro(lista);
      break;
    case '2':
      exibirRegistros(lista);
      break;
    case '3':
      printf("Saindo...\n");
      break;
    default:
      printf("Opcao invalida!\n");
      break;
    }

    printf("\n");
  } while (opcao != '3');

  liberarLista(lista);

  return 0;
}
