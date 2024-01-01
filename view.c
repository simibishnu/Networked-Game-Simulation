#include "defs.h"
/*
  Function:  outputHollow
  Purpose:   serializes and prints hollow, and then sends it to the client
       in:   the address of an EscapeType
*/
void outputHollow(EscapeType *escape){
  char buffer[MAX_BUFF];
  serializeHollow(escape, buffer);
  printf("%s", buffer);
  
  sendData(escape->viewSocket, buffer);
}

/*
  Function:  initHollow
  Purpose:   creates a 2D array that has the characters in their positions
       in:   the address of an EscapeType, a 2D array of chars
       out:  a 2D array of chars with the avatars of the characters in their positions
*/
void initHollow(EscapeType *escape, char arr[][MAX_COL]){
  for(int i=0; i<MAX_ROW; ++i){
    for(int j=0; j<MAX_COL; ++j){
       arr[i][j] = ' ';
    }
  }
 
  for(int i=0; i<escape->flyers.size; ++i){
    if(flyerIsDone(escape->flyers.elements[i])==C_FALSE){
      int flyerRow = escape->flyers.elements[i]->partInfo.pos.row;
      int flyerCol = escape->flyers.elements[i]->partInfo.pos.col;
      arr[flyerRow][flyerCol] = escape->flyers.elements[i]->partInfo.avatar;
    }
  }
  
  for(int i=0; i<escape->heroes.size; ++i){
    if(heroIsSafe(escape->heroes.elements[i])==C_FALSE){
      
      int heroRow = escape->heroes.elements[i]->partInfo.pos.row;
      int heroCol = escape->heroes.elements[i]->partInfo.pos.col;
    
      arr[heroRow][heroCol] = escape->heroes.elements[i]->partInfo.avatar;
    }
  }

}

/*
  Function:  serializeHollow
  Purpose:   constructs a 1D array with the formatted hollow, with borders, the characters, and their health information
       in:   the address of an EscapeType, an array of chars
       out:  an array of chars that represents the serialized format of the hollow
*/
void serializeHollow(EscapeType *escape, char *arr){
  char tempHollow[MAX_ROW][MAX_COL];
  int index = 0;
  char haroldHealth[MAX_STR];
  char timmyHealth[MAX_STR];
  sprintf(timmyHealth, "%d", escape->heroes.elements[0]->health);
  sprintf(haroldHealth, "%d", escape->heroes.elements[1]->health);
  initHollow(escape, tempHollow);
  
  for(int i=0; i<MAX_COL+2; ++i){
    arr[index++] = '-';
  }
  arr[index++] = '\n';
  
  for(int i=0; i<MAX_ROW; ++i){
    if(i == MAX_ROW - 1){
      arr[index++] = '=';
    }
    else{
      arr[index++] = '|';
    }
    for(int j=0; j<MAX_COL+2; ++j){
      if(j==MAX_COL+1){
        if(i == MAX_ROW-1){
          arr[index++] = '=';
        }
        else{
          arr[index++] = '|';
        }
      }
      else{
        if(j<MAX_COL){
          arr[index++] = tempHollow[i][j];
        }
      }
    
    }
    
    if(i == MAX_ROW - 1){
      arr[index++] = ' ';
      arr[index++] = ' ';
      arr[index++] = ' ';
      arr[index++] = ' ';
      arr[index++] = ' ';
      arr[index++] = ' ';
      for(int k=0; k<strlen(escape->heroes.elements[1]->name); ++k){
        arr[index++] = escape->heroes.elements[1]->name[k];
      }
      arr[index++] = ':';
      arr[index++] = ' ';
      arr[index++] = ' ';
      arr[index++] = ' ';
      
      for(int k=0; k<strlen(haroldHealth); ++k){
        arr[index++] = haroldHealth[k];
      }
      
    }
    
    if(i == MAX_ROW-2){
      arr[index++] = ' ';
      arr[index++] = ' ';
      arr[index++] = ' ';
      arr[index++] = ' ';
      arr[index++] = ' ';
      arr[index++] = ' ';
      for(int k=0; k<strlen(escape->heroes.elements[0]->name); ++k){
        arr[index++] = escape->heroes.elements[0]->name[k];
      }
      arr[index++] = ' ';
      arr[index++] = ':';
      arr[index++] = ' ';
      arr[index++] = ' ';
      arr[index++] = ' ';
      for(int k=0; k<strlen(timmyHealth); ++k){
        arr[index++] = timmyHealth[k];
      
      }
    }
    
    arr[index++] = '\n';
  }
  
  for(int i=0; i<MAX_COL+2; ++i){
    arr[index++] = '-';
  }
  arr[index++] = '\n';
  arr[index++] = '\0';
}


/*
  Function:  handleEscapeResult
  Purpose:   prints the result of the escape and sends it to the client
       in:   the address of an EscapeType
*/
void handleEscapeResult(EscapeType *escape){
  char timmyOutcome[MAX_STR];
  char haroldOutcome[MAX_STR];
  char hollowResult[MAX_BUFF];
  if(heroIsSafe(escape->heroes.elements[0])==C_TRUE){
    
    strcpy(timmyOutcome, "Timmy  ESCAPED !!!");
  }
  else{
    
    strcpy(timmyOutcome, "Timmy  IS DEAD...");
  }
  
  if(heroIsSafe(escape->heroes.elements[1])==C_TRUE){
    
    strcpy(haroldOutcome, "Harold ESCAPED !!!");
  }
  else{
    strcpy(haroldOutcome, "Harold IS DEAD...");
  }
  
  sprintf(hollowResult, "%s\n%s\n", timmyOutcome, haroldOutcome);
  printf("%s", hollowResult);
  sendData(escape->viewSocket, hollowResult);
  usleep(OUTPUT_INTERVAL);
}


