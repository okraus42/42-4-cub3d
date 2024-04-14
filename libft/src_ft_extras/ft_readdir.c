/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:15:21 by okraus            #+#    #+#             */
/*   Updated: 2024/04/14 12:06:06 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	**ft_list2split(t_list *lst)
{
	int		i;
	char	**files;
	char	*file;

	i = ft_lstsize(lst);
	files = malloc((sizeof(char *)) * (i + 1));
	if (!files)
		return (NULL);
	i = 0;
	while (lst)
	{
		file = lst->content;
		files[i] = ft_strdup(file);
		++i;
		lst = lst->next;
	}
	files[i] = NULL;
	return (files);
}

static void	ft_sortlst(t_list **head)
{
	int		sort;
	t_list	*lst;
	char	*thisfile;
	char	*nextfile;

	sort = 1;
	while (sort)
	{
		sort = 0;
		lst = *head;
		while (lst->next)
		{
			thisfile = lst->content;
			nextfile = lst->next->content;
			if (ft_strncmp(thisfile, nextfile, 1024) > 0)
			{
				lst->content = nextfile;
				lst->next->content = thisfile;
				sort = 1;
			}
			lst = lst->next;
		}
	}
}

static int	ft_check_extension(const char *string, const char *ext)
{
	int	i;
	int	len;

	len = ft_strlen(string);
	i = ft_strlen(ext);
	len -= i;
	while (i)
	{
		--i;
		if (string[len + i] != ext[i])
			return (1);
	}
	return (0);
}

static void	ft_addstr2lst(t_list **head, const char *string, const char *ext)
{
	t_list	*newlst;
	char	*file;

	if (ext && (ft_strlen(string) <= ft_strlen(ext)
			|| ft_check_extension(string, ext)))
		return ;
	file = ft_strdup(string);
	if (!file)
		return ;
	newlst = ft_lstnew(file);
	if (!newlst)
	{
		free(file);
		return ;
	}
	ft_lstadd_back(head, newlst);
}

char	**ft_readdir(const char *path, const char *extension)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;
	t_list			*lst;

	lst = NULL;
	dir = opendir(path);
	if (!dir)
	{
		ft_dprintf(2, "Error\nCannot open directory %s\n", path);
		return (NULL);
	}
	entry = readdir(dir);
	while (entry)
	{
		ft_addstr2lst(&lst, entry->d_name, extension);
		entry = readdir(dir);
	}
	closedir(dir);
	ft_sortlst(&lst);
	files = ft_list2split(lst);
	ft_lstclear(&lst, free);
	return (files);
}
