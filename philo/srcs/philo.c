/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:29:16 by anfichet          #+#    #+#             */
/*   Updated: 2024/07/24 22:17:13 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_thread_and_destroy_mutex(t_simulation *simulation, int nb_philo)
{
	int i;

	i = 0;
	while(i < nb_philo)
	{
		pthread_join(simulation->philo[i].philo_id, NULL);
		i++;
	}
	pthread_mutex_destroy(&simulation->mutex_start_and_end);
	pthread_mutex_destroy(&simulation->mutex_print);
	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&simulation->philo[i].mutex_meal);
		i++;
	}
}

int create_thread(t_simulation *simulation, int nb_philo)
{
	struct timeval  tv;
	int				i;

	i = -1;
	while (++i < nb_philo)
	{
		simulation->philo[i].start_time = &simulation->start_simul;
		if (pthread_create(&simulation->philo[i].philo_id, NULL, \
		&routine, &simulation->philo[i]) != 0)
		{
			simulation->simul_to_stop = true;
			pthread_mutex_unlock(&simulation->mutex_start_and_end);
			while (i--)
			{
				pthread_join(simulation->philo[i].philo_id, NULL);
				pthread_mutex_destroy(&simulation->philo[i].mutex_meal);
			}
			pthread_mutex_destroy(&simulation->mutex_start_and_end);
			pthread_mutex_destroy(&simulation->mutex_print);
			return (get_error_message(ERROR_THREAD));
		}
	}
	gettimeofday(&tv, NULL);
	simulation->start_simul = (tv.tv_sec *1000 + tv.tv_usec / 1000);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	t_simulation    simulation;
	int             nb_philo;

	if (check_input(argc, argv) == 1)
		return (EXIT_FAILURE);
	nb_philo = ft_pos_atoi(argv[1]);
	if (init_simulation(nb_philo, argv, &simulation) != 0)
		return (EXIT_FAILURE);

	pthread_mutex_lock(&simulation.mutex_start_and_end);
	create_thread(&simulation, nb_philo); // faire un if pour les message
	pthread_mutex_unlock(&simulation.mutex_start_and_end);

	monitoring_philo(&simulation, simulation.philo, nb_philo);
	join_thread_and_destroy_mutex(&simulation, nb_philo);
	free(simulation.philo);
	free(simulation.tfork);
	return (EXIT_SUCCESS);
}


