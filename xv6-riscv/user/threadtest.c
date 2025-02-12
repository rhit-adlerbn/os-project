#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void* myfunc(void* args){
    printf("Inside myfunc\n");
    return 0;
}


int main(int argc, char* argv[]){
    printf("Starting Thread Tests...\n");

    printf("Test 1: \n\n");
    int tid = 0; //set these for now
    void* args = 0;
    create_thread(&tid,&myfunc,&args);
    collect_thread(tid);
    printf("End Test 1 \n\n");
    

    printf("End Thread Tests\n");
    exit(0);
}
