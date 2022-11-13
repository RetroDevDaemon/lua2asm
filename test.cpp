#include <mpc.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

using namespace std;

ifstream inFile;
char* fileContents;


static mpc_val_t *print_token(mpc_val_t *x) 
{
    printf("Token: '%s'\n", (char*)x);
    return x;
}


int main(int argn, char* argv[])
{

    // open lua file 
    inFile.open(argv[1]);
    // error handling
    if(!inFile)
    {
        cerr << "cant open file\n";
        exit(1);
    }
    
    // get path and size
    filesystem::path p{argv[1]};
    cout << filesystem::file_size(p) << " bytes\n";
    
    //alocate and read in data 
    fileContents = (char*)malloc(sizeof(char)*filesystem::file_size(p));
    int inputLen = sizeof(char)*filesystem::file_size(p);
    inFile.read(fileContents, inputLen);

    inFile.close();
    
    // replace ; with \n 
    for(int i = 0; i < inputLen; i++)
    {
        if(fileContents[i] == ';')
            fileContents[i] = '\n';
    }
    // remove all comments
    for(int i = 0; i < inputLen; i++)
    {
        if(fileContents[i] == '-')
            if(fileContents[i+1] == '-')
            {   // --?
                fileContents[i] = ' ';
                fileContents[i+1] = ' ';
                i += 2;
                while(fileContents[i] != '\n' && (i < inputLen))
                {
                    fileContents[i] = ' ';
                    i ++;
                }
            }
    }
    
    mpc_parser_t* Tokens = mpc_many(
        mpcf_all_free,
        mpc_apply(
            mpc_strip(
                mpc_re("\\s*([0-9]+|[a-zA-Z_]+|[(){}-=+*\\[\\].,/&%$#!<>~^]+|['\"]+)")
                //mpc_re("\\s*([a-zA-Z_]+|[0-9]+|,|\\.|:)")
            ), 
        print_token)
    );

    mpc_result_t r;
    mpc_parse("input", fileContents, Tokens, &r);

    // bracket parsing:
    /// first { after function, delete it 
    /// first { after "for" replace with "do"
    /// every } replace with "end"
    // give a warning if a { does not match a }

    mpc_delete(Tokens);
    free(fileContents);

    return 0;
}
