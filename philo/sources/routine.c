/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:40:00 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/28 10:29:54 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	verify_while_action(t_philo *philo, unsigned long tt_action)
{
	unsigned long	timing;

	timing = gettime_ms() + tt_action;
	while (gettime_ms() < timing)
	{
		pthread_mutex_lock(&philo->data->print);
		if (philo->data->stop == 1)
		{
			pthread_mutex_unlock(&philo->data->print);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->print);
		usleep(100);
	}
	return (0);
}

int	eat_modulo(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->data->print);
	stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->print);
	if (stop == 1)
		return (1);
	if (philo->index % 2 == 1)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	if (print_messages(philo, "has taken a fork") || philo->data->n_phil == 1)
	{
		if (philo->index % 2 == 1)
			pthread_mutex_unlock(philo->l_fork);
		else
			pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	int	result;

	if (eat_modulo(philo))
		return (1);
	if (philo->index % 2 == 1)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	result = print_messages(philo, "has taken a fork");
	if (!result)
		result = print_messages_eating(philo, "is eating");
	if (philo->data->nt_eat != -1)
	{
		pthread_mutex_lock(&philo->data->mutmeal);
		philo->meals++;
		if (philo->meals >= philo->data->nt_eat)
			philo->meals = philo->data->nt_eat;
		pthread_mutex_unlock(&philo->data->mutmeal);
	}
	if (!result)
		result = verify_while_action(philo, philo->data->tt_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (result);
}

int	sleeping_thinking(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->data->print);
	stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->print);
	if (stop == 1)
		return (1);
	if (print_messages(philo, "is sleeping"))
		return (1);
	if (verify_while_action(philo, philo->data->tt_slp))
		return (1);
	if (print_messages(philo, "is thinking"))
		return (1);
	if (verify_thinking(philo))
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	int				stop;

	philo = (t_philo *)arg;
	if (gettime_ms() - philo->data->start > (unsigned long)philo->data->tt_die)
		return (0);
	if (print_messages(philo, "is thinking"))
		return (0);
	if (think_start(philo))
		return (0);
	while (1)
	{
		pthread_mutex_lock(&philo->data->print);
		stop = philo->data->stop;
		pthread_mutex_unlock(&philo->data->print);
		if (stop == 1)
			break ;
		if (eating(philo))
			break ;
		if (sleeping_thinking(philo))
			break ;
		usleep(200);
	}
	return (0);
}
