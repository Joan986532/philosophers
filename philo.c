/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:47:17 by jnauroy           #+#    #+#             */
/*   Updated: 2025/03/31 13:42:56 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_convert(char *str)
{
	int	i;
	int	value;

	value = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
		{
			printf("digits only\n");
			return (-1);
		}
		i++;
	}
	value = ft_atoi_safe(str);
	if (value == -1)
	{
		printf("numbers lower than int max only\n");
		return (-1);
	}
	return (value);
}

int	ft_parsing(char **argv, t_philo *data)
{
	data->numb_of_philos = ft_convert(argv[0]);
	if (data->numb_of_philos == -1)
		return (1);
	data->time_to_die = ft_convert(argv[1]);
	if (data->time_to_die == -1)
		return (1);
	data->time_to_eat = ft_convert(argv[2]);
	if (data->time_to_eat == -1)
		return (1);
	data->time_to_sleep = ft_convert(argv[3]);
	if (data->time_to_sleep == -1)
		return (1);
	data->notepme = ft_convert(argv[4]);
	if (data->notepme == -1)
		return (1);
	return (0);
}

void	ft_eating()
{

}

int	main(int argc, char **argv)
{
	pthread_t	*th;
	t_philo		data;
	int			i;

	i = 0;
	if (argc != 5)
		return (1);
	if (ft_parsing(argv, &data))
		return (1);
	th = malloc(sizeof(int) * data.numb_of_philos);
	while (i < data.numb_of_philos)
	{
		if (pthread_create(th[i], NULL, &ft_eating, NULL) != 0)
		{
			return (1);
		}
	}
	ft_eating();
	ft_sleaping();
	ft_thinking();
	return (0);
}
