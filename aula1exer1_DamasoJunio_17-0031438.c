#include <stdio.h>
#include <stdlib.h>

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
    Automovel carros[MAX];
} Pessoa;

Pessoa pessoas[MAX];

int main() {

    int opc;
    int id;
    int i = 0;
    int j = 0;
    int k = 0;

    do {
        printf("Escolha uma das opções abaixo:\n");
        printf("1 - Cadastrar nova pessoa\n");
        printf("2 - Cadastrar automovel\n");
        printf("3 - Listar pessoas e automoveis\n");
        printf("4 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opc);

        switch(opc){
            case 1:
                pessoas[i].id = i; 
                printf("Digite o nome de uma pessoa: ");
                scanf("%s", pessoas[i].nome);
                printf("Digite o CPF de uma pessoa: ");
                scanf("%s", pessoas[i].cpf);
                pessoas[i].num_carros = 0;

                printf("\n\nPessoa cadastrada\n\n");
                i++;
                break;
            case 2:
                if(k == i){
                    printf("\n***************\n");
                    printf("Nao existem usuarios cadastrados");
                    printf("\n***************\n");
                    break;
                }

                for(int k = 0; k < i; k++){
                    printf("ID: %d - Nome: %s - CPF: %s\n", pessoas[k].id, pessoas[k].nome, pessoas[k].cpf);
                }
                
                printf("Selecione uma pessoa para cadastrar um carro: ");
                scanf("%d", &id);

                printf("Digite a placa do veículos: ");
                scanf("%s", pessoas[id].carros[pessoas[id].num_carros].placa);
                
                printf("Digite o chassi do veículos: ");
                scanf("%s", pessoas[id].carros[pessoas[id].num_carros].chassi);
                
                printf("\n\nCarro cadastrado\n\n");
                pessoas[id].num_carros++;
                break;
            case 3: 
                if(k == i){
                    printf("\n***************\n");
                    printf("Nao existem usuarios cadastrados");
                    printf("\n***************\n");
                    break;
                }
                else{
                    for(int k = 0; k < i; k++){
                        printf("ID: %d - Nome: %s - CPF: %s\n", pessoas[k].id, pessoas[k].nome, pessoas[k].cpf);
                        if(!pessoas[k].num_carros){
                            printf("\n***************\n");
                            printf("Nao existem carros cadastrados");
                            printf("\n***************\n");
                        }
                        else {
                            printf("\n***************\n");
                            printf("Veiculos: \n");
                            for(int j = 0; j < pessoas[k].num_carros; j++){
                                printf("Placa do carro: %s\n", pessoas[k].carros[j].placa);
                                printf("Chassi do carro: %s\n", pessoas[k].carros[j].chassi);
                                printf("----------------------\n");
                            }
                            printf("\n***************\n");
                        }
                    }
                }
            
                k = 0;
                j = 0;
                break;
        }
    } while (opc != 4);
    return 0;
}