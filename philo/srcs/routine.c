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
	/*
	    par defaut le philo pense
		2 fork dispo →
		il prend les fork
		change le statut de la fourchette
		il mange / stocker le time ici
		il repose la fourchette
		change le statut de la fourchette
		il dort le temps imparti
		il pense
		si 1 fork de dispo → il pense
		si pas manger avant time_to_die → il meurt
		time_to_eat → doit conserver ses fork pendnt ce temps
		penser a verifier si le philo est mort → retourner le message
	 boucle infini dans la routine
	 */

//	printf("routine must eat %ld time\n", philo->param.nb_must_eat);
//	printf("routine to die = %ld, to eat = %ld, to sleep = %ld\n", philo->param.time_to_die, philo->param.time_to_eat, philo->param.time_to_sleep);
//	printf("timestamp %ld philo %zu is thinking\n", diff_time, philo[i].n_philo);

//	printf("timestamp : %ld, philo %zu has taken a fork\n", get_timestamp(philo), philo[i].n_philo);
//	printf("timestamp : %ld, philo %zu is eating\n", get_timestamp(philo), philo[i].n_philo);
//	printf("timestamp : %ld, philo %zu is sleeping\n", get_timestamp(philo), philo[i].n_philo);
//	printf("timestamp : %ld, philo %zu is thinking\n", get_timestamp(philo), philo[i].n_philo);
//	printf("timestamp : %ld, philo %zu died\n", get_timestamp(philo), philo[i].n_philo);
//	printf("here\n");
	/*******************************************************/

	//printf("philo n=%zu, valeur f.right num = %ld et bool = %d - valeur f.left num = %ld bool = %d\n", philo[i].n_philo, philo[i].f_right->n_fork, philo[i].f_right->fork_taken, philo[i].f_left->n_fork,philo[i].f_left->fork_taken);

	if (philo[i].f_right->fork_taken == false && philo[i].f_left->fork_taken == false)
	{
		philo[i].f_right->fork_taken = true;
		philo[i].f_left->fork_taken = true;
		printf("timestamp : %ld, philo %zu has taken a fork\n", get_timestamp(philo), philo[i].n_philo);
		get_time_last_meal(philo);
		printf("timestamp : %ld, philo %zu is eating\n", get_timestamp(philo), philo[i].n_philo);
		usleep(philo[i].param.time_to_eat * 1000);
		philo[i].f_right->fork_taken = false;
		philo[i].f_left->fork_taken = false;
		printf("timestamp : %ld, philo %zu is sleeping\n", get_timestamp(philo), philo[i].n_philo);
		usleep(philo[i].param.time_to_sleep * 1000);
	}
	else
	{
		printf("timestamp : %ld, philo %zu is thinking\n", get_timestamp(philo), philo[i].n_philo);
	}


	return (NULL);
}

/* pour calculer le temps depuis la fin d'une action */
void    get_time_last_meal(t_philo *philo)
{
	struct  timeval tv_meal;

	gettimeofday(&tv_meal, NULL);
	philo->last_meal = (tv_meal.tv_sec *1000 + tv_meal.tv_usec / 1000);
}

/* pour calculer le temps depuis le lancement du programme (a modifier pour le debut de la simulation)
sert pour le printf des actions uniquement */
size_t    get_timestamp(t_philo *philo)
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
