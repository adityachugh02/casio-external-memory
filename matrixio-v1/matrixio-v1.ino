#include <EEPROM.h>

int col_map[] = {11, 12, 13, 14, 15, 16, 2 }; //column pins
int row_map[] = {2, 3, 4, 5, 6, 7, 8, 9, 10 }; //row pins
int addr = 0; //eeprom address
int write_mode = 0;
int instruction_delay = 80;

//sequences:

int sequences[][10] = {{07,01},//avancer de
{07,11},//tourner de
{07,21},//s'orienter à
{07,02},//aller à x,y

{07,37,01},//stylo écrit
{07,37,11},//stylo relevé
{07,37,21},//mettre var à
{07,37,02},//demander valeur

{07,37,00,37,00,01},//commentaire
{07,37,00,37,00,11},//afficher résultat
{07,37,00,37,00,21},//style
{07,37,00,37,00,02},//attendre

{07,37,00,37,00,37,00,01},//répéter
{07,37,00,37,00,37,00,11},//répéter jusqu'à
{07,37,00,37,00,37,00,21},//si alors
{07,37,00,37,00,37,00,02},//si alors sinon

{07,37,00,37,00,37,00,37,00,01},//exécuter
{07,37,00,37,00,37,00,37,00,11},//copier et insérer
{07,37,00,37,00,37,00,37,00,21},//insérer ligne
{07,37,00,37,00,37,00,37,00,02}};//tout supprimer

void setup() {
  Serial.begin(9600);
  DDRD = B11111110;
  DDRB = B111111;
  DDRC = B00000111;

  //pinMode(A7, INPUT_PULLUP); //add pull-up ressistor
  //pinMode(A6, INPUT_PULLUP); //add pull-up ressistor
  pinMode(A5, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  Serial.println("MATRIXIO v1.0 (c) Jan 2022 Aditya Chugh -type 'help'-");
  Serial.println("");
}

void loop() {
  if (Serial.available() > 0) {
    String availableString = Serial.readString();
    availableString.replace(" ", "");
    
    //if (availableString.length() > 3){
      
      if (availableString.indexOf("lear") > 0){
        Serial.print("Clearing prog ");
        Serial.print(availableString[5]);
        Serial.print("...");
        int i = (String(availableString[5]).toInt()-1)*200;
        int f = i + 200;
        for (i; i < f ; i++) {
          EEPROM.write(i, 0);
        }
        Serial.println("Done.");
      } 

      if (availableString.indexOf("ist") > 0){
        int i = (String(availableString[4]).toInt()-1)*200;
        int f = i + 200;
        for (i; i < f ; i++) {
          Serial.print("Address, Instruction: ");
          Serial.print(i);
          Serial.print(", ");
          if (EEPROM.read(i) > 96){
            Serial.print(char(EEPROM.read(i)));
          } else {
            Serial.print(EEPROM.read(i));
          }
          Serial.println("");
        }
        
      }

      if (availableString.indexOf("rog") > 0){
        addr = (String(availableString[4]).toInt() - 1)*200;
        Serial.print("prog " + String(availableString[4]));
        Serial.print(" address: ");
        Serial.println(addr);
      }
      
      if (availableString.indexOf("ddr") > 0){
        String subString = availableString;
        subString.remove(0,4);
        addr = subString.toInt();
        Serial.print("Address set to: ");
        Serial.println(addr);
      }

      if (availableString.indexOf("rite") > 0){
        write_mode = 1;
        Serial.println("Write mode enabled");
      }

      if (availableString.indexOf("ead") > 0){
        write_mode = 0;
        Serial.println("Write mode disabled");
      }

      if (availableString.indexOf("elp") > 0){
        write_mode = 0;
        Serial.println(F("Commands:\n\nxy :         Instruction, where x is column and y is row of calculator key\na~t :        Shortcut instruction sequences\nwrite :      Enable writing of instructions to EEPROM memory\nread :       Disable enable writing of instructions to EEPROM memory\nprog 1~5 :   Memory address set to beginning of program 1~5\nclear 1~5 :  Clears all instructions of program 1~5\nlist 1~5 :   Lists all instructions of program 1~5\naddr 0~999 : Memory address set to 0~999 (for uno & nano)\n"));
        Serial.println(F("On Casio FX-92B & FX-92+, the bottom-most row is matrixed differently, keys should be addressed as such:\n\n'0' : 65\n',' : 64\n'x10^x' : 63\n'ANS/REP' : 62\n'EXE' : 61\n"));
        Serial.println(F("Shortcut instruction sequences for Casio FX-92+:\n\na : avancer de\nb : tourner de\nc : s'orienter à\nd : aller à x,y\n\ne : stylo écrit\nf : stylo relevé\ng : mettre var à\nh : demander valeur\n\ni : commentaire\nj : afficher résultat\nk : style\nl : attendre\n\nm : répéter\nn : répéter jusqu'à\no : si alors\np : si alors sinon\n\nq : exécuter\nr : copier et insérer\ns : insérer ligne\nt : tout supprimer\n"));
      }
      
    //}
  
    if (availableString.length() == 3){
      str_to_button_press(availableString);
      if (write_mode == 1){
        str_to_int_to_eeprom(availableString);
      }
    }

    if (availableString.length() == 2){
      sequence_to_button_press(availableString);
      if (write_mode == 1){
        int i = availableString[0];
        str_to_int_to_eeprom(String(i));
      }
    }
  }
  /*if (analogRead(A7) == 0) {
    Serial.println("Program 5");
    eeprom_read(800);
  }
  if (digitalRead(A6) == LOW) {
    Serial.println("Program 4");
    eeprom_read(600);
  }*/
  if (digitalRead(A5) == LOW) {
    Serial.println("Program 3");
    eeprom_read(400);
  }
  if (digitalRead(A4) == LOW) {
    Serial.println("Program 2");
    eeprom_read(200);
  }
  if (digitalRead(A3) == LOW) {
    Serial.println("Program 1");
    eeprom_read(0);
  }
}

void str_to_button_press(String availableString){
  
  int col = String(availableString[0]).toInt();
  int row = String(availableString[1]).toInt();
  Serial.print ("Address, Instruction: ");
  Serial.print(addr);
  Serial.print("," ),
  Serial.print(col);
  Serial.print(row);
  Serial.println("");
  digitalWrite(col_map[col], HIGH);
  digitalWrite(row_map[row], HIGH);
  delay(instruction_delay);
  digitalWrite(col_map[col], LOW);
  digitalWrite(row_map[row], LOW);
  delay(20);
  if (availableString == "61"){
    delay(500);
  }
}

void str_to_int_to_eeprom (String availableString){
  EEPROM.write(addr, availableString.toInt());
  addr = addr + 1;
}

void sequence_to_button_press (String availableString){
  int sequence = int(availableString[0])-97;
  Serial.print("Address, Instruction: ");
  Serial.print(addr);
  Serial.print("," ),
  Serial.println(availableString[0]);
  for (int i = 0 ; i < 10 ; i++){
    str_to_button_press(int_to_str(sequences[sequence][i]));
  }
}

String int_to_str (int Int){
  if (Int > 10){
    return String(Int);
  } else {
    if (0 < Int < 10){
      String subString = "0";
      subString += String(Int);
      return(subString);
    }
  }
}

void eeprom_read(int Start){
  int Stop = Start + 200;
  for (addr = Start; addr < Stop ; addr++) {
    if (EEPROM.read(addr) > 96){
      sequence_to_button_press(String(char(EEPROM.read(addr))));
    } else {
      str_to_button_press(int_to_str(EEPROM.read(addr)));
    }
  }
  addr = 0;
}
