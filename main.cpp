#include "src/HeaderManager.cpp"
#define displayWidth 901
#define displayHeight 675
#define FPS 13.0
int main(){
	FILE *fp;
	/*Initializer Allegro*/
	if(!al_init()){
		cout << "Allegro no se pudo iniciar";
		return -1;
	}
	/*Create Window*/
	ALLEGRO_DISPLAY *display;
	display = al_create_display(displayWidth,displayHeight);
	if(!display){ cout << "Fallo a crear el display" << endl; }
	al_set_window_title( display, "BomberMan" );

	/*Inserts libraries of Allegro*/
	al_install_keyboard();
	al_install_mouse();

	al_init_image_addon();
	al_init_acodec_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();

	al_reserve_samples(1);

	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);
	ALLEGRO_TIMER *frame_timer = al_create_timer(1.0/FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_SAMPLE *sound = al_load_sample("sound/title_music.ogg");
	ALLEGRO_SAMPLE *select = al_load_sample("sound/earth.ogg");	
	ALLEGRO_SAMPLE *enter = al_load_sample("sound/fire_1.ogg");
	

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(frame_timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	
	FactoryMethod fm;
	InputManager<ALLEGRO_EVENT,ALLEGRO_KEYBOARD_STATE> input;
	Maps<ALLEGRO_BITMAP> m;
	Player<ALLEGRO_BITMAP> p;

	//Cargar el juego desde el inicio 
	fm.loadSection();

   	al_start_timer(timer);
    al_start_timer(frame_timer);
	
    bool done = false,draw = false,st = false,active1 = false,active2 = false,once = false,key_timer = false,sourceX = 0;
    char c;
	int x = 0, y = 0,ap1 = 0, ap2 = 0;
				
    while(!done){
		ALLEGRO_EVENT events;
	    al_wait_for_event(event_queue,&events);
	    al_get_keyboard_state(&key_state);

	    //pressClose(done, events);
		if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)		{ done = true; }
		//pressEscape(events,s,input,p);
		if(input.IsKeyPressed(events,ALLEGRO_KEY_ESCAPE)){
			if(fm.isCreateChoosePlayer()){
	   			fm.setMenu(true);
				fm.setChoosePlayer(false);
				fm.restartInput(input);
			}else if(fm.isCreateChooseMap()){
	   			fm.setChoosePlayer(true);	
				fm.setChooseMap(false);
				fm.restartInput(input);				

				fm.loadSection(2);
				fm.setReadyPlayer(0,false);
				fm.setReadyPlayer(1,false);			
				fm.loadSection(3);
			}else if(fm.isCreateBeginPlay()){
				fm.setBeginPlay(false);
				fm.setShowPause(true);
				
				fm.restartInput(input);

				input.setUserKeyboard(0,false);
				input.setUserKeyboard(1,false);

				fm.setNoAnimatePlay(true);
			}else if(fm.isCreateSave()){
				fm.loadSection(4);
				fm.setNoAnimatePlay(false);
				fm.loadSection(1);
				if(fm.getLoadMapPlayer()){
					fm.setBeginPlay(true);
					fm.setSave(false);

			   		input.setUserKeyboard(0, true);
			   		input.setUserKeyboard(1, true);

			   		input.setX(0, p.getLastX(0));
			   		input.setY(0, p.getLastY(0));

			   		input.setX(1, p.getLastX(1));
			   		input.setY(1, p.getLastY(1));
				}else{
					fm.setSave(false);
					fm.setMenu(true);
					fm.restartInput(input);
				}
			}
		}
		//pressEnter(done,once,events,s,input,p);
	    if(input.IsKeyPressed(events,ALLEGRO_KEY_ENTER)){
	   		if(fm.isCreateMenu()){
	   			switch(fm.getButtonSelectMenu()){
	   				case 0: 
	   					fm.setMenu(false);
	   					fm.setChoosePlayer(true);
	   				break;
	   				case 1:
	   					fm.setMenu(false);
						fm.setSave(true);
	   					fm.setButtonSelectMenu(-1);
	   				break;
	   				case 2: done = true; break;	
	   			}

				fm.restartInput(input);
				//fm.setReadyPlayer(0,false);
				//fm.setReadyPlayer(1,false);
	   		}else if(fm.isCreateChoosePlayer()){
	   			if(fm.getReadyPlayer(0) == 1 && fm.getReadyPlayer(1) == 1){	   				
	   				p.pushAvatar(fm.getAvatarCodePlayer1(), fm.getAvatarCodePlayer2());
	   				fm.setChoosePlayer(false);
	   				fm.setChooseMap(true);
	   			
	   				input.setUserKeyboard(0, true);
	   				fm.restartInput(input);
	   			}
	   		}else if(fm.isCreateChooseMap()){
	   			fm.setChooseMap(false);
	   			fm.setBeginPlay(true);

	   			input.setUserKeyboard(0, true);
	   			input.setUserKeyboard(1, false);

	   			fm.restartInput(input);
	   		}else if(fm.isCreateShowResults()){
	   			input.setUserKeyboard(0, true);
	   			input.setUserKeyboard(1, true);

				fm.setMenu(true);
	   			fm.setBeginPlay(false);
	   			fm.setShowResults(false);
	   			
				fm.restartInput(input);

				fm.loadSection(4);
				fm.setLoadMapPlayer(false);
				once = false;
			}else if(fm.isCreateShowPause()){
				switch(fm.getButtonSelectPause()){
	   				case 0: 
	   					fm.setShowPause(false);
	   					fm.setBeginPlay(true);

			   			input.setUserKeyboard(0, true);
			   			input.setUserKeyboard(1, true);

			   			input.setX(0, p.getLastX(0));
			   			input.setY(0, p.getLastY(0));

			   			input.setX(1, p.getLastX(1));
			   			input.setY(1, p.getLastY(1));
			   			fm.loadSection(4);
						fm.setNoAnimatePlay(false);
	   					fm.loadSection(5);
	   				break;
	   				case 1:
	   					fm.setShowPause(false);
						fm.setSave(true);
	   					fm.setButtonSelectPause(-1);
	   				break;
	   				case 2: done = true; break;	
	   			}
			}else if(fm.isCreateSave()){

			}else{
				done = false;
			}
	   	}

	   	// Escoger el jugador
	   	//actionChoosePlayer(events,s,input);
	   	if(fm.isCreateChoosePlayer()){
	   		if(input.IsKeyPressed(events, ALLEGRO_KEY_T)){
	   			if(fm.readyPlayer(0, input))
	   				input.setUserKeyboard(0, false);
	   			else
	   				input.setUserKeyboard(0, true);
	   		}
	   		if(input.IsKeyPressed(events, ALLEGRO_KEY_P)){
	   			if(fm.readyPlayer(1, input))
	   				input.setUserKeyboard(1, false);
	   			else
	   				input.setUserKeyboard(1, true);
	   		}
	   	}

		//useSave(st,m,events,fp,s,input,p);
		if(fm.isCreateSave()){
			fm.loadSection(4);
	   		if(input.IsKeyPressed(events, ALLEGRO_KEY_C) && !fm.getLoadMapPlayer()){
	   			fm.loadSection(1);
	   			cout << "Cargar Partida" << endl;
	   			fp = fm.File("r");
	   			char c;
	   			int x,y,ap1,ap2;
	   			x = y = ap1 = ap2 = 0;
	   			while((c = fgetc(fp)) != EOF){
					if(y < 14){
						if(c == '\n'){
							y++;
							x = -1;
						}else{
							st = true;
							fm.loadSection(4);
							fm.setMap(x,y,c);
							fm.loadSection(1);							
							switch(c){
								case 'j': p.setX(0,x); p.setY(0,y); p.setLastX(0,x); p.setLastY(0,y); p.setDir(0,0); break;
								case 'g': p.setX(1,x); p.setY(1,y); p.setLastX(1,x); p.setLastY(1,y); p.setDir(1,0); break;

								case 'x': p.setX(0,x); p.setY(0,y); p.setLastX(0,x); p.setLastY(0,y); p.setDir(0,0); p.putBomb(x,y,0); break;
								case 'y': p.setX(1,x); p.setY(1,y); p.setLastX(1,x); p.setLastY(1,y); p.setDir(1,0); p.putBomb(x,y,1); break;
								
								case 'z': p.putBomb(x,y,0); break;  
							}
						}
						x++;
					}else{
						if(y == 15 ){
							ap1 = c - '0'; 	
						}else if( y == 17){
							ap2 = c - '0';
						}
						y++;
					}
				}
				
				if(st){
					fm.loadSection(4);
					fm.setNoAnimatePlay(false);
					fm.loadSection(1);
					m.setWidth(20);
					m.setHeight(14);
					x = y = 0;
					p.pushAvatar(ap1, ap2);
	    			fm.loadSection(4);
					fm.setLoadMapPlayer(true);
					fm.loadSection(1);
					fm.setSave(false);
					fm.setBeginPlay(true);
					st = false;
				}

				fclose(fp);
	   		}else if(input.IsKeyPressed(events, ALLEGRO_KEY_G) && fm.getLoadMapPlayer()){
	   			fm.loadSection(1);
	   			cout << "Guardar Partida" << endl;
	   			fp = fm.File("w");
	   			for(int y = 0;y<m.getHeight();y++){
					for(int x = 0;x<m.getWidth();x++){
						fm.loadSection(4);
						fputc(fm.getMap(x,y),fp);	
						fm.loadSection(1);
						if(x == (m.getWidth()-1) && y >= 0){
							fputc('\n',fp);
						}
					}
				}

				fputc('\n',fp);
				fputc(fm.getAvatarCodePlayer1()+'0',fp);	
				fputc('\n',fp);
				fputc(fm.getAvatarCodePlayer2()+'0',fp);

				fclose(fp);
	   		}
	   	}

		//Secciones del Juego
 	    if(events.type == ALLEGRO_EVENT_TIMER){
			if(events.timer.source == timer){
				draw = true;
				fm.loadSection();
		   		if(fm.isCreateMenu()){
	    			//Player 1
	    			if(input.getX(0) >= 0 ) { input.setX(0, 0);}	    			
	    			if(input.getY(0) >= 3 ){ input.setY(0, 2);}

		   			fm.showSection(input,m,p,false);
		   		}else if(fm.isCreateChoosePlayer()){
	    			m.loadMap(1);
	    			//Player 1
	    			if(input.getX(0) >= m.getWidth() ) { input.setX(0, m.getWidth()-1);}	    			
	    			if(input.getY(0) >= m.getHeight() ){ input.setY(0, m.getHeight()-1);}

	    			//Player 2
	    			if(input.getX(1) >= m.getWidth() ) { input.setX(1, m.getWidth()-1);}	    			
	    			if(input.getY(1) >= m.getHeight() ){ input.setY(1, m.getHeight()-1);}

	    			fm.showSection(input,m,p,false);
	    			fm.drawButton();
	    		}else if(fm.isCreateChooseMap()){
	    			//Player 1
	    			if(input.getX(0) >= 3 ) { input.setX(0, 2);}	    			
	    			if(input.getY(0) >= 1 ){ input.setY(0, 0);}
	    			fm.showSection(input,m,p,false);
	    			fm.drawButton();
	    		}else if(fm.isCreateBeginPlay()){
	    			// Descargamos el mapa en donde se va a jugar
	    			fm.downloadMapPlayer(m, p);
	    			if(!once){
	    				//Activamos el uso del teclado
		   				input.setUserKeyboard(0, true);
		   				input.setUserKeyboard(1, true);

	    				fm.showCreatePlay(m,p,input);
	    				
	    				once = true;
	    			}else{
	    				// Actualizar posicion actual
	    				p << input;
	    				fm.showSection(input,m,p,false);

	    				if(fm.getMap(p.getX(0),p.getY(0)) == '5' || fm.getMap(p.getX(1),p.getY(1)) == 'b'){
	    					fm.setBeginPlay(false);
	    					fm.setShowResults(true);
	    				}
	    			}
					p >> input;
	    		}else if(fm.isCreateShowResults()){
	    			fm.loadSection(4); fm.showSection(input,m,p,false);
	    			fm.loadSection(6); fm.showSection(input,m,p,false);
	    		}else if(fm.isCreateShowPause()){
	    			fm.loadSection(4);
	    			fm.showSection(input,m,p,false);
	    			fm.loadSection(5);

					input.setUserKeyboard(0,true);
	    			
	    			//Player 1
	    			if(input.getX(0) >= 0 ) { input.setX(0, 0);}	    			
	    			if(input.getY(0) >= 3 ) { input.setY(0, 2);}

	    			fm.showSection(input,m,p,false);
	    		}else if(fm.isCreateSave()){
	    			//Player 1
	    			if(input.getX(0) >= 3 ) { input.setX(0, 2);}	    			
	    			if(input.getY(0) >= 1 ){ input.setY(0, 0);}
	    			fm.loadSection(4);
	    			bool a = fm.getLoadMapPlayer();
	    			fm.loadSection(1);
	    			fm.showSection(input,m,p,a);
	    			fm.drawButton();
	    		}
	    	}
		}
		//putBomb(events,s,input,p);
		if(fm.isCreateBeginPlay() && input.getUserKeyboard(0) && input.getUserKeyboard(1)){
	   		if(input.IsKeyPressed(events, ALLEGRO_KEY_T))
	   			p.putBomb(p.getX(0),p.getY(0),0);
	   		
	   		if(input.IsKeyPressed(events, ALLEGRO_KEY_P))
	   			p.putBomb(p.getX(1),p.getY(1),1);
	   	}

	    if(draw){
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
			draw = false;
		}

		//actionKeyboard(events,active1,active2,key_state,frame_timer,timer,input,p);
		if(events.type == ALLEGRO_EVENT_TIMER){
	
			if(events.timer.source == timer){
				active1 = true;
				active2 = true;
					 if(al_key_down(&key_state, ALLEGRO_KEY_S))	{
					 	input.incY(0); 
					 	if (input.getUserKeyboard(0) && input.getUserKeyboard(1))
					 		p.setDir(0, 0);
					 }
				else if(al_key_down(&key_state, ALLEGRO_KEY_D)) {
					input.incX(0); 
					if(input.getUserKeyboard(0) && input.getUserKeyboard(1))
						p.setDir(0, 3);
				}
				else if(al_key_down(&key_state, ALLEGRO_KEY_W)) {
					input.decY(0); 
					if(input.getUserKeyboard(0) && input.getUserKeyboard(1))
						p.setDir(0, 2);
				}
				else if(al_key_down(&key_state, ALLEGRO_KEY_A)) {
					input.decX(0); 
					if(input.getUserKeyboard(0) && input.getUserKeyboard(1))
						p.setDir(0, 1);
				}
				else active1 = false;

					 if(al_key_down(&key_state, ALLEGRO_KEY_DOWN))	{
					 	input.incY(1); 
					 	if(input.getUserKeyboard(0) && input.getUserKeyboard(1))
					 		p.setDir(1, 0);
					 }
				else if(al_key_down(&key_state, ALLEGRO_KEY_RIGHT)) {
					input.incX(1); 
					if(input.getUserKeyboard(0) && input.getUserKeyboard(1))
						p.setDir(1, 3);
				}
				else if(al_key_down(&key_state, ALLEGRO_KEY_UP)) 	{
					input.decY(1); 
					if(input.getUserKeyboard(0) && input.getUserKeyboard(1))
						p.setDir(1, 2);
				}
				else if(al_key_down(&key_state, ALLEGRO_KEY_LEFT)) 	{
					input.decX(1); 
					if(input.getUserKeyboard(0) && input.getUserKeyboard(1))
						p.setDir(1, 1);
				}
				else active2 = false;				
			
			} else if (events.timer.source == frame_timer && input.getUserKeyboard(0) && input.getUserKeyboard(1)){
			    //Graficos de Movimiento de player 1
			    if(active1) p.incSource(0);
			    else   	    p.setSource(0,-4);

			    if(p.getSource(0) >= 224) p.setSource(0,-4);

			    //Graficos de Movimiento de player 2
			    if(active2) p.incSource(1);
			    else    	p.setSource(1,-4);

			    if(p.getSource(1) >= 224) p.setSource(1,-4);
	    	}
		}
	}
	//Destroys all libraries
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_timer(frame_timer);
	al_destroy_event_queue(event_queue);
	al_destroy_sample(sound);
	al_destroy_sample(select);
	al_destroy_sample(enter);
	return 0;
}