import random
import os

def generate_line(input_name, reference_name, num_octets, line_id):
    with open(input_name, 'a') as f_input, open(reference_name, 'a') as f_reference:
        f_input.write('{:0>6}'.format(str(hex(line_id * 16).split('x')[-1])))
        decimal_number = 0
        for octet_id in range(num_octets):
            decimal_octet = random.randint(0, 255)
            f_input.write(' {:0>2}'.format(str(hex(decimal_octet).split('x')[-1])))
            decimal_number = decimal_number * 256 + decimal_octet
            if (octet_id + 1) % 4 == 0:
                f_reference.write('{}\n'.format(decimal_number))
                decimal_number = 0
        f_input.write('\n')


# Generate tests like
# 000000 aa bb cc ... (1-16 octets)
def generate_one_line_tests(first_test):
    for test_id in range(16):
        input_name = 'input.{}'.format(first_test + test_id)
        reference_name = 'reference.{}'.format(first_test + test_id)
        generate_line(
            input_name=input_name,
            reference_name=reference_name,
            num_octets=test_id + 1,
            line_id=0
        )


# Generate tests like
# 000000 aa bb cc ... 42 (16 octets)
# 000010 dd ee .. (1-16 octets)
def generate_two_line_tests(first_test):
    for test_id in range(16):
        input_name = 'input.{}'.format(first_test + test_id)
        reference_name = 'reference.{}'.format(first_test + test_id)
        generate_line(
            input_name=input_name,
            reference_name=reference_name,
            num_octets=16,
            line_id=0
        )
        generate_line(
            input_name=input_name,
            reference_name=reference_name,
            num_octets=test_id + 1,
            line_id=1
        )


# Generate tests like
# 000000 aa bb cc ... 42 (16 octets)
# 000010 (nothing)
def generate_two_line_no_offset_test(first_test):
    input_name = 'input.{}'.format(first_test)
    reference_name = 'reference.{}'.format(first_test)
    generate_line(
        input_name=input_name,
        reference_name=reference_name,
        num_octets=16,
        line_id=0
    )
    generate_line(
        input_name=input_name,
        reference_name=reference_name,
        num_octets=0,
        line_id=1
    )


def generate_empty_tests(first_test):
    # Test:
    # 000000
    input_name = 'input.{}'.format(first_test + 0)
    reference_name = 'reference.{}'.format(first_test + 0)
    with open(input_name, 'w') as f_input, open(reference_name, 'w') as f_reference:
        f_input.write('000000\n')
    # Test:
    # (nothing, no offset)
    input_name = 'input.{}'.format(first_test + 1)
    reference_name = 'reference.{}'.format(first_test + 1)
    with open(input_name, 'w') as f_input, open(reference_name, 'w') as f_reference:
        f_input.write('\n')


def generate_long_test(first_test):
    input_name = 'input.{}'.format(first_test + 0)
    reference_name = 'reference.{}'.format(first_test + 0)
    for line_id in range(100):
        generate_line(
            input_name,
            reference_name,
            num_octets=16,
            line_id=line_id,
        )
    generate_line(
        input_name,
        reference_name,
        num_octets=15,
        line_id=100,
    )

if __name__ == '__main__':
    os.system('rm -f input.*')
    os.system('rm -f reference.*')
    generate_one_line_tests(0)  # 16 tests, 0..15
    generate_two_line_tests(16)  # 16 tests, 16..31
    generate_two_line_no_offset_test(32)  # 1 test, 32
    generate_empty_tests(33)  # 2 tests, 33..34
    generate_long_test(35)  # 1 test, 35
