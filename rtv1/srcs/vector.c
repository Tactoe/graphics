/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 19:35:43 by tmilon            #+#    #+#             */
/*   Updated: 2018/04/12 15:58:40 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	normalize(t_vector v)
{
	double	length;

	length = get_length(v);
	return (new_vector(v.x / length, v.y / length, v.z / length));
}

t_vector	cross(t_vector a, t_vector b)
{
	return (new_vector(
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x - b.z,
				a.x * b.y - a.y * b.x));
}

t_vector	new_vector_unicoord(double value)
{
	t_vector	ret;

	ret.x = value;
	ret.y = value;
	ret.z = value;
	return (ret);
}

t_vector	new_vector(double x, double y, double z)
{
	t_vector	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vector	vector_op(t_vector a, t_vector b, char type)
{
	if (type == '-')
		return (new_vector(a.x - b.x, a.y - b.y, a.z - b.z));
	else if (type == '*')
		return (new_vector(a.x * b.x, a.y * b.y, a.z * b.z));
	else if (type == '/')
		return (new_vector(a.x / b.x, a.y / b.y, a.z / b.z));
	return (new_vector(a.x + b.x, a.y + b.y, a.z + b.z));
}
