/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:53:16 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/14 15:26:57 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fractol.h"

int	interpolate(int start, int finish, float ratio)
{
	int		ret;
	t_color	a;
	t_color	b;

	a.r = start & 0x000000ff;
	a.g = start & 0x0000ff00;
	a.b = start & 0x00ff0000;
	b.r = finish & 0x000000ff;
	b.g = finish & 0x0000ff00;
	b.b = finish & 0x00ff0000;
	a.r = a.r + ((b.r - a.r) * ratio);
	a.g = a.g + ((b.g - a.g) * ratio);
	a.b = a.b + ((b.b - a.b) * ratio);
	ret = a.r | a.g | a.b;
	return (ret);
}

int	*gradient_list(int start, int finish, float steps)
{
	const int	colorlist[22] = { 0xfffafa, 0xffe4b5, 0x2f4f4f, 0x80, 0x87ceeb,
		0x7cfc00, 0xffffe0, 0xd2b48c, 0xff1493, 0x8a2be2, 0xeecbad, 0x838b83,
		0xee, 0x607b8b, 0x8ee5ee, 0x698b69, 0xb3ee3a, 0x8b8b00, 0xff6eb4,
		0xcd3278, 0x9b30ff, 0xd0d0d };
	int			*ret;
	int			i;

	if (steps > 3024)
		steps = 3024;
	if (!(ret = (int *)malloc(sizeof(int) * (steps + 1))))
		ft_abort("Malloc of gradientlist failed");
	i = -1;
	while (++i < steps)
		ret[i] = interpolate(colorlist[start], colorlist[finish], i / steps);
	return (ret);
}
