/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <tmilon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:51:48 by tmilon            #+#    #+#             */
/*   Updated: 2018/05/21 11:53:24 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	sphere_normal(t_shape shape, t_vector intersection_point)
{
	(void)shape;
	return (intersection_point);
}

t_vector	plane_normal(t_shape shape, t_vector intersection_point)
{
	(void)shape;
	(void)intersection_point;
	return (new_vector(0, 1, 0));
}

t_vector	cylinder_normal(t_shape shape, t_vector intersection_point)
{
	t_vector	normal;

	(void)shape;
	normal = new_vector(intersection_point.x, 0, intersection_point.z);
	return (normal);
}

t_vector	cone_normal(t_shape shape, t_vector intersection_point)
{
	t_vector	normal;

	normal = new_vector(intersection_point.x, shape.radius,
			intersection_point.z);
	return (normal);
}
