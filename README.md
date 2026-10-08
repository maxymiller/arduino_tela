# arduino_tela

---

## Tela

```
#include <maxymiller_lib/Tela.h>
```

Para usar a classe `Tela`, que trabalha com LCD paralelo usando `LiquidCrystal`.

Exemplo:

```
Tela tela(
  /* tamanho de cada LCD */
  16, 2,

  /* quantidade de LCDs */
  2, 2
);
```

---

## Tela_I2C

```
#include <maxymiller_lib/Tela_I2C.h>
```

Para usar a classe `Tela_I2C`, que trabalha com LCD I²C usando `LiquidCrystal_I2C`.

Exemplo:

```
Tela_I2C tela(
  /* tamanho de cada LCD */
  16, 2,

  /* quantidade de LCDs */
  2, 2
);
```

---

## Tela_SSD1306_oled

```
#include <maxymiller_lib/Tela_SSD1306_oled.h>
```

Para usar a classe `Tela_SSD1306_oled`, que trabalha com OLED I²C usando `Adafruit GFX Library` e `Adafruit SSD1306`.

Exemplo:

```
Tela_SSD1306_oled tela(
  /* quantidade de OLEDs */
  2, 2
);
```

---
