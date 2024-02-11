/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:43:08 by okraus            #+#    #+#             */
/*   Updated: 2024/02/11 10:54:56 by okraus           ###   ########.fr       */
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

# ifndef TESTMODE
#  define TESTMODE 4
# endif

# if TESTMODE == 1
#  define WIDTH 1920
#  define HEIGHT 1080
#  define MAPWIDTH 1024
#  define MAPHEIGHT 1024
#  define NOFISHEYE 1
#  define FULLSCREEN 1
#  define FOV 90
#  define DOF 16
#  define TICK 8
# elif TESTMODE == 2
#  define WIDTH 1920
#  define HEIGHT 1080
#  define MAPWIDTH 1024
#  define MAPHEIGHT 1024
#  define NOFISHEYE 0
#  define FULLSCREEN 0
#  define FOV 360
#  define DOF 8
#  define TICK 8
# elif TESTMODE == 3
#  define WIDTH 960
#  define HEIGHT 540
#  define MAPWIDTH 512
#  define MAPHEIGHT 512
#  define NOFISHEYE 1
#  define FULLSCREEN 0
#  define FOV 80
#  define DOF 8
#  define TICK 8
# elif TESTMODE == 4
#  define WIDTH 1920
#  define HEIGHT 1080
#  define MAPWIDTH 1024
#  define MAPHEIGHT 1024
#  define NOFISHEYE 1
#  define FULLSCREEN 0
#  define FOV 80
#  define DOF 16
#  define TICK 8
# else
#  define WIDTH 2560
#  define HEIGHT 1600
#  define MAPWIDTH 1024
#  define MAPHEIGHT 1024
#  define NOFISHEYE 1
#  define FULLSCREEN 1
#  define FOV 90
#  define DOF 8
#  define TICK 8
# endif


# define MINIWIDTH 256
# define MINIHEIGHT 256
# define SCREENWIDTH WIDTH
# define SCREENHEIGHT HEIGHT //- HUD later
# define TMASK 0xFFFFFFFF //


# define RAYS (SCREENWIDTH / 4) //SCREENWIDTH
# define MAXDIST (65536 * (DOF)) //play with this formula a bit later

# define UNDISCOVERDWALL 0x808080FF
# define UNDISCOVERDFLOOR 0x808080FF
//	ENUMS

// map elements, maybe add teleport? keys? sprites? items?
//floor near wall to check for collisions.

//	00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
//	RED      GREEN    BLUE      VISITED  DOOR     WALLS    CEILING  FLOOR
//  FLOOD???

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
	VISIT = 0x100000000,
	VISITED = 0xFF00000000
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

// typedef struct s_door
// {
// 	int	type;	//different types require different keys
// 	union		//position on map
// 	{
// 		unsigned int	pos;
// 		struct
// 		{
// 			unsigned char	mx;		//0x000000FF & pos; map x pos
// 			unsigned char	my;		//0x0000FF00 & pos; map y pos
// 			unsigned char	sx;		//0x00FF0000 & pos; square x pos
// 			unsigned char	sy;		//0xFF000000 & pos; square y pos
// 		};
// 		struct
// 		{
// 			unsigned short	mpos;		//0x0000FFFF & pos; map pos
// 			unsigned short	spos;		//0xFFFF0000 & pos; square pos
// 		};
// 	};
// 	int status; //256 open, 0 closed
// }	t_door;

# define NORTH 0
# define EAST 16384
# define SOUTH 32768
# define WEST 49152

# define NWALL 1
# define EWALL 2
# define SWALL 4
# define WWALL 8
# define EWWALL 10
# define NSWALL 5
# define NOWALL 0
# define NWALLCOLOUR 0x998800FF
# define EWALLCOLOUR 0xAA9900FF
# define SWALLCOLOUR 0x887700FF
# define WWALLCOLOUR 0x776600FF
# define NOWALLCOLOUR 0xFFFF00FF

# define WALLDISTANCE 64 //it is important it is bigger than actual speed 
//or with low framerate players could go through walls

typedef struct s_ray
{
	int				x[3];
	int				y[3];
	unsigned short	ra;
	union
	{
		unsigned int	c[2];
		struct
		{
			unsigned char c0a;
			unsigned char c0b;
			unsigned char c0g;
			unsigned char c0r;
			unsigned char c1a;
			unsigned char c1b;
			unsigned char c1g;
			unsigned char c1r;
		};
	};
	int				maxwidth;
	int				maxheight;
	int				dx;
	int				dy;
	union
	{
		int			xi;
		int			yi;
	};
	int				d;
	long long		length;
	long long		vl;
	long long		hl;
	long long		xs; //ray starting position 65536 is 1.000
	long long		ys;
	long long		hx;
	long long		hy;
	long long		vx;
	long long		vy;
	long long		rx;	//ray final position
	long long		ry;
	long long		hxo;	//x and y offset
	long long		hyo;
	long long		vxo;	//x and y offset
	long long		vyo;
	int				hdof;
	int				vdof;
	int				dof;
	int				hv;		//which ray is shorter (for backtracking)
	int				wall; //which wall was found (south north east west)
	unsigned long long	vm;
	unsigned long long	hm;
	unsigned long long	m;
}	t_ray;

typedef struct s_oray
{
	int				x[3];
	int				y[3];
	unsigned short	ra;
	union
	{
		unsigned int	c[2];
		struct
		{
			unsigned char c0a;
			unsigned char c0b;
			unsigned char c0g;
			unsigned char c0r;
			unsigned char c1a;
			unsigned char c1b;
			unsigned char c1g;
			unsigned char c1r;
		};
	};
	int				maxwidth;
	int				maxheight;
	int				dx;
	int				dy;
	union
	{
		int			xi;
		int			yi;
	};
	int				d;
	long long		length;
	long long		length2;
	long long		ldof;
	long long		vl;
	long long		hl;
	long long		xs; //ray starting position 65536 is 1.000
	long long		ys;
	long long		hx;
	long long		hy;
	long long		vx;
	long long		vy;
	long long		rx;	//ray final position
	long long		ry;
	long long		hxo;	//x and y offset
	long long		hyo;
	long long		vxo;	//x and y offset
	long long		vyo;
	int				hdof;
	int				vdof;
	int				dof;
	int				hv;		//which ray is shorter (for backtracking)
	int				wall; //which wall was found (south north east west)
	unsigned long long	vm;
	unsigned long long	hm;
	unsigned long long	m;
}	t_oray;

typedef struct s_player
{
	union
	{
		unsigned int	x;
		struct
		{
			unsigned short	sx;
			unsigned char	mx;
			unsigned char	unused_x;
		};
	};
	union
	{
		unsigned int	y;
		struct
		{
			unsigned short	sy;
			unsigned char	my;
			unsigned char	unused_y;
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
	int	dx;	//direction vector x
	int	dy;
	int	xd[2];
	int	yd[2];
	int	cx;	//camera vector
	int	cy;
	int	xc[2];
	int	yc[2];
	int	xn[2];
	int	yn[2];
	t_ray			ray[RAYS];
	t_oray			oray[RAYS];
	t_ray			miniray[RAYS];
	t_ray			mapray[RAYS];
	t_ray			screenray[RAYS];
	unsigned short	orientation; //0 facing north 65536 angles for start 65536 is 0 again
}	t_player;


//add door textures and stuff later
typedef struct s_map
{
	unsigned long long	m[65536];		//1d array of map representation
	char			*file;			//original mapfile string
	char			*mapstr;		//actual content of the file
	char			*northtexture;	//path to the north texture
	char			*southtexture;
	char			*westtexture;
	char			*easttexture;
	t_clr			f;			//floor colour
	t_clr			c;			//ceiling colour
	t_clr			b;			//optional brume colour
	int				valid;		//1 if valid map
	int				w;			//256
	int				ww;			//width of actual map
	int				h;			//256
	int				hh;			//height of actual map
	t_player		p;			//player pos and orientation
	unsigned int	e;			//position of exit on map, future stuff
	//t_door			**d;		//doors for bonus, NULL terminated array
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
	int				sin[65536];	//done multiplied by 65536
	int				cos[65536];
	long long		atan[65536];
	long long		natan[65536];
	long long		ntan[65536];
	long long		tan[65536];
	unsigned char	brumered[256][256];
	unsigned char	brumegreen[256][256];
	unsigned char	brumeblue[256][256];
	// int		sqr[65536];
	unsigned char	clog[65536];
	unsigned char	clin[65536];
}	t_math;

typedef struct s_textures
{
	mlx_texture_t	*nwall;
	mlx_texture_t	*ewall;
	mlx_texture_t	*swall;
	mlx_texture_t	*wwall;
	mlx_texture_t	*ceiling;
	mlx_texture_t	*floor;
}	t_textures;



typedef struct s_max
{
	mlx_t			*mlx;
	t_map			*map;
	t_math			*math;
	t_controls		*key;
	mlx_image_t		*background;
	mlx_image_t		*hud;
	mlx_image_t		*screen;
	mlx_image_t		*maximap;
	mlx_image_t		*minimap;
	mlx_image_t		*str;
	char			s[256];
	t_textures		*t;
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
	int				mmode;
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
void	ft_place_line(mlx_image_t *img, t_ray l);
void	ft_hook(void *param);

//ft_map.c
void	ft_draw_map(t_max *max);

//ft_rays.c
void	ft_init_rays(t_max *max);
void	ft_init_orays(t_max *max);

#endif
