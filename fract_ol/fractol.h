/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:11:20 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/14 16:54:17 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define W_WIDTH 600
# define W_HEIGHT 400
# define PIC_LIMIT W_WIDTH * W_HEIGHT
# define THREAD_LIMIT 40
# define MOTION_NOTIFY 6
# define PTR_MOTION_MASK (1L<<6)
# define SPACEBAR 49
# define A_KEY 0
# define R_KEY 15
# define ONE_KEY 18
# define TWO_KEY 19
# define THREE_KEY 20
# define MINUS 27
# define PLUS 24
# define NUMPAD_MINUS 78
# define NUMPAD_PLUS 69
# define LEFT_BRACKET 33
# define RIGHT_BRACKET 30
# define ESC 53
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define UP_KEY 126
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define SCROLL_UP 4
# define SCROLL_DOWN 5

typedef struct	s_point
{
	int		rx;
	int		ry;
	int		z;
	int		color;
}				t_point;

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct	s_data
{
	double	rparam;
	double	iparam;
	double	xoffset;
	double	yoffset;
	double	zoom;
	int		maxiter;
	int		gradstart;
	int		gradend;
	int		gradoffset;
	int		*gradlist;
}				t_data;

typedef struct	s_calcunit
{
	double		re;
	double		im;
	double		tmp;
	double		mandelre;
	double		mandelim;
	float		**depth;
}				t_calcunit;

typedef struct	s_mlxunit
{
	void	*mlx;
	void	*win;
	void	*pic;
	int		*picstr;
	int		a;
	int		b;
	int		c;
	int		antialiasing;
	int		fractype;
	int		update_w_mouse_mv;
	int		psychedelic_mode;
	int		(*fract[3])(t_point p, t_data data);
}				t_mlxunit;

typedef struct	s_thread_param
{
	t_point		point;
	t_mlxunit	*unit;
	t_data		data;
	int			maxy;
}				t_thread_param;

typedef struct	s_loop_param
{
	t_data		data;
	t_mlxunit	unit;
}				t_loop_param;

/*
 ** Initstruct
*/
t_data			new_data(double r, double i, int max);
t_mlxunit		new_unit(int fractype);
t_point			new_point(int x, int y, int color);
t_loop_param	new_lparam(int fractype);
void			setup_tparam(t_thread_param *tp, t_point p,
								t_data data, t_mlxunit *unit);

/*
 ** Input functs
*/
int				ft_key(int keycode, void *param);
int				ft_click_mouse(int button, int x, int y, void *param);
int				ft_move_mouse(int x, int y, void *param);

/*
 ** Display functs
*/
int				interpolate(int start, int finish, float ratio);
int				*gradient_list(int start, int finish, float steps);
void			antialiasing(t_mlxunit *unit);
void			refresh_img(t_mlxunit *unit, t_data data);
void			drawfract(t_mlxunit *unit, t_point p, t_data data);

/*
 ** Functs for fractal calculation
*/
int				julia(t_point p, t_data data);
int				mandelbrot(t_point p, t_data data);
int				ship(t_point p, t_data data);

/*
 ** Utils
*/
int				is_within_bounds(int i);
int				surrounding_pixels_differ(t_mlxunit *unit, int i);
#endif
