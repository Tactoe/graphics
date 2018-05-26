/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:35:29 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/14 11:43:03 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			is_within_bounds(int i)
{
	if (i + 1 < PIC_LIMIT && i + W_WIDTH < PIC_LIMIT
	&& i - 1 >= 0 && i - W_WIDTH >= 0)
		return (1);
	else
		return (0);
}

int			surrounding_pixels_differ(t_mlxunit *unit, int i)
{
	if (unit->picstr[i] != unit->picstr[i + 1]
	&& unit->picstr[i] != unit->picstr[i - 1]
	&& unit->picstr[i] != unit->picstr[i + W_WIDTH]
	&& unit->picstr[i] != unit->picstr[i - W_WIDTH])
		return (1);
	else
		return (0);
}
