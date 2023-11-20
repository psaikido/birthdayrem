#!/usr/bin/env bash

DATAFILE="$HOME/.config/birthdayrem/birthdays"

printf "%s\n" "awk"
awk -f ./awk/birthdayrem.awk $DATAFILE

printf "\n%s\n" "bash"
./bash/birthdayrem

printf "\n%s\n" "python"
python ./python/birthdayrem.py

printf "\n%s\n" "php"
php ./php/birthdayrem.php

printf "\n%s\n" "lua"
lua ./lua/birthdayrem.lua

printf "\n%s\n" "c"
./c/birthdayrem

printf "\n%s\n" "node"
./node/birthdayrem.js
