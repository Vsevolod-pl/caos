import random

def random_utf8_string(n):
    result=u""
    for i in xrange(n):
        a = u"\\u%04x" % random.randrange(0x10000)
        result = result + a.decode('unicode-escape')
    with open("input.txt", 'w') as f:
        f.write(result)

if __name__ == '__main__':
    random_utf8_string(int(input()));
