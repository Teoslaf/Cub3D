/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:17:28 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/19 17:01:08 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "textures/lmao.xpm"

void	init_window(t_map *map)
{
	map->vars.mlx = mlx_init();
	map->vars.win = mlx_new_window(map->vars.mlx, WIDTH, HEIGHT, "Cube3D");
	map->image.img = mlx_new_image(map->vars.mlx, WIDTH, HEIGHT);
	map->image.address = mlx_get_data_addr(map->image.img,
			&map->image.bitxpixel, &map->image.line_len, &map->image.endian);
}

void	init_map(t_map *map)
{
	map->height = 0;
	map->north_set = 0;
	map->south_set = 0;
	map->west_set = 0;
	map->east_set = 0;
	map->floor_set = 0;
	map->ceiling_set = 0;
	map->map_set = 0;
	map->map_start = 0;
	map->rows_set = 0;
	map->ceiling = NULL;
	map->floor = NULL;
	map->north = NULL;
	map->south = NULL;
	map->west = NULL;
	map->east = NULL;
	map->map = NULL;
	map->player.side = 0;
	map->player.dir_x = -1;
	map->player.dir_y = 0;
	map->player.plane_x = 0;
	map->player.plane_y = 0.66;
	map->player.step_x = 0;
	map->player.step_y = 0;
	map->player.delta_dist_x = 0;
	map->player.delta_dist_y = 0;
	map->player.side_dist_x = 0;
	map->player.side_dist_y = 0;
	map->player.perp_wall_dist = 0;
	map->player.ray_dir_x = 0;
	map->player.ray_dir_y = 0;
	map->minimap = 0;
	map->textures = malloc(sizeof(t_image) * 4);
	if (!map->textures && printf("Error allocating textures\n"))
		return;
	for (int i=0; i< 4; i++) {
		map->textures[i] = malloc(sizeof(t_image));
	}
	// map->ray = malloc(sizeof(t_ray));
	map->time = 0;
	map->old_time = 0;
}
int	close_window(t_map *map)
{
	(void)map;
	printf("CLOSING APP\n");
	exit(0);
}

void	init_hooks(t_map *map)
{
	mlx_hook(map->vars.win, 2, 1L << 0, handle_key_down, map);
	mlx_hook(map->vars.win, 4, 1L << 2, mouse_press, map);
	mlx_hook(map->vars.win, 5, 1L << 3, mouse_release, map);
	mlx_hook(map->vars.win, 6, 1L << 8, mouse_move, map);
	mlx_hook(map->vars.win, 17, 0, close_window, map);
}

void	my_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;
	dst = image->address + (y * image->line_len + x * (image->bitxpixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_map *map, int xpos, int ypos)
{
	int i, j;
	for (i = 0; i < SQUARE - 2; i++)
	{
		for (j = 0; j < SQUARE - 2; j++)
		{
			if (map->map[ypos / SQUARE][xpos / SQUARE] == '1')
				my_pixel_put(&map->image, xpos + j, ypos + i, 0xf3f3f3);
			else if (map->map[ypos / SQUARE][xpos / SQUARE] == '0'
				|| map->map[ypos / SQUARE][xpos
				/ SQUARE] == map->player.direction)
				my_pixel_put(&map->image, xpos + j, ypos + i, 0x5b5b5b);
		}
	}
	for (i = 0; i < PLAYER; i++)
	{
		for (j = 0; j < PLAYER; j++)
		{
			my_pixel_put(&map->image, map->player.pos_x * SQUARE + j + 10 - 12.5,
				map->player.pos_y * SQUARE + i + 10 - 12.5, 0xc90076);
		}
	}
}

int	create_rgb(char **color)
{
	int	red;
	int	green;
	int	blue;

	red = ft_atoi(color[1]);
	green = ft_atoi(color[3]);
	blue = ft_atoi(color[5]);
	return ((red << 16) + (green << 8) + blue);
}

void	draw_background(t_map *map)
{
	int	x;
	int	y;
	int ceiling_color;
	int floor_color;


	ceiling_color = create_rgb(map->ceiling);
	floor_color = create_rgb(map->floor);
	// printf("ceiling color: %d | floor color: %d\n", ceiling_color, floor_color);
	y = 0;
	while (y < HEIGHT /2)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_pixel_put(&map->image, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_pixel_put(&map->image, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void draw_pink_screen(t_map *map)
{
    int x, y;
    for (y = 0; y < map->height * SQUARE; y++)
    {
        for (x = 0; x < (map->width - 2) * SQUARE; x++)
        {
            my_pixel_put(&map->image, x, y, 0xD3D3D3);
        }
    }
}

void	minimap(t_map *map)
{
	int	xpos;
	int	ypos;

	draw_pink_screen(map);
	int x, y;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < (int)ft_strlen(map->map[y]) - 1)
		{
			xpos = x * SQUARE;
			ypos = y * SQUARE;
			draw_square(map, xpos, ypos);
			x++;
		}
		y++;
	}
}

void	show_map(t_map *map)
{
	t_image img;

	img.img = mlx_xpm_file_to_image(map->vars.mlx, "./textures/lmao.xpm", &img.width, &img.height);
	img.address = mlx_get_data_addr(img.img, &img.bitxpixel, &img.line_len, &img.endian);
	draw_background(map);
    for(int x = 0; x < WIDTH; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / (double)WIDTH - 1;

      map->player.ray_dir_x = map->player.dir_x + map->player.plane_x * cameraX;
      map->player.ray_dir_y = map->player.dir_y + map->player.plane_y * cameraX;
      //which box of the map we're in
      int mapX = (int)(map->player.pos_x);
      int mapY = (int)(map->player.pos_y);

      map->player.delta_dist_x = (map->player.ray_dir_x == 0) ? 1e30 : fabs(1 / map->player.ray_dir_x);
      map->player.delta_dist_y = (map->player.ray_dir_y == 0) ? 1e30 : fabs(1 / map->player.ray_dir_y);


      int hit = 0; //was there a wall hit?
      //calculate step and initial sideDist
      if(map->player.ray_dir_x < 0)
      {
        map->player.step_x = -1;
        map->player.side_dist_x = (map->player.pos_x - mapX) * map->player.delta_dist_x;
      }
      else
      {
        map->player.step_x = 1;
        map->player.side_dist_x = (mapX + 1.0 - map->player.pos_x) * map->player.delta_dist_x;
      }
      if(map->player.ray_dir_y < 0)
      {
        map->player.step_y = -1;
        map->player.side_dist_y = (map->player.pos_y - mapY) * map->player.delta_dist_y;
      }
      else
      {
        map->player.step_y = 1;
        map->player.side_dist_y = (mapY + 1.0 - map->player.pos_y) * map->player.delta_dist_y;
      }
      //perform DDA
      while(hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(map->player.side_dist_x < map->player.side_dist_y)
        {
          map->player.side_dist_x += map->player.delta_dist_x;
          mapX += map->player.step_x;
          map->player.side = 0;
        }
        else
        {
          map->player.side_dist_y += map->player.delta_dist_y;
          mapY += map->player.step_y;
          map->player.side = 1;
        }
        //Check if ray has hit a wall
        if(map->map[mapY][mapX] == '1') hit = 1;
      }
      if(map->player.side == 0)
	  	map->player.perp_wall_dist = (map->player.side_dist_x - map->player.delta_dist_x);
      else
	  	map->player.perp_wall_dist = (map->player.side_dist_y - map->player.delta_dist_y);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(HEIGHT / map->player.perp_wall_dist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + HEIGHT / 2;
    //   if(drawStart < 0)
	//   	drawStart = 0;
      int drawEnd = lineHeight / 2 + HEIGHT / 2;
    //   if(drawEnd >= HEIGHT)
	//   	drawEnd = HEIGHT - 1;

		int color;
		
		int	texX;
		double wallX;
		//give x and y sides different brightness
		if(map->player.side == 0) {
			wallX = map->player.pos_y + map->player.perp_wall_dist * map->player.ray_dir_y;
		}
		else
			wallX = map->player.pos_x + map->player.perp_wall_dist * map->player.ray_dir_x;
		

		wallX -= floor(wallX);

		texX = (int)(wallX * (double)map->textures[NORTH]->width);
		if(map->player.side == 0 && map->player.ray_dir_x > 0) 
			texX = map->textures[NORTH]->width - texX - 1;
		if (map->player.side == 1 && map->player.ray_dir_y < 0)
			texX = map->textures[NORTH]->width - texX - 1;

		double step = 1.0 * map->textures[NORTH]->height / lineHeight;

		double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
			
		int y;
		for (y = drawStart; y < drawEnd; y++) {
			// int texY = (int)texPos & (map->textures[NORTH]->height - 1);
			// texPos += step;
			// color = map->textures[NORTH]->address[map->textures[NORTH]->height * texY + texX];
			// if (map->player.side == 1)
			// 	color = (color >> 1) & 8355711;
			// my_pixel_put(&map->image, x, y, color);
		
		
			int	texY = (int)(((y - drawStart) / (double)(drawEnd - drawStart)) * map->textures[NORTH]->height);
			// color = map->textures[NORTH]->address[map->textures[NORTH]->width * texY + texX];

			double x1 = texX * map->textures[NORTH]->xoff;
			double y1 = texY * map->textures[NORTH]->yoff;

			x1 = fmod(x1, map->textures[NORTH]->width);
			y1 = fmod(y1, map->textures[NORTH]->height);

			if (x1 < 0)
				x1 += map->textures[NORTH]->width;
			if (y1 < 0)
				y1 += map->textures[NORTH]->height;
			int index = ((int)y1) * map->textures[NORTH]->line_len + x1 * (map->textures[NORTH]->bitxpixel >> 3);

			char *tbuf = &(map->textures[NORTH]->address[index]);
			// printf("tbuf val: %d\n", (*(int *)tbuf));
			if (y >= 0 && y <= HEIGHT)
				my_pixel_put(&map->image, x, y, (*(int *)tbuf));
		}
		// }
    }
	if (map->minimap == 1)
		minimap(map);

	mlx_put_image_to_window(map->vars.mlx, map->vars.win, map->image.img, 0, 0);
	// mlx_put_image_to_window(map->vars.mlx, map->vars.win, map->textures[NORTH]->img, 0, 0);

	// printf("width: %d | height: %d\n", width, height);
}



int main(int argc, char **argv)
{
	t_map *map;
	map = malloc(sizeof(t_map));
	if (!map)
		return (1);
  	init_window(map);
	init_map(map);
		if (argc < 2)
		printf("No map given!\n");
	if (argc > 2)
		printf("Too many arguments\n");
	if (read_map(argv[1], map))
		printf("Error opening the map\n");
	else{
		printf("Valid Map\n");

		init_hooks(map);
		printf("map direction: %c\n", map->player.direction);
		if (map->player.direction == 'N')
		{
			map->player.dir_x = 0;
			map->player.dir_y = -1;
		}
		else if (map->player.direction == 'S')
		{
			map->player.dir_x = 0;
			map->player.dir_y = 1;
		}
		else if (map->player.direction == 'W')
		{
			map->player.dir_x = -1;
			map->player.dir_y = 0;
		}
		else if (map->player.direction == 'E')
		{
			map->player.dir_x = 1;
			map->player.dir_y = 0;
		}
		map->player.plane_x = -map->player.dir_y;
		map->player.plane_y = map->player.dir_x;
		map->mouse.curr_x = map->player.dir_x;
		map->mouse.curr_y = map->player.dir_y;
		map->player.fov = 60;
		show_map(map);

		mlx_loop(map->vars.mlx);
	}
	return (0);
}
