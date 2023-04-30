#define RT0 86000
#define VCC 5 
#define B 3977 
#define R 86000

#define RT1 7200
#define R1 7200


void setup()
{
 pinMode(A0,INPUT); //Membuat pin input
 pinMode(A1,INPUT); //Membuat pin input
 Serial.begin(9600);
 pinMode(13,OUTPUT); //Membuat pin output
 pinMode(12,OUTPUT); //Membuat pin output
 pinMode(11,OUTPUT); //Membuat pin output
}

void loop()
{
 float T0 = 25 + 273.15;
 
 float suhu_1 = analogRead(A0); //Memasukkan nilai A0 ke suhu 1
 float suhu_2 = analogRead(A1); //Memasukkan nilai A1 ke suhu 2

 // Sensor IATS
 suhu_1 = (5.00 / 1023.00) * suhu_1 ; //Rumus Suhu
 float voltage_1 = VCC - suhu_1;
 float RT = suhu_1 / (voltage_1/R);
 float ln = log(RT/RT0);
 float sensor1 = (1/((ln/B) + (1/T0)));
 sensor1 = (sensor1 - 250.15) - 19.5 ;
 

// Sensor ECT
 suhu_2 = (5.00 / 1023.00) * suhu_2 ; //Rumus Suhu
 float voltage_2 = VCC - suhu_2;
 float RT2 = suhu_2 / (voltage_2/R1);
 float ln1 = log(RT2/RT1);
 float sensor2 = (1/((ln1/B) + (1/T0)));
 sensor2 = (sensor2 - 249.15) - 15.5 ;
  
 //Print Hasil ke Serial Monitor
 Serial.print("Suhu IATS : ");
 Serial.print(sensor1);
 Serial.print("  Suhu ECT : ");
 Serial.println(sensor2);
  
// Settingan Output LED
// Jika Low Lampu Padam
// Jika High Lampu Menyala
  if (sensor2 < 80)
  {
    digitalWrite(11, LOW); 
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
  }
  if (sensor2 >= 80  && sensor2<=100)
  {
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  }
  if (sensor2 > 100)
  {
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
 delay (2000);
}
