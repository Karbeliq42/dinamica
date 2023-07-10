#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_T 50

typedef struct {
  int id;
  char *nome;
  char *email;
  double altura;
  char *endereco;
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

int gerarID() { return proximoID++; }

void adicionarRegistro(ListaRegistros *lista) {
  Registro registro;

  registro.id = gerarID();
  printf("ID: %d \n", registro.id);

  registro.nome = (char *)malloc(STRING_T * sizeof(char));
  printf("Digite o nome: ");
  fgets(registro.nome, STRING_T, stdin);
  registro.nome[strcspn(registro.nome, "\n")] = '\0';

  int verificar = 0;
  do {
    registro.email = (char *)malloc(STRING_T * sizeof(char));
    printf("Digite seu email: ");
    fgets(registro.email, STRING_T, stdin);

    if (strstr(registro.email, "@") == NULL) {
      printf("E-mail inválido.\n");
      free(registro.email);
    } else {
      verificar = 1;
    }
  } while (!verificar);

  registro.endereco = (char *)malloc(STRING_T * sizeof(char));
  printf("Digite o endereco: ");
  fgets(registro.endereco, STRING_T, stdin);
  registro.endereco[strcspn(registro.endereco, "\n")] = '\0';

  do {
    printf("Digite a altura: ");
    scanf("%lf", &registro.altura);
    getchar();

    if (registro.altura < 1 || registro.altura > 2)
      printf("Altura inválida \n");

  } while (registro.altura < 1 || registro.altura > 2);

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
    printf("Altura: %lf\n", registro.altura);
    printf("Endereco: %s\n", registro.endereco);
    printf("\n");
  }
}

void editarRegistros(ListaRegistros *lista) {
  int id;
  printf("Digite o ID que quer alterar:");
  scanf("%d", &id);
  getchar();

  int encontrado = 0;
  for (int i = 0; i < lista->tamanho; i++) {
    if (lista->registros[i].id == id) {
      Registro *registro = &(lista->registros[i]);

      printf("Registro encontrado:\n");
      printf("ID: %d\n", registro->id);
      printf("Nome: %s\n", registro->nome);
      printf("Email: %s\n", registro->email);
      printf("Altura: %lf\n", registro->altura);
      printf("Endereco: %s\n", registro->endereco);

      printf("Digite o novo nome: ");
      fgets(registro->nome, STRING_T, stdin);
      registro->nome[strcspn(registro->nome, "\n")] = '\0';

      int verificar = 0;
      do {
        printf("Digite o novo email: ");
        fgets(registro->email, STRING_T, stdin);

        if (strstr(registro->email, "@") == NULL) {
          printf("E-mail inválido.\n");
        } else {
          verificar = 1;
        }
      } while (!verificar);

      printf("Digite o novo endereco: ");
      fgets(registro->endereco, STRING_T, stdin);
      registro->endereco[strcspn(registro->endereco, "\n")] = '\0';

      do {
        printf("Digite a nova altura: ");
        scanf("%lf", &registro->altura);
        getchar();

        if (registro->altura < 1 || registro->altura > 2)
          printf("Altura inválida \n");

      } while (registro->altura < 1 || registro->altura > 2);

      printf("Registro alterado com sucesso!\n");

      encontrado = 1;
      break;
    }
  }

  if (!encontrado) {
    printf("Registro com o ID %d não encontrado.\n", id);
  }
}

void excluirRegistro(ListaRegistros *lista) {
  int id;
  printf("Digite o ID que quer excluir:");
  scanf("%d", &id);
  getchar();

  int encontrado = 0;
  int indice_encontrado = 0;
  for (int i = 0; i < lista->tamanho; i++) {
    if (lista->registros[i].id == id) {
      encontrado = 1;
      indice_encontrado = i;
      break;
    }
  }
  if (encontrado) {
    Registro registro_excluido = lista->registros[indice_encontrado];

    free(registro_excluido.nome);
    free(registro_excluido.email);
    free(registro_excluido.endereco);

    for (int i = indice_encontrado; i < lista->tamanho - 1; i++) {
      lista->registros[i] = lista->registros[i + 1];
    }

    lista->tamanho--;
    lista->registros = (Registro *)realloc(lista->registros, lista->tamanho * sizeof(Registro));

    printf("Registro com ID %d excluido com sucesso.\n", id);
  } else {
    printf("Registro com ID %d não encontrado.\n", id);
  }
}

void liberarLista(ListaRegistros *lista) {
  for (int i = 0; i < lista->tamanho; i++) {
    free(lista->registros[i].nome);
    free(lista->registros[i].email);
    free(lista->registros[i].endereco);
  }
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
    printf("3. Editar registros\n");
    printf("4. Excluir registro\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
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
        editarRegistros(lista);
        break;
      case '4':
        excluirRegistro(lista);
        break;
      case '5':
        printf("Saindo...\n");
        break;
      default:
        printf("Opção inválida!\n");
        break;
    }

    printf("\n");
  } while (opcao != '5');

  liberarLista(lista);

  return 0;
}
