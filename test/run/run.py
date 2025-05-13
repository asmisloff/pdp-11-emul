"""
Сборка, запуск и удаление исполняемого файла с тестом.
"""

import sys
import os
import pathlib
import platform

TEST_CPP = sys.argv[1]
EXE = pathlib.PurePath(TEST_CPP).name[:-4]
OBJ_FILES = ''
if len(sys.argv) > 1:
    OBJ_FILES = ' '.join(sys.argv[2:])
CC = 'g++ -std=c++17 -g -Wall -Wextra'
CMD = f'{CC} {TEST_CPP} {OBJ_FILES} -o ../{EXE}'
RUN_CMD = f'./{EXE}' if platform.system() == 'Linux' else f'{EXE}.exe'
RM_CMD = f'rm ../{EXE}' if platform.system() == 'Linux' else f'rm ../{EXE}.exe'
os.system(CMD)
os.system(f'cd .. && {RUN_CMD}')
os.system(RM_CMD)
