/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:29:48 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/06 15:50:47 by jnauroy          ###   ########.fr       */
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
		ft_free_tab((void *)philo, data->n_phil);
		return (1);
	}
	init_philos(data);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	*th;
	t_data		data;
	t_philo		*philo;
	int			flag;
	int			i;

	i = 0;
	flag = 0;
	if (argc < 5 || argc > 6)
		return (1);
	if (init_data(&philo, argv, &data, &th))
		return (1);
	pthread_mutex_init(&data.print, NULL);
	pthread_mutex_init(&data.mutstop, NULL);
	pthread_mutex_init(&data.check, NULL);
	create_threads(&data, th);
	manager(&data, argc);
	join_threads(&data, th);
	pthread_mutex_destroy(data.forks);
	// ft_free_tab((void *)th, data.n_phil);
	// ft_free_tab((void *)data.forks, data.n_phil);
	// ft_free_tab((void *)philo, data.n_phil);
	print_messages(&data); //tmp a retirer
	return (0);
}
