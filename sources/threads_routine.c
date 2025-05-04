/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:40:00 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/04 19:40:00 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

void	create_threads(t_data *data, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < data->n_phil)
	{
		data->philos[i].time_start = gettime_ms(&data->time);
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

int	manager(t_data *data, int argc)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->n_phil)
		{
			if (data->philos[i].dead > 0)
			{
				printf("while\n");
				data->dead = 1;
				return (0);
			}
			i++;
		}
		if (argc == 6)
		{
			if (ft_all_meals(data) >= data->nt_eat * data->n_phil)
			{
				data->stop = 1;
				return (0);
			}
		}
	}
	return (0);
}

void	eating(t_philo *philo, unsigned long start)
{
	philo->last_meal = gettime_ms(&philo->data->time);
	pthread_mutex_lock(philo->l_fork);
	printf("%.9lu %d has taken a fork\n",
		philo->last_meal - start, philo->index);
	pthread_mutex_lock(philo->r_fork);
	printf("%.9lu %d has taken a fork\n",
		philo->last_meal - start, philo->index);
	printf("%.9lu %d is eating\n", philo->last_meal - start, philo->index);
	usleep(philo->data->tt_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleeping_thinking(t_philo *philo, unsigned int start)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%.9lu %d is sleeping\n",
		philo->last_meal - start, philo->index);
	usleep(philo->data->tt_slp * 1000);
	printf("%.9lu %d is thinking\n",
		philo->last_meal - start, philo->index);
	usleep(philo->data->tt_die * 1000);
	pthread_mutex_unlock(&philo->data->print);
}

int	dead_stop(t_philo *philo)
{
	if (philo->data->dead == 1)
	{
		printf("%lu A philo has died\n", gettime_ms(&philo->data->time));
		return (1);
	}
	else if (philo->data->stop == 1)
	{
		printf("Philo %d is full\n", philo->index);
		return (1);
	}
	else
		return (1);
}
void	*routine(void *arg)
{
	t_philo			*philo;
	unsigned long	time;
	unsigned long	start;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		usleep(philo->data->tt_eat * 1000);
	start = gettime_ms(&philo->data->time);
	while (1)
	{
		eating(philo, start);
		sleeping_thinking(philo, start);
		philo->meals++;
		time = gettime_ms(&philo->data->time);
		if ((unsigned long)philo->data->tt_die
			+ (unsigned long)philo->data->tt_slp
			+ (unsigned long)philo->data->tt_eat > time - philo->last_meal)
			philo->dead = 1;
		if (dead_stop(philo))
			break ;
	}
	return (0);
}
