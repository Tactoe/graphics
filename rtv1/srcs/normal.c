/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <tmilon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:51:48 by tmilon            #+#    #+#             */
/*   Updated: 2018/05/27 14:15:03 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	sphere_normal(t_shape shape, t_vector i_point)
{
	(void)shape;
	//i_point.y = cos(i_point.y / 10) * (get_length(i_point) / 10);
	return (i_point);
}

t_vector	plane_normal(t_shape shape, t_vector i_point)
{
	(void)shape;
	(void)i_point;
	return (new_vector(0, 1, 0));
}

t_vector	cylinder_normal(t_shape shape, t_vector i_point)
{
	t_vector	normal;

	(void)shape;
	normal = new_vector(i_point.x, 0, i_point.z);
	return (normal);
}

t_vector	cone_normal(t_shape shape, t_vector i_point)
{
	t_vector	normal;

	normal = new_vector(i_point.x, shape.radius, i_point.z);
	return (normal);
}
