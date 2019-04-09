#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define SCREEN_WIDTH 1509
#define SCREEN_HEIGHT 900

  /* Structure pour gérer le niveau (à compléter plus tard) */

typedef struct
  {


      SDL_Surface *background;
      //cordonnees background
      int x;
      int y;

  } Map;

 typedef struct
  {
     int x;
     int y;
     int w;
     int h;
  }AABB;

typedef struct 
  {


      SDL_Surface *image_ennemi;
      //cordonnees ennemi
      int x;
      int y;
      int h;
      int w;

     

  } Ennemi;

typedef struct 
  {


      SDL_Surface *image_objet;
      //cordonnees objet
      int x;
      int y;
      int h;
      int w;

     

  } Objet;

  void button_play(SDL_Surface *ecran);
  void button_option(SDL_Surface *ecran);
  void motion_play(SDL_Surface *ecran);
  void motion_option(SDL_Surface *ecran);
  void motion_exit(SDL_Surface *ecran);
  void son_bref( Mix_Chunk *son);
  void initiliser_background(Map map,int x,int y);
  void initiliser_objet(Objet objet,int x,int y);
  void initiliser_ennemi(Ennemi ennemi,int x,int y);
  void afficher_background(Map map,SDL_Surface *ecran);
  SDL_Color GetPixel(SDL_Surface *background_masque,int x,int y);
  int collision_background(SDL_Surface *background_masque,int collision,SDL_Rect posPerso);
  int collision_trigonometrique(SDL_Rect pos_objet,SDL_Rect pos_hero);
  int collision_inter_entite(AABB box1,AABB box2);
 

#endif // HEADER_H_INCLUDED
