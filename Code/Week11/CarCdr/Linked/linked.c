#include "../lisp.h"
#include "specific.h"

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

lisp* lisp_copy(const lisp* l){
    lisp* new_lisp = (lisp*)ncalloc(1, sizeof(lisp*));
    memcpy(new_lisp->car, l->car, sizeof(lisp));
    memcpy(new_lisp->cdr, l->cdr, sizeof(lisp));
    atomtype temp_val = l->val;
    memcpy(new_lisp->val, temp_val, sizeof(atomtype));
    return new_lisp;
}

int lisp_length(const lisp* l){

}

void lisp_tostring(const lisp* l, char* str){

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

