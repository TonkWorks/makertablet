//Small Stepper Motor and Driver


char inData[20]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character
boolean running = false;



/*-----( Import needed libraries )-----*/
#include <Stepper.h>

/*-----( Declare Constants, Pin Numbers )-----*/
#define STEPS  100   //Number of steps per revolution


/*-----( Declare objects )-----*/
/* create an instance of the stepper class, specifying
 the number of steps of the motor and the pins it's
 attached to. The pin connections need to be 4 pins connected
 to Motor Driver In1, In2, In3, In4  and then the pins entered
 here in the sequence 1-3-2-4 for proper sequencing*/

Stepper small_stepper(STEPS, 8, 10, 9, 11);

int  Steps2Take = 2038;

void setup(){   
    Serial.begin(9600);
    Serial.print("RDY!");

}

char Comp(char* This) {
    while (Serial.available() > 0) // Don't read unless
                                   // there you know there is data
    {
        if(index < 19) // One less than the size of the array
        {
            inChar = Serial.read(); // Read a character
            inData[index] = inChar; // Store it
            index++; // Increment where to write next
            inData[index] = '\0'; // Null terminate the string
        }
    }
    //Serial.println(inData);

    if (strcmp(inData,This)  == 0) {
        for (int i=0;i<19;i++) {
            inData[i]=0;
        }
        index=0;
        return(0);
    }
    else {
        return(1);
    }
}

void loop (){
  
  
    if (Comp("motoron")==0) {
        Serial.write("Motor is on\n");
        running = true;
    }
    if (Comp("motoroff")==0) {
        Serial.write("Motor is off\n");
        running = false;
    }
    if (running == true){
      run();
    }
    delay(250);
}

void run(){
  small_stepper.setSpeed(300);
  small_stepper.step(Steps2Take);
}

/* --(end main loop )-- */
