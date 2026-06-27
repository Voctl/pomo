#pragma once

void sendn(char *msg);
void update_status_file(const char *prefix, int mins, int secs,
                        const char *color);
void clear_status_file(void);
void run_timer(int minutes, const char *prefix, const char *color,
               const char *msg);

// Default times
#define WORK_TIME 25
#define BREAK_TIME 5

// Notification config
#define APP_NAME "Pomodoro"
#define WORK_MSG "yo nigga dont work go and enjoy with life."
#define BREAK_MSG "YO NIGGA JUST FOCUS ."
