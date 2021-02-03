#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char placa[8];
    char chassi[17];    
} Automovel;

typedef struct {
    int id;
    char nome[30];
    char cpf[11];
    int num_carros;
    char carros[MAX][7];
} Pessoa;

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

    int num_pessoas;

    do {
        printf("Escolha uma das opções abaixo:\n");
        printf("1 - Cadastrar nova pessoa e seus automoveis\n");
        printf("2 - Listar pessoas e automoveis\n");
        printf("3 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opc);

        switch(opc){
            case 1:
                printf("Numeros de pessoas para serem cadastradas: \n");
                scanf("%d", &num_pessoas);
                for(int k = 0; k < num_pessoas; k++){
                    pessoa.id = k;
                    arqPessoas = fopen("base_pessoas.txt", "a");
                    arqCarros = fopen("base_carros.txt", "a");

                    printf("Digite o nome de uma pessoa: ");
                    scanf(" %[^\n]", pessoa.nome);
                    printf("Digite o CPF de uma pessoa: ");
                    scanf(" %s", pessoa.cpf);

                    printf("Quantos carros essa pessoa tem? ");
                    scanf("%d", &pessoa.num_carros);

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
                printf("Pessoas cadastradas: \n");
                while(fread(&pessoa, sizeof(Pessoa), 1, arqPessoas)){
                    printf("**********************\n");
                    printf("ID: %d - Nome: %s - CPF: %s\nCarros:\n", pessoa.id, pessoa.nome, pessoa.cpf);
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
    } while (opc != 3);
    return 0;
}