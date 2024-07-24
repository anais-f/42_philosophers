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

static int	init_fork(size_t nb_philo, t_tfork *tfork)
{
	size_t	i;

	i = 0;
	while (i < nb_philo)
	{
		tfork[i].n_fork = i + 1;
		tfork[i].fork_is_busy = false;
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

static void	init_param(char **argv, t_param *param)
{
	param->time_to_die = ft_pos_atoi(argv[2]);
	param->time_to_eat = ft_pos_atoi(argv[3]);
	param->time_to_sleep = ft_pos_atoi(argv[4]);
	if (argv[5])
		param->nb_must_eat = ft_pos_atoi(argv[5]);
	else
		param->nb_must_eat = 0;
}

static int	init_mutex_philo(t_simulation *simulation, size_t count)
{
	size_t	i;

	i = count;
	simulation->philo[i].die_or_fed = &simulation->simul_to_stop;
	simulation->philo[i].mutex_start_and_end = &simulation->mutex_start_and_end;
	simulation->philo[i].mutex_print = &simulation->mutex_print;
	if (pthread_mutex_init(&simulation->philo[i].mutex_meal, NULL) != 0)
	{
		while (i--)
		{
			if (pthread_mutex_destroy(&simulation->philo[i].mutex_meal) != 0)
				return (ERROR_DESTROY_MUTEX);
		}
		return (ERROR_INIT_MUTEX);
	}
	return (EXIT_SUCCESS);
}

int	init_philo(size_t nb_philo, t_simulation *simulation)
{
	size_t	i;
	size_t	j;
	int		result;

	i = 0;
	j = 1;
	while (i < nb_philo)
	{
		simulation->philo[i].n_philo = j;
		simulation->philo[i].right_fork = &simulation->tfork[i];
		if (j < nb_philo)
			simulation->philo[i].left_fork = &simulation->tfork[i + 1];
		else if (j == nb_philo)
			simulation->philo[i].left_fork = &simulation->tfork[0];
		simulation->philo[i].param = simulation->param;
		result = init_mutex_philo(simulation, i);
		if (result != 0)
			return (get_error_message(result));
		i++;
		j++;
	}
	return (EXIT_SUCCESS);
}

int	init_simulation(size_t nb_philo, char **argv, t_simulation *simulation)
{
	simulation->philo = malloc(sizeof(t_philo) * nb_philo);
	if (!simulation->philo)
		return (EXIT_FAILURE);
	memset(simulation->philo, 0, sizeof(t_philo) * nb_philo);
	simulation->tfork = malloc(sizeof(t_tfork) * nb_philo);
	if (!simulation->tfork)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&simulation->mutex_start_and_end, NULL) != 0)
		return (get_error_message(ERROR_INIT_MUTEX));
	if (pthread_mutex_init(&simulation->mutex_print, NULL) != 0)
		return (get_error_message(ERROR_INIT_MUTEX));
	init_param(argv, &simulation->param);
	if (init_fork(nb_philo, simulation->tfork) != 0)
		return (EXIT_FAILURE);
	init_philo(nb_philo, simulation);
	simulation->simul_to_stop = false;
	return (EXIT_SUCCESS);
}
