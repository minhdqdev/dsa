import random
import string

def randomString(stringLength=10):
    """Generate a random string of fixed length """
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(stringLength))

def randomStringDigits(stringLength=6):
    """Generate a random string of letters and digits """
    lettersAndDigits = string.ascii_letters + string.digits
    return ''.join(random.choice(lettersAndDigits) for i in range(stringLength))


i = 1
with open('benchmark_clean_3.txt', 'a') as f:
    while True:
        f.write(randomStringDigits(random.randint(5, 25)) + '\n')

        print(i)
        i += 1
        if i == 20000:
            print('finish generating')
            break