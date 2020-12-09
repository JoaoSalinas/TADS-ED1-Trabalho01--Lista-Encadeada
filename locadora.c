#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "locadora.h"

float billing = 0;

 List* newList(){
     List* list = (List*) malloc(sizeof(List));

     if(!list){
         printf("Problema com a criacao da lista!\n");
         exit(0);
     }
     list->first = NULL;
     list->last = NULL;
     list->length = 0;

     return list;
 }

 Vehicle* newVehicle(){
     Vehicle *newVehicle = (Vehicle*) malloc(sizeof(Vehicle));

     if(!newVehicle){
         printf("Sem memoria disponivel!\n");
         exit(0);
     }

     printf("Codigo do veiculo: ");
     scanf("%d", &newVehicle->code);
     fflush(stdin);

     printf("\nInforme o modelo: ");
     scanf("%s", newVehicle->model);
     fflush(stdin);

     printf("\nInforme a placa: ");
     scanf("%s", newVehicle->board);
     fflush(stdin);

     printf("\nInforme o valor da diaria: ");
     scanf("%f", &newVehicle->dailyValue);
     fflush(stdin);

     return newVehicle;
 }

 int unshift(List *list , Vehicle *vehicle){

     if(list->first == NULL){
         list->last = vehicle;
     }else{
         vehicle->next = list->first;
     }
     list->first = vehicle;
     list->length++;

     printf("\nInserido com sucesso no inicio da lista!\n");
     pause();

     return list->first == vehicle ? 1 : 0;
 }

 int push(List *list, Vehicle *vehicle){

     vehicle->next = NULL;

     if(list->first == NULL){
        list->first = vehicle;
     } else{
        list->last->next = vehicle;
     }

     list->last = vehicle;
     list->length++;

    printf("\nInserido com sucesso no final da lista!\n");
    pause();

     return list->last == vehicle ? 1 : 0;
 }

 int splice(List *list, Vehicle *vehicle, int position){

    if (position > list->length){
        printf("Posicao invalida\n");
        return 0;
    }

    if(list->length == position){
        push(list, vehicle);
        return 1;
    }

    if(position == 0){
        unshift(list, vehicle);
        return 1;
    }

    Vehicle *tmp = list->first;

    int i;
    for (i = 0; i < position-1; i++){
        tmp = tmp->next;
    }

    Vehicle* next = tmp->next;
    vehicle->next = next;
    tmp->next = vehicle;

    printf("\nInserido com sucesso na posicao %d da lista!\n", position);
    pause();

    return 1;
 }

 Vehicle* shift(List *list){
    Vehicle *tmp = NULL;

    if(list->length == 0){
        printf("Lista Vazia!\n");
        return tmp;
    }

		if(list->length == 1){
			free(list->first);
			list->first = NULL;
			list->last = NULL;
		}else{
			tmp = list->first;
			list->first = list->first->next;
			free(tmp);
		}
			list->length--;

    printf("\nRemovido com sucesso no inicio da lista!\n");
    pause();

    return list->first;
 }

 Vehicle* pop(List *list){
    Vehicle *tmp = NULL;

    if(list->length == 0){
      printf("Lista Vazia!\n");
      return tmp;
    }

    if(list->length > 1){
        tmp = list->first;
        Vehicle *aux = list->first->next;
        while(aux->next != NULL){
            tmp = tmp->next;
        }
        free(aux);

        tmp->next = NULL;
        list->length--;

				if(list->length == 0){
					list->first = NULL;
					list->last = NULL;
				}

				printf("\nRemovido com sucesso no final da lista!\n");
    		pause();

        return tmp;
    }

    return tmp;
 }

 Vehicle* deleteVehicle(List *list, int position){
    Vehicle *tmp = NULL;

    if(position == 0){
        shift(list);
    }else if(position == list->length -1){
        pop(list);
    }

    if (position >= list->length){
        printf("\nPosicao invalida\n");
        return tmp;
    }

    if(list->length == 0){
      printf("\nLista Vazia!\n");
      return tmp;
    }

    tmp = getVehicle(list, position);

    Vehicle *deleting = tmp->next;

    tmp->next = deleting->next;
    deleting->next = NULL;

    free(deleting);
    list->length--;

    printf("\nRemovido com sucesso da posicao %d da lista!\n", position);
    pause();

    return tmp;
 }


 Vehicle* getVehicle(List* list, int position){
    Vehicle *tmp = list->first;

    int i;
    for (i = 0; i < position-1; i++){
        tmp = tmp->next;
    }

    return tmp;
 }

 int findIndex(List *list, char model[]){

    int index = 0;

    if(list->first == NULL){
        printf("\nLista Vazia!\n");
        return -1;
    }

    if(list->length == 1){
        if(strcmp(model, list->first->model)){
            printf("index: %d;\n", index);
            printVehicle(list->first);
            pause();
            return 0;
        }else{
					printf("\nVeiculo nao cadastrado\n");
				}
    }

    Vehicle *tmp = list->first;

    while (strcmp(model, tmp->model) != 0 || (tmp->next != NULL)){
        tmp = tmp->next;
        index++;
    }
    printf("index: %d; \n", index);
    printVehicle(getVehicle(list, index));
   	pause();

    if (tmp == NULL) {
        printf("\nVeiculo nao cadastrado\n");
    }
		return index;
 }

 int length(List *list){
     return list->first == NULL ? 0 : list->length;
 }

 void toString(List *list){
     if(list->length == 0){
         printf("\nLista Vazia!\n");
         pause();
         return;
     }
		 int position = 0;

     Vehicle *tmp = list->first;
     while(tmp != NULL) {
         printf("\nPosicao %d :\n\tCodigo: %d; \n\tModelo: %s;\n\tPlaca: %s; \n\tValor Diario: R$%.2f;\n", position, tmp->code, tmp->model, tmp->board, tmp->dailyValue);
         tmp = tmp->next;
				 position++;
     }
    pause();
}

void printVehicle(Vehicle *v){
    printf("\nVeiculo Selecionado: \n\tCodigo: %d; \n\tModelo: %s;\n\tPlaca: %s; \n\tValor Diario: R$%.2f;\n", v->code, v->model, v->board, v->dailyValue);
    pause();
}

 void rentVehicle(List *listRented, List *listAvaliable){

    if(listAvaliable->first == NULL){
        printf("\nNao ha veiculos disponiveis para aluguel\n");
        pause();
        return;
    }

    int position = 0;
		printf("\nVeiculos disponiveis:\n");
		toString(listAvaliable);
    printf("\nInforme a posicao do item que deseja alugar:\n");
    scanf("%d", &position);
    fflush(stdin);

    if(position < 0 || position >= listAvaliable->length){
        printf("\nPosicao invalida\n");
        return;
    }

    Vehicle *rentVehicle = (Vehicle*) malloc(sizeof(Vehicle));
		rentVehicle = getVehicle(listAvaliable, position);
    printVehicle(rentVehicle);

    unshift(listRented, rentVehicle);
    deleteVehicle(listAvaliable, position);
 }

 void giveBackVehicle(List *listRented, List *listAvaliable){

    if(listRented->first == NULL){
        printf("\nNao ha veiculos disponiveis para devolucao\n");
        return;
    }

    int position;
    printf("\nInforme a posicao do item que deseja devolver:\n");
    scanf("%d", &position);
    fflush(stdin);

    if(position < 0 || position >= listRented->length){
        printf("Posicao invalida\n");
        return;
    }

    Vehicle *rentVehicle = (Vehicle*) malloc(sizeof(Vehicle));
		rentVehicle = getVehicle(listRented, position);

    printf("\nInforme por quantos dias o carro ficou alugado:\n");
    int days;
    scanf("%d", &days);
    fflush(stdin);
		printf("%d dias", days);
    billing = billing + (days * rentVehicle->dailyValue);
    deleteVehicle(listRented, position);
    push(listAvaliable, rentVehicle);
    pause();
}

 void menu(List* listRented, List* listAvaliable){
    int choice = -1;

    while(choice != 0){
        printf("Selecione uma opção para continuar:\n");

				printf("###################################################\n");
				printf("#############Funcoes de Insercao###################\n");
				printf("###################################################\n");
				printf("# 1-  Inserir novo veículo(no inicio da lista):   #\n");
				printf("# 2-  Inserir novo veículo(no fim da lista):      #\n");
				printf("# 3-  Inserir novo veículo(na posicao):           #\n");
				printf("###################################################\n\n");

				printf("###################################################\n");
				printf("###############Funcoes de Remocao##################\n");
				printf("###################################################\n");
				printf("# 4-  Remover veículo(do inicio da lista):        #\n");
				printf("# 5-  Remover veículo(do final da lista):         #\n");
				printf("# 6-  Remover veículo(em posicao especifica):     #\n");
				printf("###################################################\n\n");

				printf("###################################################\n");
				printf("#########Funcoes de Busca e Visualizacao###########\n");
				printf("###################################################\n");
				printf("# 7-  Encontrar posicao por modelo):              #\n");
				printf("# 8-  Verificar tamanho da lista:                 #\n");
				printf("# 9-  Mostrar lista de disponiveis:               #\n");
				printf("# 10- Mostrar lista de alugados:                  #\n");
				printf("###################################################\n\n");

				printf("###################################################\n");
				printf("############Funcoes Locacao e Devolucao############\n");
				printf("###################################################\n");
				printf("# 11- Alugar um veiculo:                          #\n");
				printf("# 12- Devolver um veiculo:                        #\n");
				printf("###################################################\n\n");

				printf("###################################################\n");
				printf("#################Funcoes de Caixa##################\n");
				printf("###################################################\n");
				printf("# 13- Mostrar Faturamento da loja:                #\n");
				printf("###################################################\n\n");

				printf("###################################################\n");
				printf("################Funcoes de Sistema#################\n");
				printf("###################################################\n");
				printf("# 0 - Sair:                                       #\n");
				printf("###################################################\n\n");

				printf("---------------------------------------------------\n");
				printf("Informe a opcao escolhida:");
				scanf("%d", &choice);
				printf("---------------------------------------------------\n");

        switch(choice){
            int position;
            int listOption;
            case -1:
            break;
            case 1: ;
                Vehicle *vehicle1;
                vehicle1 = newVehicle();
                unshift(listAvaliable , vehicle1);
                break;
            case 2: ;
                Vehicle *vehicle2 = newVehicle();
                push(listAvaliable , vehicle2);
                break;
            case 3: ;
                Vehicle *vehicle3 = newVehicle();
                printf("Escolha uma posicao para inserir o elemento:\n");
                scanf("%d", &position);
                fflush(stdin);
                splice(listAvaliable , vehicle3, position);
                break;
            case 4: ;
                printf("Escolha de qual das listas deseja remover:\n");
                printf("1: Disponiveis;\n2: Alugados\n");
                scanf("%d", &listOption);
                fflush(stdin);
                if(listOption == 1){
                    shift(listAvaliable);
                }else if(listOption == 2){
                    shift(listRented);
                }
                break;
            case 5: ;
                printf("Escolha de qual das listas deseja remover:\n");
                printf("1: Disponiveis;\n2: Alugados\n");
                scanf("%d", &listOption);
                fflush(stdin);
                if(listOption == 1){
                    pop(listAvaliable);
                }else if(listOption == 2){
                    pop(listRented);
                }
                break;
            case 6: ;
                printf("Escolha de qual das listas deseja remover:\n");
                printf("1: Disponiveis;\n2: Alugados\n");
                scanf("%d", &listOption);
                fflush(stdin);
                printf("Escolha uma posicao para remover o elemento:\n");
                scanf("%d", &position);
                fflush(stdin);
                if(listOption == 1){
                    deleteVehicle (listAvaliable, position);
                }else if(listOption == 2){
                    deleteVehicle (listRented, position);
                }
                break;
            case 7: ;
                char model[20];
                printf("Informe o modelo que quer pesquisar:\n");
                scanf("%s", model);
                fflush(stdin);

                printf("Escolha de qual das listas deseja pesquisar:\n");
                printf("1: Disponiveis;\n2: Alugados\n");
                scanf("%d", &listOption);
                fflush(stdin);

                if(listOption == 1){
                    findIndex(listAvaliable, model);
                }else if(listOption == 2){
                    findIndex(listRented, model);
                }
                break;
            case 8: ;
                printf("Tamanho da Lista de Alugados: %d;\n", length(listRented));
                printf("Tamanho da Lista de Disponiveis: %d;\n", length(listAvaliable));
								pause();
                break;
            case 9: ;
                printf("Lista de Disponiveis:\n");
                toString(listAvaliable);
                break;
            case 10:
                printf("Lista de Alugados:\n");
                toString(listRented);
                break;
            case 11:
                rentVehicle(listRented,listAvaliable);
                break;
            case 12:
                giveBackVehicle(listRented, listAvaliable);
                break;
            case 13:
                printf("Faturamento total da loja: R$%.2f\n", billing);
								pause();
                break;
            case 0:
                printf("Volte sempre!\n");
                return;
        }
    }
 }


void pause(){
    printf("\nAperte qualquer tecla para voltar ao Menu\n");
    getchar();
    scanf("c\n");
    fflush(stdin);
		printf("\33[H\33[2J");
}
