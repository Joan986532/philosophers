/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:05:31 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/08 16:58:11 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	print_messages(t_philo *philo, char *str)
{
	unsigned long	currentime;

	pthread_mutex_lock(&philo->data->print);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	currentime = gettime_ms();
	printf("%lu %d %s\n", currentime - philo->data->start,
		philo->index, str);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

int	print_messages_eating(t_philo *philo, char *str)
{
	unsigned long	currentime;

	pthread_mutex_lock(&philo->data->print);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	currentime = gettime_ms();
	printf("%lu %d %s\n", currentime - philo->data->start,
		philo->index, str);
	philo->meals--;
	if (philo->meals < 0)
		philo->meals = 0;
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}
