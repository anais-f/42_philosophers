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
	struct timeval  tv;
	int             nb_philo;
	int             i;
	size_t          start;

	i = 0;

	// check input
	if (check_input(argc, argv) == 1)
		return (EXIT_FAILURE);
	nb_philo = ft_atoi(argv[1]);

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
			while (i--) {
				pthread_join(simulation.philo[i].philo_id, NULL);
			}
			get_error_message(ERROR_THREAD);
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

	//free_struct(&simulation, nb_philo);

	return (EXIT_SUCCESS);
}


/* check if philo is alive or die */
void    monitoring_philo(t_simulation *simulation, t_philo *philo, int nb_philo)
{
	size_t  time_since_last_meal = 0;
	size_t  actual_time = 0;
	int i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_lock(&philo[i].mutex_meal);
		if (philo[i].last_meal > 0)
		{
			pthread_mutex_unlock(&philo[i].mutex_meal);
			i++;
		}
		else
			pthread_mutex_unlock(&philo[i].mutex_meal);
	}

	while (1)
	{
		i = 0;
		while (i < nb_philo)
		{
			actual_time = get_actual_time();
			pthread_mutex_lock(&philo[i].mutex_meal);
			time_since_last_meal = actual_time - philo[i].last_meal;
			pthread_mutex_unlock(&philo[i].mutex_meal);
			if (time_since_last_meal >= philo->param.time_to_die)
			{
				pthread_mutex_lock(&simulation->mutex_start_and_end);
				simulation->simul_to_stop = true;
				pthread_mutex_unlock(&simulation->mutex_start_and_end);
				pthread_mutex_lock(&simulation->mutex_print);
				printf("%ld %zu died\n", get_timestamp_print(philo), philo->n_philo);
				pthread_mutex_unlock(&simulation->mutex_print);
				return ;
			}
			i++;
		}
	}
}

//un philo meurt s'il n'a pas manger si time to die > last meal // penser a mutex la verif / a faire dans le thread principal
// ici la condition du bon nombre de repas aussi ?? oui avec boucle pour verifier tous le monde
// attention, il faut que tous les [hilos aient mange le nb minimum de repas -> ils peuvent manger plus

//checker le set du last meal avant de debuter le monitoring > 0 et si il est set a qqchose je passe au suivant
//
