"""
Список путей к файлам .cpp, кроме тестов.
"""

import os
import pathlib

filepaths = []
root = pathlib.PurePath(os.getcwd()).parent.parent
for root, dirs, files in os.walk(root):
    path = pathlib.PurePath(root)
    if not path.name.startswith('.') and path.name != 'test':
        for file in files:
            if file.endswith('.cpp') and file != 'App.cpp':
                filepaths.append(f'{root}/{file}')
print(' '.join(filepaths))
