/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:49:44 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/28 09:52:19 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	verify_life(t_data *data)
{
	int				i;
	unsigned int	time;

	i = 0;
	while (i < data->n_phil)
	{
		pthread_mutex_lock(&data->mutmeal);
		time = gettime_ms() - data->philos[i].last_meal;
		pthread_mutex_unlock(&data->mutmeal);
		if (time > (unsigned long)data->tt_die)
		{
			pthread_mutex_lock(&data->print);
			data->stop = 1;
			printf("%lu %d died\n", gettime_ms() - data->start,
				data->philos[i].index);
			pthread_mutex_unlock(&data->print);
			return (1);
		}
		i++;
	}
	return (0);
}

int	count_meals(int lunches, t_data *data)
{
	pthread_mutex_lock(&data->print);
	if (lunches == data->n_phil)
	{
		data->stop = 1;
		usleep(200);
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	pthread_mutex_unlock(&data->print);
	return (0);
}

void	verify_lunches(t_data *data, int *lunches)
{
	int	i;

	i = 0;
	while (i < data->n_phil)
	{
		if (data->philos[i].meals == data->nt_eat)
			(*lunches)++;
		i++;
	}
}

int	manager(t_data *data, int argc)
{
	int	lunches;

	while (1)
	{
		lunches = 0;
		if (verify_life(data))
			break ;
		if (argc == 6)
		{
			pthread_mutex_lock(&data->mutmeal);
			verify_lunches(data, &lunches);
			pthread_mutex_unlock(&data->mutmeal);
			if (count_meals(lunches, data))
				break ;
		}
		usleep(3);
	}
	return (0);
}
