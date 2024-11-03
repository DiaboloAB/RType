#!/bin/bash

usage()
{
    echo "Usage: $0 <check|fix>"
}

COMMAND=$1

if [ "$COMMAND" == "check" ]; then

    rm -f log.txt
    echo "Checking formatting..."
    for file in $(find engine -name "*.cpp" -o -name "*.hpp"); do
        clang-format -n "$file" 2>> log.txt
    done

elif [ "$COMMAND" == "fix" ]; then

    echo "Fixing formatting..."
    find engine -name "*.cpp" -o -name "*.hpp" | while read file; do
        clang-format -i "$file"
    done

else
    usage
fi
