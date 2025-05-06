/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:40:00 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/06 15:52:19 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	eating(t_philo *philo)
{
	unsigned long	eat_time;

	eat_time = 0;
	philo->last_meal = gettime_ms();
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->data->print);
	printf("%.9lu %d has taken a fork\n",
		philo->last_meal - philo->data->start, philo->index);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->data->print);
	printf("%.9lu %d has taken a fork\n",
		philo->last_meal - philo->data->start, philo->index);
	printf("%.9lu %d is eating\n",
		philo->last_meal - philo->data->start, philo->index);
	pthread_mutex_unlock(&philo->data->print);
	philo->tmp_time = gettime_ms();
	eat_time = gettime_ms() + (unsigned long)philo->data->tt_eat * 1000;
	while (philo->tmp_time < eat_time)
	{
		pthread_mutex_lock(&philo->data->mutstop);
		if (philo->data->stop == 1)
		{
			pthread_mutex_unlock(&philo->data->mutstop);
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->mutstop);
		usleep(philo->data->tt_eat);
		philo->tmp_time = gettime_ms();
	}
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	sleeping_thinking(t_philo *philo)
{
	unsigned int	sleep_time;

	pthread_mutex_lock(&philo->data->print);
	philo->tmp_time = gettime_ms();
	printf("%.9lu %d is sleeping\n",
		philo->tmp_time - philo->data->start, philo->index);
	pthread_mutex_unlock(&philo->data->print);
	sleep_time = gettime_ms() + (unsigned long)philo->data->tt_slp * 1000;
	while (philo->tmp_time < sleep_time)
	{
		pthread_mutex_lock(&philo->data->mutstop);
		if (philo->data->stop == 1)
		{
			pthread_mutex_unlock(&philo->data->mutstop);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->mutstop);
		usleep(philo->data->tt_slp);
		philo->tmp_time = gettime_ms();
	}
	pthread_mutex_lock(&philo->data->print);
	philo->tmp_time = gettime_ms();
	printf("%.9lu %d is thinking\n",
		philo->tmp_time - philo->data->start, philo->index);
	pthread_mutex_unlock(&philo->data->print);
	philo->meals++;
	return (0);
}

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	// if (philo->data->n_phil == 1)
		// philo->dead = 1;
	if (gettime_ms() - philo->data->start > (unsigned long)philo->data->tt_die * 1000)
		return (0);
	if (philo->index % 2 == 0)
		usleep(philo->data->tt_eat * 1000);
	while (1)
	{
		if (philo->data->stop == 1)
			break ;
		if (eating(philo))
			break ;
		if (sleeping_thinking(philo))
			break ;
	}
	return (0);
}
