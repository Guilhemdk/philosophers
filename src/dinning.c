#include "../includes/philo.h"

void	*dinner_simulation(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->program);

	return (NULL);
}

void	start_dinner(t_program *program)
{
	int i;

	i = -1;
	if(program->max_eat_count == 0)
		return ;
	else if(program->nbr_of_philos == 1)
		;
	else
		while(++i < program->nbr_of_philos)
			thread_handler(&program->philo[i].thread_id, dinner_simulation, &program->philo[i], CREATE);
	mutex_set_int(&program->read_lock, &program->start_flag, 1);
}
