#!/bin/bash

CC="cc"
DFLAG="-DLOG"

$CC *.c $DFLAG -o philo


echo "Please choose a test case:"
select option in "Test Case 1" "Test Case 2" "Test Case 3" "Exit"; do
    case $option in
        "Test Case 1")
            echo "Running Test Case 1..."
            ./philo 4 5 3 2 1
            break
            ;;
        "Test Case 2")
            echo "Running Test Case 2..."
            ./philo 7 8 6 4 3 5
            break
            ;;
        "Test Case 3")
            echo "Running Test Case 3..."
            ./philo 1 9 5 10 6
            break
            ;;
        "Exit")
            echo "Exiting..."
            break
            ;;
        *)
            echo "Invalid option. Please select a valid test case."
            ;;
    esac
done
