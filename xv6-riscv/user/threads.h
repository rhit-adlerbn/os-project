int create_thread(void *(*function)(void *), void *arguments){
    int tid;
    if (sys_create_thread(&tid, function, arguments) < 0){
        return -1;
    }
    return tid;
}
int collect_thread(int tid){
    return sys_collect_thread(tid);
}
void exit_thread(){
    sys_exit();
}
