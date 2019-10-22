import re


with open('tv_wlp.txt', 'r') as f:
    with open('benchmark_clean.txt', 'w') as fout:
        line = f.readline()

        i = 1
        while line:
            # print(i, line)
            
            line = f.readline()

            data = (' '.join(line.split())).split()

            if len(data) >= 5:
                fout.write(f'{data[-2]}\n')

            # if i == 20:
            #     break
            print(i)
            i += 1
print('finish!')