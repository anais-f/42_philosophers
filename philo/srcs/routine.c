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

void    *routine(void *arg)
{
	t_philo     *philo;

	philo = (t_philo*)arg;
	int j = 0;

	pthread_mutex_lock(philo->mutex_start_and_end); // lock a la creation du philo qui tente de demarrer sa routine et attend que le mutex du main process s'unlock
	pthread_mutex_unlock(philo->mutex_start_and_end); // quand le mutex du MP ou d'un autre thread on l'unlock pour qu;il pusse continuer

	if (philo->n_philo % 2 == 0)
		usleep(philo->param.time_to_eat / 2);

	while (j < 8) //die == true a mettre
	{
		if (j == 0)
			printf("%ld %zu is thinking\n", get_timestamp_print(philo), philo->n_philo);
		while (philo->right_fork_taken == false || philo->left_fork_taken == false)
		{
			pthread_mutex_lock(&philo->right_fork->mutex_fork);
			pthread_mutex_lock(&philo->left_fork->mutex_fork);
			if (philo->right_fork->fork == false || philo->left_fork->fork == false)
			{
				if (philo->right_fork->fork == false) {
					printf("%ld %zu has taken a fork\n", get_timestamp_print(philo), philo->n_philo);
					philo->right_fork->fork = true;
					philo->right_fork_taken = true;
				}
				if (philo->left_fork->fork == false) {
					printf("%ld %zu has taken a fork\n", get_timestamp_print(philo), philo->n_philo);
					philo->left_fork->fork = true;
					philo->left_fork_taken = true;
				}
			}
			pthread_mutex_unlock(&philo->right_fork->mutex_fork);
			pthread_mutex_unlock(&philo->left_fork->mutex_fork);
		}

/* quand il a pris ses 2 fork, il mange */
		if (philo->right_fork_taken == true && philo->left_fork_taken == true)
		{
			printf("%ld %zu is eating\n", get_timestamp_print(philo), philo->n_philo);
			get_time_last_meal(philo);
			philo->nb_meal++;
			usleep(philo->param.time_to_eat * 1000);
			pthread_mutex_lock(&philo->right_fork->mutex_fork);
			pthread_mutex_lock(&philo->left_fork->mutex_fork);
			philo->right_fork->fork = false;
			philo->left_fork->fork = false;
			philo->right_fork_taken = false;
			philo->left_fork_taken = false;
			pthread_mutex_unlock(&philo->left_fork->mutex_fork);
			pthread_mutex_unlock(&philo->right_fork->mutex_fork);
			printf("%ld %zu is sleeping\n", get_timestamp_print(philo), philo->n_philo);
			usleep(philo->param.time_to_sleep * 1000);
			printf("%ld %zu is thinking\n", get_timestamp_print(philo), philo->n_philo);
		}

	//mutex les printf
		j++;
	}


	return (NULL);
}



/****************************************************************************/

//	printf("timestamp : %ld, philo %zu has taken a fork\n", get_timestamp_print(philo), philo->n_philo);
//	printf("timestamp : %ld, philo %zu is eating\n", get_timestamp_print(philo), philo->n_philo);
//	printf("timestamp : %ld, philo %zu is sleeping\n", get_timestamp_print(philo), philo->n_philo);
//	printf("timestamp : %ld, philo %zu is thinking\n", get_timestamp_print(philo), philo->n_philo);
//	printf("timestamp : %ld, philo %zu died\n", get_timestamp_print(philo), philo->n_philo);
//	printf("here\n");
/*******************************************************/

