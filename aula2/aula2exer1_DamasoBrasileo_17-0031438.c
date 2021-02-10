#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char placa[8];
    char chassi[17];    
} Automovel;

typedef struct {
    char nome[30];
    char cpf[11];
    int num_carros;
    char carros[MAX][7];
} Pessoa;

FILE *verificador;
Pessoa verificada;

Pessoa grupo[100];

int compararCPF (const void *x, const void *y){
    return strcmp(((Pessoa *)x)->cpf, ((Pessoa *)y)->cpf);
}

int compararNome (const void *x, const void *y){
    return strcmp(((Pessoa *)x)->nome, ((Pessoa *)y)->nome);
}

int cpfExiste(char vetor[11]){
    verificador = fopen("base_pessoas.txt", "r");
    while(fread(&verificada, sizeof(Pessoa), 1, verificador)){
        if(strcmp(vetor, verificada.cpf) == 0){
            return 1;
        }
    }
    fclose(verificador);
    return 0;
}

void ordenarPorCPF() {
    int i = 0;
    verificador = fopen("base_pessoas.txt", "r");
    while(fread(&grupo[i], sizeof(Pessoa), 1, verificador)){
        i++;
    }

    qsort(grupo, i, sizeof(Pessoa), compararCPF);
    fclose(verificador);

    verificador = fopen("base_pessoas.txt", "w");
    int tam = 0;
    while(tam < i){
        fwrite(&grupo[tam], 1, sizeof(Pessoa), verificador);
        tam++;
    }

    fclose(verificador);
}

void ordenarPorNome() {
    int i = 0;
    verificador = fopen("base_pessoas.txt", "r");
    while(fread(&grupo[i], sizeof(Pessoa), 1, verificador)){
        i++;
    }

    qsort(grupo, i, sizeof(Pessoa), compararCPF);
    fclose(verificador);

    verificador = fopen("base_pessoas.txt", "w");
    int tam = 0;
    while(tam < i){
        fwrite(&grupo[tam], 1, sizeof(Pessoa), verificador);
        tam++;
    }

    fclose(verificador);
}

Pessoa pessoa;
Automovel carro;

int main() {

    FILE *arqPessoas;
    FILE *arqCarros;
    
    int opc;
    int id;
    int j = 0;
    int k = 0;
    int indice = 0;
    char verificarCPF[11];
    int verificarCarro;

    int num_pessoas;

    do {
        printf("Escolha uma das opções abaixo:\n");
        printf("1 - Cadastrar nova pessoa e seus automoveis\n");
        printf("2 - Listar pessoas e automoveis ordenados por CPF.\n");
        printf("3 - Listar pessoas e automoveis ordenados por nome.\n");
        printf("4 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opc);

        switch(opc){
            case 1:
                printf("Digite o numeros de pessoas para serem cadastradas: \n");
                scanf("%d", &num_pessoas);
                for(int k = 0; k < num_pessoas; k++){
                    arqPessoas = fopen("base_pessoas.txt", "a");
                    arqCarros = fopen("base_carros.txt", "a");

                    printf("Digite o nome de uma pessoa: ");
                    scanf(" %[^\n]", pessoa.nome);
                    printf("Digite o CPF de uma pessoa: ");
                    scanf(" %s", verificarCPF);

                    while(strlen(verificarCPF) != 11){
                        printf("CPF não tem 11 dígitos, digite CPF válido.\n");
                        scanf(" %s", verificarCPF);
                    }

                    while(cpfExiste(verificarCPF)){
                        printf("Já existe uma pessoa com esse CPF cadastrada. Digite outro CPF válido!\n");
                        scanf(" %s", verificarCPF);
                    }

                    strcpy(pessoa.cpf, verificarCPF);

                    printf("Quantos carros essa pessoa tem? ");
                    scanf("%d", &verificarCarro);

                    while(verificarCarro == 0){
                        printf("Você está em uma plataforma para cadastrar donos de carros. É impossível cadastrar usuários sem carros, peço que digite algum número maior que 0\n");
                        scanf("%d", &verificarCarro);
                    }

                    pessoa.num_carros = verificarCarro;

                    for(int j = 0; j < pessoa.num_carros; j++){
                        printf("Digite a placa do carro: ");
                        scanf(" %[^\n]", carro.placa);
                        strcpy(pessoa.carros[j], carro.placa);

                        printf("Digite o numero do chassi do carro: ");
                        scanf(" %[^\n]", carro.chassi);
                        
                        fwrite(&carro,1, sizeof(Automovel), arqCarros);
                    }
                    fwrite(&pessoa,1, sizeof(Pessoa), arqPessoas);

                    fclose(arqPessoas);
                    fclose(arqCarros);
                }
                printf("\n\nPessoa cadastrada\n\n");
                break;
            case 2:
                arqPessoas = fopen("base_pessoas.txt", "r");
                arqCarros = fopen("base_carros.txt", "r");

                ordenarPorCPF();

                printf("Pessoas cadastradas: \n");
                while(fread(&pessoa, sizeof(Pessoa), 1, arqPessoas)){
                    printf("**********************\n");
                    printf("Nome: %s - CPF: %s\nCarros:\n", pessoa.nome, pessoa.cpf);
                    for(int j = 0; j < pessoa.num_carros; j++){
                        printf("-> %s\n", pessoa.carros[j]);
                    }
                    printf("**********************\n");
                }

                printf("Carros cadastrados: \n");
                while(fread(&carro, sizeof(Automovel), 1, arqCarros)){
                    printf("**********************\n");
                    printf("Placa: %s\nChassi: %s\n", carro.placa, carro.chassi);
                }
                printf("**********************\n");
                
                fclose(arqPessoas);
                fclose(arqCarros);

                break;
            case 3:
                arqPessoas = fopen("base_pessoas.txt", "r");
                arqCarros = fopen("base_carros.txt", "r");

                ordenarPorNome();

                printf("Pessoas cadastradas: \n");
                while(fread(&pessoa, sizeof(Pessoa), 1, arqPessoas)){
                    printf("**********************\n");
                    printf("Nome: %s - CPF: %s\nCarros:\n", pessoa.nome, pessoa.cpf);
                    for(int j = 0; j < pessoa.num_carros; j++){
                        printf("-> %s\n", pessoa.carros[j]);
                    }
                    printf("**********************\n");
                }

                printf("Carros cadastrados: \n");
                while(fread(&carro, sizeof(Automovel), 1, arqCarros)){
                    printf("**********************\n");
                    printf("Placa: %s\nChassi: %s\n", carro.placa, carro.chassi);
                }
                printf("**********************\n");
                
                fclose(arqPessoas);
                fclose(arqCarros);

                break;

        }
    } while (opc != 4);
    return 0;
}