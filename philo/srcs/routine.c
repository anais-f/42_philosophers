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

/*
 condition d'arret -> mort d'un philo ou que tous ai mange le bon nombre de repas
 */

bool    get_simul_status(t_philo *philo)
{
	bool    status;
	pthread_mutex_lock(philo->mutex_start_and_end);
	status = *philo->die_or_fed;
	pthread_mutex_unlock(philo->mutex_start_and_end);
	return (status);
}

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
		usleep(philo->param.time_to_eat / 2);
	}


//	printf("last meal = %ld et die_or_fed = %d\n", philo->last_meal, *philo->die_or_fed);
	while (get_simul_status(philo) == false)
	{
		if (j == 0)
		{
			pthread_mutex_lock(philo->mutex_print);
			printf("%ld %zu is thinking\n", get_timestamp_print(philo), philo->n_philo);
			pthread_mutex_unlock(philo->mutex_print);
		}
		while (philo->right_fork_taken == false || philo->left_fork_taken == false)
		{
			pthread_mutex_lock(&philo->right_fork->mutex_fork);
			if (philo->right_fork->fork == false)
			{
				pthread_mutex_lock(philo->mutex_print);
				printf("%ld %zu has taken a fork\n", get_timestamp_print(philo), philo->n_philo);
				pthread_mutex_unlock(philo->mutex_print);
				philo->right_fork->fork = true;
				philo->right_fork_taken = true;
			}
			pthread_mutex_unlock(&philo->right_fork->mutex_fork);
			pthread_mutex_lock(&philo->left_fork->mutex_fork);
			if (philo->left_fork->fork == false)
			{
				pthread_mutex_lock(philo->mutex_print);
				printf("%ld %zu has taken a fork\n", get_timestamp_print(philo), philo->n_philo);
				pthread_mutex_unlock(philo->mutex_print);
				philo->left_fork->fork = true;
				philo->left_fork_taken = true;
			}
			pthread_mutex_unlock(&philo->left_fork->mutex_fork);
		}

/* quand il a pris ses 2 fork, il mange */
		if (philo->right_fork_taken == true && philo->left_fork_taken == true)
		{
			pthread_mutex_lock(philo->mutex_print);
			printf("%ld %zu is eating\n", get_timestamp_print(philo), philo->n_philo);
			pthread_mutex_unlock(philo->mutex_print);
			pthread_mutex_lock(&philo->mutex_meal);
			get_time_last_meal(philo);
			philo->nb_meal++;
			pthread_mutex_unlock(&philo->mutex_meal);
			usleep(philo->param.time_to_eat * 1000);
			pthread_mutex_lock(&philo->right_fork->mutex_fork);
			philo->right_fork->fork = false;
			philo->right_fork_taken = false;
			pthread_mutex_unlock(&philo->right_fork->mutex_fork);
			pthread_mutex_lock(&philo->left_fork->mutex_fork);
			philo->left_fork->fork = false;
			philo->left_fork_taken = false;
			pthread_mutex_unlock(&philo->left_fork->mutex_fork);
			pthread_mutex_lock(philo->mutex_print);
			printf("%ld %zu is sleeping\n", get_timestamp_print(philo), philo->n_philo);
			pthread_mutex_unlock(philo->mutex_print);
			usleep(philo->param.time_to_sleep * 1000);
			pthread_mutex_lock(philo->mutex_print);
			printf("%ld %zu is thinking\n", get_timestamp_print(philo), philo->n_philo);
			pthread_mutex_unlock(philo->mutex_print);
		}
		j++;
	}
	//printf("dobby is free\n");
	return (NULL);
}

//print -> check etat simul - faire une fonction
/* lock le printf
 * lock simul state
 * check simul state
 * unlock stimul stte
 * printf
 * unlock le print
 */