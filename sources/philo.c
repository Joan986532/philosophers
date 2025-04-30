/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:47:17 by jnauroy           #+#    #+#             */
/*   Updated: 2025/04/28 18:21:21 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	init_data(t_philo **philo, char **argv, t_data *data, pthread_t **th)
{
	if (ft_parsing(argv, data) == -1)
		return (1);
	*th = malloc(sizeof(pthread_t) * data->n_phil + 1);
	if (!*th)
		return (1);
	*philo = malloc(sizeof(t_philo) * data->n_phil);
	if (!*philo)
	{
		free(th);
		return (1);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_phil);
	if (!data->forks)
	{
		free(th);
		ft_free_philo(philo, data->n_phil);
		return (1);
	}
	pthread_mutex_init(data->forks, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	*th;
	t_data		data;
	t_philo		*philo;

	if (argc != 6)
		return (1);
	if (init_data(&philo, argv, &data, &th))
		return (1);
	create_threads(&data, th);
	data.actual = 1;
	usleep(500);
	join_threads(&data, th);
	usleep(500);
	printf("%sLunches [%d]%s\n", YELLOW, data.lunches, NC);
	usleep(500);
	print_messages(&data);
	pthread_mutex_destroy(data.forks);
	return (0);
}
