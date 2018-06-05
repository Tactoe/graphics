/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 11:11:20 by cpieri            #+#    #+#             */
/*   Updated: 2018/05/28 15:43:40 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "rtv1.h"
#include <stdio.h>

int		*surf_to_int_array(SDL_Surface *surf)
{
	t_color	c;
	Uint8	r;
	Uint8	g;
	Uint8	b;
	t_point	p;
	int		*tab;

	SDL_LockSurface(surf);
	p = new_point(-1, -1, 0);
	tab = NULL;
	tab = ft_memalloc(sizeof(int) * (surf->h * surf->pitch));
	while(++p.y < surf->h)
	{
		p.x = -1;
		while (++p.x < surf->pitch)
		{
			uint32_t pixel = *( ( uint32_t * )surf->pixels + p.y * surf->w + p.x);
			//SDL_GetRGB(pixel, surf->format, &r, &g, &b);
			c.r = (int)r;
			c.g = (int)g;
			c.b = (int)b;
			if (r != 0 || g != 0 || b != 0)
				printf("adding r %d g %d b%d\n",r,g,b);
			tab[p.y * surf->pitch + p.x] = color_to_int(c);
			//printf("added %d as int\n", color_to_int(c));
		}
	}
	SDL_UnlockSurface(surf);
	return (tab);
}

void	cpy_plane(t_shape *s, char **tab)
{
	char	*ok = "textures/lena_gray.bmp";
	SDL_Surface	*surf;

	if (ft_strcmp(ok, "") != 0)
	{
		surf = SDL_LoadBMP(ok);
		s->texture = surf_to_int_array(surf);
		SDL_FreeSurface(surf);
	}
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
