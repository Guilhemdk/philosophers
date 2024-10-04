#include "../includes/philo.h"

static void	assign_forks(t_philo *philo, t_fork *fork, int i)
{
	int	total_philos;

	total_philos = philo->program->nbr_of_philos;
	philo->first_fork = &fork[(i + 1) % total_philos];
	philo->second_fork = &fork[i];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &fork[i];
		philo->second_fork = &fork[(i + 1) % total_philos];
	}
}

static void	init_philo(t_program *program)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < program->nbr_of_philos)
	{
		philo = program->philo + i;
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->program = program;
		philo->full = 0;
		mutex_handler(&philo->philo_lock, INIT);
		assign_forks(philo, program->forks, i);
	}
}

void	init_program(t_program *program)
{
	int	i;

	i = -1;
	program->threads_running = 0;
	program->all_threads_ready = 0;
	program->end_flag = 0;
	program->philo = safe_malloc(sizeof(t_philo) * program->nbr_of_philos);
	program->forks = safe_malloc(sizeof(t_fork) * program->nbr_of_philos);
	mutex_handler(&program->program_lock, INIT);
	mutex_handler(&program->write_lock, INIT);
	while (++i < program->nbr_of_philos)
	{
		mutex_handler(&program->forks[i].fork, INIT);
		program->forks[i].fork_id = i;
	}
	init_philo(program);
}

void	desynchronize_philos(t_philo *philo)
{
	if (philo->program->nbr_of_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(3e4, philo->program);
	}
	else if (philo->id % 2 != 0)
		think(philo, 1);
}
