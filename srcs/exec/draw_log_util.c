/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_log_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:53:55 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/14 14:03:52 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

char	*get_decimal(char *result, int fraction)
{
	char	*tmp;
	char	*tmp2;

	tmp = result;
	tmp2 = ft_itoa(fraction);
	if (!tmp2)
		return (NULL);
	result = ft_strjoin(result, tmp2);
	free(tmp);
	free(tmp2);
	return (result);
}

char	*get_value_float(double value)
{
	char	*result;
	int		entier;
	int		fraction;
	char	*tmp;

	value = round(value * 100);
	entier = (int)(value / 100);
	fraction = (int)(value) % 100;
	if (fraction < 0)
		result = ft_strdup("-0");
	else
		result = ft_itoa(entier);
	fraction = abs(fraction);
	if (!result)
		return (NULL);
	tmp = result;
	result = ft_strjoin(result, ".");
	free(tmp);
	if (!result)
		return (NULL);
	result = get_decimal(result, fraction);
	return (result);
}

double	calculate_fov(t_coord plane, t_coord dir)
{
	double	len_plane;
	double	fov_radians;
	double	fov_degrees;
	double	len_dir;
	
	len_dir = sqrt(dir.x * dir.x + dir.y * dir.y);
	len_plane = sqrt(plane.x * plane.x + plane.y * plane.y);
	fov_radians = 2 * atan(len_plane / len_dir);
	fov_degrees = fov_radians * (180.0 / M_PI);
	return (fov_degrees);
}

void	draw_fov(t_cub *cub)
{
	char	result[100];
	char	*tmp;
	double	fov;

	fov = calculate_fov(cub->plane, cub->dir);
	ft_memcpy(result, "fov: ", 6);
	tmp = get_value_float(fov);
	if (!tmp)
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	ft_strlcat(result, tmp, sizeof(result));
	free(tmp);
	mlx_string_put(cub->mlx, cub->win, WWIN - WMAP - 12, 110, CBLACK, result);
}
