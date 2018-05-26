/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fracts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:24:33 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/14 15:27:28 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

int		julia(t_point p, t_data data)
{
	int			i;
	t_calcunit	calcu;

	calcu.re = 1.5 * (p.rx - W_WIDTH / 2) / (data.zoom * W_WIDTH)
		+ data.xoffset;
	calcu.im = (p.ry - W_HEIGHT / 2) / (data.zoom * W_HEIGHT) + data.yoffset;
	i = 0;
	while ((calcu.re * calcu.re + calcu.im * calcu.im) <= 4
			&& i++ < data.maxiter && i < 8000)
	{
		calcu.tmp = calcu.re;
		calcu.re = calcu.re * calcu.re -
			calcu.im * calcu.im + data.rparam;
		calcu.im = 2 * calcu.tmp * calcu.im + data.iparam;
	}
	return (i);
}

int		ship(t_point p, t_data data)
{
	int			i;
	t_calcunit	calcu;

	calcu.mandelre = 1.5 * (p.rx - W_WIDTH / 2) / (data.zoom * W_WIDTH)
		+ data.xoffset;
	calcu.mandelim = (p.ry - W_HEIGHT / 2) / (data.zoom * W_HEIGHT)
		+ data.yoffset;
	i = 0;
	calcu.re = 0;
	calcu.im = 0;
	calcu.tmp = 0;
	while ((calcu.re * calcu.re + calcu.im * calcu.im) <= 4
			&& i++ < data.maxiter && i < 8000)
	{
		calcu.tmp = calcu.re;
		calcu.re = calcu.re * calcu.re - calcu.im * calcu.im
			+ calcu.mandelre;
		calcu.im = 2 * fabs(calcu.tmp * calcu.im) + calcu.mandelim;
	}
	return (i);
}

int		mandelbrot(t_point p, t_data data)
{
	int			i;
	t_calcunit	calcu;

	calcu.mandelre = 1.5 * (p.rx - W_WIDTH / 2) / (data.zoom * W_WIDTH)
		+ data.xoffset;
	calcu.mandelim = (p.ry - W_HEIGHT / 2) / (data.zoom * W_HEIGHT)
		+ data.yoffset;
	i = 0;
	calcu.re = 0;
	calcu.im = 0;
	calcu.tmp = 0;
	while ((calcu.re * calcu.re + calcu.im * calcu.im) <= 4
			&& i++ < data.maxiter && i < 8000)
	{
		calcu.tmp = calcu.re;
		calcu.re = calcu.re * calcu.re - calcu.im * calcu.im
			+ calcu.mandelre;
		calcu.im = 2 * calcu.tmp * calcu.im + calcu.mandelim;
	}
	return (i);
}
