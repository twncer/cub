### \~-- main.c --\~  
### //  
__->__ todos  
__->__ ~render_list recode. check render_ray_list.h for info [OK]~  
__->__ ~check render_ray_list_ops file and recode [OK]~  
__->__ ~add rotation ray casting algorithms [OK]~  
__->__ ~check go off the map problem [OK]~  
__->__ ~need image rendering [OK]~  
__->__ memory management :( [BURAK]  
__->__ tests and more tests need to look all scenarios [BURAK]  
__->__ find name for project group [after bonus mayb]  
__->__ decide what to do on bonus. _[will be noted below]_  

### \~-- BONUS --\~  
### //
__->__ firbal  

### \~-- render_ray_list.h --\~  
### //  
__->__ todos for better performance  
__->__ make t_ray -> *t_ray. it become an array of rays  
__->__ one node takes (SENSITIVITY * 0.05(maybe define this) * WIN_WIDTH) + 1 ray  
__->__ this way you can free only one node and alloc one node per rotate  
__->__ on render you should refactor the algo if you make changes  
__->__ HAHAHA  
__->__ OK