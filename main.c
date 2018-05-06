#include <18F4620.h>
#include <stdio.h>
#include <stdlib.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, /*NOMCLR,*/ STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use fast_io(a)
#use fast_io(b)
#use fast_io(e)
unsigned char caracter[22];
int accountant=0;
signed long result=0;
unsigned long num1=0,num2=0;
int pointer=0;
char operation;
int DoCalculation=0;
   
#define TX_232        PIN_C6
#define RX_232        PIN_C7
#use RS232(BAUD=9600, XMIT=TX_232, RCV=RX_232, stream = uart, BITS=8, PARITY=N, STOP=1)

void bloob(void);
void clean(void);
void main(void) {
   setup_oscillator(OSC_16MHZ);
   set_tris_a(0xc0);
   set_tris_b(0x0);
   set_tris_e(0x08);
   
   fprintf(uart,"Ingresa los datos siguiendo el orden >dato,dato,operacion<\r\n");
   
while (1) { 
   if(kbhit()){   
      caracter[accountant]=getch(uart);
      if(caracter[accountant]>=42 && caracter[accountant]<=62){ 
         fprintf(uart,"%c ",caracter[accountant]);
         if(caracter[accountant]=='<'){
            DoCalculation=1;
         }
      accountant++;
      } 
   }
   if(DoCalculation == 1){
      pointer++;	
      while(caracter[pointer]!=','){
         num1=num1*10 + (caracter[pointer]-'0');
         pointer++;
      }
      pointer++;
      while (caracter[pointer]!=','){
         num2=num2*10 + (caracter[pointer]-'0');
         pointer++;
      }
      pointer++;
      operation=caracter[pointer];
      
     if(num1<256 && num2 <256){   
        switch(operation){
		   case '+':
              result = (long)num1+(long)num2;
              fprintf(uart,"\rEl resultado de la operacion es: %.0f\r\n",(float)result);
		   break;
		   case '-':
		      result = (long)num1-(long)num2;
              fprintf(uart,"\rEl resultado de la operacion es: %.0f\r\n",(float)result);
		   break;
           case '*':
               result = (long)num1*(long)num2;
               fprintf(uart,"\rEl resultado de la operacion es: %.0f\r\n",(float)result);
           break;
           case '/':
              if(num2!=0){
              result = (long)num1/(long)num2;
              fprintf(uart,"\rEl resultado de la operacion es: %.0f\r\n",(float)result);
              }
              else{
                 bloob();
                 fprintf(uart,"\rError\r\n");
              }
           break;
        }
   output_a((long)result);
   output_b((long)result>>6);
   output_e((long)result>>10);
   clean();
   }
   else{
      fprintf(uart,"\rTienes numeros mayor a 255\r\n");
      output_a((long)result);
      output_b((long)result>>6);
      output_e((long)result>>10);
      output_b((long)result>>13);
      clean();
   }
   }
}
}

void clean(void){
   num1=NULL;
   num2=NULL;
   operation=NULL;
   pointer=0;
   for(int clear=0; clear<22;clear++){
      if(caracter[clear]!=NULL){
         caracter[clear]=NULL;
      }
   }
   accountant=0;
   DoCalculation=0;
   result=0;
   break;
}

void bloob(void){
   long Error=0x1;
   for(int repeaterGo = 1; repeaterGo <= 13; repeaterGo++){
      Error=Error+Error;
      output_a(Error);
      output_b(Error>>6);
      output_e(Error>>10);
      delay_ms(10);
   }
   Error=0x1000;
   for(int repeaterBack = 13; repeaterBack >=1; repeaterBack--){
      Error/=2;
      output_a(Error);
      output_b(Error>>6);
      output_e(Error>>10);
      delay_ms(10);
   }
   break;
}