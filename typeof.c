#include <stdio.h>

struct a {
        int b;
        int c;
};

int main()
{

        typeof( ((struct a*)0)->b) result;

        result = 100;

        printf("%d\n", type);

        return 0;
}
