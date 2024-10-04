#include "../includes/philo.h"

void	clean_up(t_program *program)
{
	t_philo	*philo;
	t_fork	*fork;
	int		i;

	i = -1;
	while (++i < program->nbr_of_philos)
	{
		fork = program->forks + i;
		mutex_handler(&fork->fork, DESTROY);
	}
	i = -1;
	while (++i < program->nbr_of_philos)
	{
		philo = program->philo + i;
		mutex_handler(&philo->philo_lock, DESTROY);
	}
	mutex_handler(&program->program_lock, DESTROY);
	mutex_handler(&program->write_lock, DESTROY);
	free(program->forks);
	free(program->philo);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	if (s)
	{
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
	}
}

void	error(char *message)
{
	ft_putendl_fd(message, 2);
	exit(1);
}

int	free_and_error(t_program *program)
{
	int	i;

	i = 0;
	if (program)
	{
		while (program->philo)
			free(&program->philo[i++]);
		free(program);
	}
	return (0);
}
