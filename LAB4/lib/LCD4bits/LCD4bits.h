#ifndef __LCD4BITS_H__
#define __LCD4BITS_H__

#include <Arduino.h>
#include <stdint.h>

extern uint8_t RS, E, D4, D5, D6, D7;

// Función para configurar LCD en modo 4 bits: parámetros pines rs, e, d4, d5, d6, d7
void LCD_Init(uint8_t rs, uint8_t e, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

// Función para mandar en el puerto el dato que deseamos: parámetro data
void LCD_Port(uint8_t data); 

// Función para mandar comandos: parámetro comando c
void LCD_Cmd(char c);

// Función para escribir un caracter: parámetro caracter a
void LCD_Write_Char(char a);

// Función para escribir una cadena de caracteres: parámetro cadena de caracter a
void LCD_Write_String(char *a);

// Función para establecer el cursor
void LCD_Set_Cursor(uint8_t f, uint8_t c);

// Función para limpiar visor
void LCD_Clear(void);

// Función para desplazamiento a la derecha
void LCD_Shift_Right(void);

// Función para desplazamiento a la izquierda
void LCD_Shift_Left(void);


#endif // __LCD4BITS_H__