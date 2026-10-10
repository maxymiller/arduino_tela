#ifndef TELA_H
#define TELA_H

#include <Arduino.h>
#include <LiquidCrystal.h>

class Tela {
private:
  LiquidCrystal** lcd = nullptr;
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

  boolean TELA_LIGAR = false;
  void loop();
  static void tarefaLoop(void *parameter);
public:
  Tela(
    int x, int y, int tela_total_do_x, int tela_total_do_y
  );

  void ligar();
  void add(
    int LCD_RS, int LCD_E, int LCD_D4, int LCD_D5, int LCD_D6, int LCD_D7
  );
  void escrever(String texto, int linha);
  void limpa(int linha);
  void cursor_ligar(boolean tipo);
  void cursor_desligar();
  boolean cursor_esta_ligado();
  void icoSave(int list, byte ico_8byte[]);
  void icoPrint(int tela, int list, int x, int y);
};

#endif
