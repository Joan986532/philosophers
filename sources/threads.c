/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:53:01 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/05 17:28:09 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

void	create_threads(t_data *data, pthread_t *th)
{
	int	i;

	i = 0;
	data->start = gettime_ms();
	while (i < data->n_phil)
	{
		if (pthread_create(th + i, NULL, &routine, &data->philos[i]) != 0)
			exit(1);
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
		i++;
	}
}
