#include "cube.h"

enum e_direction {
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
};

enum e_direction	getDirection(t_int_coord *player, t_int_coord *next) {
	if (next->x == player->x - 1 && next->y == player->y - 1)
		return (UP_LEFT);
	else if (next->x == player->x + 1 && next->y == player->y - 1)
		return (UP_RIGHT);
	else if (next->x == player->x - 1 && next->y == player->y + 1)
		return (DOWN_LEFT);
	else if (next->x == player->x + 1 && next->y == player->y + 1)
		return (DOWN_RIGHT);
	return (-1);
}

bool	cornerCollision(t_cub *cub, t_int_coord next) {
	t_int_coord	player;
	enum e_direction	direction;

	player = (t_int_coord){(int)cub->player.x, (int)cub->player.y};
	if (next.x == player.x && next.y == player.y)
		return (true);
	direction = getDirection(&player, &next);
	if (direction == UP_LEFT && cub->map->map[player.y][player.x - 1] == '0'
		&& cub->map->map[player.y - 1][player.x] == '0')
		return (true);
	if (direction == UP_RIGHT && cub->map->map[player.y][player.x + 1] == '0'
		&& cub->map->map[player.y - 1][player.x] == '0')
		return (true);
	if (direction == DOWN_LEFT && cub->map->map[player.y][player.x - 1] == '0'
		&& cub->map->map[player.y + 1][player.x] == '0')
		return (true);
	if (direction == DOWN_RIGHT && cub->map->map[player.y][player.x + 1] == '0'
		&& cub->map->map[player.y + 1][player.x] == '0')
		return (true);
	return (false);
}
