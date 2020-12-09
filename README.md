# dcrypt
Console Application for Encrypting and Decrypting Files using Libgcrypt

<pre>
Manual Build:
apt install build-essential libgcrypt20-dev libgpg-error-dev;
gcc dcrypt.c -o dcrypt -lgcrypt -lgpg-error;

Makefile Build:
make && make install;

Static Build:
make static && make install;

Uninstal dcrypt:
make uninstall;

Debian Package installation:
wget "https://github.com/deobox/dcrypt/raw/main/bin-amd64/dcrypt_0.1-1.deb";
dpkg -i dcrypt_0.1-1.deb;

Debian Package uninstallation:
apt remove dcrypt;

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
