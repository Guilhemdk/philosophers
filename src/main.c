#include "../inc/philo.h"

void check_args(int argc, char **argv, t_program *program)
{
    int i;

    i = 0;
    while(++i < 4)
        if(!ft_isnbr(argv[i]) || ft_atoi(argv[i]) <= 0)
            error(INVALID_ARG);
    program->nbr_of_philos = ft_atoi(argv[1]);
    program->time_to_die = ft_atoi(argv[2]);
    program->time_to_eat = ft_atoi(argv[3]);
    program->time_to_sleep = ft_atoi(argv[4]);
    if(argv[5])
    {
        if(!ft_isnbr(argv[i]) || ft_atoi(argv[i]) < 0)
            error(INVALID_ARG);
        else
            program->max_eat_count = ft_atoi(argv[5]);
    }
    program->dead_flag = 0;


}

void mutex_init(t_program *program)
{
    pthread_mutex_init(&program->dead_lock, NULL);
    pthread_mutex_init(&program->write_lock, NULL);
    pthread_mutex_init(&program->meal_lock, NULL);
}

int main(int argc, char **argv)
{
    t_program program;
    if (argc != 5 && argc != 6)
        error(INVALID_ARG_NBR);
    program.philo = malloc(sizeof(t_philo) * program.nbr_of_philos);
    if(!program.philo)
        return (NULL);
    mutex_init(&program);
}

