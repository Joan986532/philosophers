/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:13:43 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/06 16:18:27 by jnauroy          ###   ########.fr       */
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

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_phil)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philos[i].meals = 0;
		data->philos[i].index = i + 1;
		data->philos[i].tmp_time = 0;
		data->philos[i].last_meal = gettime_ms();
		data->philos[i].data = data;
		data->philos[i].l_fork = &data->forks[i];
		if (i + 1 == data->n_phil)
			data->philos[i].r_fork = &data->forks[0];
		else
			data->philos[i].r_fork = &data->forks[i + 1];
		i++;
	}
}

unsigned long	gettime_ms(void)
{
	struct timeval	time;
	unsigned long	time_ms;

	gettimeofday(&time, NULL);
	time_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_ms);
}

void	ft_free_tab(void **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
