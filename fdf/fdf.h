/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 19:04:13 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/06 13:13:09 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct	s_point
{
	int		rx;
	int		ry;
	int		z;
	int		color;
}				t_point;

typedef struct	s_mlxunit
{
	void	*mlx;
	void	*win;
	void	*pic;
	int		*picstr;
	int		a;
	int		b;
	int		c;
}				t_mlxunit;

typedef struct	s_data
{
	int			mapwidth;
	int			mapheight;
	int			highest_z;
	int			tile_w;
	int			tile_h;
	int			window_w;
	int			window_h;
	int			xoffset;
	int			yoffset;
	int			z_factor;
	t_point		**coord;
}				t_data;

typedef struct	s_loop_param
{
	t_data		data;
	t_mlxunit	unit;
}				t_loop_param;

t_data			get_data(int fd, t_data retdata);
void			print_map(t_data data, t_mlxunit *mlxunit);
t_data			new_data(void);
t_mlxunit		new_unit(t_data data);
int				end_prog(int keycode, void *param);
#endif
