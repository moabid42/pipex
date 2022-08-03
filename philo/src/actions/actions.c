/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:24:07 by moabid            #+#    #+#             */
/*   Updated: 2022/08/03 23:20:22 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(struct s_data *data, struct s_philo *philo)
{
	print_state(data, philo->philo_id, SLEEP);
	ft_usleep(data->time_to_sleep);
}

void	philo_think(struct s_data *data, struct s_philo *philo)
{
	print_state(data, philo->philo_id, THINK);
}
