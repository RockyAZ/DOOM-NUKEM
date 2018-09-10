/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 19:15:21 by azaporoz          #+#    #+#             */
/*   Updated: 2018/08/31 19:15:24 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

// # define WIDTH 640
// # define HEIGHT 400
// # define WIDTH 320
// # define HEIGHT 200
# define WIDTH 1200
# define HEIGHT 1080

#define YELLOW 4294967040
#define RED 4294901760
#define BLUE 4278190335
#define GREEN 4278255360
#define BLU 4278255615
#define PURPLE 4294902015

# define CENTER_W WIDTH / 2
# define CENTER_H HEIGHT / 2
# define WALL 1
# define FOV 60
#define SCREEN 277

# include "./libft/libft.h"
# include "SDL.h"
# include "SDL_image.h"

# include <fcntl.h>
# include <math.h>
#include<stdio.h>
#include<pthread.h>
/*
** struct s_form aka POLYGON
*/

typedef struct		s_vector
{
	double			x;
	double			y;
}					t_vector;

// typedef struct		s_draw_vector
// {
// 	double			x;
// 	double			y;
// 	int				is_right;
// }					t_draw_vector;

/*
** vert == vertex
*/
typedef struct		s_vert
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
}					t_vert;

typedef struct		s_form
{
	double			dist;
	t_vector		norm;
	t_vert			vertex;
unsigned int color;
	struct s_form	*next;
	char n;
}					t_form;

typedef struct		s_bsp
{
	struct s_bsp	*front;
	struct s_bsp	*back;
	t_form			**arr_form;
	t_form			*node_form;
	int				is_leaf;
	int				is_solid;
}					t_bsp;

typedef struct		s_screen
{
	int				x1;
	int				x2;
	struct s_screen	*next;
}					t_screen;

typedef struct		s_player
{
	t_bsp *pos;
	t_vector		view;
	double			normal;

	t_vector		view_right;
	double			normal_right;

	double			screen_coef;
	double			angle_coef;
	int				found_p;
	double			x;
	double			y;
	int				angle;
	int				front;
}					t_player;

typedef struct		s_doom
{
//если закоментить сздесь
	unsigned int	buffer[HEIGHT][WIDTH];
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*screen;
	SDL_Event		e;
	t_bsp			*bsp;
	t_form			*first_form;
	t_player		*gg;
	t_screen		*scr_buf;
//и разкоментить эту шнягу, то doom->quit будет заменён на значение приcвающееся буферу
//какого хрена???
	// unsigned int	buffer[HEIGHT][WIDTH];
	int				quit;
	int				form_counter;
}					t_doom;

//error::
void				error(char *name);
//build bsp tree::
void				first_bsp(t_doom *doom);

//vectors::
double				dot_prod(double x1, double y1, double x2, double y2);
double				pifagor(double a, double b);
t_vector			normalizing(double x, double y);
void				vector_prep(t_form *form);
//player manipulations::
void				drawing_wall(t_doom *doom);
//angle calc::
double				ft_tan(double angle);
double				ft_cos(double angle);
double				ft_sin(double angle);
double				acos_degree(double c);

//additional functions::
double				ft_min_d(double x, double y);
double				ft_max_d(double x, double y);

//shit!!::
void print_bsp(t_bsp *bsp);
#endif