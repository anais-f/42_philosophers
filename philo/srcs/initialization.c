/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:36:29 by anfichet          #+#    #+#             */
/*   Updated: 2024/07/12 13:53:14 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_simulation(size_t nb_philo, char **argv, t_simulation *simulation)
{
	//malloc des tableaux
	simulation->philo = malloc(sizeof(t_philo) * nb_philo);
	if (!simulation->philo)
		return (EXIT_FAILURE);
	simulation->tfork = malloc(sizeof(t_tfork) * nb_philo);
	if (!simulation->tfork)
		return (EXIT_FAILURE);

	//initialisation des structures
	init_arg(argv, &simulation->param);
	if (init_fork(nb_philo, simulation->tfork) != 0)
		return (EXIT_FAILURE);
	init_philo(nb_philo, simulation->philo, simulation->tfork, \
	&simulation->param);

	return (EXIT_SUCCESS);
}

int	init_fork(size_t nb_philo, t_tfork *tfork)
{
	size_t	i;

	i = 0;
	while (i < nb_philo)
	{
		tfork[i].n_fork = i + 1;
		tfork[i].fork_taken = false;
		if (pthread_mutex_init(&tfork[i].mutex_fork, NULL) != 0)
		{
			while (i--)
			{
				if (pthread_mutex_destroy(&tfork[i].mutex_fork) != 0)
					return (get_error_message(ERROR_DESTROY_MUTEX));
			}
			return (get_error_message(ERROR_INIT_MUTEX));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	init_philo(size_t nb_philo, t_philo *philo, t_tfork *tfork, \
		t_param *param)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	printf("nb philo = %zu\n", nb_philo);
	while (i < nb_philo)
	{
		philo[i].n_philo = j;
		//printf("philo n %zu et i= %ld et j =%ld\n", philo[i].n_philo, i, j);
		philo[i].param = *param;
		philo[i].f_right = &tfork[i];
		philo[i].last_meal = 0;
		philo[i].philo_is_die = false;
		if (j < nb_philo)
			philo[i].f_left = &tfork[i + 1];
		else if (j == nb_philo)
			philo[i].f_left = &tfork[0];

		i++;
		j++;
	}
}

void    init_arg(char **argv, t_param *param)
{
	struct timeval tv;

	/****************************************************/
	gettimeofday(&tv, NULL);
	param->start_time = (tv.tv_sec *1000 + tv.tv_usec / 1000);
	printf("timestamp start = %ld\n", param->start_time);
	/**********************************************/

	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		param->nb_must_eat = ft_atoi(argv[5]);
	else
		param->nb_must_eat = 0;

	//printf("to die = %ld, to eat = %ld, to sleep = %ld\n", param->time_to_die, param->time_to_eat, param->time_to_sleep);

}
