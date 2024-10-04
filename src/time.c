#include "../includes/philo.h"

void	wait_all_threads(t_program *program)
{
	while(!mutex_get_int(&program->program_lock, &program->all_threads_ready))
		;
}

long	get_time(t_timecode tcode)
{
	struct timeval time;

	if(gettimeofday(&time, NULL))
		error(TIME_ERR);
	if (tcode == MILLISECONDS)
		return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
	else if (tcode == MICROSECONDS)
		return ((time.tv_sec * 1e6) + (time.tv_usec));
	else
		error("wrong input gettime");
	return (2);
}

void	ft_usleep(long usec, t_program *program)
{
	long start;
	long elapsed;
	long rem;

	start = get_time(MICROSECONDS);
	while(get_time(MICROSECONDS) - start < usec)
	{
		if(end_of_simulation(program))
			break ;
		elapsed = get_time(MICROSECONDS) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
			while(get_time(MICROSECONDS) - start < usec)
				;
	}
}

int end_of_simulation(t_program *program)
{
	return (mutex_get_int(&program->program_lock, &program->end_flag));
}
