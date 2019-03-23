/* 
* Arduino Uno
* 
* A0: NC
* A1: NC
* A2: NC
* A3: NC
* A4: NC
* A5: NC
* 
* pin0 : NC
* pin1 : NC
* pin2 : NC
* pin3 : NC
* 
* pin4 : NC
* pin5 : NC
* pin6 : NC
* pin7 : NC
* pin8 : NC
* 
* pin9 : NC
* pin10 : NC
* pin11 : NC
* pin12 : NC
* pin13 : NC 
* 
* I2C : NC
* I2C : NC
* 
* Shield Ethernet sans POE
* 
*/

#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>

//Shield Ethernet sans Aoe Numero 2
byte mac[]={0x90,0xA2,0xDA,0x0F,0x21,0xAD};
IPAddress ip_shield(192,168,1,205);

//TCP Protocole
unsigned int port_local=5500;
EthernetServer server(port_local);

String save_message;
String cmd_message;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Début Setup");
  Ethernet.begin(mac,ip_shield);
  server.begin();
  Serial.println("Fin Setup");
}

void loop() 
{
  // Protocole TCP
  String conv_message_to_string;
  EthernetClient client = server.available();
  
  //Capteur
  float capteur1 = 10.10;
  int capteur2 = 20;
  String string_capteur1 (capteur1);
  String string_capteur2 (capteur2);
//  Serial.print("capteur1 : ");
//  Serial.println(string_capteur1);
//  Serial.print("capteur2 : ");
//  Serial.println(string_capteur2);

  //Requete TCP
 if (client) 
 {
    client.flush();
    conv_message_to_string="";  
    while (client.available() > 0) 
    {
      char c = client.read();
      conv_message_to_string+=c;
//      Serial.print("Commande b4a :");
//      Serial.println(conv_message_to_string);
    }
    Serial.print("Commande b4a :");
    Serial.println(conv_message_to_string);
    
    if(conv_message_to_string=="Acquer")
    {
      save_message=conv_message_to_string;   
    }
    else
    {
      cmd_message=conv_message_to_string;
    }
    
    if (save_message=="Acquer") 
    {
      Serial.println("Client connecte");
      Serial.print("Message : ");
      Serial.println(conv_message_to_string);
      Serial.print("capteur1 : ");
      Serial.println(string_capteur1);
      Serial.print("capteur2 : ");
      Serial.println(string_capteur2);
      client.print("Message recu :"+conv_message_to_string+"\n"+"Capteur1 : "+string_capteur1+"\n"+"capteur2 : "+string_capteur2);
     }
     conv_message_to_string="";  
  }

  /*Liste instruction pour B4A :
   * Arrete : Arreter le store
   */

   if(cmd_message=="Arrete")
   {
    Serial.println("Action de l'arduino");
    cmd_message="";
   }
}