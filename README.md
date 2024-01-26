# PS7: Kronos Log Parsing

## Contact
Name: Nicholas Bartow
Section: 201
Time to Complete: 10 hours


## Description
Explain what the project does.
This project is about writing a program that reads logs from a Kronos InTough device. Specifically it reads logs from the device that we create a report.

### Features
Describe what your major decisions were and why you did things that way.
Overall the idea was simple, its about reading logs line by line at specific points.
These points are set by regex strings and we output the times and statuts of boots.

### Approach
Describe your overall approach to solving this problem.
The first tihing to do was initiaize some values such as lines, string names for files, setting flags of regex values with the given messages in the pdf. Once there is a match then reading the line was simple and merely extracting to the output file.

### Regex
What regular expressions did you use?  Explain what each one does.
I used boost regex "messages" for the first logging and the log entry for boot sequence completion.

To find those messages i used regex search functions that searched the string line read and matched them.
### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

I had some trouble with the output, i couldn't use an ostream constructor for the file name so i just had to call file open functions to make it work with the strings of the file names.

### Extra Credit
Anything special you did.  This is required to earn bonus points.
No extra credit

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
Tutoring, forgot the name 
