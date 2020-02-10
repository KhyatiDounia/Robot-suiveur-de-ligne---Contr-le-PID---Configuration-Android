//varaible de Bluetooth
int tx=1;
int rx=0;
char inSerial[15];
int error,P,I=0,D;
int Kp=0,Ki=0,Kd=0,PIDvalue,previousError=0;
const int lineFollowSensor0 = 12;
const int lineFollowSensor1 = 18;
const int lineFollowSensor2 = 17;
const int lineFollowSensor3 = 16;
const int lineFollowSensor4 = 19;
int LFSensor[5]={0, 0, 0, 0, 0};
int vit=50;
 int vitesseM1=2;
 int arriereM1=3;
 int avantM1=4;
 int vitesseM2=5;
 int arriereM2=6;
 int avantM2=7;
 int temps=300;
 int mode=0;
void setup() {
 // put your setup code here, to run once:
 pinMode(lineFollowSensor0,INPUT);
 pinMode(lineFollowSensor1,INPUT);
 pinMode(lineFollowSensor2,INPUT);
 pinMode(lineFollowSensor3,INPUT);
 pinMode(lineFollowSensor4,INPUT);
 Serial.begin(9600);
 
 pinMode(vitesseM1,OUTPUT);
 pinMode(arriereM1,OUTPUT);
 pinMode(avantM1,OUTPUT);
 pinMode(vitesseM2,OUTPUT);
 pinMode(arriereM2,OUTPUT);
 pinMode(avantM2,OUTPUT);
 
 Serial.begin(9600);
 //Bleutooth
 pinMode(tx, OUTPUT);
 pinMode(rx, INPUT);
}
void readsensor(){
 LFSensor[0] = digitalRead(lineFollowSensor0);
LFSensor[1] = digitalRead(lineFollowSensor1);
LFSensor[2] = digitalRead(lineFollowSensor2);
LFSensor[3] = digitalRead(lineFollowSensor3);
LFSensor[4] = digitalRead(lineFollowSensor4);
if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0
)&&(LFSensor[3]== 0 )&&(LFSensor[4]== 1 )) error = 4;
else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0
)&&(LFSensor[2]== 0 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 1
)) error = 3;
else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0
)&&(LFSensor[2]== 0 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 0
)) error = 2;
else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0
)&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 0
)) error = 1;
else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0
)&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 0
)) error = 0;
else if((LFSensor[0]== 0 )&&(LFSensor[1]== 1
)&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 0
)) error =- 1;
else if((LFSensor[0]== 0 )&&(LFSensor[1]== 1
)&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 0
)) error = -2;
else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1
)&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 0
)) error = -3;
else if((LFSensor[0]== 1 )&&(LFSensor[1]== 0
)&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 0
)) error = -4;
mode=3;
if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0
)&&(LFSensor[3]== 0 )&&(LFSensor[4]== 0 )) mode = 1;
else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1
)&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 1
)) mode = 2;
 }
 void calculatePID()
{
 P = error;
 I = I + error;
 D = error-previousError;
 PIDvalue = (Kp*P) + (Ki*I) + (Kd*D);
 previousError = error;
 Serial.println(PIDvalue);
 delay(500);
}
void loop() {
 // put your main code here, to run repeatedly:
 int i=0;
 int m=0;
 delay(500);
if (Serial.available() > 0) {
while (Serial.available() > 0) {
inSerial[i]=Serial.read();
i++;
}}
inSerial[i]='\0';
 switch (inSerial[0])
 {
 case 'g':
 mode = 3;
 break;
 case 's':
 motorstop(); //turn off both motors
 break;
 case 'f':
 motorForward();
 break;
 case 'r':
 right();
 motorstop();
 break;
 case 'l':
left();
 motorstop();
 break;
 case 'b':
 motorBackward();
 break;
 case 'p':
 Kp =inSerial[2];
 break;
 case 'i':
 Ki = inSerial[2];
 break;
 case 'd':
 Kd = inSerial[2];
 break;
 }
 readsensor();
 switch (mode)
 {
 case 1://stop
motorstop();
 Serial.println("The end ");
 break;
 case 2://no line
 Serial.println("noline");
motorstop();
motorBackward();
 break;
 case 3:
 //calculatePID();
 motor();
 break;
 } 
}
void motor(){
 int vit1=vit-PIDvalue;
 if(error>0){
 Serial.println("Right");
 
 analogWrite(vitesseM1,vit1);
 digitalWrite(arriereM1,HIGH);
 digitalWrite(avantM1,LOW);
 analogWrite(vitesseM2,vit1);
 digitalWrite(arriereM2,LOW);
 digitalWrite(avantM2,HIGH);
 
 //delay(temps);
 }
 else if (error<0){
 Serial.println("left");
 analogWrite(vitesseM1,vit1);
 digitalWrite(arriereM1,LOW);
 digitalWrite(avantM1,HIGH);
 analogWrite(vitesseM2,vit1);
 digitalWrite(arriereM2,HIGH);
 digitalWrite(avantM2,LOW);
 
 //delay(temps);
 }
 else if (error==0){
 Serial.println("forward");
 
 analogWrite(vitesseM1,vit1);
 digitalWrite(arriereM1,LOW);
 digitalWrite(avantM1,HIGH);
 analogWrite(vitesseM2,vit1);
 digitalWrite(arriereM2,LOW);
 digitalWrite(avantM2,HIGH);
 
 //delay(temps);
 }
 }
void motorstop(){
 digitalWrite(avantM1,LOW);
 digitalWrite(arriereM1,LOW);
 digitalWrite(avantM2,LOW);
 digitalWrite(arriereM2,LOW);
 }
void motorBackward(){
 analogWrite(vitesseM1,50);
 digitalWrite(avantM1,LOW);
 digitalWrite(arriereM1,HIGH);
 analogWrite(vitesseM2,100);
 digitalWrite(avantM2,LOW);
 digitalWrite(arriereM2,HIGH);
 }
 void motorForward(){
 analogWrite(vitesseM1,100);
 digitalWrite(avantM1,HIGH);
 digitalWrite(arriereM1,LOW);
 analogWrite(vitesseM2,100);
 digitalWrite(avantM2,HIGH);
 digitalWrite(arriereM2,LOW);
 }
 void right(){
 analogWrite(vitesseM1,100);
 digitalWrite(avantM1,HIGH);
 digitalWrite(arriereM1,LOW);
 analogWrite(vitesseM2,100);
 digitalWrite(avantM2,LOW);
 digitalWrite(arriereM2,HIGH);
 }
  void left(){
 analogWrite(vitesseM1,100);
 digitalWrite(avantM1,LOW);
 digitalWrite(arriereM1,HIGH);
 analogWrite(vitesseM2,100);
 digitalWrite(avantM2,HIGH);
 digitalWrite(arriereM2,LOW);
 }
  
