'''

Author: Minh Dang Quang (minh.dq176823@sis.hust.edu.vn)
Reference: 
- https://gist.github.com/J2TEAM/9992744f15187ba51d46aecab21fd469
'''
from unidecode import unidecode
from random import randint

def preprocess(filename, output_filename=None):
    if output_filename is None:
        output_filename = filename

    lines = []

    # remove accents
    with open(filename, 'r') as f:
        for line in f.readlines():
            s = unidecode(str(line))
            line = ' - '.join([x.strip() for x in s.split(' - ')])
            lines.append(line + '\n')
    
    with open(filename, 'w') as f:
        for line in lines:
            f.write(line)
        

    data = {}
    vertices = {}
    edges = []
    k = 0
    with open(filename, 'r') as f:
        route_id = ''
        for i, line in enumerate(f.readlines()):
            if i % 3 == 0: # route id
                route_id = line.strip()

                edges = []
                data[route_id] = []
                continue
            
            templist = [x.strip() for x in line.split(' - ')]

            for j, v in enumerate(templist[:len(templist)-1]):
                v = v.strip()
                if j % 2 != 0:
                    if templist[j-1] not in vertices.keys():
                        vertices[templist[j-1]] = k
                        k += 1
                    if templist[j+1] not in vertices.keys():
                        vertices[templist[j+1]] = k
                        k += 1
                    
                    edges.append([vertices[templist[j-1]], vertices[templist[j+1]], v])

            data[route_id] = edges

    with open(output_filename, 'w') as f:
        f.write('# VERTICES\n')
        for verticeName in sorted(list(vertices.keys())):
        # for verticeName in vertices.keys():
            f.write(f'{vertices[verticeName]} : {verticeName}\n')

        for route_id in data.keys():
            f.write(f'# ROUTE_ID\n{route_id}\n## EDGES\n')

            for e in data[route_id]:
                f.write(f'{e[0]} {e[1]} {e[2]}\n')


if __name__ == '__main__':
    preprocess('pre.txt', 'bus_data.txt')