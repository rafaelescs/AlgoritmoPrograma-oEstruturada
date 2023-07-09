#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define maximoUsuarios 1000
#define maximoTamanhoNome 80
#define maximoTamanhoEmail 50
#define maximoTamanhoEndereco 100

typedef struct {
    int id;
    int vacina;
    double altura;
    char nome[maximoTamanhoNome];
    char email[maximoTamanhoEmail];
    char endereco[maximoTamanhoEndereco];
    char sexo[20];
} Usuario;

Usuario mainCadastros[maximoUsuarios], mainbackupUsuarios[maximoUsuarios];
int totalCadastros = 0;

int incluirID() {
    Usuario novoCadastros;
    int retorno;

    if (totalCadastros >= maximoUsuarios) {
        printf("O limite máximo de usuários foi atingido!\n");
        return;
    }

    novoCadastros.id = rand() % 1000;

    printf("Digite seu nome completo: ");
    fflush(stdin);
    fgets(novoCadastros.nome, maximoTamanhoNome, stdin);

    printf("Digite seu email: ");
    scanf("%s", novoCadastros.email);
    do {
        retorno = 1;
        for (int i = 0; i < strlen(novoCadastros.email); i++) {
        if (novoCadastros.email[i] == '@') {
                retorno = 0;
            break;
            }
        }
        if (retorno == 1) {
            printf("Email inválido. Tente novamente: ");
            scanf("%s", novoCadastros.email);
        }
    } while (retorno == 1);

    printf("Digite o sexo (Feminino, Masculino ou Indiferente): ");
    scanf("%s", novoCadastros.sexo);
    while (!(strcmp(novoCadastros.sexo, "masculino") == 0 || strcmp(novoCadastros.sexo, "feminino") == 0 ||
             strcmp(novoCadastros.sexo, "indiferente") == 0)) {
        printf("Sexo inválido! Digite novamente: ");
        scanf("%s", novoCadastros.sexo);
    }

    printf("Digite endereço: ");
    fflush(stdin);
    fgets(novoCadastros.endereco, maximoTamanhoEmail, stdin);

    printf("Digite sua altura: ");
    scanf("%lf", &novoCadastros.altura);
    while (novoCadastros.altura < 1.00 || novoCadastros.altura > 2.00) {
        printf("Altura inválida. Tente novamente: ");
        scanf("%lf", &novoCadastros.altura);
    }

    printf("O usuário é vacinado? (1 para sim, 0 para não): ");
    scanf("%d", &novoCadastros.vacina);
    while (!(novoCadastros.vacina == 1 || novoCadastros.vacina == 0)) {
        printf("Valor inválido, tente novamente (1 para sim, 0 para não): ");
        scanf("%d", &novoCadastros.vacina);
    }
    mainCadastros[totalCadastros] = novoCadastros;
    totalCadastros++;
    return 0;
}

void editarCadastro()
{
    int id;
    printf("Digite o ID do cadastro a ser editado: ");
    scanf("%d", &id);

    int i;
    for (i = 0; i < totalCadastros; i++)
    {
        if (usuarios[i].id == id)
        {
            Usuario usuario = usuarios[i];

            printf("Digite o novo nome completo: ");
            fgets(usuario.nome, maximoTamanhoNome, stdin);
            usuario.nome[strcspn(usuario.nome, "\n")] = '\0';

            printf("Digite o novo email: ");
            fgets(usuario.email, maximoTamanhoEmail, stdin);
            usuario.email[strcspn(usuario.email, "\n")] = '\0';

            printf("Digite o novo sexo (Feminino, Masculino ou Indiferente): ");
            fgets(usuario.sexo, 20, stdin);
            usuario.sexo[strcspn(usuario.sexo, "\n")] = '\0';

            printf("Digite o novo endereço: ");
            fgets(usuario.endereco, maximoTamanhoEmail, stdin);
            usuario.endereco[strcspn(usuario.endereco, "\n")] = '\0';

            printf("Digite a nova altura (entre 1 e 2 metros): ");
            scanf("%lf", &usuario.altura);
            getchar();

            printf("Recebeu a vacina? (1 - Sim, 0 - Não): ");
            scanf("%d", &usuario.vacina);

            usuarios[i] = usuario;
            printf("Cadastro editado com sucesso.\n");
            return;
        }
    }
        printf("Usuário não encontrado.\n");
}
void fazerBackup()
{
    FILE *arquivo = fopen("backup.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao criar o arquivo de backup.\n");
        return;
    }
    int i;
    for (i = 0; i < totalUsuarios; i++)
    {
        fprintf(arquivo, "%d\n", usuarios[i].id);
        fprintf(arquivo, "%s\n", usuarios[i].nome);
        fprintf(arquivo, "%s\n", usuarios[i].email);
        fprintf(arquivo, "%s\n", usuarios[i].sexo);
        fprintf(arquivo, "%s\n", usuarios[i].endereco);
        fprintf(arquivo, "%.2f\n", usuarios[i].altura);
        fprintf(arquivo, "%d\n", usuarios[i].vacina);
    }

    fclose(arquivo);

    printf("Backup realizado com sucesso.\n");
}
void fazerRestauracao()
{
    FILE *arquivo = fopen("backup.txt", "r");
    if (arquivo == NULL)
    {
        printf("Arquivo de backup não encontrado.\n");
        return;
    }
    totalUsuarios = 0;
    Usuario usuario;

    while (fscanf(arquivo, "%d", &usuario.id) == 1)
    {
        fscanf(arquivo, "%s", usuario.nome);
        fscanf(arquivo, "%s", usuario.email);
        fscanf(arquivo, "%s", usuario.sexo);
        fscanf(arquivo, "%s", usuario.endereco);
        fscanf(arquivo, "%lf", &usuario.altura);
        fscanf(arquivo, "%d", &usuario.vacina);
        usuarios[totalUsuarios++] = usuario;
    }

    fclose(arquivo);

    printf("Restauração dos dados concluída.\n");
}
int main()
{
    srand(time(NULL));
    char opcao;
    do
    {
        printf("Selecione uma opção:\n");
        printf("1. Cadastrar usuário\n");
        printf("2. Editar usuário\n");
        printf("3. Excluir usuário\n");
        printf("4. Buscar usuário pelo email\n");
        printf("5. Imprimir todos os usuários cadastrados\n");
        printf("6. Fazer backup dos usuários cadastrados\n");
        printf("7. Fazer restauração dos dados\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf(" %c", &opcao);

        getchar();

        switch (opcao)
        {
        case '1':
            cadastrarUsuario();
            break;
        case '2':
            editarUsuario();
            break;
        case '3':
            excluirUsuario();
            break;
        case '4':
            buscarUsuarioPorEmail();
            break;
        case '5':
            imprimirUsuarios();
            break;
        case '6':
            fazerBackup();
            break;
        case '7':
            fazerRestauracao();
            break;
        case '0':
            printf("Encerrando o programa.\n");
            break;
        default:
            printf("Opção inválida. Por favor, tente novamente.\n");
            break;
        }

        printf("\n");
    } while (opcao != '0');

  
  return 0;
}
