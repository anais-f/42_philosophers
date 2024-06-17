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
	t_philo         philo;
	t_tfork         tfork;
	t_param         param;
	t_simulation    simulation;
	size_t          nb_philo;
	size_t          i;

	i = 0;


	// check input
	if (check_input(argc, argv) == 1) {
		return (EXIT_FAILURE);
	}
	nb_philo = ft_atoi(argv[1]);

	//malloc les deux tableaux
	philo = malloc(sizeof(t_philo) * nb_philo);
	if (!philo)
		return (EXIT_FAILURE);
	tfork = malloc(sizeof(t_tfork) * nb_philo);
	if (!tfork)
		return (EXIT_FAILURE);

	//remplir les deux tableaux
//	init_arg(argv, &data_arg);
//	printf("main timestamp start = %ld\n", data_arg.start_time);
//	if (init_fork(nb_philo, tfork) != 0) {
//		return (EXIT_FAILURE);
//	}
//	init_philo(nb_philo, philo, tfork, &data_arg);

	//creer les threads
	while (i < nb_philo)
	{
		if (pthread_create(&(philo[i].philo_id), NULL, &routine, &philo[i]) != 0)
		{
			while (i--)
				pthread_join(philo[i].philo_id, NULL);
			get_error_message(ERROR_THREAD);
		}
		i++;
	}

	//attendre les threads
	i = 0;
	while(i < nb_philo)
	{
		pthread_join(philo[i].philo_id, NULL);
		i++;
	}

	return (EXIT_SUCCESS);
}

void    *routine(void *arg)
{
	t_philo *philo;
	struct timeval tv;
	size_t  i;
	long    actual_time;
	long    diff_time;

	philo = (t_philo*)arg;
	i = 0;
	gettimeofday(&tv, NULL);
	actual_time = (tv.tv_sec *1000 + tv.tv_usec / 1000);
	printf("time start routine = %ld\n", philo->data_arg->start_time);
	diff_time = (philo[i].data_arg->start_time - actual_time);
	printf("timestamp %ld philo %zu is thinking\n", diff_time, philo[i].n_philo);

	/* par default, il think
	 * si 2 fork dispo -> eat
	 * apres avoir eat ->sleep
	 */
	return (NULL);
}
