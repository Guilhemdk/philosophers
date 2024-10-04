#include "../includes/philo.h"

int mutex_get_int(pthread_mutex_t *mutex, int *value)
{
	int res;

	mutex_handler(mutex, LOCK);
	res = *value;
	mutex_handler(mutex, UNLOCK);
	return (res);
}

void mutex_set_int(pthread_mutex_t *mutex, int *dest, int value)
{
	mutex_handler(mutex, LOCK);
	*dest = value;
	mutex_handler(mutex, UNLOCK);
}

size_t mutex_get_long(pthread_mutex_t *mutex, long *value)
{
	long res;

	mutex_handler(mutex, LOCK);
	res = *value;
	mutex_handler(mutex, UNLOCK);
	return (res);
}

void mutex_set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	mutex_handler(mutex, LOCK);
	*dest = value;
	mutex_handler(mutex, UNLOCK);
}

