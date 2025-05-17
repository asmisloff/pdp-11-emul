Эмулятор PDP-11.
По материалам курса https://stepik.org/course/65259/syllabus
Тестовые данные взяты из репозитория автора курса: https://github.com/tatyderb/pdp11_tests.git

##Использование
После клонирования инициализировать и обновить подмодуль с контрольными примерами:
git submodule init
git submodule update

###Запуск тестов (на Linux или MSYS2 на Windows)
cd ./test/run/
make

###Сборка демо (на Linux или MSYS2 на Windows)
cd ./build/
make demo
Исполняемый файл будет называться ./build/pdp11
Демо запускает эмулятор и читает код программы из stdin.
Пример запуска (из папки build):
    ./pdp11 < ../test/e2e/zachet/putoct/putoct.pdp.o