#ifndef OS_SCHEDULER_H
#define OS_SCHEDULER_H

#ifdef __cplusplus
extern "C" {
#endif

int sched_init(void);
void sched_clean(void);
int add_proc(void);
int sched(int time, int cont);
int sched_fin(void);

#ifdef __cplusplus
}
#endif

#endif
