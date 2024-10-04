#include "../includes/philo.h"

void	wait_all_threads(t_program *program)
{
	while(!mutex_get_int(&program->read_lock, &program->start_flag))
		;
}

long	get_time(void)
{
	struct timeval time;

	if(gettimeofday(&time, NULL))
		error(TIME_ERR);
	return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
	return (2);
}

void	ft_usleep(long usec, t_program *program)
{
	long start;

	start = get_time();
	while(get_time() - start < usec)
	{
		if(end_of_simulation(program))
			break ;
		usleep(usec / 10);
	}
}

int end_of_simulation(t_program *program)
{
	return (mutex_get_int(&program->read_lock, &program->end_flag));
}
