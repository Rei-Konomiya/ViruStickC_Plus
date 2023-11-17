#include <M5StickCPlus.h>
#include <BleKeyboard.h>
#include <pass.h>

//画面の大きさ　縦135, 横240

BleKeyboard bleKeyboard("未接続");

bool blestate = false;
bool selecting = false;
int mode = 0;
int tf = true;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int getRandom(int min, int max){
  return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

void sendString(char str[], int delaytime){
  int spellnum = strlen(str);
  for(int i=0; i<spellnum; i++){
    bleKeyboard.print(str[i]);
    delay(delaytime);
  }
}


//**************************************************************

#define MODE_MAX 2+ 26

String modelist[] =
{
  "safety mode",

  "PR:Win + Lock", "sleep", "shut down",                                      // 3
  "allDeleted, lol :)", "save & close",                                       // 2 ...5
  "Win + 1~0", "Shift + Win + 1~0",                                           // 2 ...7
  "R:change resolution", "touch pad", "L:hyper zoom", "R:rand screenRotate",  // 4 ...11
  "R:mouse reverse",                                                          // 1 ...12
  "high contrast", "LB:reverse Color",                                        // 2 ...14
  "rand app select", "L:while (Alt + Esc)", "L:rand window move",             // 3 ...17
  "show desktop", "new desktop", "desktop icon",                              // 3 ...20
  "dir /s", "explorer", "task manager",                                       // 3 ...23
  "Alt + F4", "S:Alt + while (Tab)",                                          // 2 ...25
  "M:Mix treat",                                                              // 1 ...26

  "BLE Disconnect"
};

//**************************************************************


void sendCommand(){

  if(modelist[mode] == "safety mode"){

  }else if(modelist[mode] == "PR:Win + Lock"){
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("l");
    bleKeyboard.releaseAll();
    delay(200);
    M5.update();
    if(M5.BtnA.isPressed()) bleKeyboard.println(myPcPass);

  }else if(modelist[mode] == "sleep"){
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("x");
    bleKeyboard.releaseAll();
    delay(500);
    bleKeyboard.print("u");
    bleKeyboard.print("s");

  }else if(modelist[mode] == "shut down"){
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("x");
    bleKeyboard.releaseAll();
    delay(500);
    bleKeyboard.print("u");
    bleKeyboard.print("u");

  }else if(modelist[mode] == "allDeleted, lol :)"){
    bleKeyboard.press(KEY_LEFT_CTRL);
    sendString("axs", 100);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.write(KEY_F4);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("r");
    bleKeyboard.releaseAll();
    delay(500);
    bleKeyboard.println("notepad");
    delay(1000);
    sendString("These data was deleted, lol '(\n", 25); //「:)」 はキーコードのずれによる影響で「'(」になる
    delay(1000 * 10);
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("r");
    bleKeyboard.releaseAll();
    delay(500);
    bleKeyboard.println("notepad");
    delay(1000);
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.print("v");

  }else if(modelist[mode] == "Win + 1~0"){
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("1234567890");

  }else if(modelist[mode] == "Shift + Win + 1~0"){
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("1234567890");

  }else if(modelist[mode] == "task manager"){
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.write(KEY_ESC);

  }else if(modelist[mode] == "dir /s"){
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("r");
    delay(250);
    bleKeyboard.releaseAll();
    bleKeyboard.println("cmd");
    delay(1250);
    bleKeyboard.println("color 2");
    bleKeyboard.println("dir /s");

  }else if(modelist[mode] == "save & close"){
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.print("sw");

  }else if(modelist[mode] == "show desktop"){
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("d");

  }else if(modelist[mode] == "L:while (Alt + Esc)"){
    while(M5.BtnA.isPressed()){
      M5.update();
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.write(KEY_ESC);
      delay(25);
    }

  }else if(modelist[mode] == "rand app select"){
    srand((unsigned int)time(NULL));
    int randnum = getRandom(1, 10);
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.write(KEY_TAB);
    delay(200);
    bleKeyboard.releaseAll();
    for(int i=0; i<randnum; i++) bleKeyboard.write(KEY_RIGHT_ARROW);
    bleKeyboard.write(KEY_RETURN);

  }else if(modelist[mode] == "explorer"){
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("e");

  }else if(modelist[mode] == "R:change resolution"){
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("i");
    delay(500);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.write(KEY_RETURN);
    bleKeyboard.releaseAll();
    delay(1000);
    bleKeyboard.write(KEY_TAB);
    bleKeyboard.write(KEY_DOWN_ARROW);
    bleKeyboard.write(KEY_RETURN);
    bleKeyboard.releaseAll();
    delay(300);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    for(int i=0; i<4; i++) bleKeyboard.write(KEY_TAB);
    bleKeyboard.write(KEY_RETURN);
    bleKeyboard.releaseAll();
    delay(300);
    M5.update();
    if(M5.BtnA.isPressed()){
      for(int i=0; i<7; i++) bleKeyboard.write(KEY_TAB);
      delay(100);
      bleKeyboard.write(KEY_RETURN);
      bleKeyboard.write(KEY_HOME);
      bleKeyboard.write(KEY_HOME);
    }else{
      for(int i=0; i<8; i++) bleKeyboard.write(KEY_TAB);
      delay(100);
      bleKeyboard.write(KEY_RETURN);
      bleKeyboard.write(KEY_END);
      bleKeyboard.write(KEY_END);
    }
    bleKeyboard.write(KEY_RETURN);
    delay(500);
    bleKeyboard.write(KEY_LEFT_ARROW);
    bleKeyboard.write(KEY_RETURN);
    delay(100);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.write(KEY_F4);

  }else if(modelist[mode] == "touch pad"){
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("i");
    delay(300);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.write(KEY_RETURN);
    bleKeyboard.releaseAll();
    delay(1000);
    bleKeyboard.write(KEY_TAB);
    bleKeyboard.write(KEY_DOWN_ARROW);
    bleKeyboard.write(KEY_DOWN_ARROW);
    bleKeyboard.write(KEY_RETURN);
    delay(200);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    for(int i=0; i<5; i++) bleKeyboard.write(KEY_TAB);
    bleKeyboard.releaseAll();
    for(int i=0; i<5; i++) bleKeyboard.write(KEY_DOWN_ARROW);
    bleKeyboard.write(KEY_RETURN);
    delay(200);
    bleKeyboard.print(" ");
    bleKeyboard.releaseAll();
    delay(100);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.write(KEY_F4);

  }else if(modelist[mode] == "new desktop"){
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.print("d");

  }else if(modelist[mode] == "L:hyper zoom"){
    bleKeyboard.press(KEY_LEFT_GUI);
    while(M5.BtnA.isPressed()){
      M5.update();
      bleKeyboard.write(KEY_NUM_PLUS);
      delay(25);
    }

  }else if(modelist[mode] == "high contrast"){
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.write(KEY_PRTSC);
    delay(300);
    bleKeyboard.print("y");

  }else if(modelist[mode] == "R:rand screenRotate"){
    srand((unsigned int)time(NULL));
    int randNum = getRandom(1, 3);
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("i");
    delay(300);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.write(KEY_RETURN);
    bleKeyboard.releaseAll();
    delay(1000);
    bleKeyboard.write(KEY_TAB);
    bleKeyboard.write(KEY_DOWN_ARROW);
    bleKeyboard.write(KEY_RETURN);
    delay(300);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    for(int i=0; i<4; i++) bleKeyboard.write(KEY_TAB);
    bleKeyboard.write(KEY_RETURN);
    bleKeyboard.releaseAll();
    delay(400);
    for(int i=0; i<9; i++) bleKeyboard.write(KEY_TAB);
    bleKeyboard.write(KEY_RETURN);
    delay(300);
    M5.update();
    if(M5.BtnA.isPressed()) for(int i=0; i<randNum; i++) bleKeyboard.write(KEY_UP_ARROW);
    else for(int i=0; i<randNum; i++) bleKeyboard.write(KEY_DOWN_ARROW);
    bleKeyboard.write(KEY_RETURN);
    delay(500);
    bleKeyboard.write(KEY_LEFT_ARROW);
    bleKeyboard.write(KEY_RETURN);
    delay(100);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.write(KEY_F4);

  }else if(modelist[mode] == "L:rand window move"){
    uint8_t key[] = {KEY_LEFT_ARROW, KEY_RIGHT_ARROW, KEY_UP_ARROW, KEY_DOWN_ARROW};
    int memory = 0;
    int memory2 = 0;
    while(M5.BtnA.isPressed()) M5.update();
    while(!M5.BtnA.isPressed()){
      M5.update();
      bleKeyboard.press(KEY_LEFT_SHIFT);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.write(KEY_TAB);
      bleKeyboard.releaseAll();
      delay(500);
      for(int i=0; i<10; i++){
        srand((unsigned int)time(NULL));
        int randnum = getRandom(0, 6);
        randnum %= 4;
        bleKeyboard.press(KEY_LEFT_GUI);
        if(memory == randnum && memory2 == randnum) ++randnum %= 4;
        bleKeyboard.write(key[randnum]);
        bleKeyboard.releaseAll();
        memory2 = memory;
        memory = randnum;
        bleKeyboard.write(KEY_ESC);
        delay(25);
      }
    }
    while(M5.BtnA.isPressed()) M5.update();

  }else if(modelist[mode] == "R:mouse reverse"){
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("i");
    delay(300);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.write(KEY_RETURN);
    bleKeyboard.releaseAll();
    delay(1000);
    bleKeyboard.write(KEY_TAB);
    bleKeyboard.write(KEY_DOWN_ARROW);
    bleKeyboard.write(KEY_DOWN_ARROW);
    bleKeyboard.write(KEY_RETURN);
    delay(200);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    for(int i=0; i<5; i++) bleKeyboard.write(KEY_TAB);
    bleKeyboard.releaseAll();
    for(int i=0; i<4; i++) bleKeyboard.write(KEY_DOWN_ARROW);
    bleKeyboard.write(KEY_RETURN);
    delay(200);
    bleKeyboard.write(KEY_RETURN);
    M5.update();
    if(M5.BtnA.isPressed()) bleKeyboard.write(KEY_UP_ARROW);
    else bleKeyboard.write(KEY_DOWN_ARROW);
    bleKeyboard.write(KEY_RETURN);
    delay(100);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.write(KEY_F4);

  }else if(modelist[mode] == "desktop icon"){
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("d");
    bleKeyboard.releaseAll();
    delay(200);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.write(KEY_F10);
    bleKeyboard.releaseAll();
    bleKeyboard.print("vd");
    delay(200);
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("d");

  }else if(modelist[mode] == "LB:reverse Color"){
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.write(KEY_NUM_PLUS);
    bleKeyboard.releaseAll();
    delay(1000);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.write(KEY_TAB);
    delay(200);
    bleKeyboard.write(KEY_END);
    bleKeyboard.releaseAll();
    delay(200);
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.write(KEY_DOWN_ARROW);
    bleKeyboard.releaseAll();
    while(M5.BtnA.isPressed()) M5.update();
    while(!M5.BtnA.isPressed()){
      M5.update();
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.print("i");
      bleKeyboard.releaseAll();
      srand((unsigned int)time(NULL));
      int randnum = getRandom(25, 500);
      delay(randnum);
    }
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.write(KEY_ESC);

  }else if(modelist[mode] == "Alt + F4"){
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.write(KEY_F4);
  
  }else if(modelist[mode] == "S:Alt + while (Tab)"){
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.write(KEY_TAB);
    while(!M5.BtnB.isPressed()){
      M5.update();
      if(M5.BtnA.wasPressed()) bleKeyboard.write(KEY_TAB);
    }

  }else if(modelist[mode] == "M:Mix treat"){
    while(M5.BtnA.isPressed()) M5.update();
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.write(KEY_NUM_PLUS);
    for(int i=0; i<10; i++){
      bleKeyboard.write(KEY_NUM_MINUS);
      delay(100);
    }
    bleKeyboard.releaseAll();
    delay(1000);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.write(KEY_TAB);
    delay(200);
    bleKeyboard.write(KEY_END);
    bleKeyboard.releaseAll();
    delay(200);
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.write(KEY_DOWN_ARROW);
    bleKeyboard.releaseAll();

    uint8_t key[] = {KEY_LEFT_ARROW, KEY_RIGHT_ARROW, KEY_UP_ARROW, KEY_DOWN_ARROW};
    int memory = 0;
    int memory2 = 0;
    bool zoom = true;
    while(!M5.BtnA.isPressed()){
      M5.update();
      bleKeyboard.press(KEY_LEFT_SHIFT);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.write(KEY_TAB);
      bleKeyboard.releaseAll();
      delay(500);
      for(int i=0; i<10; i++){
        srand((unsigned int)time(NULL));
        int randnum = getRandom(0, 6);
        randnum %= 4;
        bleKeyboard.press(KEY_LEFT_GUI);
        if(memory == randnum && memory2 == randnum) ++randnum %= 4;
        bleKeyboard.write(key[randnum]);
        bleKeyboard.releaseAll();
        memory2 = memory;
        memory = randnum;
        bleKeyboard.write(KEY_ESC);
        delay(25);
        srand((unsigned int)time(NULL));
        int select = getRandom(0, 2);
        if(select == 0){
          bleKeyboard.press(KEY_LEFT_CTRL);
          bleKeyboard.press(KEY_LEFT_ALT);
          bleKeyboard.print("i");
        }else if(select == 1){
          bleKeyboard.press(KEY_LEFT_GUI);
          bleKeyboard.print("d");
        }else if(select == 2){
          bleKeyboard.press(KEY_LEFT_GUI);
          if(zoom) bleKeyboard.write(KEY_NUM_PLUS);
          else bleKeyboard.write(KEY_NUM_MINUS);
          zoom = !zoom;
        }

        bleKeyboard.releaseAll();
        M5.update();
        if(M5.BtnA.isPressed()) break;
        
        delay(50);
      }
    }
    while(M5.BtnA.isPressed()) M5.update();

  }else{
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("a");
    bleKeyboard.releaseAll();
    delay(1000);
    bleKeyboard.write(KEY_RIGHT_ARROW);
    bleKeyboard.write(KEY_TAB);
    bleKeyboard.write(KEY_RETURN);
    delay(300);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.write(KEY_TAB);
    bleKeyboard.releaseAll();
    bleKeyboard.write(KEY_RETURN);
    delay(300);
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.write(KEY_RETURN);
    bleKeyboard.releaseAll();
    delay(1000);
    for(int i=0; i<4; i++){
      bleKeyboard.write(KEY_TAB);
    }
    bleKeyboard.write(KEY_RETURN);
    delay(200);
    bleKeyboard.write(KEY_RETURN);
    delay(50);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.write(KEY_F4);
    delay(500);
    M5.Axp.PowerOff();

  }
  bleKeyboard.releaseAll();
}


//**************************************************************


void showstate(char *txt, uint32_t Fcolor) {
  M5.Lcd.fillRect(5, 120, 100, 20, BLACK);
  M5.Lcd.setCursor(5, 120);
  M5.Lcd.setTextColor(Fcolor, BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf(txt);
}

void showMode(){
  M5.Lcd.fillRect(0, 25, 240, 80, BLACK);
  M5.Lcd.setCursor(5, 25);
  M5.Lcd.setTextColor(DARKGREY, BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println(modelist[mode]);
  M5.Lcd.fillRect(175, 115, 240, 80, BLACK);
  M5.Lcd.setCursor(175, 115);
  M5.Lcd.setTextColor(DARKGREY, BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("%d/%d", mode, MODE_MAX-1);
}

void showProgress(int progress){
  M5.Lcd.fillRect(75, 5, 140, 20, BLACK);
  M5.Lcd.setCursor(75, 5);
  M5.Lcd.setTextSize(2);
  selecting = false;
  switch(progress){
    case 0:
      M5.Lcd.setTextColor(DARKCYAN, BLACK);
      M5.Lcd.println("boot up");
      break;
    case 1:
      M5.Lcd.setTextColor(OLIVE, BLACK);
      M5.Lcd.println("safty mode");
      break;
    case 2:
      M5.Lcd.setTextColor(DARKGREY, BLACK);
      M5.Lcd.println("select");
      break;
    case 3:
      M5.Lcd.setTextColor(PURPLE, BLACK);
      M5.Lcd.println("execute");
      break;
    case 4:
      M5.Lcd.setTextColor(DARKGREEN, BLACK);
      M5.Lcd.println("done");
      break;
    case 5:
      M5.Lcd.setTextColor(MAROON, BLACK);
      M5.Lcd.println("disabled");
      break;
  }
}

void setup() {
  M5.begin();
  
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextFont(0);
  M5.Lcd.setTextSize(2);

  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();

  M5.Lcd.fillRect(0, 0, 240, 135, BLACK);
  M5.Lcd.setCursor(5, 5);
  M5.Lcd.setTextColor(DARKGREY, BLACK);
  M5.Lcd.println("Mode:");
  showMode();
  showProgress(0);
  blestate = false;
  showstate("Disconnected", MAROON);

  delay(1000);
}

void loop() {
  M5.update();
  if (bleKeyboard.isConnected()) {
    if (!blestate) {
      blestate = true;
      showstate("Connected", NAVY);
    }
  } else {
    if (blestate) {
      blestate = false;
      showstate("Disconnected", MAROON);
    }
  }

  int axpButton = M5.Axp.GetBtnPress();
  if (M5.BtnA.isPressed()) {
    if(mode == 0){
      showProgress(1);
    }else{
      if(bleKeyboard.isConnected()){
        showProgress(3);
        sendCommand();
        showProgress(4);
      }else{
        showProgress(5);
      }
      while(M5.BtnB.isPressed()){
        M5.update();
        delay(1);
      }
    }
    delay(500);

  } else if (M5.BtnB.isPressed()) {
    if(tf){
      ++mode %= MODE_MAX;
      showMode();
      while(M5.BtnA.isPressed()) {
        M5.update();
        delay(1);
      }
    }else{
      mode += MODE_MAX-1;
      mode %= MODE_MAX;
      showMode();
      while(M5.BtnA.isPressed()) {
        M5.update();
        delay(1);
      }
    }
    delay(200);

  }else if(axpButton == 1){    // 1秒未満電源ボタンを押して離した
    mode = 0;
    showMode();
  }else if(axpButton == 2){    // 1秒未満電源ボタンを押して離した
    tf = !tf;
    M5.Lcd.fillRect(220, 5, 20, 20, BLACK);
    M5.Lcd.setCursor(220, 5);
    M5.Lcd.setTextColor(DARKGREY, BLACK);
    M5.Lcd.setTextSize(2);
    if(!tf) M5.Lcd.printf("R");

  }else{
    if(!selecting){
      showProgress(2);
      selecting = true;
    }
  }
}
