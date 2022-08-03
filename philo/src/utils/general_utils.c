/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:27:52 by moabid            #+#    #+#             */
/*   Updated: 2022/08/03 14:48:21 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_error(char *error)
{
	write(2, error, ft_strlen(error));
	exit(1);
}

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	src;
	size_t			i;

	dest = b;
	src = c;
	i = 0;
	while (i++ < n)
		*dest++ = src;
	return (b);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr)
		ft_memset(ptr, '0', size);
	else
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}
