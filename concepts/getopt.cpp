# include <iostream>
# include <cstdlib>
# include <cstdio>
# include <getopt.h>
using namespace std;

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <getopt.h>

#include <unistd.h>

int main(int argc, char *argv[])
{


    // char *ptr = NULL;
    // string ret = ptr;

    int  c = 32;

    if (c & ('e' | 'c'))
        cout << "yes\n";

    return 1;
    int option = -1;
    char *addr = NULL, *port = NULL;
    opterr = 0;
    while ((option = getopt (argc, argv, "c:e:")) != -1)
    {
         switch (option)
         {

            case 'h':
                cout << "check A : " << endl;
            //  addr = strdup(optarg);
             break;

            case 'v':
                cout << "check n" << endl;
            //  addr = strdup(optarg);
             break;

         case 'e':
            cout << "check opt : " << optarg << endl;
            //  addr = strdup(optarg);
             break;
         case 'c':
             port = strdup(optarg);
             break;
        case '?':
            cout << "error \n";
         default:
              /* unrecognised option ... add your error condition */
              break;
         }
    }

        if (addr)
            cout << addr << endl;
        else if (port)
            cout << port << endl;
        else
            cout << "non\n";
    /* rest of program */

    return 0;
}