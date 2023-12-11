#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>


struct paciente
{
    char *codigo;
    char *nome;
    char *rh;
    char *RG;
    char *cpf;
    char *ts;
    char *end;
    struct tm dataNascimento;
};

struct VetorDinamico {
    struct paciente *dados;
    int tamanho;
    int capacidade;
};

int compararPacientes(const void *a, const void *b) {
    const struct paciente *pacienteA = (const struct paciente *)a;
    const struct paciente *pacienteB = (const struct paciente *)b;
    return strcmp(pacienteA->nome, pacienteB->nome);
}

// Função para converter uma string para maiúsculas
void converterParaMaiusculas(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper(str[i]);
    }
}

// Função pra liberar memoria usada pelo paciente
void liberarPaciente(struct paciente *p)
{
    free(p->nome);
    free(p->RG);
    free(p->cpf);
    free(p->ts);
    free(p->rh);
    free(p->end);
}

// Função pra liberar a memoria de todos os pacientes no vetor
void liberarMemoria(struct VetorDinamico *pacientes)
{
    for (int i = 0; i < pacientes->tamanho; ++i)
    {
        liberarPaciente(&pacientes->dados[i]);
    }
    free(pacientes->dados);
}

void inicializarVetor(struct VetorDinamico *vetor, int capacidadeInicial) {
    vetor->dados = (struct paciente *)malloc(capacidadeInicial * sizeof(struct paciente));
    if (vetor->dados == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    // Allocate memory for strings in each paciente
    for (int i = 0; i < capacidadeInicial; ++i) {
        vetor->dados[i].codigo = NULL;
        vetor->dados[i].nome = NULL;
        vetor->dados[i].RG = NULL;
        vetor->dados[i].cpf = NULL;
        vetor->dados[i].ts = NULL;
        vetor->dados[i].rh = NULL;
        vetor->dados[i].end = NULL;
    }

    vetor->tamanho = 0;
    vetor->capacidade = capacidadeInicial;
}
void adicionarElemento(struct VetorDinamico *vetor, struct paciente paciente) {
    if (vetor->tamanho == vetor->capacidade) {
        vetor->capacidade *= 2;
        vetor->dados = (struct paciente *)realloc(vetor->dados, vetor->capacidade * sizeof(struct paciente));
        if (vetor->dados == NULL) {
            printf("Erro na realocação de memória.\n");
            exit(1);
        }
    }

    vetor->dados[vetor->tamanho] = paciente;
    vetor->tamanho++;
}

// Função para ler a data de nascimento
void lerDataNascimento(struct tm *dataNascimento)
{
    printf("=====================================\n");
    printf("Insira a data de nascimento (Modelo: DD MM YYYY): \n");
    printf("=====================================\n");

    while (1)
    {
        char data_buffer[20];
        fgets(data_buffer, sizeof(data_buffer), stdin);
        data_buffer[strcspn(data_buffer, "\n")] = '\0';

        // Verifica se a linha lida contém apenas a nova linha (\n)
        if (strlen(data_buffer) > 0)
        {
            // Converte a string para uma estrutura tm
            if (sscanf(data_buffer, "%d %d %d", &dataNascimento->tm_mday, &dataNascimento->tm_mon, &dataNascimento->tm_year) == 3)
            {
                dataNascimento->tm_year -= 1900;
                dataNascimento->tm_mon -= 1;
                break;
            }

            else
            {
                printf("Formato inválido. Insira novamente a data no formato (DD MM YYYY): \n");
            }
        }
    }
}

// Função para ler o tipo sanguíneo
void lerTipoSanguineo(char *tipoSanguineo)
{
    printf("=====================================\n");
    printf("Escolha o tipo sanguineo (A, B, O, AB): \n");
    printf("=====================================\n");
    scanf(" %c", tipoSanguineo);
    *tipoSanguineo = toupper(*tipoSanguineo); // Converte para maiúscula
    while (*tipoSanguineo != 'A' && *tipoSanguineo != 'B' && *tipoSanguineo != 'O' && *tipoSanguineo != 'AB')
    {
        printf("Opção inválida. Escolha entre A, B, O ou AB: ");
        scanf(" %c", tipoSanguineo);
        *tipoSanguineo = toupper(*tipoSanguineo); // Converte para maiúscula
    }
}

// Função para ler o fator RH
void lerFatorRH(char *fatorRH)
{
    printf("=====================================\n");
    printf("Escolha o fator RH (+ ou -): \n");
    printf("=====================================\n");
    scanf(" %c", fatorRH);
    *fatorRH = toupper(*fatorRH); // Converte para maiúscula
    while (*fatorRH != '+' && *fatorRH != '-')
    {
        printf("Opção inválida. Escolha entre + ou -: ");
        scanf(" %c", fatorRH);
        *fatorRH = toupper(*fatorRH); // Converte para maiúscula
    }
}


// Insere o paciente
struct VetorDinamico *inserir(struct VetorDinamico *pacientes)
{
    struct paciente np;

    while(1)
    {
        // Pedir nome do paciente
        char nome[255];
        printf("=====================================\n");
        printf("Insira o nome do Paciente: \n");
        printf("=====================================\n");
        fgets(nome, sizeof(nome), stdin);
        // Remover a nova linha do final
        nome[strcspn(nome, "\n")] = '\0';


        // Converter para maiúsculas
        converterParaMaiusculas(nome);

        if (strlen(nome) > 0) {
            np.nome = strdup(nome);
            break;
        }
    }



    //pedir rg
    char buffer[12];
    char RG[12];
    printf("=====================================\n");
    printf("Insira o RG do paciente: \n");
    printf("=====================================\n");
    fgets(buffer, sizeof(buffer), stdin);
    // Remover a nova linha do final
    buffer[strcspn(buffer, "\n")] = '\0';

    // Converter para maiúsculas
    converterParaMaiusculas(buffer);

    // Se a linha lida contiver apenas a nova linha (\n), atribui um valor vazio ou nulo
    if (buffer[0] == '\0' || buffer[0] == '\n') {
        np.RG = strdup("");
    } else {
        np.RG = strdup(buffer);
    }

    // Check for duplicate CPF
    while(1)
    {
        char cpf_buffer[20];
        while(1)
        {
            // Pedir CPF do paciente

            printf("=====================================\n");
            printf("Insira o CPF do paciente: \n");
            printf("=====================================\n");
            fgets(cpf_buffer, sizeof(cpf_buffer), stdin);
            cpf_buffer[strcspn(cpf_buffer, "\n")] = '\0';

            if (strlen(cpf_buffer) > 0) {
                np.cpf = strdup(cpf_buffer);
                break;
            }
        }

        int isDuplicate = 0;

        for (int i = 0; i < pacientes->tamanho; ++i) {
            if (pacientes->dados[i].cpf != NULL && strcmp(cpf_buffer, pacientes->dados[i].cpf) == 0) {
                isDuplicate = 1;
                break;
            }
        }
        if(isDuplicate)
        {
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("O CPF ja foi inserido, tente novamente.\n");
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("\n");
        }

        if (!isDuplicate)
        {
            np.cpf = strdup(cpf_buffer);
            break;

        }
    }

    //pedir tipo sanguíneo
    char tipoSanguineo;
    lerTipoSanguineo(&tipoSanguineo);
    np.ts = malloc(3);
    snprintf(np.ts, 3, "%c", tipoSanguineo);

    //pedir fator rh
    char fatorRH;
    lerFatorRH(&fatorRH);
    np.rh = malloc(2);
    snprintf(np.rh, 2, "%c", fatorRH);

    lerDataNascimento(&np.dataNascimento);

    //pedir edenreço
    char bufferEnd[255];
    printf("=====================================\n");
    printf("Insira o endereco: \n");
    printf("=====================================\n");
    fgets(bufferEnd, sizeof(bufferEnd), stdin);

    // Remover a nova linha do final
    bufferEnd[strcspn(bufferEnd, "\n")] = '\0';

    // Converter para maiúsculas
    converterParaMaiusculas(bufferEnd);

    // Se a linha lida contiver apenas a nova linha (\n), atribui um valor vazio ou nulo
    if (bufferEnd[0] == '\0' || bufferEnd[0] == '\n') {
        np.end = strdup("");
    } else {
        np.end = strdup(bufferEnd);
    }



    int codigo = rand();
    char codigostr[8];

    snprintf(codigostr, sizeof(codigostr), "%d", codigo);
    np.codigo = strdup(codigostr);
    printf("=====================================\n");
    printf("Paciente adicionado.    Codigo: %s.\n", codigostr);
    printf("  Pressione ENTER para continuar...\n");
    printf("=====================================\n");
    while(1)
    {
        fgets(buffer, sizeof(buffer), stdin);
        // Se a linha lida contiver apenas a nova linha (\n), atribui um valor vazio ou nulo
        if (buffer[0] == '\0' || buffer[0] == '\n')
        {
            // Adiciona o paciente ao vetor dinâmico
            adicionarElemento(pacientes, np);
            return pacientes;
        }

        else
        {
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("           Pressione Enter!\n");
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }

    }
}


// Função para buscar um paciente pelo CPF
int buscarPacientePorCPF(const struct VetorDinamico *pacientes, const char *cpf)
{
    for (int i = 0; i < pacientes->tamanho; ++i)
    {
        if (pacientes->dados[i].cpf != NULL && strcmp(cpf, pacientes->dados[i].cpf) == 0)
        {
            return i; // Retorna o índice do paciente encontrado
        }
    }
    return -1; // Retorna -1 se o paciente não for encontrado
}
// Enumeração para representar as opções de alteração
enum OpcoesAlteracao
{
    ALTERAR_NOME = 1,
    ALTERAR_RG,
    ALTERAR_TIPO_SANGUINEO,
    ALTERAR_FATOR_RH,
    ALTERAR_ENDERECO,
    ALTERAR_DATA_NASCIMENTO,
    ALTERAR_CPF,
    CANCELAR_ALTERACAO
};

// Função para alterar dados de um paciente
void alterarPaciente(struct VetorDinamico *pacientes)
{
    char cpf_buffer[20];
    printf("=====================================\n");
    printf("Insira o CPF do paciente que deseja alterar: \n");
    printf("=====================================\n");
    fgets(cpf_buffer, sizeof(cpf_buffer), stdin);
    cpf_buffer[strcspn(cpf_buffer, "\n")] = '\0';

    int indice = buscarPacientePorCPF(pacientes, cpf_buffer);

    if (indice == -1)
    {
        printf("Paciente com CPF %s nao encontrado.\n", cpf_buffer);
    }
    else
    {
        printf("=====================================\n");
        printf("Escolha o que deseja alterar:\n");
        printf("%d. Nome\n", ALTERAR_NOME);
        printf("%d. RG\n", ALTERAR_RG);
        printf("%d. Tipo Sanguineo\n", ALTERAR_TIPO_SANGUINEO);
        printf("%d. Fator RH\n", ALTERAR_FATOR_RH);
        printf("%d. Endereco\n", ALTERAR_ENDERECO);
        printf("%d. Data de Nascimento\n", ALTERAR_DATA_NASCIMENTO);
        printf("%d. CPF\n", ALTERAR_CPF);  // Adicionando a opção para alterar CPF
        printf("%d. Cancelar\n", CANCELAR_ALTERACAO);
        printf("=====================================\n");

        int opcao;
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer de entrada

        switch (opcao)
        {
            case ALTERAR_NOME:
                printf("Insira o novo nome: ");
                fgets(pacientes->dados[indice].nome, sizeof(pacientes->dados[indice].nome), stdin);
                pacientes->dados[indice].nome[strcspn(pacientes->dados[indice].nome, "\n")] = '\0';
                break;
            case ALTERAR_RG:
                printf("Insira o novo RG: ");
                fgets(pacientes->dados[indice].RG, sizeof(pacientes->dados[indice].RG), stdin);
                pacientes->dados[indice].RG[strcspn(pacientes->dados[indice].RG, "\n")] = '\0';
                break;
            case ALTERAR_TIPO_SANGUINEO:
                printf("Insira o novo tipo sanguíneo: ");
                fgets(pacientes->dados[indice].ts, sizeof(pacientes->dados[indice].ts), stdin);
                pacientes->dados[indice].ts[strcspn(pacientes->dados[indice].ts, "\n")] = '\0';
                break;
            case ALTERAR_FATOR_RH:
                printf("Insira o novo fator RH: ");
                fgets(pacientes->dados[indice].rh, sizeof(pacientes->dados[indice].rh), stdin);
                pacientes->dados[indice].rh[strcspn(pacientes->dados[indice].rh, "\n")] = '\0';
                break;
            case ALTERAR_ENDERECO:
                printf("Insira o novo endereço: ");
                fgets(pacientes->dados[indice].end, sizeof(pacientes->dados[indice].end), stdin);
                pacientes->dados[indice].end[strcspn(pacientes->dados[indice].end, "\n")] = '\0';
                break;
            case ALTERAR_DATA_NASCIMENTO:
                printf("Insira a nova data de nascimento (DD MM YYYY): ");
                lerDataNascimento(&pacientes->dados[indice].dataNascimento);
                break;
            case ALTERAR_CPF:
                // Função para alterar CPF
                alterarCPF(pacientes, indice);
                break;
            case CANCELAR_ALTERACAO:
                printf("Operação cancelada.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    }
}
// Função modificada para trabalhar com VetorDinamico
void imprimir_pacientes(const struct VetorDinamico *pacientes) {
    // Título
    printf("%-20s%-15s%-15s%-9s%-20s%-25s%-20s\n", "Nome", "RG", "CPF", "T.S", "Fator RH", "Endereco", "Codigo");
    printf("========================================================================================================================\n");

    // Dados dos pacientes
    for (int i = 0; i < pacientes->tamanho; i++) {

        printf("%-20s%-15s%-15s%-9s%-20s%-25s%-20s\n",
               pacientes->dados[i].nome, pacientes->dados[i].RG, pacientes->dados[i].cpf,
               pacientes->dados[i].ts, pacientes->dados[i].rh, pacientes->dados[i].end,
               pacientes->dados[i].codigo);

        printf("Data Nascimento: %02d/%02d/%04d\n",
               pacientes->dados[i].dataNascimento.tm_mday,
               pacientes->dados[i].dataNascimento.tm_mon + 1,
               pacientes->dados[i].dataNascimento.tm_year + 1900);
        printf("========================================================================================================================\n");
    }
}

// Função para salvar os dados dos pacientes em um arquivo texto
void salvarEmArquivo(const struct VetorDinamico *pacientes, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }

    // Escreve os dados dos pacientes no arquivo
    for (int i = 0; i < pacientes->tamanho; i++)
    {
        fprintf(arquivo, "%s;%s;%s;%s;%s;%s;%s;%d/%d/%d\n",
                pacientes->dados[i].codigo, pacientes->dados[i].nome, pacientes->dados[i].RG,
                pacientes->dados[i].cpf, pacientes->dados[i].ts, pacientes->dados[i].rh,
                pacientes->dados[i].end,
                pacientes->dados[i].dataNascimento.tm_mday,
                pacientes->dados[i].dataNascimento.tm_mon + 1,
                pacientes->dados[i].dataNascimento.tm_year + 1900);
    }

    fclose(arquivo);
}

/// Função para carregar dados dos pacientes de um arquivo texto
void carregarDeArquivo(struct VetorDinamico *pacientes, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        // O arquivo não existe, então tenta criar
        printf("O arquivo %s não existe. Criando o arquivo...\n", nomeArquivo);

        arquivo = fopen(nomeArquivo, "w");

        if (arquivo == NULL)
        {
            // Não foi possível criar o arquivo
            printf("Erro ao criar o arquivo %s.\n", nomeArquivo);
            return;
        }

        // Fecha o arquivo recém-criado
        fclose(arquivo);

        // Agora, reabre o arquivo para leitura
        arquivo = fopen(nomeArquivo, "r");
    }

    char linha[512]; // Ajuste o tamanho conforme necessário

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        struct paciente np;

        // Utilize a função sscanf para extrair os dados da linha e atribuir ao paciente np
        if (sscanf(linha, "%m[^;];%m[^;];%m[^;];%m[^;];%m[^;];%m[^;];%m[^;];%d/%d/%d",
                   &np.codigo, &np.nome, &np.RG, &np.cpf, &np.ts, &np.rh, &np.end,
                   &np.dataNascimento.tm_mday, &np.dataNascimento.tm_mon, &np.dataNascimento.tm_year) == 10)
        {
            // Ajuste conforme necessário para lidar com os dados lidos
            np.dataNascimento.tm_mon -= 1;
            np.dataNascimento.tm_year -= 1900;

            adicionarElemento(pacientes, np);
        }
        else
        {
            printf("Erro ao ler a linha: %s\n", linha);
        }
    }

    fclose(arquivo);
}


// Função para excluir um paciente com base no CPF
void excluirPaciente(struct VetorDinamico *pacientes, const char *cpf, int indice)
{
    // Libera a memória alocada para o paciente excluído
    liberarPaciente(&pacientes->dados[indice]);

    // Desloca os pacientes à direita do paciente excluído para preencher o espaço
    for (int i = indice; i < pacientes->tamanho - 1; ++i)
    {
        pacientes->dados[i] = pacientes->dados[i + 1];
    }

    // Reduz o tamanho do vetor dinâmico
    pacientes->tamanho--;

    printf("Paciente excluido com sucesso.\n");


}

// Função para imprimir pacientes com um determinado tipo sanguíneo
void imprimirPacientesPorTipoSanguineo(const struct VetorDinamico *pacientes, const char *tipoSanguineo)
{
    printf("Pacientes com tipo sanguineo %s:\n", tipoSanguineo);

    int pacientesEncontrados = 0;

    // Título
    printf("%-20s%-15s%-15s%-9s%-20s%-25s%-20s\n", "Nome", "RG", "CPF", "T.S", "Fator RH", "Endereco", "Codigo");
    printf("========================================================================================================================\n");

    for (int i = 0; i < pacientes->tamanho; i++)
    {
        // Comparar tipos sanguíneos, ignorando maiúsculas/minúsculas
        if (strcasecmp(pacientes->dados[i].ts, tipoSanguineo) == 0)
        {
            pacientesEncontrados++;

            printf("%-20s%-15s%-15s%-9s%-20s%-25s%-20s\n",
                   pacientes->dados[i].nome, pacientes->dados[i].RG, pacientes->dados[i].cpf,
                   pacientes->dados[i].ts, pacientes->dados[i].rh, pacientes->dados[i].end,
                   pacientes->dados[i].codigo);

            printf("Data Nascimento: %02d/%02d/%04d\n",
                   pacientes->dados[i].dataNascimento.tm_mday,
                   pacientes->dados[i].dataNascimento.tm_mon + 1,
                   pacientes->dados[i].dataNascimento.tm_year + 1900);
            printf("========================================================================================================================\n");

        }
    }

    if (pacientesEncontrados == 0)
    {
        printf("Nenhum paciente encontrado com o tipo sanguineo %s.\n", tipoSanguineo);
    }
}

// Função para imprimir pacientes com um determinado tipo sanguíneo
void imprimirPacientesPorCodigo(const struct VetorDinamico *pacientes, const char *codigo)
{
    printf("---------------------------\n");
    printf("Pacientes do codigo %s:\n", codigo);
    printf("---------------------------\n");

    int pacientesEncontrados = 0;

    // Título
    printf("%-20s%-15s%-15s%-9s%-20s%-25s%-20s\n", "Nome", "RG", "CPF", "T.S", "Fator RH", "Endereco", "Codigo");
    printf("========================================================================================================================\n");

    for (int i = 0; i < pacientes->tamanho; i++)
    {
        // Comparar tipos sanguíneos, ignorando maiúsculas/minúsculas
        if (strcasecmp(pacientes->dados[i].codigo,  codigo) == 0)
        {
            pacientesEncontrados++;

            printf("%-20s%-15s%-15s%-9s%-20s%-25s%-20s\n",
                   pacientes->dados[i].nome, pacientes->dados[i].RG, pacientes->dados[i].cpf,
                   pacientes->dados[i].ts, pacientes->dados[i].rh, pacientes->dados[i].end,
                   pacientes->dados[i].codigo);

            printf("Data Nascimento: %02d/%02d/%04d\n",
                   pacientes->dados[i].dataNascimento.tm_mday,
                   pacientes->dados[i].dataNascimento.tm_mon + 1,
                   pacientes->dados[i].dataNascimento.tm_year + 1900);
            printf("========================================================================================================================\n");

        }
    }

    if (pacientesEncontrados == 0)
    {
        printf("Nenhum paciente encontrado com o codigo %s.\n",  codigo);
    }
}


// Função modificada para ordenar pacientes antes de imprimir
void imprimir_ordem(const struct VetorDinamico *pacientes) {
    // Criar uma cópia dos dados dos pacientes
    struct paciente *copia_pacientes = malloc(pacientes->tamanho * sizeof(struct paciente));
    if (copia_pacientes == NULL) {
        printf("Erro na alocação de memória para cópia dos pacientes.\n");
        exit(1);
    }

    memcpy(copia_pacientes, pacientes->dados, pacientes->tamanho * sizeof(struct paciente));

    // Ordenando a cópia do array de pacientes usando qsort e a função de comparação
    qsort(copia_pacientes, pacientes->tamanho, sizeof(struct paciente), compararPacientes);

    // Título
    printf("%-20s%-15s%-15s%-9s%-20s%-25s%-20s\n", "Nome", "RG", "CPF", "T.S", "Fator RH", "Endereco", "Codigo");
    printf("========================================================================================================================\n");

    // Dados dos pacientes ordenados
    for (int i = 0; i < pacientes->tamanho; i++) {
        printf("%-20s%-15s%-15s%-9s%-20s%-25s%-20s\n",
               copia_pacientes[i].nome, copia_pacientes[i].RG, copia_pacientes[i].cpf,
               copia_pacientes[i].ts, copia_pacientes[i].rh, copia_pacientes[i].end,
               copia_pacientes[i].codigo);

        printf("Data Nascimento: %02d/%02d/%04d\n",
               copia_pacientes[i].dataNascimento.tm_mday,
               copia_pacientes[i].dataNascimento.tm_mon + 1,
               copia_pacientes[i].dataNascimento.tm_year + 1900);
        printf("========================================================================================================================\n");
    }

    // Liberar a memória alocada para a cópia
    free(copia_pacientes);
}

char* lerCPF() {

    char* cpf = malloc(20);  // Aloca dinamicamente espaço para o CPF

    if (cpf == NULL) {
        printf("Erro na alocação de memória para CPF.\n");
        exit(1);
    }

    printf("=====================================\n");
    printf("Insira o CPF do paciente: \n");
    printf("=====================================\n");
    fgets(cpf, 20, stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    return cpf;
}
// Função para alterar CPF
void alterarCPF(struct VetorDinamico *pacientes, int indice)
{
    char novoCPF[20];
    printf("Insira o novo CPF: ");
    fgets(novoCPF, sizeof(novoCPF), stdin);
    novoCPF[strcspn(novoCPF, "\n")] = '\0';

    // Verificar se o novo CPF já existe
    int existeCPF = 0;
    for (int i = 0; i < pacientes->tamanho; i++)
    {
        if (i != indice && strcmp(pacientes->dados[i].cpf, novoCPF) == 0)
        {
            existeCPF = 1;
            break;
        }
    }

    if (existeCPF)
    {
        printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        printf("CPF %s ja existe, nao foi posivel alterar.\n", novoCPF);
        printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    }
    else
    {
        // Liberar a memória do CPF antigo
        free(pacientes->dados[indice].cpf);

        // Alocar memória para o novo CPF
        pacientes->dados[indice].cpf = strdup(novoCPF);

        printf("CPF alterado com sucesso.\n");
    }
}