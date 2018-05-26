/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:55:34 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/14 15:27:46 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fractol.h"
#include "libft/libft.h"

t_data			new_data(double r, double i, int max)
{
	t_data	ret;

	ret.rparam = r;
	ret.iparam = i;
	ret.xoffset = 0;
	ret.yoffset = 0;
	ret.gradstart = 4;
	ret.gradend = 6;
	ret.maxiter = max;
	ret.zoom = 0.3f;
	ret.gradoffset = 0;
	return (ret);
}

t_loop_param	new_lparam(int fractype)
{
	t_loop_param	ret;
	t_mlxunit		unit;
	t_data			data;

	unit = new_unit(fractype);
	data = new_data(-0.3, 0.5, 300);
	data.gradlist = gradient_list(data.gradstart, data.gradend, data.maxiter);
	drawfract(&unit, new_point(-1, -1, 0), data);
	free(data.gradlist);
	ret.unit = unit;
	ret.data = data;
	return (ret);
}

t_point			new_point(int x, int y, int color)
{
	t_point	ret;

	ret.rx = x;
	ret.ry = y;
	ret.color = color;
	return (ret);
}

t_mlxunit		new_unit(int fractype)
{
	t_mlxunit	unit;

	if (!(unit.mlx = mlx_init())
	|| !(unit.win = mlx_new_window(unit.mlx, W_WIDTH, W_HEIGHT, "fractol"))
	|| !(unit.pic = mlx_new_image(unit.mlx, W_WIDTH, W_HEIGHT)))
		ft_abort("Malloc of mlx failed");
	unit.picstr = (int *)mlx_get_data_addr(unit.pic, &unit.a, &unit.b, &unit.c);
	unit.fractype = fractype;
	unit.fract[0] = &mandelbrot;
	unit.fract[1] = &julia;
	unit.fract[2] = &ship;
	unit.update_w_mouse_mv = -1;
	unit.psychedelic_mode = -1;
	unit.antialiasing = -1;
	return (unit);
}

void			setup_tparam(t_thread_param *tp, t_point p, t_data data,
								t_mlxunit *unit)
{
	tp->point = p;
	tp->maxy = p.ry + (W_HEIGHT / THREAD_LIMIT);
	tp->data = data;
	tp->unit = unit;
}
