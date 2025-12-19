# compile the file ref-impl.c with different options to obtain the different instantiations of S(L,m)
gcc -DKAPPA80 -o S-163-37 ref-impl.c
gcc -DKAPPA128 -o S-257-59 ref-impl.c
gcc -DKAPPA160 -o S-331-71 ref-impl.c
gcc -DKAPPA192 -o S-389-87 ref-impl.c
gcc -DKAPPA224 -o S-449-101 ref-impl.c
gcc -DKAPPA256 -o S-521-115 ref-impl.c
