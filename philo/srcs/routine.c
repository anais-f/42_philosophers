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
	size_t  i;

	philo = (t_philo*)arg;
	i = 0;

	/****************************************************************************/
	/* par default, il think
	 * si 2 fork dispo -> eat
	 * apres avoir eat ->reposer les 2 forks ->sleep -> think
	 * verifier si le philo est dead
	 */

//	printf("routine must eat %ld time\n", philo->param.nb_must_eat);
//	printf("routine to die = %ld, to eat = %ld, to sleep = %ld\n", philo->param.time_to_die, philo->param.time_to_eat, philo->param.time_to_sleep);
//	printf("timestamp %ld philo %zu is thinking\n", diff_time, philo[i].n_philo);

	/*******************************************************/
//
//timestamp_in_ms X has taken a fork
//◦ timestamp_in_ms X is eating
//◦ timestamp_in_ms X is sleeping
//◦ timestamp_in_ms X is thinking
//◦ timestamp_in_ms X died

	printf("timestamp %ld philo %zu has taken a fork\n", get_timestamp(philo), philo[i].n_philo);
	printf("timestamp %ld philo %zu is eating\n", get_timestamp(philo), philo[i].n_philo);
	printf("timestamp %ld philo %zu is sleeping\n", get_timestamp(philo), philo[i].n_philo);
	printf("timestamp %ld philo %zu is thinking\n", get_timestamp(philo), philo[i].n_philo);
	printf("timestamp %ld philo %zu died\n", get_timestamp(philo), philo[i].n_philo);
	printf("\n");


	return (NULL);
}

long    get_timestamp(t_philo *philo)
{
	struct timeval tv;
	long    actual_time;
	long    diff_time;

	gettimeofday(&tv, NULL);
	actual_time = (tv.tv_sec *1000 + tv.tv_usec / 1000);
//	printf("start time = %ld, actual time = %ld\n", philo->param.start_time, actual_time);
	diff_time = (actual_time - philo->param.start_time);
	return (diff_time);
}
