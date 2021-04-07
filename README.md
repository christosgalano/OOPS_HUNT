# Documentation #

***OOP'S HUNT aims to simulate a role playing game (linux terminal only)***

## Compilation ##

There is a simple Makefile for compiling the program. In particular, we run make from the directory that contains it to do the build and then we
have the following options:

- make          : generates the executable game.exe (if it has not already been created or if a change has been made)
- make run      : generates the executable game.exe (if it has not already been created or if a change has been made), which also runs it
- make valgrind : generates the executable game.exe (if it has not already existed or if a change has been made), which also runs with valgrind it
- make time     : generates the executable game.exe (if it has not already existed or if a change has been made), which also runs and displays details of its execution time
- make clean    : deletes the executable game.exe and needs to be rebuilt


## Assumptions ##

1. A player controls from min_no_heroes to max_no_heroes heroes. The exact number of heroes is determined by a choice of the player in the initial phase of the game.

2. Each hero can be under the influence of maximum one potion at any time.

3. If the player loses a battle then he is automatically transferred to the square he was before entering the square where the battle took place.

4. The world of the game is specially designed; it does not result from the random production of squares but follows a specific construction that aims to provide a pleasant
   experience for the player.

5. A hero can cast as many spells as he wants against a monster (one each round at max), however if the monster is already under the influence of a same type of spell with the one he is about to cast,
   then the second one will simply cause damage. That is, if the hero casts a FireSpell against a monster and in the next round he attempts to cast another FireSpell against the same
   monster, then the second one will only cause damage and it will not change the defense_reduction nor the rounds_of_effect that are currently in place from the first FireSpell.

6. In the event that the damage (taking into account specific Attributes) caused by one Living to another is less than the other Living's minimum_damage_factor% of maximum health, then
   the latter one will take damage equal to the minimum_damage_factor% of its maximum health. This rules out the possibility that one Living may not be able to
   cause damage to another (if we take into account the fact that at the end of each round each Living recovers a percentage of its health then it is obvious that the amount of damage that
   will be caused in this case is very small but not zero).

7. Regarding the leveling system it is based on a specific formula that uses the current level of a Living, as well as the lower_bound, upper_bound of each Attribute in order to
   upgrade it. The values ​​awarded to lower_bound, upper_bound of an Attribute for each category of heroes and monsters are specific and aim at their smooth adjustment depending on the level
   of the Living to which they belong.

8. Each battle consists of individual rounds where the heroes and the monsters correspond alternately, until one of the two teams contains no alive members.

9. Monsters randomly attack alive heroes.

10. Battle in a common square can only occur when the heroes enter the square. That is, if the player attempts to access the square in which his heroes are located and
    the square is of type common then there is no possibility of a battle. There will simply be a message about what happened when he entered this square (if there is a battle then
    player won because if he had lost he would have been automatically transferred to the square he had visited prior to entering the common square).

11. Since the user simply has access to the game and not the implementation, unnecessary checks are ingored (like that the indexes are not out of the array bounds) because the implementation ensures that
    there is no possibility of such thing happening.

12. It is assumed that there are no problems with memory allocation and that new does not return NULL and does not throw an exception under any circumstances.

13. In the ERD folder there are images with Entity Relationship Diagramms.
