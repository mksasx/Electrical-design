#define note_C 29          //523
#define note_C_sharp 27    //554
#define note_D 26          //587
#define note_D_sharp 24    //622
#define note_E 23          //659
#define note_F 22          //698
#define note_F_sharp 20    //740
#define note_G 19          //784
#define note_G_sharp 18    //830
#define note_A 17          //880
#define note_A_sharp 16    //932
#define note_B 15          //988
int shape = 1;             // 
int i , j = 0;
int pos = 0;               // *0 - Release 和 Off   *1 - Attack    *2 - Decay   *3 - Sustain
bool on = 0;
int n = 50;
void setup() {
  analogWriteResolution(12);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  pinMode(25, INPUT);
}

void loop() {
  float DACOUT_f;
  int DACOUT;
  int anaIN_M = analogRead(A0);
  int T_A = 10;   //A影响的最大周期数量
  int T_D = 10;   //D影响的最大周期数量
  int T_R = 10;   //L影响的最大周期数量
  int anaIN_A =analogRead(A1) * T_A / 1024;    //实际上A影响的周期数量
  int anaIN_D =analogRead(A2) * T_D / 1024;    //实际上D影响的周期数量
  float anaIN_S = 1.0 * analogRead(A3) / 1024; 
  int anaIN_R =analogRead(A4) * T_R / 1024;    //实际上R影响的周期数量
  int key_C = digitalRead(13);
  int key_C_sharp = digitalRead(2);
  int key_D = digitalRead(3);
  int key_D_sharp = digitalRead(4);
  int key_E = digitalRead(5);
  int key_F = digitalRead(6);
  int key_F_sharp = digitalRead(7);
  int key_G = digitalRead(8);
  int key_G_sharp = digitalRead(9);
  int key_A = digitalRead(10);
  int key_A_sharp = digitalRead(11);
  int key_B = digitalRead(12);
  int shape_sin = digitalRead(22);
  int shape_tri = digitalRead(23);
  int shape_saw = digitalRead(24);
  int shape_pulse = digitalRead(25);
  if ( key_C == HIGH ){
    on = 1;
    n = note_C;
  }
  if ( key_C_sharp == HIGH ){
    on = 1;
    n = note_C_sharp;
  }
  if ( key_D == HIGH ){
    on = 1;
    n = note_D;
  }
  if ( key_D_sharp == HIGH ){
    on = 1;
    n = note_D_sharp;
  }
  if ( key_E == HIGH ){
    on = 1;
    n = note_E;
  }
  if ( key_F == HIGH ){
    on = 1;
    n = note_F;
  }
  if ( key_F_sharp == HIGH ){
    on = 1;
    n = note_F_sharp;
  }
  if ( key_G == HIGH ){
    on = 1;
    n = note_G;
  }
  if ( key_G_sharp == HIGH ){
    on = 1;
    n = note_G_sharp;
  }
  if ( key_A == HIGH ){
    on = 1;
    n = note_A;
  }
  if ( key_A_sharp == HIGH ){
    on = 1;
    n = note_A_sharp;
  }
  if ( key_B == HIGH ){
    on = 1;
    n = note_B;
  }
  if ( shape_sin == HIGH ){
    shape = 1;
  }
  if ( shape_tri == HIGH ){
    shape = 2;
  }
  if ( shape_saw == HIGH ){
    shape = 3;
  }
  if ( shape_pulse == HIGH ){
    shape = 4;
  }
  if (on){
    switch (pos){
      case 0:
        pos = 1;
        if(anaIN_A==0){
            pos = 2;
            if(anaIN_D==0){
            pos = 3;
          }
        }
      break;
      case 1:
        j++;
        if(j==anaIN_A){
          pos = 2;
          j = 0;
          if(anaIN_D==0){
            pos = 3;
          }
        }
      break;
      case 2:
        j++;
        if(j>=anaIN_D){pos = 3;}
      break;
    }
    switch (shape){
      case 1:
        for(i=0;i<=n/2;i++){
          DACOUT_f = sin(i*2*3.14/n)*4096;
          DACOUT_f = DACOUT_f * anaIN_M / 1024;
          if((pos==1)&&(anaIN_A!=0)){DACOUT_f = DACOUT_f * (j+1) / anaIN_A;}
          else if((pos==2)&&(anaIN_D!=0)){DACOUT_f = DACOUT_f * (1.0 + (anaIN_S - 1.0 ) * (float(j+1) / anaIN_D));}
          else if(pos==3){DACOUT_f = DACOUT_f * anaIN_S;}
          DACOUT = int(DACOUT_f);
          if(DACOUT<0){break;}
          analogWrite(DAC0,DACOUT);
        }
        for(;i<n;i++){
          DACOUT_f = sin(i*2*3.14/n)*4096;
          DACOUT_f = DACOUT_f * anaIN_M / 1024;
          if((pos==1)&&(anaIN_A!=0)){DACOUT_f = DACOUT_f * (j+1) / anaIN_A;}
          else if((pos==2)&&(anaIN_D!=0)){DACOUT_f = DACOUT_f * (1.0 + (anaIN_S - 1.0 ) * (float(j+1) / anaIN_D));}
          else if(pos==3){DACOUT_f = DACOUT_f * anaIN_S;}
          DACOUT = int(DACOUT_f) * -1;
          analogWrite(DAC1,DACOUT);
        }
      break;
      case 2:
        for(i=0;i<(n/2);i++){
          DACOUT_f = 4096.0 * anaIN_M / 1024;
          if((pos==1)&&(anaIN_A!=0)){DACOUT_f = DACOUT_f * (j+1) / anaIN_A;}
          else if((pos==2)&&(anaIN_D!=0)){DACOUT_f = DACOUT_f * (1.0 + (anaIN_S - 1.0 ) * (float(j+1) / anaIN_D));}
          else if(pos==3){DACOUT_f = DACOUT_f * anaIN_S;}
          DACOUT = int(DACOUT_f);
          analogWrite(DAC0,DACOUT);
        }
        for(;i<n;i++){
          DACOUT_f = -4096.0 * anaIN_M / 1024;
          if((pos==1)&&(anaIN_A!=0)){DACOUT_f = DACOUT_f * (j+1) / anaIN_A;}
          else if((pos==2)&&(anaIN_D!=0)){DACOUT_f = DACOUT_f * (1.0 + (anaIN_S - 1.0 ) * (float(j+1) / anaIN_D));}
          else if(pos==3){DACOUT_f = DACOUT_f * anaIN_S;}
          DACOUT = int(DACOUT_f) * -1;
          analogWrite(DAC1,DACOUT);
        }
      break;
      case 3:
        for(i=0;i<(n/4);i++){
          DACOUT_f = 4096.0 * 4 * i / n;
          DACOUT_f = DACOUT_f * anaIN_M / 1024;
          if((pos==1)&&(anaIN_A!=0)){DACOUT_f = DACOUT_f * (j+1) / anaIN_A;}
          else if((pos==2)&&(anaIN_D!=0)){DACOUT_f = DACOUT_f * (1.0 + (anaIN_S - 1.0 ) * (float(j+1) / anaIN_D));}
          else if(pos==3){DACOUT_f = DACOUT_f * anaIN_S;}
          DACOUT = int(DACOUT_f);
          analogWrite(DAC0,DACOUT);
        }
        for(;i<(n/2);i++){
          DACOUT_f = 4096.0 - 4096.0 * 4 * (i-n/4) / n;
          DACOUT_f = DACOUT_f * anaIN_M / 1024;
          if((pos==1)&&(anaIN_A!=0)){DACOUT_f = DACOUT_f * (j+1) / anaIN_A;}
          else if((pos==2)&&(anaIN_D!=0)){DACOUT_f = DACOUT_f * (1.0 + (anaIN_S - 1.0 ) * (float(j+1) / anaIN_D));}
          else if(pos==3){DACOUT_f = DACOUT_f * anaIN_S;}
          DACOUT = int(DACOUT_f);
          analogWrite(DAC0,DACOUT);
        }
        for(;i<(n*3/4);i++){
          DACOUT_f = 4096.0 * 4 * (i-n/2) / n;
          DACOUT_f = DACOUT_f * anaIN_M / 1024;
          if((pos==1)&&(anaIN_A!=0)){DACOUT_f = DACOUT_f * (j+1) / anaIN_A;}
          else if((pos==2)&&(anaIN_D!=0)){DACOUT_f = DACOUT_f * (1.0 + (anaIN_S - 1.0 ) * (float(j+1) / anaIN_D));}
          else if(pos==3){DACOUT_f = DACOUT_f * anaIN_S;}
          DACOUT = int(DACOUT_f);
          analogWrite(DAC1,DACOUT);
        }
        for(;i<n;i++){
          DACOUT_f = 4096.0 - 4096.0 * 4 * (i-n*3/4) / n;
          DACOUT_f = DACOUT_f * anaIN_M / 1024;
          if((pos==1)&&(anaIN_A!=0)){DACOUT_f = DACOUT_f * (j+1) / anaIN_A;}
          else if((pos==2)&&(anaIN_D!=0)){DACOUT_f = DACOUT_f * (1.0 + (anaIN_S - 1.0 ) * (float(j+1) / anaIN_D));}
          else if(pos==3){DACOUT_f = DACOUT_f * anaIN_S;}
          DACOUT = int(DACOUT_f);
          analogWrite(DAC1,DACOUT);
        }
      break;
      case 4:
        for(i=0;i<n/2;i++){
          DACOUT_f = 4096.0 * 2 * i / n;
          DACOUT_f = DACOUT_f * anaIN_M / 1024;
          if((pos==1)&&(anaIN_A!=0)){DACOUT_f = DACOUT_f * (j+1) / anaIN_A;}
          else if((pos==2)&&(anaIN_D!=0)){DACOUT_f = DACOUT_f * (1.0 + (anaIN_S - 1.0 ) * (float(j+1) / anaIN_D));}
          else if(pos==3){DACOUT_f = DACOUT_f * anaIN_S;}
          DACOUT = int(DACOUT_f);
          analogWrite(DAC0,DACOUT);
        }
        for(;i<n;i++){
          DACOUT_f = -4096.0 + 4096.0 * 2 * (i-n/2) / n;
          DACOUT_f = DACOUT_f * anaIN_M / 1024;
          if((pos==1)&&(anaIN_A!=0)){DACOUT_f = DACOUT_f * (j+1) / anaIN_A;}
          else if((pos==2)&&(anaIN_D!=0)){DACOUT_f = DACOUT_f * (1.0 + (anaIN_S - 1.0 ) * (float(j+1) / anaIN_D));}
          else if(pos==3){DACOUT_f = DACOUT_f * anaIN_S;}
          DACOUT = int(DACOUT_f) * -1;
          analogWrite(DAC1,DACOUT);
        }
      break;
    }
  }
  else{
    if(pos==3){
      for(j=anaIN_R;j>0;j--){
        switch (shape){
        case 1:
          for(i=0;i<n/2;i++){
            DACOUT_f = sin(i*2*3.14/n)*4096;
            DACOUT_f = DACOUT_f * anaIN_M / 1024;
            DACOUT_f = DACOUT_f * anaIN_S;
            DACOUT_f = DACOUT_f * j / anaIN_A;
            DACOUT = int(DACOUT_f);
            if(DACOUT<0){break;}
            analogWrite(DAC0,DACOUT);
          }
          for(;i<n;i++){
            DACOUT_f = sin(i*2*3.14/n)*4096;
            DACOUT_f = DACOUT_f * anaIN_M / 1024;
            DACOUT_f = DACOUT_f * anaIN_S;
            DACOUT_f = DACOUT_f * j / anaIN_A;
            DACOUT = int(DACOUT_f) * -1;
            analogWrite(DAC1,DACOUT);
          }
        break;
        case 2:
          for(i=0;i<(n/2);i++){
            DACOUT_f = 4096.0 * anaIN_M / 1024;
            DACOUT_f = DACOUT_f * anaIN_S;
            DACOUT_f = DACOUT_f * j / anaIN_A;
            DACOUT = int(DACOUT_f);
            analogWrite(DAC0,DACOUT);
          }
          for(;i<n;i++){
            DACOUT_f = -4096.0 * anaIN_M / 1024;
            DACOUT_f = DACOUT_f * anaIN_S;
            DACOUT_f = DACOUT_f * j / anaIN_A;
            DACOUT = int(DACOUT_f) * -1;
            analogWrite(DAC1,DACOUT);
          }
        break;
        case 3:
          for(i=0;i<(n/4);i++){
            DACOUT_f = 4096.0 * 4 * i / n;
            DACOUT_f = DACOUT_f * anaIN_M / 1024;
            DACOUT_f = DACOUT_f * anaIN_S;
            DACOUT_f = DACOUT_f * j / anaIN_A;
            DACOUT = int(DACOUT_f);
            analogWrite(DAC0,DACOUT);
          }
          for(;i<(n/2);i++){
            DACOUT_f = 4096.0 - 4096.0 * 4 * (i-n/4) / n;
            DACOUT_f = DACOUT_f * anaIN_M / 1024;
            DACOUT_f = DACOUT_f * anaIN_S;
            DACOUT_f = DACOUT_f * j / anaIN_A;
            DACOUT = int(DACOUT_f);
            analogWrite(DAC0,DACOUT);
          }
          for(;i<(n*3/4);i++){
            DACOUT_f = 4096.0 * 4 * (i-n/2) / n;
            DACOUT_f = DACOUT_f * anaIN_M / 1024;
            DACOUT_f = DACOUT_f * anaIN_S;
            DACOUT_f = DACOUT_f * j / anaIN_A;
            DACOUT = int(DACOUT_f);
            analogWrite(DAC1,DACOUT);
          }
          for(;i<n;i++){
            DACOUT_f = 4096.0 - 4096.0 * 4 * (i-n*3/4) / n;
            DACOUT_f = DACOUT_f * anaIN_M / 1024;
            DACOUT_f = DACOUT_f * anaIN_S;
            DACOUT_f = DACOUT_f * j / anaIN_A;
            DACOUT = int(DACOUT_f);
            analogWrite(DAC1,DACOUT);
          }
        break;
        case 4:
          for(i=0;i<n/2;i++){
            DACOUT_f = 4096.0 * 2 * i / n;
            DACOUT_f = DACOUT_f * anaIN_M / 1024;
            DACOUT_f = DACOUT_f * anaIN_S;
            DACOUT_f = DACOUT_f * j / anaIN_A;
            DACOUT = int(DACOUT_f);
            analogWrite(DAC0,DACOUT);
          }
          for(;i<n;i++){
            DACOUT_f = -4096.0 + 4096.0 * 2 * (i-n/2) / n;
            DACOUT_f = DACOUT_f * anaIN_M / 1024;
            DACOUT_f = DACOUT_f * anaIN_S;
            DACOUT_f = DACOUT_f * j / anaIN_A;
            DACOUT = int(DACOUT_f) * -1;
            analogWrite(DAC1,DACOUT);
          }
        break;
      }
     }
    }
    pos = 0;
    j = 0;
  }
  on = 0;
}
