/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:09:23 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/14 16:47:54 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fractol.h"
#include "libft/libft.h"

static int	input_is_valid(int ac, char *input)
{
	int ret;

	ret = -1;
	if (ac != 2 || !input ||
		(ft_strcmp(input, "mandelbrot") != 0 - ++ret
		&& ft_strcmp(input, "julia") != 1 - ++ret
		&& ft_strcmp(input, "ship") != 2 - ++ret))
	{
		ft_putendl("Valid inputs:\n1) mandelbrot\n2) julia\n3) ship");
		return (-1);
	}
	return (ret);
}

static void	launch(t_loop_param *param, t_mlxunit unit)
{
	mlx_put_image_to_window(unit.mlx, unit.win, unit.pic, 0, 0);
	mlx_mouse_hook(unit.win, ft_click_mouse, param);
	mlx_key_hook(unit.win, ft_key, param);
	mlx_hook(unit.win, MOTION_NOTIFY, PTR_MOTION_MASK, ft_move_mouse, param);
	mlx_loop(unit.mlx);
}

static void	print_man(void)
{
	ft_putendl("Instructions:\nRight click: Toggle psychedelic mode on/off");
	ft_putendl("1 / 2 / 3 : Switch fractal");
	ft_putendl("Left click or Spacebar: Stop tracking mouse position");
	ft_putendl("A: Toggle anti-aliasing on/off");
	ft_putendl("R: Reset zoom");
	ft_putendl("Numeric +/-: Change major color");
	ft_putendl("Left / Right bracket: Increase / decrease precision");
	ft_putendl("Numpad +/-: Change minor color");
	ft_putendl("Scrollwheel: Zoom");
}

int			main(int ac, char **av)
{
	int				fractype;
	t_loop_param	param;

	if ((fractype = input_is_valid(ac, av[1])) < 0)
		return (0);
	param = new_lparam(fractype);
	print_man();
	launch(&param, param.unit);
	return (0);
}
