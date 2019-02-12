#include <stdio.h>
#include <stdlib.h>

#include <threads.h>

int mutex_init(mutex_t *m)
{
	if (m) {
		if (pthread_mutexattr_init(&m->attr) != 0) {
			fprintf(stderr, "Failed to create mutexattr!\n");
			return -1;
		}
		if (pthread_mutex_init(&m->handle, &m->attr) != 0) {
			fprintf(stderr, "Failed to create mutex!\n");
			return -1;
		}
	} else {
		return -1;
	}

	return 1;
}

int mutex_lock(mutex_t mutex)
{
	return pthread_mutex_lock(&mutex.handle);
}

int mutex_trylock(mutex_t mutex)
{
	return pthread_mutex_trylock(&mutex.handle);
}

int mutex_unlock(mutex_t mutex)
{
	return pthread_mutex_unlock(&mutex.handle);
}

void mutex_destroy(mutex_t mutex)
{
	pthread_mutex_destroy(&mutex.handle);
	pthread_mutexattr_destroy(&mutex.attr);
}

thread_t thread_init(void *(*func) (void*), void *restrict arg)
{
	thread_t ret;
	
	ret.handle = calloc(1, sizeof(pthread_t));

	if (ret.handle == NULL) {
		fprintf(stderr, "Failed to allocate memory for thread!\n");
		return ret;
	}
	
	if (pthread_create(ret.handle, NULL, func, arg)) {
		fprintf(stderr, "Failed to create thread!\n");
		free(ret.handle);
		ret.handle = NULL;
	}

	return ret;
}

void thread_exit(void)
{
	pthread_exit(NULL);
}

void thread_join(thread_t thread)
{
	if (thread.handle)
		pthread_join(*thread.handle, NULL);
}