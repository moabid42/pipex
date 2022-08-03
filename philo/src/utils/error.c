/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:10:16 by moabid            #+#    #+#             */
/*   Updated: 2022/08/03 16:10:18 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_num(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ac == 6 && av[5][j] == '-')
				ft_error(FOOD_ERROR);
			if (av[i][j] == '-')
				ft_error(NEGATIVE_ERROR);
			if (av[i][j] == '+')
				;
			else if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	data_sanitize(int ac, char **av)
{
	int		i;
	long	nb;

	i = 1;
	if (ac != 5 && ac != 6)
		ft_error(SYNTAX_ERROR);
	if (!ft_is_num(ac, av))
		ft_error(ARGUMENT_ERROR);
	while (av[i])
	{
		nb = ft_atoi(av[i]);
		i ++;
	}
	if (ft_atoi(av[1]) < 1)
		ft_error(NEGATIVE_ERROR);
	if (ac == 6 && ft_atoi(av[5]) < 1)
		ft_error(FOOD_ERROR);
}
