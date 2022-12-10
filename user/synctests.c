#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/syscall.h"
#include "kernel/memlayout.h"
#include "kernel/riscv.h"

//uselese header

int main() {
    int pid;
    for(int i = 0 ;i < 5; i++) pid = fork();
    int now_pid = getpid();
    if(now_pid != 0) { //tricky
        reader();
        //printf("reader %d read %d\n", now_pid, result);
    } else {
        writer();
    }
}