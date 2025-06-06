//process_data.h
#include <stdlib.h> //abs function
#include "myservo.h"
#include "mypwm.h"

char *token;
char tokens[5][30];
int x = 0;

void process_data(char *s){
  x=0;
  token = strtok(s, " ");
  while(token != NULL){
    strcpy(tokens[x], token);
    token = strtok(NULL, " ");
    x++;}
    
  if(strcmp(tokens[0],"speed") == 0) {
    int x_data = atoi(tokens[1]);// x is left right
    //printf("x_data: %d\n",x_data);
    if(x_data == 0) servo_center();
    else if (x_data > 20) servo_left();
    else if (x_data < -20) servo_right();
    
    int y_data = atoi(tokens[2]) * 2;
    printf("y_data: %d\n",y_data);
    if(y_data == 0) stop_motor();
    else if(y_data > 0) forward_motor(y_data);
    else if(y_data < 0) reverse_motor(abs(y_data));
    
    
    //int y_data = atoi(tokens[2]) * 50;//duty cycle 0 - 5000
    //y is up down
  //  int y_data = atoi(tokens[2]) * 35;//adjust 35 plus minus for motor speed
    //printf("y_data: %d\n",y_data);
   // if(y_data == 0) stop();
   // else if(y_data > 0) forward(y_data);
   // else if(y_data < 0) reverse(abs(y_data));
  }
    
}



