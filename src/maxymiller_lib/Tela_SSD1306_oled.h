#ifndef TELA_SSD1306_OLED_H
#define TELA_SSD1306_OLED_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Tela_SSD1306_oled {
private:
  Adafruit_SSD1306** oled = nullptr;
  bool cursor_ligado = false;

  String* TELA_LINE = nullptr;
  int TELA_X;
  int TELA_Y;
  String TELA_LIMPA;

  unsigned long UPTIME_MEMORIA;
  int LOOP;

  int TELA_LINE_MAX;

  int TELA_X_X;
  int TELA_X_Y;
  int TELA_USER;

  int OLED_WIDTH = 128;
  int OLED_HEIGHT = 64;

  boolean TELA_LIGAR = false;

  unsigned long CURSOR_TEMPO = 0;
  boolean cursor_estado = false;
  boolean CURSOR_BLINK = false;
  void cursor_blink(int oledTela, int x, int y);
  void setCursor(int oledTela, int x, int y);
  void nextCursor(int oledTela, int x, int y);
  void cursor_save(int oledTela, int x, int y);

  int CURSOR_X;
  int CURSOR_Y;
  int CURSOR_TELA;
  int CURSOR_LINE_BIG;

  int CURSOR_X_SAVE;
  int CURSOR_Y_SAVE;
  int CURSOR_TELA_SAVE;

  void limpa(int linha);
  //void loop();
  //static void tarefaLoop(void *parameter);
public:
  Tela_SSD1306_oled(
    int tela_total_do_x, int tela_total_do_y
  );

  void loop();
  void ligar();
  void add(
    int OLED_I2C, int OLED_SDA, int OLED_SCL
  );
  void escrever(String texto, int linha);
  void cursor_ligar(boolean tipo);
  void cursor_desligar();
  boolean cursor_esta_ligado();
  void desenharia_pixels(int tela_oled, int x_a, int y_a, int x_b, int y_b, boolean tela_pixels_on);
};

#endif
