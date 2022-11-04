#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
int my_printf(char* main_str, ... );
int decimal_order(int x);//returns the order/or 100th or 1000th
int decimal_length(int x);//returns number of characters in a number
void write_decimal(int inp_int, int* tot_char);//takes as an arugment an integer, and pointer to an integer,
// writes it in string form, tot_char pointer counts the number of characters printed and add up to existing tot_char int
int get_octal_length(int x);//returns numberlength of octal of particular integer number;
int my_strlen(char* str1);//return number of characters of particular string;
void write_octal(int a, int* tot_char);//writes integer in octal, and adds up/increments tot_char by each character printed
void write_hexadecimal(int x, int* tot_char);//writes integer in hexadecimal
void write_hexadecimal_long(uintptr_t x, int* tot_char);//writes integer in hexadecimal/and adds up/increments tot_char by each character printed
void write_ptr_part(int* tot_char);//writes 0x/and adds up/increments tot_char by each character printed in this case 2;
int get_long_hex_length(uintptr_t x);//returns number of int required for string which contatins hex value of x int;


int main(){



   return 0;
}


/*
printf analog which has %d %u %o %x %o specifiers for ints
%p for void* pointers
%c for characters
%s for strings
*/
int my_printf(char* main_str, ... ) {
    int i = 0;
    va_list args;
    va_start(args, main_str);
    int* total = (int*)malloc(sizeof(int));
    *total = 0;
    //(*total)++;
    

/*checks and writes(if no % is encountered) the first argument of the function one character by one
*/
    for(i=0; main_str[i] != '\0'; i++){
      int* temp = malloc(sizeof(int) * 1);
      /*if it encounters % -> specifier it checks the next     character*/
        if(main_str[i] == '%'){
            switch (main_str[i+1]){

//when the argument is character
            case 'c':  ;
            char p = va_arg(args, int);
            *temp = write(1, &p, 1);
            (*total)++;
            i++;
            break;

//when the argument is string
            case 's': ;
            char* str_p = va_arg(args, char*);
              while(*str_p!='\0'){
                *temp = write(1,str_p,1);
                (*total)++;
                str_p++;
            };
            i++;
            break;
//when the argument/int that should be printed  decimal
            case 'u': ;
            case 'd': ;
            int inp_int = va_arg(args, int);
            write_decimal(inp_int, total);
            i++;
            break;
            
            
//when the argument/int that should be printed  octal
            case 'o': ;
            int inp_oct = va_arg(args, int);
            write_octal(inp_oct, total);
            i++;
            break;

//when the argument/int that should be printed in hexadecimal
            case 'x': ;
            int inp_hex = va_arg(args, int);
            write_hexadecimal(inp_hex, total);
            i++;
            break;

//when the argument is a void pointer
            case 'p': ;
            void *ptr = va_arg(args, void*);
            write_ptr_part(total);
            uintptr_t a = (uintptr_t)ptr;
            write_hexadecimal_long(a, total);
            i++;
            break;

//other options will be omitted, and printed as it is
            default: ;
            char error_str[] = "\nPlease write my_printf function with correct/right specifiers!\n";
            for(i = 0; error_str[i] != '\0'; i++){
                write(1, &error_str[i], 1);
            };
            free(temp);
            free(total);
            return 0;
            }
//other options will be omitted, and printed as it is
        } else {
            *temp = write(1, &main_str[i], 1);
            (*total)++;
          
        }

      free(temp);
    }
    int a = *total;
    free(total);

    return a;
} //my_printf ends


//returns the decimal length, 10-> 2, 100->3 , 1333->4
int decimal_length(int x){
    int i = x;
    int length = 1;
    while(i>=10){
    i/=10;
    length*=10;
    }
    return length;
}
//returns the decimal's order?
//12->10, 22220->10000, 300->100 
int decimal_order(int x){
    int i = x;
    int order = 1;
    while(i>=10){
    i/=10;
    order++;
    }
    return order;
}

//writes the given inp_int to stdoout using write function
void write_decimal(int inp_int, int* tot_char){
int* temp = malloc(sizeof(int));

  //check if the integer argument is positive
if(inp_int>=0)                 
{

    int order = decimal_order(inp_int);
    int length = decimal_length(inp_int);
    int single_int = 0;
    char char_print;
    /*
until the order reaches 0 it will continuously divides a particular number by
highest order, and decresing the number by 10(1222 -> reduced to 222, 23465->reduced to 3465).. when reducing takes the first number/largest and prints it out. the step continues until number is 0 or negative.
*/    
while(order>0){
        single_int = inp_int/length;
        char_print = single_int + '0';
        *temp = write(1, &char_print,1);
        (*tot_char)++;
        inp_int%=length;
        order--;
        length/=10;
    }
  //in case with negative
/*
same principle with positive number, but first it will print '-'
*/
  
} else {
    char c = '-';
    *temp = write(1,&c,1);
    inp_int*=-1;
    int order = decimal_order(inp_int);
    int length = decimal_length(inp_int);
    int single_int = 0;
    char char_print;
    while(order>0){
        single_int = inp_int/length;
        char_print = single_int + '0';
        *temp = write(1, &char_print,1);
        (*tot_char)++;
        inp_int%=length;
        order--;
        length/=10;
    }
    }
  free(temp);
}

//returns the length of octal number
//int x->octal number->returns the length of octal number
int get_octal_length(int x){
    int a = 0;
    if (x==0){
        return 2;
    };
    while(x>0){
        x /= 8;
        a++;
    };
    return (1+a);
};

//transforms the int a to octal and writes the octal to stdout
void write_octal(int a, int* tot_char){
    char octal_list[] = "01234567";
    int oct_len = get_octal_length(a);
    char* octal_rev = (char*)malloc(sizeof(char)*oct_len);
    int* temp = malloc(sizeof(int));
    int i = 0;
    if (a == 0){
        octal_rev[0] = '0';
        octal_rev[1] = '\0';
    } else {
       
        while(a>0){
            octal_rev[i] = octal_list[a%8];
            a/=8;
            i++;
        }
        octal_rev[i] = '\0';
    };
        
   

    for(i=oct_len-2; i>=0; i--){
        *temp = write(1, octal_rev+i, 1);
        (*tot_char)++;
    };
    free(octal_rev);
    free(temp);
};

//retunrs the length of hex <-int x is switched to hex then //returns the length of it
int get_hex_length(int x){
    int a = 0;
    if (x==0){
        return 2;
    };
    while(x>0){
        x /= 16;
        a++;
    };
    return (1+a);
}
/*
retunrs the length of hex <-uinptr_t x is switched to hex then,returns the length of it(used for addresses)
*/
int get_long_hex_length(uintptr_t x){
    int a = 0;
    if (x==0){
        return 2;
    };
    while(x>0){
        x /= 16;
        a++;
    };
    return (1+a);
}

//writes a hexadecimal form of given int a
void write_hexadecimal(int a, int* tot_char){
    int hex_length = get_long_hex_length(a);
    char* hexadecimal = (char*)malloc(sizeof(char)*hex_length);
    char hex_list[] = "0123456789abcdef";
    int i = 0;
    int* temp = malloc(sizeof(int));  
    if(a==0){
        hexadecimal[0] = '0';
        hexadecimal[1] = '\0';
    } else {
        while(a>0){
            hexadecimal[i] = hex_list[a%16];
            a/=16;
            i++;
        }
        hexadecimal[i] = '\0';
    };
    for(i=hex_length-2; i>=0;i--){
        *temp = write(1, hexadecimal+i, 1);
        (*tot_char)++;
    }
    free(hexadecimal);
    free(temp);
}

/*
writes an address of a particular pointer/void* in our case
in hexadecmal form
given the uintptr_a form of an address(not hexadecimal)
*/
void write_hexadecimal_long(uintptr_t a, int* tot_char){
    int hex_length = get_long_hex_length(a);
    char* hexadecimal = (char*)malloc(sizeof(char)*hex_length);
    char hex_list[] = "0123456789abcdef";
    int i = 0;
    int* temp = malloc(sizeof(int));  
    if(a==0){
        hexadecimal[0] = '0';
        hexadecimal[1] = '\0';
    } else {
        while(a>0){
            hexadecimal[i] = hex_list[a%16];
            a/=16;
            i++;
        }
        hexadecimal[i] = '\0';
    };
    for(i=hex_length-2; i>=0;i--){
        *temp = write(1, hexadecimal+i, 1);
        (*tot_char)++;
    }
    free(hexadecimal);
    free(temp);
}


//returns the length of str1
int my_strlen(char* str1){
    int i = 0;
    while(str1[i] != '\0'){
        i++;
    }
    return i;
}

//writes the "0x" on stdout
void write_ptr_part(int* tot_char){
    int i = 0;
    int *temp = malloc(sizeof(int));  
  char ox[] = "0x";
    for(i=0;i<2;i++){
        *temp = write(1, ox+i, 1);
        (*tot_char)++;
    };
  free(temp);
}

