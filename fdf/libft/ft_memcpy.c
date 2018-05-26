/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:06:13 by tmilon            #+#    #+#             */
/*   Updated: 2018/01/10 16:47:52 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*altsrc;
	char	*altdst;

	altsrc = (char *)src;
	altdst = (char *)dst;
	while (n--)
	{
		*altdst = *altsrc;
		altdst++;
		altsrc++;
	}
	return (dst);
}
