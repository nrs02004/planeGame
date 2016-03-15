dofile("objects/guns.lua")

purple_machine_gun = Loadwith(machine_gun, blue_pellet)
purple_machine_gun.gun_name = "purple_machine_gun"

blue_minigun_L = Loadwith(minigun_L, purple_pea)
blue_minigun_L.gun_name = "blue_minigun_L"

blue_minigun_R = Loadwith(minigun_R, purple_pea)
blue_minigun_R.gun_name = "blue_minigun_R"

green_missile_launcher = Loadwith(missle_launcher, green_missile)
green_missile_launcher.gun_name = "green_missile_launcher"

weapon_list = {purple_machine_gun,
               blue_minigun_R, blue_minigun_L,
	       green_missile_launcher}