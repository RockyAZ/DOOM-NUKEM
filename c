T\n");
		recursive_draw(bsp->back, player, doom);
								  		  draw_polygon(bsp, player, doom, len);
										  					// printf("%c\n", bsp->node_form->n);
															   				  recursive_draw(bsp->front, player, doom);
																			  							 }
																											else
																												{
																												// printf("SECOND\n");
																													recursive_draw(bsp->front, player, doom);
																																			   		   if (len != 0)
																																					   	  	   	  draw_polygon(bsp, player, doom, len);
																																								  					// printf("%c\n", bsp->node_form->n);
																																													   				  recursive_draw(bsp->back, player, doom);
																																																	  							}
																																																								}

																																																								void drawing_wall(t_doom *doom)
																																																								{
																																																								 printf("===========================================================\n");
																																																								  recursive_draw(doom->bsp, doom->gg, doom);
																																																								  							printf("===========================================================\n");
																																																															}
																																																															