#include <18F4620.h>
#include <stdio.h>
#include <stdlib.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, /*NOMCLR,*/ STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use fast_io(a)
#use fast_io(b)
#use fast_io(d)
#use fast_io(e)
#define TX_232        PIN_C6
#define RX_232        PIN_C7
#use RS232(BAUD=9600, XMIT=TX_232, RCV=RX_232, stream = uart, BITS=8, PARITY=N, STOP=1)
#use fast_io(c)

char cadena(){
   char cadenaVector;
   cadenaVector=getch(uart);
   return cadenaVector;
}

void main(void) {
   setup_oscillator(OSC_16MHZ);
    char cadenaVector[12];
   int flag=0;
   int contador =0;
   while (1) {
   if(kbhit()){
      cadenaVector[contador]cadena();
      if(cadenaVector1[contador1]>=42 && cadenaVector1[contador1]<=62){ 
         fprintf(uart,"%c ",cadenaVector1[contador1]);
         if(cadenaVector1[contador1]=='<'){
            flag1=1;
         }
      contador1++;
      } 
   } 
   
   if(flag==TRUE){
      fprintf(uart,"hola mundo");
   }
   
   
   
}
}

