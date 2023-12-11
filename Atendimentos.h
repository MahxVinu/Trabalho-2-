#ifndef TRABALHO_2ETAPA_ATENDIMENTO_H
#define TRABALHO_2ETAPA_ATENDIMENTO_H

#include <sys/select.h>

typedef enum {
    VOLTAR,
    INSERIR_ATENDIMENTO,
    LISTAR_ATENDIMENTOS,
    REMOVER_ATENDIMENTO,
    MOSTRAR_ATENDIMENTOS_PACIENTE,
    MOSTRAR_DADOS_ATENDIMENTO,
    ALTERAR_ATENDIMENTO,
    SOMA_CONSULTAS_PAGAS,
    SALVAR_ALTERACOES,
    ORDENAR_POR_DATA,
    SOMAR_PRECO_POR_DATA,
    SOMA_CONSULTAS_EM_INTERVALO
} OpcoesMenu;

typedef  enum {
    CONSULTA = 1,
    RETORNO
}Tipo_Atendimento;
typedef enum{
    AGENDADO = 1,
    ESPERANDO,
    EM_ATENDIMENTO,
    ATENDIDO
}Status_Atendimento;

typedef enum{
    SAIR_ALTERAR,
    ALTERAR_STATUS,
    ALTERAR_TIPO,
    ALTERAR_DATA,
    ALTERAR_PRECO
}Alterar_opcoes;
typedef struct Atendimento{
    int codigoA;
    int codigoP;
    char tipo[20];
    char status[20];
    float preco;
    time_t data_atendimentos;
    int alterado;
    struct Atendimento *proximo;
}Atendimento;

typedef struct{
    Atendimento *inicio;
    int tam;
}Lista;

int menuAtendimento();
int inserirAtendimento(Lista *lista);
void listarAtendimentos(Lista list);
Atendimento* ExcluirAtendimento(Lista *lista,int codA);
void imprimir_por_codigoP(Lista *lista,int cod);
void imprimir_por_codigoA(Lista *lista,int cod);
Atendimento* alterarAtendimento(Lista *lista,int codA);
void Soma_precoConsultasP(Lista *lista,int cod);
void controle(Lista list);
void salvar(Lista *lista,char arq[]);
void carregar_lista(Lista *lista, char arq[]);
int verifica_CodA(int codA,Lista *lista);
int gerador();
void inserir_tipo(Atendimento *atendimento);
void inserir_status(Atendimento *atendimento);
int consultaMarcadaNaData(Lista *lista,int codPaciente,time_t dataConsulta);
void imprimirPorOrdemData(Lista *lista);
float soma_Preco_Por_Data(Lista *lista);
void soma_consultas_em_intervalo(Lista *lista);
void limparbuffer(void);
#endif //TRABALHO_2ETAPA_ATENDIMENTO_H
