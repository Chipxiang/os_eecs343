#include "types.h"
#include "user.h"
#include "param.h"
#include "ProcessInfo.h"

int
main(int argc, char *argv[])
{
    int res;
    struct ProcessInfo processInfoTable[NPROC];
    res = getprocs(processInfoTable);
    printf(1,"number of processes is %d\n", res);

    enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };
    const char* states[] = {"UNUSED", "EMBRYO", "SLEEPING", "RUNNABLE", "RUNNING","ZOMBIE"};
    
    int i;
    int ppid;
    for(i = 0; i < res; i++){
        if(strcmp(processInfoTable[i].name, "init") == 0) ppid = -1;
        else ppid = processInfoTable[i].ppid;
        printf(1, "%d  %d  %s  %d  %s\n", processInfoTable[i].pid, ppid, states[processInfoTable[i].state],
            processInfoTable[i].sz, processInfoTable[i].name);
    }
    exit();
}
