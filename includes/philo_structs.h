#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H

# include <pthread.h>

struct	s_program;

typedef enum e_timecode
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
}						t_timecode;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED
}						t_status;

typedef enum e_mutexOps
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
}						t_mutexOps;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	size_t				fork_id;
}						t_fork;

typedef struct s_philo
{
	pthread_t			thread_id;
	int					id;
	int					eating;
	int					meals_eaten;
	long				last_meal;
	int					full;
	struct s_program	*program;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_mutex_t		philo_lock;
}						t_philo;

typedef struct s_program
{
	int					end_flag;
	int					all_threads_ready;
	int					nbr_of_philos;
	long				threads_running;
	long				start_time;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				max_eat_count;
	pthread_t			the_reaper;
	pthread_mutex_t		program_lock;
	pthread_mutex_t		write_lock;
	t_fork				*forks;
	t_philo				*philo;
}						t_program;

#endif
