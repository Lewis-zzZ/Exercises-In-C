#include "../lisp.h"
#include "specific.h"
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 1000
#define RADIX 10
#define NIL NULL
#define atom(X)       lisp_atom(X)
#define cons(X, Y)    lisp_cons(X, Y)
#define car(L)        lisp_car(L)
#define cdr(L)        lisp_cdr(L)
#define copy(L)       lisp_copy(L)
#define fromstring(L) lisp_fromstring(L)

lisp* lisp_atom(const atomtype a){
    lisp* new_lisp = (lisp*)ncalloc(1, sizeof(lisp));
    new_lisp->val = a;
    new_lisp->car = NULL;
    new_lisp->cdr = NULL;
    return new_lisp;
}

lisp* lisp_cons(const lisp* l1,  const lisp* l2){
    lisp* new_lisp = (lisp*)ncalloc(1, sizeof(lisp));
    if (l1 == NULL && l2 == NULL){
        return NULL;
    }
    new_lisp->car = (lisp*)l1;
    new_lisp->cdr = (lisp*)l2;
    return new_lisp;
}

lisp* lisp_car(const lisp* l){
    if (l == NULL){
        return NULL;
    }
    return l->car;
}

lisp* lisp_cdr(const lisp* l){
    if (l == NULL){
        return NULL;
    }
    return l->cdr;
}

atomtype lisp_getval(const lisp* l){
    if (l == NULL){
        return -1;
    }
    return l->val;
}

bool lisp_isatomic(const lisp* l){
    if (l == NULL){
        return 0;
    }
    if (l->car == NULL && l->cdr == NULL){
        return 1;
    }
    return 0;
}

lisp* lisp_copy(const lisp* l){
    lisp* copy_lisp = (lisp*)ncalloc(1, sizeof(lisp));
    if (l == NULL){
        copy_lisp = NULL;
    }else {
        copy_lisp = lisp_atom(lisp_getval(l));
        copy_lisp->car = lisp_copy(lisp_car(l));
        copy_lisp->cdr = lisp_copy(lisp_cdr(l));
    }
    return copy_lisp;
}

void lisp_count_cdr(const lisp* l, int* len){
    if (lisp_cdr(l) != NULL){
        ++(*len);
        lisp_count_cdr(lisp_cdr(l), len);
    }
}

int lisp_length(const lisp* l){
    int len = 0;
    if (lisp_car(l) != NULL){
        ++len;
    }
    if (lisp_car(l) == NULL && lisp_cdr(l) != NULL){
        ++len;
    }
    lisp_count_cdr(l, &len);
    return len;
}

void lisp_scan(const lisp* l, char* str){
    if (l == NULL){
        return;
    }
    if (lisp_car(l) != NULL){
        if (!lisp_isatomic(lisp_car(l))){
            strcat(str, "(");
            lisp_scan(lisp_car(l), str);
            strcat(str, " ");
            lisp_scan(lisp_cdr(l), str);
        }else {
            char temp[MAXLENGTH];
            itoa(lisp_getval(lisp_car(l)), temp, RADIX);
            strcat(str, temp);
            if (lisp_cdr(l) != NULL){
                strcat(str, " ");
                lisp_scan(lisp_cdr(l), str);
            } else{
                strcat(str, ")");
            }
        }
    }
}

void lisp_tostring(const lisp* l, char* str){
    str[0]='\0';
    if (l == NULL){
        strcat(str, "()");
        return;
    }
    if (lisp_car(l) != NULL){
        strcat(str, "(");
        lisp_scan(l, str);
        return;
    }
    if (l != NULL & lisp_car(l) == NULL){
        if (lisp_isatomic(l)){
            char temp[MAXLENGTH];
            itoa(lisp_getval(l), temp, RADIX);
            strcat(str, temp);
        }
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

lisp* lisp_fromstring(const char* str){
    (void)str;
    return NULL;
}

lisp* lisp_list(const int n, ...){
    (void)n;
    return NULL;
}

void lisp_reduce(void (*func)(lisp* l, atomtype* n), lisp* l, atomtype* acc){
    func(l, acc);
    (void)l;
    (void)acc;
    return;
}

void test(void){
    char str[MAXLENGTH];
    printf("My Test Start ... \n");

    lisp* l1 = cons(atom(2), NIL);
    int len1 = 0;
    lisp_count_cdr(l1, &len1);
    assert(len1 == 0);
    assert(lisp_length(l1)==1);
    str[0]='\0';
    lisp_scan(l1, str);
    assert(strcmp(str, "2)")==0);

    lisp* l2 = cons(atom(1), l1);
    assert(l2);
    int len2 = 0;
    lisp_count_cdr(l2, &len2);
    assert(len2 == 1);
    assert(lisp_length(l2)==2);
    str[0]='\0';
    lisp_scan(l2, str);
    assert(strcmp(str, "1 2)")==0);

    lisp* l3 = cons(atom(3), cons(atom(4), cons(atom(5), NIL)));
    lisp* l4 = cons(l2, l3);
    int len3 = 0;
    int len4 = 0;
    lisp_count_cdr(l3, &len3);
    assert(len3 == 2);
    lisp_count_cdr(l4, &len4);
    assert(len4 == 3);
    str[0]='\0';
    lisp_scan(l4, str);
    assert(strcmp(str, "(1 2) 3 4 5)")==0);

    lisp* l5 = cons(atom(0), l4);
    assert(l5);
    int len5 = 0;
    lisp_count_cdr(l5, &len5);
    assert(len5 == 4);
    str[0]='\0';
    lisp_scan(l5, str);
    assert(strcmp(str, "0 (1 2) 3 4 5)")==0);

    lisp_free(&l5);
    assert(!l5);

    printf("My Test End. \n\n");
}
