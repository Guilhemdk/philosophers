#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include "macros.h"
# include <sys/time.h>
# include <unistd.h>
# include "philo_structs.h"

int ft_isnbr(char *str);
int ft_atoi(char *str);
void	*safe_malloc(size_t bytes);

void error(char *message);
void ft_putendl_fd(char *msg, int fd);
int ft_strlen(char *str);

void init_program(t_program *program);

void mutex_handler(pthread_mutex_t *mutex, t_mutexOps op);
void thread_handler(pthread_t *thread, void *(*fct)(void *), void *data, t_mutexOps op);
int end_of_simulation(t_program *program);

int mutex_get_int(pthread_mutex_t *mutex, int *value);
void mutex_set_int(pthread_mutex_t *mutex, int *dest, int value);
size_t mutex_get_long(pthread_mutex_t *mutex, long *value);
void mutex_set_long(pthread_mutex_t *mutex, long *dest, long value);

void	wait_all_threads(t_program *program);

long	get_time(void);
void	ft_usleep(long usec, t_program *program);
void	write_status(t_status status, t_philo *philo);
void		increase_threads(pthread_mutex_t *mutex, long *value);
int			all_all_threads_ready(pthread_mutex_t *mutex, long *threads, long philo_nbr);
void		*fk_em_up(void *data);
void		clean_up(t_program *program);
void		think(t_philo *philo, int pre_synchronizer);
void		desynchronize_philos(t_philo *philo);

void		start_dinner(t_program *program);

#endif
