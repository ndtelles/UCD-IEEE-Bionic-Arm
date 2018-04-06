import argparse
import math
import serial

# Custom version of pythonosc since the original didn't suppport the OSC type d
from pythonosc import dispatcher
from pythonosc import osc_server

# Write eeg data over serial. args[0] should be the serial object
# def eeg_handler(unused_addr, args, ch1, ch2, ch3, ch4, ch5, ch6):
#     print("EEG (uV) per channel: ", ch1, ch2, ch3, ch4, ch5, ch6)
#     data = bytearray([ch1, ch2, ch3, ch4, ch5, ch6])
#     args[0].write(data)

def jaw_clench_handler(unused_addr, args, val):
    print("Jaw clenched: ", val)
    line = str(val) + '\n'
    args[0].write(line.encode()) 

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--ip",
                        default="127.0.0.1",
                        help="The ip to listen on")
    parser.add_argument("--port",
                        type=int,
                        default=5000,
                        help="The port to listen on")
    parser.add_argument("--serial_port",
                        default="COM7",
                        help="The output serial port to write to")
    parser.add_argument("--baudrate",
                        type=int,
                        default=9600,
                        help="Baud rate of the serial port to write to")                    
    args = parser.parse_args()

    ser = serial.Serial(args.serial_port, args.baudrate, timeout=0.1)
    dispatcher = dispatcher.Dispatcher()
    # dispatcher.map("/eeg", eeg_handler, ser)
    dispatcher.map("/elements/jaw_clench", jaw_clench_handler, ser)

    server = osc_server.ThreadingOSCUDPServer(
        (args.ip, args.port), dispatcher)
    print("Serving on {}".format(server.server_address))
    server.serve_forever()