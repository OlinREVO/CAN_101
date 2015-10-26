
#Blinky With Potentiometer Control
(Advanced Blinky)


## The Code
By now you probably think you are hot shit and that you can do anything. You can output 5V on a pin, and you know what? for some things that is enough.  Sadly, for literally everything else, you are going to need some inputs. 

#### Digital Input
The first, and easiest, input that you can do is just digital. 5V will be a 1, and 0V  will be a 0. Easy peezy.

#### Analog Input
The other option is to have a range of voltages, everything from 0V to 5V.  This will utilize the ADC (a built in analog-to-digital converter), but there are some tricks to this.

## We Live in a Digital World
Like seriously everything we own is digital… Also this part will not go through everything you need to make a [compilable file](https://github.com/OlinREVO/CAN_101/tree/master/Tut_4 "I will still put some source code at the end of something that can be compiled, but you should really be able to do it yourself!")

#### Set a Pin to Digital Input
This is actually really easy. Let’s use pin 10, or PE1. For digital output, we had to set the correct bit of DDRE to a 1. For input, we set it to 0, or, because they default to 0, we leave it as is. 

However, that is shitty code practice, and if you assume that the bit is set to 0 in your code I will find you and I will tell you that you did something [stupid](https://github.com/OlinREVO/CAN_101/tree/master/Tut_4 "You should feel bad"). Instead of assuming like an asshole programmer, you can set it nicely like so:

```
DDRE &= ~( _BV(PE1) );
```

This ANDs the bits of DDRE with the inverse of the bits set by PE1. “What?” you may ask. Essentially, `_BV(PE1)` will create 00000010 and the inverse of that (~) is going to be 11111101. ANDing that with whatever DDRE is will keep every bit of DDRE the same, except for the 2nd to last bit (the one we want for PE1) which it will force to 0. If you don’t understand that explanation go [play around with binary (LINK)](https://www.codecademy.com/courses/python-intermediate-en-KE1UJ/0/1 "Click the link to learn some binary (in python)!"). 

#### Read that Pin
Now comes the hard part. Actually, this is still really easy. To read the voltage at the input pin, we have to look at a new register. The Port E Input Pins Address (or PINE). If 5V is applied to pin 10 (PE1), then PINE will have a bit flipped to a 1 where PE1 is. 0V the bit will be a 0. So you just check to see if PINE is greater than 0.

If you believed that then you should [stop believing everything I say](https://www.codecademy.com/courses/python-intermediate-en-KE1UJ/0/1. Instead you will have to check to see if the correct bit of PINE is set to 1. "You might wonder why I would write a tutorial where I would lie, and there is really no good answer."). Instead, you should do:

```
if (PINE & _BV(PE1) ) {
	// Do stuff
}
```

If this doesn’t make sense, once again: play with binary.

## Analog Discovery? 
See how easy digital is? Analog stuff is just as easy. I lied again. It is a bit more complicated, and for good reason. Before jumping into code, let’s go through what the hell we have to do first.

#### Analog to Digital
Digital is easily defined by 0V or 5V, a 1 or a 0, on… and off. Easy stuff. Literally two things you have to remember. BI-nary. Analog is everything else. 0V to 5V inclusive in our case, because anything more and our [ATmegas will fry](NULL "You don't want that unless you are Powertrain from 2014-2015").

It is easy then to convert Analog to digital, we can just convert the volts into a number. 0V would be a 0, 0.000...0001V would be a 1, 0.000...0002V is a 2 and so on. 

In order to solve this [issue](NULL "Right? You see the issue? Please say you see the issue….") we have to subdivide the voltage range. Since we store things in the digital world in bytes, a simple subdivision is by 2<sup>8</sup> (256), because that is the amount 1 byte can hold. This gives us a rather large range, and for most of our purposes this should be fine. (Actually the ATmega we are using defaults to an ADC of 10 bits (for whatever reason), which is a bit (actually 2!) more than 1 byte). We’ll go over the side effects to that later.

So now we have subdivision down, what else?

#### Time. It is always Time. 
This issue isn’t actually analog specific. Digital stuff relies on time too. Actually, everything relies on time. 

As we learned before, our ATmega’s CPU runs at 1Mhz which is pretty darn fast. In order to use the ADC, we have to tell it at what time rate to sample the voltage on the pin in order to get a reading. I recommend reading the [wikipedia article (LINK)](https://en.wikipedia.org/wiki/Analog-to-digital_converter "Link to ADC wiki") to understand this because it is really solid.  

To do this, we use this line of code:

```
ADCSRA |= _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
```
[note](NULL "You can use | in between to combine the bits to be flipped. This is the fanciest combo-bit-shifting mumbo-jumbo that is allowed on one line. Anything more and I will hunt you down and make you turn it into multiple well-commented lines.")

We know by now what most of this code does, it sets different bits of the [ADCSRA register](NULL " It is time to pull up that handy-dandy reference manual."). ADEN will turn the ADC on, and ADPS[0-2] will tell the ADC how fast to run. Check the datasheet for [exact specifications](NULL "Ctrl-F is for cheaters.").

#### Who Do I Reference? Are You My Relative!?
No, I am not talking about when you write a research paper. This is for the ADC. Voltage is relative, [as is everything in life](NULL "Is this 3 d33p 5 u? Oh God, what have I become…"). The ADC will translate voltage into numbers. Where with digital inputs everything is reference to the ATmega’s ground, the ADC can be set to reference an external source. 

For now, we will just keep that idea in the back of our head, and set the ADC to just reference internal ground. 

```
ADCSRB |= _BV(AREFEN);
```

Starting to feel comfortable with the bit shifting stuff?

#### Are We Done Yet?
Actually, yes. Mostly.

Now we just have to read the ADC. This is actually fairly easy. First we tell the ADC to begin conversion:

```
ADCSRA |= _BV(ADSC);  
```

If you look through the datasheet under the ADCSRA register section, it says that you set the ADSC bit when you want a conversion, and then the bit will be automatically reset (set to 0) when the conversion is complete. Since the ADC is not instantaneous, let’s wait for it.

```
while(bit_is_set(ADCSRA, ADSC));
```

As you can probably tell, bit_is_set() will check to see if the bit… is… set? Yes. We could also just do some binary logic with &s and whatnot, but this function makes the code more [readable](NULL " We want readable code.").  Then we just read the ADC when this while loop exits:

```
uint16_t reading = ADC;
```

We have to use a 16 bit integer to hold the ADC value, because a 8 bit integer type can’t hold it (remember the ADC we have will by default output 10 bits). 

(Ideally `uint16_t reading` is declared beforehand, although the [compiler will optimize this out and it is more readable](NULL "Well shit… More readable code is more shitty looking? Sometimes that is the case, but learn your compilers! Don’t code shittily and expect your compiler to make it optimized.")

And that is it, we now have a reading of the voltage!

## Digital To Analog. Wait, what?
Analog to digital now makes sense, but there is no possible way you can go from digital to analog. That just doesn’t make any sense. Well you are right. In a sense. 

Once again, it boils down to:
#### [Time.](NULL "<3 Time. And Thyme. I do enjoy Thyme. But my favorite spice is ginger. Or is it cinnamon? Actual I do like mint…")
1s and 0s. That is what you have to work with. C’mon, you’re in ISIM for [~~God’s~~](NULL "Not sure if this offends people...") sake! You are a genius at this. Oh now wait, all you know is filters. And op-amps. ~~Goddamn~~ [op-amps…](NULL "This was the case in my year, not sure if this is still true. I hate filters.")

Wait a second, filters are cool, they can take a really spiky signal and smooth it out. You can get rid of high frequency noise and just get the signal you want! What if we use that high frequency noise to MAKE the signal?

This is the [idea](NULL "Not really, but essentially") behind Pulse Width Modulation (PWM). You pulse a bunch of 1s (5V) and 0s (0V) at the digital port such that the “average” is the voltage you want. It is slightly more complicated in practice,~~and I recommend you google it if you want to know more.~~ Actually, definitely check the [wiki article (LINK)](https://en.wikipedia.org/wiki/Pulse-width_modulation "I supply the link. You read.")

#### Yeah the ATmega Can Do it.
These things are pretty neat. Can your computer do PWM? Well, probably. Whatever. 

First we have to set the prescaling on the PWM clock. This is fancy mumbo-jumbo for how fast we want the PWM frequency to be.  For right now, we want it to be [as fast as possible](NULL "Pull up that documentation!"):

```
TCCR0B |= _BV(CS00);
```

Now we just have to say what pin we want to use as the PWM. Not every pin can do PWMing, so you will have to check the datasheet for specifications. Our lovely pin 10 *can* do PWM, so let’s just use that one! However, since we are using it’s PWM functionality we have to call it by it’s other name: [COM0B1](NULL "For readability!")

```
TCCR0A |= _BV(COM0B1) | _BV(WGM00);
```

Setting the WGM00 bit, which determines the “mode” of operation. Check the datasheet for more information, but this will set it to be phase-correct PWM.

It also appears to be good practice to reset the other PWM pin for this register, although [I am not totally sure why](NULL "I am still learning this as well!"). We can do that with:

```
TCCR0A &= ~_BV(COM0B0);
```

You know what this does by now! Lastly, we still need to tell PE1/pin 10/COMOB1 to be output. For this, we will once again use the familiar [PE1](NULL "For readability? No. For standards.").

```
DDRE |= _BV(PE1);
```

#### Now Just Write To The Pin
You can do this! Well, it is a bit different now.

```
OCR0B = (uint8_t) (reading >> 2);
```

The OCR0B register is only 8 bits, so we need to cast our 16 bit reading as 8 bits. We bit shift right by 2 to keep the most significant bits [(we are using 16 bits to store a 10 bit number)](NULL "This starts to get a bit tricky. We have a 10 bit number stored in a 16 bit box. We want to put that into an 8 bit box. So we can get rid of the least significant bits --the last two that store a 1 and a 2-- which will make our reading off by +3 or -3, but it will allow us to put 10 bits into 8!").  

See? [Easy](NULL "Right? RIGHT?!").

## Putting It All Together
You have a lot more functionality now, and in fact basically all the functionality the ATmega can do. Digital input, output and analog input and output. What more is there? Well, there are a few more built in features that utilize these two features to build up other features that we can use, but we will get to that later. For now, be glad you can do stuff. 

You can find some examples in the examples/ folder for this tutorial. Check them out, modify them, break them, live life!

