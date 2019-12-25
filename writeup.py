import struct
from binascii import hexlify, unhexlify

little_endian = lambda x: struct.pack("<H", x)

secret = 0x03E1
cave = 0x26D0
print_stack = 0x0391
main_patching_loc = 0x069C

call_opcode = b'\xCD'
jp_opcode = b'\xC3'
ret_opcode = b'\xC9'
nop_opcode = b'\x00'

print_flag_stack = unhexlify("21D6C02A666FE5CD9103E802")

def call(address):
	return call_opcode + little_endian(address)

def jp(address):
	return jp_opcode + little_endian(address)

def construct_code_cave():
	code = call(secret)
	code += print_flag_stack
	code += ret_opcode

	return code

def construct_main_patch():
	code = call(cave)
	code += (len(print_flag_stack) - len(code)) * nop_opcode

	return code

def patch(filename):
	cave_patch = construct_code_cave()
	main_patch = construct_main_patch()

	with open(filename, "r+b") as f:
		f.seek(main_patching_loc)
		f.write(main_patch)
		f.seek(cave)
		f.write(cave_patch)

patch("GameBob.gb")