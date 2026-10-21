#define Tx_size 30
#include<reg51.h>
unsigned char tx_head;
unsigned char head_next;
unsigned char tx_tail;
unsigned char tx_buff[Tx_size];
unsigned char tx_busy;
void uart_init(){
TMOD=0X20;
SCON=0X50;
TH1=0XFD;
TL1=0XFD;
EA=1;
ES=1;
TR1=1;
}

void uart_send_string(char *str){

while(*str!= '\0'){
	head_next= tx_head+1;
	if(head_next>= Tx_size){
		head_next=0;
	}
	if(head_next==tx_tail)
		return;
  tx_buff[tx_head]= *str;
  str++;
  tx_head= head_next;
	
}
if(tx_busy==0){
SBUF= tx_buff[tx_tail];
tx_tail++;
	tx_busy=1;
}


}
void isr() interrupt 4{
if(TI==1){
TI=0;
	
if(tx_tail!= tx_head){
SBUF= tx_buff[tx_tail];
tx_tail++;
}
else{
	tx_busy=0;
}
if(tx_tail>=Tx_size){
tx_tail=0;
}
}
}

void main(){
uart_init();
uart_send_string("Circular Buffer");
}