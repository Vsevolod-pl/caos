import os
import random
import sys

MAX_INT64 = 2 ** 64 - 1

INPUT_NAME = '5.in.txt'
OUTPUT_NAME = '5.out.txt'
REFERENCE_NAME = '5.ref.txt'
BINARY_MAKE_STRING = 'gcc -m32 mul64-1.S main.c -o'
BINARY_NAME = '5.out'
LOG_NAME = '5.log.txt'


def run_test(x, y):
    os.system('echo "{0} {1}" >{in_file}'.format(x, y, in_file = INPUT_NAME))
    os.system('echo "{0}" >{ref_file}'.format(hex(x * y)[2:], ref_file = REFERENCE_NAME))
    os.system('./{binary} <{in_file} >{out_file} && diff {ref_file} {out_file} >>{log_file}'.format(
            binary = BINARY_NAME,
            in_file = INPUT_NAME,
            out_file = OUTPUT_NAME,
            ref_file = REFERENCE_NAME,
            log_file = LOG_NAME,
        )
    )


def small_tests(max_n):
    for i in range(max_n):
        for j in range(max_n):
            run_test(i, j)

def big_tests():
    for i in range(MAX_INT64 - 10, MAX_INT64 + 1):
        for j in range(MAX_INT64 - 10, MAX_INT64 + 1):
            run_test(i, j)

def random_tests(num_tests):
    for i in range(num_tests):
        x = random.randint(0, MAX_INT64)
        y = random.randint(0, MAX_INT64)
        run_test(x, y)

def compile_binary(binary_name):
    os.system(BINARY_MAKE_STRING + binary_name)


if __name__ == '__main__':
    os.system('rm -f {0}'.format(LOG_NAME))
    compile_binary(BINARY_NAME)
    print('input max small n:')
    small_tests(int(input()))
    print("small OK")
    big_tests()
    print("big OK")
    print("input # random tests:")
    random_tests(int(input()))
    print("random OK")

