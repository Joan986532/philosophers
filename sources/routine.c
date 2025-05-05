/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:40:00 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/05 18:13:34 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	dead_stop(t_philo *philo)
{
	unsigned long	time;

	if (philo->data->stop == 1)
	{
		time = gettime_ms();
		pthread_mutex_lock(&philo->data->print);
		printf("%.9lu %d program end\n", time - philo->data->start, philo->index);
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	else
		return (0);
}

void	eating(t_philo *philo)
{
	unsigned long	eat_time;

	eat_time = 0;
	philo->last_meal = gettime_ms();
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->data->print);
	printf("%.9lu %d has taken a fork\n",
		philo->last_meal - philo->data->start, philo->index);
	pthread_mutex_unlock(&philo->data->print);
	philo->tmp_time = gettime_ms();
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->data->print);
	printf("%.9lu %d has taken a fork\n",
		philo->last_meal - philo->data->start, philo->index);
	printf("%.9lu %d is eating\n",
		philo->last_meal - philo->data->start, philo->index);
	pthread_mutex_unlock(&philo->data->print);
	// while (eat_time < (unsigned long)philo->data->tt_eat * 1000)
	// {
		// philo->tmp_time = gettime_ms();
		// eat_time += philo->data->tt_eat;
		// if (dead_stop(philo))
			// break ;
		// usleep(philo->data->tt_eat);
	// }
	usleep(philo->data->tt_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleeping_thinking(t_philo *philo)
{
	unsigned int	sleep_time;

	sleep_time = 0;
	pthread_mutex_lock(&philo->data->print);
	philo->tmp_time = gettime_ms();
	printf("%.9lu %d is sleeping\n",
		philo->tmp_time - philo->data->start, philo->index);
	pthread_mutex_unlock(&philo->data->print);
	// while (sleep_time < (unsigned long)philo->data->tt_slp * 1000)
	// {
		// philo->tmp_time = gettime_ms();
		// sleep_time += philo->data->tt_slp;
		// if (dead_stop(philo))
			// break ;
		// usleep(philo->data->tt_slp);
	// }
	usleep(philo->data->tt_slp * 1000);
	pthread_mutex_lock(&philo->data->print);
	philo->tmp_time = gettime_ms();
	printf("%.9lu %d is thinking\n",
		philo->tmp_time - philo->data->start, philo->index);
	pthread_mutex_unlock(&philo->data->print);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	// unsigned long	time;

	philo = (t_philo *)arg;
	if (philo->data->n_phil == 1)
		philo->dead = 1;
	if (philo->index % 2 == 0)
		usleep(philo->data->tt_eat * 1000);
	if (gettime_ms() - philo->data->start > (unsigned long)philo->data->tt_die * 1000)
		return (0);
	while (1)
	{
		// if (dead_stop(philo))
			// break ;
		eating(philo);
		if (philo->data->stop == 1)
			break ;
		sleeping_thinking(philo);
		if (philo->data->stop == 1)
			break ;
		philo->meals++;
		// time = gettime_ms(/gc);
		// if ((unsigned long)philo->data->tt_slp
			// + (unsigned long)philo->data->tt_eat > time - philo->last_meal)
			// philo->dead = 1;
		if (philo->data->stop == 1)
			break ;
	}
	return (0);
}
