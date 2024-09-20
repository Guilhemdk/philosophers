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

size_t mutex_get_size_t(pthread_mutex_t *mutex, size_t *value)
{
	size_t res;

	mutex_handler(mutex, LOCK);
	res = *value;
	mutex_handler(mutex, UNLOCK);
	return (res);
}

void mutex_set_size_t(pthread_mutex_t *mutex, size_t *dest, size_t value)
{
	mutex_handler(mutex, LOCK);
	*dest = value;
	mutex_handler(mutex, UNLOCK);
}

