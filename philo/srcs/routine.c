/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 00:32:20 by anfichet          #+#    #+#             */
/*   Updated: 2024/07/25 16:44:18 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_to_start_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_start_and_end);
	pthread_mutex_unlock(philo->mutex_start_and_end);
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal = *philo->start_time;
	pthread_mutex_unlock(&philo->mutex_meal);
	if (philo->n_philo % 2 == 0)
		usleep((philo->param.time_to_eat * 1000) / 2);
}

static void	get_fork(t_philo *philo)
{
	if (philo->right_fork_taken == false)
	{
		pthread_mutex_lock(&philo->right_fork->mutex_fork);
		if (philo->right_fork->fork_is_busy == false)
		{
			get_status_message(philo, FORK);
			philo->right_fork->fork_is_busy = true;
			philo->right_fork_taken = true;
		}
		pthread_mutex_unlock(&philo->right_fork->mutex_fork);
	}
	if (philo->left_fork_taken == false)
	{
		pthread_mutex_lock(&philo->left_fork->mutex_fork);
		if (philo->left_fork->fork_is_busy == false)
		{
			get_status_message(philo, FORK);
			philo->left_fork->fork_is_busy = true;
			philo->left_fork_taken = true;
		}
		pthread_mutex_unlock(&philo->left_fork->mutex_fork);
	}
}

static void	release_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex_fork);
	philo->right_fork->fork_is_busy = false;
	philo->right_fork_taken = false;
	pthread_mutex_unlock(&philo->right_fork->mutex_fork);
	pthread_mutex_lock(&philo->left_fork->mutex_fork);
	philo->left_fork->fork_is_busy = false;
	philo->left_fork_taken = false;
	pthread_mutex_unlock(&philo->left_fork->mutex_fork);
}

static void	time_to_eat(t_philo *philo)
{
	get_status_message(philo, EAT);
	pthread_mutex_lock(&philo->mutex_meal);
	get_time_last_meal(philo);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->mutex_meal);
	ft_usleep(philo->param.time_to_eat * 1000, philo);
	release_fork(philo);
	get_status_message(philo, SLEEP);
	ft_usleep(philo->param.time_to_sleep * 1000, philo);
	get_status_message(philo, THINK);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		j;

	philo = (t_philo *)arg;
	j = 0;
	wait_to_start_routine(philo);
	while (get_simul_status(philo) == ACTIVE)
	{
		if (j == 0)
			get_status_message(philo, THINK);
		while (philo->right_fork_taken == false \
				|| philo->left_fork_taken == false)
		{
			get_fork(philo);
			if (get_simul_status(philo) == UNACTIVE)
				return (NULL);
			usleep(100);
		}
		if (philo->right_fork_taken == true && philo->left_fork_taken == true)
			time_to_eat(philo);
		j++;
	}
	return (NULL);
}
