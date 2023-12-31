# birthdayrem
 
 
A birthday reminder script done in awk, bash, python, php, lua, c & node.

Take a list of birthdays in the format:
"yyyy-mm-dd, [name]"

A 'death date' can also be added:
"yyyy-mm-dd, [name], yyyy-mm-dd"

Print the list in order from 'now'.

Calculate a person's current age or the age they were when they died.

LICENCE: GNU GPL

Hugh Carroll hughie@carrollonline.co.uk
https://github.com/psaikido/birthdayrem

## Installation

```
git clone https://github.com/psaikido/birthdayrem
mkdir ~/.config/birthdayrem
```

## Usage

Copy [your repo path]/birthdays to ~/.config/birthdayrem and edit it with your own data.

If all the languages are installed the ./test.sh script will run all the programs.


### awk

```
awk -f [repo]/awk/birthdayrem.awk ~/.config/birthdayrem/birthdays
```

### bash

```

chmod +x [repo]/bash/birthdayrem
[repo]/bash/birthdayrem
```
### python

```
python [repo]/python/birthdayrem.py
```

### php

```
php [repo]/php/birthdayrem.php
```

### lua

```
lua [repo]/lua/birthdayrem.lua
```

### c

```
[repo]/c/birthdayrem

or compile yourself:
cd [repo]/c
gcc birthdayrem.c -o birthdayrem
./birthdayrem
```

### node

```
chmod +x [repo]/node/birthdayrem.js
[repo]/node/birthdayrem.js
```
