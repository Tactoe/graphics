/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 19:03:34 by tmilon            #+#    #+#             */
/*   Updated: 2018/02/06 19:38:45 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"

static void		free_list(void *content, size_t content_size)
{
	char	**tofree;
	int		i;

	i = 0;
	tofree = (char **)content;
	while (i < (int)(content_size / sizeof(content)))
		free(tofree[i++]);
	free(tofree);
}

static void		setpdata(char *str_numlist, int *z,
								int *color, int hascolor)
{
	char	**comma_split;
	int		colorpos;

	if (!hascolor)
	{
		*z = ft_atoi(str_numlist);
		*color = 0x00FFFFFF;
	}
	else
	{
		comma_split = ft_strsplit(str_numlist, ',');
		if (!comma_split[0])
			ft_abort("Blank commas detected. That's mean.");
		colorpos = (!ft_strchr(comma_split[0], 'x') ? 0 : 1);
		*z = ft_atoi(comma_split[colorpos]);
		*color = (int)hex2int(comma_split[(int)abs(colorpos - 1)]);
		free_multiarray(comma_split);
	}
}

static void		init_map(t_list *str_lst, t_data *d,
					int mwidth, int mheight)
{
	int		i;
	int		j;
	char	**nmlst;

	i = 0;
	if (!(d->coord = (t_point **)malloc(sizeof(t_point *) * (mheight))))
		ft_abort("Not enough memory");
	while (str_lst != NULL)
	{
		if (!(d->coord[i] = (t_point *)malloc(sizeof(t_point) * (mwidth))))
			ft_abort("Not enough memory");
		nmlst = ((char **)str_lst->content);
		j = 0;
		while (j < d->mapwidth)
		{
			if (ft_strchr(nmlst[j], ',') == NULL)
				setpdata(nmlst[j], &d->coord[i][j].z, &d->coord[i][j].color, 0);
			else
				setpdata(nmlst[j], &d->coord[i][j].z, &d->coord[i][j].color, 1);
			j++;
		}
		i++;
		str_lst = str_lst->next;
	}
}

static t_list	*read_data(int fd, int *retwidth, int *retheight)
{
	char	*line;
	t_list	*str_lst;
	int		curlen;
	char	**str_val;

	curlen = 0;
	str_lst = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		str_val = ft_strsplit(line, ' ');
		ft_strdel(&line);
		if (*retwidth == 0)
		{
			*retwidth = ft_countstrtab(str_val);
			curlen = *retwidth;
		}
		else if ((curlen = ft_countstrtab(str_val)) < *retwidth)
			ft_abort("Found wrong line length. Exiting.");
		ftb_lstpush(&str_lst, ft_lstnew(str_val, curlen * sizeof(str_val)));
		*retheight += 1;
		free(str_val);
	}
	if (curlen != 0)
		ft_strdel(&line);
	return (curlen == 0 ? NULL : str_lst);
}

t_data			get_data(int fd, t_data retdata)
{
	t_list	*str_lst;

	str_lst = read_data(fd, &retdata.mapwidth, &retdata.mapheight);
	if (!str_lst)
		ft_abort("Please do not send me directories. It's mean and useless :(");
	init_map(str_lst, &retdata, retdata.mapwidth, retdata.mapheight);
	ft_lstdel(&str_lst, free_list);
	return (retdata);
}
