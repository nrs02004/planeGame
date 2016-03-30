-- Creates the first level of enemies! --

dofile("enemies/enemy_sheet.lua")

width = 960

mid_x = width/2
lq_x = width/4
rq_x = 3*width/4
lm_x = 10
rm_x = width - 10

first_wave = {}


first_wave = ListConcat(first_wave, hVformation(lq_x, 900, -50, 60, 5, green_baddie))

first_wave = ListConcat(first_wave, hVformation(rq_x, 1100, 50, 60, 5, blue_baddie))

first_wave = ListConcat(first_wave, Vformation(mid_x, 1300, 40, 50, 5, purple_baddie))

first_wave = ListConcat(first_wave, hformation(lq_x+50, 1600, -80, 3, orange_baddie))

first_wave = ListConcat(first_wave, hformation(rq_x-50, 1600, 80, 3, blue_baddie))

first_wave = ListConcat(first_wave, hVformation(lq_x, 1800, 50, 60, 5, green_baddie))

first_wave = ListConcat(first_wave, hVformation(rq_x, 2000, -50, 60, 5, green_baddie))

first_wave = ListConcat(first_wave, hformation(lm_x, 2350, 80, 4, orange_baddie))

first_wave = ListConcat(first_wave, hformation(rm_x, 2350, -80, 4, orange_baddie))

first_wave = ListConcat(first_wave, hformation(mid_x-40, 2450, -80, 3, purple_baddie))

first_wave = ListConcat(first_wave, hformation(mid_x+40, 2450, 80, 3, blue_baddie))

enemy_stack = {}

enemy_stack = ListConcat(enemy_stack, first_wave)

-- Making 20 identical waves --

for k=1,20 do
    enemy_stack = ListConcat(enemy_stack, push_back(deepcopy(first_wave), k*(2550-900)))
end

powerup_weapons = {"purple_machine_gun", "green_missile_launcher", "blue_missile_launcher","orange_missile_launcher"}