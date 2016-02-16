-- Creates the first level of enemies! --

dofile("enemies/enemy_sheet.lua")

width = 960

mid_x = width/2
lq_x = width/4
rq_x = 3*width/4
lm_x = 10
rm_x = width - 10

num_enemies = 0
enemy_stack = {}

num_enemies = num_enemies + 5
enemy_stack = ListConcat(enemy_stack, hVformation(lq_x, 900, -50, 60, 5))

num_enemies = num_enemies + 5
enemy_stack = ListConcat(enemy_stack, hVformation(rq_x, 1100, 50, 60, 5))

num_enemies = num_enemies + 5
enemy_stack = ListConcat(enemy_stack, Vformation(mid_x, 1300, 40, 50, 5))

num_enemies = num_enemies + 3
enemy_stack = ListConcat(enemy_stack, hformation(lq_x+50, 1600, -80, 3))

num_enemies = num_enemies + 3
enemy_stack = ListConcat(enemy_stack, hformation(rq_x-50, 1600, 80, 3))

num_enemies = num_enemies + 5
enemy_stack = ListConcat(enemy_stack, hVformation(lq_x, 1800, 50, 60, 5))

num_enemies = num_enemies + 5
enemy_stack = ListConcat(enemy_stack, hVformation(rq_x, 2000, -50, 60, 5))

enemy_stack = ListConcat(enemy_stack, hformation(lm_x, 2350, 80, 4))

enemy_stack = ListConcat(enemy_stack, hformation(rm_x, 2350, -80, 4))

enemy_stack = ListConcat(enemy_stack, hformation(mid_x, 2450, -80, 3))

enemy_stack = ListConcat(enemy_stack, hformation(mid_x, 2450, 80, 3))

--function h_waves_f