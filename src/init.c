#include "../includes/philo.h"

static void assign_forks(t_philo *philo, t_fork *fork, int i)
{
	int total_philos;

	total_philos = philo->program->nbr_of_philos;
	if (philo->id % 2)
	{
		philo->first_fork = &fork[i];
		philo->second_fork = &fork[(i + 1) % total_philos];
	}
}

static void init_philo(t_program *program)
{
	int		i;
	t_philo *philo;

	i = -1;
	while (++i < program->nbr_of_philos)
	{
		philo = program->philo + i;
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->program = program;
		assign_forks(philo, program->forks, i);
	}

}

void init_program(t_program *program)
{
	int i;

	i = -1;
	program->philo = safe_malloc(sizeof(t_philo) * program->nbr_of_philos);
	program->forks = safe_malloc(sizeof(t_fork) * program->nbr_of_philos);
	program->start_flag = 0;
	mutex_handler(&program->read_lock, INIT);
	while(++i < program->nbr_of_philos)
	{
		mutex_handler(&program->forks[i].fork, INIT);
		program->forks[i].fork_id = i;
	}
	init_philo(program);
}
