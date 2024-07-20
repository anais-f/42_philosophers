void    *routine(void *arg)
{
	t_philo     *philo;

	philo = (t_philo*)arg;
	int j = 0;

	if (philo->n_philo % 2 == 0)
		usleep(philo->param.time_to_eat / 2);

	/*
	    par defaut le philo pense
	    si 1 fork de dispo → il la prend mais ne peux pas manger, il attend
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
	 incrementer a chaque fois qu'il mange

		si pas manger avant time_to_die → il meurt
		time_to_eat → doit conserver ses fork pendnt ce temps
		penser a verifier si le philo est mort → retourner le message

	    boucle infini dans la routine
	    voir decalage des pairs et impairs avec un sleep
	    faire avec une fourchette dispo aussi -> la prendre
		lock et unlock quand je fais la verif
		 monitoring pour verif la mort du philo
		comprarer le temps actuel - le temps du dernier repas avec le time to die
	 	boucle infini dans la routine

	 condition d'arret -> mort d'un philo ou que tous ai mange le bon nombre de repas
	 */

	// 1 while tant que lq simul es en ours et ensuite un while tant que ils n'ont pas 2 fork pour manger -> par defaut ils pensent
	// ils choppent une fork des que possible et il pensent en attendant d'avoir les deux
	//bien checker la droite et gauche simultamenent et pas attendre l'une apres l'autre pour les prendre

	//printf("philo n=%zu, valeur f.right num = %ld et bool = %d - valeur f.left num = %ld bool = %d\n", philo->n_philo, philo->f_right->n_fork, philo->f_right->fork_taken, philo->f_left->n_fork,philo->f_left->fork_taken);

	while (j < 3)
	{

		pthread_mutex_lock(&philo->f_right->mutex_fork);
		pthread_mutex_lock(&philo->f_left->mutex_fork);
		if (philo->f_right->fork_taken == false && philo->f_left->fork_taken == false)
		{
			printf("%ld %zu has taken a fork\n", get_timestamp_print(philo), philo->n_philo);
			philo->f_right->fork_taken = true;
			philo->f_left->fork_taken = true;
			pthread_mutex_unlock(&philo->f_right->mutex_fork);
			pthread_mutex_unlock(&philo->f_left->mutex_fork);
			get_time_last_meal(philo); //comprarer le temps actuel - le temps du dernier repas avec le time to die
			//		printf("time last meal philo %zu = %zu\n", philo->n_philo, philo->last_meal);
			printf("%ld %zu is eating\n", get_timestamp_print(philo), philo->n_philo);
			philo->nb_meal++;
			usleep(philo->param.time_to_eat * 1000);
			pthread_mutex_lock(&philo->f_right->mutex_fork);
			pthread_mutex_lock(&philo->f_left->mutex_fork);
			philo->f_right->fork_taken = false;
			philo->f_left->fork_taken = false;
			pthread_mutex_unlock(&philo->f_right->mutex_fork);
			pthread_mutex_unlock(&philo->f_left->mutex_fork);
			printf("%ld %zu is sleeping\n", get_timestamp_print(philo), philo->n_philo);
			usleep(philo->param.time_to_sleep * 1000);
		}
		else
		{
			printf("%ld %zu is thinking\n", get_timestamp_print(philo), philo->n_philo);
		}
		pthread_mutex_unlock(&philo->f_right->mutex_fork);
		pthread_mutex_unlock(&philo->f_left->mutex_fork);
		j++;
	}


	return (NULL);
}