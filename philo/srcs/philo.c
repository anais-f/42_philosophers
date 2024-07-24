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

int main(int argc, char **argv)
{
	t_simulation    simulation;
	struct timeval  tv;
	int             nb_philo;
	int             i;
	size_t          start;

	i = 0;

	// check input
	if (check_input(argc, argv) == 1)
		return (EXIT_FAILURE);
	nb_philo = ft_pos_atoi(argv[1]);

	//creer les tableaux et initialiser les structures
	if (init_simulation(nb_philo, argv, &simulation) != 0)
		return (EXIT_FAILURE);

	//creer les threads
	pthread_mutex_lock(&simulation.mutex_start_and_end); // mutex le start, permet de bloquer le demarrage de la routine
	while (i < nb_philo)
	{
		simulation.philo[i].start_time = &start;
//printf("philo n=%zu, valeur f.right num = %ld et bool = %d - valeur f.left num = %ld bool = %d\n", simulation.philo[i].n_philo, simulation.philo[i].right_fork->n_fork, simulation.philo[i].right_fork->fork_taken, simulation.philo[i].left_fork->n_fork, simulation.philo[i].left_fork->fork_taken);
		if (pthread_create(&simulation.philo[i].philo_id, NULL, \
		&routine, &simulation.philo[i]) != 0)
		{
			simulation.simul_to_stop = true;
			pthread_mutex_unlock(&simulation.mutex_start_and_end);
			while (i--)
			{
				pthread_join(simulation.philo[i].philo_id, NULL);
				pthread_mutex_destroy(&simulation.philo[i].mutex_meal);
			}
			pthread_mutex_destroy(&simulation.mutex_start_and_end);
			pthread_mutex_destroy(&simulation.mutex_print);
			return (get_error_message(ERROR_THREAD));
		}
		i++;
	}
	gettimeofday(&tv, NULL);
	start = (tv.tv_sec *1000 + tv.tv_usec / 1000);
	pthread_mutex_unlock(&simulation.mutex_start_and_end); //le start est set partout et tous les threads sont crees donc on peut commencer la routine

	// monitoring et mutex ici
	monitoring_philo(&simulation, simulation.philo, nb_philo);


	//attendre les threads a la fin de leur routine
	i = 0;
	while(i < nb_philo)
	{
		pthread_join(simulation.philo[i].philo_id, NULL);
		i++;
	}

	//destroy mutex
	pthread_mutex_destroy(&simulation.mutex_start_and_end);
	pthread_mutex_destroy(&simulation.mutex_print);
	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&simulation.philo[i].mutex_meal);
		i++;
	}

	free(simulation.philo);
	free(simulation.tfork);
	return (EXIT_SUCCESS);
}


