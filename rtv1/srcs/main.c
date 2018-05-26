/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <tmilon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:09:23 by tmilon            #+#    #+#             */
/*   Updated: 2018/05/25 13:03:38 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		launch(t_all *param, t_mlx *mlx)
{
	SDL_RenderPresent(mlx->rend);
	while (mlx->loop)
	{
		sdl_key(param);
	}
}

static t_all	init_param(t_all param)
{
	SDL_Init(SDL_INIT_VIDEO);
	param.mlx->win = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, 0);
	SDL_SetWindowMinimumSize(param.mlx->win, W_WIDTH, W_HEIGHT);
	param.mlx->rend = SDL_CreateRenderer(param.mlx->win, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(param.mlx->rend, 0x00, 0x00, 0x00, 1);
	SDL_RenderClear(param.mlx->rend);
	param.data.ambiantlight = 0.3f;
	param.mlx->loop = 1;
	param.data.fastmode = 1;
	return (param);
}

int				main(int ac, char **av)
{
	t_all	param;

	if (ac != 2)
		ft_abort("Usage: ./rtv1 [scene_file.csv]");
	if (!(param.mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		ft_abort("Malloc Failed: struct mlx");
	param = init_param(param);
	param.data.nb_light = parse(av[1], &param.scene);
	setup_multithread(param);
	launch(&param, param.mlx);
	SDL_DestroyRenderer(param.mlx->rend);
	SDL_DestroyWindow(param.mlx->win);
	SDL_Quit();
}
