# AdventOfCoding2023_06
Advent of coding 2023 challenge 6

## Objective
The challenge for day 6 was to find all of the available integer times that would win a "boat race". The race was held over a set amount of time and you could choose how long to charge your boat which would determine how fast the boat would move. The boat would not move until the button was released and the boat would move at a unit distance per unit time equal to the length of unit time the button was pressed. The desired result would be to multiply the number of possible unit times that would beat the current record by each other. 

## Solution
Using algebra we can calculate the amount of time that the button is pressed to the distance that the boat will travel in a set amount of time.

```
totalTime = the total time of the race
distance = current distance record
movementTime = length of time that the boat is given to move
buttonTime = length of time that the button is pressed
velocity = speed of the boat

velocity = buttonTime

totalTime = movementTime + buttonTime

distance moved with constant velocity equation:
movementTime*velocity + offset = distance

We can rewrite this in terms of movementTime:
movementTime(totalTime - movementTime) = distance
-movementTime^2 + movementTime * totalTime = distance

Then we can find that we just need to find when we are beyond the record distance by using the quadratic equation
movementTime^2 - movementTime * totalTime + recordDistance = 0

start/end = (totalTime -/+ sqr(totalTime^2 -(4 * recordDistance)))2
```

Round both start and end to the floor then subtract the start from the end and multiply the results together.
