Lee Van
June 12, 2018
Word ladder lab from Longwood University's CMSC389 course.
This program (and README) was written  for a lab assignment for 
Dr. Don Blaheta ( http://cs.longwood.edu/~dblaheta/ )

The program takes in three parameters from the command line. 
	The first parameter is the starting word for the word ladder. 
	The second parameter is the ending word for the word ladder.
	The third parameter is the file containing words that will construct the word ladder.

The program uses a breadth-first search to find the minimum lenght word ladder if one exists. If no word ladder can be
constructed, the user will be notified. Otherwise, the program will output the word ladder that it found. Words are put into
a set of words and when a word is compared to the set before adding a word to the queue. 

Note: While testing on the /usr/share/dict/words file, the program took a minimum of around 30 seconds before completing on
words of length 5 for a few test cases.

To compile:
	compile ladder.cpp

To run:
	./a.out [start word] [end word] [dictionary filename]

To test:
	Run Command: 
		./a.out bed rod threeletters.txt
