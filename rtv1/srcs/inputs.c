/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <tmilon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 12:36:24 by tmilon            #+#    #+#             */
/*   Updated: 2018/05/24 15:26:53 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdlib.h>

static void		move_offset(double *offset, char c)
{
	*offset += (c == '+') ? 0.1f : -0.1f;
}

static int		update_event(t_event *touch, t_mlx *mlx)
{
	SDL_Event		event;
	int				key_code;

	while (SDL_PollEvent(&event))
	{
		key_code = event.key.keysym.scancode;
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			touch->key[key_code] = (event.type == SDL_KEYDOWN) ? 1 : 0;
			break ;
		}
		if (event.type == SDL_QUIT)
		{
			mlx->loop = 0;
			break ;
		}
	}
	return (0);
}

static int		translation(t_all *param, t_event touch)
{
	t_vector	*org;

	org = &param->scene.camera.origin;
	if (touch.key[RIGHT_KEY])
		move_offset(&org->x, '-');
	else if (touch.key[LEFT_KEY])
		move_offset(&org->x, '+');
	else if (touch.key[UP_KEY])
		move_offset(&org->y, '-');
	else if (touch.key[DOWN_KEY])
		move_offset(&org->y, '+');
	else if (touch.key[NUMPAD_PLUS])
		move_offset(&org->z, '-');
	else if (touch.key[NUMPAD_MINUS])
		move_offset(&org->z, '+');
	return (0);
}

static int		handle_escape(t_event t, int *loop)
{
	if (t.key[ESC])
		*loop = 0;
	return (0);
}

int				sdl_key(void *init)
{
	t_all		*param;
	t_event		t;
	int			valid_key;

	valid_key = 1;
	param = (t_all*)init;
	if (!(t.key = (char*)ft_memalloc(sizeof(char) * 300)))
		return (-1);
	update_event(&t, param->mlx);
	if (t.key[RIGHT_KEY] || t.key[LEFT_KEY] || t.key[UP_KEY] || t.key[DOWN_KEY]
			|| t.key[NUMPAD_PLUS] || t.key[NUMPAD_MINUS])
		translation(param, t);
	else if (t.key[W_KEY] || t.key[A_KEY] || t.key[S_KEY] || t.key[D_KEY]
			|| t.key[Q_KEY] || t.key[E_KEY])
		rotate_event(param, t);
	else if (t.key[R_KEY])
		param->data.fastmode *= -1;
	else
		valid_key = handle_escape(t, &param->mlx->loop);
	if (valid_key)
		refresh_img(*param);
	free(t.key);
	return (0);
}
