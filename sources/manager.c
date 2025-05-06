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

int	manager(t_data *data, int argc)
{
	int				i;
	unsigned long	time;

	time = 0;
	while (1)
	{
		i = 0;
		data->lunches = 0;
		while (i < data->n_phil)
		{
			time = gettime_ms();
			pthread_mutex_lock(&data->check);
			if (time - data->philos[i].last_meal
				> (unsigned long)data->tt_die * 1000)
			{
				data->stop = 1;
				pthread_mutex_lock(&data->print);
				printf("%.9lu %d died\n", time - data->start, data->philos[i].index);
				pthread_mutex_unlock(&data->print);
				pthread_mutex_unlock(&data->check);
				return (1);
			}
			pthread_mutex_unlock(&data->check);
			data->lunches += data->philos[i].meals;
			pthread_mutex_lock(&data->check);
			if (argc == 6 && data->lunches > data->n_phil * data->nt_eat)
			{
				pthread_mutex_unlock(&data->check);
				data->stop = 1;
				return (1);
			}
			pthread_mutex_unlock(&data->check);
			i++;
		}
	}
	return (0);
}
