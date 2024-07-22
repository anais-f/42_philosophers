/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 00:32:20 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/18 00:32:20 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void    *routine(void *arg)
{
	t_philo     *philo;

	philo = (t_philo*)arg;
	int j = 0;

	pthread_mutex_lock(philo->mutex_start_and_end); // lock a la creation du philo qui tente de demarrer sa routine et attend que le mutex du main process s'unlock
	pthread_mutex_unlock(philo->mutex_start_and_end); // quand le mutex du MP ou d'un autre thread on l'unlock pour qu;il pusse continuer
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal = *philo->start_time;
	pthread_mutex_unlock(&philo->mutex_meal);
	if (philo->n_philo % 2 == 0) {
		usleep((philo->param.time_to_eat * 1000) / 2);
	}

	while (get_simul_status(philo) == false)
	{
		if (j == 0)
			get_status_message(philo, THINK);
		while (philo->right_fork_taken == false || philo->left_fork_taken == false)
		{
			pthread_mutex_lock(&philo->right_fork->mutex_fork);
			if (philo->right_fork->fork_is_busy == false)
			{
				get_status_message(philo, FORK);
				philo->right_fork->fork_is_busy = true;
				philo->right_fork_taken = true;
			}
			pthread_mutex_unlock(&philo->right_fork->mutex_fork);
			pthread_mutex_lock(&philo->left_fork->mutex_fork);
			if (philo->left_fork->fork_is_busy == false)
			{
				get_status_message(philo, FORK);
				philo->left_fork->fork_is_busy = true;
				philo->left_fork_taken = true;
			}
			pthread_mutex_unlock(&philo->left_fork->mutex_fork);
		}
/* quand il a pris ses 2 fork_is_busy, il mange */
		if (philo->right_fork_taken == true && philo->left_fork_taken == true)
		{
			get_status_message(philo, EAT);
			pthread_mutex_lock(&philo->mutex_meal);
			get_time_last_meal(philo);
			pthread_mutex_unlock(&philo->mutex_meal);
//			ft_usleep(philo->param.time_to_eat * 1000);
			usleep(philo->param.time_to_eat * 1000);
			pthread_mutex_lock(&philo->right_fork->mutex_fork);
			philo->right_fork->fork_is_busy = false;
			philo->right_fork_taken = false;
			pthread_mutex_unlock(&philo->right_fork->mutex_fork);
			pthread_mutex_lock(&philo->left_fork->mutex_fork);
			philo->left_fork->fork_is_busy = false;
			philo->left_fork_taken = false;
			pthread_mutex_unlock(&philo->left_fork->mutex_fork);
			pthread_mutex_lock(&philo->mutex_meal);
			philo->nb_meal++;
			pthread_mutex_unlock(&philo->mutex_meal);
			get_status_message(philo, SLEEP);
//			ft_usleep(philo->param.time_to_sleep * 1000);
			usleep(philo->param.time_to_sleep * 1000);
			get_status_message(philo, THINK);
		}
		j++;
	}
	return (NULL);
}
