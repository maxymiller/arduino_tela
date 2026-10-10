#include <maxymiller_lib/Tela_I2C.h>

Tela_I2C::Tela_I2C(
  int x, int y, int tela_total_do_x, int tela_total_do_y
) {
  TELA_X_X = tela_total_do_x;
  TELA_X_Y = tela_total_do_y;

  TELA_X = x*TELA_X_X;
  TELA_Y = y*TELA_X_Y;

  lcd = new LiquidCrystal_I2C*[TELA_X_X*TELA_X_Y]{};
}

void Tela_I2C::ligar() {

  if(TELA_LIGAR) {
    return;
  }else{
    TELA_LIGAR = true;
  }

  int telaTotal = TELA_X_X * TELA_X_Y;

  TELA_LINE = new String[TELA_Y];

  for(int i = 0; i < TELA_X; i++) {
    TELA_LIMPA += " ";
  }

  for(int i = 0; i < telaTotal; i++) {

    if(lcd[i] != nullptr) {

      lcd[i]->init();
      lcd[i]->backlight();
    }
  }

  String telaLine = "";

  for(int i = 0; i < (TELA_X / TELA_X_X) - 6; i++) {
    telaLine += " ";
  }

  String meg = "";
  for(int i = 0; i < telaTotal; i++) {
    if(i < TELA_USER) {
      meg += "LIGADO" + telaLine;
    }else{
      break;
    }
  }

  escrever(meg, 0);
  /*xTaskCreatePinnedToCore(
    Tela_I2C::tarefaLoop,
    "tela I2C",
    10000,
    this,
    1,
    NULL,
    0
  );*/
}

/*void Tela_I2C::tarefaLoop(void *parameter) {
    Tela_I2C *tela = static_cast<Tela_I2C *>(parameter);

    if (tela == nullptr) {
        vTaskDelete(nullptr);
        return;
    }

    while (true) {
        tela->loop();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}*/

void Tela_I2C::loop() {

  if(millis() >= UPTIME_MEMORIA) {

    UPTIME_MEMORIA = millis() + 500;

    if(LOOP > 5) {

      int lcdLargura = TELA_X / TELA_X_X;
      int lcdAltura = TELA_Y / TELA_X_Y;

      for(int y = 0; y < TELA_Y; y++) {

        int lcdY = y / lcdAltura;
        int linhaLCD = y % lcdAltura;

        for(int x = 0; x < TELA_X_X; x++) {

          int indice = x + (TELA_X_X * lcdY);

          if(lcd[indice] == nullptr) {
            continue;
          }

          if(TELA_LINE[y] != "") {
            lcd[indice]->setCursor(0, linhaLCD);
            lcd[indice]->print(TELA_LIMPA);
            lcd[indice]->setCursor(0, linhaLCD);
          }

          if(
            TELA_LINE[y].length() > TELA_X &&
            LOOP < TELA_LINE_MAX
          ) {

            int inicio =
              (lcdLargura * x) + (LOOP - 5);

            String parte =
              TELA_LINE[y].substring(
                inicio,
                inicio + lcdLargura
              );

            lcd[indice]->print(parte);
          }
        }

        if(
          (
            LOOP >= TELA_LINE_MAX ||
            TELA_LINE[y].length() <= TELA_X
          ) && TELA_LINE[y] != ""
        ) {
          escrever(TELA_LINE[y], y + 1);
        }
      }
    }

    if(
      TELA_LINE_MAX <= TELA_X ||
      LOOP >= TELA_LINE_MAX
    ) {
      LOOP = 0;
    } else {
      LOOP++;
    }
  }
  //delay(500);
}

void Tela_I2C::add(
  int LCD_I2C
) {

  int telaTotal = TELA_X_X * TELA_X_Y;
  int telaX = TELA_X/TELA_X_X;
  int telaY = TELA_Y/TELA_X_Y;

  if(TELA_USER < telaTotal) {

    lcd[TELA_USER] = new LiquidCrystal_I2C(
      LCD_I2C, telaX, telaY
    );

    TELA_USER++;
  }
}

void Tela_I2C::escrever(String texto, int linha) {

  int lcdLargura = TELA_X / TELA_X_X;
  int lcdAltura = TELA_Y / TELA_X_Y;

  // Escrever na tela inteira
  if(linha == 0) {

    limpa(0);

    for(int y = 0; y < TELA_Y; y++) {

      if(y >= (texto.length() + TELA_X - 1) / TELA_X) {
        break;
      }

      String linhaTexto =
        texto.substring(
          TELA_X * y,
          TELA_X * (y + 1)
        );

      TELA_LINE[y] = linhaTexto;

      int lcdY = y / lcdAltura;
      int linhaLCD = y % lcdAltura;

      for(int x = 0; x < TELA_X_X; x++) {

        int indice = x + (TELA_X_X * lcdY);

        String parte =
          linhaTexto.substring(
            lcdLargura * x,
            lcdLargura * (x + 1)
          );

        lcd[indice]->setCursor(0, linhaLCD);
        lcd[indice]->print(parte);
      }
    }

  // Escrever em uma linha específica
  } else if(linha > 0 && linha <= TELA_Y) {

    int linhaGlobal = linha - 1;

    int lcdY = linhaGlobal / lcdAltura;
    int linhaLCD = linhaGlobal % lcdAltura;

    String linhaTexto = texto.substring(0, TELA_X);

    TELA_LINE[linhaGlobal] = texto;

    for(int x = 0; x < TELA_X_X; x++) {

      int indice = x + (TELA_X_X * lcdY);

      String parte =
        linhaTexto.substring(
          lcdLargura * x,
          lcdLargura * (x + 1)
        );

      lcd[indice]->setCursor(0, linhaLCD);
      lcd[indice]->print(parte);
    }
  }

  TELA_LINE_MAX = 0;

  for(int i = 0; i < TELA_Y; i++) {
    if(TELA_LINE[i].length() > TELA_LINE_MAX) {
      TELA_LINE_MAX = TELA_LINE[i].length();
    }
  }
}

void Tela_I2C::limpa(int linha) {

  int telaTotal = TELA_X_X * TELA_X_Y;

  if(linha == 0) {

    for(int i = 0; i < telaTotal; i++) {
      lcd[i]->clear();
    }

  } else if(linha > 0 && linha <= TELA_Y) {

    int lcdLargura = TELA_X / TELA_X_X;
    int lcdAltura = TELA_Y / TELA_X_Y;

    int linhaGlobal = linha - 1;

    int lcdY = linhaGlobal / lcdAltura;
    int linhaLCD = linhaGlobal % lcdAltura;

    for(int x = 0; x < TELA_X_X; x++) {

      int indice = x + (TELA_X_X * lcdY);

      lcd[indice]->setCursor(0, linhaLCD);
      lcd[indice]->print(
        TELA_LIMPA.substring(0, lcdLargura)
      );
    }
  }
}

void Tela_I2C::cursor_ligar(boolean tipo) {
  int telaTotal = TELA_X_X*TELA_X_Y;
  for(int i = 0; i < telaTotal; i++) {
    if(tipo) {
      lcd[i] -> cursor();
      lcd[i] -> noBlink();
    }else{
      lcd[i] -> cursor();
      lcd[i] -> blink();
    }
  }
  cursor_ligado = true;
}
void Tela_I2C::cursor_desligar() {
  int telaTotal = TELA_X_X*TELA_X_Y;
  for(int i = 0; i < telaTotal; i++) {
    lcd[i] -> noBlink();
    lcd[i] -> noCursor();
  }
  cursor_ligado = false;
}
boolean Tela_I2C::cursor_esta_ligado() {
  return cursor_ligado;
}

void Tela_I2C::icoSave(int list, byte ico_8byte[]) {
  for(int i = 0; i < TELA_USER; i++) {
    lcd[i]->createChar(list, ico_8byte);
  }
}
void Tela_I2C::icoPrint(int tela, int list, int x, int y) {
  lcd[tela]->setCursor(x, y);
  lcd[tela]->write(list);
}