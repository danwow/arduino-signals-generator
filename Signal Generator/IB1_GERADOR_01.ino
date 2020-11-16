#define AMP_MIN 0
#define AMP_MAX 500
#define FREQ_MAX 1000
#define FREQ_MIN 1

//Tensão minima e máxima suportadas pela porta DAC: 520mV - 2,80V ( Documentação Arduino - https://forum.arduino.cc/index.php?topic=154965.0 )

int Q, T, S;
float pot, periodo, _periodo, rad, pontos, conv;
float seno[360];
float pi = 3.14159265359;

void setup() {
  Serial.begin(115200);
  analogWriteResolution(12);
  pinMode(7, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  
  rad = 2 * pi;
  pontos = rad / 360;

  for (int i = 0; i <= 360; i++)
  {
    seno[i] = (sin(i * pontos) * (AMP_MAX - AMP_MIN)/2) + (AMP_MAX + AMP_MIN)/2;

    //Valores minimos e maximos de tensão = 520mV - 2.8V
    
  }

}

void loop() {
  Q = digitalRead(5); //Onda Quadrada
  T = digitalRead(6); //Onda triangular
  S = digitalRead(7); //Onda senoidal

  pot = analogRead(A1);

  conv = map(pot,0,1023,FREQ_MIN,FREQ_MAX);
  //Serial.println(1000.0/periodo); // Frequencia em Hz
  periodo = 1000/conv;
  
  if (Q == 0)
  { //Onda quadrada
    
    for (int i = AMP_MIN; i < AMP_MAX; i+=2)
    {
      Serial.println(AMP_MAX);
      delay(periodo);
    }

    for (int i = AMP_MAX; i > AMP_MIN; i-=2)
    {
      Serial.println(AMP_MIN);
      delay(periodo);
   
  }
  }
  if (T == 0)
  { //Onda triangular

    for (int i = AMP_MIN; i <= AMP_MAX; i+=2)
    {
      Serial.println(i);
      delay(periodo);
    }

    for (int i = AMP_MAX; i > AMP_MIN; i-=2)
    {
      Serial.println(i);
      delay(periodo);
    }

  }

  if (S == 0)
  { //Onda senoidal


    for (int i = 0; i <= 360; i++)
    {
     Serial.println(seno[i]);
     delay(periodo);
    }
  }

  else
  {
     Serial.println(0);
     

  }
}
