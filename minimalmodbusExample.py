import minimalmodbus
import serial

instrument = minimalmodbus.Instrument('COM12',1) # COM number will change depending on computer and port used


instrument.serial.baudrate = 9600 			# Sets the baud rate
instrument.serial.bytesize = 8				# Sets the byte size
instrument.serial.parity = serial.PARITY_NONE		# Specifies no parity bit
instrument.serial.stopbits = 1				# Specifies 1 stop bit
instrument.serial.timeout = 1				# Sets timeout value
instrument.mode = minimalmodbus.MODE_RTU	# Specifies the protocol

reg = instrument.read_register(12363,0,4,True)
print("Load Current: ", reg)

reg = instrument.read_register(36898,0,3) # Reads low voltage register value
# Arguments are: decimal register, number of decimals in data, function code
print("Low Voltage Protection: ", reg/100)


reg = instrument.write_bit(0,1,5) # Writes load output value
# Arguments are: decimal register, value to store, num of decimals, function code,
# and whether the data is signed/unsigned
if reg == None:
    print("Write Success")
else:
    print("Write Failure")


