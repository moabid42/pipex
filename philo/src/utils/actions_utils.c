/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:26:49 by moabid            #+#    #+#             */
/*   Updated: 2022/08/03 23:31:44 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_meals_check(struct s_data *data, struct s_philo *philo)
{
	if (data->nb_of_meal == philo->meal_eaten)
		return (true);
	return (false);
}

int	ft_eat_enough(struct s_data *data, struct s_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&(data->eat));
		if (data->nb_of_meal != philo[i].meal_eaten)
		{
			pthread_mutex_unlock(&(data->eat));
			return (i);
		}
		pthread_mutex_unlock(&(data->eat));
		i++;
	}
	return (i);
}
