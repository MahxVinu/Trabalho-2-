#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Atendimentos.h"
void limparbuffer()
{
    int c;
    // O loop remove tods os caracteres ate encontrar uma quebra de linha ou  final do arquivo.
    while ((c = getchar()) != '\n' && c != EOF);
}


int menuAtendimento(){
    int opcao;
    int valor;
    float soma;
    char arquivo[] = {"Atendimentos"};
    Atendimento *resposta;
    Lista listaAtendimentos;

    carregar_lista(&listaAtendimentos,arquivo);
    controle(listaAtendimentos);
    do {
        printf("$$$$$$$$$$$$$$ ATENDIMENTO $$$$$$$$$$$$$$\n");
        printf("           DIGITE SUA OPCAO\n");
        printf("0. VOLTAR\n");
        printf("1. INSERIR NOVO ATENDIMENTO\n");
        printf("2. MOSTRAR TODOS OS ATENDIMENTOS\n");
        printf("3. EXCLUIR ATENDIMENTO\n");
        printf("4. CHECAR DADOS PELO CODIGO DO PACIENTE\n");
        printf("5. CHECAR DADOS PELO CODIGO DO ATENDIMENTO\n");
        printf("6. ALTERAR ATENDIMENTO\n");
        printf("7. MOSTRAR SOMA DAS CONSULTAS PAGAS POR UM PACIENTE\n");
        printf("8. SALVAR ALTERAÇOES\n");
        printf("9. MOSTRAR ATENDIMENTOS ORDENADOS POR DATA\n");
        printf("10. MOSTRAR A SOMA DAS CONSULTAS PAGAS PARA OS ATENDIMENTOS DE UMA DETERMINADA DATA\n");
        printf("11. MOSTRAR A SOMA DAS CONSULTAS PAGAS DENTRO DE UM INTERVALO DE DATAS\n");
        printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
        scanf("%d",&opcao);
        switch (opcao) {
            case VOLTAR:
                printf("\n\tDESEJA SALVAR AS ALTERACOES REALIZADAS?\n");
                printf("\n\t1 - SIM\n\t2 - NAO\n");
                scanf("%d",&valor);
                while(1){
                    if(valor == 1 || valor == 2)
                        break;
                    scanf("%d",&valor);
                    limparbuffer();
                }
                if(valor == 1) {
                    salvar(&listaAtendimentos, arquivo);
                }

                printf("\n\tSAINDO...\n");
                break;


            case INSERIR_ATENDIMENTO:
                valor = inserirAtendimento(&listaAtendimentos);
                if(valor == 1)
                    printf("\nO CODIGO DE ATENDIMENTO JA EXISTE\n");
                else if(valor == 2)
                    printf("\nA CONSULTA JA FOI MARCADA!\n");
                else
                    printf("\n\tATENDIMENTO INSERIDO COM SUCESSO!\n");

                break;

            case  LISTAR_ATENDIMENTOS:
                listarAtendimentos(listaAtendimentos);
                break;

            case REMOVER_ATENDIMENTO:
                printf("Insira o codigo do atendimento que sera removido:\n");
                scanf("%d",&valor);
                limparbuffer();
                resposta = ExcluirAtendimento(&listaAtendimentos,valor);
                if(resposta){
                    resposta->alterado = 3;
                    printf("\nAtendimento removido: %d\n",resposta->codigoA);
                    free(resposta);
                    salvar(&listaAtendimentos,arquivo);
                }
                else{
                    printf("Codigo de atendimento inexistente!\n");
                }
                break;

            case MOSTRAR_ATENDIMENTOS_PACIENTE:
                printf("Insira o codigo do paciente que sera pesquisado:\n");
                scanf("%d",&valor);
                imprimir_por_codigoP(&listaAtendimentos,valor);
                break;

            case MOSTRAR_DADOS_ATENDIMENTO:
                printf("Insira o codigo do atendimento que sera pesquisado:\n");
                scanf("%d",&valor);
                imprimir_por_codigoA(&listaAtendimentos,valor);
                break;

            case ALTERAR_ATENDIMENTO:
                printf("Insira o codigo do atendimento que sera alterado:\n");
                scanf("%d",&valor);
                resposta = alterarAtendimento(&listaAtendimentos,valor);
                if(resposta){

                    printf("\nALTERAÇOES REALIZADAS COM SUCESSO!\n");
                }
                else{
                    printf("\nCODIGO DE ATENDIMENTO NAO ENCONTRADO!\n");

                }
                break;

            case SOMA_CONSULTAS_PAGAS:
                printf("DIGITE O CODIGO DO PACIENTE:\n");
                scanf("%d",&valor);
                Soma_precoConsultasP(&listaAtendimentos,valor);
                break;

            case SALVAR_ALTERACOES:
                salvar(&listaAtendimentos,arquivo);
                printf("\n\tALTERACOES SALVAS!\n");
                break;

            case ORDENAR_POR_DATA:
                imprimirPorOrdemData(&listaAtendimentos);
                break;

            case SOMAR_PRECO_POR_DATA:
                soma =  soma_Preco_Por_Data(&listaAtendimentos);
                if(soma){
                    printf("\n\tSOMA DAS CONSULTAS: $%.2f\n",soma);
                }
                printf("\nNENHUMA CONSULTA FOI REALIZADA NESSA DATA\n");
                break;

            case SOMA_CONSULTAS_EM_INTERVALO:
                soma_consultas_em_intervalo(&listaAtendimentos);
                break;

            default:
                printf("\nopcao invalida!\n");
                break;

        }
    }while(opcao != 0);


    return 0;
}


int inserirAtendimento(Lista *lista){
    Atendimento *aux,  *novo = malloc(sizeof(Atendimento));
    int cod;
    int retorno;
    if(novo){
        printf("INFORME OS DADOS DO ATENDIMENTO:\n");
        cod = gerador();
        retorno = verifica_CodA(cod,lista);
        if(retorno){
            return retorno;
        }
        printf("\nCODIGO DO PACIENTE:\n");
        scanf("%d",&novo ->codigoP);
        limparbuffer();
        printf("\nTIPO DE ATENDIMENTO:\n");
        inserir_tipo(novo);
        printf("\nSTATUS DE ATENDIMENTO:\n");
        inserir_status(novo);
        printf("\nPRECO DO ATENDIMENTO:\n");
        scanf("%f",&novo -> preco);
        limparbuffer();

        time_t rawtime;
        //Struct para armazenar a data do atendimento
        struct tm data_atendimento_tm = {0};
        printf("\nDATA DE ATENDIMENTO(DD/MM/AAAA):\n");
        scanf("%d/%d/%d",&data_atendimento_tm.tm_mday,&data_atendimento_tm.tm_mon,&data_atendimento_tm.tm_year);
        limparbuffer();
        data_atendimento_tm.tm_mon--; // Ajuste do mes para começar do zero (janeiro é zero)
        data_atendimento_tm.tm_year -= 1900; // Ajuste do ano para o formato correto

        //converte a data do atendimento para time_t
        rawtime = mktime(&data_atendimento_tm);
        novo->data_atendimentos = rawtime; //Armazena a data do atendimento como time_t
        retorno = consultaMarcadaNaData(lista,novo->codigoP,novo->data_atendimentos);
        if(retorno){
            return retorno;
        }
        novo->codigoA = cod;
        printf("\nCODIGO DO ATENDIMENTO:  %d\n",novo->codigoA);


        // É o primeiro?
        if(lista->inicio == NULL){
            lista->inicio = novo;
            novo->proximo = NULL;
        }
        else{
            aux = lista->inicio;
            while(aux -> proximo) {
                aux = aux->proximo;
            }
            aux ->proximo = novo;
            novo->proximo = NULL;

        }
        lista->tam++;
    }

    else{
        printf("Erro ao alocar memoria!");
        exit(1);
    }

    return retorno;
}


void listarAtendimentos(Lista list) {
    int i = 1;
    Atendimento *lista = list.inicio;

    printf("\nAtendimentos cadastrados:\n");
    printf("+---------------------------------------------------------------------------------------------+\n");
    printf("| No. | Codigo Atendimento | Codigo Paciente |   Tipo   |    Status    |   Preco   |    Data    |\n");
    printf("+---------------------------------------------------------------------------------------------+\n");

    while (lista) {
        struct tm *info_tempo;
        info_tempo = localtime(&lista->data_atendimentos);

        printf("| %-3d | %-18d | %-15d | %-8s | %-12s | $%-9.2f | %.2d/%.2d/%d |\n",
               i, lista->codigoA, lista->codigoP, lista->tipo, lista->status, lista->preco,
               info_tempo->tm_mday, info_tempo->tm_mon + 1, info_tempo->tm_year + 1900);

        lista = lista->proximo;
        ++i;
    }

    printf("+---------------------------------------------------------------------------------------------+\n");
}


Atendimento* ExcluirAtendimento(Lista *lista,int codA){
    Atendimento *aux, *remover = NULL;

    if(lista ->inicio){
        if( lista->inicio->codigoA == codA ){
            remover = lista->inicio;
            lista->inicio = remover ->proximo;
            lista->tam--;
        }
        else{
            aux = lista->inicio;
            while (aux ->proximo && aux ->proximo ->codigoA != codA) {
                aux = aux->proximo;
            }
            if(aux ->proximo){
                remover = aux ->proximo;
                aux ->proximo = remover ->proximo;
                lista->tam--;
            }
            else{
                printf("\nCODIGO DE ATENDIMENTO NAO ENCONTRADO!\n");
            }

        }

    }
    return remover;
}


void imprimir_por_codigoP(Lista *lista, int cod) {
    Atendimento *aux;
    aux = lista->inicio;
    int encontrado = 0;

    printf("\nAtendimentos do paciente com código %d:\n", cod);
    printf("+---------------------------------------------------------------------------------------------+\n");
    printf("| Codigo Atendimento | Codigo Paciente |   Tipo   |    Status    |   Preco   |    Data    |\n");
    printf("+---------------------------------------------------------------------------------------------+\n");

    while (aux) {
        if (aux->codigoP == cod) {
            struct tm *info_tempo;
            info_tempo = localtime(&aux->data_atendimentos);

            printf("| %-18d | %-15d | %-8s | %-12s | $%-9.2f | %.2d/%.2d/%d |\n",
                   aux->codigoA, aux->codigoP, aux->tipo, aux->status, aux->preco,
                   info_tempo->tm_mday, info_tempo->tm_mon + 1, info_tempo->tm_year + 1900);

            encontrado = 1;
        }
        aux = aux->proximo;
    }

    printf("+---------------------------------------------------------------------------------------------+\n");

    if (!encontrado) {
        printf("Nenhum atendimento encontrado para o paciente com código %d.\n", cod);
    }
}


void imprimir_por_codigoA(Lista *lista, int cod) {
    Atendimento *aux;
    aux = lista->inicio;
    int encontrado = 0;

    printf("\nAtendimentos com código %d:\n", cod);
    printf("+---------------------------------------------------------------------------------------------+\n");
    printf("| Codigo Atendimento | Codigo Paciente |   Tipo   |    Status    |   Preco   |    Data    |\n");
    printf("+---------------------------------------------------------------------------------------------+\n");

    while (aux) {
        if (aux->codigoA == cod) {
            struct tm *info_tempo;
            info_tempo = localtime(&aux->data_atendimentos);

            printf("| %-18d | %-15d | %-8s | %-12s | $%-9.2f | %.2d/%.2d/%d |\n",
                   aux->codigoA, aux->codigoP, aux->tipo, aux->status, aux->preco,
                   info_tempo->tm_mday, info_tempo->tm_mon + 1, info_tempo->tm_year + 1900);

            encontrado = 1;
            break;
        }
        aux = aux->proximo;
    }

    printf("+---------------------------------------------------------------------------------------------+\n");

    if (!encontrado) {
        printf("Nenhum atendimento encontrado com o código %d.\n", cod);
    }
}


Atendimento* alterarAtendimento(Lista *lista,int codA){
    Atendimento *aux, *alterar = NULL;
    int dia,mes,ano;
    int opcao;
    if(lista ->inicio) {
        if (lista->inicio->codigoA == codA) {
            alterar = lista->inicio;
        }
        else {
            aux = lista->inicio;
            while (aux->proximo && aux->proximo->codigoA != codA ) {
                aux = aux->proximo;
            }
            if (aux->proximo) {
                alterar = aux ->proximo;
            }
        }
        if (alterar) {
            do {
                printf("\n\t0 - Sair\n\t1 - ALTERAR STATUS\n\t2 - ALTERAR TIPO\n\t3 - ALTERAR DATA\n\t4 - ALTERAR PRECO\n");
                scanf("%d", &opcao);
                limparbuffer();
                if( (opcao > 0) && (opcao < 5) )
                    alterar->alterado = 1;

                switch (opcao) {
                    case ALTERAR_STATUS:
                        inserir_status(alterar);
                        break;
                    case ALTERAR_TIPO:
                        inserir_tipo(alterar);
                        break;
                    case ALTERAR_DATA:
                        //Solicitar ao usuario a nova data
                        printf("INSIRA A NOVA DATA:\n");
                        scanf("%d/%d/%d",&dia,&mes,&ano);
                        limparbuffer();
                        //Cria uma estrutura tm para reopresentar a nova data
                        struct  tm data_nova = {0};
                        data_nova.tm_year = ano - 1900;
                        data_nova.tm_mon = mes - 1;
                        data_nova.tm_mday = dia;
                        //Converter a struct tm para time_t
                        time_t novo_tempo = mktime(&data_nova);
                        //Atualizar o campo data_atendimento
                        alterar->data_atendimentos = novo_tempo;
                        break;
                    case ALTERAR_PRECO:
                        printf("Insira o preco novo:\n");
                        scanf("%f", &alterar->preco);
                        limparbuffer();
                        break;
                    case SAIR_ALTERAR:
                        break;

                    default:
                        printf("\nOPCAO INVALIDA!\n");

                        break;
                }
            } while (opcao);

        }
    }

    return alterar;

}

void Soma_precoConsultasP(Lista *lista,int cod){
    float soma = 0;
    Atendimento *aux = lista->inicio;
    printf("\nPaciente com código %d:\n", cod);
    printf("+---------------------------------------------------------------------------------------------+\n");
    printf("| Codigo Atendimento | Codigo Paciente |   Tipo   |    Status    |   Preco   |    Data    |\n");
    printf("+---------------------------------------------------------------------------------------------+\n");
    while(aux){
        if(aux->codigoP == cod){
            struct tm *info_tempo;
            info_tempo = localtime(&aux->data_atendimentos);
            printf("| %-18d | %-15d | %-8s | %-12s | $%-9.2f | %.2d/%.2d/%d |\n",aux->codigoA,aux->codigoP,aux->tipo,aux->status,aux->preco,info_tempo->tm_mday,info_tempo->tm_mon + 1,info_tempo->tm_year + 1900);
            soma += aux->preco;
        }
        aux = aux->proximo;

    }
    printf("+---------------------------------------------------------------------------------------------+\n");
    if(soma) {
        printf("\nCODIGO DO PACIENTE: %d\t SOMA DAS CONSULTAS PAGAS: $%.2f\n ", cod, soma);
    }
    else{
        printf("CODIGO NAO ENCONTRADO!\n");
    }


}

void controle(Lista list){
    Atendimento *lista = list.inicio;
    while (lista) {
        lista->alterado = 0;
        lista =lista->proximo;
    }
}

void salvar(Lista *lista, char arq[]) {
    FILE *file = fopen(arq, "wb");
    if (file) {
        Atendimento *salvar = lista->inicio;
        while (salvar) {
            if (salvar->alterado == 1) {
                fseek(file, ftell(file), SEEK_SET); // Posiciona o cursor para sobrescrever o registro
                fwrite(salvar, sizeof(Atendimento), 1, file);
            }
            else if (salvar->alterado != 3) {
                fseek(file, 0, SEEK_END); // Posiciona o cursor no final do arquivo para novos registros
                fwrite(salvar, sizeof(Atendimento), 1, file);
            }
            salvar = salvar->proximo;
        }
        fclose(file);
    } else {
        printf("\nERRO AO SALVAR O ARQUIVO\n");
        exit(1);
    }
}




void carregar_lista(Lista *lista, char arq[]) {
    Atendimento atnd;
    FILE *file = fopen(arq, "rb+");

    if(!file){
        printf("\nO ARQUIVO PODE ESTAR SENDO ABERTO PELA PRIMEIRA VEZ\n");
        file = fopen(arq,"wb");
        if(!file){
            printf("\nERRO AO ABRIR O ARQUIVO\n");
            exit(1);
        }

    }
    lista->inicio = NULL;
    lista->tam = 0;
    Atendimento *aux = NULL;
    while (fread(&atnd, sizeof(Atendimento), 1, file) == 1) {
        Atendimento *novo = (Atendimento *)malloc(sizeof(Atendimento));
        if (!novo) {
            printf("\nERRO DE ALOCACAO DE MEMORIA\n");
            exit(1);
        }
        memcpy(novo, &atnd, sizeof(Atendimento));
        novo->proximo = NULL;

        if (lista->inicio == NULL) {
            lista->inicio = novo;
            aux = novo;
        }
        else {

            aux->proximo = novo;
            aux = aux->proximo;
        }
        lista->tam++;

    }
    fclose(file);
}

int verifica_CodA(int codA,Lista *lista){
    Atendimento *verificador = lista->inicio;
    while (verificador){
        if(verificador->codigoA == codA)
            return 1;
        verificador = verificador->proximo;
    }

    return 0;
}
int gerador(){
    int cod;
    srand(time(NULL));
    cod = rand()%10000;
    return cod;
}

void inserir_tipo(Atendimento *atendimento){
    int opcao;
    printf("\n\t1 - CONSULTA\n\t2 - RETORNO\n");
    scanf("%d",&opcao);
    limparbuffer();
    while(1){
        if(opcao == 1 || opcao == 2){
            break;
        }
        scanf("%d",&opcao);
        limparbuffer();
    }
    switch (opcao) {
        case CONSULTA:
            strcpy(atendimento->tipo,"Consulta");
            break;
        case RETORNO:
            strcpy(atendimento->tipo,"Retorno");
            break;
    }
}
void inserir_status(Atendimento *atendimento) {
    int escolha;
    printf("\n\t1 - AGENDADO\n\t2 - ESPERANDO\n\t3 - EM ATENDIMENTO\n\t4 - ATENDIDO\n");
    scanf("%d", &escolha);
    limparbuffer();
    while (1) {
        if (escolha == 1 || escolha == 2 || escolha == 3 || escolha == 4) {
            break;
        }
        scanf("%d", &escolha);
        limparbuffer();
    }

    switch (escolha) {
        case AGENDADO:
            strcpy(atendimento->status, "Agendado");
            break;
        case ESPERANDO:
            strcpy(atendimento->status, "Esperando");
            break;
        case EM_ATENDIMENTO:
            strcpy(atendimento->status, "Em atendimento");
            break;
        case ATENDIDO:
            strcpy(atendimento->status, "Atendido");
            break;
    }
}
int consultaMarcadaNaData(Lista *lista,int codPaciente,time_t dataConsulta){
    Atendimento *aux = lista->inicio;
    while(aux){
        if(aux->codigoP == codPaciente && aux->data_atendimentos == dataConsulta){
            return 2;
        }
        aux = aux->proximo;
    }
    return 0;
}

void imprimirPorOrdemData(Lista *lista) {
    //Criar um array para armazenar os ponteiros para os atendimentos
    Atendimento **atendimentos = (Atendimento **) malloc(lista->tam * sizeof(Atendimento *));

    if(atendimentos == NULL){
        printf("ERRO AO ALOCAR MEMORIA\n");
        exit(1);
    }
    // preencher o array com os ponteiros para atendimento
    Atendimento *aux = lista->inicio;
    int i = 0;
    while (aux) {
        atendimentos[i] = aux;
        aux = aux->proximo;
        i++;
    }

    //ordenar usando bubble sort
    for (int j = 0; j < lista->tam - 1; ++j) {
        for (int k = 0; k < lista->tam - j - 1; ++k) {
            if (difftime(atendimentos[k]->data_atendimentos, atendimentos[k + 1]->data_atendimentos) > 0) {
                Atendimento *temp = atendimentos[k];
                atendimentos[k] = atendimentos[k + 1];
                atendimentos[k + 1] = temp;
            }
        }
    }

    //imprimir os atendimentos ordenados por data
    printf("\n\tATENDIMENTOS POR ORDEM DE DATA:\t\t tam: %d \n",lista->tam);
    printf("+---------------------------------------------------------------------------------------------+\n");
    printf("| Codigo Atendimento | Codigo Paciente |   Tipo   |    Status    |   Preco   |    Data    |\n");
    printf("+---------------------------------------------------------------------------------------------+\n");
    for (int l = 0; l < lista->tam; ++l) {
        struct tm *info_tempo;
        info_tempo = localtime(&atendimentos[l]->data_atendimentos);

        printf("| %-18d | %-15d | %-8s | %-12s | $%-9.2f | %.2d/%.2d/%d |\n",
               atendimentos[l]->codigoA, atendimentos[l]->codigoP, atendimentos[l]->tipo, atendimentos[l]->status,
               atendimentos[l]->preco, info_tempo->tm_mday, info_tempo->tm_mon + 1, info_tempo->tm_year + 1900);


    }
    printf("-----------------------------------------------------------------------------------------------\n");
    free(atendimentos);
}

float soma_Preco_Por_Data(Lista *lista){
    int dia,mes,ano;
    float soma = 0.0f;
    printf("INFORME A DATA PARA SOMAR AS CONSULTAS (DD/MM/AAAA):\n");
    scanf("%d/%d/%d",&dia,&mes,&ano);
    limparbuffer();


    //Cria uma estrutura tm para representar a dat informada
    struct tm dataProcurada = {0};
    dataProcurada.tm_year = ano - 1900;
    dataProcurada.tm_mon = mes - 1;
    dataProcurada.tm_mday = dia;

    //converte a struct tm para time_t
    time_t dataInformada = mktime(&dataProcurada);
    Atendimento *aux = lista->inicio;
    printf("\n\tATENDIMENTOS REALIZADOS EM %.2d/%.2d/%d\n",dia,mes,ano);
    printf("| Codigo Atendimento | Codigo Paciente |   Tipo   |    Status    |   Preco   |    Data    |\n");
    printf("+---------------------------------------------------------------------------------------------+\n");
    while(aux){
        //Verifica se a data do atendimento é igual a data informada

        if( difftime(aux->data_atendimentos,dataInformada) == 0){
            soma += aux->preco;
            //Converter o time_tpara uma estrutura de tempo(struct tm)
            struct tm *info_tempo;
            info_tempo = localtime(&aux->data_atendimentos);
            printf("| %-18d | %-15d | %-8s | %-12s | $%-9.2f | %.2d/%.2d/%d |\n",
                   aux->codigoA, aux->codigoP, aux->tipo, aux->status, aux->preco,info_tempo->tm_mday,info_tempo->tm_mon + 1,info_tempo->tm_year + 1900);
            printf("\n------------------------------------------------------------------------------------------\n");

        }
        aux = aux->proximo;
    }
    return soma;
}

void soma_consultas_em_intervalo(Lista *lista){
    int diaI, mesI, anoI, diaF, mesF, anoF, encontrados = 0;
    float soma = 0.0f;
    printf("\n\tINSIRA A DATA INICIAL DO INTERVALO (DD/MM/AAAA):\n");
    scanf("%d/%d/%d",&diaI,&mesI,&anoI);
    limparbuffer();
    //Cria uma estrutura tm para representar a data informada
    struct tm dataI = {0};
    dataI.tm_year = anoI - 1900;
    dataI.tm_mon = mesI - 1;
    dataI.tm_mday = diaI;
    //Converte as structs para time_t
    time_t data_inicial = mktime(&dataI);

    printf("\n\tINSIRA A DATA FINAL DO INTERVALO (DD/MM/AAAA):\n");
    scanf("%d/%d/%d",&diaF,&mesF,&anoF);
    limparbuffer();
    //Cria uma estrutura tm para representar a data informada
    struct tm dataF = {0};
    dataF.tm_year = anoF - 1900;
    dataF.tm_mon = mesF - 1;
    dataF.tm_mday = diaF;
    //Converte as structs para time_t
    time_t data_final = mktime(&dataF);

    Atendimento  *aux = lista->inicio;
    printf("\n\tATENDIMENTOS NO INTERVALO:\n");
    printf("| Codigo Atendimento | Codigo Paciente |   Tipo   |    Status    |   Preco   |    Data    |\n");
    printf("+---------------------------------------------------------------------------------------------+\n");
    while (aux){
        if(difftime(aux->data_atendimentos,data_inicial) >= 0 && difftime(data_final,aux->data_atendimentos) >= 0  ){
            struct tm *info_tempo;
            info_tempo = localtime(&aux->data_atendimentos);
            printf("| %-18d | %-15d | %-8s | %-12s | $%-9.2f | %.2d/%.2d/%d |\n",
                   aux->codigoA, aux->codigoP, aux->tipo, aux->status, aux->preco,info_tempo->tm_mday,info_tempo->tm_mon + 1,info_tempo->tm_year + 1900);
            soma += aux->preco;
            encontrados++;

        }
        aux = aux->proximo;
    }
    printf("\n------------------------------------------------------------------------------------------\n");

    if(encontrados){
        printf("\nSOMA DOS PRECOS DAS CONSULTAS DENTRO DO INTERVALO: %.2f\n",soma);
    }
    else {
        printf("\nNENHUM ATENDIMENTO ENCONTRADO DENTRO DO INTERVALO INFORMADO!\n");
    }

    printf("\n------------------------------------------------------------------------------------------\n");
}


