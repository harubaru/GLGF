#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>

typedef struct thread {
	pthread_t *handle;
} thread_t;

typedef struct mutex {
	pthread_mutex_t handle;
	pthread_mutexattr_t attr;
} mutex_t;

int mutex_init(mutex_t *m);
int mutex_lock(mutex_t mutex);
int mutex_trylock(mutex_t mutex);
int mutex_unlock(mutex_t mutex);
void mutex_destroy(mutex_t mutex);

thread_t thread_init(void *(*func) (void*), void *restrict arg);
void thread_exit(void);
void thread_join(thread_t thread);


#endif