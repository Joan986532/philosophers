/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:55:14 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/26 13:57:23 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	think_start(t_philo *philo)
{
	philo->tt_thk = philo->data->tt_eat;
	if (philo->index % 2 == 1 && philo->index != philo->data->n_phil)
	{
		if (verify_while_action(philo, philo->tt_thk))
			return (1);
	}
	else if (philo->index % 2 == 1 && philo->index == philo->data->n_phil)
	{
		philo->tt_thk *= 2;
		if (verify_while_action(philo, philo->tt_thk))
			return (1);
	}
	return (0);
}

int	verify_thinking(t_philo *philo)
{
	int	thinking;
	int	stop;

	thinking = philo->data->tt_eat - philo->data->tt_slp;
	if (thinking < 0)
		thinking = 0;
	pthread_mutex_lock(&philo->data->print);
	stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->print);
	if (stop == 1)
		return (1);
	if (verify_while_action(philo, thinking))
		return (1);
	return (0);
}
