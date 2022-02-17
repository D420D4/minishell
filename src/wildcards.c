/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:33:24 by lcalvie           #+#    #+#             */
/*   Updated: 2022/02/17 17:24:55 by lcalvie          ###   ########.fr       */
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

void	check_if_world_match(struct dirent *dirp, char *s, char **ss, int start, int end)
{
	char *temp;

	if (!ft_memcmp(dirp->d_name, ".", 1)
	|| (start != 0 && ft_memcmp(s, dirp->d_name, start))
	|| !check_middle_end_letters(dirp->d_name, s, start, end))
		return;
	else
	{
		if (*ss == NULL)
			*ss = ft_strdup(dirp->d_name);
		else
		{
			temp = *ss;
			*ss = ft_strjoin(temp, " ");
			free(temp);
			if (*ss == NULL)
				return ;
			temp = *ss;
			*ss = ft_strjoin(temp, dirp->d_name);
			free(temp);
		}
	}
}


void	get_current_dir(char *s, char **ss, int start, int end)
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
			check_if_world_match(dirp, s, ss, start, end);
	}
	if (closedir(dp))
		perror("closedir");
}

// retourne s si contient pas de wildcards sinon retourne ce qu il est cense retourner
// reste a faire : inserer au bon moment du parsing , split selon les ' ' s et trier par ordre alphabetique ascii le char ** 
// les trucs entre guillemets ne doivent pas etre wildcarder !!
void	do_wildcards(char **s)
{
	int	start;
	int	end;
	char	*ss;

	if (!is_in_str(*s, '*'))
		return;
	start = ft_strchr(*s, '*') - *s;
	end = ft_strrchr(*s, '*') - *s;
	ss = NULL;
	get_current_dir(*s, &ss, start, end);
	if (ss == NULL)
		return ;
	free(*s);
	*s = ss;
}