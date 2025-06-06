/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:29:48 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/23 17:19:09 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_data(t_philo **philo, char **argv, t_data *data, pthread_t **th)
{
	if (ft_parsing(argv, data) == -1)
		return (1);
	*th = malloc(sizeof(pthread_t) * data->n_phil);
	if (!*th)
		return (1);
	*philo = malloc(sizeof(t_philo) * data->n_phil);
	if (!*philo)
	{
		free(th);
		return (1);
	}
	data->philos = *philo;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_phil);
	if (!data->forks)
	{
		free(th);
		free(data->philos);
		return (1);
	}
	if (init_philos(data))
		return (1);
	return (0);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_phil)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->mutmeal);
}

int	main(int argc, char **argv)
{
	pthread_t	*th;
	t_data		data;
	t_philo		*philo;
	int			n_th;

	if (argc < 5 || argc > 6)
		return (1);
	if (init_data(&philo, argv, &data, &th))
		return (1);
	if (pthread_mutex_init(&data.print, NULL) == -1)
		return (1);
	if (pthread_mutex_init(&data.mutmeal, NULL) == -1)
		return (1);
	n_th = create_threads(&data, th);
	manager(&data, argc);
	join_threads(th, n_th);
	destroy_mutex(&data);
	free(th);
	free(data.forks);
	free(philo);
	return (0);
}
