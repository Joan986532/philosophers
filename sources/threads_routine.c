/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:40:00 by jnauroy           #+#    #+#             */
/*   Updated: 2025/04/30 17:42:54 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

void	create_threads(t_data *data, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < data->n_phil)
	{
		if (pthread_create(th + i, NULL,
				&routine, data) != 0)
			exit(1);
		usleep(500);
		printf("Thread %d has started\n", i + 1);
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
		printf("Thread %d has stopped\n", data->actual);
		i++;
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
	int		person;
	int		i;

	i = 0;
	data = (t_data *)arg;
	pthread_mutex_lock(&data->philo_num);
	person = data->actual + 1;
	data->actual++;
	pthread_mutex_unlock(&data->philo_num);
	printf("%sPhilo %d%s\n", GREEN, person, NC);
	while (1)
	{
		if (data->forks[person - 1].lock == 0)
		{
			pthread_mutex_lock(&data->philos[person - 1].l_fork);
			data->forks[person - 1].lock = 1;
			printf("%d has taken a fork\n", person);
			if (data->forks[person - 1].lock == 0)
			{
				pthread_mutex_lock(&data->philos[person - 1].r_fork);
				data->philos[person - 1].lock_r = 1;
				printf("%d has taken a fork\n", person);
				printf("%d is eating\n", person);
				usleep(1000);
				pthread_mutex_unlock(&data->philos[person - 1].l_fork);
				pthread_mutex_unlock(&data->philos[person - 1].r_fork);
				data->philos[person - 1].lock_l = 0;
				data->philos[person - 1].lock_r = 0;
			}
			else
			{
				pthread_mutex_unlock(&data->philos[person - 1].l_fork);
				data->philos[person - 1].lock_r = 0;
			}
		}
		printf("%d is sleeping\n", person);
		usleep(1000);
		printf("%d is thinking\n", person);
		usleep(1000);
		// printf("%d died\n", person);
		printf("%sLunches: [ %d ]%s\n", YELLOW, data->lunches, NC);
		data->lunches++;
	}
	return (0);
}
