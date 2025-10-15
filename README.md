ı-- main.c --ı
// 
// todos
// render_list recode. check render_ray_list.h for info [OK]
// check render_ray_list_ops file and recode [OK]
// add rotation ray casting algorithms [OK]
// check go off the map problem [OK]
// need image rendering [OK]
// memory management :( [BURAK]
// tests and more tests need to look all scenarios [BURAK]
// find name for project group [after bonus mayb]
// decide what to do on bonus.

ı-- render_ray_list.h --ı
//
// todos for better performance
// make t_ray -> *t_ray. it become an array of rays
// one node takes (SENSITIVITY * 0.05(maybe define this) * WIN_WIDTH) + 1 ray
// this way you can free only one node and alloc one node per rotate
// on render you should refactor the algo if you make changes
// HAHAHA
// OK