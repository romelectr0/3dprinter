#include <PCD8544.h>
#include <AFMotor.h>
AF_Stepper motor1(48,2);
AF_Stepper motor2(48,1);
static PCD8544 lcd(9,10,A5,A4,A3);
static const byte line = {255};
static const byte bottom = {1};
static const byte top = {B1000000};
boolean advencement;
int historyint[5][2];
int goodthermistval;
String historystring[5][2];
int chip1 = 7;
int chip2 = 2;
int advencebyrev = 1/20;
int dvdmotorstepperr = 20;
int motor1stepperrev;
int motor2stepperrev = 48;
int motor3stepperrev;
int motor4stepperrev = 20; 
char bufferr[64];  
int sofar;  
int heater = A0;
boolean heat = false;
boolean heating = false;
int normale;
void setup() {
  lcd.begin(84,48);
  //lcd.setInverse(true);
  pinMode(heater,OUTPUT);
  digitalWrite(heater,HIGH);
  Serial.begin(9600);
  digitalWrite(chip1,HIGH);
  digitalWrite(chip2,HIGH);
}
void loop () {
  while(Serial.available() > 0) {  
    char c=Serial.read();  
    if(sofar<64) bufferr[sofar++]=c;
    advencement = true;
    if(bufferr[sofar-1]==';') break;  
    if (bufferr[sofar] == '\n') break;
    Serial.flush();
  }
if (Serial.available() == 0) {
  heat = heatval(heat);
    if (heat && digitalRead(A1) > goodthermistval && heating) {
        digitalWrite(heater,LOW);
        heating = false;
      }
      else if (heat && digitalRead(A1) < goodthermistval && heating == false) {
         digitalWrite(heater,HIGH);
         heating = true;
        }
        else if (heat == false && (heating || digitalRead(A1) > normale)) {
            digitalWrite(heater,LOW);
            heating = false;
          }
const char printval[6] = {'M','G','X','Y','Z','E'};
const char intval[5] = {'G','M','P','S','T'};
const char floatval[5] = {'X','Y','Z','E','F'};
   for(int b = 0;b < 5;b++) {
      historystring[b][1] = stringval(bufferr,floatval[b]);
      historyint[b][1] = giveintval(bufferr,intval[b]);
    }
  for(int n = 0;n <6;n++) {
  lcd.setCursor(0,n);
  lcd.clearLine();
  lcd.print(printval[n]);
  lcd.print(" : ");
  if (n == 0) {
    lcd.print(historyint[1][1]);
  }
  else if (n == 1) {
    lcd.print(historyint[0][1]);
  }
  else if(n == 2) {
    if (!(historystring[0][1] == " ")) {
    lcd.print(historystring[0][1]);
    }
    else {
        lcd.print(historystring[0][0]);
      }
  }
  else if (n == 3) {
    if (!(historystring[1][1] == " ")) {
    lcd.print(historystring[1][1]);
    }
    else {
      lcd.print(historystring[1][0]);
      }
  }
  else if (n == 4) {
    if (!(historystring[2][1] == " ")) {
    lcd.print(historystring[2][1]);
    }
    else {
      lcd.print(historystring[2][0]);
      }
  }
  else if(n == 5) {
    if (!(historystring[3][1] == " ")) {
    lcd.print(historystring[3][1]);
    }
    else {
      lcd.print(historystring[3][0]);
      }
  }
  }
  if (((stringtofloat(historystring[0][0]) != stringtofloat(historystring[0][1])) || (stringtofloat(historystring[1][0]) != stringtofloat(historystring[1][1])) || (stringtofloat(historystring[2][0]) != stringtofloat(historystring[2][1]))) && advencement == true) {
       if (stringtofloat(historystring[2][0]) != stringtofloat(historystring[2][1])) {
           
         }
      float distancex = sqrt(pow(stringtofloat(historystring[0][1])-stringtofloat(historystring[0][0]),2));
       float distancey = sqrt(pow(stringtofloat(historystring[1][1])-stringtofloat(historystring[1][0]),2));
       float distancexy = 2*sqrt(0.25*(pow(distancex,2)+pow(distancey,2)));
       float stepx = distancex*48;
       float stepy = distancey*48;
       int stepxy = distancexy*48;
       int ratiox = distancex/distancexy;
       int ratioy = distancey/distancexy;
       Serial.print("X 0");
       Serial.println(historystring[0][0]);
       Serial.print("X 1");
       Serial.println(historystring[0][1]);
       Serial.print("Y 0");
       Serial.println(historystring[1][0]);
       Serial.print("Y 1");
       Serial.println(historystring[1][1]);
       Serial.print(" distance x :");
       Serial.println(distancex);
       Serial.print("distance y :");
       Serial.println(distancey);
       Serial.print("distance x - y :");
       Serial.println(distancexy);
       Serial.print("step x - y :");
       Serial.println(stepxy);
       for(int f = 0;f < stepxy;f++) {
       if (stringtofloat(historystring[0][0]) != stringtofloat(historystring[0][1])) {
         digitalWrite(chip1,LOW);
         digitalWrite(chip2,HIGH);
         motor1.setSpeed(stringtofloat(historystring[4][1])/2);
       if (stringtofloat(historystring[0][1]) > stringtofloat(historystring[0][0])) {
           motor1.onestep(FORWARD,SINGLE);
         }
         else {
           motor1.onestep(BACKWARD,SINGLE);
           }
           }
           if (stringtofloat(historystring[1][0]) != stringtofloat(historystring[1][1])) {
             digitalWrite(chip1,LOW);
             digitalWrite(chip2,HIGH);
             motor2.setSpeed(stringtofloat(historystring[4][1])/2);
           if (stringtofloat(historystring[0][1]) > stringtofloat(historystring[0][0])) {
             motor2.onestep(FORWARD,SINGLE);
            }
            else {
                motor1.onestep(BACKWARD,SINGLE);
              }
            }
            if (stringtofloat(historystring[1][1]) != 0) {
                digitalWrite(chip1,HIGH);
                digitalWrite(chip2,LOW);
                motor1.setSpeed(stringtofloat(historystring[3][1])/2);
                motor1.onestep(FORWARD,SINGLE);
              }
    }
    advencement = false;
      for(int b = 0;b < 5;b++) {
      historystring[b][0] = historystring[b][1];
      historyint[b][0] = historyint[b][1];
      }
    }
  bufferr[sofar]=0;
     for(int u = 0;u < 64;u++) bufferr[u] = ' ';
     sofar = 0;
     Serial.flush();
     }
     delay(1000);
    Serial.println("ok");
    
}
void movemotor(int tour,uint8_t arg,uint8_t type,int motor,int motorspeed){
  
  if (motor == 1 && 2) {
    digitalWrite(chip2,HIGH);
    digitalWrite(chip1,LOW);
    if (motor == 1) {
      AF_Stepper motor1(motor1stepperrev,1);
      motor1.setSpeed(motorspeed);
      motor1.step(tour,arg,type);
  }
    else {
      AF_Stepper motor2(motor2stepperrev,2);
      motor2.setSpeed(motorspeed);
      motor2.step(tour,arg,type);
    }
  }
  else {
    digitalWrite(chip2,LOW);
    digitalWrite(chip1,HIGH);
    if (motor == 3) {
      AF_Stepper motor3(motor3stepperrev,1);
      motor3.setSpeed(motorspeed);
      motor3.step(tour,arg,type);
    }
    else {
      AF_Stepper motor4(motor4stepperrev,2);
      motor4.setSpeed(motorspeed);
      motor4.step(tour,arg,type);
    }
  }
}
int chartoint(char character) {
  return(character-48);
}
float chartofloat(char* chararray) {
  float currentfloat = 0;
  for(int u = 0;u < sizeof(chararray);u++) {
    if (chararray[sizeof(chararray)-u] >= '0' && chararray[sizeof(chararray)-u] <= '9') currentfloat = currentfloat + (chararray[sizeof(chararray)-u] - 48)*pow(10,u+1);
    else if (chararray[sizeof(chararray)-u] == '.') currentfloat = currentfloat*pow(10,(-(u+1)));
    else {
    }
  }
}
int arraychartoint(char* chararray) {
  float currentint = 0;
  for(int u = 0;u < sizeof(chararray);u++) {
    if (chararray[sizeof(chararray)-u] >= '0' && chararray[sizeof(chararray)-u] <= '9') currentint = currentint + (chararray[sizeof(chararray)-u] - 48)*pow(10,u+1);
    if (u-1 == sizeof(chararray)) {
      return(currentint);
    }
  }
}
float stringtofloat(String string) {
    String dec = string;
    String frac = string;
    int virg = string.indexOf('.',virg);
    frac.remove(0,virg+1);
    dec.remove(virg);
    float val = float(dec.toInt());
    float fracfloat = float(frac.toInt())/pow(10,frac.length());
    return(val+fracfloat);
  }
  char* nullbufffer(char* arraytoflush) {
    char* buffertosend;
    }
float givefloatval(char buf[64],char chartofind) {
          String string = String(buf);
          for(int k = 0;k < 64;k++) {
           if (buf[k] == chartofind) {
          string.remove(0,k+1);
          char bufffer[64] ;
          string.toCharArray(bufffer,64);
          return(atof(bufffer));
          }
          }
          //return(0);
    }  
    int giveintval(char buf[64],char chartofind)  {
          String string = String(buf);
          for(int k = 0;k < 64;k++) {
            if (buf[k] == chartofind) {
          string.remove(0,k+1);
          return(string.toInt());
          }
          }
          return(0);
      }
String stringval(char buf[64],char chartofind) {
      String string = String(buf);
          for(int k = 0;k < 64;k++) {
          if (buf[k] == chartofind) {
          string.remove(0,k+1);
          int stopmoment = string.indexOf(' ');
          string.remove(stopmoment);
          return(string);
          }
          }
          return(" ");
  }
  boolean heatval (boolean curentheat) {
      for(int h = 0;h < 64;h++) {
      if (bufferr[h] == 'S') {
          if (stringtofloat(stringval(bufferr,'S')) != 0) {
              digitalWrite(heater,HIGH);
              return(true);
            }
            else {
              digitalWrite(heater,LOW);
               return(false);
              }
        }
    }
    return(curentheat);
    }
