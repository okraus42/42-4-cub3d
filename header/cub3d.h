/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:43:08 by okraus            #+#    #+#             */
/*   Updated: 2024/01/02 15:14:33 by okraus           ###   ########.fr       */
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

# define WIDTH 1920
# define HEIGHT 1080
# define MAPWIDTH 1024
# define MAPHEIGHT 1024
# define MINIWIDTH 256
# define MINIHEIGHT 256
# define TMASK 0xFFFFFFFF

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
	FLOORWNW = 0x100,
	FLOORWNE = 0x200,
	FLOORWSW = 0x400,
	FLOORWSE = 0x800,
	FLOORW = 0xFF0,
	WALL1 = 0x1000,
	WALL = 0xF000,
	FLOOD1 = 0x10000,
	FLOOD2 = 0x20000,
	EXIT = 0x100000,
	DOOR1 = 0x1000000,
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
	union		//position on map
	{
		unsigned int	pos;
		struct
		{
			unsigned char	mx;		//0x000000FF & pos; map x pos
			unsigned char	my;		//0x0000FF00 & pos; map y pos
			unsigned char	sx;		//0x00FF0000 & pos; square x pos
			unsigned char	sy;		//0xFF000000 & pos; square y pos
		};
		struct
		{
			unsigned short	mpos;		//0x0000FFFF & pos; map pos
			unsigned short	spos;		//0xFFFF0000 & pos; square pos
		};
	};
	int status; //256 open, 0 closed
}	t_door;

# define NORTH 0
# define EAST 16384
# define SOUTH 32768
# define WEST 49152

# define WALLDISTANCE 64 //it is important it is bigger than actual speed 
//or with low framerate players could go through walls

typedef struct s_player
{
	union		//position on map
	{
		unsigned int	pos;
		struct
		{
			unsigned char	mapx;		//0x000000FF & pos; map x pos
			unsigned char	mapy;		//0x0000FF00 & pos; map y pos
			unsigned char	sqrx;		//0x00FF0000 & pos; square x pos
			unsigned char	sqry;		//0xFF000000 & pos; square y pos
		};
		struct
		{
			unsigned short	mpos;		//0x0000FFFF & pos; map pos
			unsigned short	spos;		//0xFFFF0000 & pos; square pos
		};
	};
		union		//position on map
	{
		unsigned int	pos2;
		struct
		{
			unsigned char	sx;		//0x000000FF & pos2; square x pos
			unsigned char	mx;		//0x0000FF00 & pos2; map x pos
			unsigned char	sy;		//0x00FF0000 & pos2; square y pos
			unsigned char	my;		//0xFF000000 & pos2; map y pos
		};
		struct
		{
			unsigned short	x;		//0x0000FFFF & pos2; x pos
			unsigned short	y;		//0xFFFF0000 & pos2; y pos
		};
	};
	int	xx[2];	//x screen position and point ahead
	int	yy[2];	//y screen position and point ahaed
	int fov;
	int	fov2;
	int	xl[2]; //left ray
	int	yl[2];
	int	xr[2]; //right ray
	int	yr[2];
	int	speed;
	int	turnspeed;
	int	xspeed;
	int	yspeed;
	unsigned short orientation; //0 facing north 65536 angles for start 65536 is 0 again
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
	int				w;			//256
	int				ww;			//width of actual map
	int				h;			//256
	int				hh;			//height of actual map
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

typedef struct s_line
{
	int				x[3];
	int				y[3];
	int				dx;
	int				dy;
	union
	{
		int			xi;
		int			yi;
	};
	int				d;
}	t_line;

typedef struct s_math
{
	int		sin[65536];	//done multiplied by 65536
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
	mlx_t			*mlx;
	t_map			*map;
	t_math			*math;
	t_controls		*key;
	mlx_image_t		*screen;
	mlx_image_t		*maximap;
	mlx_image_t		*minimap;
	// t_imgs			*img;
	// mlx_image_t		*str;
	// mlx_image_t		*tmp;
	// char			*player_name;
	// char			*player_coalition;
	// int				death;
	// int				lives;
	// int				score;
	// int				exit;
	// int				time;
	unsigned char	mode;
	time_t			oldms;
	time_t			newms;
	unsigned int	framems;
	long			frame;
}	t_max;

// PROTOTYPES

//parser.c
int	ft_process_file(t_max *max);

//ft_game.c
void	ft_amaze_standard(t_max *max);

//ft_hook.c
void	ft_hook(void *param);

#endif
