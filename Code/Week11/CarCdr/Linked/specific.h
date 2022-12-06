#define LISPIMPL "Linked"
struct lisp{
    atomtype val;
    lisp* car;
    lisp* cdr;
};
