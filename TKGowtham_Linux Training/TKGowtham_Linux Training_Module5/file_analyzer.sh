#!/bin/bash

################################################
#
# EmbedUR - Linux Training - Module 5 Assessment
#
# Program to analyze file with given keywords
#
# Name : T K Gowtham
# College : VIT Chennai
# Email : gowthamkamalasekar@gmail.com
#
################################################

echo "This is $0"
echo "Parameters Passed : $@"

ERROR_LOG_FILE="errors.log"

log_error () {
	echo "$1" | tee -a "$ERROR_LOG_FILE"
}

show_help () {
	cat <<EOF
Usage : $0 [OPTIONS]

Options :
	-d <dir> search directory
	-k <key> keyword to search
	-f <file> file to directly search
	--help	to get help here doc for this  program

Examples :
	./file_analyzer.sh -d logs -k errors
	./file_analyzer.sh -f script.txt -k TODO
	./file_analyzer.sh --help
EOF
}

if [[ "$1" == "--help" ]]; then
        show_help
        exit 0
fi

while getopts ":f:d:k:" flag; do
        case ${flag} in
                f) file="$OPTARG" ;;
                d) dir="$OPTARG" ;;
                k) keyword="$OPTARG" ;;
                ?) log_error "Invalid Option -$OPTARG" ;;
        esac
done

validate_input () {
	if [[ ! -z "$file" && ! -f "$file" ]]; then
		log_error "Error : File $file doesn't exist" 
		exit 1
	elif [[ ! -z "$dir" && ! -d "$dir" ]]; then
		log_error "Error : Dir $dir doesn't exist"
		exit 1
	elif [[ ! "$keyword" =~ ^[a-zA-Z0-9_]+$ ]]; then
		log_error "Error : keyword is empty or doesn't follow regex"
		exit 1
	fi
}

validate_input

fileAnalyze () {
	local target=$1
	local keyword=$2

	if [[ -f "$target" ]]; then
		echo "Searching file : $target"
		content=$(cat "$target")
		if grep -q "$keyword" <<< "$content" 2>>"$ERROR_LOG_FILE"; then
			echo "FOUND : $keyword present in file $target"
		fi
	elif [[ -d "$target" ]]; then
		echo "Searching directory : $target"
		local entries=("$target"/*)
		for entry in "${entries[@]}"; do
			fileAnalyze "$entry" "$keyword"
		done
	fi
}

if [ ! -z $dir ]; then
	fileAnalyze $dir $keyword
else
	fileAnalyze $file $keyword
fi

echo "Script executed successfully with $# args. Exit status: $?"
