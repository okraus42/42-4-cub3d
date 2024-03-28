/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:43:08 by okraus            #+#    #+#             */
/*   Updated: 2024/03/28 11:03:54 by okraus           ###   ########.fr       */
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
# include "menu.h"

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
#  define DEBUGGING 1
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

# ifndef DEBUGGING
#  define DEBUGGING 0
# endif

# define STRINGS 16
# define MINIWIDTH 256
# define MINIHEIGHT 256
# define SCREENWIDTH WIDTH
# define SCREENHEIGHT HEIGHT //- HUD later
# define TMASK 0xFFFFFFFF //


# define RAYS (SCREENWIDTH) //SCREENWIDTH
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
# define EAST 4096			// == 90
# define SOUTH 8192			// == 180
# define WEST 12288			// == 270
# define MAXDEGREE 16384	// == 360

# define NORTHEAST 1
# define NORTHWEST 2
# define SOUTHWEST 3
# define SOUTHEAST 4

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

# define SQUARESIZE 65536
# define WALLDISTANCE 16384 //it is important it is bigger than actual speed 
//or with low framerate players could go through walls


typedef struct s_line
{
	int				x[3];
	int				y[3];
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
}	t_line;

typedef struct s_oray
{
	int				ra;
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
	long long		length;
	long long		length2;
	long long		ldof;
	long long		vl;
	long long		hl;
	long long		xs; //ray starting position 65536 is 1.000
	long long		ys;
	long long		hx[DOF + 1];
	long long		hy[DOF + 1];
	long long		vx[DOF + 1];
	long long		vy[DOF + 1];
	long long		tx; //test ray x position (for map discovery)
	long long		ty; //test ray y position (for map discovery)
	long long		rx;	//ray final position
	long long		ry;
	long long		hxo;	//x and y offset
	long long		hyo;
	long long		vxo;	//x and y offset
	long long		vyo;
	long long		txo;	//x and y offset
	long long		tyo;
	int				hdof;
	int				vdof;
	int				tdof;
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
	//t_oray			ray[RAYS];
	t_oray			oray[RAYS];
	t_line			miniray[RAYS];
	t_line			mapray[RAYS];
	t_oray			screenray[RAYS];
	int		orientation; //0 facing north 4096*4 angles
}	t_player;

//add door textures and stuff later
typedef struct s_map
{
	unsigned long long	m[65536];		//1d array of map representation
	char				*file;			//original mapfile string
	char				*mapstr;		//actual content of the file
	char				*northtexture;	//path to the north texture
	char				*southtexture;
	char				*westtexture;
	char				*easttexture;
	t_clr				f;				//floor colour
	t_clr				c;				//ceiling colour
	t_clr				b;				//optional brume colour
	int					valid;			//1 if valid map
	int					w;				//256
	int					ww;				//width of actual map
	int					h;				//256
	int					hh;				//height of actual map
	t_player			p;				//player pos and orientation
	unsigned int		e;				//position of exit on map, future stuff
	//t_door			**d;			//doors for bonus, NULL terminated array
}	t_map;

typedef struct s_highscore
{
	char	*name;
	char	*coalition;
	int		index;
	int		score;
}	t_hs;

// typedef enum keys
// {
// 	MLX_KEY_SPACE			= 32,
// 	MLX_KEY_APOSTROPHE		= 39,
// 	MLX_KEY_COMMA			= 44,
// 	MLX_KEY_MINUS			= 45,
// 	MLX_KEY_PERIOD			= 46,
// 	MLX_KEY_SLASH			= 47,
// 	MLX_KEY_0				= 48,
// 	MLX_KEY_1				= 49,
// 	MLX_KEY_2				= 50,
// 	MLX_KEY_3				= 51,
// 	MLX_KEY_4				= 52,
// 	MLX_KEY_5				= 53,
// 	MLX_KEY_6				= 54,
// 	MLX_KEY_7				= 55,
// 	MLX_KEY_8				= 56,
// 	MLX_KEY_9				= 57,
// 	MLX_KEY_SEMICOLON		= 59,
// 	MLX_KEY_EQUAL			= 61,
// 	MLX_KEY_A				= 65,
// 	MLX_KEY_B				= 66,
// 	MLX_KEY_C				= 67,
// 	MLX_KEY_D				= 68,
// 	MLX_KEY_E				= 69,
// 	MLX_KEY_F				= 70,
// 	MLX_KEY_G				= 71,
// 	MLX_KEY_H				= 72,
// 	MLX_KEY_I				= 73,
// 	MLX_KEY_J				= 74,
// 	MLX_KEY_K				= 75,
// 	MLX_KEY_L				= 76,
// 	MLX_KEY_M				= 77,
// 	MLX_KEY_N				= 78,
// 	MLX_KEY_O				= 79,
// 	MLX_KEY_P				= 80,
// 	MLX_KEY_Q				= 81,
// 	MLX_KEY_R				= 82,
// 	MLX_KEY_S				= 83,
// 	MLX_KEY_T				= 84,
// 	MLX_KEY_U				= 85,
// 	MLX_KEY_V				= 86,
// 	MLX_KEY_W				= 87,
// 	MLX_KEY_X				= 88,
// 	MLX_KEY_Y				= 89,
// 	MLX_KEY_Z				= 90,
// 	MLX_KEY_LEFT_BRACKET	= 91,
// 	MLX_KEY_BACKSLASH		= 92,
// 	MLX_KEY_RIGHT_BRACKET	= 93,
// 	MLX_KEY_GRAVE_ACCENT	= 96,
// 	MLX_KEY_ESCAPE			= 256,
// 	MLX_KEY_ENTER			= 257,
// 	MLX_KEY_TAB				= 258,
// 	MLX_KEY_BACKSPACE		= 259,
// 	MLX_KEY_INSERT			= 260,
// 	MLX_KEY_DELETE			= 261,
// 	MLX_KEY_RIGHT			= 262,
// 	MLX_KEY_LEFT			= 263,
// 	MLX_KEY_DOWN			= 264,
// 	MLX_KEY_UP				= 265,
// 	MLX_KEY_PAGE_UP			= 266,
// 	MLX_KEY_PAGE_DOWN		= 267,
// 	MLX_KEY_HOME			= 268,
// 	MLX_KEY_END				= 269,
// 	MLX_KEY_CAPS_LOCK		= 280,
// 	MLX_KEY_SCROLL_LOCK		= 281,
// 	MLX_KEY_NUM_LOCK		= 282,
// 	MLX_KEY_PRINT_SCREEN	= 283,
// 	MLX_KEY_PAUSE			= 284,
// 	MLX_KEY_F1				= 290,
// 	MLX_KEY_F2				= 291,
// 	MLX_KEY_F3				= 292,
// 	MLX_KEY_F4				= 293,
// 	MLX_KEY_F5				= 294,
// 	MLX_KEY_F6				= 295,
// 	MLX_KEY_F7				= 296,
// 	MLX_KEY_F8				= 297,
// 	MLX_KEY_F9				= 298,
// 	MLX_KEY_F10				= 299,
// 	MLX_KEY_F11				= 300,
// 	MLX_KEY_F12				= 301,
// 	MLX_KEY_F13				= 302,
// 	MLX_KEY_F14				= 303,
// 	MLX_KEY_F15				= 304,
// 	MLX_KEY_F16				= 305,
// 	MLX_KEY_F17				= 306,
// 	MLX_KEY_F18				= 307,
// 	MLX_KEY_F19				= 308,
// 	MLX_KEY_F20				= 309,
// 	MLX_KEY_F21				= 310,
// 	MLX_KEY_F22				= 311,
// 	MLX_KEY_F23				= 312,
// 	MLX_KEY_F24				= 313,
// 	MLX_KEY_F25				= 314,
// 	MLX_KEY_KP_0			= 320,
// 	MLX_KEY_KP_1			= 321,
// 	MLX_KEY_KP_2			= 322,
// 	MLX_KEY_KP_3			= 323,
// 	MLX_KEY_KP_4			= 324,
// 	MLX_KEY_KP_5			= 325,
// 	MLX_KEY_KP_6			= 326,
// 	MLX_KEY_KP_7			= 327,
// 	MLX_KEY_KP_8			= 328,
// 	MLX_KEY_KP_9			= 329,
// 	MLX_KEY_KP_DECIMAL		= 330,
// 	MLX_KEY_KP_DIVIDE		= 331,
// 	MLX_KEY_KP_MULTIPLY		= 332,
// 	MLX_KEY_KP_SUBTRACT		= 333,
// 	MLX_KEY_KP_ADD			= 334,
// 	MLX_KEY_KP_ENTER		= 335,
// 	MLX_KEY_KP_EQUAL		= 336,
// 	MLX_KEY_LEFT_SHIFT		= 340,
// 	MLX_KEY_LEFT_CONTROL	= 341,
// 	MLX_KEY_LEFT_ALT		= 342,
// 	MLX_KEY_LEFT_SUPER		= 343,
// 	MLX_KEY_RIGHT_SHIFT		= 344,
// 	MLX_KEY_RIGHT_CONTROL	= 345,
// 	MLX_KEY_RIGHT_ALT		= 346,
// 	MLX_KEY_RIGHT_SUPER		= 347,
// 	MLX_KEY_MENU			= 348,
// }	keys_t;

typedef struct s_control
{
	int		w;
	int		s;
	int		a;
	int		d;
	int		up;
	int		down;
	int		left;
	int		right;
	int		enter;
	int		space;
	int		add;
	int		subtract;
	int		multiply;
	int		divide;
	int		ctrl;
	int		time;
	int		t;
	int		one;
	int		two;
	int		three;
	int		four;
	int		five;
	int		six;
	int		seven;
	int		eight;
	int		nine;
	int		zero;
}	t_controls;

typedef struct s_math
{
	int				sin[MAXDEGREE];	//done multiplied by MAXDEGREE
	int				cos[MAXDEGREE];
	long long		atan[MAXDEGREE];
	long long		natan[MAXDEGREE];
	long long		ntan[MAXDEGREE];
	long long		tan[MAXDEGREE];
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
	t_controls		key;
	mlx_image_t		*background;
	mlx_image_t		*hud;
	mlx_image_t		*menuscreen;
	t_menu			menu;
	t_font			font;
	mlx_image_t		*screen;
	mlx_image_t		*maximap;
	mlx_image_t		*minimap;
	mlx_image_t		*str[STRINGS];
	char			s[STRINGS][256];
	char			name[20];
	char			coalition[20];
	char			campus[20];//make it a list later
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
	int				game_mode;
	int				difficulty;
	int				game_in_progress;
	int				mmode;
	int				ray;
	time_t			oldms;
	time_t			newms;
	unsigned int	framems;
	long			frame;
}	t_max;

// PROTOTYPES


//ft_button.c
void	ft_initbuttons(t_max *max);
void	ft_draw_button(t_button *b, int state);
void	ft_choose_in_button(t_max *max, t_button *button);

//ft_textfield.c
void	ft_inittextfields(t_max *max);
void	ft_draw_textfield(t_textfield *b, int state);
void	ft_write_in_textfield(t_max *max, t_textfield *textfield);

void	ft_initlistfields(t_max *max);
void	ft_draw_listfield(t_listfield *lf, int state);
void	ft_choose_in_listfield(t_max *max, t_listfield *listfield);

//ft_text.c
void	ft_draw_text(t_text *text, int state);

//parser.c
void	ft_init_brume(t_max *max);
void	ft_print_map(t_map *map);
void	ft_fill_colours_to_map(t_map *map);
void	ft_load_texture(char *path, mlx_texture_t **texture);
int		ft_process_file(t_max *max);

//ft_random.map.c
int		ft_process_random(t_max *max);

//ft_game.c
void	ft_amaze_standard(t_max *max);
void	ft_amaze_bonus(t_max *max);

//ft_hook.c
void	ft_hook(void *param);

//ft_map.c
void	ft_draw_map(t_max *max);

//ft_minimap.c
void	ft_draw_minimap(t_max *max);

//ft_rays.c
//void	ft_init_rays(t_max *max);
void	ft_init_orays(t_max *max);

//ft_line.c
void	ft_place_line(mlx_image_t *img, t_line l);

//ft_menu.c
void	ft_initmenu(t_max *max);
void	ft_menu(t_max *max);

//ft_keyhook.c
void	ft_keyhook(mlx_key_data_t keydata, void *param);

#endif
