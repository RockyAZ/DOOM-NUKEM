/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 20:15:12 by azaporoz          #+#    #+#             */
/*   Updated: 2018/05/25 13:37:55 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		save_rest(char **res, size_t i)
{
	char *trash_res;

	trash_res = *res;
	if ((*res)[i + 1])
	{
		*res = ft_strsub(*res, i + 1, ft_strlen(*res));
		ft_strdel(&trash_res);
	}
	else
		ft_strdel(res);
}

static void		ft_solver(int is_join, char **line, char **res, size_t i)
{
	char *trash_line;
	char *cp;

	if (is_join)
	{
		trash_line = *line;
		cp = ft_strsub(*res, 0, i);
		*line = ft_strjoin(*line, cp);
		ft_strdel(&trash_line);
		ft_strdel(&cp);
	}
	else
	{
		cp = ft_strnew(0);
		ft_strdel(line);
		*line = cp;
	}
	save_rest(res, i);
}

static int		check_res(t_line *getl, char **res, char **line)
{
	size_t	i;
	char	*tmp;

	i = -1;
	getl->err = 1;
	while (++i < ft_strlen(*res) && *res)
	{
		if ((*res)[i] == '\n')
		{
			if (i == 0 && *line && ft_strlen(*line) == 0)
				ft_solver(0, line, res, i);
			else
				ft_solver(1, line, res, i);
			return (1);
		}
	}
	tmp = *line;
	*line = ft_strjoin(*line, *res);
	ft_strdel(&tmp);
	ft_strdel(res);
	return (0);
}

static void		ft_read(t_line *getl, char **res, char **line)
{
	char buf[BUFF_SIZE + 1];

	if (read(getl->fd, buf, 0))
	{
		getl->err = -1;
		return ;
	}
	while ((getl->err = read(getl->fd, buf, BUFF_SIZE)))
	{
		buf[getl->err] = '\0';
		*res = ft_strjoin(*res, buf);
		if (check_res(getl, res, line))
			break ;
	}
}

int				get_next_line(const int fd, char **line)
{
	t_line		*getl;
	static char	*res[SIZE];

	if (fd < 0 || (unsigned long)fd > SIZE || BUFF_SIZE <= 0 || !line)
		return (-1);
	if (!(getl = (t_line*)malloc(sizeof(t_line))))
		return (-1);
	getl->fd = fd;
	*line = ft_strnew(0);
	if (res[fd] == NULL || !check_res(getl, &res[fd], line))
		ft_read(getl, &res[fd], line);
	if (getl->err == -1)
	{
		ft_strdel(line);
		ft_memdel((void*)&getl);
		return (-1);
	}
	if (getl->err == 0 && res[fd] == NULL && *line && ft_strlen(*line) == 0)
	{
		ft_strdel(line);
		ft_memdel((void*)&getl);
		return (0);
	}
	ft_memdel((void*)&getl);
	return (1);
}
