#include "defs.h"

/*
  Function:  initHero
  Purpose:   dynamically allocates and initializes one hero
       in:   the address of a HeroType pointer, the hero's avatar, initial col, and name
       out:  HeroType pointer that points to a newly initialized HeroType
*/
void initHero(HeroType** h, char avatar, int col, char *n){
  HeroType *temp = calloc(1, sizeof(HeroType));
  
  temp->partInfo.avatar = avatar;
  temp->partInfo.pos.row=MAX_ROW-1;
  temp->partInfo.pos.col=col;
  strcpy(temp->name, n);
  temp->health = MAX_HEALTH;
  temp->dead = C_FALSE;
  
  *h = temp;
}

/*
  Function:  addHero
  Purpose:   adds Hero to a HeroArrayType
       in:   the address of a HeroArrayType, the address of the hero to add to the collection
       out:  HeroArray with the hero now added
*/
void addHero(HeroArrayType *arr, HeroType *h){
  
  HeroType **temp;
  temp = calloc((arr->size)+1, sizeof(HeroType*));
    
  for(int i=0; i<arr->size; ++i){
    temp[i] = arr->elements[i];
  }
   
    
  free(arr->elements);
  arr->elements = temp;
  
  arr->elements[arr->size] = h;
  (arr->size)++;
}


/*
  Function:  heroIsSafe
  Purpose:   determines if a hero has successfully escaped the Hollow
       in:   the address of a HeroType pointer
       return: C_TRUE if the hero got to the end of the hollow without dying, C_FALSE otherwise
*/
int heroIsSafe(HeroType* hero){
  if((hero->dead == C_FALSE) && (hero->partInfo.pos.col == MAX_COL)){
    return C_TRUE;
  }
  
  return C_FALSE;

}

/*
  Function:  incurDamage
  Purpose:   decreases the provided hero's health by the strength of the provided flyer whenever a collision happens, 
             resets health to 0 if it goes below 0, and changes the hero's avatar to '+' if their health becomes 0 (they die)
       in:   the address of a HeroType pointer, the address of a FlyerType pointer
       out:  the heroe's health decreases, and if it gets to 0 then the avatar changes to '+'
*/
void incurDamage(HeroType* hero, FlyerType* flyer){
  hero->health = (hero->health) - (flyer->strength);
  if(hero->health<0){
    hero->health = 0;
  }
  
  
  if(hero->health == 0){
    hero->dead = C_TRUE;
    hero->partInfo.avatar = '+';
  }
  
  
}

