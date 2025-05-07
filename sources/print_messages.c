/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:05:31 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/05 11:55:32 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	print_messages(t_philo *philo, char *str)
{
	unsigned long	currentime;

	currentime = gettime_ms();
	pthread_mutex_lock(&philo->data->mutstop);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->mutstop);
		return (1);
	}
	pthread_mutex_lock(&philo->data->print);
	printf("%lu %d %s\n", currentime - philo->data->start,
		philo->index, str);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_unlock(&philo->data->mutstop);
	return (0);
}

void	print_status(t_data *data)
{
	printf("Number of philosophers: %s%d%s\n", YELLOW, data->n_phil, NC);
	printf("N of times each philosophers must eat: %s%d%s\n",
		YELLOW, data->nt_eat, NC);
	printf("total: %s%d%s\n", YELLOW, data->nt_eat * data->n_phil, NC);
}
