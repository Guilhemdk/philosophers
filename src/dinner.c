#include "../includes/philo.h"

void	think(t_philo *philo, int pre_synchronizer)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_synchronizer)
		write_status(THINKING, philo);
	if (philo->program->nbr_of_philos % 2 == 0)
		return ;
	t_eat = philo->program->time_to_eat;
	t_sleep = philo->program->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(t_think * 0.42, philo->program);
}

static void	eat(t_philo *philo)
{
	mutex_handler(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	mutex_handler(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	mutex_set_long(&philo->philo_lock, &philo->last_meal,
		get_time(MILLISECONDS));
	philo->meals_eaten++;
	write_status(EATING, philo);
	ft_usleep(philo->program->time_to_eat, philo->program);
	if ((philo->program->max_eat_count >= 0)
		&& philo->meals_eaten == philo->program->max_eat_count)
		mutex_set_int(&philo->philo_lock, &philo->full, 1);
	mutex_handler(&philo->first_fork->fork, UNLOCK);
	mutex_handler(&philo->second_fork->fork, UNLOCK);
}

void	*philo_hermite(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->program);
	mutex_set_long(&philo->philo_lock, &philo->last_meal,
		get_time(MILLISECONDS));
	increase_threads(&philo->program->program_lock,
		&philo->program->threads_running);
	write_status(TAKE_FIRST_FORK, philo);
	while (!end_of_simulation(philo->program))
		usleep(200);
	return (NULL);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->program);
	mutex_set_long(&philo->philo_lock, &philo->last_meal,
		get_time(MILLISECONDS));
	increase_threads(&philo->program->program_lock,
		&philo->program->threads_running);
	desynchronize_philos(philo);
	while (!(end_of_simulation(philo->program)))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		ft_usleep(philo->program->time_to_sleep, philo->program);
		think(philo, 0);
	}
	return (NULL);
}

void	start_dinner(t_program *program)
{
	int	i;

	i = -1;
	if (program->max_eat_count == 0)
		return ;
	else if (program->nbr_of_philos == 1)
		thread_handler(&program->philo[0].thread_id, philo_hermite,
			&program->philo[0], CREATE);
	else
		while (++i < program->nbr_of_philos)
			thread_handler(&program->philo[i].thread_id, dinner_simulation,
				&program->philo[i], CREATE);
	thread_handler(&program->the_reaper, fk_em_up, program, CREATE);
	program->start_time = get_time(MILLISECONDS);
	mutex_set_int(&program->program_lock, &program->all_threads_ready, 1);
	i = -1;
	while (++i < program->nbr_of_philos)
		thread_handler(&program->philo[i].thread_id, NULL, NULL, JOIN);
	mutex_set_int(&program->program_lock, &program->end_flag, 1);
	thread_handler(&program->the_reaper, NULL, NULL, JOIN);
}
