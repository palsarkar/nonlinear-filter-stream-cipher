The file ref-impl.c provides the C code for the reference implementation of the concrete stream cipher proposals made in https://eprint.iacr.org/2025/160 and https://arxiv.org/abs/2502.01110. 

To obtain the executable for S-163-37 compile using gcc -DKAPPA80 -o S-163-37 ref-impl.c
To obtain the executable for S-257-59 compile using gcc -DKAPPA128 -o S-257-59 ref-impl.c
To obtain the executable for S-331-71 compile using gcc -DKAPPA160 -o S-331-71 ref-impl.c
To obtain the executable for S-389-87 compile using gcc -DKAPPA192 -o S-389-87 ref-impl.c
To obtain the executable for S-449-101 compile using gcc -DKAPPA224 -o S-449-101 ref-impl.c
To obtain the executable for S-521-115 compile using gcc -DKAPPA256 -o S-521-115 ref-impl.c

Running the shell script S-L-m.sh creates all the executables. 

The executable S-163-37 takes two command line input. The name of a file <fname> and the number <nbits> of keystream bits that is to be generated. The file <fname> should be a text file with exactly two lines. 
The first line should provide the 80-bit key as a 0-1 string, and the second line should provide the 80-bit IV also as a 0-1 string. The executable S-163-37 writes to the standard output <nbits> keystream bits as a 0-1 string. 
The keystream bits are produced from the key and IV in the file <fname> as a 0-1 string. An example of <fname> is provided as key-IV-80.txt. The values of key and IV in this file may be changed to any desired string, and 
then S-163-37 can be run on the file to obtain the corresponding keystream bits.

The operations of the other executables S-257-59, S-331-71, S-389-87, S-449-101, S-521-115 are similar to that of S-163-37. Examples of the corresponding key-IV files are provided as key-IV-128.txt, key-IV-160.txt, 
key-IV-192.txt, key-IV-224.txt, key-IV-256.txt.
