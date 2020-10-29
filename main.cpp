#include "mbed.h"

DigitalIn Column1(p24);
DigitalIn Column2(p25);
DigitalIn Column3(p26);
DigitalIn Column4(p27);
DigitalIn Column5(p28);

BusOut Rows(p17,p16,p15,p14);

//AnalogOut Output(p18);
PwmOut SineOut(p21);
PwmOut SquareOut(p22);
PwmOut SawOut(p23);

InterruptIn SineButton(p13);
InterruptIn SawButton(p12);
InterruptIn SquareButton(p11);

// 0 = Sine, 1 = Saw, 2 = Square

int Wave = 2;

//INTERRUPT FUNCTIONS
void SineInt(){
        Wave = 0;
    }
void SawInt(){
        Wave = 1;
    }
void SquareInt(){
        Wave = 2;
    }


//THESE ARE THE OSCILLATOR WAVE FUNCTIONS
void Sine(float frequency){
        SawOut = 0.0;
        SquareOut = 0.0;
        SineOut.period(1.0f/frequency);
        SineOut = 0.5f;
    }
void Saw(float frequency){
        //Square for now
        SineOut = 0.0;
        SquareOut =0.0;
        SawOut.period(1.0f/frequency);
        SawOut = 0.7f;
        
    }
void Square(float frequency){
        SineOut = 0.0;
        SawOut =0.0;
        SquareOut.period(1.0f/frequency);
        SquareOut = 0.5f;
    }


// MAY NEED TO SWAP SWITCH STATEMENT AND WHILE:: Done
void Oscillator(float frequency,int input,int wave){ 
                switch(wave){
                        case 0: Sine(frequency); break;
                        case 1: Saw(frequency); break;
                        case 2: Square(frequency); break;
                    }
    }


int main() {
    //Interrupts
    SineButton.rise(&SineInt);
    SawButton.rise(&SawInt);
    SquareButton.rise(&SquareInt);
    
    //Initialise Pwm
    SineOut.period(0.1f);
    SquareOut.period(0.1f);
    SawOut.period(0.1f);
    SineOut = 0.0f;
    SquareOut = 0.0f;
    SawOut = 0.0f;
    
    // NOTES F2 TO C4 in a matrix layout
    float Column1_Frequencies[5] = {87.31,116.54,155.56,207.65};
    float Column2_Frequencies[5] = {92.5,123.47,164.81,220.0};
    float Column3_Frequencies[5] = {98.0,130.81,174.61,233.08};
    float Column4_Frequencies[5] = {103.83,138.59,185.0,246.94};
    float Column5_Frequencies[5] = {110.0,146.83,196.0,261.63};
    
    
    while(1) {
        for (int i=0;i<4;i++){
                switch(i){
                        //ROW 1
                        case 0: Rows = 0x1; break;
                        //ROW 2
                        case 1: Rows = 0x2; break;
                        //ROW 3
                        case 2: Rows = 0x4; break;
                        //ROW 4
                        case 3: Rows = 0x8; break;
                    }
                
                if (Column1 == 1){
                        while (Column1 == 1){
                            Oscillator(Column1_Frequencies[i],Column1,Wave);
                        }
                    }
                else if (Column2 == 1){
                        while (Column2 == 1){
                            Oscillator(Column2_Frequencies[i],Column2,Wave);
                        }
                    }
                else if (Column3 == 1){
                        while (Column3 == 1){
                            Oscillator(Column3_Frequencies[i],Column3,Wave);
                        }
                    }
                else if (Column4 == 1){
                        while (Column4 == 1){
                        Oscillator(Column4_Frequencies[i],Column4,Wave);
                        }
                    }
                else if (Column5 == 1){
                        while (Column5 == 1){
                        Oscillator(Column5_Frequencies[i],Column5,Wave);
                        }
                    }
                SineOut = 0.0f;
                SawOut = 0.0f;
                SquareOut=0.0f;
            }
    }
}