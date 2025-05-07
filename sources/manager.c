/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:49:44 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/06 16:18:44 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int verify_life(t_philo *philo)
{
	unsigned long	time;

	time = gettime_ms();
	pthread_mutex_lock(&philo->data->check);
	if (time - philo->last_meal > (unsigned long)philo->data->tt_die)
	{
		pthread_mutex_lock(&philo->data->mutstop);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->mutstop);
		pthread_mutex_lock(&philo->data->print);
		printf("%lu %d died\n", time - philo->data->start, philo->index);
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->data->check);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->check);
	return (0);
}

int	limit_lunches(int lunches, t_data *data)
{
	unsigned long	time;

	time = gettime_ms();
	pthread_mutex_lock(&data->check);
	if (lunches >= data->n_phil * data->nt_eat)
	{
		pthread_mutex_lock(&data->mutstop);
		data->stop = 1;
		pthread_mutex_unlock(&data->mutstop);
		pthread_mutex_lock(&data->print);
		printf("%lu %slunches: %d%s\n", time - data->start, GREEN, lunches, NC);
		pthread_mutex_unlock(&data->print);
		pthread_mutex_unlock(&data->check);
		return (1);
	}
	pthread_mutex_unlock(&data->check);
	return (0);
}

int	manager(t_data *data, int argc)
{
	int	i;
	int	lunches;

	while (1)
	{
		i = 0;
		lunches = 0;
		while (i < data->n_phil)
		{
			if (verify_life(&data->philos[i]))
			return (1);
			pthread_mutex_lock(&data->check);
			lunches += data->philos[i].meals;
			pthread_mutex_unlock(&data->check);
			i++;
		}
		if (argc == 6 && limit_lunches(lunches, data))
			return (1);
	}
	return (0);
}
