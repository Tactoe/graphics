/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 09:05:16 by cpieri            #+#    #+#             */
/*   Updated: 2018/05/23 09:24:05 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdlib.h>

void	parsing_quit(char *msg, char **splt_ln, char *ln)
{
	ft_putendl(msg);
	free_multiarray(splt_ln);
	free(ln);
	exit(-1);
}
