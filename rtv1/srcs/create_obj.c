/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 11:11:20 by cpieri            #+#    #+#             */
/*   Updated: 2018/05/23 12:53:44 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "rtv1.h"

void	cpy_cylinder(t_shape *s, char **tab)
{
	s->origin = new_vector(ft_atof(tab[1]), ft_atof(tab[2]), ft_atof(tab[3]));
	s->radius = ft_atof(tab[8]);
	s->height = ft_atof(tab[10]);
	s->rot = new_matrix(ft_atof(tab[5]), ft_atof(tab[6]), ft_atof(tab[7]));
	s->inv_rot = matrix_inv(s->rot);
	s->type = CYLINDER;
	s->color = hex2int(tab[4]);
	s->brillance = ft_atof(tab[12]);
	return ;
}

void	cpy_cone(t_shape *s, char **tab)
{
	s->origin = new_vector(ft_atof(tab[1]), ft_atof(tab[2]), ft_atof(tab[3]));
	s->radius = ft_atof(tab[8]) * DEG2RAD;
	s->height = ft_atof(tab[10]);
	s->rot = new_matrix(ft_atof(tab[5]), ft_atof(tab[6]), ft_atof(tab[7]));
	s->inv_rot = matrix_inv(s->rot);
	s->type = CONE;
	s->color = hex2int(tab[4]);
	s->brillance = ft_atof(tab[12]);
	return ;
}

void	cpy_plane(t_shape *s, char **tab)
{
	s->origin = new_vector(ft_atof(tab[1]), ft_atof(tab[2]), ft_atof(tab[3]));
	s->width = ft_atof(tab[9]);
	s->rot = new_matrix(ft_atof(tab[5]), ft_atof(tab[6]), ft_atof(tab[7]));
	s->inv_rot = matrix_inv(s->rot);
	s->type = PLANE;
	s->color = hex2int(tab[4]);
	s->brillance = ft_atof(tab[12]);
	return ;
}

void	cpy_sphere(t_shape *s, char **tab)
{
	s->origin = new_vector(ft_atof(tab[1]), ft_atof(tab[2]), ft_atof(tab[3]));
	s->radius = ft_atof(tab[8]);
	s->rot = new_matrix(ft_atof(tab[5]), ft_atof(tab[6]), ft_atof(tab[7]));
	s->inv_rot = matrix_inv(s->rot);
	s->type = SPHERE;
	s->color = hex2int(tab[4]);
	s->brillance = ft_atof(tab[12]);
	return ;
}
