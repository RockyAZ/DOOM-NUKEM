/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 19:15:58 by azaporoz          #+#    #+#             */
/*   Updated: 2018/08/31 19:15:58 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	doom_prepare(t_doom **doom,int x,int y)
{
	t_doom *cp_doom;

	if (!(cp_doom = (t_doom*)malloc(sizeof(t_doom))))
		error("doom malloc error\n");
	// cp_doom->quit = (int*)malloc(sizeof(int));
	// *cp_doom->quit = 0;
	cp_doom->quit = 0;	
	cp_doom->gg = (t_player*)malloc(sizeof(t_player));
	cp_doom->gg->x = x;
	cp_doom->gg->y = y;
	cp_doom->gg->view.x = 0;
	cp_doom->gg->view.y = 1;
	cp_doom->gg->normal = dot_prod(cp_doom->gg->x, cp_doom->gg->y, cp_doom->gg->view.x, cp_doom->gg->view.y);
	cp_doom->gg->view_right.x = cp_doom->gg->view.y;
	cp_doom->gg->view_right.y = cp_doom->gg->view.x * -1;
	cp_doom->gg->normal_right = dot_prod(cp_doom->gg->x, cp_doom->gg->y, cp_doom->gg->view_right.x, cp_doom->gg->view_right.y);
	cp_doom->gg->angle = 180;
	cp_doom->gg->angle_coef = (float)WIDTH / (float)FOV;
	cp_doom->gg->screen_coef = FOV / WIDTH;
cp_doom->scr_buf = (t_screen*)malloc(sizeof(t_screen));//here malloc for t_screen?!?!?
	*doom = cp_doom;
}

void	print_normal(t_doom *doom)
{
	printf("A::%f::%f\n", doom->first_form->norm.x, doom->first_form->norm.y);
	printf("B::%f::%f\n", doom->first_form->next->norm.x, doom->first_form->next->norm.y);
	printf("C::%f::%f\n", doom->first_form->next->next->norm.x, doom->first_form->next->next->norm.y);
	printf("D::%f::%f\n", doom->first_form->next->next->next->norm.x, doom->first_form->next->next->next->norm.y);
	printf("E::%f::%f\n", doom->first_form->next->next->next->next->norm.x, doom->first_form->next->next->next->next->norm.y);
}

void	print_normal_1(t_doom *doom)
{
	printf("A::%f::%f\n", doom->first_form->norm.x, doom->first_form->norm.y);
}

void	calc_forms(t_form *form)
{
	while (form != NULL)
	{
		vector_prep(form);
		form = form->next;
	}
}

void	make_forms(t_doom *doom)
{
	t_form	*form;

	form = (t_form*)malloc(sizeof(t_form));
	form->vertex.x1 = 2;
	form->vertex.y1 = 7;
	form->vertex.x2 = 6;
	form->vertex.y2 = 4;
	form->color = RED;
	form->n = 'A';

	form->next = (t_form*)malloc(sizeof(t_form));
	form->next->vertex.x1 = 1;
	form->next->vertex.y1 = 1;
	form->next->vertex.x2 = 3;
	form->next->vertex.y2 = 5;
	form->next->color = BLUE;
	form->next->n = 'B';

	form->next->next = (t_form*)malloc(sizeof(t_form));
	form->next->next->vertex.x1 = 5;
	form->next->next->vertex.y1 = 1;
	form->next->next->vertex.x2 = 5;
	form->next->next->vertex.y2 = 4;
	form->next->next->color = GREEN;
	form->next->next->n = 'C';

	form->next->next->next = (t_form*)malloc(sizeof(t_form));
	form->next->next->next->vertex.x1 = 3;
	form->next->next->next->vertex.y1 = 8;
	form->next->next->next->vertex.x2 = 5;
	form->next->next->next->vertex.y2 = 6;
	form->next->next->next->color = BLU;
	form->next->next->next->n = 'D';

	form->next->next->next->next = (t_form*)malloc(sizeof(t_form));
	form->next->next->next->next->vertex.x1 = 1;
	form->next->next->next->next->vertex.y1 = 3;
	form->next->next->next->next->vertex.x2 = 1;
	form->next->next->next->next->vertex.y2 = 5;
	form->next->next->next->next->n = 'E';
	form->next->next->next->next->color = PURPLE;
	form->next->next->next->next->next = NULL;

	doom->first_form = form;
	doom->form_counter = 5;
}

void	make_forms_1(t_doom *doom)
{
	t_form	*form;

	form = (t_form*)malloc(sizeof(t_form));
	form->vertex.x1 = 4;
	form->vertex.y1 = 5;
	form->vertex.x2 = 40;
	form->vertex.y2 = 5;
	form->color = RED;
	form->n = 'A';

	form->next = (t_form*)malloc(sizeof(t_form));
	form->next->vertex.x1 = 0;
	form->next->vertex.y1 = 8;
	form->next->vertex.x2 = 4;
	form->next->vertex.y2 = 8;
	form->next->color = GREEN;
	form->next->n = 'B';
	form->next->next = NULL;
// form->next = NULL;
// doom->form_counter = 1;

	doom->form_counter = 2;
	doom->first_form = form;
}

int	main(int ac, char **av)
{
	t_doom *doom;
	if (ac != 3)
		return(printf("ARGC!!!!\n"));
	doom_prepare(&doom ,atoi(av[1]), atoi(av[2]));

	SDL_Init(SDL_INIT_VIDEO);
	doom->win = SDL_CreateWindow("DOOM-NUKEM, BITCH!!", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	doom->ren = SDL_CreateRenderer(doom->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	doom->screen = SDL_CreateTexture(doom->ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
	SDL_SetTextureBlendMode(doom->screen, SDL_BLENDMODE_BLEND);

	// make_forms(doom);
make_forms_1(doom);
	
	calc_forms(doom->first_form);
	first_bsp(doom);

// print_normal(doom);
// print_normal_1(doom);

	print_bsp(doom->bsp);
	drawing_wall(doom);
	// system ("leaks doom-nukem");
unsigned long long int rr = 0;
double old;
	while (doom->quit == 0)
	{
rr++;
		SDL_SetRenderDrawColor(doom->ren, 0, 0, 0, 0);
		SDL_RenderClear(doom->ren);
	// event_callback(win);
	// active_keys(win);
		while (SDL_PollEvent(&doom->e))
		{
			if (doom->e.type == SDL_KEYDOWN && doom->e.key.keysym.sym == SDLK_w)
				doom->gg->y += 1;
			else if (doom->e.type == SDL_KEYDOWN && doom->e.key.keysym.sym == SDLK_s)
				doom->gg->y -= 1;
			else if (doom->e.type == SDL_KEYDOWN && doom->e.key.keysym.sym == SDLK_d)
				doom->gg->x += 1;
			else if (doom->e.type == SDL_KEYDOWN && doom->e.key.keysym.sym == SDLK_a)
				doom->gg->x -= 1;
			else if (doom->e.type == SDL_KEYDOWN && doom->e.key.keysym.sym == SDLK_RIGHT)
			{
				old = doom->gg->view.x;
				doom->gg->view.x = doom->gg->view.x * cos(-0.04) - doom->gg->view.y * sin(-0.04);
				doom->gg->view.y = old * sin(-0.04) + doom->gg->view.y * cos(-0.04);
				
			}
			else if (doom->e.type == SDL_KEYDOWN && doom->e.key.keysym.sym == SDLK_LEFT)
			{
				old = doom->gg->view.x;
				doom->gg->view.x = doom->gg->view.x * cos(0.04) - doom->gg->view.y * sin(0.04);
				doom->gg->view.y = old * sin(0.04) + doom->gg->view.y * cos(0.04);
			}

			else if (doom->e.type == SDL_KEYDOWN && doom->e.key.keysym.sym == SDLK_ESCAPE)
				doom->quit = 1;
	doom->gg->view_right.x = doom->gg->view.y;
	doom->gg->view_right.y = doom->gg->view.x * -1;
	doom->gg->normal_right = dot_prod(doom->gg->x, doom->gg->y, doom->gg->view_right.x, doom->gg->view_right.y);
			if (doom->e.type == SDL_QUIT)
				doom->quit = 1;
		}
		drawing_wall(doom);
		SDL_UpdateTexture(doom->screen, NULL, doom->buffer[0], WIDTH << 2);
		for(int j = 0; j < HEIGHT; j++)
			for(int h = 0; h < WIDTH; h++)
				doom->buffer[j][h] = 0;
		SDL_RenderCopy(doom->ren, doom->screen, NULL, NULL);
		SDL_RenderPresent(doom->ren);
printf("%llu\n", rr);
	}
	printf("%d\n", doom->quit);
	// SDL_DestroyRenderer(doom->ren);
	// SDL_DestroyWindow(doom->win);
	SDL_Quit();
	return (0);
}
  // while (SDL_PollEvent(&doom->e))
  // {
  // if (doom->e.type == SDL_QUIT)
  // doom->quit = 1;
  // if (doom->e.type == SDL_KEYDOWN)
  // {
  // if (doom->e.key.keysym.sym == SDLK_w)
  // doom->gg->y += 1;
  // if (doom->e.key.keysym.sym == SDLK_s)
  // doom->gg->y -= 1;
  // if (doom->e.key.keysym.sym == SDLK_a)
  // doom->gg->x -= 1;
  // if (doom->e.key.keysym.sym == SDLK_d)
  // doom->gg->x += 1;
  // if (doom->e.key.keysym.sym == SDLK_ESCAPE)
  // doom->quit = 1;
  // }
  // // key_press_add(win->e.key.keysym.sym, win);  
  // }