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

	philo = (t_philo*)arg;
	int j = 0;
	/*
	    par defaut le philo pense
	    si 1 fork de dispo → il la prend mais ne peux pas manger
		2 fork dispo →
		il prend les fork
	    securise mes fork →mutex lock
		change le statut de la fourchette
		il mange / stocker le time ici
		il repose la fourchette
		change le statut de la fourchette
	    unlock mutex
		il dort le temps imparti
		il pense

		si pas manger avant time_to_die → il meurt
		time_to_eat → doit conserver ses fork pendnt ce temps
		penser a verifier si le philo est mort → retourner le message

	    boucle infini dans la routine
	    voir decalage des pairs et impairs avec un sleep
	    faire avec une fourchette dispo aussi -> la prendre
		lock et unlock quand je fais la verif
		 monitoring pour verif la mort du philo
		comprarer le temps actuel - le temps du dernier repas avec le time to die
	 */

	//printf("philo n=%zu, valeur f.right num = %ld et bool = %d - valeur f.left num = %ld bool = %d\n", philo->n_philo, philo->f_right->n_fork, philo->f_right->fork_taken, philo->f_left->n_fork,philo->f_left->fork_taken);

	while (j < 3)
	{

//		pthread_mutex_lock(&philo->f_right->mutex_fork);
//		pthread_mutex_lock(&philo->f_left->mutex_fork);
		if (philo->f_right->fork_taken == false && philo->f_left->fork_taken == false)
		{
			printf("ts : %ld, philo %zu has taken two forks\n", get_timestamp_print(philo), philo->n_philo);
			philo->f_right->fork_taken = true;
			philo->f_left->fork_taken = true;
//			pthread_mutex_unlock(&philo->f_right->mutex_fork);
//			pthread_mutex_unlock(&philo->f_left->mutex_fork);
			get_time_last_meal(philo); //comprarer le temps actuel - le temps du dernier repas avec le time to die
			printf("time last meal philo %zu = %zu\n", philo->n_philo, philo->last_meal);
			printf("ts : %ld, philo %zu is eating\n", get_timestamp_print(philo), philo->n_philo);
			usleep(philo->param.time_to_eat * 1000);
//			pthread_mutex_lock(&philo->f_right->mutex_fork);
//			pthread_mutex_lock(&philo->f_left->mutex_fork);
			philo->f_right->fork_taken = false;
			philo->f_left->fork_taken = false;
//			pthread_mutex_unlock(&philo->f_right->mutex_fork);
//			pthread_mutex_unlock(&philo->f_left->mutex_fork);
			printf("ts : %ld, philo %zu is sleeping\n", get_timestamp_print(philo), philo->n_philo);
			usleep(philo->param.time_to_sleep * 1000);
			monitoring_philo(philo);
		}
		else
		{
			printf("ts : %ld, philo %zu is thinking\n", get_timestamp_print(philo), philo->n_philo);
		}
		j++;
	}


	return (NULL);
}

/* check if philo is alive or die */
void    monitoring_philo(t_philo *philo)
{
	//un philo meurt s'il n'a pas manger si time to die > last meal // penser a mutex la verif
//	struct  timeval tv;
//	size_t  actual;
//	gettimeofday(&tv, NULL);
//	actual = (tv.tv_sec *1000 + tv.tv_usec / 1000);

	size_t  time_since_last_meal;
	size_t  actual_time;

	actual_time = get_actual_time(philo);
	//printf("actual time = %ld vs vrai gettimeofdays = %ld\n", actual_time, actual);
	time_since_last_meal = actual_time - philo->last_meal;
	printf("time last meal =%ld et time actual =%ld, diff entre les deux var=%ld et calcul =%ld\n", philo->last_meal, actual_time, time_since_last_meal, actual_time - philo->last_meal);
	if (time_since_last_meal >= philo->param.time_to_die)
		philo->philo_is_die = true;

}

/****************************************************************************/

//	printf("timestamp : %ld, philo %zu has taken a fork\n", get_timestamp_print(philo), philo->n_philo);
//	printf("timestamp : %ld, philo %zu is eating\n", get_timestamp_print(philo), philo->n_philo);
//	printf("timestamp : %ld, philo %zu is sleeping\n", get_timestamp_print(philo), philo->n_philo);
//	printf("timestamp : %ld, philo %zu is thinking\n", get_timestamp_print(philo), philo->n_philo);
//	printf("timestamp : %ld, philo %zu died\n", get_timestamp_print(philo), philo->n_philo);
//	printf("here\n");
/*******************************************************/


