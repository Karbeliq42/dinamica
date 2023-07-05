#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  char nome[50];
  char sexo[20];
  double altura;
  int vacinado;
  char email[50];
} Usuario;

void cadastrarUsuario(Usuario **usuarios, int *numUsuarios, int *contadorIDs) {
  Usuario novoUsuario;

  printf("----- Cadastrar Usuário -----\n");
  printf("Digite o nome: ");
  scanf("%s", novoUsuario.nome);

  do {
    printf("Digite o sexo (feminino, masculino ou indiferente): ");
    scanf("%s", novoUsuario.sexo);

    if (strcmp(novoUsuario.sexo, "feminino") == 0 ||
        strcmp(novoUsuario.sexo, "masculino") == 0 ||
        strcmp(novoUsuario.sexo, "indiferente") == 0) {
      printf("Sexo válido.\n");
    } else {
      printf("Sexo inválido. Digite novamente.\n");
    }
  } while (!(strcmp(novoUsuario.sexo, "feminino") == 0 ||
             strcmp(novoUsuario.sexo, "masculino") == 0 ||
             strcmp(novoUsuario.sexo, "indiferente") == 0));

  do {
    printf("Digite a altura: ");
    scanf("%lf", &novoUsuario.altura);

    if (novoUsuario.altura >= 1 && novoUsuario.altura <= 2) {
      printf("Altura válida.\n");
    } else {
      printf("Altura inválida. Digite novamente.\n");
    }
  } while (!(novoUsuario.altura >= 1 && novoUsuario.altura <= 2));

  do {
    printf("Digite 1 se você estiver vacinado ou 2 se não estiver: ");
    scanf("%d", &novoUsuario.vacinado);

    switch (novoUsuario.vacinado) {
    case 1:
      printf("Você está vacinado!\n");
      break;
    case 2:
      printf("Você não está vacinado.\n");
      break;
    default:
      printf("Opção inválida. Digite novamente.\n");
      break;
    }
  } while (novoUsuario.vacinado != 1 && novoUsuario.vacinado != 2);

  do {
    printf("Digite o seu email: ");
    scanf("%s", novoUsuario.email);

    // Verificar se o caractere '@' está presente no email
    if (strstr(novoUsuario.email, "@") == NULL) {
      printf("Email inválido. Digite novamente.\n");
    } else {
      printf("Email válido.\n");
      break; // Sai do loop quando o email for válido
    }
  } while (1);

  novoUsuario.id = (*contadorIDs)++;
  (*numUsuarios)++;
  *usuarios = realloc(*usuarios, (*numUsuarios) * sizeof(Usuario));
  (*usuarios)[(*numUsuarios) - 1] = novoUsuario;

  printf("Usuário cadastrado com sucesso!\n");
}

void editarUsuario(Usuario *usuarios, int numUsuarios) {
  int idEditar;
  printf("Digite o ID do usuário que deseja editar: ");
  scanf("%d", &idEditar);

  for (int i = 0; i < numUsuarios; i++) {
    if (usuarios[i].id == idEditar) {
      printf("----- Editar Usuário -----\n");

      printf("Digite o novo nome: ");
      scanf("%s", usuarios[i].nome);

      do {
        printf("Digite o novo sexo (feminino, masculino ou indiferente): ");
        scanf("%s", usuarios[i].sexo);

        if (strcmp(usuarios[i].sexo, "feminino") == 0 ||
            strcmp(usuarios[i].sexo, "masculino") == 0 ||
            strcmp(usuarios[i].sexo, "indiferente") == 0) {
          printf("Sexo válido.\n");
        } else {
          printf("Sexo inválido. Digite novamente.\n");
        }
      } while (!(strcmp(usuarios[i].sexo, "feminino") == 0 ||
                 strcmp(usuarios[i].sexo, "masculino") == 0 ||
                 strcmp(usuarios[i].sexo, "indiferente") == 0));

      do {
        printf("Digite a nova altura: ");
        scanf("%lf", &usuarios[i].altura);

        if (usuarios[i].altura >= 1 && usuarios[i].altura <= 2) {
          printf("Altura válida.\n");
        } else {
          printf("Altura inválida. Digite novamente.\n");
        }
      } while (!(usuarios[i].altura >= 1 && usuarios[i].altura <= 2));

      do {
        printf("Digite 1 se você estiver vacinado ou 2 se não estiver: ");
        scanf("%d", &usuarios[i].vacinado);

        switch (usuarios[i].vacinado) {
        case 1:
          printf("Você está vacinado!\n");
          break;
        case 2:
          printf("Você não está vacinado.\n");
          break;
        default:
          printf("Opção inválida. Digite novamente.\n");
          break;
        }
      } while (usuarios[i].vacinado != 1 && usuarios[i].vacinado != 2);

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

      printf("Usuário editado com sucesso!\n");
      return;
    }
  }

  printf("Usuário não encontrado.\n");
}

void excluirUsuario(Usuario **usuarios, int *numUsuarios) {
  int idExcluir;
  printf("Digite o ID do usuário que deseja excluir: ");
  scanf("%d", &idExcluir);

  for (int i = 0; i < *numUsuarios; i++) {
    if ((*usuarios)[i].id == idExcluir) {
      for (int j = i; j < (*numUsuarios) - 1; j++) {
        (*usuarios)[j] = (*usuarios)[j + 1];
      }

      (*numUsuarios)--;
      *usuarios = realloc(*usuarios, (*numUsuarios) * sizeof(Usuario));
      printf("Usuário excluído com sucesso!\n");
      return;
    }
  }

  printf("Usuário não encontrado.\n");
}

void listarUsuarios(Usuario *usuarios, int numUsuarios) {
  if (numUsuarios == 0) {
    printf("Nenhum usuário cadastrado.\n");
    return;
  }

  printf("----- Lista de Usuários -----\n");
  for (int i = 0; i < numUsuarios; i++) {
    printf("ID: %d\n", usuarios[i].id);
    printf("Nome: %s\n", usuarios[i].nome);
    printf("Sexo: %s\n", usuarios[i].sexo);
    printf("Altura: %.2f\n", usuarios[i].altura);
    printf("Vacinado: %s\n", (usuarios[i].vacinado == 1) ? "Sim" : "Não");
    printf("Email: %s\n", usuarios[i].email);
    printf("-----------------------------\n");
  }
}

int main() {
  Usuario *usuarios = NULL;
  int numUsuarios = 0;
  int contadorIDs = 1;
  int opcao;

  do {
    printf("----- Menu -----\n");
    printf("1 - Cadastrar usuário\n");
    printf("2 - Editar usuário\n");
    printf("3 - Excluir usuário\n");
    printf("4 - Listar usuários\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

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
      printf("Encerrando o programa.\n");
      break;
    default:
      printf("Opção inválida. Digite novamente.\n");
      break;
    }

    printf("\n");
  } while (opcao != 0);

  free(usuarios);

  return 0;
}
