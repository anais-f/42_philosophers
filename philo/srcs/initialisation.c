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
	pthread_mutex_t mutex_start_and_end;

	//malloc des tableaux
	simulation->philo = malloc(sizeof(t_philo) * nb_philo);
	if (!simulation->philo)
		return (EXIT_FAILURE);
	simulation->tfork = malloc(sizeof(t_tfork) * nb_philo);
	if (!simulation->tfork)
		return (EXIT_FAILURE);

	//initialisation des structures
	if (pthread_mutex_init(&mutex_start_and_end, NULL) != 0)
		return (get_error_message(ERROR_INIT_MUTEX));
	simulation->mutex_start_and_end = mutex_start_and_end;

	init_arg(argv, &simulation->param);
	if (init_fork(nb_philo, simulation->tfork) != 0)
		return (EXIT_FAILURE);
	init_philo(nb_philo, simulation);

	return (EXIT_SUCCESS);
}

int	init_fork(size_t nb_philo, t_tfork *tfork)
{
	size_t	i;

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
					return (get_error_message(ERROR_DESTROY_MUTEX));
			}
			return (get_error_message(ERROR_INIT_MUTEX));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

//possible de la remettre en void si pas de mutex declare
int	init_philo(size_t nb_philo, t_simulation *simulation)
{
	size_t	i;
	size_t	j;

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
		simulation->philo[i].right_fork_taken = false;
		simulation->philo[i].left_fork_taken = false;
		simulation->philo[i].die_or_fed = false;
		simulation->philo[i].last_meal = 0;
		simulation->philo[i].nb_meal = 0;
		simulation->philo[i].start_time = 0;
		simulation->philo[i].mutex_start_and_end = &simulation->mutex_start_and_end;
		simulation->philo[i].param = simulation->param;
		i++;
		j++;
	}
	return (EXIT_SUCCESS);
}

void    init_arg(char **argv, t_param *param)
{
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		param->nb_must_eat = ft_atoi(argv[5]);
	else
		param->nb_must_eat = 0;

	//printf("to die = %ld, to eat = %ld, to sleep = %ld\n", param->time_to_die, param->time_to_eat, param->time_to_sleep);

}
