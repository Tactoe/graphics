/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 14:06:23 by tmilon            #+#    #+#             */
/*   Updated: 2018/05/27 14:49:46 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

t_color new_color(int a, int b, int c)
{
	t_color ret;

	ret.r = a;
	ret.g = b;
	ret.b = c;
	return (ret);
}

int	coloralter(int color, double u, double v)
{
	int size = 60;
	int rainbowsize = size * 6;
	t_color	*rainbow;
	int	i;

	i = 0;
	rainbow = malloc(sizeof(t_color) * (rainbowsize + 1));
	for (int r = 0; r < size; r++)
	{
		rainbow[i] = new_color(r * 255 / size, 255, 0);
		i++;
	}
	for (int g = size; g > 0; g--) 
	{
		rainbow[i] = new_color(255, g * 255 / size ,0);
		i++;
	}
	for (int b=0; b<size; b++)
	{
		rainbow[i] = new_color(255, 0, b * 255 / size);
		i++;
	}
	for (int r=size; r>0; r--)
	{
		rainbow[i] = new_color(r * 255 / size, 0, 255);
		i++;
	}
	for (int g=0; g<size; g++)
	{
		rainbow[i] = new_color(0, g * 255 / size, 255);
		i++;
	}
	for (int b=size; b>0; b--)
	{
		rainbow[i] = new_color(0, 255, b * 255 / size);
		i++;
	}
	rainbow[i] = new_color(0, 255, 0);
	color = color_to_int(rainbow[(int)(v * rainbowsize * 4) % rainbowsize]);
	free(rainbow);
	return (color);
}

int	checker_pattern(int color, double u, double v)
{
	u *= 10;
	v *= 10;
	if (((int)u % 2 == 0 && (int)v % 2 == 0)
	|| (((int)u % 2 != 0 && (int)v % 2 != 0)))
			color = interpolate(color, (0xFFFFFF - color), 0.3);
	return (color);
	
}

void		get_uv_mapping_coord(double *u, double *v, t_intersect i, t_shape s)
{
	if (s.type == PLANE)
	{
		*u /= s.width;
		*v /= s.width;
	}
	if (s.type == SPHERE)
	{
		*u = 0.5 + (atan2(i.normal.z, i.normal.x) / (2 * PI));
		*v = 0.5 - (asin(i.normal.y) / PI);
	}
	else if (s.type == CYLINDER)
	{
		*u = 0.5 + atan2(i.normal.z, i.normal.x) / (2 * PI);
		*v = i.point.y / s.height;
	}
	else if (s.type == CONE)
	{
		*u = 0.5 + atan2(i.normal.z, i.normal.x) / (2 * PI);
		*v = i.point.y / s.height;
	}
}

int			texture(int color, t_intersect i, t_shape s)
{
	double u;
	double v;

	u = i.point.x;
	v = i.point.z;
	get_uv_mapping_coord(&u, &v, i, s);
	//color = checker_pattern(color, u, v);
	//color = coloralter(color, u, v);
	return (color);
}
