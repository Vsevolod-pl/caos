import os
import random
import sys

MAX_INT32 = 2 ** 31 - 1
MIN_INT32 = -MAX_INT32 - 1

INPUT_NAME = '4.in.txt'
BINARY_MAKE_STRING = 'gcc -m32 tester.c segments-2.S simpleio_i686.S -o'
BINARY_NAME = '4.out'

def get_intersection_length(left1, right1, left2, right2):
    if right1 <= left2:
        return 0
    if right2 <= left1:
        return 0
    left = max(left1, left2)
    right = min(right1, right2)
    return right - left

def test_random_input(num_pairs, min_value, max_value):
    result = 0
    os.system('rm {in_file}'.format(in_file = INPUT_NAME))
    for i in range(num_pairs):
        left1, left2 = [
                random.randint(min_value, max_value) for i in range(2)
        ]
        right1 = left1 + random.randint(0, max_value)
        right2 = left2 + random.randint(0, max_value)
        os.system('echo "{0} {1} {2} {3}">>{in_file}'.format(left1, right1, left2, right2, in_file = INPUT_NAME))
        result += get_intersection_length(
                left1, right1, left2, right2,
        )
    print('Reference is {}'.format(result))
    print('Output is ')
    os.system(
        './{binary} <{in_file}'.format(
            binary = BINARY_NAME,
            in_file = INPUT_NAME,
        )
    )


def compile_binary(binary_name):
    os.system(BINARY_MAKE_STRING + binary_name)


if __name__ == '__main__':
    compile_binary(BINARY_NAME)
    test_random_input(int(input()), -10, 10)

