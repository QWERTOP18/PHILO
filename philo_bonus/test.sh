#!/bin/bash

echo "Please choose a test case:"
select option in "Test Case 1" "Test Case 2" "Test Case 3" "Exit"; do
    case $option in
        "Test Case 1")
            echo "Running Test Case 1..."
            ./philo_bonus 4 310 200 100 
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
            ./philo_bonus 7 8 6 40 30
            break
            ;;
        "Test Case 3")
            echo "Running Test Case 3..."
            ./philo_bonus 1 9 5 10 6
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

# Do not test with more than 200 philosophers.

# Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.

# Test 1 800 200 200. The philosopher should not eat and should die.

# Test 5 800 200 200. No philosopher should die.

# Test 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.

# Test 4 410 200 200. No philosopher should die.

# Test 4 310 200 100. One philosopher should die.

# Test with 2 philosophers and check the different times: a death delayed by more than 10 ms is unacceptable.

# Test with any values of your choice to verify all the requirements. Ensure philosophers die at the right time, that they don't steal forks, and so forth.