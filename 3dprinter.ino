#include <PCD8544.h>
//#include <AFMotor.h>
#include<math.h>
#define buffersize 70
#define ratioscale 20
//AF_Stepper motor1(48,2);
//AF_Stepper motor2(48,1);
static PCD8544 lcd(9,10,A5,A4,A3);
static const byte line = {255};
static const byte bottom = {1};
static const byte apple[] = {/*0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xF7, 0xE7, 0x47, 0x07, 0x07, 0x0F, 0x0F, 0x3F, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x0F, 0x0F, 0x07, 0x07, 0x47, 0xE7, 0xF7, 0xE7, 0xFF,
0xFF, 0xFF, 0xFF, 0x7F, 0xFC, 0xF0, 0xE0, 0xC1, 0x83, 0x83, 0x81, 0x80, 0x80, 0x80, 0x00, 0x00,
0x00, 0x00, 0x02, 0x07, 0x0F, 0x0F, 0x5F, 0x3F, 0x1F, 0x1F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x1F, 0x1F, 0x3F, 0x5F, 0x0F, 0x0F, 0x07, 0x02, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80,
0x80, 0x81, 0x83, 0x83, 0xC1, 0xE0, 0xF0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0x78, 0x08, 0x00, 0x01, 0x00, 0x80, 0xC0, 0xC0, 0xC0, 0x80, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x01, 0x00, 0x08, 0x78, 0xFE,
0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x1C, 0x20, 0x80, 0x00, 0x00, 0x07, 0x07,
0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x07, 0x07, 0x00, 0x00,
0x80, 0x20, 0x1C, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x3F, 0x0F, 0x07, 0x83, 0xC1, 0xC1, 0x81, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x40, 0xE0,
0xF0, 0xF0, 0xE0, 0xC0, 0x80, 0x80, 0xC0, 0xE0, 0xC0, 0x80, 0x80, 0xC0, 0xE0, 0xC0, 0x80, 0x80,
0xC0, 0xE0, 0xF0, 0xF0, 0xE0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x81, 0xC1, 0xC1,
0x83, 0x07, 0x0F, 0x3F, 0xFE, 0xFF, 0xFE, 0xFF, 0xFF, 0xEF, 0xEF, 0xE7, 0xE2, 0xE0, 0xE0, 0xF0,
0xF0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF0, 0xF0, 0xE0, 0xE0, 0xE2,
0xE7, 0xEF, 0xEF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFE*/
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xE0, 0xF0, 0xB0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0xC0, 0xC8, 0xCF, 0xCF,
0xC7, 0xE3, 0xE1, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xE0, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0B, 0x03, 0x01, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB,
0xF8, 0xA0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x1F, 0x7F, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x5F, 0x1F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
boolean advencement;
int historyint[5][2];
String historystring[5][2];
//int chip1 = 7;
//int chip2 = 2;
int advencebyrev = 1/20;
int dvdmotorstepperr = 20;
int motor1stepperrev;
int motor2stepperrev = 48;
int motor3stepperrev;
int motor4stepperrev = 20;
float mmperrev = 1;
char bufferr[buffersize];
int sofar;  
int heater = A0;
float heat = 0;
boolean heating = false;
int normale;
int goodthermistval = 500;
const char printval[6] = {'M','G','X','Y','Z','E'};
const char intval[5] = {'G','M','P','S','T'};
const char floatval[5] = {'X','Y','Z','E','F'};
char newbuffer[buffersize];
int newsofar;
boolean check;
boolean calibration = false;
float rayon = 1;
float stepdist = 1/400;
float pi = 3.141592;
int dirpin = 2;
int steppin = 3;
int xmotor = 4;
int ymotor = 5;
int zmotor = 6;
int emotor = 7;
int ms1 = 8;
int ms2 = 11;
boolean extrudermod;
float extruderspeed = 0;
float steptime;
float motorspeed;
void setup() {
  lcd.begin(84,48);
  Serial.begin(9600);
  //digitalWrite(chip1,HIGH);
  //digitalWrite(chip2,HIGH);
  /*lcd.setInverse(true);
  lcd.drawBitmap(random,84,48);
  delay(1000);*/
  pinMode(heater,OUTPUT);
  pinMode(dirpin,OUTPUT);
  pinMode(steppin,OUTPUT);
  pinMode(xmotor,OUTPUT);
  pinMode(ymotor,OUTPUT);
  pinMode(zmotor,OUTPUT);
  pinMode(emotor,OUTPUT);
  pinMode(ms1,OUTPUT);
  pinMode(ms2,OUTPUT);
  lcd.setCursor(0,1);
  lcd.clearLine();
  lcd.setCursor(0,0);
  lcd.drawBitmap(apple,84,48);
  for(int i= 0;i < 5;i++) {
      historystring[i][0] = " ";
    }
  digitalWrite(xmotor,HIGH);
  digitalWrite(ymotor,HIGH);
  digitalWrite(zmotor,HIGH);
  digitalWrite(emotor,HIGH);
}
void loop () {
while(true) {
  while(Serial.available() > 0) {  
    char c=Serial.read();  
    if(sofar<buffersize) bufferr[sofar++]=c; 
    advencement = true;
    if(bufferr[sofar-1]==';') break;  
    if (bufferr[sofar] == '\n') break;
    Serial.flush();
  }
 if (havesomething() || bufferr[0] == '$') {
     if (bufferr[0] != '$') {
          calibration = false;
       }
       else {
           calibration = true;
         }
      break;
    }
  }
  lcd.clear();
  while(true) {
   extrudermod = getextrudermod(extrudermod);
   extruderspeed = getextruderspeed(extruderspeed);
if (havesomething() || check == false) {
  if (bufferr[0] == '$') {
  historystring[4][1] = "240";
  }
  check = true;
  if (bufferr[0] != '$') {
  heat = heatval(heat);
  /*if (havesomething() == true) {
  Serial.println("heat value : ");
  Serial.print(heat);
  Serial.println("thermist val : ");
  Serial.print(digitalRead(A1));
  }*/
    if (heat > 0 && digitalRead(A1) > goodthermistval && heating == true) {
        digitalWrite(heater,LOW);
        heating = false;
      }
      else if (heat > 0 && digitalRead(A1) < goodthermistval && heating == false) {
         digitalWrite(heater,HIGH);
         heating = true;
        }
        else if (heat == 0 && (heating || digitalRead(A1) > normale)) {
            digitalWrite(heater,LOW);
            heating = false;
          }
   for(int b = 0;b < 5;b++) {
      for(int s = 0;s < buffersize;s++) {
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
  }
  if ((((stringtofloat(historystring[0][0]) != stringtofloat(historystring[0][1])) || (stringtofloat(historystring[1][0]) != stringtofloat(historystring[1][1])) || (stringtofloat(historystring[2][0]) != stringtofloat(historystring[2][1]))) && advencement == true) || bufferr[0] == '$') {
    if (stringtofloat(historystring[4][1]) > 0) {
        motorspeed = stringtofloat(historystring[4][1]);
      }
      else {
          motorspeed = stringtofloat(historystring[4][0]);
        }
    steptime = motorspeed/600;
    float distancexye;
    float distancexe;
    float distanceye;
    float distancexy;
      float stepxye;
      float stepxe;
      float stepye;
      float stepxy;
      float ratiox;
      float ratioy;
      float ratioe;
      float ratiomultiplicator;
      int nbsteploop;
      int numberloop;
      float distancex;
      float distancee = stringtofloat(historystring[3][1]);
      float distancey;
      if (bufferr[0] != '$') {
       distancex = sqrt(pow((stringtofloat(historystring[0][1])-stringtofloat(historystring[0][0])),2));
       distancey = sqrt(pow((stringtofloat(historystring[1][1])-stringtofloat(historystring[1][0])),2));
       }
       else {
           distancex = stringtofloat(stringval(bufferr,'X'));
           distancey = stringtofloat(stringval(bufferr,'Y'));
         }
       float stepx = (distancex*400)/(rayon*2*pi);
       float stepy = (distancey*400)/(rayon*2*pi);
       if (bufferr[0] == '$') {
         Serial.println("calibration mode ");
         }
         Serial.print("X : ");
        Serial.println(stringtofloat(historystring[0][1]));
        Serial.print("Y : ");
        Serial.println(stringtofloat(historystring[1][1]));
       Serial.print("distance x : ");
       Serial.println(distancex);
       Serial.print("distance y  : ");
       Serial.println(distancey);
       if (distancex == 0 && distancey != 0) {
           Serial.print("Y step : ");
           Serial.println(stepy);
           Serial.println("X step : 0");
           zprint();
         }
         else if (distancey == 0 && distancex != 0) {
             Serial.print("X step  : ");
             Serial.println(stepx);
             Serial.println("Y step : 0");
             zprint();
           }
         if (((distancex && distancey) != 0) || (bufferr[0] == '$' && ((stringtofloat(stringval(bufferr,'X')) && stringtofloat(stringval(bufferr,'Y'))) != 0))) {
       distancexy = distancex+distancey;
       stepxy = (distancexy*400)/(rayon*2*pi);
       //ratioe = distancee/(distancex+distancey+distancee);
       ratiox = distancex/(distancex+distancey);
       ratioy = distancey/(distancex+distancey);
       ratiomultiplicator = ratioscale/*ratiomultiplier(ratiox,ratioy,0,stepxy)*/;
       nbsteploop = numberstepperloop(ratiomultiplicator,ratiox,ratioy,0);
       numberloop = numberofloop(stepxy,nbsteploop);
       float steptimexy;
       steptimexy = ((steptime*distancexy)*500/stepxy);
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
       Serial.print("step time :");
       Serial.println(steptimexy);
       Serial.print("step xy :");
       Serial.println(stepxy);
       zprint();
       zrun(steptime);
       int inloop;
       if (distancee > 0) {
         float stepe = (distancee*400)/(rayon*2*pi);
         inloop = perfectstepparloop(stepe,0,numberloop,false);
         int outloop = numberloop/inloop;
         numberloop = outloop;
         }
         else {
           inloop = 1;
           }
       for(int f = 0;f < numberloop;f++) {
         if (distancee > 0) {
             digitalWrite(emotor,LOW);
             digitalWrite(dirpin,HIGH);
             digitalWrite(steppin,HIGH);
             delayMicroseconds(3);
             digitalWrite(steppin,LOW);
             digitalWrite(emotor,HIGH);
           }
      for(int h = 0;h < inloop;h++) {
     for(int j= 0;j < ratiomultiplicator*ratiox;j++) {
       if ((stringtofloat(historystring[0][1]) > stringtofloat(historystring[0][0])) || (stringtofloat(stringval(bufferr,'X')) > 0)) {
          digitalWrite(xmotor,LOW);
          digitalWrite(dirpin,HIGH);
          digitalWrite(steppin,HIGH);
          if (j == ratiomultiplicator*ratiox) {
            delayMicroseconds(steptimexy*1000);
          }
          else {
            delayMicroseconds(steptimexy*2000);
          }
          digitalWrite(steppin,LOW);
          digitalWrite(xmotor,HIGH);
         }
         else {
          digitalWrite(xmotor,LOW);
          digitalWrite(dirpin,LOW);
          digitalWrite(steppin,HIGH);
          if (j == ratiomultiplicator*ratiox) {
            delayMicroseconds(steptimexy*1000);
          }
          else {
           delayMicroseconds(steptimexy*2000);
          }
          digitalWrite(steppin,LOW);
          digitalWrite(xmotor,HIGH);
           }
           }
             for(int j = 0;j < ratiomultiplicator*ratioy;j++) {
           if ((stringtofloat(historystring[1][1]) > stringtofloat(historystring[1][0])) || (stringtofloat(stringval(bufferr,'Y')) > 0)) {
                        digitalWrite(ymotor,LOW);
                        digitalWrite(dirpin,HIGH);
                        digitalWrite(steppin,HIGH);
                        if (j == ratiomultiplicator*ratioy) {
                        delayMicroseconds(steptimexy*1000);
                        }
                        else {
                          delayMicroseconds(steptimexy*2000);
                          }
                        digitalWrite(steppin,LOW);
                        digitalWrite(ymotor,HIGH);
            }
            else {
                       digitalWrite(ymotor,LOW);
                        digitalWrite(dirpin,LOW);
                        digitalWrite(steppin,HIGH);
                        if (j == ratiomultiplicator*ratioy) {
                        delayMicroseconds(steptimexy*1000);
                        }
                        else {
                          delayMicroseconds(steptimexy*2000);
                          }
                        digitalWrite(steppin,LOW);
                        digitalWrite(ymotor,HIGH);
              }
            }
            /*if (bufferr[0] != '$' && distancee > 0) {
           for(int j = 0;j < ratiomultiplicator*ratioe;j++) {
            digitalWrite(emotor,LOW);
            digitalWrite(dirpin,HIGH);
            digitalWrite(steppin,HIGH);
            if (j == ratiomultiplicator*ratioe) {
              delayMicroseconds(steptimexye*1000);
            }
            else {
              delayMicroseconds(steptimexye*3000);
            }
            digitalWrite(steppin,LOW);
            digitalWrite(emotor,HIGH);
            }
            }*/
    }
    }
    }
  /*  else 

    if ((distancex == 0 && distancey != 0) || (bufferr[0] == '$' && (stringtofloat(stringval(bufferr,'X')) == 0 && stringtofloat(stringval(bufferr,'Y')) != 0))) {
             distanceye = sqrt(pow(distancey,2)+pow(distancee,2));
             stepye = (distanceye*400)/(rayon*2*pi);
             ratioy = distancey/(distancey+distancee);
             ratioe = distancee/(distancey+distancee);
             ratiomultiplicator = ratiomultiplier(0,ratioy,ratioe,stepye);
             nbsteploop = numberstepperloop(ratiomultiplicator,0,ratioy,ratioe);
             numberloop = numberofloop(stepye,nbsteploop);
             float steptimey;
             float steptimeye = ((steptime*distanceye)*500/stepye);
             if (bufferr[0] != '$' && (distancee > 0 || extrudermod == true)) {
                 for(int f = 0;f < numberloop;f++) {
                   for(int j = 0;j < ratiomultiplicator*ratioy;j++) {
                    if ((stringtofloat(historystring[1][1]) > stringtofloat(historystring[1][0])) || (stringtofloat(stringval(bufferr,'Y')) > 0)) {
                        digitalWrite(ymotor,LOW);
                        digitalWrite(dirpin,HIGH);
                        digitalWrite(steppin,HIGH);
                        delayMicroseconds(steptimeye*1000);
                        digitalWrite(steppin,LOW);
                        digitalWrite(ymotor,HIGH);
            }
            else {
                        digitalWrite(ymotor,LOW);
                        digitalWrite(dirpin,LOW);
                        digitalWrite(steppin,HIGH);
                        delayMicroseconds(steptimeye*1000);
                        digitalWrite(steppin,LOW);
                        digitalWrite(ymotor,HIGH);
              }
                     }
                   for(int j = 0;j < ratiomultiplicator*ratioe;j++) {
                        digitalWrite(emotor,LOW);
                        digitalWrite(dirpin,HIGH);
                        digitalWrite(steppin,HIGH);
                        delayMicroseconds(steptimeye*1000);
                        digitalWrite(steppin,LOW);
                        digitalWrite(emotor,HIGH);
                     }
                   }
               }
               else {
               steptimey  = (steptime*distancey)*1000/stepy;
             for(int j = 0;j < stepy;j++) {
           if ((stringtofloat(historystring[1][1]) > stringtofloat(historystring[1][0])) || (stringtofloat(stringval(bufferr,'Y')) > 0)) {
                        digitalWrite(ymotor,LOW);
                        digitalWrite(dirpin,HIGH);
                        digitalWrite(steppin,HIGH);
                        delayMicroseconds(steptimey*1000);
                        digitalWrite(steppin,LOW);
                        digitalWrite(ymotor,HIGH);
            }
            else {
                        digitalWrite(ymotor,LOW);
                        digitalWrite(dirpin,LOW);
                        digitalWrite(steppin,HIGH);
                        delayMicroseconds(steptimey*1000);
                        digitalWrite(steppin,LOW);
                        digitalWrite(ymotor,HIGH);
              }
              }
            }
      }
      else */if (((distancey == 0 && distancex != 0) || (bufferr[0] == '$' && (stringtofloat(stringval(bufferr,'Y')) == 0 && stringtofloat(stringval(bufferr,'X')) != 0))) || (distancex == 0 && distancey != 0) || (bufferr[0] == '$' && (stringtofloat(stringval(bufferr,'X')) == 0 && stringtofloat(stringval(bufferr,'Y')) != 0))) {
               zrun(steptime);
              int motorval;
             char motorprintval;
             int motorprincval;
             float distancemotore;
             float motordistance;
             float stepmotore;
             float ratiomotor;
             float motorstep;
        if ((distancey == 0 && distancex != 0) || (bufferr[0] == '$' && (stringtofloat(stringval(bufferr,'Y')) == 0 && stringtofloat(stringval(bufferr,'X')) != 0))) {
                 motorval = 0;
                 motorprintval = 'X';
                 motorprincval = xmotor;
                 motordistance = distancex;
                 motorstep = stepx;
               }
          else if ((distancex == 0 && distancey != 0) || (bufferr[0] == '$' && (stringtofloat(stringval(bufferr,'X')) == 0 && stringtofloat(stringval(bufferr,'Y')) != 0))) {
              motorval = 1;
              motorprintval = 'Y';
              motorprincval = ymotor;
              motordistance = distancey;
              motorstep = stepy;
            }
             distancemotore = sqrt(pow(motordistance,2)+pow(distancee,2));
             stepmotore = (distancemotore*400)/(rayon*2*pi);
             ratiomotor = motordistance/(motordistance+distancee); 
             ratioe = distancee/(motordistance+distancee);
             ratiomultiplicator = ratiomultiplier(ratiomotor,0,ratioe,stepmotore);
             nbsteploop = numberstepperloop(ratiomultiplicator,ratiomotor,0,ratioe);
             numberloop = numberofloop(stepmotore,nbsteploop);
             float steptimemotor;
             float steptimemotore = ((steptime*distancemotore)*500/stepmotore);
             if (bufferr[0] != '$' && distancee > 0 && extrudermod == false) {
               Serial.println("E extrusion mode");
                 for(int f = 0;f < numberloop;f++) {
                   for(int j = 0;j < ratiomultiplicator*ratiomotor;j++) {
                    if ((stringtofloat(historystring[motorval][1]) > stringtofloat(historystring[motorval][0])) || (stringtofloat(stringval(bufferr,motorprintval)) > 0)) {
                        digitalWrite(motorprincval,LOW);
                        digitalWrite(dirpin,HIGH);
                        digitalWrite(steppin,HIGH);
                        delayMicroseconds(steptimemotore*1000);
                        digitalWrite(steppin,LOW);
                        digitalWrite(motorprincval,HIGH);
            }
            else {
                        digitalWrite(motorprincval,LOW);
                        digitalWrite(dirpin,LOW);
                        digitalWrite(steppin,HIGH);
                        delayMicroseconds(steptimemotore*1000);
                        digitalWrite(steppin,LOW);
                        digitalWrite(motorprincval,HIGH);
              }
                     }
                   for(int j = 0;j < ratiomultiplicator*ratioe;j++) {
                        digitalWrite(emotor,LOW);
                        digitalWrite(dirpin,HIGH);
                        digitalWrite(steppin,HIGH);
                        delayMicroseconds(steptimemotore*1000);
                        digitalWrite(steppin,LOW);
                        digitalWrite(emotor,HIGH);
                     }
                   }
               }
               else if (distancee == 0 && extrudermod == false) {
                 Serial.println("no extrusion mod");
               steptimemotor  = (steptime*motordistance)*1000/motorstep;
             for(int j = 0;j < motorstep;j++) {
           if ((stringtofloat(historystring[motorval][1]) > stringtofloat(historystring[motorval][0])) || (stringtofloat(stringval(bufferr,motorprintval)) > 0)) {
                        digitalWrite(motorprincval,LOW);
                        digitalWrite(dirpin,HIGH);
                        digitalWrite(steppin,HIGH);
                        delayMicroseconds(steptimemotor*1000);
                        digitalWrite(steppin,LOW);
                        digitalWrite(motorprincval,HIGH);
            }
            else {
                        digitalWrite(motorprincval,LOW);
                        digitalWrite(dirpin,LOW);
                        digitalWrite(steppin,HIGH);
                        delayMicroseconds(steptimemotor*1000);
                        digitalWrite(steppin,LOW);
                        digitalWrite(motorprincval,HIGH);
              }
              }
            }
            else if (bufferr[0] != '$' && extrudermod == true) {
              Serial.println("M108 extrusion mod");
              if (sqrt(pow(stringtofloat(historystring[4][1]),2)) < extruderspeed) {
                for(int j = 0;j < motorstep;j++) {
                  if ((stringtofloat(historystring[motorval][1]) > stringtofloat(historystring[motorval][0])) || (stringtofloat(stringval(bufferr,motorprintval)) > 0)) {
                        digitalWrite(motorprincval,LOW);
                        digitalWrite(dirpin,HIGH);
                        digitalWrite(steppin,HIGH);
                        delayMicroseconds(100);
                        digitalWrite(steppin,LOW);
                        digitalWrite(motorprincval,HIGH);                        
                        for(int w = 0;w < int(extruderspeed/sqrt(pow(stringtofloat(historystring[4][1]),2)));w++) {
                          digitalWrite(emotor,LOW);
                          digitalWrite(dirpin,HIGH);
                          digitalWrite(steppin,HIGH);
                          delayMicroseconds((steptimemotore*1000)/int(extruderspeed/sqrt(pow(stringtofloat(historystring[4][1]),2))));
                          digitalWrite(steppin,LOW);
                          digitalWrite(emotor,HIGH);
                          }
              }
              else {
                        digitalWrite(motorprincval,LOW);
                        digitalWrite(dirpin,LOW);
                        digitalWrite(steppin,HIGH);
                        delayMicroseconds(100);
                        digitalWrite(steppin,LOW);
                        digitalWrite(motorprincval,HIGH);                        
                        for(int w = 0;w < int(extruderspeed/sqrt(pow(stringtofloat(historystring[4][1]),2)));w++) {
                          digitalWrite(emotor,LOW);
                          digitalWrite(dirpin,HIGH);
                          digitalWrite(steppin,HIGH);
                          delayMicroseconds((steptimemotore*1000)/int(extruderspeed/sqrt(pow(stringtofloat(historystring[4][1]),2))));
                          digitalWrite(steppin,LOW);
                          digitalWrite(emotor,HIGH);
                          }
                    }
                  }
              }
              else if (sqrt(pow(stringtofloat(historystring[4][1]),2)) > extruderspeed) {
                float motorspeed;
                if (stringtofloat(historystring[4][1]) > 0) motorspeed = stringtofloat(historystring[4][1]);
                else motorspeed = stringtofloat(historystring[4][0]);
                  int nbstepmotore = perfectstepparloop(motorspeed,extruderspeed,motorstep,true);
                  int nbloopmotore = motorstep/nbstepmotore;
                  Serial.print("nombre de step : ");
                  Serial.println(nbstepmotore);
                  Serial.print(" nombre de loop : ");
                  Serial.println(nbloopmotore);
                 for(int j = 0;j < int(nbloopmotore);j++) {
                        digitalWrite(emotor,LOW);
                        digitalWrite(dirpin,HIGH);
                        digitalWrite(steppin,HIGH);
                        delayMicroseconds(3);
                        digitalWrite(steppin,LOW);
                        digitalWrite(emotor,HIGH);
                        for(int w = 0;w < int(nbstepmotore);w++) {
                          digitalWrite(motorprincval,LOW);
                          if ((stringtofloat(historystring[motorval][1]) > stringtofloat(historystring[motorval][0])) || (stringtofloat(stringval(bufferr,motorprintval)) > 0)) {
                            digitalWrite(dirpin,HIGH);
                          }
                          else {
                            digitalWrite(dirpin,LOW);
                          }
                          digitalWrite(steppin,HIGH);
                          delayMicroseconds(int(extruderspeed/motorspeed)/(steptimemotore*1000));
                          digitalWrite(steppin,LOW);
                          digitalWrite(motorprincval,HIGH);
                          }
              }
                  }                  
                }
            }
        if (bufferr[0] != '$') {
    advencement = false;
      for(int b = 0;b < 5;b++) {
      historystring[b][0] = historystring[b][1];
      historyint[b][0] = historyint[b][1];
      delay(500);
      }
    }
  bufferr[sofar]=0;
     for(int u = 0;u < buffersize;u++) bufferr[u] = ' ';
     sofar = 0;
     //Serial.flush();
     }
     }
 while(true) {
  while(Serial.available() > 0) {  
    char c=Serial.read();  
    if(newsofar<buffersize) newbuffer[newsofar++]=c; 
    advencement = true;
    if(newbuffer[newsofar-1]==';') break;  
    if (newbuffer[newsofar] == '\n') break;
    Serial.flush();
  }
  if (havesomethingelse() == true && check == false && heat) {
    break;
    }
    if (calibration == false) {
     delay(1000);
     Serial.println("ok");
     }
     if (havesomethingelse()) {
            if ((bufferr[0]  || newbuffer[0]) == '$') {
         calibration = true;
       }
       else {
           calibration = false;
         }
         for(int y = 0;y < buffersize;y++) bufferr[y] = newbuffer[y];
         break;
       }
       for(int u = 0;u < buffersize;u++) newbuffer[u] = ' ';
       newsofar = 0;
   }
     for(int u = 0;u < buffersize;u++) newbuffer[u] = ' ';
     newsofar = 0;
     check = false;

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
    return(string.toFloat());
  }
  char* nullbufffer(char* arraytoflush) {
    char* buffertosend;
    }
int stringtoint(String string) {
    return(string.toInt());
  }
float givefloatval(char buf[buffersize],char chartofind) {
          String string = String(buf);
          for(int k = 0;k < buffersize;k++) {
           if (buf[k] == chartofind) {
          string.remove(0,k+1);
          char bufffer[64] ;
          string.toCharArray(bufffer,64);
          return(atof(bufffer));
          }
          }
    }  
    int giveintval(char buf[buffersize],char chartofind)  {
          String string = String(buf);
          for(int k = 0;k < buffersize;k++) {
            if (buf[k] == chartofind) {
          string.remove(0,k+1);
          return(string.toInt());
          }
          }
          return(0);
      }
String stringval(char buf[buffersize],char chartofind) {
      String string = String(buf);
          for(int k = 0;k < buffersize;k++) {
          if (buf[k] == chartofind) {
          string.remove(0,k+1);
          int stopmoment = string.indexOf(' ');
          string.remove(stopmoment);
          return(string);
          }
          }
          return(" ");
  }
  String laststringval(char buf[buffersize],char chartofind) {
      String string = String(buf);
          for(int k = 0;k < buffersize;k++) {
          if (buf[buffersize-1-k] == chartofind) {
          string.remove(0,buffersize-2-k);
          int stopmoment = string.indexOf(' ');
          string.remove(stopmoment);
          return(string);
          }
          }
          return(" ");
    }
  float ratiomultiplier(float ratioofx,float ratioofy,float ratioofe,float numberofstep) {
    float ecart[ratioscale][3];
    float mediumecart[ratioscale];
    int lowestval[ratioscale];
    int lowval;
    float ratio[3];
    int rationumber = 0;
    ratio[0] = ratioofx;
    ratio[1] = ratioofy;
    ratio[2] = ratioofe;
    for(int y = 0;y < 3;y++) {
      if (ratio[y] > 0) {
          rationumber++;
        }
      }
      for(int q = 1;q < ratioscale;q++) {
          ecart[q-1][0] = (ratioofx-(int(ratioofx)))*q;
          ecart[q-1][1] = (ratioofy-(int(ratioofy)))*q;
          ecart[q-1][2] = (ratioofe-(int(ratioofe)))*q;
          mediumecart[q-1] = (ecart[q-1][0]+ecart[q-1][1]+ecart[q-1][2])/rationumber;
          }
               float minval = mediumecart[0];
               int minratio = 1;
                 for(int y = 1;y < ratioscale+1;y++) {
                   if (mediumecart[y] < minval) {
                     minval = mediumecart[y];
                     minratio = y+1;
                     }
                   }
                   return(minratio);
                   }
          
    int numberstepperloop(float ratio_multiplier,float ratioofx,float ratioofy,float ratioofe) {
        return(ratio_multiplier*(ratioofx+ratioofy+ratioofe));
      }
      int numberofloop(float numberofstep,int numbersteploop) {
          return(numberofstep/numbersteploop);
        }
        float heatval (float curentheat) {
    for(int g = 0;g < buffersize;g++) {
      if (bufferr[g] == 'M') {
      if (stringtoint(stringval(bufferr,'M')) == 104) {
    for(int h = 0;h < buffersize;h++) {
      if (bufferr[h] == 'S') {
          if ((stringtofloat(stringval(bufferr,'S')) || stringtofloat(stringval(bufferr,'E'))) != 0) {
              digitalWrite(heater,HIGH);
              return(stringtofloat(stringval(bufferr,'S')));
            }
            else {
              digitalWrite(heater,LOW);
               return(0);
              }
        }
        }
    }
    }
    }
    return(curentheat);
    }
    boolean havesomething() {
      for(int d = 0;d < buffersize;d++) {
        for(int y = 0;y < 5;y++) {
       if (bufferr[d] == floatval[y] || bufferr[d] == intval[y]) {
      return(true);
    }
    }
      }
      return(false);
      }
      boolean havesomethingelse() {
        /*if (newbuffer[0] == '$') {
          return(false);
          }*/
        for(int d = 0;d < buffersize;d++) {
        for(int y = 0;y < 5;y++) {
       if (newbuffer[d] == floatval[y] || newbuffer[d] == intval[y]) {
      return(true);
    }
    }
      }
      return(false);
        }
        void zrun(float steptimer) {
          if ((stringtofloat(historystring[2][0]) != stringtofloat(historystring[2][1])) || bufferr[0] == '$') {
            if ((stringtofloat(stringval(bufferr,'Z')) > 0) || bufferr[0] != '$') {
           /*digitalWrite(chip1,LOW);
           digitalWrite(chip2,HIGH);
           motor2.setSpeed(30);*/
           if (bufferr[0] != '$') {
           //motor2.step(sqrt(pow(stringtofloat(historystring[2][1])-stringtofloat(historystring[2][0]),2))*48,FORWARD,SINGLE);
           for(int n = 0;n <(sqrt(pow(stringtofloat(historystring[2][1])-stringtofloat(historystring[2][0]),2))*400)/(2*pi*rayon);n++) {
                         digitalWrite(zmotor,LOW);
                        digitalWrite(dirpin,HIGH);
                        digitalWrite(steppin,HIGH);
                        delayMicroseconds(steptime*1000);
                        digitalWrite(steppin,LOW);
                        digitalWrite(zmotor,HIGH);
             }
           }
           else {
             for(int n = 0;n < (stringtofloat(stringval(bufferr,'Z'))*400)/(2*pi*rayon);n++) {
                        digitalWrite(zmotor,LOW);
                        digitalWrite(dirpin,HIGH);
                        digitalWrite(steppin,HIGH);
                        delayMicroseconds(steptime*1000);
                        digitalWrite(steppin,LOW);
                        digitalWrite(zmotor,HIGH);
             }
           }
         }
          }
          }
          void zprint() {
                     Serial.print("Z step : ");
                     if (bufferr[0] != '$') {
                     Serial.println((stringtofloat(historystring[2][1])-stringtofloat(historystring[2][0]))*48);
                     }
                     else {
                         Serial.println(stringtofloat(stringval(bufferr,'Z'))*48);
                       }
            }
          void erun(float lengthh) {
               if (stringtofloat(historystring[3][1]) > 0) {
                        digitalWrite(emotor,LOW);
                        digitalWrite(dirpin,HIGH);
                        digitalWrite(steppin,HIGH);
                        delay(3);
                        digitalWrite(steppin,LOW);
                        delay(3);
                        digitalWrite(emotor,HIGH);
              }
            }
            boolean getextrudermod(boolean extrudermodd) {
                for(int d = 0;d < buffersize;d++) {
                    if (bufferr[d] == 'M') {
                        if (historyint[1][1] == 101) {
                            return(true);
                          }
                         else if (historyint[1][1] == 108) {
                             if (stringtofloat(historystring[3][1]) > 0) {
                                 return(true);
                               }
                              else {
                                  return(false);
                                }
                           }
                         else if (historyint[1][1] == 103) {
                           return(false);
                           }
                      }
                  }
               for(int d = 0;d < buffersize;d++) {
                    if (bufferr[d] == 'M') {
                        if (stringtoint(stringval(bufferr,'M')) == 101) {
                            return(true);
                          }
                         else if (stringtoint(stringval(bufferr,'M')) == 108) {
                             if (stringtofloat(stringval(bufferr,'S')) > 0) {
                                 return(true);
                               }
                              else {
                                  return(false);
                                }
                           }
                         else if (stringtoint(stringval(bufferr,'M')) == 103) {
                           return(false);
                           }
                      }
                  }
                  return(extrudermodd);
              }
            float getextruderspeed (float extruderspeedd) {
                for(int d = 0;d < buffersize;d++) {
                    if (bufferr[d] == 'M') {
                        if (historyint[1][1] == 108) {
                            return(stringtofloat(historystring[3][1])/10);
                          }
                      }
                  }
                for(int d = 0;d < buffersize;d++) {
                    if (bufferr[d] == 'M') {
                        if (stringtoint(stringval(bufferr,'M')) == 108) {
                            return(stringtofloat(stringval(bufferr,'S'))/10);
                          }
                      }
                  }
                  return(extruderspeedd);
              }
              int perfectstepparloop(float param1,float param2,int nbstep,boolean mode) {
                int possibility[nbstep*nbstep][2];
                int nbpossible = 0;
                for(int y = 1;y < nbstep;y++) {
                      for(int u = 1;u < nbstep;u++) {
                        if (y*u == nbstep) {
                            possibility[nbpossible][0] = u;
                            possibility[nbpossible][1] = y;
                            nbpossible++;
                          }
                    }
                }
                float ecart[nbpossible+1][2];
                float mediumecart[nbpossible+1];
                for(int y = 0;y < nbpossible+1;y++) {
                  if (mode) {
                    ecart[y][0] = sqrt(pow(param1-(param2/possibility[y][0]),2));
                    ecart[y][1] = sqrt(pow(param2-possibility[y][1]*(param2/possibility[y][0]),2));
                    mediumecart[y] = (ecart[y][0]+ecart[y][1])/2;
                    }
                    else {
                        mediumecart[y] = sqrt(pow(param1-possibility[y][0],2));
                      }
                  }
                 float minval = mediumecart[0];
                 for(int y = 0;y < nbpossible+1;y++) {
                   if (mediumecart[y] < minval) {
                     minval = mediumecart[y];
                     }
                   }
                   return(minval);
                }
