/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 17:47:21 by cpieri            #+#    #+#             */
/*   Updated: 2018/05/27 14:12:26 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	img_put_pixel(t_mlx *unit, t_point point)
{
	t_color c;

	c = int_to_color(point.color);
	SDL_SetRenderDrawColor(unit->rend, c.r, c.g, c.b, 1);
	SDL_RenderDrawPoint(unit->rend, point.x, point.y);
}

void	refresh_img(t_all param)
{
	SDL_SetRenderDrawColor(param.mlx->rend, 0x00, 0x00, 0x00, 1);
	SDL_RenderClear(param.mlx->rend);
	setup_multithread(param);
	SDL_RenderPresent(param.mlx->rend);
}
