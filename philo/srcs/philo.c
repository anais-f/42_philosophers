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
	t_philo *philo;
	t_fork  *fork;
	int nb_philo;

	nb_philo = ft_atoi(argv[1]);

	if (check_input(argc, argv) == 1)
		return (1);

	philo = malloc(sizeof(t_philo) * nb_philo);
	if (!philo)
		return (1);
	fork = malloc(sizeof(t_fork) * nb_philo);
	if (!fork)
		return (1);


	// init le tableau de philo
	init_philo(nb_philo, philo);
	init_fork(nb_philo, fork);

	// creer les threads
	pthread_create(&(philo[0].philo_id), NULL, &routine, NULL);

	//printf("numero philo = %lu\n", philo[0].philo_id);

	//attendre les threads
	pthread_join(philo[0].philo_id, NULL);
	return (0);
}

void    init_philo(int nb_philo, t_philo *philo)
{
	int i;

	i = 0;
	printf("nb philo = %d\n", nb_philo);
	while (i < nb_philo)
	{
		philo[i].n_philo = i + 1;
		printf("philo n %d\n", philo[i].n_philo);
		//philo[i].fork[0] = init_fork(nb_philo, philo[i].fork);
		i++;
	}
}

void    init_fork(int nb_philo, t_fork *fork)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		fork[i].fork = false;
		pthread_mutex_init(&fork[i].mutex_fork, NULL);
		i++;
	}
}

void    *routine(void *arg)
{
	(void)arg;
	printf(" horodatage philo X is thinking\n");

	/* par default, il think
	 * si 2 fork dispo -> eat
	 * apres avoir eat ->sleep
	 */
	return (NULL);
}
