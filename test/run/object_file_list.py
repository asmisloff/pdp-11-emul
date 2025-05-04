"""
Список имен объектных файлов, используемых в тестах.
"""

import os
import pathlib

filenames = []
root = pathlib.PurePath(os.getcwd()).parent.parent
for root, dirs, files in os.walk(root):
    path = pathlib.PurePath(root)
    if not path.name.startswith('.') and path.name != 'test':
        for file in files:
            if file.endswith('.cpp') and file != 'App.cpp':
                filenames.append(file.replace('.cpp', '.o'))
print(' '.join(filenames))
