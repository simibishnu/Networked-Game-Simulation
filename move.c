#include "defs.h"

/*
  Function:  setPos
  Purpose:   sets a position with the provided row and col, resetting values if they are out of the hollow's bounds
       in:   the address of a PositionType, a row, a col
       out:  a PositionType that's initialized with the provided row and col
*/
void setPos(PositionType* pos, int row, int col){
  
  if(col<0){
    col = 0;
  }
  
  if(col>MAX_COL){
    col = MAX_COL;
  }
  
  if(row<0){
    row = 0;
  }
  
  if(row>MAX_ROW){
    row = MAX_ROW;
  }
  
  pos->row = row;
  pos->col = col;

}

/*
  Function:  moveHero
  Purpose:   computes a hero's next move and updates their position
       in:   the address of a HeroType pointer, the address of an EscapeType
       out:  the hero's position that's updated
*/
void moveHero(HeroType *hero, EscapeType *escape){
  int randNum = randomInt(101);
  int newPos = hero->partInfo.pos.col;
  
  if(hero->partInfo.avatar =='T'){
    if(randNum<=50){
      newPos+=DIR_RIGHT*2;
    }
    if(randNum>50 && randNum<=80){
      newPos+=DIR_LEFT;
    }
    if(randNum>80 && randNum<=100){
      newPos+= DIR_RIGHT;
    }
  }
  
  if(hero->partInfo.avatar == 'H'){
    if(randNum<=20){
      newPos+= DIR_SAME;
    }
    if(randNum>20 && randNum<=30){
      newPos+=DIR_RIGHT*5;
    }
    if(randNum>30 && randNum<=40){
      newPos+=DIR_LEFT*4;
    }
    if(randNum>40 && randNum<=80){
      newPos+=DIR_RIGHT*3;
    }
    if(randNum>80 && randNum<=100){
     newPos+= DIR_LEFT*2;
    }
  }
  
  setPos(&(hero->partInfo.pos), MAX_ROW-1, newPos);
  
}

/*
  Function:  moveFlyer
  Purpose:   computes the flyer's next move, updates its position, and deals with any collisions with heroes
       in:   the address of a FlyerType, the address of a EscapeType 
       out:  the flyer's updated position
*/
void moveFlyer(FlyerType *flyer, EscapeType *escape){
  int row = flyer->partInfo.pos.row;
  int col = flyer->partInfo.pos.col;
  int dir = DIR_SAME;
  
  HeroType *temp = NULL;
  
  if(flyer->partInfo.avatar == 'v'){
    row += 1;
    col += randomInt(3)-1;
  }
  if(flyer->partInfo.avatar == '@'){
    row += randomInt(7)-3;
    computeHeroDir(escape, flyer, &dir);
    col += (randomInt(3)+1)*dir;
  }
  
  setPos(&(flyer->partInfo.pos), row, col);
  temp = checkForCollision(&(flyer->partInfo.pos), escape);
  
  if(temp!=NULL){
    incurDamage(temp, flyer);
  }
}

/*
  Function:  computeHeroDir
  Purpose:   computes direction of the closest hero to the provided flyer and returns it in the dir parameter
       in:   the address of an EscapeType, the addres of a FlyerType, the address of dir
       out:  the direction of the closest hero 
*/
void computeHeroDir(EscapeType* escape, FlyerType* flyer, int* dir){
  int distance = 0;
  int closestDistance = MAX_COL;
  
  for(int i=0; i<escape->heroes.size; ++i){
    if(heroIsSafe(escape->heroes.elements[i])==C_FALSE && escape->heroes.elements[i]->dead==C_FALSE){
       distance = escape->heroes.elements[i]->partInfo.pos.col - flyer->partInfo.pos.col;
       if(abs(distance)<abs(closestDistance)){
         closestDistance = distance;
         if(closestDistance<0){
           *dir = DIR_LEFT;
         }
         else if(closestDistance>0){
           *dir = DIR_RIGHT;
         }
         else{
           *dir = DIR_SAME;
         }
       } 
    }
  }

}