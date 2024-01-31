import numpy as np
import serial
import argparse
import sys

def run_benchmark(sample, predict, raw_predict, args):
    with serial.Serial(args.serial_port, args.serial_baudrate) as ser:
        all_runtime = []

        # avoid cold start by performing inference once and discard result
        ser.write(sample[0].astype(np.uint8).tobytes())
        if args.validate_p:
            for _ in range(args.num_class):
                ser.readline()
        ser.readline()

        # send test data and retrive runtime, stop when encounter incorrect result
        for i in range(args.num_test_sample):
            ser.write(sample[i].astype(np.uint8).tobytes())

            if args.validate_p:
                p = [int(ser.readline().decode("utf-8").strip()) for j in range(args.num_class)]
                if not np.array_equal(p, raw_predict[i].astype(int)):     
                    print (f'Incorrect p: {p} vs {raw_predict[i].astype(int)}')
                    # sys.exit(1)

            result = ser.readline()
            result = result.decode("utf-8").strip().split(' ')
            # print(result)

            board_predict = int(result[0])
            runtime = int(result[1][:-2])

            if board_predict != predict[i]:
                print (f'Incorrect result: {board_predict} vs {predict[i]}')
                sys.exit(1)

            all_runtime.append(runtime)

    return all_runtime

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate test_data.h and test_data.c')
    parser.add_argument('-i', '--test-input', help="path to the sample/predict datafile e.g. 'test/ptb_d64'. '_predict.npy' and '_sample.npy will be append automatically'")
    parser.add_argument('-c', '--num-class', type=int, help='number of class in the model')
    parser.add_argument('-r', '--timer-resolution', type=float, default=1.0, help='')
    parser.add_argument('-s', '--serial-port', help='')
    parser.add_argument('-b', '--serial-baudrate', type=int, default=115200, help='')
    parser.add_argument('-v', '--validate-p', action='store_true', help='')
    parser.add_argument('-t', '--num-test-sample', type=int, default=5, help='maximum value of the input')
    args = parser.parse_args()
    
    # load test data
    sample = np.load(args.test_input + '_sample.npy')
    predict = np.load(args.test_input + '_predict.npy')
    raw_predict = np.load(args.test_input + '_raw_predict.npy')

    runtimes = run_benchmark(sample, predict, raw_predict, args)
    print (f'Average runtime = {sum(runtimes) / args.num_test_sample * args.timer_resolution} us')


