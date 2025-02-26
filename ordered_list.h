#ifndef ORDERED_LIST_H
#define ORDERED_LIST_H

typedef struct {
    int max; // tamanho alocado
    int n; // numero de elementos na lista
    int* items; // vetor com os elementos
} t_ordered_list;

t_ordered_list* create_ordered_list(int max);
int size(t_ordered_list*);
int is_empty(t_ordered_list*);
int is_full(t_ordered_list*);
void destroy(t_ordered_list*);
void clear(t_ordered_list*);
int insert(t_ordered_list*, int value);
int search(t_ordered_list*, int value);
int remove_by_index(t_ordered_list*, int index);
int remove_by_value(t_ordered_list*, int value);
int remove_end(t_ordered_list*);
void print_ordered_list(t_ordered_list*);
t_ordered_list* merge(t_ordered_list*, t_ordered_list*);

#endif