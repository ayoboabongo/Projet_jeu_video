#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "header.h"
#include "math.h"
#include "time.h"

 void initiliser_hero(Hero hero,int x,int y)
{
  hero.x=x;
  hero.y=y;
  hero.pos_vie[0].x=0;
  hero.pos_vie[0].y=30;
  hero.pos_vie[1].x=0;
  hero.pos_vie[1].y=60;
  hero.pos_vie[2].x=0;
  hero.pos_vie[2].y=90;
  hero.pos_temps.x=20;
  hero.pos_temps.y=0;
  hero.pos_score.x=40;
  hero.pos_score.y=0;
  hero.image_hero= SDL_LoadBMP("hero.bmp");
  hero.vie[0]=SDL_LoadBMP("vie.bmp");
  hero.vie[1]=SDL_LoadBMP("vie.bmp");
  hero.vie[2]=SDL_LoadBMP("vie.bmp");
}
void afficher_heroi(Hero hero,SDL_Surface *ecran)
{
    initiliser_hero(hero,0,650);

    SDL_Rect  pos_hero;

    pos_hero.x=hero.x;
    pos_hero.y=hero.y;

   // ecran = SDL_SetVideoMode(1509,905, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    hero.image_hero= SDL_LoadBMP("hero.bmp");
    hero.vie[0]=SDL_LoadBMP("vie.bmp");
    hero.vie[1]=SDL_LoadBMP("vie.bmp");
    hero.vie[2]=SDL_LoadBMP("vie.bmp");
  
        SDL_SetColorKey(hero.image_hero, SDL_SRCCOLORKEY, SDL_MapRGB(hero.image_hero->format, 255, 255,255));
        SDL_SetColorKey(hero.vie[0], SDL_SRCCOLORKEY, SDL_MapRGB(hero.vie[0]->format, 255, 255,255));
        SDL_SetColorKey(hero.vie[1], SDL_SRCCOLORKEY, SDL_MapRGB(hero.vie[1]->format, 255, 255,255));
        SDL_SetColorKey(hero.vie[2], SDL_SRCCOLORKEY, SDL_MapRGB(hero.vie[2]->format, 255, 255,255));

    SDL_BlitSurface(hero.image_hero, NULL, ecran, &pos_hero);
    SDL_BlitSurface(hero.vie[0], NULL, ecran, &hero.pos_vie[0]);
    SDL_BlitSurface(hero.vie[1], NULL, ecran, &hero.pos_vie[1]);
    SDL_BlitSurface(hero.vie[2], NULL, ecran, &hero.pos_vie[2]);
    SDL_BlitSurface(hero.score, NULL, ecran, &hero.pos_score);
    SDL_BlitSurface(hero.score, NULL, ecran, &hero.pos_temps);
    SDL_Flip(ecran);

  
}

 void initiliser_objet(Objet objet,int x,int y)
{
  objet.x=x;
  objet.y=y;
  objet.image_objet= SDL_LoadBMP("coin.bmp");
}


  void initiliser_ennemi(Ennemi ennemi,int x,int y)
{
  ennemi.x=x;
  ennemi.y=y;
  ennemi.image_ennemi= SDL_LoadBMP("coin.bmp");
}

void afficher_ennemi(Ennemi ennemi,SDL_Surface *ecran)
{
    initiliser_ennemi(ennemi,450,650);

    SDL_Rect  pos_ennemi;

    pos_ennemi.x=ennemi.x;
    pos_ennemi.y=ennemi.y;

   // ecran = SDL_SetVideoMode(1509,905, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    ennemi.image_ennemi= SDL_LoadBMP("coin.bmp");
    SDL_BlitSurface(ennemi.image_ennemi, NULL, ecran, &pos_ennemi);
    SDL_Flip(ecran);
  
}


void initiliser_background(Map map,int x,int y)
{
  map.x=x;
  map.y=y;
  map.background= SDL_LoadBMP("first_stage.bmp");
}


void afficher_background(Map map,SDL_Surface *ecran)
{
    initiliser_background(map,0,0);

    SDL_Rect  position_background;
    position_background.x=map.x;
    position_background.y=map.y;

    //ecran = SDL_SetVideoMode(1509,905, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    map.background= SDL_LoadBMP("first_stage.bmp");
    SDL_BlitSurface(map.background, NULL, ecran, &position_background);
    SDL_Flip(ecran);

}

 void cleanup()
   {
       Map map;
     /* Libère l'image du background */

      if (map.background != NULL)
      {
            SDL_FreeSurface(map.background);
      }

  }


int collision_trigonometrique(SDL_Rect pos_objet,SDL_Rect pos_hero)
{
	int collision=0;
	//coordonnées hero
	double x,y,w,h;
	x=pos_hero.x;
	y=pos_hero.y;
	w=pos_hero.w;
	h=pos_hero.h;
	double x1,y1,R1;
	x1=x+w/2;
	y1=y+h/2;
	R1=sqrt(((w/2)*(w/2))+((h/2)*(h/2)));

	/*if(w<h)
		R1=w/2;
	else
		R1=h/2;*/

	//coordonnées objet
	double X,Y,W,H;
	X=pos_objet.x;
	Y=pos_objet.y;
	W=pos_objet.w;
	H=pos_objet.h;

	double x2,y2,R2;
	x2=X+W/2;
	y2=Y+H/2;
	R2=sqrt(((W/2)*(W/2))+((H/2)*(H/2)));

	double D1,D2;
	D1=sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
	D2=R1+R2;
	if(D1<=D2)
		collision=1;
	else
		collision=0;

	return collision;

}


int collision_inter_entite(Hero hero,Ennemi ennemi)
{
	int collision;
       if((ennemi.x >= hero.x + hero.w)      // trop à droite
       || (ennemi.x + ennemi.w <= hero.x) // trop à gauche
	   || (ennemi.y >= hero.y + hero.h) // trop en bas
	   || (ennemi.y + ennemi.h <= hero.y))  // trop en haut
          collision=0; 
   else
          collision=1; 

      return collision;

}

SDL_Color GetPixel(SDL_Surface *background_masque,int x,int y)
{
      SDL_Color color;
      Uint32 col=0;
      //Determine position
      char* pPosition=(char* ) background_masque->pixels;
      pPosition+= (background_masque->pitch * y);
      pPosition+= (background_masque->format->BytesPerPixel *x);
      memcpy(&col ,pPosition ,background_masque->format->BytesPerPixel);
      //convertir color
      SDL_GetRGB(col,background_masque->format, &color.r, &color.g, &color.b);

return (color);

}


int collision_background(SDL_Surface *background_masque,int collision,SDL_Rect posPerso)
{
      SDL_Color couleur_obstacle;
      float x[8];
      float y[8];
      int i;
      int X,Y,H,W;
      X=posPerso.x;
      Y=posPerso.y;

      W=posPerso.w;
      H=posPerso.h;

      x[0]=X;          y[0]=Y;
      x[1]=X+W/2;      y[1]=Y;
      x[2]=X+W;        y[2]=Y;
      x[3]=X;          y[3]=Y+H/2;
      x[4]=X;          y[4]=Y+H;
      x[5]=X+W/2;      y[5]=Y+H;
      x[6]=X+W;        y[6]=Y+H;
      x[7]=X+W;        y[7]=Y+H/2;
    collision=0;
	for(i=0;i<8&&collision==0;i++)
       {
	       couleur_obstacle=GetPixel(background_masque,x[i],y[i]);
	        if(couleur_obstacle.r==0&&couleur_obstacle.g==0&&couleur_obstacle.b==0)
                       collision=1;     
 
       }

      return collision;
}

 

void gestion_vie_score(Hero hero,SDL_Surface *ecran)
{
    Ennemi ennemi;
    SDL_Rect pos_objet;
    SDL_Rect pos_hero;
    Objet objet;
    SDL_Event event; 
    TTF_Init();
    TTF_Font *police = NULL; 
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255}; 
    int continuer = 1; 
    int tempsActuel = 0, tempsPrecedent = 0, compteur,compteur_min,score_;
    compteur=59;
    compteur_min=4; 
    score_=0;
    char temps[50]; /* Tableau de char suffisamment grand */
    char score_joueur[50];


         SDL_Init(SDL_INIT_VIDEO); 
         ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); 
         SDL_WM_SetCaption("Gestion du texte avec SDL_ttf", NULL);
         /* Chargement de la police */ 
         police = TTF_OpenFont("HeartyScript.ttf", 65); 
         /* Initialisation du temps et du texte */ 
        /* tempsActuel = SDL_GetTicks(); 
         sprintf(temps, "Temps : %d s", compteur / 1000);*/
         //texte = TTF_RenderText_Shaded(police, temps, couleurNoire,couleurBlanche); 
        /* texte = TTF_RenderText_Blended(police,temps, couleurNoire);
         score=TTF_RenderText_Blended(police,score_joueur,couleurNoire);*/
    
                 while ( continuer )
                   { 

                        SDL_PollEvent(&event);
                             switch ( event.type ) 
                                 { 

                                      case SDL_QUIT: 
                                          continuer = 0;
                                           break; 
                                 }

                         SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                         tempsActuel = SDL_GetTicks(); 
                          /* Si 100 ms au moins se sont écoulées */ 
                         if ( tempsActuel - tempsPrecedent == 1000 ) 
                               {
      
                                  compteur -= 1; /* On rajoute 100 ms au compteur */ 
                                  if(compteur==0)
                                     {
                                         compteur_min-=1;
                                         compteur=59;
                                           if(compteur_min==0&&compteur==0)
                                                   continuer=0;
                                     } 
                                  sprintf(temps, "Temps : %d :%d",compteur_min, compteur); 
                                  sprintf(score_joueur,"Score : %d",score_);
                                  SDL_FreeSurface(hero.temps); /* On supprime la surface précédente */ 
                                  /* On écrit la chaîne temps dans la SDL_Surface */ 
                                  //texte = TTF_RenderText_Shaded( police, temps, couleurNoire,couleurBlanche);
                                  SDL_FreeSurface(hero.score);
                                  hero.temps =  TTF_RenderText_Shaded(police,temps,couleurNoire,couleurBlanche);
                                  hero.score =  TTF_RenderText_Shaded(police,score_joueur,couleurNoire,couleurBlanche);
                                  tempsPrecedent = tempsActuel; /* On met à jour le tempsPrecedent */ 

                              } 
                          if(collision_trigonometrique(pos_objet,pos_hero)==1)
                                        score_=score_ + 10;


                          if(collision_inter_entite(hero,ennemi)==1)
                           {

                                 if(hero.vie[0]!=NULL&&hero.vie[1]!=NULL&&hero.vie[2]!=NULL)
                                       SDL_FreeSurface(hero.vie[2]);
           
                                 if(hero.vie[0]!=NULL&&hero.vie[1]!=NULL&&hero.vie[2]==NULL)
                                       SDL_FreeSurface(hero.vie[1]);

                                 if(hero.vie[0]!=NULL&&hero.vie[1]==NULL&&hero.vie[2]==NULL)
                                     {
                                       SDL_FreeSurface(hero.vie[0]);
                                       continuer=0;

                                     }
                           }
                          SDL_BlitSurface(hero.temps, NULL, ecran, &hero.pos_temps); /* Blit du texte */ 
                          SDL_BlitSurface(hero.score, NULL, ecran, &hero.pos_score); 
                          SDL_Flip(ecran); 
                      
                     }
        SDL_FreeSurface(hero.temps); 
        SDL_FreeSurface(hero.score);
       

        TTF_CloseFont(police); 
        TTF_Quit();
        
     SDL_Quit();
      
} 


void button_play(SDL_Surface *ecran)
{
         Map map;
         Hero hero;
         Ennemi ennemi; 
         SDL_Surface   *sprite = NULL,*image_menu=NULL,*perso=NULL,*vie1=NULL,*vie2=NULL,*vie3=NULL,*objet=NULL,*background_masque=NULL;
         SDL_Rect  position_menu, positionSprite,position_perso,position_vie1,position_vie2,position_vie3,position_objet,pos_masque;
         SDL_Event event;
        /* TTF_Font *police = NULL;
         SDL_Color couleurNoire = {0,0,0};
         TTF_Init();
         police = TTF_OpenFont("angelina.ttf",22);*/
         position_menu.x=0;
         position_menu.y=0;
         pos_masque.x=0;
         pos_masque.y=0;
         positionSprite.x = 0; 
         positionSprite.y = 580;

         position_perso.x = 0; 
         position_perso.y = 0;
         /*position_vie.x=2;
         position_vie.y=0;*/
         position_vie1.x=30;
         position_vie1.y=0;
         position_vie2.x=60;
         position_vie2.y=0;
         position_vie3.x=90;
         position_vie3.y=0;
         position_objet.x=600;
         position_objet.y=600;

         SDL_Init(SDL_INIT_VIDEO);
        //SDL_WM_SetIcon(IMG_Load("sdl_icone.bmp"), NULL);
        SDL_ShowCursor(SDL_ENABLE);

        ecran = SDL_SetVideoMode(1509,905, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
        
        background_masque=SDL_LoadBMP("background_masque.bmp");
        image_menu = SDL_LoadBMP("background.bmp");
        sprite = SDL_LoadBMP("hero.bmp");
        perso = SDL_LoadBMP("perso_gauche.bmp");
        objet=SDL_LoadBMP("coin.bmp");
        SDL_SetColorKey(objet, SDL_SRCCOLORKEY, SDL_MapRGB(objet->format, 255, 255,255));
       // vie=TTF_RenderText_Blended(police, "vie:", couleurNoire);
        vie1=SDL_LoadBMP("vie1.bmp");
        vie2=SDL_LoadBMP("vie2.bmp");
        vie3=SDL_LoadBMP("vie3.bmp");
        SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 255,255));
        SDL_SetColorKey(perso, SDL_SRCCOLORKEY, SDL_MapRGB(perso->format, 255, 255,255));
        SDL_SetColorKey(vie1, SDL_SRCCOLORKEY, SDL_MapRGB(vie1->format, 255, 255,255));
        SDL_SetColorKey(vie2, SDL_SRCCOLORKEY, SDL_MapRGB(vie2->format, 255, 255,255));
        SDL_SetColorKey(vie3, SDL_SRCCOLORKEY, SDL_MapRGB(vie3->format, 255, 255,255));
        
        int continuer=1;
        int collision,col_trigo,col_inter;
         while(continuer)
          {
             SDL_WaitEvent(&event);
             /* traitement événements */ 
               switch ( event.type )
                   {
                       case SDL_QUIT: 
                           continuer = 0; 
                           break; 
                       case SDL_KEYDOWN: 
                             switch ( event.key.keysym.sym )
                                   { 
                                       case SDLK_UP: // Flèche haut
                                         //if(positionSprite.y>250)
                                   if((collision_background(background_masque,collision,positionSprite)==0)&&(collision_inter_entite(hero,ennemi)==0)&&(collision_trigonometrique( position_objet, positionSprite)==0))
                                             positionSprite.y-=10; 
                                             
                                        break; 

                                       case SDLK_DOWN: // Flèche bas 
                                        // if((positionSprite.y+170)<800)
                                  if((collision_background(background_masque,collision,positionSprite)==0)&&(collision_inter_entite(hero,ennemi)==0)&&(collision_trigonometrique( position_objet,positionSprite)==0))
                                           positionSprite.y+=10; 
                                           break; 

                                       case SDLK_RIGHT: // Flèche droite 
                                         // if((positionSprite.x+90)<1509)
                                  if((collision_background(background_masque,collision,positionSprite)==0)&&(collision_inter_entite(hero,ennemi)==0)&&(collision_trigonometrique( position_objet, positionSprite)==0))
                                             positionSprite.x+=10; 
                                        
                                           break; 

                                       case SDLK_LEFT: // Flèche gauche 
                                if((collision_background(background_masque,collision,positionSprite)==0)&&(collision_inter_entite(hero,ennemi)==0)&&(collision_trigonometrique( position_objet, positionSprite)==0))
                                           positionSprite.x-=10; 
                                           break; 
                                       
                                    } 
                           break; 
                  //col_trigo=collision_trigonometrique(position_objet,positionSprite);
                 // col_inter=collision_inter_entite(s,position)      
                   }
             //afficher_background(map,ecran)
             SDL_BlitSurface(background_masque,NULL,ecran,&pos_masque);
             SDL_BlitSurface(image_menu, NULL, ecran, &position_menu);
             SDL_BlitSurface(sprite, NULL, ecran, &positionSprite);
             //SDL_BlitSurface(vie, NULL, ecran, &position_vie);
             SDL_BlitSurface(vie1, NULL, ecran, &position_vie1);
             SDL_BlitSurface(vie2, NULL, ecran, &position_vie2);
             SDL_BlitSurface(vie3, NULL, ecran, &position_vie3);
             SDL_BlitSurface(objet, NULL, ecran, &position_objet);
             SDL_Flip(ecran);
             /* if((positionSprite.x+90)==position_objet.x||((positionSprite.x+90)==position_objet.y))
                                              SDL_FreeSurface(vie3);*/
          } 

       SDL_FreeSurface(background_masque);
       SDL_FreeSurface(image_menu);
       SDL_FreeSurface(sprite);
       SDL_FreeSurface(vie1);
       SDL_FreeSurface(vie2);
       SDL_FreeSurface(vie3);
       SDL_FreeSurface(objet);
        
       /*TTF_CloseFont(police);
       TTF_Quit();*/

       SDL_Quit(); 
}

void button_option(SDL_Surface *ecran)
{
        SDL_Surface  *image_option=NULL;
        SDL_Rect  position_s_option;

         position_s_option.x=0;
         position_s_option.y=0;

         SDL_Init(SDL_INIT_VIDEO);
        //SDL_WM_SetIcon(IMG_Load("sdl_icone.bmp"), NULL);
         SDL_ShowCursor(SDL_ENABLE);

         ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

         image_option = SDL_LoadBMP("S_option.bmp");
         int continuer=1;
          while(continuer)
            {

              SDL_BlitSurface(image_option, NULL, ecran, &position_s_option);
              SDL_Flip(ecran);

            }

         SDL_FreeSurface(image_option);

}

void motion_play(SDL_Surface *ecran)
{
    SDL_Surface  *imageDeFond = NULL,*play=NULL,*setting=NULL,*exit=NULL;
    SDL_Rect positionFond,position_game,position_options,position_quit,position_click;
    SDL_Event event;
    SDL_Surface *ecran1 = NULL;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurBlanche={255,255,255};


    positionFond.x = 0;
    positionFond.y = 0;
    position_game.x=180;
    position_game.y=100;
    position_options.x=180;
    position_options.y=200;
    position_quit.x=180;
    position_quit.y=300;


   int continuer =1;

    SDL_Init(SDL_INIT_VIDEO);
     TTF_Init();
    //SDL_WM_SetIcon(IMG_Load("sdl_icone.bmp"), NULL);
     SDL_ShowCursor(SDL_ENABLE);

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);

    police = TTF_OpenFont("HeartyScript.ttf", 65);

    /* Chargement d'une image Bitmap dans une surface */
    imageDeFond = SDL_LoadBMP("foret.bmp");
    /* On blitte par-dessus l'écran */
   
    play=TTF_RenderText_Blended(police, "PLAY", couleurBlanche);
    
    setting=TTF_RenderText_Blended(police, "OPTION",couleurNoire);
    
    exit=TTF_RenderText_Blended(police, "QUIT",  couleurNoire);
   
          SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
          SDL_BlitSurface(play, NULL, ecran, &position_game);
          SDL_BlitSurface(setting, NULL, ecran, &position_options);
          SDL_BlitSurface(exit, NULL, ecran, &position_quit);
          SDL_Flip(ecran);
          
}

void motion_option(SDL_Surface *ecran)
{
    SDL_Surface  *imageDeFond = NULL,*play=NULL,*setting=NULL,*exit=NULL;
    SDL_Rect positionFond,position_game,position_options,position_quit,position_click;
    SDL_Event event;
    SDL_Surface *ecran1 = NULL;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurBlanche={255,255,255};


    positionFond.x = 0;
    positionFond.y = 0;
    position_game.x=180;
    position_game.y=100;
    position_options.x=180;
    position_options.y=200;
    position_quit.x=180;
    position_quit.y=300;


   int continuer =1;

    SDL_Init(SDL_INIT_VIDEO);
     TTF_Init();
    //SDL_WM_SetIcon(IMG_Load("sdl_icone.bmp"), NULL);
     SDL_ShowCursor(SDL_ENABLE);

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);

    police = TTF_OpenFont("HeartyScript.ttf", 65);

    /* Chargement d'une image Bitmap dans une surface */
    imageDeFond = SDL_LoadBMP("foret.bmp");
    /* On blitte par-dessus l'écran */
   
    play=TTF_RenderText_Blended(police, "PLAY", couleurNoire);
    
    setting=TTF_RenderText_Blended(police, "OPTION",couleurBlanche);
    
    exit=TTF_RenderText_Blended(police, "QUIT",  couleurNoire);
   
          SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
          SDL_BlitSurface(play, NULL, ecran, &position_game);
          SDL_BlitSurface(setting, NULL, ecran, &position_options);
          SDL_BlitSurface(exit, NULL, ecran, &position_quit);
          SDL_Flip(ecran);
          
  
}

void motion_exit(SDL_Surface *ecran)
{
    SDL_Surface  *imageDeFond = NULL,*play=NULL,*setting=NULL,*exit=NULL;
    SDL_Rect positionFond,position_game,position_options,position_quit,position_click;
    SDL_Event event;
    SDL_Surface *ecran1 = NULL;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurBlanche={255,255,255};


    positionFond.x = 0;
    positionFond.y = 0;
    position_game.x=180;
    position_game.y=100;
    position_options.x=180;
    position_options.y=200;
    position_quit.x=180;
    position_quit.y=300;


   int continuer =1;

    SDL_Init(SDL_INIT_VIDEO);
     TTF_Init();
    //SDL_WM_SetIcon(IMG_Load("sdl_icone.bmp"), NULL);
     SDL_ShowCursor(SDL_ENABLE);

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);

    police = TTF_OpenFont("HeartyScript.ttf", 65);

    /* Chargement d'une image Bitmap dans une surface */
    imageDeFond = SDL_LoadBMP("foret.bmp");
    /* On blitte par-dessus l'écran */
   
    play=TTF_RenderText_Blended(police, "PLAY", couleurNoire);
    
    setting=TTF_RenderText_Blended(police, "OPTION", couleurNoire);
    
    exit=TTF_RenderText_Blended(police, "QUIT", couleurBlanche);
   

          SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
          SDL_BlitSurface(play, NULL, ecran, &position_game);
          SDL_BlitSurface(setting, NULL, ecran, &position_options);
          SDL_BlitSurface(exit, NULL, ecran, &position_quit);
          SDL_Flip(ecran);
          
}


void son_bref( Mix_Chunk *son)
{

   if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
    
   Mix_AllocateChannels(3); //Allouer 3 canaux
   Mix_Volume(1, MIX_MAX_VOLUME); //Mettre à mi-volume le post 1
   //Mix_Chunk *son;//Créer un pointeur pour stocker un .WAV
   son = Mix_LoadWAV("son_bref.wav"); //Charger un wav dans un pointeur
   Mix_VolumeChunk(son, MIX_MAX_VOLUME); //Mettre un volume pour ce wav
   Mix_PlayChannel(1, son, 0);//Joue le son 1 sur le canal 1 ; le joue une fois (0 + 1)
}


