/* ************************************************************************** */
/*                                                */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 14:06:23 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/05 19:48:23 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

t_color new_color(int a, int b, int c)
{
	t_color ret;

	ret.r = a;
	ret.g = b;
	ret.b = c;
	return (ret);
}

int	coloralter(int color, double u, double v)
{
	int size = 60;
	int rainbowsize = size * 6;
	t_color	*rainbow;
	int	i;

	i = 0;
	rainbow = malloc(sizeof(t_color) * (rainbowsize + 1));
	for (int r = 0; r < size; r++)
	{
		rainbow[i] = new_color(r * 255 / size, 255, 0);
		i++;
	}
	for (int g = size; g > 0; g--) 
	{
		rainbow[i] = new_color(255, g * 255 / size ,0);
		i++;
	}
	for (int b=0; b<size; b++)
	{
		rainbow[i] = new_color(255, 0, b * 255 / size);
		i++;
	}
	for (int r=size; r>0; r--)
	{
		rainbow[i] = new_color(r * 255 / size, 0, 255);
		i++;
	}
	for (int g=0; g<size; g++)
	{
		rainbow[i] = new_color(0, g * 255 / size, 255);
		i++;
	}
	for (int b=size; b>0; b--)
	{
		rainbow[i] = new_color(0, 255, b * 255 / size);
		i++;
	}
	rainbow[i] = new_color(0, 255, 0);
	color = interpolate(color, color_to_int(rainbow[(int)(v * rainbowsize * 4) % rainbowsize]),0.9);
	free(rainbow);
	return (color);
}

int	checker_pattern(int color, double u, double v)
{
	u *= 10;
	v *= 10;
	if (((int)u % 2 == 0 && (int)v % 2 == 0)
	|| (((int)u % 2 != 0 && (int)v % 2 != 0)))
			color = interpolate(color, (0xFFFFFF - color), 0.3);
	return (color);
	
}

int	get_texture_color(double u, double v, t_shape s)
{
	double	modif;
	double	tmpmodif;
	double reduc;
	double uback;
	double vback;

	vback = v;
	uback = u;
	modif = s.textunit.texture_width;
	//printf("Modif is %f \n", modif);
	if (s.type == PLANE)
	{
		u = u * modif / (s.width  * 2 * s.textunit.xscale);
		v = v * modif / (s.width  * 2 * s.textunit.yscale);
		u += modif;
		v += modif;
		//u += 100;
		//v += 100;
		//modif = modif / 2;
		//u += tmpmodif;
		//v += tmpmodif;
		//u += s.width;
		/*
		if (s.textunit.xscale < 1)
			u += modif ;
		else
			u = (u + modif) / 2;
		if (s.textunit.yscale < 0.5)
			reduc = -5 + s.textunit.yscale * 10;
		else if (s.textunit.yscale < 1)
			reduc = 0.5 - s.textunit.yscale;
		else
			reduc = 0.5 - s.textunit.yscale;
		v += modif * 0.5;*/
	}
	else if (s.type == SPHERE)
	{
		u = u * modif / (s.textunit.xscale);
		v = v * modif / (s.textunit.yscale);
		//u = u * modif / (s.radius);
		//v = v * modif / (s.radius);
		//u += 100;
		//v += 100;
		//u += modif * 0.5;
		//v += modif * 0.5;
	}
	else if (s.type == CYLINDER)
	{
		u = u * modif / (s.textunit.xscale);
		v = v * modif / (s.textunit.yscale);
		//u += modif * (s.radius);
		//v += modif * ( s.height );
	}
	else if (s.type == CONE)
	{
		u = u * modif / (s.textunit.xscale);
		v = v * modif / (s.textunit.yscale);
		//u += modif * (s.radius);
		//v += modif * ( s.height / 2);
	}
	u = (int)u % (int)modif;
	v = (int)v % (int)modif;
	//printf("u %f v %f got converted to u %f v %f\n",uback, vback,  ceil(u), ceil(v));
	if ((int)u + (int)v * modif < modif * modif && (int)u >= 0 && (int)v >= 0 && (int)v < modif && (int)u < modif)
	{
		//if (uback >= 0.9)
		return (s.textunit.texture[(int)u + (int)((int)v * modif)]);
	}else
		return(0);
}

void		get_uv_mapping_coord(double *u, double *v, t_intersect i, t_shape s)
{
	if (s.type == PLANE)
	{
		*u = i.point.x + s.width * (s.textunit.xscale);
		*v = -i.point.z + s.width * (s.textunit.yscale);
	}
	if (s.type == SPHERE)
	{
		*u = 0.5 + (atan2(i.normal.z, i.normal.x) / (2 * PI));
		*v = 0.5 - (asin(i.normal.y) / PI);
	}
	else if (s.type == CYLINDER)
	{
		*u = 0.5 + atan2(i.normal.z, i.normal.x) / (2 * PI);
		*v = i.point.y / s.height;
	}
	else if (s.type == CONE)
	{
		*u = 0.5 + atan2(i.normal.z, i.normal.x) / (2 * PI);
		*v = i.point.y / s.height;
	}
}

int			texture(int color, t_intersect i, t_shape s)
{
	double u;
	double v;

	get_uv_mapping_coord(&u, &v, i, s);
	if (s.textunit.has_texture)
		color = get_texture_color(u, v, s);
	//color = checker_pattern(color, u, v);
	//color = coloralter(color, u, v);
	return (color);
}
