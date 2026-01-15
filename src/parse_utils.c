#include "../cub3d.h"

static int	get_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	parse_rgb(char *line)
{
	char	**rgb;
	int		c[3];

	rgb = ft_split(line, ',');
	if (!rgb || get_arr_len(rgb) != 3)
	{
		free_arr(rgb);
		exit_error(NULL, "Error\nInvalid color format (Must be R,G,B)");
	}
	if (!is_numeric(rgb[0]) || !is_numeric(rgb[1]) || !is_numeric(rgb[2]))
	{
		free_arr(rgb);
		exit_error(NULL, "Error\nColor values must be numeric");
	}
	c[0] = ft_atoi(rgb[0]);
	c[1] = ft_atoi(rgb[1]);
	c[2] = ft_atoi(rgb[2]);
	free_arr(rgb);
	if (c[0] < 0 || c[0] > 255 || c[1] < 0 || c[1] > 255 || c[2] < 0 || c[2] > 255)
		exit_error(NULL, "Error\nColor values must be between 0 and 255");
	return ((c[0] << 16) | (c[1] << 8) | c[2]);
}
