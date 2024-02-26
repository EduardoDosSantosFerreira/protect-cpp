#include <LiquidCrystal.h>
#include <Keypad.h>

#define LINES 4
#define COLUMNS 4
#define DISTANCE_SENSOR 11

#define FIRST_WINDOW 1024
#define DOOR 2048
#define SECOND_WINDOW 3072
#define ZONE 4096

#define ON 1
#define OFF 0

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int melody[] = {
  NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5,
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, 
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, 
  NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
  NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
  NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
  NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_F4,
  NOTE_G4, 0, NOTE_G4, NOTE_D5,
  NOTE_C5, 0, NOTE_AS4, 0,
  NOTE_A4, 0, NOTE_A4, NOTE_A4,
  NOTE_C5, 0, NOTE_AS4, NOTE_A4, 
  NOTE_G4,0, NOTE_G4, NOTE_AS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
  NOTE_G4,0, NOTE_G4, NOTE_AS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
  NOTE_G4, 0, NOTE_G4, NOTE_D5,
  NOTE_C5, 0, NOTE_AS4, 0,
  NOTE_A4, 0, NOTE_A4, NOTE_A4,
  NOTE_C5, 0, NOTE_AS4, NOTE_A4, 
  NOTE_G4,0, NOTE_G4, NOTE_AS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
  NOTE_G4,0, NOTE_G4, NOTE_AS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5
};

int note_durations[] = {
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
};

// Keyboard setup
char keyboard[LINES][COLUMNS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte lines_ports[LINES] = {9,8,7,6};
byte columns_ports[COLUMNS] = {5,4,3,2};

Keypad keypad = Keypad(
  makeKeymap(keyboard), 
  lines_ports, 
  columns_ports,
  LINES,
  COLUMNS
);
// End of keyboard setup

// Setup LCD
LiquidCrystal lcd(A0, A1, A2, A3, A4, 10);

// Keyboard variables of control
char keys_selected[16];
int keys_index = 0;
bool has_result = false;

// Alarm system control
int alarm_codes[4][2] = {
  {1024, 1},
  {2048, 1},
  {3072, 1},
  {4096, 1}
};

void setup()
{
  lcd.begin(16,2);
  
  show_tutorial();
}

void loop()
{ 
  listen_keyboard();
  check_entries();
  check_zone();
}

void show_tutorial()
{  
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("* Limpa");
  lcd.setCursor(0,1);
  lcd.print("# Liga alarme");
  
  delay(3000);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("D Desliga alarme");
  
  delay(3000);
  lcd.setCursor(0,0);
  lcd.clear();
  
}

void listen_keyboard()
{
  char key = keypad.getKey();
  delay(20);
  handle_action(key);
}

long get_movement_distance()
{
  pinMode(DISTANCE_SENSOR, OUTPUT);
  digitalWrite(DISTANCE_SENSOR, LOW);
  delayMicroseconds(2);
  digitalWrite(DISTANCE_SENSOR, HIGH);
  delayMicroseconds(5);
  digitalWrite(DISTANCE_SENSOR, LOW);
  pinMode(DISTANCE_SENSOR, INPUT);
  
  long duration = pulseIn(DISTANCE_SENSOR, HIGH);
  
  return microseconds_to_centimeters(duration);
}

long microseconds_to_centimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void play_alarm()
{
  for (int i = 0; i < 112; i++) {
    int note_duration = 700 / note_durations[i];
    tone(12, melody[i], note_duration);

    int pause_between_notes = note_duration * 1.50;
    delay(pause_between_notes);
    
    noTone(8);
  }
}

void check_entries()
{
  int tension = analogRead(A5);
  int first_window_state = get_element_state(FIRST_WINDOW);
  int second_window_state = get_element_state(SECOND_WINDOW);
  int door_state = get_element_state(DOOR);
  
  switch (tension) {
    // Window 1
    case 558:
    	if (first_window_state == ON) {
          	alarm_fired(FIRST_WINDOW, first_window_state);
    		set_element_state(FIRST_WINDOW, OFF);
    		play_alarm();
          	show_deactivated_feedback(FIRST_WINDOW);
        }
    	break;
    // Door
    case 279: 
    	if (door_state == ON) {
          	alarm_fired(DOOR, door_state);
    		set_element_state(DOOR, OFF);
    		play_alarm();
          	show_deactivated_feedback(DOOR);
        }
    	break;
    // Window 2
    case 186:
    	if (second_window_state == ON) {
          	alarm_fired(SECOND_WINDOW, second_window_state);
    		set_element_state(SECOND_WINDOW, OFF);
    		play_alarm();
          	show_deactivated_feedback(SECOND_WINDOW);
        }
    
    	break;
    // Window 1 + Door
   	case 744:
    	if (
          first_window_state == ON ||
          door_state == ON
        ) {
          	bool w = alarm_fired(FIRST_WINDOW, first_window_state);
          	bool d = alarm_fired(DOOR, door_state);
          
    		set_element_state(FIRST_WINDOW, OFF);
    		set_element_state(DOOR, OFF);
          
          	if (w) {
              show_deactivated_feedback(FIRST_WINDOW);
            }
          
          	if (d) {
              show_deactivated_feedback(DOOR);
          	}
          
    		play_alarm();
        }
    
    	break;
    // Window 1 + Window 2
    case 837:
    	if (
          first_window_state == ON ||
          second_window_state == ON
        ) {
          	bool w = alarm_fired(FIRST_WINDOW, first_window_state);
          	bool w2 = alarm_fired(SECOND_WINDOW, second_window_state);
          
    		set_element_state(FIRST_WINDOW, OFF);
    		set_element_state(SECOND_WINDOW, OFF);
          
          	if (w) {
              show_deactivated_feedback(FIRST_WINDOW);
            }
          
          	if (w2) {
              show_deactivated_feedback(SECOND_WINDOW);
          	}
          
    		play_alarm();
        }
    
    	break;
    // Window 2 + Door
    case 465:
    	if (
          door_state == ON ||
          second_window_state == ON
        ) {
          	bool d = alarm_fired(DOOR, door_state);
          	bool w = alarm_fired(SECOND_WINDOW, second_window_state);
          
    		set_element_state(DOOR, OFF);
    		set_element_state(SECOND_WINDOW, OFF);
          
          	if (d) {
              show_deactivated_feedback(DOOR);
            }
          
          	if (w) {
              show_deactivated_feedback(SECOND_WINDOW);
          	}
          
    		play_alarm();
        }
    
    	break;
    // All
    case 1023:
    	if (
          door_state == ON ||
          first_window_state == ON ||
          second_window_state == ON
        ) {
          	bool d = alarm_fired(DOOR, door_state);
          	bool w = alarm_fired(FIRST_WINDOW, first_window_state);
          	bool w2 = alarm_fired(SECOND_WINDOW, second_window_state);
          
    		set_element_state(DOOR, OFF);
    		set_element_state(FIRST_WINDOW, OFF);
    		set_element_state(SECOND_WINDOW, OFF);
          
          	if (w) {
              show_deactivated_feedback(FIRST_WINDOW);
            }
          
          	if (w2) {
              show_deactivated_feedback(SECOND_WINDOW);
          	}
          
            if (d) {
              show_deactivated_feedback(DOOR);
            }
          
          	play_alarm();
        }
    
    	break;
  }
}

void check_zone()
{
  long movement_distance = get_movement_distance();
  int state = get_element_state(ZONE);
  // Serial.println(movement_distance);
  
  if (movement_distance < 333 && state == ON) {
    alarm_fired(ZONE, state);
    set_element_state(ZONE, OFF);
    play_alarm();
    show_deactivated_feedback(ZONE);
  }
}

bool element_exists(int code)
{
  for (int i = 0; i < 4; i++) {
    if (alarm_codes[i][0] == code) {
      return true;
    }
  }
  
  return false;
}

int get_element_state(int code)
{
  for (int i = 0; i < 4; i++) {
    if (alarm_codes[i][0] == code) {
      return alarm_codes[i][1];
    }
  }
}

int set_element_state(int code, int state)
{
  for (int i = 0; i < 4; i++) {
    if (alarm_codes[i][0] == code) {
      alarm_codes[i][1] = state;
      break;
    }
  }
}

void handle_action(char key)
{
  switch(key) {
    case '0':
  	case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    	add_key(key);
    	break;
    case 'A':
    	break;
    case 'B':
    	break;
    case 'C':
        break;
    case 'D':
    	turn_off();
        break;
    case '#':
    	turn_on();
    	break;
    case '*':
    	clear();
    	break;
    default:
    	break;
  }
}

bool is_number(char key)
{
  switch(key) {
    case '0':
  	case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    	return true;
   	default:
    	return false;
  }
}

void clear()
{
  lcd.clear();
  lcd.setCursor(0,0);
  memset(&keys_selected, NULL, (sizeof(char) * 16));
  keys_index = 0;
  has_result = false;
}

void add_key(char key)
{
  if (has_result) {
  	clear();
  }
  
  keys_selected[keys_index] = key;
  lcd.setCursor(keys_index, 0);
  lcd.print(key);
  keys_index++;
}

void turn_on()
{
  String num = "";
  
  for (int i = 0; i < 16; i++) {
    if (is_number(keys_selected[i])) {
      num.concat(keys_selected[i]);
    }
  }
  
  int code = num.toInt();
  
  if (element_exists(code)) {
    set_element_state(code, ON);
    show_active_feedback(code);
  }
}

void turn_off()
{
  String num = "";
  
  for (int i = 0; i < 16; i++) {
    if (is_number(keys_selected[i])) {
      num.concat(keys_selected[i]);
    }
  }
  
  int code = num.toInt();
  
  if (element_exists(code)) {
    set_element_state(code, OFF);
    show_deactivated_feedback(code);
  }
}

bool alarm_fired(int code, int state)
{  
  if (state == ON) {
    clear();

    switch(code) {
      case FIRST_WINDOW:
        lcd.print("Janela 1- Alarme");
        lcd.setCursor(0,1);
        lcd.print("esta disparando");
      	break;
      case DOOR:
        lcd.print("Porta- Alarme");
        lcd.setCursor(0,1);
        lcd.print("esta disparando");
      	break;
      case SECOND_WINDOW:
        lcd.print("Janela 2- Alarme");
        lcd.setCursor(0,1);
        lcd.print("esta disparando");
      	break;
      case ZONE:
        lcd.print("Zona 2- Alarme");
        lcd.setCursor(0,1);
        lcd.print("esta disparando");
      	break;
    }
    
    return true;
  }
  
  return false;
}

void show_deactivated_feedback(int code)
{
  clear();
  
  switch(code) {
    case FIRST_WINDOW:
   		lcd.print("Janela 1- Alarme");
    	lcd.setCursor(0,1);
    	lcd.print("esta desligado");
    	break;
    case DOOR:
    	lcd.print("Porta- Alarme");
    	lcd.setCursor(0,1);
    	lcd.print("esta desligado");
    	break;
    case SECOND_WINDOW:
    	lcd.print("Janela 2- Alarme");
    	lcd.setCursor(0,1);
    	lcd.print("esta desligado");
    	break;
    case ZONE:
    	lcd.print("Zona 2- Alarme");
    	lcd.setCursor(0,1);
    	lcd.print("esta desligado");
    	break;
  }
  
  delay(3000);
  clear();
}

void show_active_feedback(int code)
{
  clear();
  
  switch(code) {
    case FIRST_WINDOW:
    	lcd.print("Alarme da");
    	lcd.setCursor(0, 1);
    	lcd.print("Janela 1 ativado");
    	break;
    case DOOR:
    	lcd.print("Alarme da");
    	lcd.setCursor(0, 1);
    	lcd.print("Porta ativado");
    	break;
    case SECOND_WINDOW:
    	lcd.print("Alarme da");
    	lcd.setCursor(0, 1);
    	lcd.print("Janela 2 ativado");
    	break;
    case ZONE:
    	lcd.print("Alarme da");
    	lcd.setCursor(0, 1);
    	lcd.print("Zona 2 ativado");
    	break;
  }
  
  delay(3000);
  clear();
}