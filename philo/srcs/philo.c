/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:29:16 by anfichet          #+#    #+#             */
/*   Updated: 2024/04/15 17:29:16 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_simulation    simulation;
	size_t          nb_philo;
	size_t          i;

	i = 0;

	// check input
	if (check_input(argc, argv) == 1)
		return (EXIT_FAILURE);
	nb_philo = ft_atoi(argv[1]);

	//remplir les tableaux et initialiser les structures
	if (init_simulation(nb_philo, argv, &simulation) != 0)
		return (EXIT_FAILURE);

	//creer les threads
	while (i < nb_philo)
	{
		//printf("philo n=%zu, valeur f.right num = %ld et bool = %d - valeur f.left num = %ld bool = %d\n", simulation.philo[i].n_philo, simulation.philo[i].f_right->n_fork, simulation.philo[i].f_right->fork_taken, simulation.philo[i].f_left->n_fork, simulation.philo[i].f_left->fork_taken);
		if (pthread_create(&simulation.philo[i].philo_id, NULL, \
		&routine, &simulation.philo[i]) != 0)
		{
			while (i--)
				pthread_join(simulation.philo[i].philo_id, NULL);
			get_error_message(ERROR_THREAD);
		}
		i++;
	}

	//mettre le start time une fois les threads crees et avant le mutex start

	//attendre les threads
	i = 0;
	while(i < nb_philo)
	{
		pthread_join(simulation.philo[i].philo_id, NULL);
		i++;
	}

	return (EXIT_SUCCESS);
}

