
def print_formatted(n):
    d = len(bin(n))-2
    
    for i in range(1, n+1):
        dec_str = "{}".format(i).rjust(d)
        oct_str = " {:o}".format(i).rjust(d)
        hex_str = " {:x}".format(i).rjust(d)
        bin_str = " {:b}".format(i).rjust(d)

        print("{}{}{}{}".format(dec_str, oct_str, hex_str, bin_str))


if __name__ == '__main__':
    n = int(input())
    print_formatted(n)