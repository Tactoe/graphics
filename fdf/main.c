/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 14:13:31 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/10 18:30:10 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fdf.h"
#include "libft/libft.h"
#include <fcntl.h>

int			main(int ac, char **av)
{
	t_data			data;
	t_mlxunit		unit;
	t_loop_param	param;
	int				fd;

	if (ac != 2)
		return (0);
	if ((fd = open(av[1], O_RDONLY)) < 0)
		ft_abort("Wrong file");
	data = get_data(fd, new_data());
	unit = new_unit(data);
	close(fd);
	print_map(data, &unit);
	param.data = data;
	param.unit = unit;
	mlx_do_key_autorepeaton(unit.mlx);
	mlx_put_image_to_window(unit.mlx, unit.win, unit.pic, 0, 0);
	mlx_key_hook(unit.win, end_prog, &param);
	mlx_loop(unit.mlx);
	return (0);
}
