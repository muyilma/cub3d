/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:38:38 by omgorege          #+#    #+#             */
/*   Updated: 2026/01/21 12:54:26 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	check_extension(char *file, char *str)
{
	char	*re;
	int		flen;

	flen = ft_strlen(file);
	re = ft_strrchr(file, '.');
	if (!re || flen <= 4 || ft_strncmp(re, str, 5) != 0)
		return (0);
	if (file[flen - 5] == '/')
		return (0);
	return (1);
}

void	check_args(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		exit_error(NULL, ERR_USAGE);
	if (!check_extension(argv[1], ".cub"))
		exit_error(NULL, ERR_EXT);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error not open file\n", 2);
		exit(1);
	}
	close(fd);
}

int	get_digit_len(char *str)
{
	int	len;

	len = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	while (ft_isdigit(*str))
	{
		len++;
		str++;
	}
	return (len);
}
