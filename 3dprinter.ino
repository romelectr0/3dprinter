#include <newascii.h>
#include <AFMotor.h>
AF_Stepper motor1(48,2);
AF_Stepper motor2(48,1);
static PCD8544 lcd(9,10,A5,A4,A3);
static const byte line = {255};
static const byte bottom = {1};
boolean advencement;
int historyint[5][2];
String historystring[5][2];
int chip1 = 7;
int chip2 = 2;
int advencebyrev = 1/20;
int dvdmotorstepperr = 20;
int motor1stepperrev;
int motor2stepperrev = 48;
int motor3stepperrev;
int motor4stepperrev = 20;
float mmperrev = 1;
char bufferr[64];
int sofar;  
int heater = A0;
boolean heat = false;
boolean heating = false;
int normale;
int goodthermistval = 500;
void setup() {
  lcd.begin(84,48);
  Serial.begin(9600);
  digitalWrite(chip1,HIGH);
  digitalWrite(chip2,HIGH);
  /*lcd.setInverse(true);
  lcd.drawBitmap(random,84,48);
  delay(1000);*/
  lcd.setCursor(0,1);
  lcd.clearLine();
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
  Serial.println("heat value : ");
  Serial.print(heat);
  Serial.println("thermist val : ");
  Serial.print(digitalRead(A1));
    if (heat == true && digitalRead(A1) > goodthermistval && heating == true) {
        digitalWrite(heater,LOW);
        heating = false;
      }
      else if (heat == true && digitalRead(A1) < goodthermistval && heating == false) {
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
      for(int s = 0;s < 64;s++) {
       if (bufferr[s] == floatval[b]) {
      historystring[b][1] = stringval(bufferr,floatval[b]);
      }
        if (bufferr[s] == intval[b]) {
       if (stringval(bufferr,intval[b]) != " ") {
      historyint[b][1] = giveintval(bufferr,intval[b]);
      }
      }
      }
    }
  for(int n = 0;n <3;n++) {
  lcd.setCursor(0,n);
  lcd.clearLine();
  lcd.print(printval[n+2]);
  lcd.print(" : ");
 if(n == 0) {
    if (!(historystring[0][1] == " ")) {
    lcd.print(historystring[0][1]);
    }
    else {
        lcd.print(historystring[0][0]);
      }
  }
  else if (n == 1) {
    if (!(historystring[1][1] == " ")) {
    lcd.print(historystring[1][1]);
    }
    else {
      lcd.print(historystring[1][0]);
      }
  }
  else if (n == 2) {
    if (!(historystring[2][1] == " ")) {
    lcd.print(historystring[2][1]);
    }
    else {
      lcd.print(historystring[2][0]);
      }
  }
  }
  if (((stringtofloat(historystring[0][0]) != stringtofloat(historystring[0][1])) || (stringtofloat(historystring[1][0]) != stringtofloat(historystring[1][1])) || (stringtofloat(historystring[2][0]) != stringtofloat(historystring[2][1]))) && advencement == true) {
      float distancex = sqrt(pow(stringtofloat(historystring[0][1])-stringtofloat(historystring[0][0]),2));
       float distancey = sqrt(pow(stringtofloat(historystring[1][1])-stringtofloat(historystring[1][0]),2));
       float distancexy = 2*sqrt(0.25*(pow(distancex,2)+pow(distancey,2)));
       float stepx = distancex*(motor2stepperrev/mmperrev);
       float stepy = distancey*(motor2stepperrev/mmperrev);
       int stepxy = distancexy*(motor2stepperrev/mmperrev);
       float ratiox = distancex/(distancex+distancey);
       float ratioy = distancey/(distancex+distancey);
       float ratiomultiplicator = ratiomultiplier(ratiox,ratioy,stepxy);
       int nbsteploop = numberstepperloop(ratiomultiplicator,ratiox,ratioy);
       int numberloop = numberofloop(stepxy,nbsteploop);
       Serial.print("ratio x");
       Serial.println(ratiox);
       Serial.print("ratio y");
       Serial.println(ratioy);
       Serial.print("ratiomultiplicator : ");
       Serial.println(ratiomultiplicator);
       Serial.print("nbsteploop : ");
       Serial.println(nbsteploop);
       Serial.print("numberloop : ");
       Serial.println(numberloop);
       Serial.print("X step : ");
       Serial.println(ratiomultiplicator*ratiox*numberloop);
       Serial.print("Y step : ");
       Serial.println(ratiomultiplicator*ratioy*numberloop);
       Serial.print("Z step : ");
       Serial.println((stringtofloat(historystring[2][1])-stringtofloat(historystring[2][0]))*48);
       if (stringtofloat(historystring[2][0]) != stringtofloat(historystring[2][1])) {
           digitalWrite(chip1,LOW);
           digitalWrite(chip2,HIGH);
           motor2.setSpeed(30);
           motor2.step(sqrt(pow(stringtofloat(historystring[2][1])-stringtofloat(historystring[2][0]),2))*48,FORWARD,SINGLE);
         }
       for(int f = 0;f < numberloop;f++) {
       if (ratiox != 0) {
         digitalWrite(chip1,LOW);
         digitalWrite(chip2,HIGH);
         motor1.setSpeed(stringtofloat(historystring[4][1])/2);
         for(int j= 0;j < ratiomultiplicator*ratiox;j++) {
       if (stringtofloat(historystring[0][1]) > stringtofloat(historystring[0][0])) {
           motor1.onestep(FORWARD,SINGLE);
         }
         else {
           motor1.onestep(BACKWARD,SINGLE);
           }
           }
           }
           if (ratioy != 0) {
             digitalWrite(chip1,LOW);
             digitalWrite(chip2,HIGH);
             motor2.setSpeed(stringtofloat(historystring[4][1])/2);
             for(int j = 0;j < ratiomultiplicator*ratioy;j++) {
           if (stringtofloat(historystring[0][1]) > stringtofloat(historystring[0][0])) {
             motor2.onestep(FORWARD,SINGLE);
            }
            else {
                motor2.onestep(BACKWARD,SINGLE);
              }
            }
            }
            if (stringtofloat(historystring[3][1]) != 0) {
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
      delay(500);
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
  float ratiomultiplier(float ratioofx,float ratioofy,float numberofstep) {
    float ecart[10][2];
    float mediumecart[10];
    int lowestval[10];
    int lowval;
      for(int q = 1;q < 11;q++) {
          ecart[q-1][0] = (ratioofx-(int(ratioofx)))*q;
          ecart[q-1][1] = (ratioofy-(int(ratioofy)))*q;
          mediumecart[q-1] = (ecart[q-1][0]+ecart[q-1][1])/2;
          if (q == 10) {
          for(int m = 0;m <10;m++) {
          lowval = 0;
          for(int h = 0;h <10;h++) {
            if (mediumecart[m] < mediumecart[h]) {
             lowestval[m] = lowval;
             lowval++;
          }
          }
          if (m == 9) {
                   for(int h = 1;h < 10;h++) {
                       for(int l = 0;l < 10;l++) {
                           if (lowestval[l] == h && (l+1)*(ratioofx+ratioofy) <= numberofstep) {
                             return(l+1);
                          }
                        }
                     }
                     return(0);
                   }
                }
              }
            }
          }
    int numberstepperloop(float ratio_multiplier,float ratioofx,float ratioofy) {
        return(ratio_multiplier*(ratioofx+ratioofy));
      }
      int numberofloop(float numberofstep,int numbersteploop) {
          return(numberofstep/numbersteploop);
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
