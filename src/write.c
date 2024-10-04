#include "../includes/philo.h"

void	write_status(t_status status, t_philo *philo)
{
	long elapsed;

	if(philo->full)
		return ;
	elapsed = get_time(MILLISECONDS);
	mutex_handler(&philo->program->write_lock, LOCK);
	if((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !end_of_simulation(philo->program))
		printf("\033[33m%-6ld philo%d has taken a new fork\n", elapsed, philo->id);
	else if(status == EATING && !end_of_simulation(philo->program))
		printf("\033[32m%-6ld philo%d is eating\n", elapsed, philo->id);
	else if(status == SLEEPING && !end_of_simulation(philo->program))
		printf("\033[35m%-6ld philo%d is sleeping\n", elapsed, philo->id);
	else if(status == THINKING && !end_of_simulation(philo->program))
		printf("%-6ld philo%d is thinking\n", elapsed, philo->id);
	else if(status == DIED	&& !end_of_simulation(philo->program))
		printf("\033[31m%-6ld philo%d died\n", elapsed, philo->id);
	mutex_handler(&philo->program->write_lock, UNLOCK);
}
