# Second task

## Installation

Для корректной работы программы требуется GraphViz и Doxygen

```sh
sudo apt-get install graphviz                        # debian
sudo apt-get install doxygen doxygen-doc doxygen-gui # debian
```

## Launch

Компиляция всего проекта

```sh
make
```

Запуск

```sh
./task2.out
```

Для запуска всех тестов

```sh
./launch_tests.sh
```

Для создания и просмотра документации с помощью браузера firefox

```sh
make docs
firefox html/index.html
```

Также я использую удобный для меня и дебага скрипт запуска всего-всего и просмотра всех дампов.
```sh
./m
```

ALERT: используется консольный просматриватель jpeg: feh.
Его надо устанавить отдельно или поменять в скрипте
```sh
sudo apt-get install feh # debian
```
