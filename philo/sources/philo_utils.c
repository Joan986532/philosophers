/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:40:51 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/27 17:59:37 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	parsing_sign(char *nptr, int *i)
{
	while (nptr[*i] == ' ')
		(*i)++;
	if (!nptr)
	{
		ft_putstr_fd("no null strings\n", 2);
		return (-1);
	}
	while (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (*i > 0)
		{
			ft_putstr_fd("only one sign authorized\n", 2);
			return (-1);
		}
		if (nptr[*i] == '-')
		{
			ft_putstr_fd("positives numbers only\n", 2);
			return (-1);
		}
		(*i)++;
	}
	return (0);
}

int	is_wrong_format(char *nptr, int *i, int *nb_digit)
{
	if (!ft_isdigit(nptr[*i]))
	{
		while (nptr[*i] == ' ')
			(*i)++;
		if (nptr[*i] == '\0')
			return (0);
		else
		{
			ft_putstr_fd("wrong format\n", 2);
			return (-1);
		}
	}
	else
	{
		(*nb_digit)++;
		return (0);
	}
}

int	is_limit(char *nptr, int *i, int *nb)
{
	if ((*nb) > INT_MAX / 10)
	{
		ft_putstr_fd("number higher than int max\n", 2);
		return (-1);
	}
	(*nb) *= 10;
	if ((*nb) > INT_MAX - (nptr[*i] - 48))
	{
		ft_putstr_fd("number higher than int max\n", 2);
		return (-1);
	}
	(*nb) += nptr[*i] - 48;
	return (0);
}

int	ft_atoi_philo(char *nptr)
{
	int	i;
	int	nb;
	int	nb_digit;

	i = 0;
	nb = 0;
	nb_digit = 0;
	if (parsing_sign(nptr, &i) == -1)
		return (-1);
	while (nptr[i] != '\0')
	{
		if (is_wrong_format(nptr, &i, &nb_digit) == -1)
			return (-1);
		if (nptr[i] == '\0')
			break ;
		else if (is_limit(nptr, &i, &nb) == -1)
			return (-1);
		i++;
	}
	if (nb == 0 && nb_digit == 0)
		return (-1);
	else
		return (nb);
}

int	data_argv(char **argv, t_data *data)
{
	data->n_phil = ft_atoi_philo(argv[1]);
	if (data->n_phil == 0)
	{
		ft_putstr_fd("need at least 1 philo\n", 2);
		return (-1);
	}
	if (data->n_phil == -1)
		return (-1);
	data->tt_die = ft_atoi_philo(argv[2]);
	if (data->tt_die == -1)
		return (-1);
	data->tt_eat = ft_atoi_philo(argv[3]);
	if (data->tt_eat == -1)
		return (-1);
	return (0);
}
