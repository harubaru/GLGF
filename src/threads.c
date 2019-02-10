#include <stdio.h>
#include <stdlib.h>

#include <threads.h>

mutex_t mutex_init()
{
	mutex_t ret;
	pthread_mutexattr_init(&ret.attr);
	pthread_mutex_init(&ret.handle, &ret.attr);
	return ret;
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