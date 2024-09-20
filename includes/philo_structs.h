#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H

#include "philo.h"

struct s_program;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time_code;

typedef enum e_mutexOps
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN
}			t_mutexOps;

typedef struct s_fork
{
	pthread_mutex_t fork;
	size_t			fork_id;
}		t_fork;

typedef struct s_philo
{
    pthread_t   thread_id;
    int         id;
    int         eating;
    int meals_eaten;
    size_t last_meal;
    int *dead;
	struct s_program *program;
    t_fork		*first_fork;
    t_fork		*second_fork;
    pthread_mutex_t *write_lock;
    pthread_mutex_t *dead_lock;
    pthread_mutex_t *meal_lock;
}       t_philo;

typedef struct s_program
{
    int dead_flag;
	int start_flag;
    int nbr_of_philos;
    size_t start_time;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    long	max_eat_count;
	pthread_mutex_t read_lock;
    pthread_mutex_t dead_lock;
    pthread_mutex_t write_lock;
    pthread_mutex_t meal_lock;
	t_fork		*forks;
    t_philo     *philo;
}               t_program;

#endif
