int NUM_BTNS = 14;
int NUM_KNOBS = 3;
int NUM_LEDS=4;
int knobs[3];
int btns[14];
int leds[4];

int bytePD = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);//La serial de comunicacion
  pinMode(A0,INPUT); //Modo del pin, en este caso va leer entonces input
                    //A0 en la pi pico es GP26

  pinMode(A1,INPUT);
  pinMode(A2,INPUT);//LOS A# son las terminales analogicas
  
  for(int i = 0; i < NUM_BTNS; i++){
    pinMode(i, INPUT);
  }
  for(int i = 14; i < 18; i++){
    pinMode(i,OUTPUT);
  }
  
}

void loop() {
  
  if (Serial.available() > 0) {
    // read the incoming byte:
    bytePD = Serial.read();
  }

  leerBytes(bytePD); 
  
  knobs[0] = analogRead(A0);
  knobs[1] = analogRead(A1);
  knobs[2] = analogRead(A2);

  

  for(int i = 0; i < NUM_KNOBS; i++){
    Serial.print(knobs[i]);
    Serial.print(" ");  
  }

  
  for(int i = 0; i < NUM_BTNS; i++){
    btns[i] = digitalRead(i);
    Serial.print(btns[i]);
    Serial.print(" ");  
  }
  
  // Serial.print(bytePD);
  // Serial.print(" ");  
  
  
  Serial.println();
  delay(5);


}

void leerBytes(int a){
    switch(a){
      case 0:
        ponerBits(0,0,0,0);break;
      case 1:
        ponerBits(0,0,0,1);break;
      case 2:
        ponerBits(0,0,1,0);break;
      case 3:
        ponerBits(0,0,1,1);break;
      case 4:
        ponerBits(0,1,0,0);break;
      case 5:
        ponerBits(0,1,0,1);break;
      case 6:
        ponerBits(0,1,1,0);break;
      case 7:
        ponerBits(0,1,1,1);break;
      case 8:
        ponerBits(1,0,0,0);break;
      default:
        ponerBits(0,0,0,0);break;

    }


}


void ponerBits(int el3, int el2, int el1, int el0){

  digitalWrite(14, el3);
  digitalWrite(15, el2);
  digitalWrite(16, el1);
  digitalWrite(17, el0);


}