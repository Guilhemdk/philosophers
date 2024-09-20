#include "../inc/philo.h"

int error(char *message)
{
    ft_putendl_fd(message, 2);
    exit(1);
}

int free_and_error(t_program *program)
{
	int i;

	i = 0;
	if (program)
	{
		while(program->philo)
			free(&program->philo[i++]);
		free(program);
	}
}
