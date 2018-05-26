/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 14:40:36 by cpieri            #+#    #+#             */
/*   Updated: 2018/05/19 15:49:00 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

static t_vector	build_row(t_vector src, t_mat add)
{
	double	a;
	double	b;
	double	c;

	a = (src.x * add.rgt.x) + (src.y * add.up.x) + (src.z * add.fwd.x);
	b = (src.x * add.rgt.y) + (src.y * add.up.y) + (src.z * add.fwd.y);
	c = (src.x * add.rgt.z) + (src.y * add.up.z) + (src.z * add.fwd.z);
	return (new_vector(a, b, c));
}

t_mat			matrix_mult(t_mat m1, t_mat m2)
{
	t_mat	ret;

	ret.rgt = build_row(m1.rgt, m2);
	ret.up = build_row(m1.up, m2);
	ret.fwd = build_row(m1.fwd, m2);
	return (ret);
}

t_vector		adjust_direction(t_vector src, t_mat mat)
{
	t_vector	ret;

	ret.x = mat.rgt.x * src.x + mat.rgt.y * src.y + mat.rgt.z * src.z;
	ret.y = mat.up.x * src.x + mat.up.y * src.y + mat.up.z * src.z;
	ret.z = mat.fwd.x * src.x + mat.fwd.y * src.y + mat.fwd.z * src.z;
	return (ret);
}
