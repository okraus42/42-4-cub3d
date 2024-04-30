/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:43:08 by okraus            #+#    #+#             */
/*   Updated: 2024/04/30 16:10:25 by okraus           ###   ########.fr       */
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
#  define FULLSCREEN 1

#  define MAXDOF 16
# elif TESTMODE == 2
#  define WIDTH 1920
#  define HEIGHT 1080
#  define MAPWIDTH 1024
#  define MAPHEIGHT 1024
#  define FULLSCREEN 0
0
#  define MAXDOF 8
# elif TESTMODE == 3
#  define WIDTH 960
#  define HEIGHT 540
#  define MAPWIDTH 512
#  define MAPHEIGHT 512
#  define FULLSCREEN 0

#  define MAXDOF 8
# elif TESTMODE == 4
#  define WIDTH 1920
#  define HEIGHT 1080
#  define MAPWIDTH 1024
#  define MAPHEIGHT 1024
#  define FULLSCREEN 0

#  define MAXDOF 32
# else
#  define WIDTH 2560
#  define HEIGHT 1600
#  define MAPWIDTH 1024
#  define MAPHEIGHT 1024
#  define FULLSCREEN 1

#  define MAXDOF 8
# endif

# ifndef DEBUGGING
#  define DEBUGGING 0
# endif

# define STRINGS 16
# define MINIWIDTH 256
# define MINIHEIGHT 256
# define SUPERMAPWIDTH 960
# define SUPERMAPHEIGHT 540
# define SUPERMAPBORDER 128

# define SCREENWIDTH (960)
# define SCREENHEIGHT (540) //- HUD later
# define TMASK 0xFFFFFFFF //


# define RAYS (SCREENWIDTH) //SCREENWIDTH
// # define max->settings.maxdist (65536 * (DOF)) //play with this formula a bit later

# define UNDISCOVERDWALL 0x808080FF
# define UNDISCOVERDFLOOR 0x808080FF
//	ENUMS

// map elements, maybe add teleport? keys? sprites? items?
//floor near wall to check for collisions.

//	00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
//	RED      GREEN    BLUE      VISITED  DOOR     WALLS    CEILING  FLOOR
//  FLOOD???

// 00000000 00000000 00000000 00000000
//  DOOR WALLS CEILING  FLOOR
//  FLOOD???

//	00000000 00000000 00000000 00000000
//	RED      GREEN    BLUE      VISITED
//

//	00000000 00000000 00000000 00000000
//	 NORTH    SOUTH     EAST     WEST   WALL
//

//	00000000 00000000 00000000 00000000
//	 KEY     TEXTURE    ????   open/close  DOOR
//	locked					   10010101 - closing
//							   00111011 - opening
//							   11111111 - closed
//							   00000000 - opened

// WALL 0	//perimeter wall separating outside and inside
// WALL 1	// precalculated columns
// other types of wall

# define EMPTINESS 0x0			//outside of the playable map
# define FLOOR1 0x1
# define FLOORFLAMINGO 0x4
# define FLOOR 0xFF
# define FLOORWN 0x10
# define FLOORWE 0x20
# define FLOORWS 0x40
# define FLOORWW 0x80
# define FLOORWNW 0x100
# define FLOORWNE 0x200
# define FLOORWSW 0x400
# define FLOORWSE 0x800
# define FLOORW 0xFF0
# define WALL1 0x1000
# define WALL 0xF000
# define FLOOD1 0x10000
# define FLOOD2 0x20000
# define EXIT 0x2			//exit behaves like floor
# define DOOREAST 0x1000000
# define DOORWEST 0x2000000
# define DOORSOUTH 0x4000000
# define DOORNORTH 0x8000000
# define DOOR 0xF000000
# define DOORNS 0xC000000
# define DOOREW 0x3000000
# define VISIT 0x100000000
# define VISITED 0xFF00000000

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

# if DEBUGGING
#  define NWALLCOLOUR 0xFFFFFFFF
#  define EWALLCOLOUR 0xAA0000FF
#  define SWALLCOLOUR 0x887700FF
#  define WWALLCOLOUR 0x0000AAFF
#  define NOWALLCOLOUR 0xFFFF00FF
# else
#  define DOORCOLOUR 0x53565AFFU
#  define NWALLCOLOUR 0x998800FFU
#  define EWALLCOLOUR 0xAA9900FFU
#  define SWALLCOLOUR 0x887700FFU
#  define WWALLCOLOUR 0x776600FFU
#  define NOWALLCOLOUR 0xFFFF00FFU
# endif


# define SQUARESIZE 65536
# define SQUAREHALF 32768
# define WALLDISTANCE 16384 //it is important it is bigger than actual speed 
//or with low framerate players could go through walls

typedef struct s_wallcheck
{
	int	x;
	int	y;
	int	ny;
	int	sy;
	int	ex;
	int	wx;
}	t_wallcheck;

typedef struct s_walltexture
{
	int				y;
	int				x;
	int				u;
	int				v;
	int				r;
	int				wall_height;
	int				offset;
	int				fake_wall_height;
	int				fake_offset;
	long long		length;
	long long		fake_length;
	unsigned int	wallfog;
	unsigned int	wallfogalpha;
}	t_walltexture;

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
	unsigned long long		vl;
	unsigned long long		hl;
	long long		xs; //ray starting position 65536 is 1.000
	long long		ys;
	long long		hx[MAXDOF + 1];
	long long		hy[MAXDOF + 1];
	long long		vx[MAXDOF + 1];
	long long		vy[MAXDOF + 1];
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
	unsigned int		mpos;	//position of ray in the map
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
	int	smx;	//x position on supermap
	int	smy;	//y position on supermap
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
	int	cx;	//camera plane vector
	int	cy;
	int	xc[2];
	int	yc[2];
	int	xn[2];
	int	yn[2];
	
	int	reveal;			//radius of revealed map
	//t_oray			ray[RAYS];
	t_oray			oray[RAYS];
	t_line			miniray[RAYS];
	t_line			mapray[RAYS];
	//t_oray			screenray[RAYS];
	int		orientation; //0 facing north 4096*4 angles
}	t_player;

# define SPRITE_EXIT 0
# define SPRITE_FLAMINGO 1
# define SPRITETYPES 2

# define EXIT_TEXTURE 0
# define EXIT_GLOW 1
# define FLAMINGO_TEXTURE 2
# define FLAMINGO_GLOW 3
# define SPRITETEXTURES 4

typedef struct s_sprite
{
	int	type;
	int	visible;
	int	state;
	char	text[16];  //text on sprite e.g. "Libft"
	int	frame;
	int	maxframe;
	int	texture; //map
	int	glowtexture;
	int	x;
	int	y;
	// int	x_left;
	// int	y_left;
	// int	x_right;
	// int	y_right;
	int	z;
	int	spx; //sprite relative position
	int	spy;
	// int	spx_left; //sprite relative position
	// int	spy_left;
	// int	spx_right; //sprite relative position
	// int	spy_right;
	int	spz;
	int			direction;
	// int			direction_left;
	// int			direction_right;
	double		distance;
	// double		distance_left;
	// double		distance_right;
	int			radius; //angle
	long long	length;
	int			sprite_height;
	int	xpa;
	int	relativedirection;
	// int	relativedirection_left;
	// int	relativedirection_right;
	int sda;
	int	xstart;
	// int	xmiddle;
	int	xend;
}	t_sprite;

//add door textures and stuff later
typedef struct s_map
{
	unsigned long long	m[65536];		//1d array of map representation
	unsigned int		doors[65536];	//info about doors
	char				file[4096];		//original mapfile string
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
	//unsigned int		e;				//position of exit on map, future stuff
	t_sprite			sprites[256];
	int					exitcount;
	// int					firstflamingo;
	// int					lastflamingo;
	int					current_sprite[SPRITETYPES];
	int					total_sprite[SPRITETYPES];
	int					spritecount;
	//t_door			**d;			//doors for bonus, NULL terminated array
}	t_map;


// remove or simplify
typedef struct s_control
{
	// int		left_shift;
	// int		right_shift;
	int		caps_lock;
}	t_controls;

typedef struct s_keyboard
{
	int		shift;
	int		ctrl;
	int		alt;
	int		caps_lock;
	int		num_lock;
	int		scroll_lock;
	int		character;
}	t_kb;

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
	mlx_texture_t	*door;
	mlx_texture_t	*ceiling;
	mlx_texture_t	*floor;
	mlx_texture_t	*textbg;
	mlx_texture_t	*font;
	mlx_texture_t	*menubg;
	mlx_texture_t	*button;
	mlx_texture_t	*buttonplus;
	mlx_texture_t	*textfield;
	mlx_texture_t	*listfield;
	mlx_texture_t	*supermapfloor;
	mlx_texture_t	*supermapwall;
	mlx_texture_t	*sprites[SPRITETEXTURES]; // 0 is skipped for checking if texture even exists
}	t_textures;

typedef struct s_images
{
	mlx_image_t		*background;
	mlx_image_t		*hud;
	mlx_image_t		*menuscreen;
	mlx_image_t		*textscreen;
	mlx_image_t		*screen;		//3d
	mlx_image_t		*spritescreen;	//sprites
	mlx_image_t		*fogscreen;		//fog
	mlx_image_t		*maximap;
	mlx_image_t		*minimap;
	mlx_image_t		*supermap;
	mlx_image_t		*overlay;		//put text here
	// mlx_image_t		*str[STRINGS];	//strings from MLX
}	t_images;

typedef struct s_gametext
{
	mlx_texture_t	*background;
	mlx_texture_t	*font;
	char			*text;
	char			stats[512];
	int				i;	
	mlx_image_t		*image;
	unsigned int	c;
	unsigned int	cb;
	int				sx;
	int				sy;
	int				x;
	int				y;
	int				highlight;
	int				offset;
	int				height;
	int				timems;
}	t_gametext;

typedef struct s_highscore
{
	char			name[64];
	char			coalition[64];
	char			campus[64];
	unsigned int	timems;
	int				index;
	int				score;
	int				level;
}	t_hs;

typedef struct s_overlay
{
	t_text		basicinfo;
	t_text		playerinfo;
	t_text		gameplayinfo;
	t_text		timeinfo;
	t_text		rayinfo;
}	t_overlay;

typedef struct s_settings
{
	int			fov;
	int			dof;
	int			lightdist;
	long long	maxdist;
	int			tick;
	// int		width;
	// int		height;
	// int		mapwidth;
	// int		mapheight;
	// int		miniwidth;
	// int		miniheight;
	int			fisheyecorrection;
	int			debugging;
}	t_settings;

typedef struct s_max
{
	mlx_t			*mlx;
	t_map			map; //no need for pointer
	t_math			*math; //no need for a pointer
	t_controls		key;
	int				keys[350];
	t_kb			kb;
	t_menu			menu;
	t_gametext		gamestart;
	t_gametext		gamewon;
	t_gametext		gamelost;
	t_font			font;
	t_overlay		overlay;
	t_settings		settings;
	// mlx_image_t		*str[STRINGS];	//replace later with our own thing
	//char			s[STRINGS][256];//replace later with our own thing
	char			name[20];
	char			coalition[20];
	char			campus[20];//make it a list later
	t_textures		t;//not a pointer
	t_images		i;
	// int				death;
	// int				lives;
	// int				score;
	// int				exit;
	// int				time;
	int				game_mode;		//GAMESTART / MENU / GAMEPLAY/ GAMEWON...
	int				game_type;		//CAMPAIGN, TIMETRIAL, ONEMAP
	int				difficulty;		//EASY MEDIUM HARD
	int				game_in_progress;
	int				reachedexit;
	int				mmode;
	int				ray;
	int				level;
	int				score;
	time_t			oldms;
	time_t			newms;
	unsigned int	gamems;
	unsigned int	levelms;
	unsigned int	framems;
	unsigned int	limitms;
	unsigned int	timetriallimitms;
	char			campaignmap[256];
	long			frame;
	unsigned int	fog[SCREENHEIGHT][SCREENWIDTH];
}	t_max;

// PROTOTYPES

//ft_free.c
void	ft_free(t_max *max);
void	ft_exit(t_max *max, int code);
void	ft_freemap(t_map *map);

//ft_button.c
void	ft_initbuttons(t_max *max);
void	ft_draw_button(t_button *b, int state);
void	ft_choose_in_button(t_max *max, t_button *button);

//ft_textfield.c
void	ft_inittextfields(t_max *max);
void	ft_draw_textfield(t_textfield *b, int state);
void	ft_write_in_textfield(t_max *max, t_textfield *textfield);

//ft_listfield.c
void	ft_initlistfields(t_max *max);
void	ft_bigreinitlistfield(t_max *max);
void	ft_draw_listfield(t_listfield *lf, int state);
void	ft_choose_in_listfield(t_max *max, t_listfield *listfield);

//ft_text.c
void	ft_draw_text(t_text *text, int state);

//ft_halloffame.c
int		ft_writescore(t_max *max);
int		ft_readscore(t_max *max);
void	ft_halloffame(t_max *max);

//parser.c
void	ft_init_brume(t_max *max);
void	ft_print_map(t_map *map);
void	ft_fill_colours_to_map(t_map *map);
void	ft_load_texture(char *path, mlx_texture_t **texture);
int		ft_process_file(t_max *max);
void	ft_init_time(t_max *max);

//ft_random.map.c
void	ft_inittimetrialmap(t_randommap *rm, int level);
int		ft_process_random(t_max *max);

//ft_game.c
void	ft_amaze_standard(t_max *max);

//ft_game_bonus.c
void	ft_amaze_bonus(t_max *max);

//ft_gamestart.c
void	ft_draw_background(t_max *max);
void	ft_draw_gametext(t_gametext *text);
void	ft_initgamestart(t_max *max);
void	ft_gamestart(t_max *max);

void	ft_initgamewon(t_max *max);
void	ft_gamewon(t_max *max);

void	ft_initgamelost(t_max *max);
void	ft_gamelost(t_max *max);

//ft_hook.c
void	ft_hook(void *param);

//ft_map.c
void	ft_draw_map(t_max *max);

//ft_minimap.c
void	ft_draw_minimap(t_max *max);

//ft_rays.c
//void	ft_init_rays(t_max *max);
void	ft_visit_map(t_map *map, long long length, long long dist, int mp);
void	ft_init_orays(t_max *max);

//ft_line.c
void	ft_place_line(mlx_image_t *img, t_line l);

//ft_menu.c
void	ft_initmenu(t_max *max);
void	ft_menu(t_max *max);
void	ft_resume(t_max *max);
void	ft_newgame(t_max *max);

//ft_mousehook.c
void	ft_cursorhook(void *param);
void	ft_mousehook(void *param);

//ft_gameplay.c
void	ft_gameplay(t_max *max);

//ft_overlay.c
void	ft_init_overlay(t_max *max);
void	ft_clear_overlay(t_max *max);

//ft_saveload.c
int	ft_savegame(t_max *max);
int	ft_loadgame(t_max *max);
int	ft_quicksave(t_max *max);
int	ft_quickload(t_max *max);
int	ft_save(t_max *max, char *path);
int	ft_load(t_max *max, char *path);


//ft_screen2d.c
void	ft_draw_screen2d(t_max *max);
//ft_screen2d.c
void	ft_draw_screen2dquad(t_max *max);

//ft_screen3d.c
void	ft_draw_screen3d(t_max *max);
void	ft_init_fogscreen(t_max *max);

//ft_sprite.c
void	ft_init_sprites_flamingo(t_map *map, int i);
void	ft_init_sprites_doors(t_map *map, int i, int type);
void	ft_init_sprites(t_max *max);
void	ft_check_sprites(t_max *max);
void	ft_draw_sprites(t_max *max);

//ft_doors.c
void	ft_interact_door(t_max *max);
void	ft_check_doors(t_max *max);

//ft_settings.c
void	ft_init_settings(t_max *max);

//ft_keyhook.c
void	ft_clear_keys(t_max *max);
void	ft_keyhook(mlx_key_data_t keydata, void *param);

#endif
