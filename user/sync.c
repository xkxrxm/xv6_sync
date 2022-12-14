#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// ������ѧ�ҾͲ�����
void test1(int m){
    int i; 
    
    for(i=0;i<3;i++)
        fork();
    // ���Ϊ0�����Լ���ͬ�����Ե�
    // ���Ϊ1������δ��ͬ����
    philosopher(m);
}

// ���Գ���1����֤�Ƿ�ʵ��ͬ��
void test2(){
    int i; 
    int pid;

    for(i=0;i<3;i++)
        pid=fork();

    for(i=0;i<10000;i++)
        var_add();

    printf("%d :%d\n",pid,var_read());

    sleep(10);
}

int 
main(int argc,char* argv[])
{
    if(argv[1][0]=='a')//add
        test2();
    else if(argv[1][2]=='_')//ph_not
        test1(1);
    else if (argv[1][0]=='p')//ph
        test1(0);
    else if (argv[1][0]=='c')//clear
        var_clear();
    else
        printf("invalid command!\n");
    
    exit(0);
}
