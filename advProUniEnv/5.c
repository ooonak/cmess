#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 1024

void hansolo()
{
        

}

/* Create temporary file */
int tmp_file()
{
        FILE *fp;
        /* Create temporary file that is automatically deleted on exist */
        fp = tmpfile();

        return 0;
}

/* Create memory stream for 'string builder' */
int mem_stream()
{
        FILE *fp;
        char buf[SIZE];

        /* Open memory stream backed by buf as file */
        fp = fmemopen(buf, SIZE, "w+");
        if (fp == NULL)
                puts("fmemopen error");

        /* Now we can use fprintf as string builder */
        int i = 10;
        fprintf(fp, "Here you can buid the string you like.\
                        Just include any %d numbers.\n", i);

        /* Remember to flush before printing */
        fflush(fp);

        printf("%s", buf);

        /* Concatenation example */
        memset(buf, '\0', SIZE);
        fseek(fp, 0, SEEK_SET);
        fprintf(fp, "First_\n");
        fprintf(fp, "Second_\n");
        fprintf(fp, "Third_\n");
        fflush(fp);

        printf("%s", buf);


        /* Same could be done this way */

        return 0;
}

int main()
{
        mem_stream();

        tmp_file();

        return 0;
}
