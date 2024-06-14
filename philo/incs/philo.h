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


typedef struct s_fork
{
	bool            fork;
	pthread_mutex_t mutex_fork;
}   t_fork;


typedef struct s_philo
{
	pthread_t  philo_id;
	int        n_philo;
	t_fork     *fork_right;
	t_fork     *fork_left;
}   t_philo;



void    *routine(void *arg);
void    init_philo(int nb_philo, t_philo *philo);
int    init_fork(int nb_philo, t_fork *fork);

/* Utils */
int	ft_atoi(const char *str);
int check_input(int argc, char **argv);

#endif
