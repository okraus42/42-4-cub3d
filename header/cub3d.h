/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:43:08 by okraus            #+#    #+#             */
/*   Updated: 2023/12/30 13:50:40 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

// INCLUDES

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <sys/wait.h>
# include <time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "../.MLX42/include/MLX42/MLX42.h"
# include "../libft/header/libft.h"

//	DEFINITIONS

//	ENUMS

// map elements, maybe add teleport? keys? sprites? items?
//floor near wall to check for collisions.
typedef enum e_emap
{
	EMPTINESS = 0x0,
	FLOOR1 = 0x1,
	FLOOR = 0xFF,
	FLOORWN = 0x10,
	FLOORWE = 0x20,
	FLOORWS = 0x40,
	FLOORWW = 0x80,
	WALL1 = 0x100,
	WALL = 0xF00,
	FLOOD1 = 0x1000,
	FLOOD2 = 0x2000,
	EXIT = 0x10000,
	DOOR1 = 0x100000,
}	t_emap;

//	STRUCTURES

typedef union u_clr
{
	unsigned int	rgba;
	struct
	{
		unsigned char	a;
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
	};
} t_clr;

typedef struct s_door
{
	int	type;	//different types require different keys
	int	pos;	//position on map
	int status; //256 open, 0 closed
}	t_door;

# define NORTH 0
# define EAST 4096
# define SOUTH 8192
# define WEST 12288

typedef struct s_player
{
	int	pos;	//position on map & 0xFFFF | 0xFFFF0000 & position in the square
	int orientation; //0 facing north 16384 angles for start 16384 is 0 again
}	t_player;


//add door textures and stuff later
typedef struct s_map
{
	unsigned int	m[65536];		//1d array of map representation
	char			*file;			//original mapfile string
	char			*mapstr;		//actual content of the file
	char			*northtexture;	//path to the north texture
	char			*southtexture;
	char			*westtexture;
	char			*easttexture;
	t_clr			f;			//floor colour
	t_clr			c;			//ceiling colour
	int				valid;		//1 if valid map
	int				w;			//width of map
	int				h;			//height of map
	t_player		p;			//player pos and orientation
	unsigned int	e;			//position of exit on map, future stuff
	t_door			**d;		//doors for bonus, NULL terminated array
}	t_map;

typedef struct s_highscore
{
	char	*name;
	char	*coalition;
	int		index;
	int		score;
}	t_hs;

typedef struct s_control
{
	int		w;
	int		s;
	int		a;
	int		d;
	int		space;
	int		ctrl;
	int		time;
	int		t;
}	t_controls;

typedef struct s_math
{
	int		sin[65536];
	int		cos[65536];
	int		sqr[65536];
	int		clr1[65536];
	int		clr2[65536];
}	t_math;

typedef struct s_imgs
{
	mlx_instance_t	*pi;
	mlx_instance_t	*ei;
	mlx_instance_t	*ci;
	mlx_instance_t	*c2i;
	mlx_instance_t	*dci;
	mlx_instance_t	*doi;
}	t_imgs;

typedef struct s_max
{
	mlx_t		*mlx;
	t_map		*map;
	t_controls	*key;
	t_imgs		*img;
	mlx_image_t	*str;
	mlx_image_t	*tmp;
	char		*player_name;
	char		*player_coalition;
	int			death;
	int			lives;
	int			score;
	int			exit;
	int			time;
}	t_max;

// PROTOTYPES

//parser.c
int	ft_process_file(t_max *max);

#endif
