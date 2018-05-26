/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <tmilon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:55:34 by tmilon            #+#    #+#             */
/*   Updated: 2018/05/23 13:20:30 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

t_light	new_light(t_vector origin, double intensity, int color)
{
	t_light	ret;

	ret.origin = origin;
	ret.intensity = intensity;
	ret.color = color;
	return (ret);
}

t_point	new_point(int x, int y, int color)
{
	t_point ret;

	ret.x = x;
	ret.y = y;
	ret.color = color;
	return (ret);
}

t_mat	new_matrix(double x, double y, double z)
{
	t_mat	ret;
	t_mat	tmp;

	identity_mat(&ret);
	rotate_x(&tmp, x);
	if (x)
		ret = matrix_mult(ret, tmp);
	rotate_y(&tmp, y);
	if (y)
		ret = matrix_mult(ret, tmp);
	rotate_z(&tmp, z);
	if (z)
		ret = matrix_mult(ret, tmp);
	return (ret);
}

t_ray	new_ray(t_vector o, t_vector d)
{
	t_ray	ret;

	ret.origin = o;
	ret.direction = d;
	return (ret);
}

t_scene	new_scene(t_list *shape_lst, t_list *light_lst)
{
	t_scene		ret;

	ret.shape_lst = shape_lst;
	ret.light_lst = light_lst;
	return (ret);
}
