# Работа с GitHub для проекта 50hz-spwm

## Информация о репозитории

- **URL репозитория**: https://github.com/kvas00/50hz-spwm
- **Автор**: Vittorio (kvas00@gmail.com)
- **Основная ветка**: main

## Начальная настройка (уже выполнено)

### Git конфигурация
```bash
git config user.name "Vittorio"
git config user.email "kvas00@gmail.com"
```

### SSH ключ для GitHub
SSH ключ уже создан и находится в `~/.ssh/id_ed25519.pub`

Публичный ключ для добавления на GitHub:
```
ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIHRYr0ofyqIB/WcpgLgLkQ6D7LSTlMuJgLvDh0S1FGj9 kvas00@gmail.com
```

**Добавление SSH ключа на GitHub:**
1. Откройте https://github.com/settings/ssh/new
2. Вставьте ключ выше в поле "Key"
3. Укажите название (например, "Linux Workstation")
4. Нажмите "Add SSH key"

## Базовые команды для ежедневной работы

### 1. Проверка статуса
```bash
git status
```
Показывает измененные файлы и текущую ветку.

### 2. Просмотр изменений
```bash
git diff
```
Показывает, что именно изменилось в файлах.

### 3. Добавление изменений
```bash
# Добавить все изменённые файлы
git add .

# Добавить конкретный файл
git add Core/Src/main.c

# Добавить файлы по шаблону
git add Core/Src/*.c
```

### 4. Создание коммита
```bash
git commit -m "Описание изменений"
```

**Пример хорошего сообщения коммита:**
```bash
git commit -m "Add PWM configuration for TIM2 channels 1 and 2"
```

### 5. Отправка на GitHub
```bash
# Первый раз (уже выполнено)
git push -u origin main

# Последующие разы
git push
```

### 6. Получение изменений с GitHub
```bash
# Загрузить и применить изменения
git pull

# Только загрузить без применения
git fetch
```

## Типичный рабочий процесс

### Внесение изменений в проект

1. **Внесите изменения в код** (например, в CubeMX или вручную)

2. **Проверьте, что изменилось:**
   ```bash
   git status
   git diff
   ```

3. **Соберите проект и убедитесь, что всё работает:**
   ```bash
   cmake --build build/Debug
   ```

4. **Добавьте изменения:**
   ```bash
   git add .
   ```

5. **Создайте коммит:**
   ```bash
   git commit -m "Краткое описание изменений

   Более подробное описание, если нужно.
   Можно использовать несколько строк."
   ```

6. **Отправьте на GitHub:**
   ```bash
   git push
   ```

## Работа с ветками

### Создание новой ветки для экспериментов
```bash
# Создать и переключиться на новую ветку
git checkout -b feature/pwm-frequency-control

# Работайте с кодом...

# Коммит изменений
git add .
git commit -m "Experiment with PWM frequency control"

# Отправка ветки на GitHub
git push -u origin feature/pwm-frequency-control
```

### Переключение между ветками
```bash
# Вернуться на основную ветку
git checkout main

# Переключиться на другую ветку
git checkout feature/pwm-frequency-control
```

### Слияние веток
```bash
# Переключиться на main
git checkout main

# Слить изменения из другой ветки
git merge feature/pwm-frequency-control

# Отправить на GitHub
git push
```

## Просмотр истории

### История коммитов
```bash
# Краткая история
git log --oneline

# Подробная история
git log

# История с графиком веток
git log --graph --oneline --all

# Последние 5 коммитов
git log -5
```

### Просмотр конкретного коммита
```bash
git show <хеш-коммита>

# Например
git show 55168f4
```

## Отмена изменений

### Отменить изменения в файле (до add)
```bash
git checkout -- Core/Src/main.c
```

### Убрать файл из staged (после add, до commit)
```bash
git reset HEAD Core/Src/main.c
```

### Отменить последний коммит (локально)
```bash
# Отменить коммит, но оставить изменения
git reset --soft HEAD~1

# Отменить коммит и изменения
git reset --hard HEAD~1
```

⚠️ **Внимание**: Не используйте `--hard` если не уверены! Изменения будут потеряны.

## Полезные советы

### .gitignore
Файл `.gitignore` уже настроен и игнорирует:
- Каталог `build/` - артефакты сборки
- Файлы `.vscode/` - настройки IDE
- Скомпилированные файлы (*.o, *.elf, *.bin)

### Просмотр удалённых репозиториев
```bash
git remote -v
```

### Клонирование репозитория на другой компьютер
```bash
# С SSH (после добавления SSH ключа)
git clone git@github.com:kvas00/50hz-spwm.git

# С HTTPS
git clone https://github.com/kvas00/50hz-spwm.git
```

## Работа с CubeMX

### После регенерации кода в CubeMX

1. **CubeMX сохраняет пользовательский код** между метками:
   ```c
   /* USER CODE BEGIN ... */
   // Ваш код здесь
   /* USER CODE END ... */
   ```

2. **Проверьте изменения:**
   ```bash
   git diff
   ```

3. **Если всё корректно, закоммитьте:**
   ```bash
   git add .
   git commit -m "Update CubeMX configuration: enable TIM2 PWM"
   git push
   ```

## Безопасность

### Удаление старого токена
После настройки SSH ключа удалите старый Personal Access Token:
1. Откройте https://github.com/settings/tokens
2. Найдите старый токен
3. Нажмите "Delete"

### Проверка SSH соединения
```bash
ssh -T git@github.com
```

Должно вывести: `Hi kvas00! You've successfully authenticated...`

## Решение проблем

### Проблема: git push требует пароль
**Решение**: Убедитесь, что используется SSH URL:
```bash
git remote set-url origin git@github.com:kvas00/50hz-spwm.git
```

### Проблема: конфликт при git pull
**Решение**:
```bash
# Посмотрите конфликтующие файлы
git status

# Отредактируйте файлы вручную, удалив маркеры конфликта
# Затем:
git add .
git commit -m "Resolve merge conflict"
git push
```

### Проблема: случайно закоммитил ненужный файл
**Решение**:
```bash
# Удалить из git, но оставить в файловой системе
git rm --cached путь/к/файлу

# Добавить в .gitignore
echo "путь/к/файлу" >> .gitignore

# Закоммитить изменения
git add .gitignore
git commit -m "Remove accidentally committed file"
git push
```

## Дополнительные ресурсы

- **GitHub репозиторий**: https://github.com/kvas00/50hz-spwm
- **Git документация**: https://git-scm.com/doc
- **GitHub документация**: https://docs.github.com

## Шпаргалка команд

```bash
# Статус
git status

# Добавить все изменения
git add .

# Коммит
git commit -m "Сообщение"

# Отправить на GitHub
git push

# Получить с GitHub
git pull

# История
git log --oneline

# Создать ветку
git checkout -b имя-ветки

# Переключиться на ветку
git checkout имя-ветки

# Слить ветку в текущую
git merge имя-ветки

# Посмотреть изменения
git diff

# Отменить изменения в файле
git checkout -- имя-файла
```
