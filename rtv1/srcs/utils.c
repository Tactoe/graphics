/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:35:29 by tmilon            #+#    #+#             */
/*   Updated: 2018/05/21 09:19:20 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

double	dotprod(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	get_length(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	magnitude(t_vector v)
{
	return (fabs(v.x) + fabs(v.y) + fabs(v.z));
}

void	ft_abort_free(char *msg, char *line)
{
	free(line);
	ft_abort(msg);
}
