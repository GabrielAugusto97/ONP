#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 400

typedef struct{
    struct no *topo;
    int tamanho;
} tPilha;

typedef struct no {
    char dado;
    struct no *prox;
} tNo;

void cria(tPilha *pilha){
    pilha->topo = NULL;
    pilha->tamanho = 0;
}

int vazia(tPilha pilha){
    if(pilha.tamanho == 0){
        return 1;
    }else
        return 0;
}

int tamanho(tPilha pilha){
    return (pilha.tamanho + 1);
}

int cheia(tPilha pilha){
    if(MAX_LENGTH == pilha.tamanho + 1){
        return 1;
    }else
        return 0;
}

int top(tPilha *pilha, char *dado){
    if(vazia(*pilha)){
        return 0;
    }else{
        tNo *aux;
        aux = pilha->topo;

        *dado = aux->dado;
        return 1;
    }
}

int push(tPilha *pilha, char elem){
    if(cheia(*pilha)){
        return 0;
    }else{
        tNo *novoNo;
        novoNo = (tNo*) malloc(sizeof (tNo));
        if(novoNo == NULL){
            return 0; /* Memória Insuficiente */
        }
        novoNo->dado = elem;
        novoNo->prox = NULL;
        if(vazia(*pilha)){
            pilha->topo = novoNo;
        }else{
            tNo *aux;
            aux = pilha->topo;
            pilha->topo = novoNo;
            novoNo->prox = aux;
        }
        pilha->tamanho++;

        return 1;
    }
}

int pop(tPilha *pilha, char *dado){
    if(vazia(*pilha)){
        return 0;
    }else{
        tNo *aux;
        aux = pilha->topo;

        *dado = aux->dado;
        pilha->topo = aux->prox;

        free(aux);
        pilha->tamanho--;
        return 1;
    }
}

int main(void){
    tPilha conv;
    cria(&conv);

    int numExp = 0;
    scanf("%d", &numExp);

    char exp[numExp][MAX_LENGTH]; /* Array bidimensional para armazenar as expressões infixas */
    for(int i = 0; i < numExp; i++){
        scanf("%s", exp[i]);
    }
    printf("\n");

    for(int i = 0; i < numExp; i++){
        for(int j = 0; exp[i][j] != '\0'; j++){
            char a, b;
            a = exp[i][j];
            if(a >= 'a' && a <= 'z'){
                printf("%c", a);
            }else if(a == '('){
                push(&conv, a);
            }else if(a == '+' || a == '-' || a == '/' || a == '*' || a == '^'){
                push(&conv, a);
            }else if(a == ')'){
                do{
                    pop(&conv, &b);
                    if(b != '(')
                        printf("%c", b);
                }while(b != '(');
            }
            if(exp[i][j+1] == '\0'){
                    do{
                        pop(&conv, &b);
                    if(vazia(conv) && b != '(')
                        printf("%c", b);
                    }while(!vazia(conv));
            }
        }
        printf("\n");
    }
    return 0;
}
