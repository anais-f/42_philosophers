/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:14:41 by anfichet          #+#    #+#             */
/*   Updated: 2024/07/23 18:20:04 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void wait_start_monitoring(t_philo *philo, int nb_philo)
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

static void time_to_stop(t_simulation *simulation, t_philo *philo, \
			size_t t_last_meal)
{
	pthread_mutex_lock(&simulation->mutex_start_and_end);
	simulation->simul_to_stop = true;
	pthread_mutex_unlock(&simulation->mutex_start_and_end);
	if (t_last_meal >= philo->param.time_to_die)
	{
		pthread_mutex_lock(philo->mutex_print);
		printf("%ld %zu %s\n", print_time(philo), philo->n_philo, DIE);
		pthread_mutex_unlock(philo->mutex_print);
	}
	return ;
}

/* check if philo is die or has eaten enough */
void    monitoring_philo(t_simulation *simulation, t_philo *philo, int nb_philo)
{
	size_t  t_last_meal;
	size_t  actual_time;
	int     i;
	int     check_meal;

	wait_start_monitoring(philo, nb_philo);
	while (1)
	{
		i = 0;
		check_meal = 0;
		while (i < nb_philo)
		{
			actual_time = get_actual_time();
			pthread_mutex_lock(&philo[i].mutex_meal);
			t_last_meal = actual_time - philo[i].last_meal;
			pthread_mutex_unlock(&philo[i].mutex_meal);
			if (philo[i].nb_meal >= simulation->param.nb_must_eat)
				check_meal++;
			if (t_last_meal >= philo->param.time_to_die || \
				(simulation->param.nb_must_eat > 0 && check_meal == nb_philo))
				return (time_to_stop(simulation, &philo[i], t_last_meal));
			i++;
			usleep(100);
		}
	}
}
