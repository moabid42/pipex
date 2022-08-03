/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:09:40 by moabid            #+#    #+#             */
/*   Updated: 2022/08/03 16:09:42 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	struct s_data	data;

	data_create(&data, ac, av);
	if (!threading(&data))
		ft_error(THREADING_ERROR);
	data_destroy(&data);
	return (0);
}
