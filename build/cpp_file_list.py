"""
Список путей к файлам .cpp, кроме тестов.
"""

import os
import pathlib

PROJECT_NAME = 'pdp-11-emul'
filepaths = []
root = pathlib.PurePath(os.getcwd())
while root.parts[-1].lower() != PROJECT_NAME:
    root = root.parent
for root, dirs, files in os.walk(root):
    path = pathlib.PurePath(root)
    if not path.name.startswith('.') and path.name != 'test':
        for file in files:
            if file.endswith('.cpp') and file != 'demo.cpp':
                filepaths.append(f'{root}/{file}')
print(' '.join(filepaths))
