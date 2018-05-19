# spell-checker

This is a simplified version of the spell check program

## How to build?

`git clone https://github.com/rajesh92/spell-checker.git`

`make` - this builds your code and creates executable

`./spell-checker dictionary.txt input.txt` - this runs your code

`make clean` - this cleans your code and removes object files and executables

### INPUTS

`dictionary.txt` - This contains the words found in language dictionary. [Source](https://github.com/dwyl/english-words/blob/master/words_alpha.txt)

`input.txt` - This is the user file that will be analyzed

## What does it do?

The program loads up the dictionary in memory at runtime and walks through each word in the `input.txt` file. It ignores the words which have matches in the `dictionary.txt`. If the word is not present in dictionary it tries to find a word close to it as a suggestion.





Known issues:

1. Current code ignores punctuation
2. Current code is case sensitive
