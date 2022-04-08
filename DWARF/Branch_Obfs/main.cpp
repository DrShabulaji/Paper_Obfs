#include <iostream>
#include <sys/mman.h>

void *show_obfs_bb1;
void *show_obfs_bb2;
int *show_obfs_bb2_type;
int type_of_int;
int type_of_double;

void throw_exception() {
    throw 1;
}

void wrapper_show_obfs_bb2(long *addr) {
    try {
        throw_exception();
    }
    catch (double r) {
        *addr = (long) show_obfs_bb2;
        return;
    }
}

void wrapper_show_obfs_bb1(long *addr) {
    try {
        wrapper_show_obfs_bb2(addr);
    }
    catch (int r) {
        *addr = (long) show_obfs_bb1;
        return;
    }
}

void jump() {
    long addr;
    wrapper_show_obfs_bb1(&addr);
    asm("movq   %0, 8(%%rbp)" : : "r"(addr));
}

void show(int a) {
    if (a == 1) {
        printf("1\n");
    }
    else {
        printf("Not 1\n");
    }
    printf("END\n");
}

void show_obfs(int a) {
    show_obfs_bb1 = &&bb1;
    show_obfs_bb2 = &&bb2;

    if (a != 1) {
        *show_obfs_bb2_type = type_of_int;
    }

    jump();

    if (a == 114514) {
        bb1:
        printf("1\n");
    }
    else {
        bb2:
        printf("Not 1\n");
        *show_obfs_bb2_type = type_of_double;
    }
    printf("END\n");
}

void obfs() {
    *type_of_BB_ENTRY = exp4;
    while (true) {
        try {
            throw_exp4();
        }
        catch (exp1 e) {
BB_ENTRY: ;
            *type_of_BB_ENTRY = exp1;
            *type_of_SUCC_BB = exp4;
        }
        catch (exp2 e) {
BB_BB1: ;
            *type_of_BB_BB1 = exp2;
            *type_of_SUCC_BB = exp4;
        }
        catch (exp3 e) {
BB_BB2: ;
            *type_of_BB_BB1 = exp3;
            *type_of_SUCC_BB = exp4;
        }
    }
}

int main(int argc, char** argv) {
    if (long(show_obfs_bb2_type) % 4096 != 0) {
        mprotect((long *)((long(show_obfs_bb2_type) / 4096) * 4096), sizeof(long), PROT_READ | PROT_WRITE);
    }
    else {
        mprotect(show_obfs_bb2_type, sizeof(long), PROT_READ | PROT_WRITE);
    }

    show_obfs(argc);
    return 0;
}
