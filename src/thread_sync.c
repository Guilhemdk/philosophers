#include "../includes/philo.h"

void	wait_all_threads(t_program *program)
{
	while(!mutex_get_int(&program->read_lock, &program->start_flag))
		;
}

size_t	get_time(t_time_code time_code)
{
	struct timeval time;

	if(gettimeofday(&time, NULL))
		error(TIME_ERR);
	if (time_code == SECOND)
		return (time.tv_sec + time.tv_usec / 1e6);
	else if (time_code == MILLISECOND)
		return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((time.tv_sec * 1e6) + time.tv_usec);
	else
		error(TIME_ERR);
	return (2);
}


abcdef
