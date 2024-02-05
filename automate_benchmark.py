import os
import subprocess
import sys
import argparse
import benchmark
import numpy as np
import time
from prettytable import PrettyTable

vanilla_ldc_configs = [
    '-DMICROVSA_IMPL=MICROVSA_IMPL_VANILLA_LDC',
    '-DMICROVSA_IMPL=MICROVSA_IMPL_VANILLA_LDC -DMICROVSA_IMPL_FIX_SIZE'
]

binary_ldc_configs_8_bit = [
    '-DMICROVSA_IMPL=MICROVSA_IMPL_BINARY_LDC -DMODEL_TRANSPOSE_F -DMICROVSA_IMPL_USE_LUT -DMICROVSA_IMPL_LUTBIT=8 -DMICROVSA_IMPL_FLAVOR_8BITADD',
    '-DMICROVSA_IMPL=MICROVSA_IMPL_BINARY_LDC -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_F -DMICROVSA_IMPL_USE_LUT -DMICROVSA_IMPL_LUTBIT=8 -DMICROVSA_IMPL_FLAVOR_8BITADD'
]

binary_ldc_configs_16_bit = [
    '-DMICROVSA_IMPL=MICROVSA_IMPL_BINARY_LDC -DMODEL_TRANSPOSE_F -DMICROVSA_IMPL_USE_LUT -DMICROVSA_IMPL_LUTBIT=8',
    '-DMICROVSA_IMPL=MICROVSA_IMPL_BINARY_LDC -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_F -DMICROVSA_IMPL_USE_LUT -DMICROVSA_IMPL_LUTBIT=8'
]

binary_ldc_configs_32_bit = [
    '-DMICROVSA_IMPL=MICROVSA_IMPL_BINARY_LDC -DMODEL_TRANSPOSE_F',
    '-DMICROVSA_IMPL=MICROVSA_IMPL_BINARY_LDC -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_F',
    '-DMICROVSA_IMPL=MICROVSA_IMPL_BINARY_LDC -DMODEL_TRANSPOSE_F -DMICROVSA_IMPL_USE_LUT -DMICROVSA_IMPL_LUTBIT=11',
    '-DMICROVSA_IMPL=MICROVSA_IMPL_BINARY_LDC -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_F -DMICROVSA_IMPL_USE_LUT -DMICROVSA_IMPL_LUTBIT=11'
]

mcu_opt_configs_8bit = {
    'MCU-Optimized (C/C)': ['-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_FIX_SIZE',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_FLAVOR_8BITADD -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_FLAVOR_8BITADD -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_POINTERIZE -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_POINTERIZE -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_UNROLL -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_UNROLL -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_UNROLL -DMICROVSA_IMPL_FLAVOR_8BITADD -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_UNROLL -DMICROVSA_IMPL_FLAVOR_8BITADD -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C'],
    'MCU-Optimized (C/R)': ['-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CR',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CR -DMICROVSA_IMPL_FIX_SIZE',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CR -DMICROVSA_IMPL_OPTIMIZE_MEM -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CR -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CR -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_FLAVOR_8BITADD -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CR -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_FLAVOR_8BITADD -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CR -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_POINTERIZE -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CR -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_POINTERIZE -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_C'],
    'MCU-Optimized (R/R I)': ['-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI',
                              '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI -DMICROVSA_IMPL_FIX_SIZE',
                              '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI -DMICROVSA_IMPL_POINTERIZE',
                              '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI -DMICROVSA_IMPL_POINTERIZE -DMICROVSA_IMPL_FIX_SIZE',
                              '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI -DMICROVSA_IMPL_POINTERIZE -DMICROVSA_IMPL_FLAVOR_8BITADD',
                              '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI -DMICROVSA_IMPL_POINTERIZE -DMICROVSA_IMPL_FIX_SIZE -DMICROVSA_IMPL_FLAVOR_8BITADD',
                              '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI -DMICROVSA_IMPL_UNROLL',
                              '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI -DMICROVSA_IMPL_UNROLL -DMICROVSA_IMPL_FIX_SIZE',
                              '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI -DMICROVSA_IMPL_UNROLL -DMICROVSA_IMPL_FLAVOR_8BITADD',
                              '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI -DMICROVSA_IMPL_UNROLL -DMICROVSA_IMPL_FIX_SIZE -DMICROVSA_IMPL_FLAVOR_8BITADD'],
    'MCU-Optimized (R/R II)': ['-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRII',
                               '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRII -DMICROVSA_IMPL_FIX_SIZE',
                               '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRII -DMICROVSA_IMPL_OPTIMIZE_MEM',
                               '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRII -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_FIX_SIZE',
                               '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRII -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_FLAVOR_8BITADD',
                               '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRII -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_FLAVOR_8BITADD -DMICROVSA_IMPL_FIX_SIZE',
                               '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRII -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_POINTERIZE',
                               '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRII -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_POINTERIZE -DMICROVSA_IMPL_FIX_SIZE']
}

mcu_opt_configs_16_32bit = {
    'MCU-Optimized (C/C)': ['-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_FIX_SIZE',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_POINTERIZE -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_POINTERIZE -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_UNROLL -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CC -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_UNROLL -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_F -DMODEL_TRANSPOSE_C'],
    'MCU-Optimized (C/R)': ['-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CR',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CR -DMICROVSA_IMPL_FIX_SIZE',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CR -DMICROVSA_IMPL_OPTIMIZE_MEM -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CR -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CR -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_POINTERIZE -DMODEL_TRANSPOSE_C',
                            '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_CR -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_POINTERIZE -DMICROVSA_IMPL_FIX_SIZE -DMODEL_TRANSPOSE_C'],
    'MCU-Optimized (R/R I)': ['-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI',
                              '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI -DMICROVSA_IMPL_FIX_SIZE',
                              '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI -DMICROVSA_IMPL_POINTERIZE',
                              '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI -DMICROVSA_IMPL_POINTERIZE -DMICROVSA_IMPL_FIX_SIZE',
                              '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI -DMICROVSA_IMPL_UNROLL',
                              '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRI -DMICROVSA_IMPL_UNROLL -DMICROVSA_IMPL_FIX_SIZE'],
    'MCU-Optimized (R/R II)': ['-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRII',
                               '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRII -DMICROVSA_IMPL_FIX_SIZE',
                               '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRII -DMICROVSA_IMPL_OPTIMIZE_MEM',
                               '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRII -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_FIX_SIZE',
                               '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRII -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_POINTERIZE',
                               '-DMICROVSA_IMPL=MICROVSA_IMPL_MCU_OPT_RRII -DMICROVSA_IMPL_OPTIMIZE_MEM -DMICROVSA_IMPL_POINTERIZE -DMICROVSA_IMPL_FIX_SIZE']
}

def assert_file_already_existed(paths):
    for p in paths:
        if os.path.exists(p):
            print (f'Error: {p} is already existed. Please run the cleanup script (./cleanup.sh) and try again.')
            sys.exit(1)

def extract_ram_flash_usage(log):
    ram = 0
    flash = 0
    lines = log.split('\n')
    for l in lines:
        if l.startswith('RAM:'):
            token = l.split(' ')
            ram = int(token[token.index('(used') + 1])
        if l.startswith('Flash:'):
            token = l.split(' ')
            flash = int(token[token.index('(used') + 1])
    return ram, flash

def upload_and_benchmark(project_dir, config, sample, predict, raw_predict, args):
    # build and upload    
    process = subprocess.run(f'PLATFORMIO_BUILD_FLAGS=\'{config}\' {args.platformio_path} run -t upload -d {project_dir}', shell=True, capture_output=True)
    if process.returncode != 0:
        print (process.stdout.decode('utf-8'))
        print (process.stderr.decode('utf-8'))
        sys.exit(1)
    log = process.stdout.decode('utf-8')
    ram, flash = extract_ram_flash_usage(log)

    time.sleep(2)

    # run benchmark and measure runtime
    all_runtime = benchmark.run_benchmark(sample, predict, raw_predict, args)
    avg_runtime = sum(all_runtime) / len(all_runtime)

    return ram, flash, avg_runtime

def get_source_dir_name(project_dir):
    if os.path.exists(os.path.join(project_dir, 'src')):
        return 'src'    # most development boards except ST
    else:
        return 'Src'    # project generated by stm32pio
    
def get_include_dir_name(project_dir):
    if os.path.exists(os.path.join(project_dir, 'src')):
        return 'src'    # most development boards except ST
    else:
        return 'Inc'    # project generated by stm32pio

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate test_data.h and test_data.c')
    parser.add_argument('-i', '--mcu-dir', help='name of the example directory to run the benchmark e.g. ESP32, STM32L0_PIO, etc.')
    parser.add_argument('-w', '--word-size', type=int, help="MCU's word size in bit (8, 16 or 32)")
    parser.add_argument('-m', '--model', help="name of the model e.g. ptb, qksd, har, fsdd etc.")
    parser.add_argument('-d', '--df', type=int, help="dimension of the F, V, and C vector in bit (Df in the paper)")
    parser.add_argument('-c', '--num-class', type=int, help='number of class in the model')
    parser.add_argument('-r', '--timer-resolution', type=float, default=1.0, help='unit of time return from the MCU timer (see benchmark_util.c). default to 1us.')
    parser.add_argument('-s', '--serial-port', help='')
    parser.add_argument('-b', '--serial-baudrate', type=int, default=115200, help='')
    parser.add_argument('--platformio_path', default='pio', help="path to the platformio executable. default to 'pio'.")
    parser.add_argument('-v', '--validate-p', action='store_true', help='')
    parser.add_argument('-t', '--num-test-sample', type=int, default=5, help='maximum value of the input')
    args = parser.parse_args()

    project_dir = f'examples/{args.mcu_dir}'
    assert_file_already_existed([f'{project_dir}/{get_include_dir_name(project_dir)}/model.h', f'{project_dir}/{get_source_dir_name(project_dir)}/model.c'])

    table = PrettyTable()
    table.field_names = ['Config', 'RAM (Bytes)', 'Flash (Bytes)', 'Runtime (us)']

    common_build_flag = f' -DMICROVSA_MAX_NUM_CLASS={args.num_class} -DMICROVSA_MAX_FHV_DIM={args.df // args.word_size} -DMICROVSA_MAX_FHV_DIM_BIT={args.df} '
    if args.validate_p:
        common_build_flag += ' -DMICROVSA_IMPL_DEBUG_P '

    # load test data for vanilla and binary LDC
    sample = np.load(f'test_data/{args.model}_{args.df}s_sample.npy')
    predict = np.load(f'test_data/{args.model}_{args.df}s_predict.npy')
    raw_predict = np.load(f'test_data/{args.model}_{args.df}s_raw_predict.npy')

    # test vanilla LDC
    print ('Testing vanilla LDC...')
    os.symlink(f'../../../model/model_{args.model}_{args.df}sb.h', f'{project_dir}/{get_include_dir_name(project_dir)}/model.h')
    os.symlink(f'../../../model/model_{args.model}_{args.df}sb.c', f'{project_dir}/{get_source_dir_name(project_dir)}/model.c')
    results = []
    for i, build_flag in enumerate(vanilla_ldc_configs):
        print (f'    Configuration {i+1}/{len(vanilla_ldc_configs)}...')
        ram, flash, avg_runtime = upload_and_benchmark(project_dir, build_flag + common_build_flag, sample, predict, raw_predict, args)
        results.append([ram, flash, avg_runtime])
    best_result = min(results, key=lambda e: e[2])
    table.add_row(['Vanilla LDC', best_result[0], best_result[1], best_result[2]])
    os.remove(f'{project_dir}/{get_include_dir_name(project_dir)}/model.h')
    os.remove(f'{project_dir}/{get_source_dir_name(project_dir)}/model.c')

    # test binary LDC
    print ('Testing binary LDC...')
    os.symlink(f'../../../model/model_{args.model}_{args.df}s.h', f'{project_dir}/{get_include_dir_name(project_dir)}/model.h')
    os.symlink(f'../../../model/model_{args.model}_{args.df}s.c', f'{project_dir}/{get_source_dir_name(project_dir)}/model.c')
    if args.word_size == 8:
        configs = binary_ldc_configs_8_bit
    elif args.word_size == 16:
        configs = binary_ldc_configs_16_bit
    else:
        configs = binary_ldc_configs_32_bit
    results = []
    for i, build_flag in enumerate(configs):
        print (f'    Configuration {i+1}/{len(configs)}...')
        ram, flash, avg_runtime = upload_and_benchmark(project_dir, build_flag + common_build_flag, sample, predict, raw_predict, args)
        results.append([ram, flash, avg_runtime])
    best_result = min(results, key=lambda e: e[2])
    table.add_row(['Binary LDC', best_result[0], best_result[1], best_result[2]])
    os.remove(f'{project_dir}/{get_include_dir_name(project_dir)}/model.h')
    os.remove(f'{project_dir}/{get_source_dir_name(project_dir)}/model.c')

    # load test data for MCU-optimized LDC
    sample = np.load(f'test_data/{args.model}_{args.df}_sample.npy')
    predict = np.load(f'test_data/{args.model}_{args.df}_predict.npy')
    raw_predict = np.load(f'test_data/{args.model}_{args.df}_raw_predict.npy')

    # test MCU-optimized LDC
    os.symlink(f'../../../model/model_{args.model}_{args.df}.h', f'{project_dir}/{get_include_dir_name(project_dir)}/model.h')
    os.symlink(f'../../../model/model_{args.model}_{args.df}.c', f'{project_dir}/{get_source_dir_name(project_dir)}/model.c')
    if args.word_size == 8:
        configs = mcu_opt_configs_8bit
    else:
        configs = mcu_opt_configs_16_32bit
    for opt_name in ['LUT', 'Bit-fiddling']:
        if opt_name == 'LUT': 
            extra_flag = f' -DMICROVSA_IMPL_USE_LUT -DMICROVSA_IMPL_LUTBIT={8 if args.word_size != 32 else 11} '
        elif opt_name == 'Bit-fiddling':
            # only 32-bit MCU support bit-fiddling
            if args.word_size != 32:
                continue
            extra_flag = ''

        for name, build_flags in configs.items():
            full_name = f'{name} ({opt_name})'
            print (f'Testing {full_name}...')
            results = []
            for i, build_flag in enumerate(build_flags):
                print (f'    Configuration {i+1}/{len(build_flags)}...')
                ram, flash, avg_runtime = upload_and_benchmark(project_dir, build_flag + common_build_flag + extra_flag, sample, predict, raw_predict, args)
                results.append([ram, flash, avg_runtime])
            best_result = min(results, key=lambda e: e[2])
            table.add_row([full_name, best_result[0], best_result[1], best_result[2]])
    os.remove(f'{project_dir}/{get_include_dir_name(project_dir)}/model.h')
    os.remove(f'{project_dir}/{get_source_dir_name(project_dir)}/model.c')

    print (table)
