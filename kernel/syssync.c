#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "stat.h"
#include "spinlock.h"
#include "proc.h"
#include "fs.h"
#include "sleeplock.h"
#include "file.h"
#include "fcntl.h"
// useless headers?
#include "syssync.h"

struct signal {
    int val;
    struct spinlock lk;
};
struct signal RW, R;
int reader_count = 0;

void initsignal(struct signal *s, char *name) { initlock(&s->lk, name); s->val = 0; }

void WAIT(struct signal *s) {
    while(1) {
        acquire(&s->lk);
        if(s->val > 0) {
            s->val = s->val - 1;
            release(&s->lk);
            break;
        }
        release(&s->lk);
    }
}

void SIGNAL(struct signal *s) {
    while(1) {
        acquire(&s->lk);
        s->val = s->val + 1;
        release(&s->lk);
    }
}

uint64 sys_reader(void) {
    while(1) {
        // sleep need?
        WAIT(&R);
        if(reader_count == 0)
            WAIT(&RW);
        reader_count ++;
        SIGNAL(&R);
        printf("reader begin read a thing\n");
        //read here
        printf("reader end read a thing\n");
        WAIT(&R);
        reader_count --;
        if(reader_count == 0)
            SIGNAL(&RW);     
        SIGNAL(&R);
    }
}

uint64 sys_writer(void) {
    while(1) {
        // sleep need?
        WAIT(&RW);
        printf("writer begin read a thing\n");
        //write here
        printf("writer end read a thing\n");
        SIGNAL(&RW);
    }
}

uint64 sys_peterson(void) {
    
}

