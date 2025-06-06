//main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btlib.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "mypwm.h"
#include "myservo.h"
#include "process_data.h"

#define ENABLE_READKEY 1
#define ENABLE_INPUTPIN 2

void set_usb_flags(int flags);
int read_usb_endchar(unsigned char *buf,int len,unsigned char endchar,int toms);

  // callback for LE server
int lecallback(int node,int op,int cticn);

char *devices = { 
"DEVICE = Picostack type=mesh  node=1  address=local          \n\
PRIMARY_SERVICE=1800                                          \n\
  LECHAR=Device name    SIZE=16 PERMIT=02 UUID=2A00  ;index 0 \n\
PRIMARY_SERVICE=112233445566778899AABBCCDDEEFF00              \n\
   LECHAR = Data        SIZE=8  PERMIT=06 UUID=ABCD  ;index 1 \n\
   LECHAR = LED control SIZE=1  PERMIT=04 UUID=CAFE  ;index 2 \n\
"};
                                                                 

void mycode(void);

void mycode(){
  
  sleep_ms(3000);  // 3s delay for USB monitor
  set_usb_flags(ENABLE_READKEY | ENABLE_INPUTPIN);
  
//init servo
init_servo();

//init motor pwm
init_pwm();
  
  if(init_blue(devices) == 0)
    return;
    
  while(1)
    {
    le_server(lecallback,10);  // 10 = 1 second timer 
    }
  }

int lecallback(int node,int op,int cticn){
  unsigned char data_received[30];
  
  if(op == LE_CONNECT) cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

  else if(op == LE_WRITE && cticn == 2){ //writing to characteristic CAFE, index 2
    read_ctic(localnode(),2,data_received,sizeof(data_received));
    process_data(data_received);
  }
  else if(op == LE_DISCONNECT) cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN,0);

  return(SERVER_CONTINUE);
  }





