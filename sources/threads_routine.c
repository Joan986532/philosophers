/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:40:00 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/03 18:05:07 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

void	create_threads(t_data *data, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < data->n_phil)
	{
		data->philos[i].time_start = gettime_ms(&data->time);
		if (pthread_create(th + i, NULL, &routine, &data->philos[i]) != 0)
			exit(1);
		usleep(500);
		i++;
	}
}

void	join_threads(t_data *data, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < data->n_phil)
	{
		if (pthread_join(th[i], NULL) != 0)
			exit(1);
		printf("Thread %d has stopped\n", i);
		i++;
	}
}

void	*routine_manager(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (data->dead > 0)
			exit(0);
		if (data->lunches >= data->nt_eat * data->n_phil)
			break ;
	}
	return (0);
}

void	eating(t_philo *philo)
{
	philo->last_meal = gettime_ms(&philo->data->time);
	pthread_mutex_lock(philo->l_fork);
	printf("[%lu] %d has taken a fork\n", philo->last_meal, philo->index);
	pthread_mutex_lock(philo->r_fork);
	printf("[%lu] %d has taken a fork\n", philo->last_meal, philo->index);
	printf("[%lu] %d is eating\n", philo->last_meal, philo->index);
	usleep(philo->data->tt_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	unsigned long	time;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		usleep(philo->data->tt_eat * 1000);
	while (1)
	{
		eating(philo);
		printf("%d is sleeping\n", philo->index);
		usleep(philo->data->tt_slp * 1000);
		printf("%d is thinking\n", philo->index);
		usleep(philo->data->tt_die * 1000);
		pthread_mutex_lock(&philo->data->print);
		pthread_mutex_unlock(&philo->data->print);
		philo->meals++;
		// printf("time: %lu\n", time);
		// printf("time: %lu\n", philo->last_meal);
		time = gettime_ms(&philo->data->time);
		if ((unsigned long)philo->data->tt_die
			+ (unsigned long)philo->data->tt_slp > time - philo->last_meal)
			philo->dead = 1;
		printf("life time: %d\n", philo->data->tt_die + philo->data->tt_slp);
		printf("time: %lu\n", time - philo->last_meal);
		if (philo->data->dead == 1 || philo->data->stop == 1)
		{
			if (philo->data->dead == 1)
				printf("A philo has died\n");
			else if (philo->data->stop == 1)
				printf("Philo %d is full\n", philo->index);
			break ;
		}
	}
	return (0);
}
