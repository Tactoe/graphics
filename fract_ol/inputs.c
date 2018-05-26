/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 12:36:24 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/14 17:02:22 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h>

static void	move_fract(int keycode, t_data *data)
{
	float	modif;

	modif = 0.3 / data->zoom;
	if (keycode == LEFT_KEY)
		data->xoffset -= modif;
	else if (keycode == RIGHT_KEY)
		data->xoffset += modif;
	else if (keycode == DOWN_KEY)
		data->yoffset += modif;
	else if (keycode == UP_KEY)
		data->yoffset -= modif;
}

static void	handle_gradient(int keycode, t_data *data)
{
	if (keycode == MINUS)
		data->gradstart -= data->gradstart > 0 ? 1 : 0;
	else if (keycode == PLUS)
		data->gradstart += data->gradstart < 22 ? 1 : 0;
	else if (keycode == NUMPAD_PLUS)
		data->gradend += data->gradend < 22 ? 1 : 0;
	else if (keycode == NUMPAD_MINUS)
		data->gradend -= data->gradend > 0 ? 1 : 0;
}

static void	change_or_reset(int keycode, t_loop_param *myparam)
{
	if (keycode == ONE_KEY)
		myparam->unit.fractype = 0;
	else if (keycode == TWO_KEY)
		myparam->unit.fractype = 1;
	else if (keycode == THREE_KEY)
		myparam->unit.fractype = 2;
	myparam->data = new_data(-0.3, 0.5, 300);
}

int			ft_key(int keycode, void *param)
{
	t_loop_param	*myparam;
	t_data			*data;

	if (keycode == ESC)
		exit(0);
	myparam = (t_loop_param *)param;
	data = &myparam->data;
	if (keycode >= LEFT_KEY && keycode <= UP_KEY)
		move_fract(keycode, data);
	else if (keycode == MINUS || keycode == PLUS
			|| keycode == NUMPAD_PLUS || keycode == NUMPAD_MINUS)
		handle_gradient(keycode, data);
	else if (keycode == R_KEY || (keycode >= ONE_KEY && keycode <= THREE_KEY))
		change_or_reset(keycode, myparam);
	else if (keycode == LEFT_BRACKET)
		data->maxiter -= data->maxiter > 50 ? data->maxiter / 10 : 0;
	else if (keycode == RIGHT_BRACKET)
		data->maxiter += data->maxiter < 100000 ? data->maxiter / 10 : 0;
	else if (keycode == SPACEBAR)
		myparam->unit.update_w_mouse_mv = -myparam->unit.update_w_mouse_mv;
	else if (keycode == A_KEY)
		myparam->unit.antialiasing = -myparam->unit.antialiasing;
	refresh_img(&myparam->unit, myparam->data);
	return (0);
}
