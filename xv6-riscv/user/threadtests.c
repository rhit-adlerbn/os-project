// Test that thread create and collect works.
// Tiny executable so that the limit can be filling the proc table.

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

typedef struct multiple_args_container {
  int tid;
  char letter;
} ma_container;

int* shared_val;

void
*thread_func1(void *args)
{
  printf("Hello World! from thread!\n");
  
  exit_thread();
  return 0;
}

void 
*thread_func2(void *args)  
{
  int *tidPtr = (int *)args;
  printf("Hello World! from thread %d!\n", *tidPtr);

  exit(0);
  return 0;
}

void
*thread_func3(void *args) 
{
  ma_container *container = (ma_container *) args;
  printf("Reporting letter %c from thread %d!\n", container->letter, container->tid);

  sleep(1);

  exit(0);
  return 0;
}
void
*thread_func4(void *args)
{
  int tid = *(int*)args;
  printf("Shared val: %d, in thread %d\n",*shared_val,tid);
  printf("Thread %d modifing shared val\n",tid);
  *shared_val += 1;
 
  sleep(5);
  printf("Exiting thread %d with shared val: %d\n",tid,*shared_val);
  exit(0);
  return 0;
}
//simple_thread: test one thread creation with no args
void simple_thread_test(void) {
  
  printf("Test 1: Simple thread (no args) \n");

  int tid;
  void *args = 0;
  create_thread(&tid, &thread_func1, &args);
  //collect_thread(tid);
  
  sleep(1);

  printf("Finished Test 1\n\n");

}

void thread_with_arg_test(void) {

  printf("Test 2: Thread with one arg\n");

  int tid;
  void* args = (void *) 13557;
  create_thread(&tid, &thread_func2, &args);
  //collect_thread(tid);
  
  sleep(1);

  printf("Finished Test 2\n\n");
}

void thread_with_args_test(void) {

  printf("Test 3: Thread with multiple arguments\n");

  int tid;
  ma_container *container = malloc(sizeof(ma_container));
  container->tid = 12;
  container->letter = 'a';

  void* args = (void *) container;
  create_thread(&tid, &thread_func3, args);
  //collect_thread(tid);
  
  sleep(1);

  printf("Finished Test 3\n\n");

}

void multiple_threads(void) {
  
  printf("Test 4: Multiple Threads with multiple args\n");
  
  //set up args, create threads
  int i;
  int tids[3];
  for (i = 0; i < 3; i++) {
    ma_container *container = malloc(sizeof(ma_container)); 
    container->tid = i;
    container->letter = 'a' + i;

    create_thread(&tids[i], &thread_func3, (void *) container);
    sleep(1);
  }

  //collect threads
  //int j;
  //for(j = 0; j < 3; j++) {
  //  collect_thread(tids[j]);
  //}

  printf("Finished Test 4\n\n");

}

void multiple_funcs_test(void) {

  printf("Test 5: Multiple threads with different functions\n");

  int tids[2];
  void* args = 0;
  create_thread(&tids[0], &thread_func1, &args);
  
  sleep(1);
  
  create_thread(&tids[1], &thread_func2, &args);


  //collect_thread(tids[0]);
  //collect_thread(tids[1]);

  sleep(1);

  printf("Finished Test 5\n\n");

}
void shared_memory_test(void){
  printf("Test 6: Modifing shared memory\n");
  shared_val = malloc(sizeof(int));
  int tids[3];
  for(int i = 0; i<3; i++){
    create_thread(&tids[i], &thread_func4, &tids[i]);
    sleep(1);
  }
  printf("Finished test 6\n\n");
}
int main(int argc, char* argv[]) {
    printf("Starting Thread Tests...\n");

    simple_thread_test();
    sleep(1);
    thread_with_arg_test();
    sleep(1);
    thread_with_args_test();
    sleep(1);
    multiple_threads();
    sleep(1);
    multiple_funcs_test();
    sleep(1);
    shared_memory_test();
    printf("Finished with Thread Tests...\n");

    exit(0);
}

