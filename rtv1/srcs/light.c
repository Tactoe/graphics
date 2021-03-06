/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 10:50:35 by tmilon            #+#    #+#             */
/*   Updated: 2018/05/27 14:14:34 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

static double	get_intensity(t_intersect inter, t_light light, t_data data)
{
	t_vector	lightdir;
	double		intensity;

	lightdir = vector_op(light.origin, inter.point, '-');
	intensity = dotprod(normalize(lightdir), normalize(inter.normal));
	intensity = intensity <= 0 ? data.ambiantlight :
		intensity * light.intensity * 2 + data.ambiantlight;
	intensity = intensity >= 1 ? 1 : intensity;
	return (intensity);
}

static int		fuse(int start, int finish, int ratio)
{
	t_color	a;
	t_color	b;

	a = int_to_color(start);
	b = int_to_color(finish);
	a.r = a.r + b.r / ratio;
	a.g = a.g + b.g / ratio;
	a.b = a.b + b.b / ratio;
	return (color_to_int(a));
}

double			cartoon(double i)
{
	if (i > 0 && i < 0.4)
		i = 0;
	if (i > 0.4 && i < 0.8)
		i = 0.4;
	if (i > 0.8 && i < 1)
		i = 0.8;
	return (i);
}
static double	brillance_intensity(t_intersect inter, t_light light)
{
	t_vector	lightdir;
	double		intensity;
	t_vector	reflect;

	lightdir = vector_op(light.origin, inter.point, '-');
	intensity = 2 * dotprod(inter.normal, lightdir);
	reflect = vector_op(new_vector_unicoord(intensity), inter.normal, '*');
	reflect = vector_op(reflect, lightdir, '-');
	intensity = dotprod(reflect,
			vector_op(inter.dir_to_cam, new_vector_unicoord(-1), '*'));
	intensity = intensity < 0 ? 0 : intensity;
	intensity = pow(intensity, 14 / (get_length(lightdir) + 0.01));
	intensity *= inter.shape_copy.brillance * light.intensity;
	intensity = intensity > 1 ? 1 : intensity;
	//intensity = cartoon(intensity);
	return (intensity);
}

static int	shadows(t_list *shape_lst, t_intersect inter, t_light light)
{
	t_ray		ray;
	t_vector	dir;
	t_vector	rayorigin;
	double		dist;

	rayorigin = vector_op(inter.normal, new_vector_unicoord(0.00001), '*');
	rayorigin = vector_op(inter.point, rayorigin, '+');
	dir = vector_op(light.origin, rayorigin, '-');
	ray = new_ray(rayorigin, normalize(dir));
	dist = get_length(dir);
	return (get_nearest_intersection(ray, shape_lst, &inter, dist));
}

int			set_color(t_list *light_lst, t_list *shape_lst,
		t_intersect intersection, t_data data)
{
	int			ret;
	int			tmp;
	double		intensity;
	t_light		light;

	ret = 0;
	while (light_lst != NULL)
	{
		light = *(t_light*)light_lst->content;
		if (light.color == -1)
			break ;
		intensity = get_intensity(intersection, light, data);
		//intensity = cartoon(intensity);
		tmp = interpolate(0, intersection.shape_copy.color, intensity);
		if (!shadows(shape_lst, intersection, light))
			tmp = interpolate(tmp, light.color,
					brillance_intensity(intersection, light));
		else
			tmp = interpolate(tmp, 0, light.intensity - data.ambiantlight < 0 ? 0 : light.intensity - data.ambiantlight);
		if (!ret)
			ret = tmp;
		else
			ret = fuse(ret, tmp, data.nb_light);
		light_lst = light_lst->next;
	}
	return (ret);
}
