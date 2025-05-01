/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:29:48 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/01 10:31:29 by jnauroy          ###   ########.fr       */
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
	numerote_philo(data);
	data->forks = malloc(sizeof(t_mutex) * data->n_phil);
	if (!data->forks)
	{
		free(th);
		ft_free_philo(philo, data->n_phil);
		return (1);
	}
	connect_to_mutex(data);
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
	pthread_mutex_init(&data.philo_num, NULL);
	create_threads(&data, th);
	data.actual = 0;
	while (1)
	{
		if (data.dead > 0)
			exit(0);
		if (data.lunches >= data.nt_eat * data.n_phil)
			break ;
	}
	printf("%sLunches [%d]%s\n", YELLOW, data.lunches, NC);
	join_threads(&data, th);
	print_messages(&data);
	pthread_mutex_destroy(data.forks);
	return (0);
}
