#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include "macros.h"
# include <sys/time.h>
# include <unistd.h>

struct s_program;

typedef struct s_philo
{
    pthread_t   thread;
    int         id;
    int         eating;
    int meals_eaten;
    size_t last_meal;
    int *dead;
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *write_lock;
    pthread_mutex_t *dead_lock;
    pthread_mutex_t *meal_lock;
}       t_philo;

typedef struct s_program
{
    int dead_flag;
    int nbr_of_philos;
    size_t start_time;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t max_eat_count;
    pthread_mutex_t dead_lock;
    pthread_mutex_t write_lock;
    pthread_mutex_t meal_lock;
    t_philo     *philo;
}               t_program;

int ft_isnbr(char *str);
int ft_atoi(char *str);

int error(char *message);
int ft_putendl_fd(char *msg, int fd);
int ft_strlen(char *str);
#endif
