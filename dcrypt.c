#include <stdio.h>
#include <gcrypt.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include <termios.h>
#include <string.h>

#define VERSION "0.1"

static void
usage(const char *myname, FILE *out)
{
    fputs("\n", out);
    fputs("Usage:\n", out);
    fprintf(out, " %s [Options] file.ext\n", myname);
    fputs("\n", out);
    fputs("Options:\n", out);
	fputs(" -e, --encrypt encrypt a file\n", out);
	fputs(" -d, --decrypt decrypt a file\n", out);
	fputs(" -v, --version print version information\n", out);
	fputs(" -h, --help print help information\n", out);
    fputs("\n", out);
    exit(out == stderr ? EXIT_FAILURE : EXIT_SUCCESS);
}

int main(int argc, char** argv)
{

 	/* check parameters */
	if (argc - optind == 0) {
        fprintf(stderr, "%s: no arguments provided %d, expected >=%d\n", argv[0], argc - optind, 1);
        usage(argv[0], stderr);
    }
	
	/* file privided */
	 if (argc < 3)
    {
		fprintf(stderr, "%s: no input file provided\n", argv[0]);
		usage(argv[0], stderr);
    }
	
	/* does file exist */
	FILE *file;
	if (file = fopen(argv[2], "r")) {
		fclose(file);
		printf("-> File %s accepted\n", argv[2]);
	} else {
		fprintf(stderr, "%s: file %s does not exist \n", argv[0], argv[2]);
		usage(argv[0], stderr);
	}

	/* parse parameters */
	static const struct option longopts[] = {
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
		{"encrypt", no_argument, NULL, 'e'},
		{"decrypt", no_argument, NULL, 'd'},
        {NULL, 0, NULL, 0}
    };
	static int cmd = 0; static char mymode = 0;
    while ((cmd = getopt_long(argc, argv, "hved", longopts, NULL)) != -1) {
        switch (cmd) {
            case 'h':
                usage(argv[0], stdout);
            case 'v':
                puts(VERSION);
                return EXIT_SUCCESS;
            case 'e':
                printf("-> Running in encryption mode\n");
				mymode = 1;
				break;
            case 'd':
                printf("-> Running in decryption mode\n");
				mymode = 2;
				break;
            default:
                usage(argv[0], stderr);
        }
    }

    /* get encryption key */
    struct termios oflags, nflags;
    char s[64];

    /* disabling echo */
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
        perror("tcsetattr");
        return EXIT_FAILURE;
    }

    printf("-> Enter encryption key: ");
    fgets(s, sizeof(s), stdin);
    s[strlen(s) - 1] = 0;
    /* printf("entered '%s'\n", s); */

    char d[64];
    printf("-> Confirm encryption key: ");
    fgets(d, sizeof(d), stdin);
    d[strlen(d) - 1] = 0;
    /* printf("entered '%s'\n", d); */

    /* restore terminal */
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
        perror("tcsetattr");
        return EXIT_FAILURE;
    }
    
    if ( strcmp(s, d) != 0 ) {
	printf("-> Encryption key did not match!\n");
	return EXIT_FAILURE;
    }

    /* gcrypt init */
    unsigned char *x;
    unsigned i;
    unsigned int l = gcry_md_get_algo_dlen(GCRY_MD_SHA256);

    gcry_md_hd_t h;
    gcry_md_open(&h, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE);
    gcry_md_write(h, s, strlen(s));
    x = gcry_md_read(h, GCRY_MD_SHA256);

    /* Print SHA256
    for (i = 0; i < l; i++) { printf("%02x", x[i]); }
    printf("\n");
    */

    /* Encrypt file */
    char iniVector[16];
    char *encBuffer = NULL;
    FILE *fp, *fpout;
    char *key = s;
    gcry_cipher_hd_t hd;
    int bufSize = 16, bytes, algo = GCRY_CIPHER_AES128, keyLength = 16, blkLength = 16;

    memset(iniVector, 0, 16);
    encBuffer = malloc(bufSize);

    if ( mymode == 1 ) {
		
    char outfile[200] = "encrypted-";
    strcat(outfile,argv[2]);
    if( access(outfile, F_OK ) != -1 ) { remove(outfile); }

    fp = fopen(argv[2], "r");
    fpout = fopen(outfile, "w");
    printf("-> Encrypting %s to %s\n", argv[2], outfile);

    gcry_cipher_open(&hd, algo, GCRY_CIPHER_MODE_CBC, 0);
    gcry_cipher_setkey(hd, key, keyLength);
    gcry_cipher_setiv(hd, iniVector, blkLength);

    while(!feof(fp))
    {
        bytes = fread(encBuffer, 1, bufSize, fp);
        if (!bytes) break;
        while(bytes < bufSize)
            encBuffer[bytes++] = 0x0;
        gcry_cipher_encrypt(hd, encBuffer, bufSize, NULL, 0);
        bytes = fwrite(encBuffer, 1, bufSize, fpout);
    }
    gcry_cipher_close(hd);
    fclose(fp);
    fclose(fpout);
    }

   /* Decrypt file */
   if ( mymode == 2 ) {
   char outfile[200] = "decrypted-";
   strcat(outfile,argv[2]);
	
    gcry_cipher_open(&hd, algo, GCRY_CIPHER_MODE_CBC, 0);
    gcry_cipher_setkey(hd, key, keyLength);
    gcry_cipher_setiv(hd, iniVector, blkLength);

    if( access( outfile, F_OK ) != -1 ) { remove(outfile); }
    fp = fopen(argv[2], "r");
    fpout = fopen(outfile, "w");
    printf("-> Decrypting %s to %s \n", argv[2], outfile);

    while(!feof(fp))
    {
        bytes = fread(encBuffer, 1, bufSize, fp);
        if (!bytes) break;
        gcry_cipher_decrypt(hd, encBuffer, bufSize, NULL, 0);
        bytes = fwrite(encBuffer, 1, bufSize, fpout);
    }
    gcry_cipher_close(hd);

    free(encBuffer); encBuffer = NULL;
   }
   
   printf("-> Completed\n");
   return 0;
}
