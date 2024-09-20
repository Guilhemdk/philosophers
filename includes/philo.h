#ifndef PHILO_H
# define PHILO_H

abcdef

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include "macros.h"
# include <sys/time.h>
# include <unistd.h>
# include "philo_structs.h"

int ft_isnbr(char *str);
int ft_atoi(char *str);
void	*safe_malloc(size_t bytes);

int error(char *message);
int ft_putendl_fd(char *msg, int fd);
int ft_strlen(char *str);

void init_program(t_program *program);

void mutex_handler(pthread_mutex_t *mutex, t_mutexOps op);
void thread_handler(pthread_t *thread, void *(*fct)(void *), void *data, t_mutexOps op);

int mutex_get_int(pthread_mutex_t *mutex, int *value);
void mutex_set_int(pthread_mutex_t *mutex, int *dest, int value);
size_t mutex_get_size_t(pthread_mutex_t *mutex, size_t *value);
void mutex_set_size_t(pthread_mutex_t *mutex, size_t *dest, size_t value);

void	wait_all_threads(t_program *program);

size_t	get_time(t_time_code time_code);

#endif
