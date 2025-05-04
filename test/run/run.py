"""
Сборка, запуск и удаление исполняемого файла с тестом.
"""

import sys
import os
import pathlib

TEST_CPP = sys.argv[1]
EXE = pathlib.PurePath(TEST_CPP).name[:-4]
OBJ_FILES = ''
if len(sys.argv) > 1:
    OBJ_FILES = ' '.join(sys.argv[2:])
CC = 'g++ -std=c++17 -g -Wall -Wextra'
CMD = f'{CC} {TEST_CPP} {OBJ_FILES} -o ../{EXE}'
os.system(CMD)
os.system(f'cd .. && ./{EXE}')
os.system(f'rm ../{EXE}')
