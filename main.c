/*********************************************************************************\
*
* MMMMMMMMMMMM   SSSSSSSSSSSS   WW   WW   WW   MECHATRONIK
* MM   MM   MM   SS             WW   WW   WW   SCHULE
* MM   MM   MM   SSSSSSSSSSSS   WW   WW   WW   WINTERTHUR
* MM   MM   MM             SS   WW   WW   WW   
* MM   MM   MM   SSSSSSSSSSSS   WWWWWWWWWWWW   www.msw.ch
*
*
* Dateiname: main.c
*
* Projekt  : Muster
* Hardware : uC-Board, ATmega2560v von Atmel
*
* Copyright: MSW, E2
*
* Beschreibung:
* =============
* Siehe Prüfungsaufgabe
*
*
* Verlauf:
* ========
* Datum:      Autor:                             Version
* 13.11.2023 Tijan Jotic, Cédric der XIII          V1.0      
*
\*********************************************************************************/

//uC-Board-Treiber hinzufügen
#include "Control_Loop.h"

#include "ucBoardDriver.h"

#include "stdint.h"

//Defines

#define GIVEN_SCALE_W       71232 //Istwert

#define AMPLIFICATION_P         2   //P-Verstärkung


//Hauptprogramm
int main(void)
{
    initBoard(0);
    
    uint16_t controlScale_x = 0; //Regelungsgrösse = x
    int16_t errorScale_e = 0; //Differenz des Soll-Werts und des Ist-Werts. 

    int16_t regulationScale_y = 0; //Ausgang des reglers.

    
    //Unendlichschlaufe
    while(1)
    {
        controlScale_x = adcRead(ADC_00_X4_PORTF_BIT0);

        errorScale_e = GIVEN_SCALE_W - controlScale_x;
        regulationScale_y = 
            (errorScale_e * AMPLIFICATION_P)      //P-Anteil
            + (0)   //I-Anteil
            + (0);  //D-Anteil
        
        Control_Loop_output_regulation_scale(regulationScale_y);
    }
}

