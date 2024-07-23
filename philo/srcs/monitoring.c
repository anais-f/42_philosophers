/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:14:41 by anfichet          #+#    #+#             */
/*   Updated: 2024/07/22 15:14:41 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    wait_start_monitoring(t_philo *philo, int nb_philo)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_lock(&philo[i].mutex_meal);
		if (philo[i].last_meal > 0)
		{
			pthread_mutex_unlock(&philo[i].mutex_meal);
			i++;
		}
		else
			pthread_mutex_unlock(&philo[i].mutex_meal);
	}
}

/* check if philo is die or has eaten enough */
void    monitoring_philo(t_simulation *simulation, t_philo *philo, int nb_philo)
{
	size_t  t_last_meal;
	size_t  actual_time;
	size_t  meal;
	int i;
	int check_meal;

	check_meal = 0;
	wait_start_monitoring(philo, nb_philo);
	while (1)
	{
		i = 0;
		while (i < nb_philo)
		{
			actual_time = get_actual_time();
			pthread_mutex_lock(&philo[i].mutex_meal);
			t_last_meal = actual_time - philo[i].last_meal;
			meal = philo[i].nb_meal;
			pthread_mutex_unlock(&philo[i].mutex_meal);
			if (meal >= simulation->param.nb_must_eat)
				check_meal++;
			if (t_last_meal >= philo->param.time_to_die || (simulation->param.nb_must_eat > 0 && check_meal == nb_philo))
			{
				pthread_mutex_lock(&simulation->mutex_start_and_end);
				simulation->simul_to_stop = true;
				pthread_mutex_unlock(&simulation->mutex_start_and_end);
				if (t_last_meal >= philo->param.time_to_die)
				{
					pthread_mutex_lock(&simulation->mutex_print);
					printf("%ld %zu died\n", get_timestamp_print(philo), philo[i].n_philo);
					pthread_mutex_unlock(&simulation->mutex_print);
				}
				return;
			}
			i++;
			usleep(100);
		}
	}
}
