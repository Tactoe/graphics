/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 19:54:57 by tmilon            #+#    #+#             */
/*   Updated: 2018/01/04 15:01:17 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	time_to_stop(t_cont *cont)
{
	while (cont->char_to_print > cont->offset
			&& cont->buffer[cont->offset] != '\n')
		cont->offset++;
	if (cont->buffer[cont->offset] == '\n')
		return (cont->char_to_print > cont->offset);
	return (0);
}

static int	setup_line(t_cont **pcont, t_cont *cont, char **line, int fd)
{
	*line = ft_strsub(cont->buffer, 0, cont->offset);
	if (cont->char_to_print <= 0 && cont->rstate <= 0)
	{
		if (cont->buffer)
			ft_strdel(&cont->buffer);
		pcont[fd] = NULL;
		return (0);
	}
	cont->char_to_print -= cont->offset + (cont->rstate > 0
				&& cont->buffer[cont->offset] == '\n'
				&& cont->char_to_print != cont->offset);
	ft_memcpy(cont->buffer, &cont->buffer[cont->offset + 1],
			cont->char_to_print);
	cont->offset = 0;
	return (1);
}

static int	boost_buffer(t_cont *cont)
{
	char		*new_buffer;

	cont->length += BUFF_SIZE;
	if (!(new_buffer = malloc((cont->length + 1) * sizeof(char))))
		return (0);
	ft_strcpy(new_buffer, cont->buffer);
	new_buffer[cont->length] = '\0';
	free(cont->buffer);
	cont->buffer = new_buffer;
	return (1);
}

static int	setup(t_cont *cont)
{
	if (!(cont->buffer = malloc((BUFF_SIZE + 1) * sizeof(char))))
		return (0);
	cont->buffer[BUFF_SIZE] = '\0';
	cont->length = BUFF_SIZE;
	cont->char_to_print = 0;
	cont->offset = 0;
	cont->rstate = 1;
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	static t_cont	*cont;

	if (!cont)
		cont = (t_cont *)malloc(sizeof(t_cont *) * 2000);
	if (fd >= 2000 || fd < 0 || line == NULL
			|| (!cont[fd].buffer && !setup(&cont[fd])))
		return (-1);
	if (cont[fd].rstate == -1)
		setup(&cont[fd]);
	if (cont[fd].buffer && cont[fd].rstate == 0)
		return (0);
	while (cont[fd].rstate > 0 && !time_to_stop(&cont[fd]))
	{
		while (cont[fd].char_to_print + BUFF_SIZE > cont[fd].length)
			if (!boost_buffer(&cont[fd]))
				return (-1);
		if ((cont[fd].rstate =
		read(fd, cont[fd].buffer + cont[fd].char_to_print, BUFF_SIZE)) < 0)
			return (-1);
		cont[fd].char_to_print += cont[fd].rstate;
	}
	return (setup_line(&cont, &cont[fd], line, fd));
}
