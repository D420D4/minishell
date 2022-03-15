/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:33:24 by lcalvie           #+#    #+#             */
/*   Updated: 2022/03/15 02:54:45 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_start_sequence(char *sequence, char **d_name, char **s, int i)
{
	int	len_sequence;

	if (!sequence || sequence[0] == '\0')
	{
		free(sequence);
		return (1);
	}
	len_sequence = ft_strlen(sequence);
	if (ft_memcmp(sequence, *d_name, len_sequence))
	{
		free(sequence);
		return (0);
	}
	free(sequence);
	*d_name = *d_name + len_sequence;
	*s = *s + i + 1;
	return (1);
}

int	check_end_sequence(char *sequence, char *d_name)
{
	int	len;
	int	len_sequence;

	if (!sequence || sequence[0] == '\0')
	{
		free(sequence);
		return (1);
	}
	len = ft_strlen(d_name);
	len_sequence = ft_strlen(sequence);
	if (len < len_sequence)
	{
		free(sequence);
		return (0);
	}
	if (ft_memcmp(sequence, d_name + len - len_sequence, len_sequence + 1))
	{
		free(sequence);
		return (0);
	}
	free(sequence);
	return (1);
}
/*
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
*/

int	check_first_wildards(char **s, char **d_name, t_data *data)
{
	int	i;
	int	quote;
	char	*sub;

	i = 0;
	quote = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '*' && !quote)
		{
			sub = transform(ft_substr(*s, 0, i), data);
			if (!check_start_sequence(sub, d_name, s, i))
				return (0);
			else
				return (1);
		}
		else if ((*s)[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if ((*s)[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	return (1);
}

int	check_sequence(char *sequence, char **d_name)
{
	int	len;
	char	*search;

	if (!sequence || sequence[0] == '\0')
	{
		free(sequence);
		return (1);
	}
	len = ft_strlen(*d_name);
	search = ft_strnstr(*d_name, sequence, len);
	if (search == NULL)
	{
		free(sequence);
		return (0);
	}
	*d_name = search + ft_strlen(sequence);
	free(sequence);
	return (1);
}

int	check_wildards(char *s, char *d_name, t_data *data)
{
	int	i;
	int	quote;
	int	d;
	char	*sub;

	i = 0;
	d = 0;
	quote = 0;
	while (s[i])
	{
		if (s[i] == '*' && !quote)
		{
			sub = transform(ft_substr(s, d, i - d), data);
			if (!check_sequence(sub, &d_name))
				return (0);
			d = i + 1;
		}
		else if (s[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	sub = transform(ft_substr(s, d, i - d), data);
	if (!check_end_sequence(sub, d_name))
		return (0);
	return (1);
}

//Because we are in an universe with multiple worlds and instead ckecking only a little word, our ambitious make us checking WORLD ;-P
void	check_if_world_match(char *d_name, char *s, t_list **wilds, t_data *data)
{
	char	*temp;

	if (ft_memcmp(d_name, ".", 1))
	{
		temp = d_name;
		if (check_first_wildards(&s, &d_name, data))
		{
			if (check_wildards(s, d_name, data))
				ft_lstadd_back(wilds, ft_lstnew(ft_strdup(temp)));
		}
	}
}

void	get_current_dir(char *s, t_list **wilds, t_data *data)
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
			check_if_world_match(dirp->d_name, s, wilds, data);
	}
	if (closedir(dp))
		perror("closedir");
}

char	**ft_sort_str(t_list *wilds)
{
	char	**split;
	int	size;

	split = list_to_tab(wilds);
	ft_lstclear(&wilds, &free);
	if (split == NULL)
		return (0);
	size = 0;
	while (split[size])
		size++;
	ft_sort_vector(split, size);
	return (split);
}

char	**do_wildcards_word(char *s, t_data *data)
{
	t_list	*wilds;
	char	*cpy;

	wilds = 0;
	cpy = ft_strdup(s);
	if (!cpy)
		return (NULL);
	get_current_dir(cpy, &wilds, data);
	free(cpy);
	return (ft_sort_str(wilds));
}
