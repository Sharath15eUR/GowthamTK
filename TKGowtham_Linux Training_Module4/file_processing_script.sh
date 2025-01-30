#!/bin/bash

################################################
# EmbedUR - Linux Training - Module 4 Assessment
#
# Read a file line by line and output line to
# a file if line contains specific words
#
# Name : T K Gowtham
# Email : gowthamkamalasekar@gmail.com
# College : VIT Chennai
################################################

# Reading line by line using while loop takes a lot of time !!!

inputfile=$1

> output.txt #clearing the output file contents

while IFS="\n" read -r line 
do
	if echo "$line" | grep -q -E '("frame.time"|"wlan.fc.type"|"wlan.fc.subtype"):';
	then
		echo "$line" >> output.txt
	fi
done < $inputfile

echo "Script Completed."


#The above script taking 4 mins time to process 50K lines
# Most efficient approach to reduce the processing time using grep command as given below
# Which takes 3 seconds to process 32 lakhs lines

#grep -E '("frame.time"|"wlan.fc.type"|"wlan.fc.subtype"):' "$inputfile" > output.txt
