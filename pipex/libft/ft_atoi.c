/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:09:30 by moabid            #+#    #+#             */
/*   Updated: 2022/05/24 16:19:57 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_isspace(int c)
{
	return (c == '\f' || c == '\n' || c == '\r' \
	|| c == '\t' || c == '\v' || c == ' ');
}

int	ft_atoi(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		num = num * 10 + *str++ - '0';
	// if (*str != '\0')
	// 	return (0);
	if (num > MAX || num < MIN)
		return (0);
	return (num * sign);
}

// int main(void)
// {
// 	printf("%d\n", ft_atoi("12r3"));
// }
