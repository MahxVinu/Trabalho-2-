//
// Created by Marcos Vinicius on 10/12/2023.
//

#ifndef S1_1A_ETAPA_IP_PACIENTES_H
#define S1_1A_ETAPA_IP_PACIENTES_H


#include <time.h>
#include <stdlib.h>

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

// Função de comparação para qsort
int compararPacientes(const void *a, const void *b);


// Função para converter uma string para maiúsculas
void converterParaMaiusculas(char *str);

// Função pra liberar memoria usada pelo paciente
void liberarPaciente(struct paciente *p);

// Função pra liberar a memoria de todos os pacientes no vetor
void liberarMemoria(struct VetorDinamico *pacientes);

void inicializarVetor(struct VetorDinamico *vetor, int capacidadeInicial);

void adicionarElemento(struct VetorDinamico *vetor, struct paciente paciente);

// Função para ler a data de nascimento
void lerDataNascimento(struct tm *dataNascimento);

// Insere o paciente
struct VetorDinamico *inserir(struct VetorDinamico *pacientes);

// Função para buscar um paciente pelo CPF
int buscarPacientePorCPF(const struct VetorDinamico *pacientes, const char *cpf);

// Enumeração para representar as opções de alteração
enum OpcoesAlteracao
{
    ALTERAR_NOME = 1,
    ALTERAR_RG,
    ALTERAR_TIPO_SANGUINEO,
    ALTERAR_FATOR_RH,
    ALTERAR_ENDERECO,
    ALTERAR_DATA_NASCIMENTO,
    CANCELAR_ALTERACAO
};

// Função para alterar dados de um paciente
void alterarPaciente(struct VetorDinamico *pacientes);

// Função modificada para trabalhar com VetorDinamico
void imprimir_pacientes(const struct VetorDinamico *pacientes);

// Função para salvar os dados dos pacientes em um arquivo texto
void salvarEmArquivo(const struct VetorDinamico *pacientes, const char *nomeArquivo);

/// Função para carregar dados dos pacientes de um arquivo texto
void carregarDeArquivo(struct VetorDinamico *pacientes, const char *nomeArquivo);

// Função para excluir um paciente com base no CPF
void excluirPaciente(struct VetorDinamico *pacientes, const char *cpf, int indice);

// Função para imprimir pacientes com um determinado tipo sanguíneo
void imprimirPacientesPorTipoSanguineo(const struct VetorDinamico *pacientes, const char *tipoSanguineo);


// Função para imprimir pacientes com um determinado tipo sanguíneo
void imprimirPacientesPorCodigo(const struct VetorDinamico *pacientes, const char *codigo);

// Função modificada para ordenar pacientes antes de imprimir
void imprimir_ordem(const struct VetorDinamico *pacientes);

char* lerCPF();

void alterarCPF(struct VetorDinamico *pacientes, int indice);
#endif //S1_1A_ETAPA_IP_PACIENTES_H
