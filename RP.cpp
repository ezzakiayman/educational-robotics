#include "SimpleTimer.h"
#include <Servo.h>
#include <StringSplitter.h>
#include <SoftwareSerial.h>
#include <Wire.h>
SimpleTimer timer;
Servo servod,servog;
int pin2=4,info=13,pin3=5,dr=2,ga=3, sens=5, i=1,compteur=0,pos=5;
int vald=0,valg=0,valeur=0,fin=1;
float d,g;
String readString="";
void setup() {
pinMode(info,OUTPUT);
pinMode(dr,INPUT);
pinMode(ga,INPUT);
digitalWrite(info, LOW);
Serial.begin(115200);
attachInterrupt(digitalPinToInterrupt(dr), droite, CHANGE);
attachInterrupt(digitalPinToInterrupt(ga), gauche, CHANGE);
// timer.setInterval(1000, asservi);
servod.attach(pin2);
servog.attach(pin3);
servod.write(50);
servog.write(50);
}
void loop() {
//timer.run();
while (Serial.available()) {
 //delay to allow byte to arrive in input buffer
 delay(2);
 char c = Serial.read();
 if(c=='*'){
 readString = Serial.readStringUntil('$');
 break;
 }}
 if(readString.length()>0 && readString.length()<20 and fin){

 vald=0;valg=0;fin=0;
 digitalWrite(info, LOW);
 Serial.println(readString);
 valeur=getValue(readString, ';', 4).toInt();
 sens=getValue(readString, ';', 5).toInt();
 d=getValue(readString, ';', 2).toInt();
 g=getValue(readString, ';', 3).toInt();
 if(d==0 && g==0){d=60;g=40;}

 /*****************************************************************************/
 if(valeur>0 && valeur <1000 )
 {
 if(sens>0)
 {
 valeur=int(valeur/sens)+1;
 }
 servod.write(int(d));
 servog.write(int(g));
 }
 /*****************************************************************************/
}
 readString="";
 }
/**************************************avancer***************************************/
void gauche(){
valg++;
if(valg==valeur)
{
 arret();
}
}
void droite(){
vald++;
if(vald==valeur)
{
 arret();
}
}
void arret(){
 servod.write(g);
 servog.write(d);
 delay(500);
 servod.write(50);
 servog.write(50);
 digitalWrite(info, HIGH);
 Serial.print("fin..................");
 fin=1;

}
String getValue(String data, char separator, int index)
{
 int found = 0;
 int strIndex[] = {0, -1};
 int maxIndex = data.length()-1;
 for(int i=0; i<=maxIndex && found<=index; i++){
 if(data.charAt(i)==separator || i==maxIndex){
 found++;
 strIndex[0] = strIndex[1]+1;
 strIndex[1] = (i == maxIndex) ? i+1 : i;
 }
 }
 return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void affiche(){
Serial.print("gauche:");
 Serial.println(valg );
 Serial.print("droite:");
 Serial.println(vald);
 Serial.print("g:");
 Serial.println(g);
 Serial.print("d:");
 Serial.println(d);
}