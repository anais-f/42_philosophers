/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:39:42 by anfichet          #+#    #+#             */
/*   Updated: 2024/07/18 18:39:42 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t  get_actual_time(t_philo *philo)
{
	struct  timeval tv;
	size_t  actual_time;

	(void)philo;
	gettimeofday(&tv, NULL);
	actual_time = (tv.tv_sec *1000 + tv.tv_usec / 1000);

	return (actual_time);
}

void    get_time_last_meal(t_philo *philo)
{
	struct  timeval tv_meal;

	gettimeofday(&tv_meal, NULL);
	philo->last_meal = (tv_meal.tv_sec *1000 + tv_meal.tv_usec / 1000);
}

/* pour calculer le temps depuis le lancement du programme (a modifier pour le debut de la simulation)
sert pour le printf des actions uniquement */
size_t    get_timestamp_print(t_philo *philo)
{
	struct timeval tv;
	size_t    actual_time;
	size_t    diff_time;

	gettimeofday(&tv, NULL);
	actual_time = (tv.tv_sec *1000 + tv.tv_usec / 1000);
//	printf("start time = %ld, actual time = %ld\n", philo->param.start_time, actual_time);
	diff_time = (actual_time - philo->param.start_time);
	return (diff_time);
}