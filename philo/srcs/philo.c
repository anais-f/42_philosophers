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
	struct timeval  tv;
	size_t  start;


	i = 0;
	//start = 0;

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
	gettimeofday(&tv, NULL);
	start = (tv.tv_sec *1000 + tv.tv_usec / 1000);
	//printf("\t\t\t\t\tstaet main = %ld\n", start);
	pthread_mutex_unlock(&simulation.mutex_start_and_end); //le start est set partout et tous les threads sont crees donc on peut commencer la routine

	// monitoring et mutex ici
	/*
	pthread_mutex_lock(&simulation.philo->mutex_start_and_end);
	fonction monitoring;
	pthread_mutex_unlock(&simulation.philo->mutex_start_and_end);
	*/


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
void    monitoring_philo(t_philo *philo)
{
	//un philo meurt s'il n'a pas manger si time to die > last meal // penser a mutex la verif / a faire dans le thread principal
	// ici la condition du bon nombre de repas aussi ?? oui avec boucle pour verifier tous le monde
	// attention, il faut que tous les [hilos aient mange le nb minimum de repas -> ils peuvent manger plus
//	struct  timeval tv;
//	size_t  actual;
//	gettimeofday(&tv, NULL);
//	actual = (tv.tv_sec *1000 + tv.tv_usec / 1000);

	size_t  time_since_last_meal;
	size_t  actual_time;

	actual_time = get_actual_time(philo);
	//printf("actual time = %ld vs vrai gettimeofdays = %ld\n", actual_time, actual);
	time_since_last_meal = actual_time - philo->last_meal;
//	printf("time last meal =%ld et time actual =%ld, diff entre les deux var=%ld et calcul =%ld\n", philo->last_meal, actual_time, time_since_last_meal, actual_time - philo->last_meal);
	if (time_since_last_meal >= philo->param.time_to_die)
		philo->die_or_fed = true;

}

