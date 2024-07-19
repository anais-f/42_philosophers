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

typedef enum s_error
{
	ERROR_INIT_MUTEX = 3,
	ERROR_DESTROY_MUTEX,
	ERROR_THREAD,

}   t_error;

typedef struct s_fork
{
	size_t          n_fork;
	bool            fork_taken;
	pthread_mutex_t mutex_fork;
}   t_tfork;

typedef struct s_param
{
	size_t  start_time;
	size_t  time_to_die;
	size_t  time_to_eat;
	size_t  time_to_sleep;
	size_t  nb_must_eat;
}   t_param;

typedef struct s_philo
{
	pthread_t   philo_id;
	size_t      n_philo;
	t_tfork     *f_right;
	t_tfork     *f_left;
	size_t      last_meal;
	size_t      nb_meal;
	bool        philo_is_die; //pour verifier si un est mort pour stop tout le reste et de print - A MUTEX
	t_param     param;
}   t_philo;

typedef struct s_simulation
{
	t_philo *philo;
	t_tfork *tfork;
	t_param param;
}   t_simulation;


/* Routine */
void    *routine(void *arg);
void    monitoring_philo(t_philo *philo);

/* Time */
size_t  get_timestamp_print(t_philo *philo);
void    get_time_last_meal(t_philo *philo);
size_t  get_actual_time(t_philo *philo);

/* Initialization */
void    init_philo(size_t nb_philo, t_philo *philo, t_tfork *tfork, t_param *param);
int     init_fork(size_t nb_philo, t_tfork *fork);
void    init_arg(char **argv, t_param *param);
int     init_simulation(size_t nb_philo, char **argv, t_simulation *simulation);

/* Utils */
int     ft_atoi(const char *str);
int     check_input(int argc, char **argv);
int     get_error_message(int code);

#endif
