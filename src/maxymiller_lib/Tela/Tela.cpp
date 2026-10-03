#include <maxymiller_lib/Tela.h>

Tela::Tela(
  int LCD_RS, int LCD_E, int LCD_D4, int LCD_D5, int LCD_D6, int LCD_D7,
  int x, int y, int tela_total_do_x, int tela_total_do_y
) {
  TELA_X_X = tela_total_do_x;
  TELA_X_Y = tela_total_do_y;

  TELA_X = x*TELA_X_X;
  TELA_Y = y*TELA_X_Y;

  lcd = new LiquidCrystal*[TELA_X_X*TELA_X_Y]{};
  add(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
}

void Tela::ligar() {

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

      lcd[i]->begin(
        TELA_X / TELA_X_X,
        TELA_Y / TELA_X_Y
      );
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
}

void Tela::loop() {

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

          lcd[indice]->setCursor(0, linhaLCD);

          if(
            TELA_LINE[y].length() >= TELA_X &&
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
          LOOP >= TELA_LINE_MAX ||
          TELA_LINE[y].length() < TELA_X
        ) {
          escrever(TELA_LINE[y], y + 1);
        }
      }
    }

    if(
      TELA_LINE_MAX > TELA_X &&
      LOOP >= TELA_LINE_MAX
    ) {
      LOOP = 0;
    } else {
      LOOP++;
    }
  }
}

void Tela::add(
  int LCD_RS,
  int LCD_E,
  int LCD_D4,
  int LCD_D5,
  int LCD_D6,
  int LCD_D7
) {

  int telaTotal = TELA_X_X * TELA_X_Y;

  if(TELA_USER < telaTotal) {

    lcd[TELA_USER] = new LiquidCrystal(
      LCD_RS,
      LCD_E,
      LCD_D4,
      LCD_D5,
      LCD_D6,
      LCD_D7
    );

    TELA_USER++;
  }
}

void Tela::escrever(String texto, int linha) {

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

    TELA_LINE[linhaGlobal] = linhaTexto;

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

void Tela::limpa(int linha) {

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

void Tela::cursor_ligar(boolean tipo) {
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
void Tela::cursor_desligar() {
  int telaTotal = TELA_X_X*TELA_X_Y;
  for(int i = 0; i < telaTotal; i++) {
    lcd[i] -> noBlink();
    lcd[i] -> noCursor();
  }
  cursor_ligado = false;
}
boolean Tela::cursor_esta_ligado() {
  return cursor_ligado;
}
