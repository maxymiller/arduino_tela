#ifndef TELA_I2C_H
#define TELA_I2C_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class Tela_I2C {
private:
  LiquidCrystal_I2C** lcd = nullptr;
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
  //void loop();
  //static void tarefaLoop(void *parameter);
public:
  Tela_I2C(
    int x, int y, int tela_total_do_x, int tela_total_do_y
  );

  void loop();
  void ligar();
  void add(
    int LCD_I2C
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
