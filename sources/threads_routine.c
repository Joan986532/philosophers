/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:40:00 by jnauroy           #+#    #+#             */
/*   Updated: 2025/04/28 17:35:14 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

void	create_threads(t_data *data, pthread_t *th)
{
	while (data->actual <= data->n_phil + 1)
	{
		if (data->actual != data->n_phil + 1)
		{
			if (pthread_create(&th[data->actual - 1], NULL,
					&routine, data) != 0)
				exit(1);
			usleep(500);
			printf("Thread %d has started\n", data->actual);
		}
		else
		{
			if (pthread_create(&th[data->actual - 1], NULL,
					&routine_manager, data) != 0)
				exit(1);
			printf("%sThread manager %d has started%s\n",
				GREEN, data->actual + 1, NC);
		}
		data->actual++;
	}
}

void	join_threads(t_data *data, pthread_t *th)
{
	while (data->actual <= data->n_phil + 1)
	{
		if (pthread_join(th[data->actual - 1], NULL) != 0)
			exit(1);
		printf("Thread %d has stopped\n", data->actual);
		data->actual++;
	}
}

void	*routine_manager(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (data->dead > 0)
			exit(0);
		if (data->lunches >= data->nt_eat * data->n_phil)
			break ;
	}
	return (0);
}

void	*routine(void *arg)
{
	t_data	*data;
	int		i;
	int		num;	

	data = (t_data *)arg;
	i = 0;
	pthread_mutex_lock(data->mutex);
	num = data->actual;
	printf("%sPhilo %d%s\n", GREEN, num, NC);
	while (i < data->nt_eat)
	{
		printf("%d has taken a fork\n", num);
		printf("%d has taken a fork\n", num);
		printf("%d is eating\n", num);
		printf("%d is sleeping\n", num);
		printf("%d is thinking\n", num);
		printf("%d died\n", num);
		printf("%sLunches: [ %d ]%s\n", YELLOW, data->lunches, NC);
		data->lunches++;
		i++;
		usleep(1);
	}
	pthread_mutex_unlock(data->mutex);
	return (0);
}
