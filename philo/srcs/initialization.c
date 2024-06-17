/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:36:29 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/17 16:36:29 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_simulation(size_t nb_philo, char **argv, t_param param)
{
	init_arg(argv, &data_arg);
	printf("main timestamp start = %ld\n", data_arg.start_time);
	if (init_fork(nb_philo, tfork) != 0) {
		return (EXIT_FAILURE);
	}
	init_philo(nb_philo, philo, tfork, &data_arg);
}

int    init_fork(size_t nb_philo, t_tfork *tfork)
{
	size_t i;

	i = 0;
	while (i < nb_philo)
	{
		tfork[i].n_fork = i + 1;
		tfork[i].fork = false;
		if (pthread_mutex_init(&tfork[i].mutex_fork, NULL) != 0)
		{
			while (i--)
			{
				if (pthread_mutex_destroy(&tfork[i].mutex_fork) != 0)
					get_error_message(ERROR_DESTROY_MUTEX);
			}
			get_error_message(ERROR_INIT_MUTEX);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void    init_philo(size_t nb_philo, t_philo *philo, t_tfork *tfork, t_param param)
{
	size_t i;
	size_t j;

	i = 0;
	j = 1;
//	printf("nb philo = %zu\n", nb_philo);
	while (i < nb_philo)
	{
		philo[i].n_philo = j;
//		printf("philo n %zu\n", philo[i].n_philo);
		philo[i].f_right = &tfork[i];
		philo[i].param = param;
		if (j < nb_philo)
			philo[i].f_left = philo[i + 1].f_right;
		else if (j == nb_philo)
			philo[nb_philo].f_left = philo[0].f_right;
		i++;
		j++;
	}
}

void    init_arg(char **argv, t_param param)
{
	struct timeval tv;
	(void)argv;

	gettimeofday(&tv, NULL);
	param.start_time = (tv.tv_sec *1000 + tv.tv_usec / 1000);
	printf("timestamp start = %ld\n", param.start_time);
}
