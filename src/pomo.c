#include "pomo.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void sendn(char *msg) {
  char command[256];
  snprintf(command, sizeof(command), "notify-send 'Pomodoro' '%s'", msg);
  system(command);
}

void update_status_file(const char *prefix, int mins, int secs,
                        const char *color) {
  FILE *fp = fopen("/tmp/pomo_status", "w");
  if (fp) {
    fprintf(fp, "{\"full_text\": \"%s %02d:%02d\", \"color\": \"%s\"}\n",
            prefix, mins, secs, color);
    fclose(fp);
  }
}

void clear_status_file(void) {
  FILE *fp = fopen("/tmp/pomo_status", "w");
  if (fp) {
    fprintf(fp, "{\"full_text\": \"\"}\n");
    fclose(fp);
  }
}

void handle_signal(int sig) {
  (void)sig;
  clear_status_file();
  printf("\e[?25h\n");
  exit(0);
}

void run_timer(int minutes, const char *prefix, const char *color,
               const char *msg) {
  int total_seconds = minutes * 60;
  while (total_seconds > 0) {
    int mins = total_seconds / 60;
    int secs = total_seconds % 60;

    printf("\r\e[K%s Left: %02d:%02d", prefix, mins, secs);
    fflush(stdout);

    update_status_file(prefix, mins, secs, color);

    sleep(1);
    total_seconds--;
  }
  printf("\n");
  sendn((char *)msg);
}

int main(int argc, char *argv[]) {
  int work_time = WORK_TIME;
  int break_time = BREAK_TIME;

  if (argc > 1) {
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
      printf("Usage: %s [work_minutes] [break_minutes]\n", argv[0]);
      printf("Default: Work %d mins, Break %d mins\n", WORK_TIME, BREAK_TIME);
      return 0;
    }
    work_time = atoi(argv[1]);
    if (work_time <= 0) {
      fprintf(stderr, "[ Error ]: Invalid work time '%s'\n", argv[1]);
      return 1;
    }
  }
  if (argc > 2) {
    break_time = atoi(argv[2]);
    if (break_time <= 0) {
      fprintf(stderr, " [ Error ]: Invalid break time '%s'\n", argv[2]);
      return 1;
    }
  }

  signal(SIGINT, handle_signal);
  signal(SIGTERM, handle_signal);

  printf("\e[?25l");
  fflush(stdout);

  run_timer(work_time, "WORK", "#FF9900", WORK_MSG);

  run_timer(break_time, "BREAK", "#55FF55", BREAK_MSG);

  clear_status_file();
  printf("\e[?25h");
  fflush(stdout);

  return 0;
}
