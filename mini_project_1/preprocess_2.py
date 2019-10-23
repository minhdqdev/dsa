
with open('benchmark_clean_3.txt', 'r') as f:
    with open('benchmark_clean_4.txt', 'a') as fout:
        a = {}

        line = f.readline()

        i = 1
        while line:
            if line not in a.keys():
                a[line] = 1
            else:
                a[line] += 1

            line = f.readline()
            
            print(i)
            i += 1
        print('finish phase 1')

        for k in a.keys():
            fout.write(f'{k}')
        print('finish phase 2')
        
