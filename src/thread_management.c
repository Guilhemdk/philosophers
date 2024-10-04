#include "../includes/philo.h"

static void	handle_thread_error(int status, t_mutexOps op)
{
	if (status == 0)
		return ;
	else if (status == EAGAIN)
		error("No ressources to create another thread");
	else if (status == EINVAL && op == CREATE)
		error("the value specified by attribute is invalid");
	else if (status == EINVAL && op == JOIN)
		error("The value specified by the thread is not joinable");
	else if (status == ESRCH)
		error("No thread could be found corresponding to that");
	else if (status == EDEADLK)
		error("A deadlokc was detected or thread specifies the calling thread ");
}

static void	handle_mutex_error(int status, t_mutexOps op)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (op == LOCK || op == UNLOCK))
		error("The value specified by mutex is invalid");
	else if (status == EINVAL && op == INIT)
		error("the value specified by attr is invalid");
	else if (status == EDEADLK)
		error("A deadlock would occure if the thread blocked waiting for mutex.");
	else if (status == EPERM)
		error("the current thread does not hold the lock on mutex");
	else if (status == ENOMEM)
		error("The process cannot allocate enough memory to create another mutex");
	else if (status == EBUSY)
		error("Mutex is locked");
}

void	thread_handler(pthread_t *thread, void *(*fct)(void *), void *data,
		t_mutexOps op)
{
	if (op == CREATE)
		handle_thread_error(pthread_create(thread, NULL, fct, data), op);
	else if (op == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), op);
}

void	mutex_handler(pthread_mutex_t *mutex, t_mutexOps op)
{
	if (op == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), op);
	else if (op == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), op);
	else if (op == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), op);
	else if (op == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), op);
	else
		error(MUTEX_OP);
}

void	increase_threads(pthread_mutex_t *mutex, long *value)
{
	mutex_handler(mutex, LOCK);
	(*value)++;
	mutex_handler(mutex, UNLOCK);
}
