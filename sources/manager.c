/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:49:44 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/05 18:11:52 by jnauroy          ###   ########.fr       */
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
		usleep(100);
		while (i < data->n_phil)
		{
			time = gettime_ms();
			if (time - data->philos[i].last_meal
				> (unsigned long)data->tt_die * 1000)
			{
				printf("%sSTOP%s\n", RED, NC);
				data->stop = 1;
				return (1);
			}
			data->lunches += data->philos[i].meals;
			if (argc == 6 && data->lunches > data->n_phil * data->nt_eat)
			{
				printf("%sSTOP limit%s\n", RED, NC);
				data->stop = 1;
				return (1);
			}
			i++;
		}
	}
	return (0);
}
