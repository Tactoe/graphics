/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <tmilon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:50:46 by tmilon            #+#    #+#             */
/*   Updated: 2018/05/29 12:34:03 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

int	resolve_quadratic_equation(t_calcunit *calc, double *t)
{
	double	tmp;

	calc->delta = (calc->b * calc->b) - (4.0 * calc->a * calc->c);
	if (calc->delta < 0)
		return (0);
	calc->delta = sqrt(calc->delta);
	calc->t0 = (-calc->b - calc->delta) / (2.0 * calc->a);
	calc->t1 = (-calc->b + calc->delta) / (2.0 * calc->a);
	tmp = calc->t0;
	calc->t0 = (calc->t0 < calc->t1 ? calc->t0 : calc->t1);
	calc->t1 = (calc->t1 == calc->t0 ? tmp : calc->t1);
	calc->t0 = ((calc->t0 > *t) || (calc->t0 <= DIST_MIN)) ? -1 : calc->t0;
	calc->t1 = ((calc->t1 > *t) || (calc->t1 <= DIST_MIN)) ? -1 : calc->t1;
	return (calc->t0 == -1 && calc->t1 == -1 ? 0 : 1);
}

int	intersect_sphere(t_shape shape, t_ray ray, double *t)
{
	t_calcunit	calc;

	shape.origin = adjust_direction(shape.origin, shape.inv_rot);
	shape.origin = vector_op(ray.origin, shape.origin, '-');
	calc.a = dotprod(ray.direction, ray.direction);
	calc.b = 2 * dotprod(ray.direction, shape.origin);
	calc.c = dotprod(shape.origin, shape.origin) - shape.radius * shape.radius;
	if (resolve_quadratic_equation(&calc, t))
		limit_sphere(shape, ray, t, calc);
	return (*t == calc.t0 || *t == calc.t1 ? 1 : 0);
}

int	intersect_plane(t_shape shape, t_ray ray, double *t)
{
	double		a;
	double		width;
	double		length;
	double		dist;
	t_vector	norm;

	norm = new_vector(0, 1, 0);
	norm = normalize(norm);
	if ((a = dotprod(ray.direction, norm)) == 0)
		return (0);
	shape.origin = adjust_direction(shape.origin, shape.inv_rot);
	shape.origin = vector_op(ray.origin, shape.origin, '-');
	dist = -dotprod(shape.origin, norm) / a;
	if (dist <= DIST_MIN || dist >= *t)
		return (0);
	width = shape.origin.x + (dist * ray.direction.x);
	length = shape.origin.z + (dist * ray.direction.z);
	if ((width >= -shape.width) && (width < shape.width)
			&& (length >= -shape.width) && (length < shape.width)
			&& width * width + length * length < 10000)
		*t = dist;
	return (*t == dist ? 1 : 0);
}

int	intersect_cylinder(t_shape shape, t_ray ray, double *t)
{
	t_calcunit	calc;
	double		get_in;
	double		get_out;

	shape.origin = adjust_direction(shape.origin, shape.inv_rot);
	shape.origin = vector_op(ray.origin, shape.origin, '-');
	calc.a = ray.direction.x * ray.direction.x
				+ ray.direction.z * ray.direction.z;
	calc.b = 2.0 * (ray.direction.x * shape.origin.x
			+ ray.direction.z * shape.origin.z);
	calc.c = shape.origin.x * shape.origin.x +
		shape.origin.z * shape.origin.z - shape.radius * shape.radius;
	if (resolve_quadratic_equation(&calc, t))
		limit_cylinder(shape, ray, t, calc);
	return (*t == calc.t0 || *t == calc.t1 ? 1 : 0);
}

int	intersect_cone(t_shape shape, t_ray ray, double *t)
{
	t_calcunit	calc;
	double		get_in;
	double		get_out;

	shape.origin = adjust_direction(shape.origin, shape.inv_rot);
	shape.origin = vector_op(ray.origin, shape.origin, '-');
	calc.a = ray.direction.x * ray.direction.x + ray.direction.z
	* ray.direction.z + (-shape.radius * (ray.direction.y * ray.direction.y));
	calc.b = 2.0 * ((ray.direction.x * shape.origin.x + ray.direction.z
	* shape.origin.z) + (-shape.radius * ray.direction.y * shape.origin.y));
	calc.c = (shape.origin.x * shape.origin.x + shape.origin.z
	* shape.origin.z) + (-shape.radius * shape.origin.y * shape.origin.y);
	if (resolve_quadratic_equation(&calc, t))
		limit_cone(shape, ray, t, calc);
	return (*t == calc.t0 || *t == calc.t1 ? 1 : 0);
}
