import os

N = 30
N_SERIAL = 5

def exercise_2():
    os.system('gcc -o dgemm_serial_ss ./dgemm_serial_ss.c')
    os.system(f'python3 exec_times.py -n {N_SERIAL} -i ./dgemm_serial_ss -o ./e2/times_no_o2')
    
    os.system('gcc -o dgemm_serial_ss_o2 ./dgemm_serial_ss.c -O2')
    os.system(f'python3 exec_times.py -n {N_SERIAL} -i ./dgemm_serial_ss_o2 -o ./e2/times_o2')

def exercise_3():
    os.system('gcc -msse -o dgemm_data_parallelism_ss ./dgemm_data_parallelism_ss.c -O3')
    os.system(f'python3 exec_times.py -n {N} -i ./dgemm_data_parallelism_ss -o ./e3/times')
    
def exercise_4():
    os.system('gcc -msse -o dgemm_instruction_parallelism_ss ./dgemm_instruction_parallelism_ss.c -O3')
    os.system(f'python3 exec_times.py -n {N} -i ./dgemm_instruction_parallelism_ss -o ./e4/times')
    
def exercise_5():
    os.system('gcc -msse -o dgemm_cache_parallel_ss ./dgemm_cache_parallel_ss.c -O3')
    os.system(f'python3 exec_times.py -n {N} -i ./dgemm_cache_parallel_ss -o ./e5/times')
    
def exercise_6():
    os.system('gcc -msse -fopenmp -o dgemm_multithread_parallel_ss ./dgemm_multithread_parallel_ss.c -O3')
    os.system(f'python3 exec_times.py 1 -n {N} -i ./dgemm_multithread_parallel_ss -o ./e6/times_1')
    os.system(f'python3 exec_times.py 2 -n {N} -i ./dgemm_multithread_parallel_ss -o ./e6/times_2')
    os.system(f'python3 exec_times.py 4 -n {N} -i ./dgemm_multithread_parallel_ss -o ./e6/times_4')
    os.system(f'python3 exec_times.py 8 -n {N} -i ./dgemm_multithread_parallel_ss -o ./e6/times_8')
    

# print('Executing exercise 2...')
# exercise_2()

# print('Executing exercise 3...')
# exercise_3()

# print('Executing exercise 4...')
# exercise_4()

# print('Executing exercise 5...')
# exercise_5()

print('Executing exercise 6...')
exercise_6()
