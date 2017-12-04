#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED


class control;

enum class_enum {
  castle_g1, knight_g1, bishop_g1, king_g1, queen_g1,bishop_g2, knight_g2, castle_g2,pawn_g1,pawn_g2,pawn_g3,pawn_g4,pawn_g5,pawn_g6,pawn_g7,pawn_g8,
  castle_b1, knight_b1, bishop_b1, king_b1, queen_b1,bishop_b2, knight_b2, castle_b2,pawn_b1,pawn_b2,pawn_b3,pawn_b4,pawn_b5,pawn_b6,pawn_b7,pawn_b8
};

struct position {
  int x;
  int y;
  position() {
    x = y = 0;
  }
  bool operator ==(position psn);
  bool operator !=(position psn);
};

bool position::operator== (position psn) {
  if (x == psn.x && y == psn.y)
    return true;
  return false;
}
bool position::operator!= (position psn) {
  if (x != psn.x || y != psn.y)
    return true;
  return false;
}
position return_pos(int x, int y) {
  position temporary;
  temporary.x = x;
  temporary.y = y;
  return temporary;
}
int rand_range(int lower, int upper) {
  int difference = upper - lower + 1;
  return ((rand() % difference) + lower);
}

void app_image(SDL_Surface* image, SDL_Surface* canvas, SDL_Rect rect) {
  SDL_BlitSurface(image, NULL, canvas, &rect);
}

void app_image(SDL_Surface* image, SDL_Rect Clip , SDL_Surface* canvas, SDL_Rect rect) {
  SDL_BlitSurface(image, &Clip, canvas, &rect);
}

void app_image(int x, int y, SDL_Surface* image, SDL_Surface* canvas) {
  SDL_Rect tempr;
  tempr.x = x;
  tempr.y = y;
  SDL_BlitSurface(image, NULL, canvas, &tempr);
}

void app_image(int x, int y, SDL_Rect Clip, SDL_Surface* image, SDL_Surface* canvas) {
  SDL_Rect tempr;
  tempr.x = x;
  tempr.y = y;
  SDL_BlitSurface(image, &Clip, canvas, &tempr);
}
/*SDL_Surface *load_image(std::string filename) {
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;
  loadedImage = IMG_Load(filename.c_str());
  if (loadedImage != NULL) {
    optimizedImage = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);
  }
  return optimizedImage;
}*/
SDL_Surface *load_image(std::string filename,int r = 0,int g = 0, int b = 0) {
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;
  loadedImage = IMG_Load(filename.c_str());
  if (loadedImage != NULL) {
    optimizedImage = SDL_DisplayFormat(loadedImage);
    if (optimizedImage != NULL) {
      Uint32 colorkey = SDL_MapRGB(optimizedImage->format,r,g,b);
      SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
    }
    SDL_FreeSurface(loadedImage);
  }
  return optimizedImage;
}
SDL_Surface *load_image(std::string filename,int r,int g, int b, int a) {
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;
  loadedImage = IMG_Load(filename.c_str());
  if (loadedImage != NULL) {
    optimizedImage = SDL_DisplayFormat(loadedImage);
    if (optimizedImage != NULL) {
      Uint32 colorkey = SDL_MapRGB(optimizedImage->format,r,g,b);
      SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
      SDL_SetAlpha(optimizedImage, SDL_SRCALPHA, a);
    }
    SDL_FreeSurface(loadedImage);
  }
  return optimizedImage;
}

int startup() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    return 1;
  screen = SDL_SetVideoMode(screen_x, screen_y, screen_bpp, SDL_SWSURFACE|SDL_DOUBLEBUF);
  if (screen == NULL)
    return 1;
  SDL_WM_SetCaption(caption.c_str(), NULL);
}

class sprite {
protected:
  int x,y;
  SDL_Rect offset;
  SDL_Surface* image;
  int xnum, ynum;
  bool active;
public:
  sprite(string image_path,int r,int g,int b,int a) {
    image = load_image(image_path,r,g,b,a);
    x = y = ynum = xnum = 0;
    active = false;
    offset.x = offset.y = offset.h = offset.w = 0;
  }
  sprite(string image_path,int r,int g,int b) {
    image = load_image(image_path,r,g,b);
    x = y = ynum = xnum = 0;
    active = false;
    offset.x = offset.y = offset.h = offset.w = 0;
  }
  sprite(string image_path) {
    image = load_image(image_path);
    x = y = ynum = xnum = 0;
    active = false;
    offset.x = offset.y = offset.h = offset.w = 0;
  }
  sprite() {
    x = y =ynum = xnum = 0;
    active = false;
    offset.x = offset.y = offset.h = offset.w = 0;
  }
  ~sprite() {
    SDL_FreeSurface(image);
  }
  void load_class_image(string image_path) {
    image = load_image(image_path);
  }
  void load_class_image(string image_path,int r, int g, int b) {
    image = load_image(image_path, r, g, b);
  }
  void load_class_image(string image_path,int r, int g, int b, int a) {
    image = load_image(image_path,r,g,b,a);
  }

  void update_off() {
    offset.x = x;
    offset.y = y;
    active = true;
  }
  void teleport(int tx, int ty) {
    x = tx;
    y = ty;
    update_off();
    active = true;
  }
  void teleport(position temp) {
    x = temp.x;
    y = temp.y;
    update_off();
    active = true;
  }
  virtual void apply_image() {
    app_image(image,screen,offset);
    active = true;
  }
  virtual void apply_image(position thepos) {
    SDL_Rect trect;
    trect.x = thepos.x;
    trect.y = thepos.y;
    app_image(image,screen,trect);
  }
  void deactivate() {
    active = false;
  }
  bool get_active() {
    return active;
  }
  position get_position() {
    position temp;
    temp.x = x;
    temp.y = y;
    return temp;
  }

};


class animate: public sprite {
protected:
  int f_n; //frame number
  int f_w; //frame width
  int f_h; //frame height
  int animateframe;
  int enumnumber;
  SDL_Rect *rctptr;
  control *main_control;
  bool firstmove;
  bool good;
public:
  void set_enum_number(int enumnum) {
    enumnumber = enumnum;
  }
  void set_good(bool yesgood){
   good = yesgood;
  }
  bool is_good(){ return good;}
  int get_enum_number() {
    return enumnumber;
  }
  void set_control(control *temp) {
    main_control = temp;
  }
  void  Set_Width(int pixels) {
    f_w = pixels;
  }
  void Set_Height(int pixels) {
    f_h = pixels;
  }
  void  Set_Number(int frames) {
    f_n = frames;
    rctptr = new SDL_Rect[frames]; //array of sdl_rects
  }
  int Ret_sx() {
    return f_w;
  }
  int Ret_sy() {
    return f_h;
  }
  position Ret_cent_pos(){
   return return_pos(x + f_w / 2, y + f_h / 2);
  }
  void Set_Rects() {
    for (int temp = 0; temp < f_n ;temp++) {
      rctptr[temp].w = f_w;
      rctptr[temp].h = f_h;
      rctptr[temp].x = temp*f_w; // number * width because sprite sheet is horiz, set to h if ver
      rctptr[temp].y = 0;
    }
  }
  void Set_Everything(int width, int height, int frame_number) {
    Set_Number(f_w = width);
    Set_Number(f_h = height);
    Set_Number(frame_number);
    Set_Rects();
  }
  void apply_image() {
    app_image(image,rctptr[animateframe % f_n],screen,offset);
    active = true;
  }
  void apply_image(position thepos) {
    SDL_Rect trect;
    trect.x = thepos.x;
    trect.y = thepos.y;
    app_image(image,rctptr[animateframe % f_n],screen,trect);
  }

  void inc_frame() {
    if (animateframe > 10000)
      animateframe = 0;

    animateframe++;
  }

  void dec_frame() {
    if (animateframe > 1)
      animateframe--;
    else {
      animateframe = 10000;
    }
  }

  void jmp_frame(int temp) { //NO EXCEPTION HANDLING!! BE CAREFUL
    animateframe = temp;
  }
  void End_This() {
    SDL_FreeSurface(image);
    image = NULL;
  }
  void hasnot_moved() {
    firstmove = true;
  }
  void has_moved() {
    firstmove = false;
  }
  virtual bool valid_move(position pos) {return false;}

};

class control {
protected:
  animate *allofthem[piecenum];
  bool whichactive[piecenum];
  animate *activepiece;
public:

  control() {
    for (int temp = 0; temp < piecenum; temp++) {
      whichactive[temp] = false;
    }
  }
  void activate_piece(animate &piece,int piece_enum_num) {
    allofthem[piece_enum_num] = &piece;
    piece.set_control(this);
    whichactive[piece_enum_num] = true;
    piece.set_enum_number(piece_enum_num);
    piece.hasnot_moved();
  }

  void kill(int piece_number) {
    whichactive [piece_number] = false;

  }
  void kill(animate* piece) {
    kill((*piece).get_enum_number());
  }
  void kill(position map_pos) {
    for (int temp = 0; temp < piecenum; temp++) {
      if (whichactive[temp]) {
        if ((*allofthem[temp]).get_position() == map_pos)
          kill(temp);
      }
    }
  }
  bool enemy_here(position thispos) {
    for (int temp = piecenum / 2; temp < piecenum; temp++) {
      if (whichactive[temp]) {
        if ((*allofthem[temp]).get_position() == thispos) {
          activepiece = allofthem[temp];
          return true;

        }
      }
    }
    return false;
  }
  bool enemy_here(position thispos, bool nochange) {
    for (int temp = piecenum / 2; temp < piecenum; temp++) {
      if (whichactive[temp]) {
        if ((*allofthem[temp]).get_position() == thispos) {
          if (!nochange){
          activepiece = allofthem[temp];
          }
          return true;

        }
      }
    }
    return false;
  }

  bool hero_here(position thispos) {
    for (int temp = 0; temp < piecenum / 2; temp++) {
      if (whichactive[temp]) {
        if ((*allofthem[temp]).get_position() == thispos) {
          activepiece = allofthem[temp];
          return true;

        }
      }
    }
    return false;
  }
    bool hero_here(position thispos, bool nochange) {
    for (int temp = 0; temp < piecenum / 2; temp++) {
      if (whichactive[temp]) {
        if ((*allofthem[temp]).get_position() == thispos) {
            if (!nochange){
          activepiece = allofthem[temp];
            }
          return true;

        }
      }
    }
    return false;
  }
  bool anything_here(position thispos) {
    for (int temp = 0; temp < piecenum; temp++) {
      if (whichactive[temp]) {
        if ((*allofthem[temp]).get_position() == thispos) {
          activepiece = allofthem[temp];
          return true;

        }
      }
    }
    return false;
  }
    bool anything_here(position thispos, bool nochange) {
    for (int temp = 0; temp < piecenum; temp++) {
      if (whichactive[temp]) {
        if ((*allofthem[temp]).get_position() == thispos) {
            if (!nochange){
          activepiece = allofthem[temp];
            }
          return true;

        }
      }
    }
    return false;
  }

  void apply_active() {
    for (int temp = 0; temp < piecenum; temp++) {
      if (whichactive[temp]) {
        (*allofthem[temp]).apply_image();
      }
    }
  }
  void inc_frames(){
     for (int temp = 0; temp < piecenum; temp++) {
      if (whichactive[temp]) {
        (*allofthem[temp]).inc_frame();
      }
    }
  }

  void apply_possible(animate* piece_poss, animate* placehld){
   int tempint = 0;
   tempint++;
   if ((*piece_poss).is_good()){
   for (int temp = 0; temp < screen_x; temp += 50){
    for (int tempy = 0; tempy < screen_y; tempy += 50){
        position temppos = return_pos(temp,tempy);
      if ((*piece_poss).valid_move(temppos) && !hero_here(temppos,true)){
            (*placehld).teleport(temp,tempy);
            (*placehld).apply_image();


      }
    }
   }
   }
   else {
     for (int temp = 0; temp < screen_x; temp += 50){
    for (int tempy = 0; tempy < screen_y; tempy += 50){
        position temppos = return_pos(temp,tempy);
      if ((*piece_poss).valid_move(temppos) && !enemy_here(temppos,true)){
            (*placehld).teleport(temp,tempy);
            (*placehld).apply_image();


      }
    }
   }
   }
  }
  void set_good_VS_evil(){
      for (int temp = 0; temp < piecenum / 2; temp++){
          (*allofthem[temp]).set_good(true);
      }
      for (int temp = piecenum / 2; temp < piecenum; temp++){
          (*allofthem[temp]).set_good(false);
      }
  }


  animate* get_active() {
    return activepiece;

  }
};

class death: public animate{
protected:
bool activated;
int death_frame;
public:
death(){
 death_frame = f_n;
 activated = false;
}
void center_teleport(position t){
 x = t.x - f_w / 2;
 y = t.y - f_h / 2;
     update_off();
    active = true;
}
void start_death(){
 activated = true;
 death_frame = 0;
}
void death_animate(){
 if (death_frame < f_n){
 apply_image();
 inc_frame();
 death_frame++;
 }
}
~death(){
 End_This();
}

};


class piece_knight: public animate {
protected:
public:
  bool valid_move(position pos) {
    if (pos.x == x - 100 || pos.x == x + 100) {
      if (pos.y == y - 50 || pos.y == y + 50) {
        return true;
      }
    } else if (pos.x == x - 50 || pos.x == x + 50) {
      if (pos.y == y + 100 || pos.y == y - 100) {
        return true;
      }

    }
    return false;
  }
  ~piece_knight() {
    End_This();
  }
}knight,knight_two,bknight,bknight_two;

class piece_king: public animate {
protected:
public:
  bool valid_move(position pos) {
    if (pos.x != x || pos.y != y){
     if ((pos.x + 50 == x || pos.x - 50 == x )&& pos.y == y){
       return true;
     }
     else if ((pos.y + 50 == y || pos.y - 50 == y) && pos.x == x){
       return true;
     }
     else if (abs(pos.x - x) == 50 && abs(pos.y - y) == 50){
      return true;
     }
     return false;
    }
    return false;
  }
  ~piece_king() {
    End_This();
  }
}king,bking;

class piece_queen: public animate {
protected:
public:
  bool valid_move(position pos) {
      if ((pos.x == x && pos.y != y)){ // vertical
      if (pos.y > y){
          for (int temp = y + 50; temp < pos.y; temp = temp + 50){
           position temppos;
           temppos = return_pos(pos.x,temp);
           if ((*main_control).anything_here(temppos))
           return false;
          }
          return true;
      }
      else if (pos.y < y){
          for (int temp = pos.y + 50; temp < y; temp = temp + 50){
           position temppos;
           temppos = return_pos(pos.x,temp);
           if ((*main_control).anything_here(temppos))
           return false;
          }
          return true;
      }

      return false; // shouldn't get here
  }
  if ((pos.x != x && pos.y == y)){ // horizontal
       if (pos.x > x){
          for (int temp = x + 50; temp < pos.x; temp = temp + 50){
           position temppos;
           temppos = return_pos(temp,pos.y);
           if ((*main_control).anything_here(temppos))
           return false;
          }
          return true;
      }
      else if (pos.x < x){
          for (int temp = pos.x + 50; temp < x; temp = temp + 50){
           position temppos;
           temppos = return_pos(temp,pos.y);
           if ((*main_control).anything_here(temppos))
           return false;
          }
          return true;
      }

      return false; // shouldn't get here
  }
     if (abs(pos.x - x) == abs(pos.y - y)) { // as long as the change in x == change in y
        if (pos.x > x && pos.y > y){ // down right
            position temppos;
            temppos = pos;
            while (temppos.x > x + 50){
             temppos.x -= 50;
             temppos.y -= 50;
             if ((*main_control).anything_here(temppos)){
              return false;
             }
            }
        }
        else if (pos.x < x && pos.y > y) { // down left
            position temppos;
            temppos = pos;
            while (temppos.x < x - 50){
             temppos.x += 50;
             temppos.y -= 50;
             if ((*main_control).anything_here(temppos)){
              return false;
             }
            }
        }
        else if (pos.x > x && pos.y < y){ // up right
            position temppos;
            temppos = pos;
            while (temppos.x > x + 50){
             temppos.x -= 50;
             temppos.y += 50;
             if ((*main_control).anything_here(temppos)){
              return false;
             }
            }
        }
        else if (pos.x < x && pos.y < y - 50) { // up left
            position temppos;
            temppos = return_pos(x,y);
            while (temppos.x > pos.x + 50){
             temppos.x -= 50;
             temppos.y -= 50;
             if ((*main_control).anything_here(temppos)){
              return false;
             }
            }
        }
      return true;
      }
      return false;
  }
  ~piece_queen() {
    End_This();
  }
}queen, bqueen;

class piece_pawn: public animate {
protected:
public:
  bool valid_move(position pos) {

    if (firstmove) {
      if (pos.x == x) {
        if ((pos.y == y - 50 || pos.y == y - 100) && !(*main_control).anything_here(pos))
          return true;
      }
        if ((*main_control).enemy_here(pos))
          if (abs(pos.x - x) == abs(pos.y - y) && y - pos.y == 50) {
            return true;
          }

    }
    else {
        if (pos.x == x) {
        if (pos.y == y - 50 && !(*main_control).anything_here(pos))
          return true;
        }
        if ((*main_control).enemy_here(pos)){
          if (abs(pos.x - x) == abs(pos.y - y) && y - pos.y == 50) {
            return true;
          }
      }
    }
  return false;
  }
  ~piece_pawn() {
    End_This();
  }
}pawn[8];

class piece_bpawn: public animate {
protected:
public:
  bool valid_move(position pos) {

    if (firstmove) {
      if (pos.x == x) {
        if ((pos.y == y + 50 || pos.y == y + 100) && !(*main_control).anything_here(pos))
          return true;
      }
        if ((*main_control).hero_here(pos))
          if (abs(pos.x - x) == abs(pos.y - y) && (pos.y - y == 50)) {
            return true;
          }

    }
    else {
        if (pos.x == x) {
        if (pos.y == y + 50 && !(*main_control).anything_here(pos))
          return true;
        }
        if ((*main_control).hero_here(pos)){
          if (abs(pos.x - x) == abs(pos.y - y)&& (pos.y - y == 50)) {
            return true;
          }
      }
    }
  return false;
  }
  ~piece_bpawn() {
    End_This();
  }
}bpawn[8];

class piece_castle: public animate {
protected:
public:
  bool valid_move(position pos) {
  if ((pos.x == x && pos.y != y)){ // vertical
      if (pos.y > y){
          for (int temp = y + 50; temp < pos.y; temp = temp + 50){
           position temppos;
           temppos = return_pos(pos.x,temp);
           if ((*main_control).anything_here(temppos))
           return false;
          }
          return true;
      }
      else if (pos.y < y){
          for (int temp = pos.y + 50; temp < y; temp = temp + 50){
           position temppos;
           temppos = return_pos(pos.x,temp);
           if ((*main_control).anything_here(temppos))
           return false;
          }
          return true;
      }

      return false; // shouldn't get here
  }
  if ((pos.x != x && pos.y == y)){ // horizontal
       if (pos.x > x){
          for (int temp = x + 50; temp < pos.x; temp = temp + 50){
           position temppos;
           temppos = return_pos(temp,pos.y);
           if ((*main_control).anything_here(temppos))
           return false;
          }
          return true;
      }
      else if (pos.x < x){
          for (int temp = pos.x + 50; temp < x; temp = temp + 50){
           position temppos;
           temppos = return_pos(temp,pos.y);
           if ((*main_control).anything_here(temppos))
           return false;
          }
          return true;
      }

      return false; // shouldn't get here
  }
  return false;
  }
  ~piece_castle() {
    End_This();
  }
}castle,castle_two,bcastle,bcastle_two;

class piece_bishop: public animate {
protected:
public:
  bool valid_move(position pos) {
   if (abs(pos.x - x) == abs(pos.y - y)) { // as long as the change in x == change in y
        if (pos.x > x && pos.y > y){ // down right
            position temppos;
            temppos = pos;
            while (temppos.x > x + 50){
             temppos.x -= 50;
             temppos.y -= 50;
             if ((*main_control).anything_here(temppos)){
              return false;
             }
            }
        }
        else if (pos.x < x && pos.y > y) { // down left
            position temppos;
            temppos = pos;
            while (temppos.x < x - 50){
             temppos.x += 50;
             temppos.y -= 50;
             if ((*main_control).anything_here(temppos)){
              return false;
             }
            }
        }
        else if (pos.x > x && pos.y < y){ // up right
            position temppos;
            temppos = pos;
            while (temppos.x > x + 50){
             temppos.x -= 50;
             temppos.y += 50;
             if ((*main_control).anything_here(temppos)){
              return false;
             }
            }
        }
        else if (pos.x < x && pos.y < y - 50) { // up left
            position temppos;
            temppos = return_pos(x,y);
            while (temppos.x > pos.x + 50){
             temppos.x -= 50;
             temppos.y -= 50;
             if ((*main_control).anything_here(temppos)){
              return false;
             }
            }
        }
      return true;
      }
      return false;
  }



  ~piece_bishop() {
    End_This();
  }
}bishop, bishop_two,bbishop,bbishop_two;



class Timer {
private:
  int startTicks,pausedTicks;
  bool paused,started;
public:
  Timer();
  void start(), stop(), pause(), unpause();
  int get_ticks();
  bool is_started(), is_paused();
};
Timer::Timer() {
  startTicks = pausedTicks = 0;
  paused = started = false;
}
void Timer::start() {
  started = true;
  paused = false;
  startTicks = SDL_GetTicks();
}
void Timer::stop() {
  started = paused = false;
}
void Timer::pause() {
  if ((started == true) && (paused == false)) {
    paused = true;
    pausedTicks = SDL_GetTicks() - startTicks;
  }
}
void Timer::unpause() {
  if (paused == true) {
    paused = false;
    startTicks = SDL_GetTicks() - pausedTicks;
    pausedTicks = 0;
  }
}
int Timer::get_ticks() {
  if (started == true) {
    if (paused == true) {
      return pausedTicks;
    } else {
      return SDL_GetTicks() - startTicks;
    }
  }
  return 0;
}
bool Timer::is_started() {
  return started;
}
bool Timer::is_paused() {
  return paused;
}

#endif // IMAGE_H_INCLUDED
