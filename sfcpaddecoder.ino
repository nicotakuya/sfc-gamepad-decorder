//super famicom gamepad decorder
//by takuya matsubara

#define SFC_CLOCK 5
#define SFC_LATCH 6
#define SFC_DATA 7

//output pin table
//D8+0:UP
//D8+1:DOWN
//D8+2:LEFT
//D8+3:RIGHT
//D8+4:A
//D8+5:B
//D8+6:X
//D8+7:START
//D8+8:SELECT
//D8+9:Y
//D8+10:L
//D8+11:R

//PD0 D0
// :  :
//PD7 D7
//PB0 D8
// :  :
//PB5 D13
//PC0 D14
// :  :
//PC5 D19
char dnum[]={
  8+5, //B
  8+9, //Y
  8+8, //SELECT
  8+7, //START
  8+0, //UP
  8+1, //DOWN
  8+2, //LEFT
  8+3, //RIGHT
  8+4, //A
  8+6, //X
  8+10, //L
  8+11, //R
  0, //-
  0, //-
  0, //-
  0 //-
};

void setup() {
  int bitnum;
  Serial.begin(115200);  //baudrate
  
  pinMode(SFC_DATA, INPUT_PULLUP);
  pinMode(SFC_CLOCK, OUTPUT);
  pinMode(SFC_LATCH, OUTPUT);
  digitalWrite(SFC_LATCH, LOW);
  digitalWrite(SFC_CLOCK, HIGH);

  for(bitnum=0; bitnum<16; bitnum++){
    if(dnum[bitnum] > 0){
      pinMode(dnum[bitnum], OUTPUT);
      digitalWrite(dnum[bitnum], LOW);
    }
  }
  delay(10);
}

void loopwait(void){
  int i;
  for(i=0;i<100;i++){
  }
}

int onesec=0;
#define DEBUG 0

void loop() {
  unsigned int dat;
  int bitnum;
  int pinnum;

  digitalWrite(SFC_LATCH, HIGH);
  loopwait();
  digitalWrite(SFC_LATCH, LOW); //LATCH ON

  dat = 0;
  for(bitnum=0; bitnum<16; bitnum++){
    dat = dat<<1;
    pinnum = dnum[bitnum];
    if(pinnum > 0){
      if(digitalRead(SFC_DATA)==LOW){
        dat |= 1;
        pinMode(pinnum, OUTPUT);
      }else{
        pinMode(pinnum, INPUT); //high impedance
      }
    }
    digitalWrite(SFC_CLOCK, LOW);
    loopwait();
    digitalWrite(SFC_CLOCK, HIGH);
  }
  if(DEBUG){
    onesec += 16;         //debug
    if(onesec>=1000){     //debug
      onesec -= 1000;     //debug
      Serial.print(dat,HEX);  //debug
      Serial.write('\n');  //debug
    }                       //debug
  }
  delay(16);
}

