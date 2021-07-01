/* This Program is the main entry point
 * in order to call insertion_sort
 */

#include <insertion_sort.cpp>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char const *argv[])
{

    /**
     * YOUR CODE HERE
     * 1. Check for the number of arguments.
     * Only proceed if the number of argument is correct,
     * We will only check for ./main [INPUT_FILE] [OUTPUT_FILE]
     * 
     */
    if(argc != 3)
    {
        printf("Number of Arugments Incorrect\n");
        return 0;
    }
    fstream myfile;
    myfile.open(argv[1]);
    string line1_str;
    string line2_str;
    getline(myfile,line1_str);
    getline(myfile,line2_str);
    int line1 = atoi(line1_str.c_str());
    int temp;
    int* line2 = (int *) malloc(sizeof(int)*strlen(line2_str.c_str()));
    int p = 0;
    char* str = (char *) malloc(sizeof(char)*strlen(line2_str.c_str()));
    strcpy(str,line2_str.c_str());
    char* temp_str =(char*) malloc(sizeof(char)*8);
    while (p<line1)
    {
        int rc = sscanf(str,"%d",&temp);
        if (rc!=1) 
        {
            break;
        }
        else
        {
            line2[p]= temp;
        }
        sprintf(temp_str, "%d",temp);
        int len = strlen(temp_str);
        p++;
        str+=(len+1);
    }
    myfile.close();
    /**
     * YOUR CODE HERE
     * 3. Build IntSequence
     */
    IntSequence A;
    A.length = line1;
    A.array = line2;

    insertion_sort(A);

    /**
     * YOUR CODE HERE
     * 5. Write the file into [OUTPUT_FILE]
     */
    ofstream output_file;
    int k = 0;
    char** output_str = (char**) malloc(sizeof(char*)*line1);
    output_file.open(argv[2]);
    while (k<line1)
    {
        int temp_int = A.array[k];
        output_str[k] = (char*) malloc(sizeof(char)*8);
        int rc = sprintf(output_str[k], "%d",temp_int);
        output_file<<output_str[k];
        output_file<<" ";
        k++;
    }
    output_file.close();
    free(line2);
    free(temp_str);
    free(output_str);
    return 0;
}
