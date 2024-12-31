#!/bin/bash

CC="cc -fsanitize=thread"
DFLAG="-DLOG"

$CC *.c $DFLAG -o philo


echo "Please choose a test case:"
select option in "Test Case 1" "Test Case 2" "Test Case 3" "Exit"; do
    case $option in
        "Test Case 1")
            echo "Running Test Case 1..."
            ./philo 4 310 200 100 
            break
            # 0       1       has taken a fork
            # 0       1       is eating
            # 0       3       has taken a fork
            # 0       3       is eating
            # 200     2       has taken a fork
            # 200     2       is eating
            # 200     1       is sleeping
            # 200     4       has taken a fork
            # 200     4       is eating
            # 200     3       is sleeping
            # 300     3       is thinking
            # 300     1       is thinking
            # 310     1       died
            ;;
        "Test Case 2")
            echo "Running Test Case 2..."
            ./philo 7 8 6 40 30
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
