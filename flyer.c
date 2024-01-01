#include "defs.h"

/*
  Function:  spawnFlyer
  Purpose:   dynamically allocates and initializes one flyer and adds it to the provided escape's flyer collection
       in:   the address of a EscapeType, the flyer's avatar, strength, initial row, and column
       out:  the escape's flyer collection with the newly added flyer
*/
void spawnFlyer(EscapeType *escape, char avatar, int strength, int row, int col){
  FlyerType *temp = calloc(1, sizeof(FlyerType));
 
  temp->partInfo.avatar = avatar;
  temp->partInfo.pos.row = row;
  temp->partInfo.pos.col = col;
  temp->strength = strength;
    
  addFlyer(&(escape->flyers), temp);

}

/*
  Function:  addFlyer
  Purpose:   adds provided flyer to the provided FlyerArrayType
       in:   the address of a FlyerArrayType, the address of a FlyerType
       out:  the FlyerArrayType with a newly added flyer
*/

void addFlyer(FlyerArrayType* arr, FlyerType* flyer){
  arr->elements[arr->size] = flyer;
  ++arr->size;
}


/*
  Function:  flyerIsDone
  Purpose:   checks if the provided flyer has reached the ground of the hollow
       in:   the address of a FlyerType
       return: C_TRUE if the flyer is on the ground, C_FALSE otherwise
*/
int  flyerIsDone(FlyerType* flyer){
  if(flyer->partInfo.pos.row == MAX_ROW){
    return C_TRUE;
  }
  
  return C_FALSE;
  
}
/*
  Function:  checkForCollision
  Purpose:   checks if a collision has occured with the provided flyer and the heroes, and returns the hero that's hit if there is a collision, returns NULL otherwise
       in:   the address of a flyer's position, the address of an EscapeType
       return: returns the address of the hero that got hit if there is a collision, otherwise returns NULL
*/
HeroType* checkForCollision(PositionType* flyerPos, EscapeType* escape){
  for(int i=0; i<escape->heroes.size; ++i){
     if(escape->heroes.elements[i]->partInfo.pos.col == flyerPos->col && escape->heroes.elements[i]->partInfo.pos.row == flyerPos->row){
       return escape->heroes.elements[i];
     }
   }
   
  return NULL;

}