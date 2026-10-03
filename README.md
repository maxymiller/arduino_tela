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
  /* LCD inicial */
  12, 11, 5, 4, 3, 2,

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
  /* LCD inicial */
  0x27,

  /* tamanho de cada LCD */
  16, 2,

  /* quantidade de LCDs */
  2, 2
);
```

---
