# Learn Git
If you are really interested in learning how to use Git with Github, then don't read this tutorial and instead follow [this tutorial (LINK)](https://git-scm.com/book/en/v2/Getting-Started-About-Version-Control "It is awesomely in depth and will teach you to be the git-master of all project teams.")

Otherwise, if you want to have a brief overview of how to use git (and more importantly how WE are using git for this project) then this tutorial thing should be good enough.

## Don't Push to Master
This is the first and most important rule. Never, ever push to master. There is no reason to EVER push to master, and if you do it [I will be pissed.](null "This may result in you being banned temporarily or some other punishment. Or I might just give you a sad, dissapointed look.") 

> Your recent pull-request doesn't actually work, but you have a quick fix for it and you just need to quickly push to master...

NO! Bad! Make another pull-request. Don't push to master.

If I haven't stressed this enough -- Do. Not. Push. To. Master. Ever.

#### What the hell do you mean?
So my rant about pushing to master might not make any sense if you don't have any idea what a branch is. [And that is okay!](null "Just don't push to master") [I am just conditioning you,](null "To not push to master") which I think is totally fine. 

## Git in a nutshell
Git is a distributed version control system (DVCS), which means that there is not *really* a [central hub for the code.](null "People might say that extensions to git adding large file storage change this idea -- which is sorta true. But True git is stateless") Put simply, if you `clone` a repository you now have all of the code in that repository AND all the history. A `git clone` command copies all of the data on the server and puts it on your computer.

This is awesome because if the server code gets deleted, you have it. And if your computer code gets deleted, the server has [most of it.](null "The server will not hold onto local branches, which I will go into soon")

#### Branches
Everyone having the same code and history is great because losing data is [going to be difficult](null "Especially if you back up your data. Right? You do that regularly, right?"). The issue is when say Person A makes changes to File C and Person B also makes changes to File C. Both people `push` to the server (which tells the server to update its code to match yours) at [the same time](null "This isn't exactly how merge conflicts work, as whoever uploads first sets the standard on the server and then the other person is screwed over. We'll go into that later"). 

Now git is pretty cool -- if Person A and Person B made changes to different sections of File C, git doesn't complain and seamlessly merges the two changed files into one super-changed file. All is well. However, if Person A and Person B made changes to the same section (such as to the same function) then git won't know what to do, and will rightly complain about a merge conflict. We will go over how those are resolved later, but for now we will learn a method of preventing merge conflicts from ever happening.

The easiest, and best, way to prevent merge conflicts from happening is to use the beautiful `branch` command. 

```
git branch Fix_For_File_C
```

This command will copy the current "branch" of the project you are in when you call it and name it Fix_For_File_C. You can then switch to this new branch using the `git checkout Fix_For_File_C` [command](null "For pro users you can do both commands in one by just doing `git checkout -b Fix_For_File_C`")

Now you have your own (local) branch, where you can make any changes you want and you don't have to worry about anyone changing code that you are changing. Local branches are nice because nobody can mess with it; the downside is that no one else can see it, so if your [computer goes down then all your code is gone.](null "This is why we make backups.") The other downside of nobody being able to see it is that nobody can build off of it, which sorta defeats the purpose of [jointly working on code.](null "I prefer Open Source projects where the code is freely available to anyone who is using my computer on my account with my passwords.")

Local branches, and branches in general, have a very explicit purpose. They are there to temporarily hold changes until they are [merged into master.](null "Note how they aren't pushed to master. Don't push to master.") So when you have finished making your changes to the code, and have added or fixed a feature, you are ready to "publish" your branch to the server, which in our case is [Github.](null "Note that Github and git are not the same. Github is a service, and git is software.") To do this, you type the easily remembered command:

```
git push --set-upstream origin Fix_For_File_C
```

Or you can just do `git push` and have git tell you the [command to type.](null "Since `git push` is invalid for local branches it will tell you the correct command to publish the branch to the remote) Quickly breaking down what the command does, it pushes the Fix_For_File_C branch to [origin which is the server which is Github in our case.](null "Read the pro git guide if you really want to learn this stuff -- it is super cool!")

#### Code Review
Now you have your branch published to Github and it can be found in the Repo under the [branch pull-down menu](null "Right above the listing of the files in the Repo"). However it still isn't merged into master, and unless someone [branches off your branch](null "`master` isn't special, and in fact is just a branch. So any branch can have a branch come off of it.) You want your code in the [Master branch, along with the other awesome code](null "But you won't resort to cheating by pushing to master. I will hunt you down if you do."). To do that, you need to initiate a pull-request.

A pull-request isn't actually a git command, and it is a feature that Github has created in order to make code review easier. You can create a pull-request by clicking the weird looking button to the left of the [branch pull-down menu.](null "Or by looking with your eyes at the page. There are a few different places you can initiate a pull-request") It will ask for some details and comments about the pull-request, and you should be as explicit as possible. Anything less than a paragraph and you have not [written enough](null "But don't put in filler text because that just wastes time. Oh god its high school english class all over again...")

Once you have completed that process, you should notice a little `1` next to the `Pull Requests` tab on the right. If you click on this you can see the Pull Requests that are currently being awaited code review. You can look at these and take note of how easily it is to tell what has been changed in the branch and how it will [affect](null "effect?") Master. Do NOT complete your own [Pull Request.](null "That is just a shitty thing to do.")

[Someone](null "Probably me...") will come around, look at your code and complete the pull request if it [looks good.](null "Otherwise they will post passive-aggressive comments on your pull-request asking why you are using TCP/IP when UDP/IP works soooo much better even though they don't realize that nobody cares how fast the messages travel and the messages that do travel it is desired to see them in an ordered manner, which really brings up the issue of why the hell we are sending the data the way we are and the fact that we should really just rethink our shitty code structure for that section which is the part that THEY wrote and not my fucking problem. But I'm not salty or anything.") 

Woohoo! You have done it! You have made it to Master! You are one with the world!

#### Cleanup
After completely the difficult task of getting your code to master, it is now time to clean up the mess you created on the path. For example, we have a public branch that is no longer being used and you have a local branch whose [name is no longer relevant.](null "Name your branches descriptively!) I don't care about how you organize your [personal computer](null "I prefer to keep my computer filesystem organized like a web... or a pile of files. I think a pile of files is a good description.") but I *do* care about our public branches. 

To delete a branch that has been merged to Master [via a pull-request](null "And no other way.") you simply click the `branches` tab at the top, and then click the delete button. Easy, peezy, [cover-girl.](null "Wait, what?!")

Cleaning up your own computer files is [even easier.](null "Technically it is harder, but it is still easy") You simply:

```
git checkout master
git pull
```

To go back to the [master branch and update it.](null "But don't push from it. Ever.") And then

```
git branch -d [BRANCH NAME]
```

To remove the old branch. Now you can branch off from master again and continue on!

## Things Getting Nasty
Remember before I was talking about Merge conflicts and stuff? Well they are the worst and [I hate them.](null "You will too!") To help prevent diseases such as Merge conflicts, remember to regularly update your master branch and keep your local branch updated with the master branch. This can be done via:

```
git checkout master
git pull
git checkout [BRANCH]
git merge master
```

However, sometimes someone will commit a change which will [effect](null "affect?") your work. You will get a merge conflict.

##### Dealing with the nasty

Sometimes there is that pile of poop sitting in the middle of your dorm room, and you are pretty sure it is your roommates fault. It has sat there for a while, with neither of you willing to fix the problem. Eventually you will have to clean it up, and it is better to do it [sooner rather than later.](null "And definitely do it before your significant other comes over and breaks up with you because 'Why the fuck is there a pile of shit on your floor?`")

~~You can see more information about a merge conflict by doing `git status`. This should display a few things, files that are to be [changed](null "in green") and files that are in [conflict](null "in red"). Edit the files in conflict using any [text editing tool you want.](null "If it isn't vim you are a peasant.")~~ I was writing this, and then I realized Github has an awesome writeup of [how to solve a merge conflict (LINK)](https://help.github.com/articles/resolving-a-merge-conflict-from-the-command-line/). Just look at that, I have better work to do. 

