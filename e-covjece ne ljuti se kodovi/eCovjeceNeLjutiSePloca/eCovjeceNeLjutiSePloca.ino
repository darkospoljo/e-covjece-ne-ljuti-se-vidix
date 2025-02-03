#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <esp_now.h>
#include <WiFi.h>

int crvenikuca = 4, plavikuca = 4, zelenikuca = 4, zutikuca = 4;
int kockabroj = 0, Igrac = 1, brojPokusaja = 0, start = 0; 
int provjeraCrveni = 0;
int provjeraPlavi = 0;
int provjeraZeleni = 0;
int provjeraZuti = 0;
int crveni[] = {0, -1, -1, -1, -1};
int crveni_[] = {0, -1, -1, -1, -1};
int plavi[] = {0, -1, -1, -1, -1};
int plavi_[] = {0, -1, -1, -1, -1};
int zeleni[] = {0, -1, -1, -1, -1};
int zeleni_[] = {0, -1, -1, -1, -1};
int zuti[] = {0, -1, -1, -1, -1};
int zuti_[] = {0, -1, -1, -1, -1};
int crveniKraj[] = {0, -1, -1, -1, -1};
int plaviKraj[] = {0, -1, -1, -1, -1};
int zeleniKraj[] = {0, -1, -1, -1, -1};
int zutiKraj[] = {0, -1, -1, -1, -1};

int kockabroj1;
int crvenikraj;
unsigned long previousTime = 0;
bool klik;
bool igracc[5];
typedef struct struct_message {
  //int kockabroj;
  bool klik;
  bool igracc[5];
} struct_message;

struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println("Klik");
  for(int i = 1; i <= 4; i++){
    if(myData.igracc[i] == true){
      Serial.println(i);
    }
    //myData.igracc[i] = false;
  }
  Serial.println("---------");
}
#define StazaPin 38
#define StazaBroj 40
Adafruit_NeoPixel Staza(StazaBroj, StazaPin, NEO_GRB + NEO_KHZ800);

#define KucaBroj 4

#define CrveniKucaPin 10
Adafruit_NeoPixel Crveni(KucaBroj, CrveniKucaPin, NEO_GRB + NEO_KHZ800);

#define PlaviKucaPin 12
Adafruit_NeoPixel Plavi(KucaBroj, PlaviKucaPin, NEO_GRB + NEO_KHZ800);

#define ZeleniKucaPin 21
Adafruit_NeoPixel Zeleni(KucaBroj, ZeleniKucaPin, NEO_GRB + NEO_KHZ800);

#define ZutiKucaPin 18
Adafruit_NeoPixel Zuti(KucaBroj, ZutiKucaPin, NEO_GRB + NEO_KHZ800);

#define CrveniKrajPin 8
Adafruit_NeoPixel CrveniKraj(KucaBroj, CrveniKrajPin, NEO_GRB + NEO_KHZ800);

#define PlaviKrajPin 11
Adafruit_NeoPixel PlaviKraj(KucaBroj, PlaviKrajPin, NEO_GRB + NEO_KHZ800);

#define ZeleniKrajPin 13
Adafruit_NeoPixel ZeleniKraj(KucaBroj, ZeleniKrajPin, NEO_GRB + NEO_KHZ800);

#define ZutiKrajPin 14
Adafruit_NeoPixel ZutiKraj(KucaBroj, ZutiKrajPin, NEO_GRB + NEO_KHZ800);

#define KockaPin 3
#define KockaLEDBroj 7
Adafruit_NeoPixel Kocka(KockaLEDBroj, KockaPin, NEO_GRB + NEO_KHZ800);
#define BRIGTNESS2020 30
uint32_t Crvena = Crveni.Color(255, 0, 0);
uint32_t Plava = Plavi.Color(0, 0, 255);
uint32_t Zelena = Zeleni.Color(0, 255, 0);
uint32_t Zuta = Zuti.Color(255, 255, 0);
uint32_t Bijela = Staza.Color(30, 30, 30);
uint32_t Bijela1 = PlaviKraj.Color(5, 5, 5);
uint32_t Ljubicasta = Kocka.Color(255, 0, 255);
uint32_t boja[5];
void setup() {
  boja[1] = Kocka.Color(255, 0, 0);
  boja[2] = Kocka.Color(0, 0, 255);
  boja[3] = Kocka.Color(0, 255, 0);
  boja[4] = Kocka.Color(255, 255, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  pinMode(StazaPin, OUTPUT);
  Staza.begin();
  Staza.setBrightness(30);
  Staza.clear();
  for(int i = 0; i <= StazaBroj; i++){
    Staza.setPixelColor(i, Staza.Color(50, 50, 50));
    Staza.show();
    delay(10);
  }
  pinMode(CrveniKucaPin, OUTPUT);
  Crveni.begin();
  Crveni.setBrightness(BRIGTNESS2020);
  Crveni.clear();
  for(int i = 0; i <= KucaBroj; i++){
    Crveni.setPixelColor(i, Crveni.Color(255, 0, 0));
    Crveni.show();
    delay(100);
  }
  pinMode(PlaviKucaPin, OUTPUT);
  Plavi.begin();
  Plavi.setBrightness(BRIGTNESS2020);
  Plavi.clear();
  for(int i = 0; i <= KucaBroj; i++){
    Plavi.setPixelColor(i, Plavi.Color(0, 0, 255));
    Plavi.show();
    delay(100);
  }
  pinMode(ZeleniKucaPin, OUTPUT);
  Zeleni.begin();
  Zeleni.setBrightness(BRIGTNESS2020);
  Zeleni.clear();
  for(int i = 0; i <= KucaBroj; i++){
    Zeleni.setPixelColor(i, Zeleni.Color(0, 255, 0));
    Zeleni.show();
    delay(100);
  }
  pinMode(ZutiKucaPin, OUTPUT);
  Zuti.begin();
  Zuti.setBrightness(BRIGTNESS2020);
  Zuti.clear();
  for(int i = 0; i <= KucaBroj; i++){
    Zuti.setPixelColor(i, Zuti.Color(255, 255, 0));
    Zuti.show();
    delay(100);
  }
  pinMode(CrveniKrajPin, OUTPUT);
  CrveniKraj.begin();
  CrveniKraj.setBrightness(BRIGTNESS2020);
  CrveniKraj.clear();
  for(int i = 0; i <= KucaBroj; i++){
    CrveniKraj.setPixelColor(i, CrveniKraj.Color(255, 0, 0));
    CrveniKraj.show();
    delay(100);
  }
  pinMode(PlaviKrajPin, OUTPUT);
  PlaviKraj.begin();
  PlaviKraj.setBrightness(BRIGTNESS2020);
  PlaviKraj.clear();
  for(int i = 0; i <= KucaBroj; i++){
    PlaviKraj.setPixelColor(i, PlaviKraj.Color(0, 0, 255));
    PlaviKraj.show();
    delay(100);
  }
  pinMode(ZeleniKrajPin, OUTPUT);
  ZeleniKraj.begin();
  ZeleniKraj.setBrightness(BRIGTNESS2020);
  ZeleniKraj.clear();
  for(int i = 0; i <= KucaBroj; i++){
    ZeleniKraj.setPixelColor(i, ZeleniKraj.Color(0, 255, 0));
    ZeleniKraj.show();
    delay(100);
  }
  pinMode(ZutiKrajPin, OUTPUT);
  ZutiKraj.begin();
  ZutiKraj.setBrightness(BRIGTNESS2020);
  ZutiKraj.clear();
  for(int i = 0; i <= KucaBroj; i++){
    ZutiKraj.setPixelColor(i, ZutiKraj.Color(255, 255, 0));
    ZutiKraj.show();
    delay(100);
  }
  pinMode(KockaPin, OUTPUT);
  Kocka.begin();
  Kocka.setBrightness(BRIGTNESS2020);
  Kocka.clear();
  for(int i = 0; i <= KockaLEDBroj; i++){
    Kocka.setPixelColor(i, Kocka.Color(255, 255, 255));
    Kocka.show();
    delay(100);
  }
  
  //Staza.clear();
  //Crveni.clear();
  //Plavi.clear();
  //Zeleni.clear();
  //Zuti.clear();
  CrveniKraj.clear();
  PlaviKraj.clear();
  ZeleniKraj.clear();
  ZutiKraj.clear();
  Kocka.clear();
  //Staza.show();
  //Crveni.show();
  //Plavi.show();
  //Zeleni.show();
  //Zuti.show();
  CrveniKraj.show();
  PlaviKraj.show();
  ZeleniKraj.show();
  ZutiKraj.show();
  Kocka.show();
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}
void kocka(){
  switch(kockabroj){
    case 0:
    {
      Kocka.clear();
      Kocka.show();
      break;
    }
    case 1:
    {
      Kocka.clear();
      Kocka.setPixelColor(0, boja[Igrac]);
      Kocka.show();
      break;
    }
    case 2:
    {
      Kocka.clear();
      Kocka.setPixelColor(1, boja[Igrac]);
      Kocka.setPixelColor(4, boja[Igrac]);
      Kocka.show();
      break;
    }
    case 3:
    {
      Kocka.clear();
      Kocka.setPixelColor(0, boja[Igrac]);
      Kocka.setPixelColor(1, boja[Igrac]);
      Kocka.setPixelColor(4, boja[Igrac]);
      Kocka.show();
      break;
    }
    case 4:
    {
      Kocka.clear();
      Kocka.setPixelColor(1, boja[Igrac]);
      Kocka.setPixelColor(3, boja[Igrac]);
      Kocka.setPixelColor(4, boja[Igrac]);
      Kocka.setPixelColor(6, boja[Igrac]);
      Kocka.show();
      break;
    }
    case 5:
    {
      Kocka.clear();
      Kocka.setPixelColor(0, boja[Igrac]);
      Kocka.setPixelColor(1, boja[Igrac]);
      Kocka.setPixelColor(3, boja[Igrac]);
      Kocka.setPixelColor(4, boja[Igrac]);
      Kocka.setPixelColor(6, boja[Igrac]);
      Kocka.show();
      break;
    }
    case 6:
    {
      Kocka.clear();
      Kocka.setPixelColor(1, boja[Igrac]);
      Kocka.setPixelColor(2, boja[Igrac]);
      Kocka.setPixelColor(3, boja[Igrac]);
      Kocka.setPixelColor(4, boja[Igrac]);
      Kocka.setPixelColor(5, boja[Igrac]);
      Kocka.setPixelColor(6, boja[Igrac]);
      Kocka.show();
      break;
    }
  }
}
void staza(){
  unsigned long currentTime = millis();
  Staza.clear();
  Staza.fill(Bijela, 0);
  for(int j = 1; j <= 4; j++){
    Staza.setPixelColor(crveni_[j], Crvena);
    if(plaviKraj[j] < 0){
      Staza.setPixelColor(plavi_[j], Plava);
    }
    if(zeleniKraj[j] < 0){
      Staza.setPixelColor(zeleni_[j], Zelena);
    }
    if(zutiKraj[j] < 0){
      Staza.setPixelColor(zuti_[j], Zuta);
    }
  }
  Staza.show();
}
void CrvenaKuca(){
  Crveni.clear();
  Crveni.fill(Crvena, 0, crvenikuca);
  if(crvenikuca == 0){
    Crveni.clear();
  }
  Crveni.show();
}
void PlavaKuca(){
  Plavi.clear();
  Plavi.fill(Plava, 0, plavikuca);
  if(plavikuca == 0){
    Plavi.clear();
  }
  Plavi.show();
}
void ZelenaKuca(){
  Zeleni.clear();
  Zeleni.fill(Zelena, 0, zelenikuca);
  if(zelenikuca == 0){
    Zeleni.clear();
  }
  Zeleni.show();
}
void ZutaKuca(){
  Zuti.clear();
  Zuti.fill(Zuta, 0, zutikuca);
  if(zutikuca == 0){
    Zuti.clear();
  }
  Zuti.show();
}
void Crvenikraj(){
  CrveniKraj.clear();
  CrveniKraj.fill(Bijela1, 0);
  for(int j = 1; j <= 4; j++){
    CrveniKraj.setPixelColor(crveniKraj[j], Crvena);
  }
  CrveniKraj.show();
}
void Plavikraj(){
  PlaviKraj.clear();
  PlaviKraj.fill(Bijela1, 0);
  for(int j = 1; j <= 4; j++){
    PlaviKraj.setPixelColor(plaviKraj[j], Plava);
  }
  PlaviKraj.show();
}
void Zelenikraj(){
  ZeleniKraj.clear();
  ZeleniKraj.fill(Bijela1, 0);
  for(int j = 1; j <= 4; j++){
    ZeleniKraj.setPixelColor(zeleniKraj[j], Zelena);
  }
  ZeleniKraj.show();
}
void Zutikraj(){
  ZutiKraj.clear();
  ZutiKraj.fill(Bijela1, 0);
  for(int j = 1; j <= 4; j++){
    ZutiKraj.setPixelColor(zutiKraj[j], Zuta);
  }
  ZutiKraj.show();
}
void igrac(){
  if(Igrac == 1){
    if(crvenikuca == 4){
      if(brojPokusaja == 3 && kockabroj != 6){
        //delay(500);
        Igrac++;
        brojPokusaja = 0;
        kockabroj = 0;
        kockabroj1 = 0;
      }
      else{
        if(myData.klik == true && kockabroj != 6){
          kockabroj = 0;
          kocka();
          delay(100);
          kockabroj = random(6, 7);
          //kockabroj = 6;
          brojPokusaja++;
          myData.klik = false;
          delay(500);
        }
        if(kockabroj == 6){
          for(int i = 1; i <= 4; i++){
            if(myData.igracc[i] == true){
              crveni[i] = 0;
              crveni_[i] = 0;
              crvenikuca--;
              CrvenaKuca();
              Staza.setPixelColor(crveni[i], Crvena);
              Staza.show();
              brojPokusaja = 0;
              kockabroj = 0;
              kockabroj1 = 0;
              myData.igracc[i] = false;
            }
          }
        }
      }
    }
    else if(crvenikuca < 4){
      if(brojPokusaja == 1){
        Igrac++;
        brojPokusaja = 0;
        kockabroj = 0;
        kockabroj1 = 0;
        kocka();
        
      }
      else{
        if(myData.klik == true && kockabroj == 0){
          kockabroj = 0;
          kocka();
          delay(100);
          kockabroj = random(1, 7);
          kocka();
          kockabroj1 = kockabroj;
          myData.klik = false;
        }
        for(int i = 1; i <= 4; i++){
          if(myData.igracc[i] == true && crveni[i] < 0 && kockabroj == 6){
            crvenikuca--;
            CrvenaKuca();
            crveni[i] = 0;
            crveni_[i] = 0;
            Staza.setPixelColor(crveni[i], Crvena);
            Staza.show();
            kockabroj = 0;
            kockabroj1 = 0;
            kocka();
            myData.igracc[i] = false;
          }
          else if(myData.igracc[i] == true && crveni[i] >= 0){
            if(crveni[i] < 0 && kockabroj == 6){
              crvenikuca--;
              CrvenaKuca();
              crveni[i] = 0;
              crveni_[i] = 0;
              Staza.setPixelColor(crveni[i], Crvena);
              Staza.show();
              kockabroj = 0;
              kocka();
              myData.igracc[i] = false;
            }
            else if((crveni[i] >= 0) && (crveni[i] + kockabroj <= 43)){
              for(int j = crveni[i]; j <= crveni[i] + kockabroj1; j++){
                //crveni[i] = j;
                crveni_[i] = j;
                staza();
                delay(500);
                if(j > 39){
                  crveniKraj[i] = j - 40;
                  CrveniKraj.setPixelColor(crveniKraj[i], Crvena);
                  CrveniKraj.setPixelColor(crveniKraj[i-1], Bijela);
                  CrveniKraj.show();
                }
                
              }
            }
            crveni[i] = crveni[i] + kockabroj1;
            kocka();
            for(int k = 1; k <= 4; k++){
              if(crveni[i] == plavi[k]){
                plavi[k] = -1;
                plavikuca++;
                //PlavaKuca();
              }
              else if(crveni[i] == zeleni[k]){
                zeleni[k] = -1;
                zelenikuca++;
                //ZelenaKuca();
              }
              else if(crveni[i] == zuti[k]){
                zuti[k] = -1;
                zutikuca++;
                //ZutaKuca();
              }
            }
            staza();
            if(kockabroj != 6){
              brojPokusaja++;
              
            }
            else{
              kockabroj = 0;
              kockabroj1 = 0;
            }
          }
        }
      }
    }
  }
  else if(Igrac == 2){
    
    if(plavikuca == 4){
      if(brojPokusaja == 3 && kockabroj != 6){
        //delay(500);
        Igrac++;
        brojPokusaja = 0;
        kockabroj = 0;
        kockabroj1 = 0;
      }
      else{
        if(myData.klik == true && kockabroj != 6){
          kockabroj = 0;
          kocka();
          delay(100);
          kockabroj = random(6, 7);
          //kockabroj = 6;
          brojPokusaja++;
          myData.klik = false;
          //delay(500);
        }
        if(kockabroj == 6){
          for(int i = 1; i <= 4; i++){
            if(myData.igracc[i] == true){
              plavi[i] = 10;
              plavi_[i] = 10;
              plavikuca--;
              PlavaKuca();
              Staza.setPixelColor(plavi[i], Plava);
              Staza.show();
              brojPokusaja = 0;
              kockabroj = 0;
              kockabroj1 = 0;
              myData.igracc[i] = false;
            }
          }
        }
      }
    }
    else if(plavikuca < 4){
      if(brojPokusaja == 1){
        Igrac++;
        brojPokusaja = 0;
        kockabroj = 0;
        kockabroj1 = 0;
        kocka();
        
      }
      else{
        if(myData.klik == true && kockabroj == 0){
          kockabroj = 0;
          kocka();
          delay(100);
          kockabroj = random(1, 7);
          kocka();
          kockabroj1 = kockabroj;
          myData.klik = false;
        }
        for(int i = 1; i <= 4; i++){
          if(myData.igracc[i] == true && plavi[i] < 0 && kockabroj == 6){
            plavikuca--;
            PlavaKuca();
            plavi[i] = 10;
            plavi_[i] = 10;
            Staza.setPixelColor(plavi[i], Plava);
            Staza.show();
            kockabroj = 0;
            kockabroj1 = 0;
            kocka();
            myData.igracc[i] = false;
          }
          else if(myData.igracc[i] == true && plavi[i] >= 0){
            if(plavi[i] < 0 && kockabroj == 6){
              plavikuca--;
              PlavaKuca();
              plavi[i] = 10;
              plavi_[i] = 10;
              Staza.setPixelColor(plavi[i], Plava);
              Staza.show();
              kockabroj = 0;
              kocka();
              myData.igracc[i] = false;
            }
            else if((plavi[i] >= 0) && (plavi[i] + kockabroj <= 53)){
              for(int j = plavi[i]; j <= plavi[i] + kockabroj1; j++){
                //crveni[i] = j;
                plavi_[i] = j;
                
                //staza();
                delay(500);
                if(j <= 39){
                  plavi_[i] = j;
                }
                else if(j > 39 && j <= 49){
                  plavi_[i] = j - 40;
                }
                else if(j > 49){
                  plaviKraj[i] = j - 50;
                }
                Plavikraj();
                staza();
                //delay(500);
                
              }
            }
            plavi[i] = plavi[i] + kockabroj1;
            kocka();
            for(int k = 1; k <= 4; k++){
              if(crveni[i] == plavi[k]){
                plavi[k] = -1;
                plavikuca++;
                //PlavaKuca();
              }
              else if(crveni[i] == zeleni[k]){
                zeleni[k] = -1;
                zelenikuca++;
                //ZelenaKuca();
              }
              else if(crveni[i] == zuti[k]){
                zuti[k] = -1;
                zutikuca++;
                //ZutaKuca();
              }
            }
            staza();
            if(kockabroj != 6){
              brojPokusaja++;
              
            }
            else{
              kockabroj = 0;
              kockabroj1 = 0;
            }
          }
        }
      }
    }
  }
  else if(Igrac == 3){
    
    if(zelenikuca == 4){
      if(brojPokusaja == 3 && kockabroj != 6){
        //delay(500);
        Igrac++;
        brojPokusaja = 0;
        kockabroj = 0;
        kockabroj1 = 0;
      }
      else{
        if(myData.klik == true && kockabroj != 6){
          kockabroj = 0;
          kocka();
          delay(100);
          kockabroj = random(6, 7);
          //kockabroj = 6;
          brojPokusaja++;
          myData.klik = false;
          //delay(500);
        }
        if(kockabroj == 6){
          for(int i = 1; i <= 4; i++){
            if(myData.igracc[i] == true){
              zeleni[i] = 20;
              zeleni_[i] = 20;
              zelenikuca--;
              ZelenaKuca();
              Staza.setPixelColor(zeleni[i], Zelena);
              Staza.show();
              brojPokusaja = 0;
              kockabroj = 0;
              kockabroj1 = 0;
              myData.igracc[i] = false;
            }
          }
        }
      }
    }
    else if(zelenikuca < 4){
      if(brojPokusaja == 1){
        Igrac++;
        brojPokusaja = 0;
        kockabroj = 0;
        kockabroj1 = 0;
        kocka();
        
      }
      else{
        if(myData.klik == true && kockabroj == 0){
          kockabroj = 0;
          kocka();
          delay(100);
          kockabroj = random(1, 7);
          kocka();
          kockabroj1 = kockabroj;
          myData.klik = false;
        }
        for(int i = 1; i <= 4; i++){
          if(myData.igracc[i] == true && zeleni[i] < 0 && kockabroj == 6){
            zelenikuca--;
            ZelenaKuca();
            zeleni[i] = 0;
            zeleni_[i] = 0;
            Staza.setPixelColor(zeleni[i], Zelena);
            Staza.show();
            kockabroj = 0;
            kockabroj1 = 0;
            kocka();
            myData.igracc[i] = false;
          }
          else if(myData.igracc[i] == true && zeleni[i] >= 0){
            if(zeleni[i] < 0 && kockabroj == 6){
              zelenikuca--;
              ZelenaKuca();
              zeleni[i] = 20;
              zeleni_[i] = 20;
              Staza.setPixelColor(zeleni[i], Zelena);
              Staza.show();
              kockabroj = 0;
              kocka();
              myData.igracc[i] = false;
            }
            else if((zeleni[i] >= 0) && (zeleni[i] + kockabroj <= 63)){
              for(int j = zeleni[i]; j <= zeleni[i] + kockabroj1; j++){
                //crveni[i] = j;
                zeleni_[i] = j;
                
                staza();
                delay(500);
                if(j <= 39){
                  zeleni_[i] = j;
                }
                else if(j > 39 && j <= 59){
                  zeleni_[i] = j - 40;
                }
                else if(j > 49){
                  zeleniKraj[i] = j - 60;
                }
                Zelenikraj();
                staza();
                //delay(500);
                
              }
            }
            zeleni[i] = zeleni[i] + kockabroj1;
            kocka();
            for(int k = 1; k <= 4; k++){
              if(crveni[i] == plavi[k]){
                plavi[k] = -1;
                plavikuca++;
                PlavaKuca();
              }
              else if(crveni[i] == zeleni[k]){
                zeleni[k] = -1;
                zelenikuca++;
                ZelenaKuca();
              }
              else if(crveni[i] == zuti[k]){
                zuti[k] = -1;
                zutikuca++;
                ZutaKuca();
              }
            }
            staza();
            if(kockabroj != 6){
              brojPokusaja++;
              
            }
            else{
              kockabroj = 0;
              kockabroj1 = 0;
            }
          }
        }
      }
    }
  }
  else if(Igrac == 4){
    
    if(zutikuca == 4){
      if(brojPokusaja == 3 && kockabroj != 6){
        Igrac = 1;
        brojPokusaja = 0;
        kockabroj = 0;
        kockabroj1 = 0;
      }
      else{
        if(myData.klik == true && kockabroj != 6){
          kockabroj = 0;
          kocka();
          delay(100);
          kockabroj = random(6, 7);
          brojPokusaja++;
          myData.klik = false;
        }
        if(kockabroj == 6){
          for(int i = 1; i <= 4; i++){
            if(myData.igracc[i] == true){
              zuti[i] = 30;
              zuti_[i] = 30;
              zutikuca--;
              ZutaKuca();
              Staza.setPixelColor(zuti[i], Zuta);
              Staza.show();
              brojPokusaja = 0;
              kockabroj = 0;
              kockabroj1 = 0;
              myData.igracc[i] = false;
            }
          }
        }
      }
    }
    else if(zutikuca < 4){
      if(brojPokusaja == 1){
        Igrac = 1;
        brojPokusaja = 0;
        kockabroj = 0;
        kockabroj1 = 0;
        kocka();
        
      }
      else{
        if(myData.klik == true && kockabroj == 0){
          kockabroj = 0;
          kocka();
          delay(100);
          kockabroj = random(1, 7);
          kocka();
          kockabroj1 = kockabroj;
          myData.klik = false;
        }
        for(int i = 1; i <= 4; i++){
          if(myData.igracc[i] == true && zuti[i] < 0 && kockabroj == 6){
            zutikuca--;
            ZutaKuca();
            zuti[i] = 30;
            zuti_[i] = 30;
            Staza.setPixelColor(zuti[i], Zuta);
            Staza.show();
            kockabroj = 0;
            kockabroj1 = 0;
            kocka();
            myData.igracc[i] = false;
          }
          else if(myData.igracc[i] == true && zuti[i] >= 0){
            if(zuti[i] < 0 && kockabroj == 6){
              zutikuca--;
              ZutaKuca();
              zuti[i] = 30;
              zuti_[i] = 30;
              Staza.setPixelColor(zuti[i], Zuta);
              Staza.show();
              kockabroj = 0;
              kocka();
              myData.igracc[i] = false;
            }
            else if((zuti[i] >= 0) && (zuti[i] + kockabroj <= 63)){
              for(int j = zuti[i]; j <= zuti[i] + kockabroj1; j++){
                zuti_[i] = j;
                //staza();
                delay(500);
                if(j <= 39){
                  zuti_[i] = j;
                }
                else if(j > 39 && j <= 59){
                  zuti_[i] = j - 40;
                }
                else if(j > 49){
                  zutiKraj[i] = j - 60;
                }
                Zutikraj();
                staza();
                //delay(500);
                
              }
            }
            zuti[i] = zuti[i] + kockabroj1;
            kocka();
            for(int k = 1; k <= 4; k++){
              if(crveni[i] == plavi[k]){
                plavi[k] = -1;
                plavikuca++;
                PlavaKuca();
              }
              else if(crveni[i] == zeleni[k]){
                zeleni[k] = -1;
                zelenikuca++;
                ZelenaKuca();
              }
              else if(crveni[i] == zuti[k]){
                zuti[k] = -1;
                zutikuca++;
                ZutaKuca();
              }
            }
            staza();
            if(kockabroj != 6){
              brojPokusaja++;
              
            }
            else{
              kockabroj = 0;
              kockabroj1 = 0;
            }
          }
        }
      }
    }
  }
}
void loop() {
  if(start == 0){
    if(myData.klik == true){
      start = 1;
      Serial.println("Start = 1");
      myData.klik = false;
    }
  }
  if(start == 1){
    igrac();
    kocka();
    staza();
  }
}



















//Ovo nije finalna verzija koda
//Ovaj kod još treba nadogradnju
//Napomena: Ako se kod ne compila u arduino IDE -> koristiti platformIO i VSCode