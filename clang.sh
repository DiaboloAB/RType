#!/bin/bash

usage()
{
    echo "Usage: $0 <check|fix>"
}

COMMAND=$1

if [ "$COMMAND" == "check" ]; then

    echo "Checking formatting..."
    find engine include libs src -name "*.cpp" -o -name "*.hpp" | while read file; do
        clang-format -n "$file"
    done

elif [ "$COMMAND" == "fix" ]; then

    echo "Fixing formatting..."
    find engine include libs src -name "*.cpp" -o -name "*.hpp" | while read file; do
        clang-format -i "$file"
    done

else
    usage
fi
