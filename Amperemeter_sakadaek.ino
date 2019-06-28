#include "EmonLib.h"              
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
EnergyMonitor emonR,emonS,emonT;

double RIrms = 0;  
double SIrms = 0;
double TIrms = 0;
  
double Rrms =  0;
double Srms =  0;
double Trms =  0;
  
void setup() 
{
  Serial.begin(115200);
   
  emonR.current(A0, 111.1);//R
  emonS.current(A1, 111.1);//S
  emonT.current(A2, 111.1);//T
  
  lcd.begin(16,2);
  lcd.backlight();
  
  lcd.clear();//Clean the screen
  lcd.setCursor(0,0); 
  lcd.print("- AmpereMeter -");
  lcd.setCursor(0,1);
  lcd.print("<<< Sakadaek >>>"); 
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Created by:");
  lcd.setCursor(0,1);
  lcd.print("     The The Luk"); 
  delay(2000);
}

void loop() 
{
  RIrms = emonR.calcIrms(1480);//1480 sample  
  SIrms = emonS.calcIrms(1480); 
  TIrms = emonT.calcIrms(1480); 

  /*
   * kenapa dibagi 2,karena arus ac bentuknya 1 gelombang (1 bukit satu lembah)
   * dan Rms itu merupakan arus maksimal dikali akar 2
   * maka perlu dibagi dua untuk medapatkan arus Rms-nya
   */
  
  Rrms = RIrms/2;
  Srms = SIrms/2;
  Trms = TIrms/2;

  lcd.clear();
  
  //R
  lcd.setCursor(0,0); 
  lcd.print("R:");
  if (Rrms<0 || Rrms>100){
    lcd.print("err");
  }else{
    lcd.print(Rrms,1);
    lcd.print("A");
  }

  //S
  lcd.setCursor(0,1); 
  lcd.print("S:");
  if (Srms<0 || Srms>100){
    lcd.print("err");
  }else{
    lcd.print(Srms,1);
    lcd.print("A");
  }
    
  //T
  lcd.setCursor(9,0); 
  lcd.print("T:");
  if (Trms<0 ||  Trms>100){
    lcd.print("err");
  }else{
    lcd.print(Trms,1);
    lcd.print("A");
  }
  
  //============Print Serial==================//
  Serial.print("| Rrms: ");
  Serial.print(Rrms,1);
  Serial.print(" A  |  ");

  Serial.print("Srms: ");
  Serial.print(Srms,1);
  Serial.print(" A  |  ");

  Serial.print("Trms: ");
  Serial.print(Trms,1);
  Serial.print(" A  |  ");   
  
  Serial.println();
  //==============================//
    
  //delay(1000);

}
