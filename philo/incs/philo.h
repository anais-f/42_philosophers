/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:29:13 by anfichet          #+#    #+#             */
/*   Updated: 2024/04/15 17:29:13 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h> //memset
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/time.h>

# define THINK  "is thinking"
# define FORK   "has taken a fork"
# define EAT    "is eating"
# define SLEEP  "is sleeping"
# define DIE    "died"

typedef enum s_error
{
	ERROR_INIT_MUTEX = 3,
	ERROR_DESTROY_MUTEX,
	ERROR_THREAD,

}   t_error;

typedef struct s_fork
{
	size_t          n_fork;
	bool            fork_is_busy;
	pthread_mutex_t mutex_fork;
}   t_tfork;

typedef struct s_param
{
	size_t  time_to_die;
	size_t  time_to_eat;
	size_t  time_to_sleep;
	size_t  nb_must_eat;
}   t_param;

typedef struct s_philo
{
	pthread_t       philo_id;
	size_t          n_philo;
	t_tfork         *right_fork;
	t_tfork         *left_fork;
	bool            right_fork_taken;
	bool            left_fork_taken;
	bool            *die_or_fed;
	size_t          last_meal;
	size_t          nb_meal;
	size_t          *start_time;
	pthread_mutex_t *mutex_start_and_end;
	pthread_mutex_t *mutex_print;
	pthread_mutex_t mutex_meal;
	t_param         param;
}   t_philo;

typedef struct s_simulation
{
	t_philo         *philo;
	t_tfork         *tfork;
	bool            simul_to_stop;
	pthread_mutex_t mutex_start_and_end;
	pthread_mutex_t mutex_print;
	t_param         param;
}   t_simulation;


/* Routine */
void    *routine(void *arg);
void    monitoring_philo(t_simulation *simulation, t_philo *philo, int nb_philo);

/* Time */
size_t  get_timestamp_print(t_philo *philo);
void    get_time_last_meal(t_philo *philo);
size_t  get_actual_time(void);
/* Initialization */
int    init_philo(size_t nb_philo, t_simulation * simulation);

int     init_fork(size_t nb_philo, t_tfork *fork);
int    init_param(char **argv, t_param *param);
int     init_simulation(size_t nb_philo, char **argv, t_simulation *simulation);
/* Utils */
int     ft_atoi(const char *str);

int     check_input(int argc, char **argv);
int     get_error_message(int code);
bool    get_simul_status(t_philo *philo);
int get_status_message(t_philo *philo, char *status);
void    ft_usleep(size_t time);

void free_struct(t_simulation *simulation, size_t nb_philo);

#endif
