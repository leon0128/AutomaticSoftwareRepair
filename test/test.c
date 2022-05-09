int getValue(int *pointer)
{
    return *pointer;
}

int main(int argc, char **argv)
{
    int value;

    value = 10;
    if(getValue(&value) != 10)
        return 1;
    
    getValue((int*)0);

    return 0;
}