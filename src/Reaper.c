#include "../includes/philo.h"

int		all_threads_ready(pthread_mutex_t *mutex, long *threads, long philo_nbr)
{
	int checker;

	checker = 0;
	mutex_handler(mutex, LOCK);
	if(*threads == philo_nbr)
		checker = 1;
	mutex_handler(mutex, UNLOCK);
	return (checker);
}

static int philo_died(t_philo * philo)
{
	long	elapsed;
	long	t_to_die;

	if (mutex_get_int(&philo->philo_lock, &philo->full))
		return (0);
	elapsed = get_time(MILLISECONDS) -
		mutex_get_long(&philo->philo_lock, &philo->last_meal);
	t_to_die = philo->program->time_to_die / 1e3;
	if(elapsed > t_to_die)
	{
		write_status(DIED, philo);
		return (1);
	}
	return (0);
}

void	*fk_em_up(void *data)
{
	int i;
	t_program *program;

	program = (t_program *)data;

	while(!all_threads_ready(&program->program_lock,
				&program->threads_running,
				program->nbr_of_philos))
		;
	while(!end_of_simulation(program))
	{
		i = -1;
		while (++i < program->nbr_of_philos
				&& !end_of_simulation(program))
		{
			if (philo_died(program->philo + i))
			{
				mutex_set_int(&program->program_lock,
						&program->end_flag, 1);
				write_status(DIED, program->philo + i);
			}
		}
	}
	return (NULL);
}
