/* BY THE NAME OF ALLAH THE MERCIFUL THE COMPASSIONATE.
 * Library name: "chess-resource.h" .
 * Author: nacereddine abed elillah.
 * Purpose: play the chess game.
 * Remarque: all rights are reserved to the author and the author will not be responsible for any
         illegal use of this game engine.
 * last time modified: 19/01/14 17:43 */
 
#include "chess-resource.h"

int main (){
    int move_memory[80][8][8];
    int move_number=0; // an increment for move_memory.
    int board[8][8]; // the chess board.
    char old_moves [140]; // hold the last 28 moved.
    int index,a=0; // index to old_moves/a is the last position in old moves.
    int turn=1; // refers to the current turn.
    int error=0; // changed if there any mistakes have been made.
    char move[5]; // holds the next move.
    int l_move; // holds the last move in numeral forme.
    char choice; // the user's choice at the welcome screen and the pawn's transformation.
               //(I chose it to be a character type so even if the user types a character  instead of an integer the game will not freeze )
    int index_i,index_j; //  index to board (the caller).
       
    for (index_i=0;index_i!=8;index_i++){
          for(index_j=0;index_j!=8;index_j++){board[index_i][index_j]=0;}} // clear board
    
    for (index=0;index!=80;index++){
          for (index_i=0;index_i!=8;index_i++){
                for(index_j=0;index_j!=8;index_j++){move_memory[index][index_i][index_j]=0;}}} // clear move_memory.      
    
    for (index_i=0;index_i!=140;index_i++){old_moves[index_i]='\0';} // clear old_moves 
    
          
    welcome(choice);
   
    
    
   if(int(choice)-48==2){ 
      start_up(board,old_moves,turn);
      for (index_i=0;index_i!=8;index_i++){
                            for(index_j=0;index_j!=8;index_j++){
                                move_memory[move_number][index_i][index_j]=board[index_i][index_j];}} 
          
      while(1){     
        
        show_screen(board,old_moves,turn,error);        
        if((error!=0)&&(error!=12)&&(error!=13)&&(error!=14)){error=0; cin.get(); cin.get();}
        else{if(error==12){char choice2; 
                      cout<<"enter your choice:";
                      cin>>choice2;
                      int y1,x1,y2,x2; // the coordinate in the board./ old position. / new position.
                      int t;// indicate the colore of the pawn.
                      
                      x2=left(l_move,10); y2=(left(l_move,100)-x2)/10;
                      x1=(left(l_move,1000)-y2*10-x2)/100; y1=(l_move-x1*100-y2*10-x2)/1000;
                      if(turn==1){turn=2;t=0;}else{turn=1;t=1;}
                      
                      if(int(choice2)-48==1){board[y2][x2]=20+t; board[y1][x1]=0;}
                        else{if(int(choice2)-48==2){board[y2][x2]=30+t; board[y1][x1]=0;}
                             else{if(int(choice2)-48==3){board[y2][x2]=50+t; board[y1][x1]=0;}
                                  else{if(int(choice2)-48==4){board[y2][x2]=60+t; board[y1][x1]=0;}
                                             else {board[y2][x2]=20+t; board[y1][x1]=0;}
                                             }}}error=0; }    
             else{cout<<"next move:";
                  for (index_i=0;index_i!=5;index_i++){cin>>move[index_i];}
                  l_move=check_input_move(move,board,error,turn); } 
             if(error==15){break;}// the user asked to exit the game
             else{if(error==14){start_up(board,old_moves,turn);}// the user asked for a new game.
             else{if(error==13){// the user asked to undo the last move.
                                if(move_number==0){/*do nothing*/}
                           else{move_number--;
                                for (index_i=0;index_i!=8;index_i++){
                                   for(index_j=0;index_j!=8;index_j++){
                                       board[index_i][index_j]= move_memory[move_number][index_i][index_j];}}
                                if(turn==1){turn=2;}else{turn=1;}       
                                for (index_i=a-5;index_i!=a;index_i++){old_moves[index_i]='\0';}
                                a=a-5;
                                error=0;
                                
                               } 
                          
                          
                          }
             else{if(error==0){move_number++;
                               for (index_i=0;index_i!=8;index_i++){
                               for(index_j=0;index_j!=8;index_j++){
                                move_memory[move_number][index_i][index_j]=board[index_i][index_j];}}
        
                          for(index=a;index!=a+5;index++){old_moves[index]=move[index-a];}
                              a=index;
                              if(a==140){ a=135;
                                          char tmp[140]; // tmporary storage array.
                                          for (index_i=0;index_i!=140;index_i++){tmp[index_i]=old_moves[index_i];}// putting old_moves in tmp.
                                          for (index_i=0;index_i!=140;index_i++){old_moves[index_i]='\0';} // clear old_moves.
                                          for (index_i=0;index_i!=135;index_i++){old_moves[index_i]=tmp[index_i+5];} 
                                          /*deleting the first move and regrouping the remaining.*/}
                         }}}} 
             }
        system("cls");
               }         }
     return(1);
     }
