#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int screen_x = 400;
const int screen_y = 400;
const int screen_bpp = 32;
const int frames_per_second = 20;
const int piecenum = 32;

const string caption = "<<==--_CHESS_--==>>";

SDL_Surface* screen = NULL;
SDL_Event event;

bool quit = false;

#include "image.h"

position GetClosestSquare(int xcor, int ycor);

int main(int argc, char* args[]) {
  startup();
  Timer fps;

  animate *aniptr;

  int mousex = 0, mousey = 0, movenum = 0;

  position mousepos;
  position rightmousepos;
  position mousepos_cur;

  control main_control;

  bool somethingselected = false, playeroneturn = true, pawnsel = false;

  queen.load_class_image("Resources\\queen_action.png",255,255,255);
  queen.Set_Everything(50,50,2);
  queen.teleport(50 * (4),50 * (7));
  king.load_class_image("Resources\\king_action.png",255,255,255);
  king.Set_Everything(50,50,2);
  king.teleport(50 * (3),50 * (7));

  for (int temp = 0; temp < 8; temp++) {
    pawn[temp].load_class_image("Resources\\bishop_action2.png",255,255,255);
    pawn[temp].Set_Everything(50,50,2);
    pawn[temp].teleport(50 * (temp),50 * (6));

    bpawn[temp].load_class_image("Resources\\b_bishop_action2.png",255,255,255);
    bpawn[temp].Set_Everything(50,50,2);
    bpawn[temp].teleport(50 * (temp),50 * (1));
  }

  knight.load_class_image("Resources\\knight_action.png",255,255,255);
  knight.Set_Everything(50,50,2);
  knight.teleport(50 * (1),50 * (7));
  knight_two.load_class_image("Resources\\knight_action.png",255,255,255);
  knight_two.Set_Everything(50,50,2);
  knight_two.teleport(50 * (6),50 * (7));
  bishop.load_class_image("Resources\\pawn_action.png",255,255,255);
  bishop.Set_Everything(50,50,2);
  bishop.teleport(50 * (2),50 * (7));
  bishop_two.load_class_image("Resources\\pawn_action.png",255,255,255);
  bishop_two.Set_Everything(50,50,2);
  bishop_two.teleport(50 * (5),50 * (7));
  castle.load_class_image("Resources\\castle_action2.png",255,255,255);
  castle.Set_Everything(50,50,4);
  castle.teleport(50 * (0),50 * (7));
  castle_two.load_class_image("Resources\\castle_action2.png",255,255,255);
  castle_two.Set_Everything(50,50,4);
  castle_two.teleport(50 * (7),50 * (7));

  bqueen.load_class_image("Resources\\b_queen_action.png",255,255,255);
  bqueen.Set_Everything(50,50,2);
  bqueen.teleport(50 * (4),50 * (0));

  bking.load_class_image("Resources\\b_king_action.png",255,255,255);
  bking.Set_Everything(50,50,2);
  bking.teleport(50 * (3),50 * (0));

  bknight.load_class_image("Resources\\b_knight_action.png",255,255,255);
  bknight.Set_Everything(50,50,2);
  bknight.teleport(50 * (1),50 * (0));

  bknight_two.load_class_image("Resources\\b_knight_action.png",255,255,255);
  bknight_two.Set_Everything(50,50,2);
  bknight_two.teleport(50 * (6),50 * (0));

  bbishop.load_class_image("Resources\\b_pawn_action.png",255,255,255);
  bbishop.Set_Everything(50,50,2);
  bbishop.teleport(50 * (2),50 * (0));

  bbishop_two.load_class_image("Resources\\b_pawn_action.png",255,255,255);
  bbishop_two.Set_Everything(50,50,2);
  bbishop_two.teleport(50 * (5),50 * (0));

  bcastle.load_class_image("Resources\\b_castle_action2.png",255,255,255);
  bcastle.Set_Everything(50,50,4);
  bcastle.teleport(50 * (0),50 * (0));

  bcastle_two.load_class_image("Resources\\b_castle_action2.png",255,255,255);
  bcastle_two.Set_Everything(50,50,4);
  bcastle_two.teleport(50 * (7),50 * (0));

  animate selected;
  selected.load_class_image("Resources\\selected3.png",255,255,255);
  selected.Set_Everything(50,50,2);
  selected.teleport(150,200);
  death x_thing;
  x_thing.load_class_image("Resources\\circle_thing.png",255,255,255);
  x_thing.Set_Everything(200,200,5);
  x_thing.teleport(150,200);

  animate piece_sel;
  piece_sel.load_class_image("Resources\\selected4.png",255,255,255,150);
  piece_sel.Set_Everything(50,50,4);
  animate valid_move;
  valid_move.load_class_image("Resources\\dots.png",255,255,255,169);
  valid_move.Set_Everything(50,50,4);

  sprite background("Resources\\checkerboard.png");

  main_control.activate_piece(queen,queen_g1);
  main_control.activate_piece(king,king_g1);
  main_control.activate_piece(bishop,bishop_g1);
  main_control.activate_piece(bishop_two,bishop_g2);
  main_control.activate_piece(knight,knight_g1);
  main_control.activate_piece(knight_two,knight_g2);
  main_control.activate_piece(castle,castle_g1);
  main_control.activate_piece(castle_two,castle_g2);
  for (int temp = 0; temp < 8; temp++) {
    main_control.activate_piece(pawn[temp],temp + 8);
  }

  main_control.activate_piece(bqueen,queen_b1);
  main_control.activate_piece(bking,king_b1);
  main_control.activate_piece(bbishop,bishop_b1);
  main_control.activate_piece(bbishop_two,bishop_b2);
  main_control.activate_piece(bknight,knight_b1);
  main_control.activate_piece(bknight_two,knight_b2);
  main_control.activate_piece(bcastle,castle_b1);
  main_control.activate_piece(bcastle_two,castle_b2);
  for (int temp = 0; temp < 8; temp++) {
    main_control.activate_piece(bpawn[temp],temp + 24);
  }

  main_control.set_good_VS_evil();

  int frame = 0;

  while (!quit) {
    fps.start();
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        quit = true;
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.x < screen_x && event.button.y < screen_y) {
          if (event.button.button == SDL_BUTTON_LEFT) {
            mousex = event.button.x;
            mousey = event.button.y;
            mousepos = GetClosestSquare(mousex,mousey);
            if (playeroneturn) {
              if (main_control.hero_here(mousepos)) {
                somethingselected = true;
                aniptr = main_control.get_active();
              } else {
                somethingselected = false;
              }
            } else { // second player's turn
              if (main_control.enemy_here(mousepos)) {
                somethingselected = true;
                aniptr = main_control.get_active();
              } else {
                somethingselected = false;
              }
            }
          }
          if (event.button.button == SDL_BUTTON_RIGHT) {

            if (somethingselected) {
              rightmousepos = GetClosestSquare(event.button.x,event.button.y);
              if (rightmousepos != (*aniptr).get_position() ) {


                if (playeroneturn && !main_control.hero_here(rightmousepos)) {
                  if ((*aniptr).valid_move(rightmousepos)) {
                    (*aniptr).teleport(rightmousepos);
                    (*aniptr).has_moved();
                    playeroneturn = !playeroneturn;
                    somethingselected = false;
                    if (main_control.enemy_here(rightmousepos)) {
                      main_control.kill(main_control.get_active());
                      x_thing.center_teleport((*main_control.get_active()).Ret_cent_pos());
                      x_thing.start_death();
                    }
                  }
                } else if (!playeroneturn && !main_control.enemy_here(rightmousepos)) {
                  if ((*aniptr).valid_move(rightmousepos)) {
                    (*aniptr).teleport(rightmousepos);
                    (*aniptr).has_moved();
                    playeroneturn = !playeroneturn;
                    somethingselected = false;
                    if (main_control.hero_here(rightmousepos)) {
                      main_control.kill(main_control.get_active());
                      x_thing.center_teleport((*main_control.get_active()).Ret_cent_pos());
                      x_thing.start_death();
                    }
                  }
                }
              }
            }
          }
        }
      }
      if (event.type == SDL_MOUSEMOTION) {
        if (event.button.x < screen_x && event.button.y < screen_y) {
          mousepos_cur = GetClosestSquare(event.button.x,event.button.y);
        }
      }
    }

    background.apply_image();
    selected.apply_image();
    x_thing.death_animate();

    if (frame % 4 == 0) {
      valid_move.inc_frame();
      main_control.inc_frames(); // animate all pieces
    }
    if (frame % 3 == 0) {
      selected.inc_frame();
      piece_sel.inc_frame();
    }

    if (somethingselected) {
      piece_sel.teleport((*aniptr).get_position());
      piece_sel.apply_image();
      main_control.apply_possible(&(*aniptr),&valid_move);
    }

    selected.teleport(mousepos_cur.x,mousepos_cur.y);
    main_control.apply_active();

    frame++;
    if (SDL_Flip(screen) == -1)
      return 3;

    if (fps.get_ticks() < 1000 / frames_per_second)          // Keep these together   ---
      SDL_Delay((1000 / frames_per_second) - fps.get_ticks()); // Keep these together   ---
  }

  SDL_Quit();
  return 0;
}

position GetClosestSquare(int xcor, int ycor) {
  position endpos;
  for (int temp = 1; temp < 9; temp++) {
    if (xcor - temp * 50 <= 0) {
      endpos.x = (temp - 1) * 50 ;
      break;
    }
  }

  for (int temp = 1; temp < 9; temp++) {
    if (ycor - temp * 50 <= 0) {
      endpos.y = (temp - 1) * 50;
      break;
    }
  }
  return endpos;
}
