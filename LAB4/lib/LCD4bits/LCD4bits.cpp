#include "LCD4bits.h"

uint8_t RS, EN, D4, D5, D6, D7;
//*****************************************************************************
// Inicializar LCD en modo 4 bits
//*****************************************************************************
void LCD_Init(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
    RS = rs;
    EN = en;

    D4 = d4;
    D5 = d5;
    D6 = d6;
    D7 = d7;
   

    pinMode(RS, OUTPUT);
    pinMode(EN, OUTPUT);
    

    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);

    uint8_t port[] = {D4, D5, D6, D7};

    for (int i = 0; i < 4; i++)
    {
        pinMode(port[i], OUTPUT);
    }

    

    LCD_Port(0x00);
    delay(20);
    LCD_Cmd(0x03);
    delay(5);
    LCD_Cmd(0x03);
    delay(11);
    LCD_Cmd(0x03);
    /////////////////////////////////////////////////////
    LCD_Cmd(0x02);
    LCD_Cmd(0x02);
    LCD_Cmd(0x08);
    LCD_Cmd(0x00);
    LCD_Cmd(0x0C);
    LCD_Cmd(0x00);
    LCD_Cmd(0x06);
}
//*****************************************************************************
// Función para cargar el valor en el puerto
//*****************************************************************************
void LCD_Port(uint8_t data)
{
    if (data & 1)
    {
        digitalWrite(D4, HIGH); // D4 = 1;
    }
    else
    {
        digitalWrite(D4, LOW); // D4 = 0;
    }
    if (data & 2)
    {
        digitalWrite(D5, HIGH); // D5 = 1;
    }
    else
    {
        digitalWrite(D5, LOW); // D5 = 0;
    }
    if (data & 4)
    {
        digitalWrite(D6, HIGH); // D6 = 1;
    }
    else
    {
        digitalWrite(D6, LOW); // D6 = 0;
    }

    if (data & 8)
    {
        digitalWrite(D7, HIGH); // D7 = 1;
    }
    else
    {
        digitalWrite(D7, LOW); // D7 = 0;
    }
}
//*****************************************************************************
// Enviar comandos
//*****************************************************************************
void LCD_Cmd(char c)
{
    digitalWrite(RS, LOW);      // RS = 0 - Dato como comando
    LCD_Port(c);
    digitalWrite(EN, HIGH);      // E = 1
    delay(4);
    digitalWrite(EN, LOW);       // E = 0
}
//*****************************************************************************
// Enviar caracter
//*****************************************************************************
void LCD_Write_Char(char a)
{
    char temp, y;
    temp = a & 0x0F;
    y = a & 0xF0;
    digitalWrite(RS, HIGH);     // Dato como dato RS = 1

    LCD_Port(y >> 4);           //Data transfer
    digitalWrite(EN, HIGH);      // E = 1
    delayMicroseconds(40);
    //delay(4);
    digitalWrite(EN, LOW);       // E = 0

    LCD_Port(temp);
    digitalWrite(EN, HIGH);       // E = 1
    //delay(4);
    delayMicroseconds(40);
    digitalWrite(EN, LOW);        // E = 0
}
//*****************************************************************************
// Enviar cadena de caracteres
//*****************************************************************************
void LCD_Write_String(char *a)
{
    for (int i = 0; a[i] != '\0'; i++)
    {
        LCD_Write_Char(a[i]);
    }
}
//*****************************************************************************
// Función para establecer el cursor
//*****************************************************************************
void LCD_Set_Cursor(uint8_t f, uint8_t c)
{
    uint8_t temp, z, y;
    if (f == 1)
    {
        temp = 0x80 + c - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        LCD_Cmd(z);
        LCD_Cmd(y);
    }
    else if (f == 2)
    {
        temp = 0xC0 + c - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        LCD_Cmd(z);
        LCD_Cmd(y);
    }
}
//*****************************************************************************
// Limpieza del visor
//*****************************************************************************
void LCD_Clear(void)
{
    LCD_Cmd(0x00);
    LCD_Cmd(0x01);
}
//*****************************************************************************
// Desplazamiento hacia la derecha
//*****************************************************************************
void LCD_Shift_Right(void)
{
    LCD_Cmd(0x01);
    LCD_Cmd(0x0C);
}
//*****************************************************************************
// Desplazamiento hacia la izquierda
//*****************************************************************************
void LCD_Shift_Left(void)
{
    LCD_Cmd(0x01);
    LCD_Cmd(0x08);
}
