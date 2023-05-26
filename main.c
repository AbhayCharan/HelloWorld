#include <stdio.h>
#include <stdlib.h>

char LABEL[] = "Hello World!";

struct crypt_oper
{
	unsigned char *label;
	unsigned int len;
} __attribute__((__packed__));

static int crypto_operation(struct crypt_oper *co1, struct crypt_oper *co2)
{
	if (co1->label) {
		if (!co1->len) {
			printf("ERR: invalid label length.");
			return -1;
		}

		co2->len = co1->len;
		co2->label = (char*) malloc(co2->len);
		if(co2->label) {
            for(int i=0; i<co2->len; ++i)
                co2->label[i] = co1->label[i];
        }
	}
	
	return 0;
}

int main(void)
{
	struct crypt_oper oper1;
	struct crypt_oper oper2;
	
    oper1.label = (char*)&LABEL;
    oper1.len = sizeof(LABEL);
    
    printf("Hello World?\n");
    
    crypto_operation(&oper1, &oper2);

    for(int i=0; i<oper2.len; ++i)
        printf("\noper2.label[%d] == %c", i, oper2.label[i]);

    printf("\nsizeof(oper1) = %ld\n", sizeof(oper1));
    printf("\noper1.len     = %d\n", oper1.len);
    free(oper2.label);
    
    return 0;
}
