#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include"pomo.h"

void sendn(char *msg){
    char command[256];
    snprintf(command, sizeof(command), "notify-send 'Pomodoro' '%s' ", msg);
    system(command);
}

void run_timer(int minutes, char *msg){
    int total_seconds = minutes * 60;
    while (total_seconds >  0){
    printf("\rTime Left:  %02d:%02d\n", total_seconds / 60, total_seconds % 60);
    fflush(stdout);
    sleep(1);
    total_seconds--;
    }
    printf("\n");
    sendn(msg);
}


int main(int argc, char *argv[]){
//for run
    run_timer(WORK_TIME, WORK_MSG);
//for break
    run_timer(BREAK_TIME, BREAK_MSG);

    return 0;
}

