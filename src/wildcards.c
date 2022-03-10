/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:33:24 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/10 14:10:19 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_end_letters(char *d_name, char *s, int end)
{
	int	i;
	int	j;

	i = end + 1;
	j = 0;
	while (s[i] && d_name[j])
	{
		while(d_name[j] && d_name[j] != s[i])
			j++;
		if (!d_name[j])
			return (0);
		i++;
		j++;
	}
	return (1);
}

int	check_middle_end_letters(char *d_name, char *s, int start, int end)
{
	int	i;
	int	j;

	i = start;
	j = start;
	while (i < end)
	{
		if (s[i] != '*')
		{
			while(d_name[j] && d_name[j] != s[i])
				j++;
			if (!d_name[j])
				return (0);
		}
		i++;
	}
	if (ft_strlen(d_name + j) < ft_strlen(s + end + 1))
		return (0);
	else
		j += ft_strlen(d_name + j) - ft_strlen(s + end + 1);
	return (check_end_letters(d_name + j, s, end));
}

char	*ft_strdup_quote(const char *s)
{
	int		i;
	char	*ss;

	i = 0;
	if (!s)
		return (NULL);
	while (*(s + i))
		i++;
	ss = (char *)malloc(sizeof(char) * (i + 3));
	if (!ss)
		return (0);
	ss[i + 2] = 0;
	ss[i-- + 1] = '\'';
	while (i >= 1)
	{
		ss[i] = s[i];
		i--;
	}
	ss[0] = '\'';

	return (ss);
}


//Because we are in an universe with multiple worlds and instead ckecking only a little word, our ambitious make us checking WORLD ;-P
void	check_if_world_match(struct dirent *dirp, char *s, t_list **wilds, int start, int end)
{
	//char *temp;

	if (!ft_memcmp(dirp->d_name, ".", 1)
	|| (start != 0 && ft_memcmp(s, dirp->d_name, start))
	|| !check_middle_end_letters(dirp->d_name, s, start, end))
		return;
	else
	{
		/*
		if (*ss == NULL)
			*ss = ft_strdup_quote(dirp->d_name);
		else
		{
			temp = *ss;
			*ss = ft_strjoin(temp, " '");
			free(temp);
			if (*ss == NULL)
				return ;
			temp = *ss;
			*ss = ft_strjoin(temp, dirp->d_name);
			free(temp);
			temp = *ss;
			*ss = ft_strjoin(temp, "\'");
			free(temp);	
		}*/
		ft_lstadd_back(wilds, ft_lstnew(ft_strdup(dirp->d_name)));
	}
}

void	get_current_dir(char *s, t_list **wilds, int start, int end)
{
	DIR	*dp;
	char	*pwd;
	int	read_next;
	struct dirent *dirp;

	pwd = malloc(sizeof(char) * 4096);
	if (pwd == NULL)
		return ;
	if (getcwd(pwd,4096) == NULL)
	{
		free(pwd);
		return (perror("getcwd"));
	}
	dp = opendir(pwd);
	free(pwd);
	if (dp == NULL)
		return (perror("opendir"));
	read_next = 1;
	while(read_next)
	{
		dirp = readdir(dp);
		if (dirp == NULL)
			read_next = 0;
		else
			check_if_world_match(dirp, s, wilds, start, end);
	}
	if (closedir(dp))
		perror("closedir");
}

char	**ft_sort_str(t_list *wilds)
{
	char	**split;
	int	size;

	split = list_to_tab(wilds);
	if (split == NULL)
		return (0);
	size = 0;
	while (split[size])
		size++;
	ft_sort_vector(split, size);
	return (split);/*
	*wilds = ft_strjoin_vector(size, split, " ");
	if (*wilds == NULL)
		return (0);
	return (1);*/
}

char	**do_wildcards_word(char *s)
{
	t_list	*wilds;

	wilds = 0;
	get_current_dir(s, &wilds, ft_strchr(s, '*') - s, ft_strrchr(s, '*') - s);
	/*
	if (wild == NULL || !ft_sort_str(&wild))
	{
		*i = j -1;
		return NULL;
	}*/
	return (ft_sort_str(wilds));
	//printf("__%s__",wild);
	/*final = malloc(sizeof(char) * (ft_strlen(*s) - (end - start) + ft_strlen(wild) + 1));
	if (final == NULL && ft_sort_str(&wild))
	{
		*i = j -1;
		return 1;
	}
	//printf("%d %d\n", start, j);
	ft_memcpy(final, *s, start);
	ft_memcpy(final + start, wild, ft_strlen(wild));
	ft_memcpy(final + start + ft_strlen(wild), *s + end, ft_strlen(*s + end) + 1);
	free(*s);
	*s = final;
	*i = end;
	return (0);*/
}
/*
int	do_wildcards(char **s)
{
	int start;

	start = 0;
	while ((*s)[start])
	{
		if (start == 0 || (*s)[start] == ' ')
		{
			while ((*s)[start] == ' ')
				start++;
			do_wildcards_word(s, &start);
		}
		start++;
	}

	return (0);
}*/
