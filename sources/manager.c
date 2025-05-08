/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:49:44 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/08 17:13:26 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	verify_life(t_philo *philo)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->data->mutstop);
	time = gettime_ms() - philo->last_meal;
	pthread_mutex_unlock(&philo->data->mutstop);
	if (time > (unsigned long)philo->data->tt_die)
	{
		pthread_mutex_lock(&philo->data->print);
		philo->data->stop = 1;
		printf("%lu %d died\n", gettime_ms() - philo->data->start,
			philo->index);
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	return (0);
}

int	limit_lunches(int lunches, t_data *data)
{
	if (lunches >= data->n_phil * data->nt_eat)
	{
		pthread_mutex_lock(&data->print);
		data->stop = 1;
		pthread_mutex_unlock(&data->print);
		return (1);
	}
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
			pthread_mutex_lock(&data->print);
			if (data->philos[i].meals == 0)
				++lunches;
			// lunches += data->philos[i].meals;
			pthread_mutex_unlock(&data->print);
			// if (argc == 6 && limit_lunches(lunches, data))
				// return (1);
			i++;
		}
		if (argc == 6 && lunches == data->n_phil)
		{
			pthread_mutex_lock(&data->print);
			data->stop = 1;
			pthread_mutex_unlock(&data->print);
			return (1);
		}
		usleep(1);
	}
	return (0);
}
