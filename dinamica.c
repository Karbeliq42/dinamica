#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

#define MaxUsers 3

typedef struct {
  int id;
  char nome[20];
  double altura;
  int vacinado;
  char email[50];
  char sexo[15];
  char endereco[100];
} Usuario;

void cadastrarUsuario(Usuario **usuarios, int *numUsuarios, int *contadorIDs) {
  if (*numUsuarios >= MaxUsers) {
    printf("Número máximo de usuários atingido.\n");
    return;
  }

  Usuario novoUsuario;

  novoUsuario.id = (*contadorIDs)++;
  printf("ID gerado: %d\n", novoUsuario.id);

  printf("Digite o nome: ");
  scanf("%s", novoUsuario.nome);

  do {
    printf("Digite o sexo (feminino, masculino ou indiferente): ");
    scanf("%s", novoUsuario.sexo);

    if (strcmp(novoUsuario.sexo, "feminino") == 0 || strcmp(novoUsuario.sexo, "masculino") == 0 || strcmp(novoUsuario.sexo, "indiferente") == 0) {
      printf("Sexo válido.\n");
    } else {
      printf("Sexo inválido. Digite novamente.\n");
    }
  } while (!(strcmp(novoUsuario.sexo, "feminino") == 0 || strcmp(novoUsuario.sexo, "masculino") == 0 || strcmp(novoUsuario.sexo, "indiferente") == 0));

  do {
    printf("Digite o email: ");
    scanf("%s", novoUsuario.email);

    // Verificar se o caractere '@' está presente no email
    if (strstr(novoUsuario.email, "@") == NULL) {
      printf("Email inválido. Digite novamente.\n");
    } else {
      printf("Email válido.\n");
      break; // Sai do loop quando o email for válido
    }
  } while (1);

  printf("Digite a altura: ");
  scanf("%lf", &novoUsuario.altura);

  printf("Digite o endereço: ");
  scanf("%s", novoUsuario.endereco);

  (*numUsuarios)++;
  *usuarios = realloc(*usuarios, (*numUsuarios) * sizeof(Usuario));
  (*usuarios)[(*numUsuarios) - 1] = novoUsuario;

  printf("Usuário cadastrado com sucesso!\n");
}

void editarUsuario(Usuario *usuarios, int numUsuarios) {
  int idEditar;
  printf("Digite o ID do usuário que deseja editar: ");
  scanf("%d", &idEditar);

  int encontrado = 0;
  for (int i = 0; i < numUsuarios; i++) {
    if (idEditar == usuarios[i].id) {
      encontrado = 1;

      printf("Digite o novo nome: ");
      scanf("%s", usuarios[i].nome);

      do {
        printf("Digite o novo sexo (feminino, masculino ou indiferente): ");
        scanf("%s", usuarios[i].sexo);

        if (strcmp(usuarios[i].sexo, "feminino") == 0 || strcmp(usuarios[i].sexo, "masculino") == 0 || strcmp(usuarios[i].sexo, "indiferente") == 0) {
          printf("Sexo válido.\n");
        } else {
          printf("Sexo inválido. Digite novamente.\n");
        }
      } while (!(strcmp(usuarios[i].sexo, "feminino") == 0 || strcmp(usuarios[i].sexo, "masculino") == 0 || strcmp(usuarios[i].sexo, "indiferente") == 0));

      do {
        printf("Digite o novo email: ");
        scanf("%s", usuarios[i].email);

        // Verificar se o caractere '@' está presente no email
        if (strstr(usuarios[i].email, "@") == NULL) {
          printf("Email inválido. Digite novamente.\n");
        } else {
          printf("Email válido.\n");
          break; // Sai do loop quando o email for válido
        }
      } while (1);

      printf("Digite a nova altura: ");
      scanf("%lf", &usuarios[i].altura);

      printf("Digite o novo endereço: ");
      scanf("%s", usuarios[i].endereco);

      printf("Usuário editado com sucesso!\n");
      break; // Sai do loop quando encontrar o usuário
    }
  }

  if (!encontrado) {
    printf("Usuário não encontrado.\n");
  }
}

void excluirUsuario(Usuario **usuarios, int *numUsuarios) {
  int idExcluir;
  printf("Digite o ID do usuário que deseja excluir: ");
  scanf("%d", &idExcluir);

  int encontrado = 0;
  for (int i = 0; i < *numUsuarios; i++) {
    if (idExcluir == (*usuarios)[i].id) {
      encontrado = 1;

      // Deslocar os elementos à frente do usuário a ser excluído para trás
      for (int j = i; j < *numUsuarios - 1; j++) {
        (*usuarios)[j] = (*usuarios)[j + 1];
      }

      (*numUsuarios)--;
      *usuarios = realloc(*usuarios, (*numUsuarios) * sizeof(Usuario));
      printf("Usuário excluído com sucesso!\n");
      break; // Sai do loop quando encontrar o usuário
    }
  }

  if (!encontrado) {
    printf("Usuário não encontrado.\n");
  }
}

void listarUsuarios(Usuario *usuarios, int numUsuarios) {
  printf("----- Lista de Usuários -----\n");

  for (int i = 0; i < numUsuarios; i++) {
    printf("ID: %d\n", usuarios[i].id);
    printf("Nome: %s\n", usuarios[i].nome);
    printf("Sexo: %s\n", usuarios[i].sexo);
    printf("Altura: %.2lf\n", usuarios[i].altura);
    printf("Vacinado: %s\n", usuarios[i].vacinado == 1 ? "Sim" : "Não");
    printf("Email: %s\n", usuarios[i].email);
    printf("Endereço: %s\n", usuarios[i].endereco);
    printf("-----------------------------\n");
  }
}

int main() {
  srand(time(NULL));
  Usuario *usuarios = NULL;
  int numUsuarios = 0;
  int contadorIDs = 1; // Inicializar contador de IDs em 1
  int opcao;

  do {
    printf("----- Menu -----\n");
    printf("1 - Cadastrar Usuário\n");
    printf("2 - Editar Usuário\n");
    printf("3 - Excluir Usuário\n");
    printf("4 - Listar Usuários\n");
    printf("0 - Sair\n");
    printf("----------------\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    system(CLEAR_SCREEN);

    switch (opcao) {
      case 1:
        cadastrarUsuario(&usuarios, &numUsuarios, &contadorIDs);
        break;
      case 2:
        editarUsuario(usuarios, numUsuarios);
        break;
      case 3:
        excluirUsuario(&usuarios, &numUsuarios);
        break;
      case 4:
        listarUsuarios(usuarios, numUsuarios);
        break;
      case 0:
        printf("Encerrando o programa...\n");
        break;
      default:
        printf("Opção inválida. Tente novamente.\n");
    }

    printf("\n");
  } while (opcao != 0);

  free(usuarios);

  return 0;
}
