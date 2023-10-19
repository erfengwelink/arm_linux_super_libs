#include <stdio.h>
#include <stdlib.h>
#include "spinlock.h"

int main(int argc, char *argv[]) {
    struct spinlock lock;
    printf("lock spinlock_init\n");

    spinlock_init(&lock);
    printf("lock spinlock_lock\n");


    spinlock_lock(&lock);


    printf("lock spinlock_unlock\n");

    spinlock_unlock(&lock);
    printf("lock end ... \n");


    return 0;
}