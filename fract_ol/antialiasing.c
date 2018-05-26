/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:52:50 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/14 15:26:22 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	blend(t_mlxunit *unit, int i, float modif)
{
	unit->picstr[i] = interpolate(unit->picstr[i], unit->picstr[i + 1], modif);
	unit->picstr[i] = interpolate(unit->picstr[i], unit->picstr[i - 1], modif);
	unit->picstr[i] = interpolate(unit->picstr[i],
			unit->picstr[i + W_WIDTH], modif);
	unit->picstr[i] = interpolate(unit->picstr[i],
			unit->picstr[i - W_WIDTH], modif);
}

void		antialiasing(t_mlxunit *unit)
{
	int		pass;
	float	modif;
	int		i;

	pass = -1;
	while (++pass < 5)
	{
		i = -1;
		modif = (5 - pass) * 0.1;
		while (++i < PIC_LIMIT)
		{
			if (is_within_bounds(i))
				if (surrounding_pixels_differ(unit, i))
					blend(unit, i, modif);
		}
	}
}
