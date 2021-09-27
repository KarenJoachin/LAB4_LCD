//--------------------------------------------------------------------------------
//Universidad del Valle de Guatemala
//BE3015 Electronica Digital 2
//Karen Joachin
//Laboratorio 4 LCD
//fila columna
//-----------------------------------------------------------------------------
//Librerias
//-----------------------------------------------------------------------------
#include <Arduino.h>
#include <LiquidCrystal.h>
//-----------------------------------------------------------------------------
//Definiciond de etiquetas
//-----------------------------------------------------------------------------

#define d4 19
#define d5 21
#define d6 5
#define d7 22
#define en 15
#define rs 18

#define pot1 32
#define pot2 13
//botones para incrementar y decrementar
#define btn1 14
#define btn2 27
//-----------------------------------------------------------------------------
//Prototipo de funciones
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//Variabls Globales
//-----------------------------------------------------------------------------
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);
uint8_t decenas, unidades, decimal;
uint8_t decenas2, unidades2, decimal2;
int adcRaw;
float voltaje;
float voltaje2;

int cbtn1 = 0;
int contador = 0;
int suma = 0;
int resta = 0;
int sube = 0;
int baja = 0;
bool presionar = false;
//-----------------------------------------------------------------------------
//ISR
//-----------------------------------------------------------------------------
void IRAM_ATTR sumab1() //interrupcion de incremento
{
  suma = digitalRead(btn1);
  if (suma != sube)
  {
    if (suma == LOW)
    {
      presionar = true;
      contador++;
      Serial.println(contador);
    }

    delay(50);
  }

  sube = suma;
  if (contador > 255)
  {
    contador = 0;
  }
}
void IRAM_ATTR restab2() //interrupcion de decremento
{
  resta = digitalRead(btn2);
  if (resta != baja)
  {
    if (resta == LOW)
    {
      presionar = true;
      contador--;
      Serial.println(contador);
    }
    delay(50);
  }

  baja = resta;
  if (contador < 1)
  {
    contador= 0;
  }
}
//-----------------------------------------------------------------------------
//Configuracion
//-----------------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  LCD.begin(16, 2);

  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);

  // ACA Adjuntar Interrupción al pin GPIO
  attachInterrupt(btn1, sumab1, RISING);
  attachInterrupt(btn2, restab2, RISING);
}
//-----------------------------------------------------------------------------
//loop principal
//-----------------------------------------------------------------------------

void loop()
{
  contador;
  //pra primer potenciometro
  voltaje = analogReadMilliVolts(pot1) / 10.0;
  int temp = voltaje;
  decenas = temp / 100.0;
  temp = temp - decenas * 100.0;
  unidades = temp / 10.0;
  temp = temp - unidades * 10.0;
  decimal = temp;

  //para segundo potenciometro
  voltaje2 = analogReadMilliVolts(pot2) / 10.0;
  int temp2 = voltaje2;
  decenas2 = temp2 / 100.0;
  temp2 = temp2 - decenas2 * 100.0;
  unidades2 = temp2 / 10.0;
  temp2 = temp2 - unidades2 * 10.0;
  decimal2 = temp2;

  Serial.print("voltaje: ");
  Serial.print(voltaje);
  Serial.print("\n");

  Serial.print("voltaje2: ");
  Serial.print(voltaje2);
  Serial.print("\n");

  Serial.print("CPU: ");
  Serial.print(contador);
  Serial.print("\n");
  Serial.print("\n");

  //para limpiar LCD
  LCD.clear();
  LCD.print("Pot1:");
  LCD.print("Pot2:");
  LCD.print("CPU:");

  LCD.setCursor(0, 1); //para cambiar de fila y columna
  LCD.print(decenas);
  LCD.print('.');
  LCD.print(unidades);
  LCD.print(decimal);
  LCD.print(" ");

  LCD.print(decenas2);
  LCD.print('.');
  LCD.print(unidades2);
  LCD.print(decimal2);
  LCD.print(" ");
  LCD.print(contador);

  delay(1000);
}