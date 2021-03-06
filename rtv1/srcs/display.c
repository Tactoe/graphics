/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <tmilon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:02:53 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/02 10:58:29 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

t_intersect	new_intersection(t_shape shape, t_ray ray, double point_dist)
{
	t_vector	tmp;
	t_intersect	ret;
	t_vector	(*normals[10])(t_shape shape, t_vector inter);

	normals[SPHERE] = &sphere_normal;
	normals[PLANE] = &plane_normal;
	normals[CYLINDER] = &cylinder_normal;
	normals[CONE] = &cone_normal;
	shape.origin = adjust_direction(shape.origin, shape.inv_rot);
	ret.point = vector_op(ray.origin, shape.origin, '-');
	tmp = vector_op(ray.direction, new_vector_unicoord(point_dist), '*');
	ret.point = vector_op(ret.point, tmp, '+');
	ret.normal = normalize(normals[shape.type](shape, ret.point));
	shape.color = texture(shape.color, ret, shape);
	ret.shape_copy = shape;
	if (shape.type == PLANE)
	{
		if (dotprod(ray.direction, ret.normal) > DIST_MIN)
			ret.normal = vector_op(ret.normal, new_vector_unicoord(-1), '*');
	}
	ret.point = vector_op(ret.point, shape.origin, '+');
	ret.point = adjust_direction(ret.point, shape.rot);
	ret.normal = adjust_direction(ret.normal, shape.rot);
	ret.normal = normalize(ret.normal);
	ret.dir_to_cam = adjust_direction(ray.direction, shape.rot);
	return (ret);
}

int				get_nearest_intersection(t_ray ray, t_list *shape_lst,
					t_intersect *nearest_intersect, double maxdist)
{
	int			(*collisions[10])(t_shape shape, t_ray ray, double *t);
	t_shape		shape;
	t_shape		nearest_shape;

	collisions[SPHERE] = &intersect_sphere;
	collisions[PLANE] = &intersect_plane;
	collisions[CYLINDER] = &intersect_cylinder;
	collisions[CONE] = &intersect_cone;
	nearest_shape.color = 0;
	while (shape_lst != NULL)
	{
		shape = *(t_shape*)shape_lst->content;
		if (shape.type == -1)
			break ;
		if (collisions[shape.type](shape,
					adapt_ray(ray, shape.inv_rot), &maxdist))
			nearest_shape = shape;
		shape_lst = shape_lst->next;
	}
	if (nearest_shape.color)
		*nearest_intersect = new_intersection(nearest_shape,
				adapt_ray(ray, nearest_shape.inv_rot), maxdist);
	return (nearest_shape.color ? 1 : 0);
}

static void	raytrace(t_scene env, int *colorarray, t_point p, t_data data)
{
	t_ray		ray;
	t_vector	direction;
	t_intersect	intersection;

	direction = set_axe(p.x, p.y, &(env.camera));
	ray = new_ray(env.camera.origin, normalize(direction));
	if (get_nearest_intersection(ray, env.shape_lst, &intersection, DIST_MAX))
	{
		p.color = set_color(env.light_lst, env.shape_lst, intersection, data);
		colorarray[p.x + p.y *W_WIDTH] = p.color;
	}
}

static void	*raytrace_thread(void *voidparam)
{
	t_all	*param;
	t_point	p;
	t_data	data;
	t_scene	env;

	param = (t_all*)voidparam;
	p = param->point;
	data = param->data;
	env = param->scene;
	while (p.y < param->maxy)
	{
		p.x = -1;
		if (p.y % 5 == 0 || data.fastmode == -1)
			while (++p.x < W_WIDTH)
				if (p.x % 5 == 0 || data.fastmode == -1)
					raytrace(env, param->colorarray, p, data);
		p.y++;
	}
	pthread_exit(0);
}

void		setup_multithread(t_all param)
{
	t_point	p;
	t_all	tparam[THREAD_LIMIT];
	pthread_t	thread_id[THREAD_LIMIT];
	int			i;

	i = 0;
	p = new_point(-1, -1, 0);
	param.colorarray = malloc(PIC_LIMIT * sizeof(int));
	while (++p.y < W_HEIGHT)
	{
		if (p.y % (W_HEIGHT / THREAD_LIMIT) == 0)
		{
			ft_memcpy((void*)&tparam[i], (void*)&param, sizeof(t_all));
			tparam[i].point = p;
			tparam[i].maxy = p.y + (W_HEIGHT / THREAD_LIMIT);
			pthread_create(&thread_id[i], NULL, raytrace_thread, &tparam[i]);
			i++;
		}
	}
	while (i >= 0)
		pthread_join(thread_id[--i], NULL);
	p = new_point (-1, -1, 0);
	while (++p.y < W_HEIGHT)
	{
		p.x = -1;
		while (++p.x < W_WIDTH)
		{
			p.color = param.colorarray[p.x + p.y * W_WIDTH];
			img_put_pixel(param.mlx, p);
		}
	}
}
