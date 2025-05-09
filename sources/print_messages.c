/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:05:31 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/09 17:08:32 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	print_messages(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->stop == 0)
	{
		printf("%lu %d %s\n", gettime_ms() - philo->data->start,
			philo->index, str);
		pthread_mutex_unlock(&philo->data->print);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->print);
	return (1);
}

int	print_messages_eating(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->stop == 0)
	{
		pthread_mutex_lock(&philo->data->mutmeal);
		philo->last_meal = gettime_ms();
		pthread_mutex_unlock(&philo->data->mutmeal);
		printf("%lu %d %s\n", gettime_ms() - philo->data->start,
			philo->index, str);
		pthread_mutex_unlock(&philo->data->print);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->print);
	return (1);
}
