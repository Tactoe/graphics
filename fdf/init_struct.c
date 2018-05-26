/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:55:34 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/06 13:20:12 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fdf.h"
#include <stdlib.h>

t_data		new_data(void)
{
	t_data	ret;

	ret.mapwidth = 0;
	ret.mapheight = 0;
	ret.xoffset = 0;
	ret.yoffset = 15;
	ret.coord = NULL;
	ret.window_w = 2200;
	ret.window_h = 1400;
	ret.tile_w = 6;
	ret.tile_h = ret.tile_w / 2;
	ret.z_factor = 1;
	return (ret);
}

t_mlxunit	new_unit(t_data data)
{
	t_mlxunit	unit;

	unit.mlx = mlx_init();
	unit.win = mlx_new_window(unit.mlx, data.window_w, data.window_h, "fdf");
	unit.pic = mlx_new_image(unit.mlx, data.window_w, data.window_h);
	unit.picstr = (int *)mlx_get_data_addr(unit.pic, &unit.a, &unit.b, &unit.c);
	return (unit);
}
