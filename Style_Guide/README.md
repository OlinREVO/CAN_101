# Style Guide: How To Be Stylish
Much like the clothes you wear, the code you write says a lot about you. If you are dressed like a slob, with shirts that are too big for you and jeans that sag, you will be seen as a slob and generally [treated as such](null "It is a tough life for true slobs."). Much like that, if your code looks like shit, we won't include it in our codebase.

## Readable Code
The goal of all of this is to make code easily readable. We don't want to sift through lines of C in order to figure out what a function you wrote does. This will require two things -- consistency of style and comments. 

## Consistency of Style
There is a lot of contention about what good C code looks like, and there are a ton of different style guides out there. The Linux Kernel, for example, has some weird quirks to it's style --but everyone line of code follows it. Much like the Linux Kernel, our code-base will be unified and from an outsiders point of view will look like [one person wrote all of it](null "That one person will be me. I will get all the credit.").

#### 1. Variables
##### *1.1* There will be NO global definition of variables.
This means defining variables outside of a function. Macro definitions will be allowed only if there is a REALLY good reason for it, otherwise use a constant variable. 

##### *1.2* All variable definitions will be at the beginning of a function.
Remember to include a quick comment on what they are for (if it is not overtly obvious).

##### *1.3* Pointers will be named with a lowercase "p" in front, such as pTmp.
No other variable should have a lowercase "p" and then an uppercase letter, which will allow pointers to be easily distinguishable.

##### *1.4* Variables will be named with seudo camelCase.
The first letter will be lowercase, and every "word" will be capitalized. 

#### 2. Functions
##### *2.1* Functions will be defined as either [int or void](null "This is not a hard and fast rule, if there is a VERY good reason to use a different function definition then do so.").

##### *2.2* Functions will return 0 for success, or -1 for error
If you need to pass a value out, use a pointer in the input arguments. 

##### *2.3* Error check all functions
Any time you call a function, ensure that it has not returned an error. If it has, deal with it [appropriately](null "If that means taking off all your clothes and rolling around in mud then do so.")

##### *2.4* Functions will be named_with_underscores
This will help differntiate functions from variables. Do NOT use capital letters in function names, unless it is necessary.

##### *2.5* Functions will 

#### 3. Brackets
##### *3.1* Brackets will start on the same line and end on a separate line.
This is possibly the most contested C-style thing in the book. A starting bracket for a function, for loop, if statement, etc. will be on that same line like so:
```
while(1){
```

It will end on a new line. [There will be no arguing about this](null "There are good arguments to be made, but since I am writing the style guide I get to force it to be in my style.").

#### 4. Spacing
##### *4.1* 4 spaces per every indent.
[Do not use tab characters](null "I will hunt you down and for every tab character you write I will make you write 4 spaces instead.").


## Commenting: Be Good At It
If you write bad comments, you are [literally the worst person](null "Literally. As in, figuratively literally."). What is a good comment you ask?

#### It is Descriptive

#### It says "why" and not "how"
```
DDRE |= _BV(PE1) // Set pin 10 (PE1) as output
```

The comment above is totally useless. I can look that up in the datasheet. *WHY* is pin 10 being set as an output?

```
// Set pin 10 (PE1) as output
// Using pin 10 to drive an LED to blink
DDRE |= _BV(PE1)
```

Is much more descriptive and is actually useful. 

