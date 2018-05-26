/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 09:26:41 by tmilon            #+#    #+#             */
/*   Updated: 2018/01/13 09:28:12 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi_base(const char *str)
{
	unsigned int	n;
	int				loopamount;
	int				neg;

	n = 0;
	loopamount = 0;
	while (ftb_isspace(*str) == 1 && *str != '\0' && *str != '-' &&
				*str != '\e')
		str++;
	str += (*str == '+' && ft_isdigit(*(str + 1)) == 1 ? 1 : 0);
	if (*str == '-')
		neg = *(str++);
	else
		neg = 10;
	while (ft_isdigit(*str) != 0)
	{
		if (n * 10 < n && loopamount < 2)
			loopamount += (neg != 10 ? 2 : 1);
		else if (n * 10 < n)
			return (neg != 10 ? 0 : -1);
		n *= 10;
		n += (*str - 48);
		str++;
	}
	return (neg != 10 ? -n : n);
}
