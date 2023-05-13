#include <math.h> 
#include <stdio.h>



unsigned long rsa(unsigned long seed, int key, int mod)
{
    unsigned long c = (unsigned long)pow(seed, key);
    c = c % mod;
    return c;
}



// int main()
// {
//     double a = 3;
//     double b = 5;
//     int public[] = {5, 14};
//     int private[] = {11, 14};

//     int val = rsa(13, public[0], public[1]);
//     printf("Encrypted value: %d\n", val);

//     val = rsa(val, private[0], private[1]);
//     printf("Decrypted value: %d\n", val);

//     return 0;
// }