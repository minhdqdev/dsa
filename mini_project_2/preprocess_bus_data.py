# coding=utf-8
'''


Author: Minh Dang Quang (minh.dq176823@sis.hust.edu.vn)
Reference: 
- https://gist.github.com/J2TEAM/9992744f15187ba51d46aecab21fd469
'''
from unidecode import unidecode

def preprocess(filename, output_filename=None):
    if output_filename is None:
        output_filename = filename

    lines = []

    with open(filename, 'r') as f:
        for line in f.readlines():
            if len(line) > 5:
                s = unidecode(str(line))

                line = ' - '.join([x.strip() for x in line.split('-')])

                lines.append(s)
            else:
                lines.append(line)

    with open(output_filename, 'w') as f:
        for line in lines:
            print(line)
            f.write(line)

if __name__ == '__main__':
    preprocess('pre.txt', 'bus_data.txt')