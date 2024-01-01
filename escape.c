#include "defs.h"

/*
  Function:  runEscape
  Purpose:   initializes the escape for the game, contains the game loop, handles escape result, cleans up escape
*/
void runEscape(){
  EscapeType escape;
  
  initEscape(&escape);
  
  while(1){
    if(escape.flyers.size<MAX_ARR){
      int randBird = randomInt(101);
      int randMonkey = randomInt(101);
      
      if(randBird<=BIRD_SPAWN_RATE){
        int birdRow = randomInt(5);
        int birdCol = randomInt(MAX_COL);
        int birdStrength = randomInt(3)+3;
        
        spawnFlyer(&escape, 'v', birdStrength, birdRow, birdCol);
      }
      if(randMonkey<=MONKEY_SPAWN_RATE){
        int monkeyRow = randomInt(MAX_ROW);
        int monkeyCol = randomInt(MAX_COL);
        int monkeyStrength = randomInt(4)+8;
        
        spawnFlyer(&escape, '@', monkeyStrength, monkeyRow, monkeyCol);
      }
    }
    
    for(int i=0; i<escape.heroes.size; ++i){
      if(heroIsSafe(escape.heroes.elements[i])==C_FALSE && escape.heroes.elements[i]->dead==C_FALSE){
        moveHero(escape.heroes.elements[i], &escape);
      }
    }
    
    for(int i=0; i<escape.flyers.size; ++i){
      if(flyerIsDone(escape.flyers.elements[i])==C_FALSE){
        moveFlyer(escape.flyers.elements[i], &escape);
      }
    }
    
    
    outputHollow(&escape);
    usleep(OUTPUT_INTERVAL);
    system("clear");
    if(escapeIsOver(&escape)==C_TRUE){
      break;
    }
    
  }
  
  outputHollow(&escape);
  usleep(OUTPUT_INTERVAL);
  handleEscapeResult(&escape);
  usleep(OUTPUT_INTERVAL);
  cleanupEscape(&escape);
  
}

/*
  Function:  escapeIsOver
  Purpose:   checks if the escape is over (ie. whether either hero is dead or has escaped)
       in:   the address of a EscapeType
       return:  returns C_TRUE if the escape is over, C_FALSE otherwise
*/
int escapeIsOver(EscapeType *escape){
  if((heroIsSafe(escape->heroes.elements[0])==C_TRUE || escape->heroes.elements[0]->dead==C_TRUE) && (heroIsSafe(escape->heroes.elements[1])==C_TRUE || escape->heroes.elements[1]->dead==C_TRUE)){

    return C_TRUE;
  }
  
  return C_FALSE;
}

/*
  Function:  initEscape
  Purpose:   initializes escape, seeds PRNG, initializes the hero and flyer arrays, allocates and 
             initializes both heroes and adds them to the heroes array, initializes sockets and 
             blocks until client connection request is received
       in:   the address of a EscapeType
       out:  an Escape with initialized values
*/

void initEscape(EscapeType* escape){
  srand( (unsigned)time( NULL ) );
  
  escape->heroes.elements = NULL;
  escape->heroes.size = 0;
  
  escape->flyers.size = 0;
  
  int timmyInitCol = 0;
  int haroldInitCol = 0;
  
  while(1){
    timmyInitCol = randomInt(5);
    haroldInitCol = randomInt(5);
    if(timmyInitCol!=haroldInitCol){
      break;
    }
  }
  
  HeroType *timmy;
  HeroType *harold;
  
  initHero(&timmy, 'T', timmyInitCol, "Timmy");
  initHero(&harold, 'H', haroldInitCol, "Harold");
  
  addHero(&(escape->heroes), timmy);
  addHero(&(escape->heroes), harold);
  
  setupServerSocket(&(escape->listenSocket));
  
  acceptConnection(escape->listenSocket, &(escape->viewSocket));
  
}


/*
  Function:  cleanupEscape
  Purpose:   cleans up escape by deallocating memory, sending termination message to client, and closing its sockets
       in:   the address of an EscapeType
       out:  the EscapeType with the deallocated memory and closed sockets
*/

void cleanupEscape(EscapeType *escape){
  char buffer[MAX_BUFF];
  for(int i=0; i<escape->heroes.size; ++i){
    free(escape->heroes.elements[i]);
  }
  
  free((escape->heroes.elements));
  
  for(int i=0; i<escape->flyers.size; ++i){
    free(escape->flyers.elements[i]);
  }
  strcpy(buffer, "quit");
  sendData(escape->viewSocket, buffer);
  usleep(OUTPUT_INTERVAL);
  close(escape->listenSocket);
  close(escape->viewSocket);
}

