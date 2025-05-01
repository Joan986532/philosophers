/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:13:43 by jnauroy           #+#    #+#             */
/*   Updated: 2025/04/30 17:36:42 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

void	ft_free_philo(t_philo **philo, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		free(philo[i]);
		i++;
	}
	free(philo);
}

void	numerote_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_phil)
	{
		data->philos[i].num = i + 1;
		i++;
	}
}

void	connect_to_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_phil)
	{
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		data->philos->lock_l = 0;
		data->philos->l_fork = data->forks[i].mutex;
		if (i + 1 == data->n_phil)
			data->philos->r_fork = data->forks[0].mutex;
		else
			data->philos->r_fork = data->forks[i + 1].mutex;
		i++;
	}
}
