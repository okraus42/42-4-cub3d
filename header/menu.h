/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:56:41 by okraus            #+#    #+#             */
/*   Updated: 2024/03/28 16:04:25 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../.MLX42/include/MLX42/MLX42.h"
# include "../libft/header/libft.h"

//modes
# define MENU 1
# define GAMESTART 2
# define GAMEPLAY 3
# define GAMEWIN 4
# define GAMELOSS 5
# define NEXTLEVEL 6

//buttons
//mainbuttons
# define RESUME 0
# define NEWGAME 1
# define SAVEGAME 2
# define LOADGAME 3
# define SETTINGS 4
# define HALLOFFAME 5
# define QUITGAME 6
# define MAINBUTTONSCOUNT 7

//newwriting
# define NAME 0
# define COALITION 1
# define CAMPUS 2
# define NWBACK 3
# define NWCONTINUE 4
# define WRITINGBUTTONCOUNT 5
# define WRITINGTEXTFIELDCOUNT 3

//game difficulty
# define EASY 0
# define MEDIUM 1
# define HARD 2
# define GDBACK 3
# define GDCONTINUE 4
# define DIFFICULTYBUTTONCOUNT 5

//game type
# define CAMPAIGN 0
# define TIMETRIAL 1
# define ONEMAP 2
# define GTBACK 3
# define GTCONTINUE 4
# define GAMETYPEBUTTONCOUNT 5

//map type
# define CUSTOM 0
# define RANDOM 1
# define MTBACK 2
# define MAPTYPEBUTTONCOUNT 3

//map selection
# define MSBACK 2
# define MSCONTINUE 3
# define MAPSELECTIONBUTTONCOUNT 4

// compile with libft.a
// pass number for
// width, height, ratio of dead ends, loops, T-intersections, X-intersections
// notoverlapping room placement attempts, overlapping rooms placement attempts
// chance to create extra doors (higher is better, 4096 is max)
// chance to remove deadends 0 keeps deadends, 1 removes dead ends,
// 2 - 1024 chance to remove percentage of deadends
// like 52 26 4 5 3 2 20 10 25 512
//	++ floor colour || ceiling colour || fog colour

//random parametres
//width || height
//deadends || loops || T || X
//rooms not overlapping || rooms overlapping
// doors || deadends
# define RWIDTH 0
# define RHEIGHT 1
# define RRATIODE 2 //deadends || loops || T || X
# define RRATIOLO 3
# define RRATIOTI 4
# define RRATIOXI 5
# define RNOROOMS 6
# define ROROOMS 7
# define RDOORS 8
# define RDEADENDS 9
# define RBACK 10
# define RCONTINUE 11
# define RANDOMBUTTONCOUNT 12

# define MAINBUTTONS 0		//resume-quit
# define NEWWRITING 1		// name, coalition, campus 
# define NEWDIFFICULTY 2	//easy, medium, hard
# define NEWSELECTION 3		// campaign, time, one level
# define NEWLEVEL 4			// select map || random map
# define NEWMAP 5			// choose a map from the list
# define NEWRANDOM 6		// choose parameters for a random generation
# define BUTTONGROUPS 7

# define S_RESUME "RESUME"
# define S_SETTINGS "SETTINGS"
# define S_HALLOFFAME "HALL OF\n  FAME"
# define S_NEWGAME "NEW GAME"
# define S_QUITGAME "QUIT GAME"
# define S_SAVEGAME "SAVE GAME"
# define S_LOADGAME "LOAD GAME"

# define S_NAME "NAME"
# define S_COALITION "COALITION"
# define S_CAMPUS "CAMPUS"
# define S_EASY "EASY"
# define S_MEDIUM "MEDIUM"
# define S_HARD "HARD"
# define S_BACK "BACK"
# define S_CONTINUE "CONTINUE"
# define S_CAMPAIGN "CAMPAIGN"
# define S_TIMETRIAL "TIME TRIAL"
# define S_ONEMAP "ONE MAP"
# define S_CUSTOM "CUSTOM"
# define S_RANDOM "RANDOM"
# define S_RWIDTH "WIDTH"
# define S_RHEIGHT "HEIGHT"
# define S_RRATIODE "RATIODE"
# define S_RRATIOLO "RATIOLO"
# define S_RRATIOTI "RATIOTI"
# define S_RRATIOXI "RATIOXI"
# define S_RNOROOMS "NO ROOMS"
# define S_ROROOMS "O ROOMS"
# define S_RDOORS "DOORS"
# define S_RDEADENDS "DEAD ENDS"

//# define S_ ""

# define C_INACTIVE 0x7F7F7FFF
# define C_ACTIVE 0X7F007FFF
# define C_SELECTED 0XFF00FFFF
# define C_ACTIVATED 0XFF7FFFFF

# define INVISIBLE 0
# define INACTIVE 1
# define ACTIVE 2
# define SELECTED 4
# define ACTIVATED 8

typedef struct s_text
{
	mlx_texture_t	*font;
	mlx_image_t		*image;
	char			*text;
	char			str[20];
	unsigned int	c;
	unsigned int	cb;
	int				sx;
	int				sy;
	int				x;
	int				y;
	int				i;
	int				highlight;
	int				offset;
	int				height;
}	t_text;

typedef struct s_values
{
	int				min;
	int				max;
	int				value;
}	t_values;

typedef struct s_randommap
{
	t_values	width;
	t_values	height;
	t_values	ratiode;
	t_values	ratiolo;
	t_values	ratioti;
	t_values	ratioxi;
	t_values	rnorooms;
	t_values	rorooms;
	t_values	rdoors;
	t_values	rdeadends;
}	t_randommap;

typedef struct s_button
{
	mlx_texture_t	*button;
	mlx_image_t		*image;
	t_text			text;
	unsigned int	c;
	int				x;
	int				y;
	int				w;
	int				h;
	int				id;
	int				group;
	int				state;
	t_values		*val;
	char			*str;
	struct s_button	*up;
	struct s_button	*down;
	struct s_button	*left;
	struct s_button	*right;
}	t_button;

typedef struct s_textfield
{
	mlx_texture_t	*textfield;
	mlx_image_t		*image;
	t_text			text;
	unsigned int	c;
	int				x;
	int				y;
	int				w;
	int				h;
	int				state;
}	t_textfield;

typedef struct s_listfield
{
	mlx_texture_t	*listfield;
	mlx_image_t		*image;
	t_text			text[5];
	t_dlist			*texts;
	char			*files[5]; //temporary before list is working
	unsigned int	c;
	int				x;
	int				y;
	int				w;
	int				h;
	int				highlight;
	int				state;
}	t_listfield;

typedef struct s_font
{
	mlx_texture_t	*asciitest;
}	t_font;

typedef struct s_menu
{
	int				current_button[BUTTONGROUPS];
	int				current_buttongroup;
	int				enter;
	int				selection;
	int				newmap;
	int				newwriting;
	int				cm_state;
	int				random_state[RANDOMBUTTONCOUNT];
	t_randommap		rm;
	//int			newlevel;
	mlx_texture_t	*background;
	mlx_texture_t	*button;
	mlx_texture_t	*buttonplus;
	mlx_texture_t	*textfield;
	mlx_texture_t	*listfield;
	// t_button		yes;
	// t_button		no;
	t_textfield		newwritingfields[WRITINGTEXTFIELDCOUNT];
	t_button		mainbuttons[MAINBUTTONSCOUNT];
	t_button		newwritingbuttons[WRITINGBUTTONCOUNT];
	t_button		gamedifficultybuttons[DIFFICULTYBUTTONCOUNT];
	t_button		gametypebuttons[GAMETYPEBUTTONCOUNT];
	t_button		maptypebuttons[MAPTYPEBUTTONCOUNT];
	t_button		mapselectionbuttons[MAPSELECTIONBUTTONCOUNT];
	t_button		randomselectionbuttons[RANDOMBUTTONCOUNT];
	t_listfield		custommap;
}	t_menu;

