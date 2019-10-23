import re

def preprocess(filepath):
    with open(filepath, 'r', encoding='utf-8') as f:
        with open('benchmark_clean.txt', 'a', encoding='utf-8') as fout:
            line = f.readline()

            i = 1
            while line:
                # print(i, line)
                
                line = f.readline()

                data = (' '.join(line.split())).split()

                if len(data) >= 5:
                    fout.write(f'{data[-2]}\n')

                print(i)
                i += 1
    print('finish!')

import os

for fi in os.listdir('wlp0'):
    try:
        preprocess('wlp0/' + fi)
        print(f'finish {fi}')
    except UnicodeDecodeError:
        continue