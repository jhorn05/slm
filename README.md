# slm – Small Language Model

`slm` is a command-line tool that trains a simple character-based language model
on a text file and uses it to generate new "text" – an artificial idiot.

## How it works

The model works on k-grams: strings of exactly k consecutive characters

**Training:** The program slides a window of length k over the training text and counts

- how often each k-gram occurs.
- for each k-gram, how often each character immediately follows it.

**Generating:**

1. Choose a starting k-gram, weighted by how often each k-gram occurs, and output it.
2. Look at the characters that followed the current k-gram in the training text and
   sample the next character, weighted by those counts. Output it.
3. Drop the first character of the current k-gram and append the new one.
4. Repeat from step 2 until the requested number of characters has been output.

Without a pseudocount, the generator stops early if it reaches a k-gram that was never
followed by any character, so the output may be shorter than requested.

**Pseudocount:** With the option -a, a pseudocount a is added to the count of every
character in the alphabet (all distinct characters in the training text).
The probability of character c after k-gram w then becomes

    P(c | w) = (count(w, c) + a) / (N(w) + a · |alphabet|)

where N(w) is the number of times w was followed by some character.
With a > 0 every character is possible after every k-gram, so the generator never gets stuck,
and k-grams that never occurred in the text get a uniform distribution.

## Compiling

Requires a C++17 compiler (e.g. g++ or clang) and make.
make: builds the executable slm
make clean: removes the executable and all object files

## Usage

-a pseudocount: a non-negative number added to every count
k: positive intiger, the k-gram lenght
file: the training text
length: number of characters to output, including starting k-gram

### Examples

$ ./slm 2 moby_dick.txt 20
he in the Jonacts st

$ ./slm 6 moby_dick.txt 200
of Captain circle upon the upper
stubbornness. And all he beef was enough we known aside! Stand clap the tutelary guard the snugly housekeepers, when I start beats; I told me that there with all the

$ ./slm -a 0.01 3 moby_dick.txt 40
ess (loong
now; ber; foriveree, st core


A larger k gives output that looks more like real English, since each character
depends on a longer context. A small *k* gives mostly words that don't really make sense.

### Errors

User errors are reported with a message on standard error and a non-zero exit status, for example:

$ ./slm 2 no_such_file.txt 100
slm: cannot open file 'no_such_file.txt'


Detected errors: wrong number of arguments, k or length not a positive integer,
length smaller than k, -a not followed by a non-negative number, unknown options,
a training file that cannot be opened, and a training text too short to contain
any k-gram followed by a character.

## Code structure

All source code is in src/:

main.cpp: parses command-line arguments, runs training and generation, catches exeptions
LanguageModel.h/.cpp: class LanguageModel: reads the training file and stores k-gram counts, transition counts and alphabet
TextGenerator.h/.cpp: class TextGenerator: generates text from a LanguageModel

Errors are detected where they occur and thrown as std::invalid_argument
or std::runtime_error. They are caught in main.

## Observations

- With a = 0 and a small training text, generation often stops early.
- A small pseudocount works well for small k. For larger k, many k-grams occur only
  once or twice, so even a = 0.01 gives a noticeable chance of a random character. That
  character usually creates a k-gram that never occurred in the text, which has a
  uniform distribution, so the output tends to turn into random characters for the rest of the run.
- The training texts contain some non-ASCII characters (curly quotes), which are stored
  as several bytes. The program treats each byte as one character, as the assignment allows,
  so these can occasionally appear as `?` in the output.
