#include <maxymiller_lib/Tela_SSD1306_oled.h>

Tela_SSD1306_oled::Tela_SSD1306_oled(
  int tela_total_do_x, int tela_total_do_y
) {
  TELA_X_X = tela_total_do_x;
  TELA_X_Y = tela_total_do_y;

  TELA_X = 10*TELA_X_X;
  TELA_Y = 4*TELA_X_Y;

  oled = new Adafruit_SSD1306*[TELA_X_X*TELA_X_Y]{};
  //add(OLED, OLED_SDA, OLED_SCL);
}

void Tela_SSD1306_oled::ligar() {

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

  /*for(int i = 0; i < telaTotal; i++) {

    if(lcd[i] != nullptr) {

      lcd[i]->begin(
        TELA_X / TELA_X_X,
        TELA_Y / TELA_X_Y
      );
    }
  }*/

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
}

void Tela_SSD1306_oled::loop() {

  if(millis() >= UPTIME_MEMORIA) {

    UPTIME_MEMORIA = millis() + 500;

    if(LOOP > 5) {
      limpa(0);

      int lcdLargura = TELA_X / TELA_X_X;
      int lcdAltura = TELA_Y / TELA_X_Y;

      for(int y = 0; y < TELA_Y; y++) {

        int lcdY = y / lcdAltura;
        int linhaLCD = y % lcdAltura;

        for(int x = 0; x < TELA_X_X; x++) {

          int indice = x + (TELA_X_X * lcdY);

          if(oled[indice] == nullptr) {
            continue;
          }

          setCursor(indice, 0, linhaLCD);

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

            oled[indice]->print(parte);
            oled[indice]->display();
          }
        }

        if(
          LOOP >= TELA_LINE_MAX ||
          TELA_LINE[y].length() <= TELA_X
        ) {
          escrever(TELA_LINE[y], y + 1);
        }
      }
    }

    cursor_blink(CURSOR_TELA, CURSOR_X, CURSOR_Y);

    if(
      TELA_LINE_MAX <= TELA_X ||
      LOOP >= TELA_LINE_MAX
    ) {
      LOOP = 0;
    } else {
      LOOP++;
    }
  }
}

void Tela_SSD1306_oled::add(
  uint8_t OLED,
  int OLED_SDA,
  int OLED_SCL
) {
  int telaTotal = TELA_X_X * TELA_X_Y;

  if(TELA_USER < telaTotal) {

    oled[TELA_USER] = new Adafruit_SSD1306(
      OLED_WIDTH,
      OLED_HEIGHT,
      &Wire,
      -1
    );

    Wire.begin(OLED_SDA, OLED_SCL);

    if (!oled[TELA_USER]->begin(SSD1306_SWITCHCAPVCC, OLED)) {
      while (true) {
        delay(1000);
      }
    }

    oled[TELA_USER]->setTextSize(2);
    oled[TELA_USER]->setTextColor(SSD1306_WHITE);

    TELA_USER++;
  }
}

void Tela_SSD1306_oled::escrever(String texto, int linha) {

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

        setCursor(indice, 0, linhaLCD);
        nextCursor(indice, parte.length(), linhaLCD);
        oled[indice]->print(parte);
        oled[indice]->display();
      }
    }

  // Escrever em uma linha específica
  } else if(linha > 0 && linha <= TELA_Y) {

    int linhaGlobal = linha - 1;

    int lcdY = linhaGlobal / lcdAltura;
    int linhaLCD = linhaGlobal % lcdAltura;

    String linhaTexto = texto.substring(0, TELA_X);

    TELA_LINE[linhaGlobal] = texto;

    limpa(linha);

    for(int x = 0; x < TELA_X_X; x++) {

      int indice = x + (TELA_X_X * lcdY);

      String parte =
        linhaTexto.substring(
          lcdLargura * x,
          lcdLargura * (x + 1)
        );

      setCursor(indice, 0, linhaLCD);
      nextCursor(indice, parte.length(), linhaLCD);
      oled[indice]->print(parte);
      oled[indice]->display();
    }
  }

  TELA_LINE_MAX = 0;

  for(int i = 0; i < TELA_Y; i++) {
    if(TELA_LINE[i].length() > TELA_LINE_MAX) {
      TELA_LINE_MAX = TELA_LINE[i].length();
    }
  }
}

void Tela_SSD1306_oled::limpa(int linha) {

  int telaTotal = TELA_X_X * TELA_X_Y;

  if(linha == 0) {

    for(int i = 0; i < telaTotal; i++) {
      oled[i]->clearDisplay();
    }

  } else if(linha > 0 && linha <= TELA_Y) {

    int lcdLargura = TELA_X / TELA_X_X;
    int lcdAltura = TELA_Y / TELA_X_Y;

    int linhaGlobal = linha - 1;

    int lcdY = linhaGlobal / lcdAltura;
    int linhaLCD = linhaGlobal % lcdAltura;

    for(int x = 0; x < TELA_X_X; x++) {

      int indice = x + (TELA_X_X * lcdY);

      for(int i = 0; i < OLED_WIDTH; i++) { // SSD1306_WHITE  SSD1306_BLACK
        oled[indice]->drawLine(i, (linhaGlobal*16), i, (linhaGlobal*16)+13, SSD1306_BLACK);
      }
      //setCursor(indice, 0, linhaLCD);
      //oled[indice]->print(
        //TELA_LIMPA.substring(0, lcdLargura)
      //);
    }
  }
}

void Tela_SSD1306_oled::cursor_ligar(boolean tipo) {
  //int telaTotal = TELA_X_X*TELA_X_Y;
  //for(int i = 0; i < telaTotal; i++) {
    if(tipo) {
      //lcd[i] -> cursor();
      CURSOR_BLINK = false; //lcd[i] -> noBlink();
    }else{
      //lcd[i] -> cursor();
      CURSOR_BLINK = true; //lcd[i] -> blink();
    }
  //}
  cursor_ligado = true;
}
void Tela_SSD1306_oled::cursor_desligar() {
  //int telaTotal = TELA_X_X*TELA_X_Y;
  //for(int i = 0; i < telaTotal; i++) {
    CURSOR_BLINK = false; //lcd[i] -> noBlink();
    //lcd[i] -> noCursor();
  //}
  cursor_ligado = false;
}
boolean Tela_SSD1306_oled::cursor_esta_ligado() {
  return cursor_ligado;
}

void Tela_SSD1306_oled::cursor_blink(int oledTela, int x, int y) {
  if((x != CURSOR_X || y != CURSOR_Y) && cursor_ligado) {
    for(int i = 0; i < 10; i++) {
      oled[CURSOR_TELA]->drawLine(CURSOR_X+i, CURSOR_Y - 14, CURSOR_X+i, CURSOR_Y, SSD1306_BLACK);
    }
    oled[CURSOR_TELA]->display();
    CURSOR_X = x;
    CURSOR_Y = y;
    CURSOR_TELA = oledTela;
  }

  if (millis() - CURSOR_TEMPO >= 500) {
    CURSOR_TEMPO = millis();
    cursor_estado = !cursor_estado;

    if (cursor_estado) {
      if(CURSOR_BLINK) {
        for(int i = 0; i < TELA_X/TELA_X_X; i++) {
          oled[oledTela]->drawLine(x+i, y - 14, x+i, y, SSD1306_WHITE);
        }
      }else if(cursor_ligado) {
        for(int i = 0; i < TELA_X/TELA_X_X; i++) {
          oled[oledTela]->drawLine(x+i, y, x+i, y, SSD1306_WHITE);
        }
      }
    }else{
      if(cursor_ligado) {
        for(int i = 0; i < TELA_X/TELA_X_Y; i++) {
          oled[oledTela]->drawLine(x+i, y - 14, x+i, y-1, SSD1306_BLACK);
        }
      }
    }

    oled[oledTela]->display();
  }
}

void Tela_SSD1306_oled::setCursor(int oledTela, int x, int y) {
  cursor_blink(oledTela, x*12, (y*16)+14);
  oled[oledTela]->setCursor(x*12, y*16);
}
void Tela_SSD1306_oled::nextCursor(int oledTela, int x, int y) {
  cursor_blink(oledTela, x*12, (y*16)+14);
}
void Tela_SSD1306_oled::desenharia_pixels(int tela_oled, int x_a, int y_a, int x_b, int y_b, boolean tela_pixels_on) {
  if(tela_pixels_on) {
    oled[tela_oled]->drawLine(x_a, y_a, x_b, y_b, SSD1306_WHITE);
  }else{
    oled[tela_oled]->drawLine(x_a, y_a, x_b, y_b, SSD1306_BLACK);
  }
}
