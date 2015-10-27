# CAN
This tutorial will cover what CAN is, how our ATmega's utilize CAN and how to use our CAN api to make your Nodes work with our CAN network.

This document will also serve as partial documentation of our CAN API, with more detailed documentation in the `CAN_2015-2016` repo.

### What is CAN?
Most simply CAN is a method of networking an arbitrary system with many different devices. It allows for any device to talk to any other device quickly, easily and most importantly, reliably. It can also do this using only two wires. 

[CAN is a way of life.](null "At this point you should consider turning away and learning CAN on your own. The goofiness will only increase 10x") Well, a way of life in terms of the embedded systems world. You see, CAN is not a program, software or programming language -- it is just a [protocol](null "Invented at Bosch in the 1980s, so it is relatively new in the grand scheme of things."). It says that there are two wires, CAN-Low and CAN-High, that span across many nodes -- called the CAN bus -- and when they have their voltages *pulled together* it counts as a 1, and when the voltages are *pulled apart* it is a 0. What the sequence of 1s and 0s say is also [specified in the protocol.](null "Thankfully, I don't know what we would do otherwise...") All of this [can](null "Hah! Get it? CAN?") be seen in the following diagram pulled shamelessly from Wikipedia:

![CAN-bus.png](https://raw.githubusercontent.com/OlinREVO/CAN_101/master/Tut_5/CAN-bus.png "Oh look at me, I can do images!")

So there you go, you technically know everything about CAN. It is a bunch of microcontrollers, or other devices, with two wires connecting to all of them that allow for mass data transfer throughout the entire system. [It is that simple.](null "I like things that are simple")

### CAN in Depth
Looking at the [diagram above](null "Seriously, it is the best diagram I have ever seen. I love it. I am going to print it out and marry it. Wait, what is going on?") you [might notice some interesting features.](null "Or you might not, I don't know your life") First things first, what the hell do the different sections mean? You can see the data field, a whopping 8 bits of data, but what the hell is the rest of that crap?

Well, let us venture into the [tabular world of tables.](null "This sentence doesn't make sense, but I had to have a transition.")

| Field | Meaning |
|:--- | :--- |
| Start of Frame | A bit of 0 to tell nodes to start listening, for the CAN line has something to say. [Interestingly](null "Actually this is pretty common, so not that interesting...") the 0 in the CAN bus means a data point, while the 1 is the default. So when no CAN message is going across the line, it is recognized as a bunch of 1s.|
| Arbitration Field | This field is a unique identifier for the message, and what that means is left up to the [user to decide.](null "Awwww, how sweet!") In most cases it says who the message is for (remember there can be a lot of nodes connected to the CAN bus) and what the priority is. How that is done varies, and we will go over that in a future section.|
| Control Field | This field specifies how long the data field will be. It is 4 bits and it says how many [bytes](null "byte = 8 bits") the Data field will be. |
| Data Field | This field holds all the data, whatever that may be. Once again, it is left up to [us to decide how to use it.](null "Kindof, although I will go over why we have no control later on")|
| CRC Field | Error checking field, ensures that the data is transmitted correctly.|
| End of Frame | The ending note for all CAN messages. 7 bits of 1.|

*Note: You can also find all of this on the Wikipedia article about the*[CAN bus (LINK)](https://en.wikipedia.org/wiki/CAN_bus "Click me! Click me!")* and it gives a more detailed overview!*
