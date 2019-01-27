import os

def run_tests(num_tests):
    os.system('rm -f ./betole_tests/output.*')
    for test_id in range(num_tests):
        os.system('./betole-1 <./betole_tests/input.{0} >./betole_tests/output.{0}'.format(test_id))
        print("Test {}".format(test_id))
        os.system('diff ./betole_tests/output.{0} ./betole_tests/reference.{0}'.format(test_id))

if __name__ == '__main__':
    num_tests = int(input())
    run_tests(num_tests)
