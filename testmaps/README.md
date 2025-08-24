# CUB3D Test Maps

This directory contains various test maps to validate your cub3D parser implementation.

## Valid Maps

### valid_basic.cub
- Simple 5x5 map with one player (N)
- All required elements present
- Map properly closed by walls

### valid_complex.cub  
- Complex map from the subject example
- Contains spaces within the map
- Irregular map shape but properly closed
- Player positioned at N

### valid_random_order.cub
- Elements defined in random order (not the typical order)
- Multiple empty lines between elements
- Player positioned at W

### valid_with_spaces.cub
- Map contains spaces as valid characters
- Player positioned at S with spaces around

### valid_minimal.cub
- Smallest possible valid map (3x3)
- Player positioned at E
- Uses extreme color values (0,0,0 and 255,255,255)

## Invalid Maps

### invalid_no_player.cub
- Error: Map has no player starting position
- Should return error about missing player

### invalid_multiple_players.cub  
- Error: Map has multiple players (N and N)
- Should return error about multiple players

### invalid_not_closed_top.cub
- Error: Top border is not closed (starts with 0)
- Should return error about map not being closed

### invalid_not_closed_bottom.cub
- Error: Bottom border is not closed (starts with 0) 
- Should return error about map not being closed

### invalid_not_closed_left.cub
- Error: Left border is not closed (starts with 0)
- Should return error about map not being closed

### invalid_not_closed_right.cub
- Error: Right border is not closed (ends with 0)
- Should return error about map not being closed

### invalid_missing_north_texture.cub
- Error: Missing NO (North texture) identifier
- Should return error about missing required element

### invalid_missing_floor_color.cub
- Error: Missing F (Floor color) identifier
- Should return error about missing required element

### invalid_color_out_of_range.cub
- Error: Color value 256 is out of range [0,255]
- Should return error about invalid color range

### invalid_incomplete_color.cub
- Error: Floor color only has 2 values instead of 3 (R,G,B)
- Should return error about incomplete color specification

### invalid_character_in_map.cub
- Error: Map contains invalid character 'X'
- Should return error about invalid map character

### invalid_duplicate_texture.cub
- Error: North texture (NO) is defined twice
- Should return error about duplicate element

### invalid_map_not_rectangular.cub
- Error: Map is missing the last row (not rectangular)
- Should return error about invalid map format

### invalid_no_map.cub
- Error: File contains no map section
- Should return error about missing map

### invalid_negative_color.cub
- Error: Color value -1 is negative
- Should return error about invalid color value

## Expected Behavior

Your parser should:
1. Accept all valid maps without errors
2. Reject all invalid maps with appropriate error messages
3. Always print "Error\n" followed by a descriptive message for invalid maps
4. Exit with appropriate error codes

## Testing Usage

```bash
./cub3d testmaps/valid_basic.cub          # Should work
./cub3d testmaps/invalid_no_player.cub    # Should print "Error\n" + message
```
