/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_log_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:53:55 by rgiraud           #+#    #+#             */
/*   Updated: 2024/05/02 00:13:02 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

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
	tmp = result;
	result = ft_strjoin(result, ft_itoa(fraction));
	free(tmp);
	return (result);
}

double	calculate_fov(double planeX, double planeY)
{
	double	norm;
	double	fov_radians;
	double	fov_degrees;

	norm = sqrt(planeX * planeX + planeY * planeY);
	fov_radians = 2 * atan(norm);
	fov_degrees = fov_radians * (180.0 / M_PI);
	return (fov_degrees);
}

void	draw_fov(t_cub *cub)
{
	char	result[100];
	char	*tmp;
	double	fov;

	fov = calculate_fov(cub->plane.x, cub->plane.y);
	ft_memcpy(result, "fov: ", 6);
	tmp = get_value_float(fov);
	if (!tmp)
		return (free_cub(cub), quit_cub(MALLOC_ERROR));
	ft_strlcat(result, tmp, sizeof(result));
	free(tmp);
	mlx_string_put(cub->mlx, cub->win, WWIN - WMAP - 12, 110, CBLACK, result);
}