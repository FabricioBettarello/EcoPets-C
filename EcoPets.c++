#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define pinoTrig 7
#define pinoEcho 6
#define vermelho 4
#define amarelo 3
#define verde 2
#define buzzer 5
#define motor1 8
#define motor2 9
#define pinoServo 9

LiquidCrystal_I2C lcd(0x27,16,2);
Servo cam;


void luzVerde(){
  digitalWrite(vermelho, LOW);
  digitalWrite(amarelo, LOW);
  digitalWrite(verde, HIGH);
}

void luzAmarela(){
  digitalWrite(vermelho, LOW);
  digitalWrite(amarelo, HIGH);
  digitalWrite(verde, LOW);
}

void luzVermelha(){
  digitalWrite(vermelho, HIGH);
  digitalWrite(amarelo, LOW);
  digitalWrite(verde, LOW);
}

void bipar(){
  for(int i = 0; i < 3; i++){ //bipar 3 vezes
      tone(buzzer,440);
      delay(100);
      noTone(buzzer);
      delay(100);
    }
}

void semGiro(){
  cam.write(0);
}

void abrirPortao(){
  cam.write(180);
}

void setup()
{
  pinMode(pinoTrig, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(pinoEcho, INPUT);
  cam.attach(pinoServo);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop()
{
  //pinoTrig
  digitalWrite(pinoTrig, HIGH);
  delay(100); 
  digitalWrite(pinoTrig, LOW);
  
  //pinoEcho
  int duracao = pulseIn(pinoEcho,HIGH);
  int distancia = (duracao/2)/29.1;
  
  //exibir no monitor serial
  Serial.print(distancia);
  Serial.println("cm");
  
  //exibir nível da água
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nivel da Agua:");
  lcd.setCursor(0,1);
  lcd.print(100-distancia);
  
  
  //Controlando LED
   if (distancia > 300){
    noTone(7);
    semGiro();
    luzVerde();
  }
  else if (distancia > 100 && distancia < 300){
    noTone(7);
    semGiro();
    luzAmarela();    
  }
  else if(distancia < 100){ // nível de perigo
    bipar();
    luzVermelha();
    abrirPortao();  
  }
  
}
