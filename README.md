# 50hz-spwm

Проект генератора SPWM на частоте 50 Гц для микроконтроллера STM32F401CCU6.

## Технические характеристики

- **Микроконтроллер**: STM32F401CCU6
- **Ядро**: ARM Cortex-M4 с FPU
- **Частота системы**: 84 МГц
- **Внешний кварц**: 25 МГц
- **RAM**: 64 КБ
- **Flash**: 256 КБ

## Функциональность

Базовая конфигурация проекта включает:
- Инициализацию системной частоты (84 МГц)
- Настройку GPIO (LED на PC13)
- Готовность к добавлению PWM генерации

## Структура проекта

```
50hz-spwm/
├── Core/               # Исходный код приложения
│   ├── Inc/           # Заголовочные файлы
│   └── Src/           # Исходные файлы (.c)
├── Drivers/           # HAL драйверы STM32
│   ├── CMSIS/         # CMSIS библиотеки
│   └── STM32F4xx_HAL_Driver/  # HAL драйверы
├── cmake/             # CMake конфигурация
├── docs/              # Документация
├── .gitignore         # Git исключения
├── CMakeLists.txt     # Основной файл CMake
├── CMakePresets.json  # Пресеты CMake
├── 50hz-spwm.ioc     # Файл конфигурации STM32CubeMX
└── README.md          # Этот файл
```

## Требования

### Программное обеспечение

- **CMake** >= 3.22
- **ARM GCC Toolchain** (arm-none-eabi-gcc)
- **STM32CubeMX** (для регенерации конфигурации)
- **Git** (для контроля версий)

### Опционально

- **OpenOCD** или **ST-Link** для прошивки и отладки
- **Visual Studio Code** с расширением C/C++

## Сборка проекта

### Конфигурация и сборка

```bash
# Конфигурация Debug сборки
cmake -B build/Debug --preset=Debug

# Сборка проекта
cmake --build build/Debug -j$(nproc)
```

### Очистка и пересборка

```bash
rm -rf build/Debug
cmake -B build/Debug --preset=Debug
cmake --build build/Debug -j$(nproc)
```

### Результаты сборки

После успешной сборки файлы будут в `build/Debug/`:
- `50hz-spwm.elf` - исполняемый файл с отладочной информацией

**Использование памяти** (базовая конфигурация):
- RAM: 1584 байт / 64 КБ (2.42%)
- Flash: 5716 байт / 256 КБ (2.18%)

## Разработка

### Модификация в STM32CubeMX

1. Откройте файл `50hz-spwm.ioc` в STM32CubeMX
2. Внесите необходимые изменения (периферия, тактирование и т.д.)
3. Сгенерируйте код
4. Добавьте пользовательский код между метками:
   ```c
   /* USER CODE BEGIN ... */
   // Ваш код здесь
   /* USER CODE END ... */
   ```

### Работа с Git

Подробная документация по работе с Git и GitHub находится в [docs/github-workflow.md](docs/github-workflow.md).

**Быстрые команды:**

```bash
# Проверить статус
git status

# Добавить изменения
git add .

# Создать коммит
git commit -m "Описание изменений"

# Отправить на GitHub
git push
```

## Прошивка

### С помощью OpenOCD

```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/Debug/50hz-spwm.elf verify reset exit"
```

### С помощью ST-Link Utility

1. Откройте ST-Link Utility
2. Подключитесь к устройству
3. Загрузите файл `build/Debug/50hz-spwm.elf`
4. Нажмите "Program & Verify"

## Документация

- [docs/README.md](docs/README.md) - Обзор документации
- [docs/github-workflow.md](docs/github-workflow.md) - Работа с Git и GitHub

## Автор

Vittorio (kvas00@gmail.com)

## Лицензия

Этот проект использует компоненты STMicroelectronics, которые предоставляются "AS-IS".
