/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:43:08 by okraus            #+#    #+#             */
/*   Updated: 2023/12/29 15:52:39 by okraus           ###   ########.fr       */
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
typedef enum e_emap
{
	EMPTINESS = 0x0,
	FLOOR1 = 0x1,
	WALL1 = 0x10,
	PLAYERNORTH = 0x100,
	PLAYEREAST = 0x200,
	PLAYERSOUTH = 0x400,
	PLAYERWEST = 0x800,
	EXIT = 0x1000,
	DOOR1 = 0x10000,
}	t_emap;

//	STRUCTURES

union u_clr
{
	unsigned int	rgba;
	struct
	{
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
		unsigned char	a;
	};
};

typedef struct s_door
{
	int	type;	//different types require different keys
	int	pos;	//position on map
	int status; //256 open, 0 closed
}	t_door;

typedef struct s_player
{
	int	pos;	//position on map & 0xFFFF | 0xFFFF0000 & position in the square
	int orientation; //0 facing north 16384 angles for start 16384 is 0 again
}	t_door;


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
	u_clr			f;			//floor colour
	u_clr			c;			//ceiling colour
	int				w;			//width of map
	int				h;			//height of map
	t_player		p;			//player struct with pos and orientation
	int				e;			//position of exit on map
	t_door			**d;-			//doors for bonus, NULL terminated array
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
int	ft_process_file(t_map *map);

#endif
