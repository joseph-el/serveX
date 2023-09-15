# include <iostream>

void error()
{
    puts("error");
    throw false;
}

void call () {

    puts("hlll");
    error();
    puts("alex");
}


int main ()
{
    try {
    call();

    }
    catch (bool)
        {
            puts("exp true");
        }

}