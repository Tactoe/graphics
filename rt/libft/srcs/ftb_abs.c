/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftb_abs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 13:39:14 by tmilon            #+#    #+#             */
/*   Updated: 2018/01/13 13:41:30 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ftb_abs(int n)
{
	if (n == -2147483648)
		return (2147483647);
	return (n < 0 ? -n : n);
}
