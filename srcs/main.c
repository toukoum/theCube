/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:21:25 by rgiraud           #+#    #+#             */
/*   Updated: 2024/04/23 00:14:16 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>


void minimap(t_cub *cub)
{
	size_t width = cub->arg->width;
	size_t height = cub->arg->height;
	char **map = cub->arg->map;
	
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, width * TSIZE, height * TSIZE, "minimap test");
	// Dessiner la carte
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            int color = (map[y][x] == '1') ? 0x000000 : 0xFFFFFF; // Noir pour les murs, blanc pour le sol
            if (map[y][x] == cub->arg->start_angle) color = 0xFF0000; // Rouge pour le joueur

            // Dessiner un carré pour la case
            for (int dy = 0; dy < TSIZE; dy++) {
                for (int dx = 0; dx < TSIZE; dx++) {
                    mlx_pixel_put(cub->mlx, cub->win, x * TSIZE + dx, y * TSIZE + dy, color);
                }
            }
        }
    }
    mlx_loop(cub->mlx); // Commencer la boucle d'événements
}
int	main(int argc, char **argv)
{
	t_args	args;
	t_cub	cub;

	if (argc != 2)
		quit(NUMBERS_ARGC);
	parse(&args, argv[1]);
	cub.arg = &args;
	minimap(&cub);
	//free_all_map(&cub, ALL_GOOD);
	return (0);
}
