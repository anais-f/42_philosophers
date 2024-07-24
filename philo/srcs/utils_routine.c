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

bool	get_simul_status(t_philo *philo)
{
	bool	status;

	pthread_mutex_lock(philo->mutex_start_and_end);
	status = *philo->die_or_fed;
	pthread_mutex_unlock(philo->mutex_start_and_end);
	return (status);
}

int	get_status_message(t_philo *philo, char *status)
{
	bool	state_print;

	pthread_mutex_lock(philo->mutex_print);
	pthread_mutex_lock(philo->mutex_start_and_end);
	state_print = *philo->die_or_fed;
	pthread_mutex_unlock(philo->mutex_start_and_end);
	if (state_print == ACTIVE)
	{
		printf("%ld %zu %s\n", print_time(philo), philo->n_philo, status);
		pthread_mutex_unlock(philo->mutex_print);
	}
	else
		pthread_mutex_unlock(philo->mutex_print);
	return (EXIT_SUCCESS);
}

void	ft_usleep(size_t time, t_philo *philo)
{
	struct timeval	tv;
	size_t			actual_time;
	size_t			waited;
	size_t			start_time;

	gettimeofday(&tv, NULL);
	start_time = (tv.tv_sec * 1000000 + tv.tv_usec);
	actual_time = (tv.tv_sec * 1000000 + tv.tv_usec);
	waited = actual_time - start_time;
	while (waited < time)
	{
		if (get_simul_status(philo) == UNACTIVE)
			return ;
		usleep(150);
		gettimeofday(&tv, NULL);
		actual_time = (tv.tv_sec * 1000000 + tv.tv_usec);
		waited = actual_time - start_time;
	}
}
