#include "philo.h"

//function used by the thread
void *routine_function(pthread_mutex_t mutex, void *arg)
{
	(int)arg;
	pthread_mutex_lock(&mutex); //locks the function until thread has finished
	//do something
	//...
	pthread_mutex_unlock(&mutex); //unlock the function for next thread
	free(arg);
}

int main(int argc, char **argv)
{
    pthread_t	*threads;
	pthread_mutex_t mutex;
	int i;
	int *res;
	int number_of_philos;

	number_of_philos = ft_atoi(argv[1]);
	threads = malloc(sizeof(pthread_t) * number_of_philos);
	if (!threads)
		error(THREAD_MALLOC_ERR);
	pthread_mutex_init(&mutex, 'attributes (set to NULL by default)'); //initialize the lock
	i = 0;
	while(i < number_of_philos)
	{
		if (pthread_create(threads[i], NULL, &routine_function, (void *)i) != 0) //initialize threads
			error(THREAD_CREATION_ERR);
	}
	i = 0;
	while(i < number_of_philos)
		if (pthread_join(threads[i],'result of the function (void **) &res' ) != 0) //Waiting for threads to finish
			error(THREAD_JOIN_ERR);
	pthread_mutex_destroy(&mutex); //destroy lock
    return (0);
}

/*
pthread_mutex_init:(mutex variable, attributes)
pthread_create:(thread, attributes, function call, argument)
pthread_join:(thread, result of function call)
*/