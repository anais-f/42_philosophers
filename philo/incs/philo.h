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
	bool            fork;
	pthread_mutex_t mutex_fork;
}   t_tfork;

typedef struct s_param
{
	long    start_time;
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
	t_param     param;
}   t_philo;

typedef struct s_simulation
{
	t_philo *philo;
	t_tfork *tfork;
	t_param param;
}   t_simulation;



void    *routine(void *arg);
long    get_timestamp(t_philo *philo);

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
