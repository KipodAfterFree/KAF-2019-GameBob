# GameBob

GameBob is an information security challenge in the reversing category, and was presented to participants of [KAF CTF 2019](https://play.kaf.sh)

## Challenge story

I built that small GameBoy program that just prints out the flag, and I don't think I forgot anything.

## Challenge exploit

This challenge is vulnerable to binary patching, which can be used after reversing the binary in order to solve the challenge.
However, this is not the only solution and the two will be discussed in the next paragraph.

## Challenge solution

The challenge consists of 2 parts. The first one is understanding the functionality of the program, and the second one is getting the flag out of the binary. That can be done either by patching or static analysis.

In the first part, the solvers should look on the symbol names at first, where they can see there are many functions related to a stack. After that, they should look for the key "flag" in the symbol names and find "_flag_stack", which is probably a stack where the flag is stored, and afterwards printed with "_print_stack". Right before it there is the global variable "_key", which we can infer from that there are some operations related to encryption / decryption on the flag. There is also a function called "_secret", which is a very suspicious one.

So now that we have some background, let's try to dive into the main function with the [bgb](http://bgb.bircd.org/) debugger. We can see using the debugger that there are many push function calls in the main, and then a call to print_stack. Probably there isn't a call to secret which does the decryption of the values on the stack. After we know that, we can patch the binary in order to add a call to secret. [Here](writeup.py) is a script that does the patching.

## Building and installing

To build the challenge, execute the following commands:
```bash
cd challenge
make.bat
```

## Usage

In order to run it, just drag GameBob.gb into [bgb](http://bgb.bircd.org/).

## Flag

Flag is:
```flagscript
KAF{g4m3b0y_15_n07_50_0ld}
```

## License
[MIT License](https://choosealicense.com/licenses/mit/)
