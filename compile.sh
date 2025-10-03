#!/bin/bash

isValidCharacter()
{
	local prompt="$1"
	local valid_characters="$2"

	while true; do
		read -r -p "$prompt" choice
		choice="${choice,,}"
		if [[ "$valid_characters" == *"$choice"* && ${#choice} == 1 ]]; then
			# Check if choice matches valid_characters and is 1 character long
			printf %s "$choice"
			break
		fi
	done
}

input=$(isValidCharacter "[c]lang++ or [g]cc?
" "cg")

if [ "$input" == "c" ]; then
clang++ -o0 ffdb.cpp -o ffdb_clang # Some reason HAS permissions
printf "Your C++ code has been compiled"
elif [ "$input" == "g" ]; then
g++ -S ffdb.cpp -o ffdb_g++ # Some reason doesn't have permissions
printf "Your C++ code has been compiled"
fi

# Remove -g if debugger not needed
# Will need to create an interactive script.