dofile("objects/guns.lua")

blue_machine_gun = Loadwith(machine_gun, blue_pellet)
blue_machine_gun.gun_name = "blue_machine_gun"

purple_minigun = Loadwith(minigun, purple_pea)
purple_minigun.gun_name = "purple_minigun"

green_missile_launcher = Loadwith(missile_launcher, green_missile)
green_missile_launcher.gun_name = "green_missile_launcher"

blue_missile_launcher = Loadwith(narrow_missile_launcher, blue_missile)
blue_missile_launcher.gun_name = "blue_missile_launcher"

orange_missile_launcher = Loadwith(missile_launcher, orange_missile)
orange_missile_launcher.gun_name = "orange_missile_launcher"

blue_angle_minigun = Loadwith(minigun, blue_angle_pea)
blue_angle_minigun.gun_name = "blue_angle_minigun"

green_angle_machine_gun = Loadwith(machine_gun, green_angle_pellet)
green_angle_machine_gun.gun_name = "green_angle_machine_gun"

my_weapon_list = {blue_machine_gun,
               purple_minigun,
	       green_missile_launcher,
	       blue_missile_launcher,
	       orange_missile_launcher,
	       blue_angle_minigun,
	       green_angle_machine_gun}

--[[ BADDIE GUNS --]]

baddie_green_gun = Loadwith(baddie_gun, green_bullet)
baddie_green_gun.gun_name = "baddie_green_gun"

baddie_purple_gun = Loadwith(baddie_gun, purple_bullet)
baddie_purple_gun.gun_name = "baddie_purple_gun"

baddie_orange_gun = Loadwith(baddie_gun, orange_bullet)
baddie_orange_gun.gun_name = "baddie_orange_gun"

baddie_blue_gun = Loadwith(baddie_gun, blue_bullet)
baddie_blue_gun.gun_name = "baddie_blue_gun"


enemy_weapon_list = {baddie_green_gun,
		     baddie_purple_gun,
		     baddie_orange_gun,
		     baddie_blue_gun}

function ListConcat(t1,t2)
    for i=1,#t2 do
        t1[#t1+1] = t2[i]
    end
    return t1
end

weapon_list = ListConcat(my_weapon_list, enemy_weapon_list)