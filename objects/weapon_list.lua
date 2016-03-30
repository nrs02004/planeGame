dofile("objects/guns.lua")

purple_machine_gun = Loadwith(machine_gun, blue_pellet)
purple_machine_gun.gun_name = "purple_machine_gun"

blue_minigun_L = Loadwith(minigun_L, purple_pea)
blue_minigun_L.gun_name = "blue_minigun_L"

blue_minigun_R = Loadwith(minigun_R, purple_pea)
blue_minigun_R.gun_name = "blue_minigun_R"

green_missile_launcher = Loadwith(missile_launcher, green_missile)
green_missile_launcher.gun_name = "green_missile_launcher"

blue_missile_launcher = Loadwith(wide_missile_launcher, blue_missile)
blue_missile_launcher.gun_name = "blue_missile_launcher"

orange_missile_launcher = Loadwith(double_wide_missile_launcher, orange_missile)
orange_missile_launcher.gun_name = "orange_missile_launcher"

my_weapon_list = {purple_machine_gun,
               blue_minigun_R, blue_minigun_L,
	       green_missile_launcher,
	       blue_missile_launcher,
	       orange_missile_launcher}

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