dofile("objects/guns.lua")

green_machine_gun = Loadwith(machine_gun, green_bullet)
green_machine_gun.gun_name = "green_machine_gun"

green_missile_launcher = Loadwith(missle_launcher, green_missile)
green_missile_launcher.gun_name = "green_missile_launcher"

weapon_list = {green_machine_gun, green_missile_launcher}