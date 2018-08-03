/* An emergency brake is done by pulling a stepper motor.
 *  This function pulls the brake pedal as long as the bottun is pressed.
 *  When the button is released, the motor makes a reverse turn for a short peried
 *  in order to release the brake. 
 * 
 * TODO: LoRa Sender should be added
 * TODO: Button to be attached to an interrupt pin
 */
const byte PUL=7; //define Pulse pin
const byte DIR=6; //define Direction pin
const byte ENA=5; //define Enable Pin

int button=4;
int last_button_state=0;
int button_state;
int num_step=500;

int entered=0;

int turn_num=1000;
void setup() {
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode(button,INPUT_PULLUP);
}

void loop() {

  while(digitalRead(button)==0){
        
      digitalWrite(DIR,LOW);
      digitalWrite(ENA,HIGH);
      digitalWrite(PUL,HIGH);
      delayMicroseconds(num_step);
      digitalWrite(PUL,LOW);
      delayMicroseconds(num_step);
    
   entered=1;
  } 


  if(entered==1){
    entered=0;
    for(int i=0; i<turn_num;i++){
       digitalWrite(DIR,HIGH);
      digitalWrite(ENA,HIGH);
      digitalWrite(PUL,HIGH);
      delayMicroseconds(num_step);
      digitalWrite(PUL,LOW);
      delayMicroseconds(num_step);

  }
  
 }
}
  
  
 

  

