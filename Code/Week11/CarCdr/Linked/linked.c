#include "../lisp.h"
#include "specific.h"
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 1000
#define RADIX 10

lisp* lisp_atom(const atomtype a){
    lisp* new_lisp = (lisp*)ncalloc(1, sizeof(lisp*));
    new_lisp->val = a;
    new_lisp->car = NULL; //new_lisp->car = some_lisp
    new_lisp->cdr = NULL;
    //*new_lisp.car = (lisp*)calloc(1, sizeof(a));
    return new_lisp;
}

lisp* lisp_cons(const lisp* l1,  const lisp* l2){
    lisp* new_lisp = (lisp*)ncalloc(1, sizeof(lisp*));
    if (l1 == NULL && l2 == NULL){
        return NULL;
    }
    new_lisp->car = (lisp*)l1;
    new_lisp->cdr = (lisp*)l2;
    return new_lisp;
}

lisp* lisp_car(const lisp* l){
    return l->car;
}

lisp* lisp_cdr(const lisp* l){
    return l->cdr;
}

atomtype lisp_getval(const lisp* l){
    return (l->val);
}

bool lisp_isatomic(const lisp* l){
    if (l->car == NULL && l->cdr == NULL){
        return 1;
    }
    return 0;
}

lisp* lisp_copy(const lisp* l){
    lisp* new_lisp = (lisp*)ncalloc(1, sizeof(lisp*));

    memcpy(new_lisp->car, l->car, sizeof(lisp));
    memcpy(new_lisp->cdr, l->cdr, sizeof(lisp));
    atomtype temp_val = l->val;
    memcpy(&new_lisp->val, &temp_val, sizeof(atomtype));
    return new_lisp;
}

void lisp_count_cdr(const lisp* l, int* len){
    if (lisp_cdr(l) != NULL){
        ++(*len);
        lisp_count_cdr(lisp_cdr(l), len);
    }
}

int lisp_length(const lisp* l){
    int len = 0;
    lisp_count_cdr(l, &len);
    return len;
}

void lisp_tostring(const lisp* l, char* str){
    if (lisp_isatomic(l)){
        char temp[MAXLENGTH];
        itoa(lisp_getval(l), temp, RADIX);
        strcat(str, temp);
        if (lisp_cdr(l) == NULL){
            strcat(str, ")");
        } else{
            strcat(str, " ");
        }
        lisp_tostring(lisp_car(l), str);
        lisp_tostring(lisp_cdr(l), str);
    } else{
        strcat("(");
        lisp_tostring(lisp_car(l), str);
        lisp_tostring(lisp_cdr(l), str);
    }

}

void lisp_free(lisp** l){
    if (l == NULL || *l == NULL){
        return;
    }
    lisp* cur = *l;
    lisp_free(&(cur->car));
    lisp_free(&(cur->cdr));
    free(*l);
    *l = NULL;
}

void test(void){

}