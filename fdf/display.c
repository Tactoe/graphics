/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:02:53 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/15 18:07:25 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fdf.h"
#include <stdlib.h>

static void	img_put_pixel(t_mlxunit *unit, t_point point, t_data data)
{
	if ((point.ry * data.window_w) + point.rx < data.window_w * data.window_h
	&& ((point.ry * data.window_w) + point.rx) < data.window_w * (point.ry + 1)
	&& ((point.ry * data.window_w) + point.rx) > data.window_w * point.ry
	&& point.ry >= 0 && point.rx >= 0
	&& ((point.ry * data.window_w) + point.rx >= 0))
		unit->picstr[point.ry * data.window_w + point.rx] = point.color;
}

static void	bresenham(t_data data, t_mlxunit *unit, t_point start, t_point finish)
{
	int distx;
	int disty;
	int err;
	int tmp_err;

	distx = abs(finish.rx - start.rx);
	disty = abs(finish.ry - start.ry);
	err = (distx > disty ? distx : -disty) / 2;
	while (start.rx != finish.rx || start.ry != finish.ry)
	{
		img_put_pixel(unit, start, data);
		tmp_err = err;
		if (tmp_err > -distx)
		{
			err -= disty;
			start.rx += (start.rx < finish.rx ? 1 : -1);
		}
		if (tmp_err < disty)
		{
			err += distx;
			start.ry += (start.ry < finish.ry ? 1 : -1);
		}
	}
	img_put_pixel(unit, start, data);
}

static void	get_dots(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->mapheight)
	{
		x = 0;
		while (x < data->mapwidth)
		{
			data->coord[y][x].rx = (x - y) * data->tile_w +
				data->window_w / 2 + data->xoffset * data->tile_w;
			data->coord[y][x].ry = ((x + y) * data->tile_h)
				- data->coord[y][x].z * data->z_factor
				+ data->window_h / 2 + data->yoffset * data->tile_h;
			x++;
		}
		y++;
	}
}

void		print_map(t_data data, t_mlxunit *unit)
{
	int x;
	int y;

	get_dots(&data);
	y = 0;
	while (y < data.mapheight)
	{
		x = 0;
		while (x < data.mapwidth)
		{
			if (x < data.mapwidth - 1)
				bresenham(data, unit, data.coord[y][x], data.coord[y][x + 1]);
			if (y < data.mapheight - 1)
				bresenham(data, unit, data.coord[y][x], data.coord[y + 1][x]);
			x++;
		}
		y++;
	}
}
