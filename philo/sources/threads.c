/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:53:01 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/27 15:37:36 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	create_threads(t_data *data, pthread_t *th)
{
	int	i;

	i = 0;
	data->start = gettime_ms();
	while (i < data->n_phil)
	{
		if (pthread_create(th + i, NULL, &routine, &data->philos[i]) != 0)
			break ;
		i++;
	}
	return (i);
}

void	join_threads(pthread_t *th, int n_th)
{
	int	i;

	i = 0;
	while (i < n_th)
	{
		pthread_join(th[i], NULL);
		i++;
	}
}
