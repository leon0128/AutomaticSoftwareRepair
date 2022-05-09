int getValue(int * pointer)
{
    
    if(pointer == (int *)0)
        
        return 0;
    else
        ;
    
    return * pointer;
}

int main(int argc, char * * argv)
{
    int value;
    value = 10;
    
    if(getValue(& value) != 10)
        
        return 1;
    else
        ;
    getValue((int *)0);
    
    return 0;
}