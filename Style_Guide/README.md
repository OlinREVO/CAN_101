# Style Guide: How To Be Stylish
Much like the clothes you wear, the code you write says a lot about you. If you are dressed like a slob, with shirts that are too big for you and jeans that sag, you will be seen as a slob and generally [treated as such](null "It is a tough life for true slobs."). Much like that, if your code looks like shit, we won't include it in our codebase.

## Readable Code
The goal of all of this is to make code easily readable. We don't want to sift through lines of C in order to figure out what a function you wrote does. This will require two things -- consistency of style and comments. 

## Consistency of Style
There is a lot of contention about what good C code looks like, and there are a ton of different style guides out there. The Linux Kernel, for example, has some weird quirks to it's style --but everyone line of code follows it. Much like the Linux Kernel, our code-base will be unified and from an outsiders point of view will look like [one person wrote all of it](null "That one person will be me. I will get all the credit.").

#### 1. Variables
*1.1* There will be NO global definition of variables. This means defining variables outside of a function. Macro definitions will be allowed only if there is a REALLY good reason for it, otherwise use a constant variable. 

*1.2* All variable definitions will be at the beginning of a function, and will have a quick comment on what they do (if it is not overtly obvious).

For Example:

BAD:
```
int tmp;

int main( void ){
    tmp++;
    return tmp;
}
```

GOOD:
```
int main( void ){
    int tmp;
    return tmp;
}
```
#### 2. Functions
*2.1* Functions will be defined as either [int or void](null "This is not a hard and fast rule, if there is a VERY good reason to use a different function definition then do so."). There will be no other form of function definition. If you need to pass a value back out, do so with pointers in the input arguments.

GOOD:
```
int I_am_function( void ){
    // Stuff
}
```

BAD:
```
const char *I_am_function( void ){
    // Stuff
}
```
