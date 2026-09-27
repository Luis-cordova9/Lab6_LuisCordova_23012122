#include "RTE_Components.h"
#include CMSIS_device_header

#define MASK(x)   (1<<x) // para 1 pin de leer o prender led 

#define MASK2(x)  (3<<(2*x)) // 2 para ver tipo de resistencia y si es entrada o salida 


#define PuertoLEDsOut   GPIOB->ODR // salida 
#define LD1   0     // CN4 pin 6
#define LD2   4     // CN4 pin 15
#define LD3   5     // CN4 pin 14
#define LD4   6     // CN4 pin 9   
#define LD5   3     // CN3 pin 15  

#define TODOS   (MASK(LD1)|MASK(LD2)|MASK(LD3)|MASK(LD4)|MASK(LD5))

#define PuertoJoyIn     GPIOA->IDR // entrada 

#define ARRIBA      0   // CN3 pin 12  
#define DERECHA     1   // CN3 pin 11  
#define ABAJO       4   // CN3 pin 9   
#define IZQUIERDA   7   // CN3 pin 6   
#define FONDO       8   // CN4 pin 12  


void Configurar_LEDs(void);
void Configurar_Joystick(void);
void encender(int led);
void apagar(void);
int  arriba(void);
int  abajo(void);
int  derecha(void);
int  izquierda(void);
int  boton(void);

int main(void){

  Configurar_LEDs();
  Configurar_Joystick();

  while(1){
    if(arriba())          encender(LD1);
    if(abajo())      encender(LD3);
    if(derecha())    encender(LD2);
    if(izquierda())  encender(LD4);
    if(boton())      encender(LD5);
    
    else                  apagar();
  }
}

void Configurar_LEDs(void){

  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;   // activar reloj B
  // limpiamos 00
  GPIOB->MODER &= ~MASK2(LD1);
  GPIOB->MODER &= ~MASK2(LD2);
  GPIOB->MODER &= ~MASK2(LD3);
  GPIOB->MODER &= ~MASK2(LD4);
  GPIOB->MODER &= ~MASK2(LD5);
  // poner como salida 01
  GPIOB->MODER |= MASK(2*LD1);
  GPIOB->MODER |= MASK(2*LD2);
  GPIOB->MODER |= MASK(2*LD3);
  GPIOB->MODER |= MASK(2*LD4);
  GPIOB->MODER |= MASK(2*LD5);

  // todos apagados al empezar 
  apagar();                             
}

void Configurar_Joystick(void){

  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;   // reloj A

  // entrada 00
  GPIOA->MODER &= ~MASK2(ARRIBA);
  GPIOA->MODER &= ~MASK2(DERECHA);
  GPIOA->MODER &= ~MASK2(ABAJO);
  GPIOA->MODER &= ~MASK2(IZQUIERDA);
  GPIOA->MODER &= ~MASK2(FONDO);

  // limpiar 00
  GPIOA->PUPDR &= ~MASK2(ARRIBA);
  GPIOA->PUPDR &= ~MASK2(DERECHA);
  GPIOA->PUPDR &= ~MASK2(ABAJO);
  GPIOA->PUPDR &= ~MASK2(IZQUIERDA);
  GPIOA->PUPDR &= ~MASK2(FONDO);

  // pull-up 01 
  GPIOA->PUPDR |= MASK(2*ARRIBA);
  GPIOA->PUPDR |= MASK(2*DERECHA);
  GPIOA->PUPDR |= MASK(2*ABAJO);
  GPIOA->PUPDR |= MASK(2*IZQUIERDA);
  GPIOA->PUPDR |= MASK(2*FONDO);
}


 // enncender solo 1                          
void encender(int led){
  PuertoLEDsOut = (PuertoLEDsOut & ~TODOS) | MASK(led);
}
 // apagar todos 
void apagar(void){
  PuertoLEDsOut &= ~TODOS;
}
// leer el boton precionado 
int arriba(void){     
  return !(PuertoJoyIn & MASK(ARRIBA));    
}
int abajo(void){     
  return !(PuertoJoyIn & MASK(ABAJO));     
}
int derecha(void){    
  return !(PuertoJoyIn & MASK(DERECHA));   
}
int izquierda(void){  
  return !(PuertoJoyIn & MASK(IZQUIERDA)); 
}
int boton(void){     
   return !(PuertoJoyIn & MASK(FONDO)); 
}
