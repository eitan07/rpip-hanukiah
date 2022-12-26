#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
const int rs = 15, en = 14, d4 = 16, d5 = 17, d6 = 18, d7 = 19;
byte holiday_day = 8;

const int c1 = 8, c2 = 7, c3 = 6, c4 = 5, c5 = 3, c6 = 2, c7 = 1, c8 = 0, cs = 4;

SoftwareSerial ble(13, 12);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  rp2040.idleOtherCore();
  waitingForCommand();
  ble.begin(9600);
  for (int i = 0; i <= 8; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

char incoming_text[20];
void loop() {
  if (ble.available()) {
    memset(incoming_text, 0, 20);
    ble.readString().toCharArray(incoming_text, 20);
    if (prefix("/startHanukiah", incoming_text)) {
      holiday_day = char2int(incoming_text[15]);
      startHanukiah();
      ble.println("Starting Hanukiah!");
      ble.println(holiday_day, DEC);
    }
  }
}

byte char2byte(char inp) {
  byte a;

  char *_temp = (char*) malloc(2 * sizeof(char));
  _temp[0] = inp;
  _temp[1] = '\0';
  sscanf(_temp, "%d", &a);
  free(_temp);
  return a;
}

void startHanukiah() {
  for (int i = 0; i <= 8; i++) {
    digitalWrite(i, LOW);
  }

  digitalWrite(4, HIGH); // Shamash
  switch (holiday_day) {
    case 1:
      digitalWrite(c1, HIGH);
      break;
    case 2:
      digitalWrite(c1, HIGH);
      digitalWrite(c2, HIGH);
      break;
    case 3:
      digitalWrite(c1, HIGH);
      digitalWrite(c2, HIGH);
      digitalWrite(c3, HIGH);
      break;
    case 4:
      digitalWrite(c1, HIGH);
      digitalWrite(c2, HIGH);
      digitalWrite(c3, HIGH);
      digitalWrite(c4, HIGH);
      break;
    case 5:
      digitalWrite(c1, HIGH);
      digitalWrite(c2, HIGH);
      digitalWrite(c3, HIGH);
      digitalWrite(c4, HIGH);
      digitalWrite(c5, HIGH);
      break;
    case 6:
      digitalWrite(c1, HIGH);
      digitalWrite(c2, HIGH);
      digitalWrite(c3, HIGH);
      digitalWrite(c4, HIGH);
      digitalWrite(c5, HIGH);
      digitalWrite(c6, HIGH);
      break;
    case 7:
      digitalWrite(c1, HIGH);
      digitalWrite(c2, HIGH);
      digitalWrite(c3, HIGH);
      digitalWrite(c4, HIGH);
      digitalWrite(c5, HIGH);
      digitalWrite(c6, HIGH);
      digitalWrite(c7, HIGH);
      break;
    case 8:
      digitalWrite(c1, HIGH);
      digitalWrite(c2, HIGH);
      digitalWrite(c3, HIGH);
      digitalWrite(c4, HIGH);
      digitalWrite(c5, HIGH);
      digitalWrite(c6, HIGH);
      digitalWrite(c7, HIGH);
      digitalWrite(c8, HIGH);
      break;
  }
}

bool prefix(const char *pre, const char *str)
{
  return strncmp(pre, str, strlen(pre)) == 0;
}

void startLCD() {
  lcd.begin(16, 2);
  lcd.noBlink();
  lcd.createChar(0, smiley);
}

void waitingForCommand() {
  lcd.println("Waiting for");
  lcd.print("command....");
}

int lcd_slide = 0;
int refresh_rate = 3;
byte smiley[] = {
  0x00,
  0x00,
  0x0A,
  0x0A,
  0x00,
  0x11,
  0x0E,
  0x00
};

void setup1() {

}

void loop1() {
  lcd.clear();
  lcd.home();
  char day[3];
  sprintf(day, "%d%s", holiday_day, numberEnding(holiday_day));
  switch (lcd_slide) {
    case 0:
      lcd.print("Happy Hanukah!");
      break;
    case 1:
      lcd.print("Today is the ");
      lcd.print(day);
      lcd.setCursor(0, 1);
      lcd.print("day of Hanukah!");
      break;
    case 2:
      lcd.print("Sevivons sov sov sov,");
      lcd.setCursor(0, 1);
      lcd.print("Hanukah hu hag tov!");
      break;
    case 3:
      lcd.write((uint8_t) 0);
      break;
  }
  if (lcd_slide < 3) {
    lcd_slide++;
  } else {
    lcd_slide = 0;
  }
  delay(refresh_rate * 1000);
}

const char *numberEnding(int num) {
  switch (num) {
    case 1:
      return "st";
      break;
    case 2:
      return "nd";
      break;
    case 3:
      return "rd";
      break;
    default:
      return "th";
      break;
  }
}
