/*
Name:			Benedikt Howard
E-mail:			benedikthoward@gmail.com
Student Number:	85748242
Lab Section:	L2O
Date:			13. Apr, 2023
Purpose:		A implementation of the classic Simon's game memory game on an arduino uno
*/

//define constants etc.
#define Game_Length 5
#define Time_OUT_S 5
int sequence[Game_Length];
long unsigned int time;

#define LED_LOSE 13
#define LEDR 12
#define LEDY 11
#define LEDB 10
#define LEDG 9
#define LED_WIN 8

#define pb_red 7
#define pb_yellow 6
#define pb_blue 5
#define pb_green 4

//define functions prototypes
void DisplaySequence(int sequence[],int index);//generates random sequence from index 0 to i and displays it
int checkSequence(int sequence[],int index); // returns 1 for the correct sequence being entered and 0 otherwise
void reset(int sequence[]);//clears the array
void dispWL(int win);//pass 1 for win and 0 for loss
void StartSequence(void);//turns all the Game LEDs on for 2s , then off and delays for 2 seconds


//initialization
void setup()
{
 
  pinMode(LED_LOSE,OUTPUT);
  pinMode(LED_WIN,OUTPUT);
  pinMode(LEDR,OUTPUT);
  pinMode(LEDY,OUTPUT);
  pinMode(LEDB,OUTPUT);
  pinMode(LEDG,OUTPUT);
  
  pinMode(pb_red,INPUT);
  pinMode(pb_yellow,INPUT);
  pinMode(pb_blue,INPUT);
  pinMode(pb_green,INPUT);
  randomSeed(analogRead(0));
}


//main program loop
void loop()
{
  StartSequence();
  
  for(int i =0; i<Game_Length;i++){
    DisplaySequence(sequence, i);
    if(checkSequence(sequence, i))
    {
    	//does nothing and iterates loop
    }
    else//the sequence was not correctly entered and the game was lost
    {
      dispWL(0);
      break;
    }
    //can only be reached if all the sequences were correctly input and the game was won
    if(i ==Game_Length-1)
    {
      dispWL(1);
    }
      
  }
  reset(sequence);
  
}

void DisplaySequence(int sequence[],int index)//generates random sequence from index 0 to i and displays it
{
  for(int i=0;i<=index;i++){
    if(i==index)
    {
  		sequence[i]=random(9,13);
    }
    digitalWrite(sequence[i],HIGH);
    delay(2000);
    digitalWrite(sequence[i],LOW);
    delay(500);
  }
} 

int checkSequence(int sequence[],int index)// returns 1 for the correct sequence being entered and 0 otherwise
{
  for(int i=0;i<=index;i++){
    time = millis();
    while(digitalRead(sequence[i]-5)==LOW){
      //checks if it has been two Time_OUT_S seconds since the last LED lit up or a button was pressed
      //checks if a wrong button was pressed by comparing the the index in the array (-5 for pin offset) to the digital read of that button
      if(millis()>=Time_OUT_S*1000+time||(digitalRead(pb_red)&&sequence[i]-5!=pb_red)||(digitalRead(pb_yellow)&&sequence[i]-5!=pb_yellow)||(digitalRead(pb_blue)&&sequence[i]-5!=pb_blue)||(digitalRead(pb_green)&&sequence[i]-5!=pb_green)){
      	return 0;
      }
    }
    //keeps the LED associated with a correct button press on while it is pressed
    while(digitalRead(sequence[i]-5)){
    	digitalWrite(sequence[i],HIGH);
    }
    digitalWrite(sequence[i],LOW);
  }
  delay(2000);
  return 1;
}

void reset(int sequence[])//clears the array
{
  for(int i=0;i<Game_Length;i++){
  	sequence[i]=0;
  }
}

void dispWL(int win)
{
  if(win>0){
    digitalWrite(LED_WIN,HIGH);
      delay(1000);
      digitalWrite(LED_WIN,LOW);
      delay(1000);
      digitalWrite(LED_WIN,HIGH);
      delay(1000);
      digitalWrite(LED_WIN,LOW);
      delay(1000);
      digitalWrite(LED_WIN,HIGH);
      delay(1000);
      digitalWrite(LED_WIN,LOW);
  }else{
    digitalWrite(LED_LOSE,HIGH);
      delay(1000);
      digitalWrite(LED_LOSE,LOW);
      delay(1000);
      digitalWrite(LED_LOSE,HIGH);
      delay(1000);
      digitalWrite(LED_LOSE,LOW);
      delay(1000);
      digitalWrite(LED_LOSE,HIGH);
      delay(1000);
      digitalWrite(LED_LOSE,LOW);
  } 

}

void StartSequence(void)
{
	digitalWrite(LEDR,HIGH);
  digitalWrite(LEDY,HIGH);
  digitalWrite(LEDB,HIGH);
  digitalWrite(LEDG,HIGH);
  delay(2000);
  digitalWrite(LEDR,LOW);
  digitalWrite(LEDY,LOW);
  digitalWrite(LEDB,LOW);
  digitalWrite(LEDG,LOW);
  delay(2000);

}
