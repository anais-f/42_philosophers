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
	//int i = 0;

	pthread_mutex_lock(philo->mutex_start_and_end); // lock a la creation du philo qui tente de demarrer sa routine et attend que le mutex du main process s'unlock
	pthread_mutex_unlock(philo->mutex_start_and_end); // quand le mutex du MP ou d'un autre thread on l'unlock pour qu;il pusse continuer
	if (philo->n_philo % 2 == 0)
		usleep(philo->param.time_to_eat / 2);

	while (j < 8) //die == true a mettre
	{
		pthread_mutex_lock(&philo->f_right->mutex_fork);
		pthread_mutex_lock(&philo->f_left->mutex_fork);
		while (philo->f_right->fork_taken == false || philo->f_left->fork_taken == false)
		{
			printf("%ld %zu is thinking\n", get_timestamp_print(philo), philo->n_philo);
			if (philo->f_right->fork_taken == false)
			{
				printf("%ld %zu has taken a fork\n", get_timestamp_print(philo), philo->n_philo);
				philo->f_right->fork_taken = true;
			}
			if (philo->f_left->fork_taken == false)
			{
				printf("%ld %zu has taken a fork\n", get_timestamp_print(philo), philo->n_philo);
				philo->f_left->fork_taken = true;
			}

			pthread_mutex_unlock(&philo->f_right->mutex_fork);
			pthread_mutex_unlock(&philo->f_left->mutex_fork);
		}
		pthread_mutex_lock(&philo->f_right->mutex_fork);
		pthread_mutex_lock(&philo->f_left->mutex_fork);
		if (philo->f_right->fork_taken == true && philo->f_left->fork_taken == true)
		{
			printf("%ld %zu is eating\n", get_timestamp_print(philo), philo->n_philo);
			get_time_last_meal(philo);
			philo->nb_meal++;
			usleep(philo->param.time_to_eat * 1000);
			philo->f_right->fork_taken = false;
			philo->f_left->fork_taken = false;
			pthread_mutex_unlock(&philo->f_left->mutex_fork);
			pthread_mutex_unlock(&philo->f_right->mutex_fork);
			printf("%ld %zu is sleeping\n", get_timestamp_print(philo), philo->n_philo);
			usleep(philo->param.time_to_sleep * 1000);
			printf("%ld %zu is thinking\n", get_timestamp_print(philo), philo->n_philo);

		}
//
		pthread_mutex_unlock(&philo->f_right->mutex_fork);
		pthread_mutex_unlock(&philo->f_left->mutex_fork);


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

