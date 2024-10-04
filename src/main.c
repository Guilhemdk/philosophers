#include "../includes/philo.h"

int	check_args(char **argv, t_program *program)
{
	int	i;

	i = 0;
	while (++i <= 4)
		if (!ft_isnbr(argv[i]) || ft_atoi(argv[i]) <= 0)
			return (0);
	program->nbr_of_philos = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]) * 1e3;
	program->time_to_eat = ft_atoi(argv[3]) * 1e3;
	program->time_to_sleep = ft_atoi(argv[4]) * 1e3;
	if (argv[5])
	{
		if (!ft_isnbr(argv[5]) || ft_atoi(argv[5]) < 0)
			return (0);
		else
			program->max_eat_count = ft_atoi(argv[5]);
	}
	else
		program->max_eat_count = -1;
	return (1);
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc != 5 && argc != 6)
	{
		error(INVALID_ARG_NBR);
	}
	if (!check_args(argv, &program))
		error(INVALID_ARG);
	init_program(&program);
	start_dinner(&program);
	clean_up(&program);
	return (0);
}
