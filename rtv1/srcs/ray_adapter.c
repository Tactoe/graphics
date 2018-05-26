/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_adapter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:45:18 by tmilon            #+#    #+#             */
/*   Updated: 2018/05/21 12:02:29 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

double	matrix_det(t_mat mat)
{
	double	res;

	res = 0;
	res += mat.rgt.x * mat.up.y * mat.fwd.z;
	res += mat.up.x * mat.fwd.y * mat.rgt.z;
	res += mat.fwd.x * mat.rgt.y * mat.up.z;
	res -= mat.rgt.x * mat.fwd.y * mat.up.z;
	res -= mat.fwd.x * mat.up.y * mat.rgt.z;
	res -= mat.up.x * mat.rgt.y * mat.fwd.z;
	return (res);
}

t_mat	matrix_inv(t_mat mat)
{
	t_mat	ret;
	double	det;

	det = matrix_det(mat);
	if (det != 0)
	{
		ret.rgt = new_vector((mat.up.y * mat.fwd.z)
				- (mat.up.z * mat.fwd.y), (mat.rgt.z * mat.fwd.y)
				- (mat.rgt.y * mat.fwd.z), (mat.rgt.y * mat.up.z)
				- (mat.rgt.z * mat.up.y));
		ret.up = new_vector((mat.up.z * mat.fwd.x)
				- (mat.up.x * mat.fwd.z), (mat.rgt.x * mat.fwd.z)
				- (mat.rgt.z * mat.fwd.x), (mat.rgt.z * mat.up.x)
				- (mat.rgt.x * mat.up.z));
		ret.fwd = new_vector((mat.up.x * mat.fwd.y)
				- (mat.up.y * mat.fwd.x), (mat.rgt.y * mat.fwd.x)
				- (mat.rgt.x * mat.fwd.y), (mat.rgt.x * mat.up.y)
				- (mat.rgt.y * mat.up.x));
		ret.rgt = vector_op(ret.rgt, new_vector_unicoord(1.0 / det), '*');
		ret.up = vector_op(ret.up, new_vector_unicoord(1.0 / det), '*');
		ret.fwd = vector_op(ret.fwd, new_vector_unicoord(1.0 / det), '*');
		return (ret);
	}
	return (mat);
}

t_ray	adapt_ray(t_ray ray, t_mat mat)
{
	ray.origin = adjust_direction(ray.origin, mat);
	ray.direction = adjust_direction(ray.direction, mat);
	ray.direction = normalize(ray.direction);
	return (ray);
}
