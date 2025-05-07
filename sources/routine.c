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

int verify_while_action(t_philo *philo, unsigned long tt_action)
{
	unsigned long	timing;
	unsigned long	time;

	time = gettime_ms();
	timing = gettime_ms() + tt_action;
	while (time < timing)
	{
		pthread_mutex_lock(&philo->data->mutstop);
		if (philo->data->stop == 1)
		{
			pthread_mutex_unlock(&philo->data->mutstop);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->mutstop);
		usleep(tt_action);
		time = gettime_ms();
	}
	return (0);
}

int	eating(t_philo *philo)
{
	int	result;

	philo->last_meal = gettime_ms();
	pthread_mutex_lock(philo->l_fork);
	if (print_messages(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	pthread_mutex_lock(philo->r_fork);
	result = print_messages(philo, "has taken a fork");
	if (!result)
	{
		result = print_messages(philo, "is eating");
		pthread_mutex_lock(&philo->data->check);
		philo->meals++;
		pthread_mutex_unlock(&philo->data->check);
	}
	if (!result)
		result = verify_while_action(philo, philo->data->tt_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (result);
}

int	sleeping_thinking(t_philo *philo)
{
	unsigned long	time;

	time = gettime_ms();
	if (print_messages(philo, "is sleeping"))
		return (1);
	if (verify_while_action(philo, philo->data->tt_slp))
		return (1);
	time = gettime_ms();
	if (print_messages(philo, "is thinking"))
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (gettime_ms() - philo->data->start > (unsigned long)philo->data->tt_die)
		return (0);
	if (philo->index % 2 == 0)
		if (verify_while_action(philo, philo->data->tt_eat))
			return (0);
	while (1)
	{
		if (philo->data->stop == 1)
			break ;
		if (eating(philo))
			break ;
		if (sleeping_thinking(philo))
			break ;
		usleep(10);
	}
	return (0);
}