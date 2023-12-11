#include <stdio.h>
#include <stdlib.h>
#include "pacientes.h"
#include <string.h>
#include "Atendimentos.h"

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




// Prototypes
void menu();
void menuP();
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
    printf("            DIGITE SUA OPCAO\n");
    printf("1. PACIENTE\n");
    printf("2. ATENDIMENTO\n");
    printf("3. SALVAR\n");
    printf("4. SAIR\n");
    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");

    int opcm = 0;
    scanf("%d", &opcm);
    limparBufferEntrada();

    switch (opcm) {
        case PACIENTE:
            menuP();
            break;
        case ATENDIMENTO:
            menuAtendimento();
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
    printf("            DIGITE SUA OPCAO:\n");
    printf("1. INSERIR NOVO PACIENTE\n");
    printf("2. ALTERAR PACIENTE EXISTENTE\n");
    printf("3. EXCLUIR UM PACIENTE\n");
    printf("4. CHECAR DADOS PELO CODIGO DO PACIENTE\n");
    printf("5. MOSTRAR PACIENTES DE UM TIPO SANGUINEO\n");
    printf("6. MOSTRAR PACIENTES PELO DIA DO ATENDIMENTO\n");
    printf("7.MOSTRAR TODOS OS PACIENTES\n");
    printf("8. MOSTRAR PACIENTES EM ORDEM ALFABETICA\n");
    printf("9. SALVAR ALTERACOES\n");
    printf("10. VOLTAR\n");
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
                excluirPaciente(&pacientes,indice);
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
        case LISTAR_CONSULTA:


    }
}

// Menu de Atendimento






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