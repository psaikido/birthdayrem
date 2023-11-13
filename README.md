# birthdayrem
 
 
A birthday reminder script done in awk, bash & python.

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
