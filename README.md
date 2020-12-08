# dcrypt
Console Application for Encrypting and Decrypting Files using Libgcrypt

<pre>
Manual Build:
apt install build-essential libgcrypt20-dev
gcc dcrypt.c -o dcrypt -lgcrypt -lgpg-error

Makefile Build:
make

Note: Makefile will build both dynamic and static executables.

Usage:
 ./dcrypt [Options] file.ext
 
Options:
 -e, --encrypt encrypt a file
 -d, --decrypt decrypt a file
 -v, --version print version information
 -h, --help print this information

Examples:
 Encrypt a file: 
$ dcrypt -e test.txt
-> File test.txt accepted
-> Running in encryption mode
-> Enter encryption key:
-> Encrypting test.txt to encrypted-test.txt
-> Completed

 Decrypt a file: 
$ dcrypt -d encrypted-test.txt
-> File encrypted-test.txt accepted
-> Running in decryption mode
-> Enter encryption key:
-> Decrypting encrypted-test.txt to decrypted-encrypted-test.txt
-> Completed

 Binaries:
 <a href='https://github.com/deobox/dcrypt/tree/main/bin-amd64' target='_blank'>https://github.com/deobox/dcrypt/tree/main/bin-amd64</a>
</pre> 
