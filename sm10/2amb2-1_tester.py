import filecmp
import os
import random
import sys

MAX_UINT64 = 2 ** 64 - 1

BINARY_MAKE_STRING = 'gcc -m32 tester.c 2amb2-1.S 2amb2-1_data.S simpleio_i686.S -o'
BINARY_NAME = '1.out'
INPUT_FILE = '1.in.txt'
OUTPUT_FILE = '1.out.txt'
REFERENCE_FILE = '1.ref.txt'


def has_diff(file1, file2):
    return not filecmp.cmp(file1, file2)


def compile_binary(binary_name):
    os.system(BINARY_MAKE_STRING + binary_name)


def evaluate_result(a, b):
    return a * 2 - b // 2


def generate_two_uint64():
    # return random.randint(0, 200), random.randint(0, 100)
    return random.randint(0, MAX_UINT64 // 2), random.randint(0, MAX_UINT64)


def has_overflow(a, b):
    if a * 2 > MAX_UINT64:
        return True
    if not (0 <= evaluate_result(a, b) <= MAX_UINT64):
        return True
    return False


def stress_test(num_tests):
    for i in range(num_tests):
        sys.stdout.write("#{test_id}: ".format(test_id = i))
        a, b = generate_two_uint64()
        if (has_overflow(a, b)):
            sys.stdout.write('{0}, {1} -> overflow\n'.format(a, b))
        else:
            result = evaluate_result(a, b)
            os.system('echo "{0} {1}" > {in_file}'.format(a, b, 
                in_file = INPUT_FILE)
            )
            os.system('echo "{result}" >{ref_file}'.format(
                result=result,
                ref_file=REFERENCE_FILE)
            )
            os.system('./{binary} <{in_file} >{out_file}'.format(
                binary=BINARY_NAME,
                in_file=INPUT_FILE,
                out_file=OUTPUT_FILE)
            )
            if has_diff(OUTPUT_FILE, REFERENCE_FILE):
                sys.stdout.write('{0}, {1} ->'.format(a, b))
                sys.stdout.write(open(OUTPUT_FILE).readlines()[0])
                os.system('cat {out_file}'.format(
                    out_file=OUTPUT_FILE)
                )
                sys.stdout.write('instead of {result}\n'.format(
                    result=result)
                )
                return 1
            else:
                sys.stdout.write('OK\n')


if __name__ == '__main__':
    compile_binary(BINARY_NAME)
    stress_test(int(input()))
