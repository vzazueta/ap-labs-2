Lab - Goroutines vs OS Threads
==============================
Read section 9.8 from The [Go Programming Language](https://www.amazon.com/dp/0134190440/ref=cm_sw_em_r_mt_dp_U_Uz0RDbHAH27PH) book.
Then, do the 9.4 and 9.5 exercises.

- Update the `README.md` file on instructions about how to run your programs.
- Your 2 programs must automatically generate their proper  result report depending on what parameters they received.
- Generated reports are free format and written on any file extension (i.e. .txt, .pdf, .md, .svg, .png, .jpg, .tex)

General Requirements and Considerations
---------------------------------------
- Submit only `*.go` files.
- Don't forget to handle errors properly.
- Coding best practices implementation will be also considered.


How to submit your work
=======================
```
GITHUB_USER=<your_github_user>  make submit
```
More details at: [Classify API](../../classify.md)

---------------------------------------

Instructions:

Exercise 9.4: The syntax to use this program can be done in both ways: the traditional and with pipes.
		Shall the user choose the traditional way, the pipeline limit will be set in 30000000 by default. The limit for my computer, as I found
		during the exercise, was around 40000000 and 50000000, so to be sensible 
		about other people's computers, the default is 30000000.
		If you do it the pipes way, you just need to set a --pipe # instruction
		for the program to use as input. This will not show the limitations of
		the computer, but it will give the user an idea of how the memory usage
		progresses.

Exercise 9.5: Since this exercise is more about measuring time, which is limitless unlike
		the memory of a computer, the amount of time is up to the user.
		Once we set the program to run, the user can wait as long as he/she
		wants, and to end it we must press Ctrl+C to send an 'interruption'
		signal. This will have tracked the time it took for each message to 
		be received, and then divided it by the time since the beginning of
		the run.
