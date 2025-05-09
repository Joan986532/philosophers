/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:49:44 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/09 15:27:01 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	verify_life(t_philo *philo)
{
	unsigned int	time;

	pthread_mutex_lock(&philo->data->mutmeal);
	time = gettime_ms() - philo->last_meal;
	pthread_mutex_unlock(&philo->data->mutmeal);
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
			pthread_mutex_lock(&data->mutmeal);
			if (data->philos[i].meals == data->nt_eat)
				lunches++;
			pthread_mutex_unlock(&data->mutmeal);
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
