#!/usr/bin/env python

import glob
import re
import random

files = glob.glob("input*.txt", recursive=False)
files = [
    int(re.match("^input(\d+).txt", f).group(1)) for f in files
]
files.sort()
n = max(files) + 1
for i in range(10):
    filename = f'input{n+i}.txt'
    with open(filename, 'w') as f:
        a = random.randint(0, 100000000000)
        b = random.randint(0, 100000000000)
        c = a * b
        f.write(f'{a}\n{b}\n{c}\n')
