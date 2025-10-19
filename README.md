
## Todos

### Completed
- [OK] render_list recode. check render_ray_list.h for info
- [OK] check render_ray_list_ops file and recode
- [OK] add rotation ray casting algorithms
- [OK] check go off the map problem
- [OK] need image rendering
- [OK] decide what to do on bonus
- [OK] memory management (Burak)

### In Progress
- [ ] remove useless and commented code blocks
- [ ] find name for project group (brainstorm here) -> firbal?
- [ ] tests and more tests need to look all scenarios (Burak)

## Bonus

### CHANGE
- [ ] real-time movement and rendering
- [ ] ground and sky will be a texture
- [ ] wall collision

### NEW
- [ ] looking up and down with mouse and keys
- [ ] minimap

### Spell System General Ideas
- [ ] an entity class for all (door, fireball etc.)
- [ ] subclasses for entities
- [ ] spellbook (fire, alohomora(unlock door), colloportus(locks door))
- [ ] key SPACE activate the spell
- [ ] key Q passes the next spell

### Fireball
- [ ] renders after scene, as foreground
- [ ] fireball have white spaces that doesnt renders

### Doors
- [ ] in map validation door must process as 0
- [ ] add doors as array in map struct. need door count then alloc sizeof(t_door) * doorcount
- [ ] doors have lock -> int lock
- [ ] a door have its location and direction -> t_vec pos, double dov(radian)
- [ ] identify doors by its position -> this is a function that looks all the doors and returns the searched
- [ ] key E should open unlocked doors
- [ ] opening of a door is -> changes dov rapidly
- [ ] sound effect on open
- [ ] sound effect for locked doors
- [ ] sound effect on lock
- [ ] sound effect on unlock
