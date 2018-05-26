/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 12:36:24 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/06 13:20:32 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx_macos/mlx.h"
#include <stdlib.h>

static void	restore_img(t_loop_param *myparam)
{
	myparam->unit.pic = mlx_new_image(myparam->unit.mlx, myparam->data.window_w,
			myparam->data.window_h);
	myparam->unit.picstr = (int *)mlx_get_data_addr(myparam->unit.pic,
			&myparam->unit.a, &myparam->unit.b, &myparam->unit.c);
	print_map(myparam->data, &myparam->unit);
	mlx_put_image_to_window(myparam->unit.mlx, myparam->unit.win,
			myparam->unit.pic, 0, 0);
}

static void	move_map(int keycode, t_loop_param *myparam)
{
	if (keycode == 123)
	{
		myparam->data.xoffset -= myparam->data.xoffset >= -1000000 ? 30 : 0;
		mlx_destroy_image(myparam->unit.mlx, myparam->unit.pic);
		restore_img(myparam);
	}
	else if (keycode == 124)
	{
		myparam->data.xoffset += myparam->data.xoffset <= 1000000 ? 30 : 0;
		mlx_destroy_image(myparam->unit.mlx, myparam->unit.pic);
		restore_img(myparam);
	}
	else if (keycode == 125)
	{
		myparam->data.yoffset += myparam->data.yoffset <= 1000000 ? 30 : 0;
		mlx_destroy_image(myparam->unit.mlx, myparam->unit.pic);
		restore_img(myparam);
	}
	else if (keycode == 126)
	{
		myparam->data.yoffset -= myparam->data.yoffset >= -1000000 ? 30 : 0;
		mlx_destroy_image(myparam->unit.mlx, myparam->unit.pic);
		restore_img(myparam);
	}
}

static void	adjust_zoom(int keycode, t_loop_param *myparam)
{
	if (keycode == 24)
	{
		myparam->data.tile_w += myparam->data.tile_w <= 100000 ? 1 : 0;
		myparam->data.tile_h = myparam->data.tile_w / 2;
		restore_img(myparam);
	}
	else if (keycode == 27)
	{
		myparam->data.tile_w -= myparam->data.tile_w >= 4 ? 1 : 0;
		myparam->data.tile_h = myparam->data.tile_w / 2;
		restore_img(myparam);
	}
}

static void	adjust_z(int keycode, t_loop_param *myparam)
{
	if (keycode == 69)
	{
		myparam->data.z_factor += myparam->data.z_factor <= 100000 ? 1 : 0;
		restore_img(myparam);
	}
	else if (keycode == 78)
	{
		myparam->data.z_factor -= myparam->data.z_factor >= -100000 ? 1 : 0;
		restore_img(myparam);
	}
}

int			end_prog(int keycode, void *param)
{
	t_loop_param	*myparam;
	t_data			data;
	t_mlxunit		unit;

	myparam = (t_loop_param *)param;
	data = myparam->data;
	unit = myparam->unit;
	if (keycode == 24 || keycode == 27)
		adjust_zoom(keycode, myparam);
	if (keycode == 78 || keycode == 69)
		adjust_z(keycode, myparam);
	else if (keycode >= 123 && keycode <= 126)
		move_map(keycode, myparam);
	else if (keycode == 53)
		exit(0);
	return (0);
}
