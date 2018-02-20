# README #

## General info ##

This is the unofficial repo for Adversity, the heart of the whole project. It contains everything Adversity is built from - code, graphics, data, design insights, etc.
It also contains all versions, a complete issue list, a project board and other resources.
For the official Issue Tracker and Versions list, see [Adversity Official repo](https://bitbucket.org/raddosgames/adversity-official/overview).
To download dependencies required to build the project, go to [Adversity-dependencies repo](https://bitbucket.org/raddosgames/adversity-dependencies).

| Current version |   |
| --------------- | - |
| Official        | 1.0.2 - beta |
| Dev             | 1.0.2 - beta |

Next official release:

** 1.1.0 - beta   -   2018-04-01 **

### How do I get set up? ###

#### Summary ####

---

**_ Note to nonprogrammers _**

_You can skip most of the instructions provided here, but please read 1. as it contains generally useful knowledge._

---

You should be able to build Adversity on Windows and Linux devices.

The approaches listed below are the recommended ones and you are not forbidden from doing it another way, as long as it works and doesn't impose any threat on Adversity nor Raddos Games.

Separate approaches are marked using letters.

1.Repository access

First you need to easily access this repository from your computer. It's a Git repo, so you'll need a Git client to do so. You could go with just a bare Git bash or Git GUI for graohical interface, but it is recommended that you download and install a more sophisticated client. Good candidates are [SourceTree](https://www.sourcetreeapp.com/) (Win, Mac) and [GitKraken](https://www.gitkraken.com/) (Win, Mac, Linux).

Once you install a Git client of your choice, proceed to the Add remote repository step in the program. Log in using your BitBucket account, choose Adversity (without any additional text), choose the destination, where the repo will be cloned to and click Clone or something like that.

![Cloning](https://bitbucket.org/repo/7EK6z9k/images/2473478235-cloning.png)

After a few seconds you should be able to see the commit history. Then, if no other instructions were provided, please check out _develop_ branch. Next, start working on your feature by creating a new feature branch. Commit made changes and push them to the repo regularly. When you've done enough and would like to incorporate your changes into the develop branch, open a pull request.

If you lost me in the last two lines, please go [here](https://www.git-tower.com/blog/git-cheat-sheet/) or [here](https://www.atlassian.com/git/tutorials/atlassian-git-cheatsheet) to learn more about Git. You can also check out its official documentation or ask admins. You should also review latest commits to get a feeling of how it should look like.

2.Dependencies

Adversity uses several 3rd party libraries to work properly. You must download them to be able to build the project.
You can do so, downloading and setting it all up on your own, but there are packages prepared for you to quickly go into action.

2.1.Overview

You will need to download that software:

- APeR (by _NemesorRaddus_)
- RBoundedValue (by _NemesorRaddus_)
- spdlog (3rd party)
- VerInfoFileGen (by _NemesorRaddus_)

Another very important dependency is the Qt framework, but we'll get into that later.

2.2.a.How to download it on your own

Spdlog should be rather easy to download. *You only need the _include_ dir.* However the paths next to #include directives in its files rely on additional make include path. You will need to change each of them to use relative system or change include settings in your version of .pro file or Makefile.

The rest of the libs should be available somewhere on my account, if not and you really want to do it on your own, contact me.

2.2.b.How to download it in a package

Go to the [download section of the dependencies repo](https://bitbucket.org/raddosgames/adversity-dependencies/downloads/).

Click _Download repository_. Ignore security warnings should they appear.

You will receive an archive with a folder inside. Copy the content of that folder into the main Adversity directory on your computer.

Then run init-win or init-linux, depending on your platform, to initialize the dependencies. After the process is complete, you can remove those init files.

You're ready to go :)

3.Qt Framework

The whole project relies on it. Without it, nothing works. There are many ways how you can obtain it.
Currently used version: 5.10.1

3.a.Installer

Download Installer, with Qt Creator bundled with the framework. Go [here](https://www.qt.io/download) and choose open source OR get the installer from the [cloud](https://mega.nz/#F!8ZRynTpA!op81fl7Lgt-oi0bxA5NslA) (if it's not easily available on Qt's website, sometimes they hide it somewhere in the back:/).

Run it, select currently used Qt version, Desktop (MinGW on Windows) and Android ARMeABIv7. Then select Tools, latest MinGW (if on Windows).

![Qt installer on Linux](https://bitbucket.org/repo/7EK6z9k/images/3246473002-qt%20installer.png)

Install.

Open the cloned main project and you can start working :)

It's probably the easiest way, working on most platforms.

3.b.From source

You can also download the Qt source and use another IDE, but it's harder. However, if you choose to do so, prefer nondevelop dynamically-linked release build of Qt.

3.c.Package manager

If working on Linux, you can also try downloading everything using apt or similar tool. Be warned though, that Qt provided in such services usually heavily lags behind with versions and may not be suitable for working on Adversity.

Those are 3 ways you can download Qt, but remember that it's only what we recommend; your ways aren't limited to this list.

4.Configuring Android settings

This section describes actions needed to build for mobile devices with Android. You can skip it if desktop version satisfies you.

4.1.SDK, JRE, JDK

You can get all these things by installing [Android Studio](https://developer.android.com/studio/index.html). Alternatively, you can also download them separately, but it's a little harder.

4.2 NDK, Android APIs, AVD

Now open Android Studio. Something like this should appear:

![Android Studio](https://bitbucket.org/repo/7EK6z9k/images/1092374839-android%20studio.png)

Now click the configure button, then SDK manager.

First of all, you'll need to select NDK for installing. Without it you can't compile code for Android.

![NDK](https://bitbucket.org/repo/7EK6z9k/images/3437052932-ndk.png)

Now, you need to select which version of Android API you would like to use. And here, you can have a little more freedom. These settings depend on what your intentions are, because there are two ways of testing Adversity on mobile device:

- by using a physical device, such as your smartphone
- or an AVD, Android Virtual Device

![APIs](https://bitbucket.org/repo/7EK6z9k/images/3111347047-sdk.png)

You need better PC specs to run AVDs smoothly, however they are more comfortable as you don't need to plug in your device to test the game. AVDs require also a bit more storage as you need to have a system image to run them. And sometimes bugs might occur, which won't be visible on virtual device. On the other hand, with AVDs you can choose whichever device you want, with the API you like and experiment a bit more. The choice is yours (of course you can also mix these techniques if you want :) ). Just remember that if you decide to test on physical device, your device must be supported (especially the API is important).

After you complete this step, Qt Creator should automatically detect compiler from NDK and be ready to build the project. If you're doing it another way, you'll have to tinker with it a bit more.

---

That's it. If you have any questions, please contact the admins.