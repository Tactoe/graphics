/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <tmilon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 17:15:16 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/02 10:53:50 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <SDL.h>
# include <stdio.h> // AVIRRER
# include "../libft/include/libft.h"

/*
 ******************************* Disp defines *********************************
*/

# define W_WIDTH			1280
# define W_HEIGHT			900
# define PIC_LIMIT			W_WIDTH * W_HEIGHT
# define DIST_MAX			2000000
# define DIST_MIN			0.00000001
# define THREAD_LIMIT		4
# define MOTION_NOTIFY		6
# define PI					3.141592653
# define DEG2RAD			0.01745329251
# define PTR_MOTION_MASK	(1L<<6)

/*
 ******************************* Keys defines *********************************
*/

# define Q_KEY				20
# define W_KEY				26
# define S_KEY				22
# define E_KEY				8
# define A_KEY				4
# define D_KEY				7
# define R_KEY				21
# define NUMPAD_MINUS		86
# define NUMPAD_PLUS		87
# define ESC				41
# define LEFT_KEY			80
# define RIGHT_KEY			79
# define DOWN_KEY			81
# define UP_KEY				82

/*
 ******************************* Item defines *********************************
*/

# define RAY_T_MIN			0.0001f
# define RAY_T_MAX			1.0e30f

# define SPHERE				0
# define CAMERA				1
# define LIGHT				2
# define PLANE				3
# define CONE				4
# define CYLINDER			5

/*
 ** Basic structs
*/

typedef struct		s_point
{
	int			x;
	int			y;
	int				color;
}					t_point;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_mat
{
	t_vector		fwd;
	t_vector		up;
	t_vector		rgt;
}					t_mat;

typedef struct		s_textunit
{
	int	has_texture;
	int	*texture;
	int	texture_width;
	double	xscale;
	double	yscale;
}					t_textunit;


typedef struct		s_calcunit
{
	double			a;
	double			b;
	double			c;
	double			delta;
	double			t0;
	double			t1;
	t_vector		get_in;
	t_vector		get_out;
}					t_calcunit;

/*
 ** Objects struct
*/

typedef struct		s_camera
{
	t_vector		origin;
	t_mat			rot;
	double			w;
	double			h;
	double			fov;
	double			aspect_ratio;
}					t_camera;

typedef struct		s_light
{
	t_vector		origin;
	double			intensity;
	int				color;
}					t_light;

typedef struct		s_shape
{
	int				type;
	int				color;
	t_vector		origin;
	double			height;
	double			width;
	double			radius;
	double			brillance;
	t_mat			rot;
	t_mat			inv_rot;
	t_textunit		textunit;
	void			*shape;
}					t_shape;

/*
 ** Structs for raytracing
*/

typedef struct		s_ray
{
	t_vector		origin;
	t_vector		direction;
}					t_ray;

typedef struct		s_intersect
{
	int				color;
	t_vector		point;
	t_vector		normal;
	t_vector		dir_to_cam;
	t_shape			shape_copy;
}					t_intersect;

/*
 ** SDL handling structs
*/

typedef struct		s_event
{
	char			*key;
}					t_event;

typedef struct		s_img
{
	void			*img_s;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
}					t_img;

typedef struct		s_mlx
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	t_img			img;
	int				loop;
	t_event			eve;
}					t_mlx;

/*
 ** Environement Struct
*/

typedef struct		s_data
{
	double			x_offset;
	double			y_offset;
	double			z_offset;
	double			zoom;
	double			ambiantlight;
	int				fastmode;
	int				nb_light;
}					t_data;

typedef struct		s_scene
{
	t_list			*shape_lst;
	t_list			*light_lst;
	t_camera		camera;
}					t_scene;

typedef struct		s_all
{
	t_scene			scene;
	t_mlx			*mlx;
	t_data			data;
	t_point			point;
	int				maxy;
	int				*colorarray;
}					t_all;

/*
 **	Calc_struct
*/

typedef struct		s_thread_param
{
	t_mlx			*unit;
	t_data			data;
	int				maxy;
}					t_thread_param;

/*
 ** Initstruct
*/

t_light				new_light(t_vector origin, double intensity, int color);
t_ray				new_ray(t_vector o, t_vector d);
t_point				new_point(int x, int y, int color);
t_shape				new_shape(int type, void *shape, int color);
t_scene				new_env(t_list *shape_lst, t_list *lightlist);
t_camera			new_cam(t_vector orig, double x, double y, double z);
t_mat				new_matrix(double x, double y, double z);

/*
 **	Vectors file
*/

t_vector			new_vector_unicoord(double f);
t_vector			new_vector(double x, double y, double z);
t_vector			vector_op(t_vector a, t_vector b, char type);
t_vector			cross(t_vector a, t_vector b);
t_vector			normalize(t_vector v);

/*
 ** Intersection checking
*/

int					intersect_sphere(t_shape shape, t_ray ray, double *t);
int					intersect_plane(t_shape shape, t_ray ray, double *t);
int					intersect_cylinder(t_shape shape, t_ray ray, double *t);
int					intersect_cone(t_shape shape, t_ray ray, double *t);

/*
 ** Normal fetchers
*/

t_vector			sphere_normal(t_shape shape, t_vector intersection_point);
t_vector			plane_normal(t_shape shape, t_vector intersection_point);
t_vector			cylinder_normal(t_shape shape, t_vector intersection_point);
t_vector			cone_normal(t_shape shape, t_vector intersection_point);

/*
 ** Display functs
*/

int					no_collisions(t_list *shape_lst,
		t_intersect inter, t_light light);
int					set_color(t_list *light_lst, t_list *shape_lst,
		t_intersect intersection, t_data data);
int					interpolate(int start, int finish, float ratio);
int					get_nearest_intersection(t_ray ray, t_list *shape_lst,
		t_intersect *nearest_intersect, double maxdist);
void				setup_multithread(t_all param);

/*
 **	Img file
*/

void				img_put_pixel(t_mlx *unit, t_point point);
void				refresh_img(t_all param);

/*
 **	Utils file
*/

double				get_vect_dist(t_vector a, t_vector b);
double				magnitude(t_vector v);
double				get_length(t_vector v);
double				dotprod(t_vector a, t_vector b);

/*
 **	rotate_matrice
*/

t_vector			adjust_direction(t_vector src, t_mat mat);
t_ray				adapt_ray(t_ray ray, t_mat mat);
t_mat				matrix_inv(t_mat mat);
t_mat				matrix_mult(t_mat m1, t_mat m2);
void				identity_mat(t_mat *src);
void				rotate_x(t_mat *src, double a);
void				rotate_y(t_mat *src, double a);
void				rotate_z(t_mat *src, double a);
void				rotate_event(t_all *param, t_event touch);

/*
 ** Limiters
*/

void				limit_sphere(t_shape shape, t_ray ray,
									double *t,t_calcunit calc);
void				limit_cylinder(t_shape shape, t_ray ray,
									double *t, t_calcunit calc);
void				limit_cone(t_shape shape, t_ray ray,
									double *t, t_calcunit calc);

/*
 ** Texture
*/

int			texture(int color, t_intersect i, t_shape s);

/*
 **	Camera
*/

t_vector			set_axe(int x, int y, t_camera *cam);

/*
 **	Parse
*/

t_light				cpy_light(char **tab);
void				cpy_cone(t_shape *shape, char **tab);
void				cpy_cylinder(t_shape *shape, char **tab);
void				cpy_sphere(t_shape *shape, char **tab);
void				cpy_plane(t_shape *shape, char **tab);
int					parse(char *file, t_scene *scene);
void				create_scene(char *s, t_scene *scene,
		int *nb_cam, int *nb_lght);
void				ft_abort_free(char *msg, char *line);
void				parsing_quit(char *msg, char **splt_ln, char *ln);

/*
 ** Colors
*/
int					sdl_key(void *init);
t_color				int_to_color(int n);
int					color_to_int(t_color c);

#endif
