/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:29:48 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/02 17:44:55 by jnauroy          ###   ########.fr       */
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
		ft_free_philo(philo, data->n_phil);
		return (1);
	}
	init_philos(data);
	return (0);
}

int	ft_all_meals(t_philo *philo)
{
	int	total;
	int	limit;
	int	i;

	i = 0;
	limit = philo[i].data->n_phil;
	total = 0;
	while (i < limit)
	{
		total += philo[i].meals;
		i++;
	}
	philo->data->lunches = total;
	return (total);
}

int	main(int argc, char **argv)
{
	pthread_t	*th;
	t_data		data;
	t_philo		*philo;
	int			flag;
	int			i;

	flag = 0;
	if (argc != 6)
		return (1);
	if (init_data(&philo, argv, &data, &th))
		return (1);
	pthread_mutex_init(&data.print, NULL);
	create_threads(&data, th);
	while (1)
	{
		i = 0;
		while (i < data.n_phil)
		{
			if (data.philos[i].dead > 0)
			{
				printf("while\n");
				data.dead = 1;
				flag = 1;
				break ;
			}
			i++;
		}
		if (flag == 1)
			break ;
		if (ft_all_meals(data.philos) >= data.nt_eat * data.n_phil)
		{
			data.stop = 1;
			break ;
		}
	}
	printf("%sLunches [%d]%s\n", YELLOW, data.lunches, NC);
	join_threads(&data, th);
	pthread_mutex_destroy(data.forks);
	print_messages(&data);
	return (0);
}
