#include <stdio.h>
#include <stdlib.h>
#include "pacientes.h"
#include <string.h>


struct VetorDinamico pacientes;

// Enum for menu options
enum MainMenuOptions {
    PACIENTE = 1,
    ATENDIMENTO,
    SALVAR,
    SAIR
};

// Enum for paciente menu options
enum PacienteMenuOptions {
    INSERIR = 1,
    ALTERAR,
    REMOVER,
    IMPRIMIR_DADOS,
    LISTAR_TIPO_SANGUINEO,
    LISTAR_CONSULTA,
    LISTAR_TODOS,
    LISTAR_ALFABETICA,
    SALVARP,
    VOLTAR_PACIENTE
};

// Enum for atendimento menu options
enum AtendimentoMenuOptions {
    INSERIR_ATENDIMENTO = 1,
    ALTERAR_ATENDIMENTO,
    EXCLUIR_ATENDIMENTO,
    LISTAR_POR_CODIGO_ATENDIMENTO,
    LISTAR_POR_CODIGO_PACIENTE,
    LISTAR_POR_DATA,
    SOMA_CONSULTAS_PACIENTE,
    SOMA_CONSULTAS_DATA,
    SOMA_CONSULTAS_INTERVALO,
    SALVARA,
    VOLTAR_ATENDIMENTO
};

// Prototypes
void menu();
void menuP();
void menuA();
void limparBufferEntrada();
void salvarDados();
int realizarAlteracoesAntesDeSair();

int main()
{
    inicializarVetor(&pacientes, 10);

    carregarDeArquivo(&pacientes,"pacientes.txt");

    srand(time(NULL));

    menu();

    return 0;
}

// Menu Principal
void menu()
{
    printf("$$$$$$$$$$$$$$ CLINICA AJALMAR $$$$$$$$$$$$$$\n");
    printf("            digite sua opcao\n");
    printf("1. Paciente\n");
    printf("2. Atendimento\n");
    printf("3. Salvar\n");
    printf("4. Sair\n");
    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");

    int opcm = 0;
    scanf("%d", &opcm);
    limparBufferEntrada();

    switch (opcm) {
        case PACIENTE:
            menuP();
            break;
        case ATENDIMENTO:
            menuA();
            break;

        case SALVAR:
            salvarEmArquivo(&pacientes,"pacientes.txt");
            menu();
            break;
        case SAIR:
        {
            int i = realizarAlteracoesAntesDeSair();

            if (i == 1) {
                salvarDados();
                exit(0);
            }
            else if (i == 0)
            {
                exit(0);
            }
            else {
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                printf("Opcao invalida. Insira um codigo valido.\n");
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                menu();
            }
        }

    }
}

// Menu do Paciente
void menuP()
{
    printf("$$$$$$$$$$$$$$ PACIENTE $$$$$$$$$$$$$$\n");
    printf("            digite sua opcao\n");
    printf("1. Inserir novo paciente\n");
    printf("2. Alterar paciente existente\n");
    printf("3. Excluir um paciente\n");
    printf("4. Checar dados pelo codigo do paciente\n");
    printf("5. Mostrar pacientes de um tipo sanguineo\n");
    printf("6. Mostrar pacientes pelo dia do atendimento\n");
    printf("7. Mostrar todos os pacientes\n");
    printf("8. Mostrar pacientes em ordem alfabetica\n");
    printf("9. Salvar Alteracoes\n");
    printf("10. Voltar\n");
    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");

    int opc = 0;
    scanf("%d", &opc);
    limparBufferEntrada();

    switch (opc) {
        case INSERIR:
            inserir(&pacientes);
            menuP();
            break;
        case ALTERAR:
            alterarPaciente(&pacientes);
            menuP();
            break;
        case REMOVER:
        {
            char *cpf = lerCPF();

            int indice = buscarPacientePorCPF(&pacientes, cpf);

            if (indice == -1)
            {
                printf("Paciente com CPF %s nao encontrado.\n", cpf);
            }

            else
            {
                excluirPaciente(&pacientes, cpf, indice);
            }

            menuP();
        }
        case IMPRIMIR_DADOS:
        {
            char* cd = malloc(10);  // Aloca dinamicamente espaço para o TS


            printf("=====================================\n");
            printf("Insira o codigo do paciente: \n");
            printf("=====================================\n");
            fgets(cd, 10, stdin);
            cd[strcspn(cd, "\n")] = '\0';

            int indice = -1;

            for (int i = 0; i < pacientes.tamanho; ++i)
            {
                if (pacientes.dados[i].codigo != NULL && strcmp(cd, pacientes.dados[i].codigo) == 0)
                {
                    indice = i;
                    break;
                }
            }

            if (indice == -1)
            {
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                printf("Não existe pacientes com este codigo\n");
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            }

            else
            {
                imprimirPacientesPorCodigo(&pacientes,cd);
            }

            free(cd);
            menuP();
            break;
        }



        case LISTAR_TIPO_SANGUINEO:
        {
            char* ts = malloc(5);  // Aloca dinamicamente espaço para o TS


            printf("=====================================\n");
            printf("Insira o tipo sanguineo do paciente: \n");
            printf("=====================================\n");
            fgets(ts, 5, stdin);
            ts[strcspn(ts, "\n")] = '\0';

            int indice;

            for (int i = 0; i < pacientes.tamanho; ++i)
            {
                if (pacientes.dados[i].ts != NULL && strcmp(ts, pacientes.dados[i].ts) == 0)
                {
                    indice = 1;
                    break;
                }
                else indice = -1;
            }

            if (indice == -1)
            {
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                printf("Não existe pacientes com este tipo sanguineo\n");
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            }

            else
            {
                imprimirPacientesPorTipoSanguineo(&pacientes,ts);
            }

            free(ts);

            menuP();
            break;
        }

        case LISTAR_TODOS:
            imprimir_pacientes(&pacientes);
            menuP();
            break;

        case LISTAR_ALFABETICA:
            imprimir_ordem(&pacientes);
            menuP();
            break;
        case SALVARP:
            salvarEmArquivo(&pacientes,"pacientes.txt");
            menuP();
            break;

        case VOLTAR_PACIENTE:
            menu();
            break;
    }
}

// Menu de Atendimento
void menuA()
{
    printf("$$$$$$$$$$$$$$ Atendimento $$$$$$$$$$$$$$\n");
    printf("            digite sua opcao\n");
    printf("1. Inserir novo atendimento\n");
    printf("2. Alterar atendimento existente\n");
    printf("3. Excluir um atendimento\n");
    printf("4. Checar dados pelo codigo do atendimento\n");
    printf("5. Checar dados pelo codigo do paciente\n");
    printf("6. Mostrar pacientes em ordem de data de atendimento\n");
    printf("7. Mostrar soma das consultas de um paciente\n");
    printf("8. Mostrar soma das consultas de uma data de consulta\n");
    printf("9. Mostrar soma das consultas de um intervalo\n");
    printf("10. Voltar\n");
    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");

    int opcA = 0;
    scanf("%d", &opcA);
    limparBufferEntrada();

    switch (opcA) {
        case INSERIR_ATENDIMENTO:
            menuA();
            break;


        // insere aqui os outros cases

        case SALVARP:
            menuA();
            break;

        case VOLTAR_ATENDIMENTO:
            menu();
            break;
    }
}

void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// Função para salvar os dados em um arquivo
void salvarDados()
{
    salvarEmArquivo(&pacientes, "pacientes.txt");
    printf("Dados salvos com sucesso!\n");
}

// Função para perguntar ao usuário se deseja realizar alterações antes de sair
int realizarAlteracoesAntesDeSair()
{
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("         Deseja realizar alteracoes antes de sair?\n");
    printf("                 (1 - Sim, 0 - Nao):\n");
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    int resposta;
    scanf("%d", &resposta);
    limparBufferEntrada();
    return resposta;
}