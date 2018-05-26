/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 13:35:35 by tmilon            #+#    #+#             */
/*   Updated: 2018/05/22 15:11:11 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

void	identity_mat(t_mat *mat)
{
	mat->rgt = new_vector(1, 0, 0);
	mat->up = new_vector(0, 1, 0);
	mat->fwd = new_vector(0, 0, 1);
}

void	rotate_x(t_mat *mat, double a)
{
	a *= DEG2RAD;
	mat->rgt = new_vector(1, 0, 0);
	mat->up = new_vector(0, cos(a), -sin(a));
	mat->fwd = new_vector(0, sin(a), cos(a));
}

void	rotate_y(t_mat *mat, double a)
{
	a *= DEG2RAD;
	mat->rgt = new_vector(cos(a), 0, sin(a));
	mat->up = new_vector(0, 1, 0);
	mat->fwd = new_vector(-sin(a), 0, cos(a));
}

void	rotate_z(t_mat *mat, double a)
{
	a *= DEG2RAD;
	mat->rgt = new_vector(cos(a), -sin(a), 0);
	mat->up = new_vector(sin(a), cos(a), 0);
	mat->fwd = new_vector(0, 0, 1);
}

void	rotate_event(t_all *param, t_event touch)
{
	t_camera	*cam;
	t_mat		mat;
	double		modif;

	modif = 5;
	cam = &param->scene.camera;
	if (touch.key[Q_KEY])
		rotate_z(&mat, modif);
	if (touch.key[E_KEY])
		rotate_z(&mat, -modif);
	if (touch.key[W_KEY])
		rotate_x(&mat, modif);
	if (touch.key[S_KEY])
		rotate_x(&mat, -modif);
	if (touch.key[A_KEY])
		rotate_y(&mat, modif);
	if (touch.key[D_KEY])
		rotate_y(&mat, -modif);
	cam->rot = matrix_mult(cam->rot, mat);
}
