#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void emptyfunc(void){
    printf("how did i get here?");
}
static void* myfunc(void* args){
    int* num = (int*)args;
    printf("Inside myfunc\n");
    printf("Num: %d\n",*num);
    *num *= 2;
    printf("Num being returned: %d\n",*num);
    return 0;
}



int main(int argc, char* argv[]){
    printf("Starting Thread Tests...\n");

    printf("Test 1: \n\n");
    int args = 5;
    int tid = 0;
    printf("Address of myfunc: %p\n", myfunc); 
    create_thread(&tid,myfunc,(void*)&args);
    sleep(10);
    printf("TID: %d\n",tid);
    printf("Num after: %d\n",args);
   
    //collect_thread(tid);
    printf("End Test 1 \n\n");
    

    printf("End Thread Tests\n");
    exit(0);
}
