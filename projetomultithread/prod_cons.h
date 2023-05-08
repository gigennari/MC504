#ifndef PROD_CONS_H
#define PROD_CONS_H

/***
 * Opções disponíveis no cardápio
 * Cada comida pode ter um tempo diferente de preparação e consumo, assim o restaurante fica bem "paralelizado"
 * */

enum Food {
    Frango,
    Carbonara,
    Porpeta,
    Mignon,
    Camarao
};

/**
 * Estrutura da lista que será a fila
 * Cliente é uma senha enquanto está na fila, e ao entra no restaurante, ele vira uma Thread cujo ID é 'senha'.
 * */
typedef struct Client {

    struct Cliente *next;  //aponta pro próximo da fila

    int senha; // ID do cliente
    enum Food food; //tipo de comida que o Cliente pode pedir(ele já sabe com antecedência)
} No;

typedef struct Cliente *p_no;

// p_no *start; // ponteiro pro início da fila
// p_no *last; // ponteiro pro final da fila

/***
 * Cria uma lista ligada
*/
p_no create_list();

/***
 * Coloca mais um cliente na fila pra entrar no restaurante.
 * Atualiza o ponteiro de fim
*/
void insert_node(p_no last, p_no client);



#endif