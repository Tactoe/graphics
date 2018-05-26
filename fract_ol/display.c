/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:02:53 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/14 15:52:24 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fractol.h"
#include <stdlib.h>
#include <pthread.h>

static void	img_put_pixel(t_mlxunit *unit, t_point point)
{
	if (point.ry * W_WIDTH + point.rx < PIC_LIMIT
	&& (point.ry * W_WIDTH + point.rx) < W_WIDTH * (point.ry + 1)
	&& (point.ry * W_WIDTH + point.rx) > W_WIDTH * point.ry
	&& point.ry >= 0 && point.rx >= 0
	&& (point.ry * W_WIDTH + point.rx >= 0))
		unit->picstr[point.ry * W_WIDTH + point.rx] = point.color;
}

static void	*split_print(void *param)
{
	int				i;
	t_thread_param	*tparam;
	t_point			p;
	t_mlxunit		*unit;

	tparam = (t_thread_param *)param;
	p = tparam->point;
	unit = tparam->unit;
	while (p.ry < tparam->maxy)
	{
		p.rx = -1;
		while (++p.rx < W_WIDTH)
		{
			i = unit->fract[unit->fractype](p, tparam->data);
			if (i < tparam->data.maxiter)
			{
				p.color = tparam->data.gradlist[i % (50 + tparam->data.maxiter)
				+ (unit->psychedelic_mode > 0 ? tparam->data.gradoffset : 0)];
				img_put_pixel(unit, p);
			}
		}
		p.ry++;
	}
	pthread_exit(0);
}

void		refresh_img(t_mlxunit *unit, t_data data)
{
	mlx_destroy_image(unit->mlx, unit->pic);
	unit->pic = mlx_new_image(unit->mlx, W_WIDTH, W_HEIGHT);
	unit->picstr = (int *)mlx_get_data_addr(unit->pic,
			&unit->a, &unit->b, &unit->c);
	data.gradlist = gradient_list(data.gradstart, data.gradend,
			(50 + data.maxiter) * 2);
	drawfract(unit, new_point(-1, -1, 0), data);
	free(data.gradlist);
	mlx_put_image_to_window(unit->mlx, unit->win, unit->pic, 0, 0);
}

void		drawfract(t_mlxunit *unit, t_point p, t_data data)
{
	t_thread_param	tparam[THREAD_LIMIT];
	pthread_t		thread_id[THREAD_LIMIT];
	int				i;

	i = 0;
	while (++p.ry < W_HEIGHT)
	{
		if (p.ry % (W_HEIGHT / THREAD_LIMIT) == 0)
		{
			setup_tparam(&tparam[i], p, data, unit);
			pthread_create(&thread_id[i], NULL, split_print, &tparam[i]);
			i++;
		}
	}
	while (i >= 0)
		pthread_join(thread_id[--i], NULL);
	if (unit->antialiasing > 0)
		antialiasing(unit);
}
