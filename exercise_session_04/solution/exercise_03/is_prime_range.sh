#!/bin/bash
MAXNUMBER=$1

if [[ -z $MAXNUMBER ]]; then
    echo "Enter a maximum number: "
    read MAXNUMBER
fi

if [[ ! $MAXNUMBER =~ ^[0-9]*$ ]]; then
    echo "$MAXNUMBER is not an integer."
    exit 1
fi

# Function to check if a number is prime
is_prime() {
    # Read the first argument, containing the number to check
    NUMBER=$1
    # ISPRIME is the variable that will contain the result of the function
    ISPRIME="True"
    for ((i = 2 ; i < $NUMBER ; i++)); do
        if [ $(expr $NUMBER % $i) -eq 0 ]; then
            ISPRIME="False"
            break
        fi
    done
}

# Loop over the range of number specified
for ((num = 2 ; num < $MAXNUMBER ; num++)); do
    is_prime $num
    if [[ $ISPRIME == "True" ]]; then
        echo "$num is prime"
    else
        echo "$num is not prime"
    fi
done
