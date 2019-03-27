#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>



void button_play(SDL_Surface *ecran)
{
         SDL_Surface   *sprite = NULL,*image_menu=NULL,*perso=NULL;
         SDL_Rect  position_menu, positionSprite,position_perso;
         SDL_Event event;
         position_menu.x=0;
         position_menu.y=0;
         positionSprite.x = 0; 
         positionSprite.y = 580;

         position_perso.x = 0; 
         position_perso.y = 0;

         SDL_Init(SDL_INIT_VIDEO);
        //SDL_WM_SetIcon(IMG_Load("sdl_icone.bmp"), NULL);
        SDL_ShowCursor(SDL_ENABLE);

        ecran = SDL_SetVideoMode(1509,905, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

        image_menu = SDL_LoadBMP("first_stage.bmp");
        sprite = SDL_LoadBMP("perso_droite.bmp");
        perso = SDL_LoadBMP("perso_gauche.bmp");
        SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 255, 255,255));
        SDL_SetColorKey(perso, SDL_SRCCOLORKEY, SDL_MapRGB(perso->format, 255, 255,255));
        int continuer=1;
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
                                         if(positionSprite.y>250)
                                             positionSprite.y-=10; 
                                             
                                        break; 

                                       case SDLK_DOWN: // Flèche bas 
                                         if((positionSprite.y+170)<800)
                                           positionSprite.y+=10; 
                                           break; 

                                       case SDLK_RIGHT: // Flèche droite 
                                          if((positionSprite.x+90)<1509)
                                         {
                                             positionSprite.x+=10;

                                             position_perso.x=positionSprite.x;
                                             position_perso.y=positionSprite.y;
                                             // SDL_FreeSurface(sprite);
                                             SDL_BlitSurface(perso, NULL, ecran, &position_perso);
                                             
                                             //SDL_FreeSurface(perso);
                                            // SDL_BlitSurface(sprite, NULL, ecran, &positionSprite);
                                             SDL_Flip(ecran);
                                         } 
                                           break; 

                                       case SDLK_LEFT: // Flèche gauche 
                                           positionSprite.x-=10; 
                                           break; 
                                      default: // on ne traite pas les autres événements 
                                              break; 
                                    } 
                           break; 
                       default: // on ne traite pas les autres événements 
                            break; 
                   }

             SDL_BlitSurface(image_menu, NULL, ecran, &position_menu);
             SDL_BlitSurface(sprite, NULL, ecran, &positionSprite);
             SDL_Flip(ecran);
          } 
       
        
       SDL_FreeSurface(image_menu);
       SDL_FreeSurface(sprite); 
      // SDL_Quit(); 
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

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *imageDeFond = NULL,*play=NULL,*setting=NULL,*exit=NULL;
    SDL_Rect positionFond,position_game,position_options,position_quit,position_click;
    SDL_Event event;
    SDL_Surface *ecran1 = NULL;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};


    positionFond.x = 0;
    positionFond.y = 0;
    position_game.x=180;
    position_game.y=100;
    position_options.x=180;
    position_options.y=200;
    position_quit.x=180;
    position_quit.y=300;


   int continuer =1;
   int valeur=-1;

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
    
    exit=TTF_RenderText_Blended(police, "QUIT", couleurNoire);
    

   if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }

   Mix_Music *music;
   music=Mix_LoadMUS("musique.mp3");
   Mix_PlayMusic(music,-1);

   Mix_Chunk *son;

 while (continuer)
    {
          
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_RIGHT) // On arrête le programme si on a fait un clic droit
                    continuer = 0;
                   // break;

          if(event.button.button == SDL_BUTTON_LEFT)
              {
                    position_click.x=event.button.x;
                    position_click.y=event.button.y;
               if(event.button.x>=position_game.x&&(event.button.x<=position_game.x+200)&&event.button.y>=position_game.y&&(event.button.y<=position_game.y+80))
                   {
                      button_play(ecran);

                   }

               if(event.button.x>=position_options.x&&(event.button.x<=position_options.x+200)&&event.button.y>=position_options.y&&(event.button.y<=position_options.y+80))
                   {
                       button_option(ecran);

                   }

               if(event.button.x>=position_quit.x&&(event.button.x<=position_quit.x+200)&&event.button.y>=position_quit.y&&(event.button.y<=position_quit.y+80))
                   {
                            continuer = 0;
                           // break;

                   }

             }

               break;
        case SDL_MOUSEMOTION:
                       position_click.x=event.motion.x;
                       position_click.y=event.motion.y;
                  if(event.motion.x>=position_game.x&&(event.motion.x<=position_game.x+200)&&event.motion.y>=position_game.y&&(event.motion.y<=position_game.y+80))
                   {
                       
                          motion_play(ecran);
                              
                          son_bref(son);
                   }

                if(event.motion.x>=position_options.x&&(event.motion.x<=position_options.x+200)&&event.motion.y>=position_options.y&&(event.motion.y<=position_options.y+80))
                   {
                          motion_option(ecran);
                            
                           son_bref(son);

                   }

                 if(event.motion.x>=position_quit.x&&(event.motion.x<=position_quit.x+200)&&event.motion.y>=position_quit.y&&(event.motion.y<=position_quit.y+80))
                   {

                          motion_exit(ecran);
                              
                          son_bref(son);
                   }
             break;
 
        }
         SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
          SDL_BlitSurface(play, NULL, ecran, &position_game);
          SDL_BlitSurface(setting, NULL, ecran, &position_options);
          SDL_BlitSurface(exit, NULL, ecran, &position_quit);
          SDL_Flip(ecran);

   }

   
    //pause();
 /* On libère la surface */
    SDL_FreeSurface(imageDeFond);
    TTF_CloseFont(police);
    TTF_Quit();

    Mix_CloseAudio();
    Mix_FreeMusic(music);
    Mix_FreeChunk(son);

    SDL_Quit();

    return EXIT_SUCCESS;
}

