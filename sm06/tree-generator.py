import random
import os

def generate_test():
    num_trees = random.randint(0, 5)
    input_sequence = []
    reference_sequence = []
    for i in range(num_trees):
        tree_length = random.randint(0, 10)
        tree_set = set()
        for i in range(tree_length):
            item = random.randint(1, 10)
            input_sequence.append(item)
            tree_set.add(item)
        input_sequence.append(0)
        for item in reversed(sorted(tree_set)):
            reference_sequence.append(item)
        reference_sequence.append(0)

    return ' '.join(str(x) for x in input_sequence), ' '.join(str(x) for x in reference_sequence)


def run_tests(num_tests):
    BINARY_NAME = 'alexa'
    INPUT_NAME = 'input_alexa'
    OUTPUT_NAME = 'output_alexa'
    REFERENCE_NAME = 'reference_alexa'
    for i in range(num_tests):
        input_s, reference_s = generate_test()
        with open('{}{}'.format(INPUT_NAME, i), 'w') as f_input:
           f_input.write(input_s)
        with open('{}{}'.format(REFERENCE_NAME, i), 'w') as f_reference:
           f_reference.write(reference_s)
           f_reference.write('\n')
        os.system('./{3} <{0}{2} >{1}{2}'.format(INPUT_NAME, OUTPUT_NAME, i, BINARY_NAME))
        os.system('diff {0}{2} {1}{2}'.format(OUTPUT_NAME, REFERENCE_NAME, i))


if __name__ == '__main__':
    run_tests(int(input()))
