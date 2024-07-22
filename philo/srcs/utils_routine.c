/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:16:17 by anfichet          #+#    #+#             */
/*   Updated: 2024/07/22 14:16:17 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool    get_simul_status(t_philo *philo)
{
	bool    status;
	pthread_mutex_lock(philo->mutex_start_and_end);
	status = *philo->die_or_fed;
	pthread_mutex_unlock(philo->mutex_start_and_end);
	return (status);
}

int get_status_message(t_philo *philo, char *status)
{
	bool    state_print;
	pthread_mutex_lock(philo->mutex_print);
	pthread_mutex_lock(philo->mutex_start_and_end);
	state_print = *philo->die_or_fed;
	pthread_mutex_unlock(philo->mutex_start_and_end);
	if (state_print == false)
	{
		printf("%ld %zu %s\n", get_timestamp_print(philo), philo->n_philo, status);
		pthread_mutex_unlock(philo->mutex_print);
	}
	else
		pthread_mutex_unlock(philo->mutex_print);
	return (EXIT_SUCCESS);
}

void    ft_usleep(size_t time)
{
	struct timeval  tv;
	size_t actual_time;
	size_t waited;
	size_t start_time;

	start_time = gettimeofday(&tv, NULL);
	usleep(time * 0.8);
	actual_time = gettimeofday(&tv, NULL);
	waited = actual_time - start_time;
	while (waited < time)
	{
		usleep(50);
		actual_time = gettimeofday(&tv, NULL);
		waited = actual_time - start_time;
//		if (waited >= time)
//			break;
	}

}

/* usleep -> temps en micro seconde  nos param = temps en millisecondes
 * milli * 1000 pour passer en micro
 * micro / 1000 pour passer en milli */