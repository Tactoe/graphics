/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <tmilon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:53:16 by tmilon            #+#    #+#             */
/*   Updated: 2018/04/25 17:41:46 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			color_to_int(t_color c)
{
	return ((((c.r > 0xff) ? 0xff : c.r) << 16) |
			(((c.g > 0xff) ? 0xff : c.g) << 8) |
			((c.b > 0xff) ? 0xff : c.b));
}

t_color		int_to_color(int n)
{
	t_color	a;

	a.r = (n & 0x00FF0000) >> 16;
	a.g = (n & 0x0000FF00) >> 8;
	a.b = (n & 0x000000FF);
	return (a);
}

int			interpolate(int start, int finish, float ratio)
{
	t_color	a;
	t_color	b;

	a = int_to_color(start);
	b = int_to_color(finish);
	a.r = a.r + ((b.r - a.r) * ratio);
	a.g = a.g + ((b.g - a.g) * ratio);
	a.b = a.b + ((b.b - a.b) * ratio);
	return (color_to_int(a));
}
