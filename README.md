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

# Tela e Tela_I2C

---

## Ícones personalizados — `icoSave()` e `icoPrint()`

A função `icoSave()` salva um ícone personalizado na memória do LCD I²C. A função `icoPrint()` posiciona o cursor e exibe o ícone na tela selecionada.

### Exemplo

```cpp
#include <Arduino.h>
#include <maxymiller_lib/Tela_I2C.h>

Tela_I2C tela(16, 2, 1, 1);

byte icone[8] = {
    0b00100,
    0b01110,
    0b11111,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00000
};

void setup() {
    tela.add(0x27);

    // Salva o ícone na posição 0
    tela.icoSave(0, icone);

    // Exibe o ícone no LCD 0, na coluna 0 e linha 0
    tela.icoPrint(0, 0, 0, 0);
}

void loop() {
}
```

### Parâmetros

**`icoSave(int list, byte ico_8byte[])`**

* `list`: posição do caractere personalizado, normalmente de `0` a `7`.
* `ico_8byte`: array com 8 bytes que define o desenho.

**`icoPrint(int tela, int list, int x, int y)`**

* `tela`: índice do LCD que receberá o ícone.
* `list`: posição do caractere personalizado salvo com `icoSave()`.
* `x`: coluna onde o ícone será exibido.
* `y`: linha onde o ícone será exibido.

**Observação:** o endereço `0x27` é apenas um exemplo e pode variar conforme o módulo I²C.
