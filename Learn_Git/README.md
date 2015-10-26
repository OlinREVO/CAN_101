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


