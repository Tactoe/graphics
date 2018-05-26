/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:51:42 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/14 15:51:04 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			ft_move_mouse(int x, int y, void *param)
{
	t_loop_param	*myparam;

	myparam = (t_loop_param*)param;
	if (myparam->unit.update_w_mouse_mv > 0)
	{
		myparam->data.rparam = (float)(x - W_WIDTH / 2) /
			(600 - myparam->data.zoom * 2);
		myparam->data.iparam = (float)(y - W_HEIGHT / 2) /
			(600 - myparam->data.zoom * 2);
		refresh_img(&myparam->unit, myparam->data);
	}
	return (0);
}

static void	zoom(int button, int x, int y, t_data *data)
{
	float	modifzoom;

	modifzoom = data->zoom / 10;
	if (button == SCROLL_UP)
	{
		data->gradoffset = data->gradoffset + 1 < 50 + data->maxiter ?
			data->gradoffset + 1 : 0;
		data->zoom += modifzoom;
	}
	else if (button == SCROLL_DOWN)
	{
		data->gradoffset = data->gradoffset - 1 >= 0 ?
			data->gradoffset - 1 : 50 + data->maxiter;
		data->zoom -= data->zoom > 0.2 ? modifzoom : 0;
	}
	data->xoffset += (float)(x - W_WIDTH / 2) /
		1000 / data->zoom;
	data->yoffset += (float)(y - W_HEIGHT / 2) /
		1000 / data->zoom;
}

int			ft_click_mouse(int button, int x, int y, void *param)
{
	t_loop_param	*myparam;

	myparam = (t_loop_param*)param;
	if (button == MOUSE_LEFT)
		myparam->unit.update_w_mouse_mv = -myparam->unit.update_w_mouse_mv;
	else if (button == MOUSE_RIGHT)
		myparam->unit.psychedelic_mode = -myparam->unit.psychedelic_mode;
	else if (button == SCROLL_UP || button == SCROLL_DOWN)
		zoom(button, x, y, &myparam->data);
	refresh_img(&myparam->unit, myparam->data);
	return (0);
}
