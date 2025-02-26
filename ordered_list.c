#include <stdio.h>
#include <stdlib.h>
#include "ordered_list.h"

//Eduardo Ferraz
//Pedro Belini

// 1) Indique o(s) ponto(s) forte(s) e fraco(s) de uma lista ordenada, justificando-os.

// Pontos Fortes
// 1 - Tempo de busca é menor do que em listas não ordenadas.
// 2 - Manutenção de ordem com dados organizados que facilitam operações e a visualização.
// 3 - Fácil acesso aos menores e maiores valores.

// Pontos Fracos
// 1 - Quanto maior a lista, maior processo de inserção.
// 2 - Manter uma lista ordenada se torna mais complexa dependendo da quantidade de remoções e inserções.
// 3 - Requer uma estratégia inteligente para o aumento de memória se o usuário desejar inserir mais itens.

// 2) Descreva a estratégia utilizada para o aumento de memória quando o usuário deseja inserir mais itens que o alocado previamente.

// Adotamos uma estratégia híbrida que verifica o tamanho da lista e escolhe uma das duas opções:
// A) Se o tamanho da lista for 5000>=, a lista aumentará seu tamanho em 50%. 10.000 -> 15.000.
// B) Se o tamanho da lista for <5000, a lista ira dobrar de tamanho. 3000 -> 6000.

int binarySearch(t_ordered_list *list, int value){
    int start = 0;
    int end = list->n;

    while(start<=end){
        int mid = (start+end)/2;
        if(list->items[mid]==value){
            return mid;
        }

        if(list->items[mid]>value){
            end = mid-1;
        }else{
            start = mid+1;
        }
    }

    return -1;
}

void append(t_ordered_list* list, int value){
    list->items[list->n++] = value;
}

t_ordered_list* create_ordered_list(int max){
    t_ordered_list *newList = malloc(sizeof(t_ordered_list));
    newList->max = max;
    newList->n = 0;
    newList->items = malloc(sizeof(int)* (size_t) max);

    return newList;
}

int size(t_ordered_list* list){
    return list->n;
}

int is_empty(t_ordered_list* list){
    if(list->n<=0){
        return 1;
    }
    return 0;
}

int is_full(t_ordered_list* list){
    if(list->n>=list->max){
        return 1;
    }
    return 0;
}

void destroy(t_ordered_list* list){
    free(list->items);
    free(list);
}

void clear(t_ordered_list* list){
    list->n = 0;
}

int find_insert_index(t_ordered_list* list, int value){
    int counter = 0;

    while(counter<list->n && list->items[counter]<value){
        counter++;
    }

    return counter;
}   

int grow_list(t_ordered_list* list){
    size_t newSize;
    if(list->max>=50000){
        newSize = (size_t) list->max * (size_t) 1.5;
    }else{
        newSize = (size_t) list->max*2;
    }

    list->items = (int*) realloc(list->items,sizeof(int)*newSize);
    if(list->items == NULL){
        return -1;
    }

    list->max = (int)newSize;
    return 0;
}

int insert(t_ordered_list* list, int value){
    if(is_full(list)){
        grow_list(list);
    }

    int index = find_insert_index(list,value);

    list->n++;
    for(int i=list->n;i>index;i--){ 
        list->items[i] = list->items[i-1];
    }
    list->items[index] = value;

    return 0;
}

int search(t_ordered_list* list, int value){
    return binarySearch(list,value);
}

int remove_by_index(t_ordered_list* list, int index){
    if(is_empty(list) || index>=list->n){
        return -1;
    }

    for(int i=index;i<list->n-1;i++){
        list->items[i]=list->items[i+1];
    }
    list->n--;
    return 0;
}

int remove_by_value(t_ordered_list* list, int value){
    int index = binarySearch(list,value);

    if(index==-1){
        return index;
    }

    remove_by_index(list,index);
    return 0;
}

int remove_end(t_ordered_list* list){
    if(is_empty(list)){
        return -1;
    }

    list->n--;
    return 0;
}

void print_ordered_list(t_ordered_list* list){
    for(int i=0;i<list->n;i++){
        printf("%d ",list->items[i]);
    }
    printf("\n");
}

t_ordered_list* merge(t_ordered_list* list1, t_ordered_list* list2){
    t_ordered_list *merged_list = create_ordered_list(list1->n+list2->n);

    int counter1 = 0, counter2 = 0;
    while(counter1<list1->n && counter2<list2->n){
        if(list1->items[counter1]<=list2->items[counter2]){
            append(merged_list,list1->items[counter1]);
            counter1++;
        }else{
            append(merged_list,list2->items[counter2]);
            counter2++;
        }
    }

    while(counter1<list1->n){
        append(merged_list,list1->items[counter1]);
        counter1++;
    }
    while(counter2<list2->n){
        append(merged_list,list2->items[counter2]);
        counter2++;
    }

    return merged_list;
}
