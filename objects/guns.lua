slow_speed = 150.0
fast_speed = 800.0
enemy_speed = 500.0

fast_accel = 1600.0

bullet_hitboxes={{x=8-8, y=11-8, r=4},
		 {x=8-8, y=4-8, r=4}}

pea_hitboxes={{x=2-2, y=2-2, r=2}}

pellet_hitboxes={{x=4-4, y=3-4, r=4}}

machine_gun={alternate = -1,
	     portWidth = 25,
	     fireport = 1,
	     cool_down_length = 0.15}
	     
minigun={alternate = 2,
	 portWidth = -10,
	 fireport = 1,
	 cool_down_length = 0.05}	

minigun_L={alternate = 1,
	     portWidth = -10,
	     fireport = 1,
	     cool_down_length = 0.05}

minigun_R={alternate = 1,
	     portWidth = 10,
	     fireport = 1,
	     cool_down_length = 0.05}

missile_launcher={alternate = -1,
		 portWidth = 30.0,
		 fireport = 1,
		 cool_down_length = 0.3}


narrow_missile_launcher={alternate = -1,
		      portWidth = 15.0,
		      fireport = 1,
		      cool_down_length = 0.4}

baddie_gun={alternate = 1,
	    portWidth = 0.0,
 	    fireport = 0,
  	    cool_down_length = 3}

green_bullet={bullet_init_speed_x = 0.0,
	      bullet_init_speed_y = enemy_speed,
	      bullet_accel_x = 0,
	      bullet_accel_y = 0,
	      bullet_dmg = 100.0,
	      bullet_name="tri_bullet",
	      bullet_color = "green",
	      hitboxes = bullet_hitboxes}


purple_bullet={bullet_init_speed_x = 0.0,
	      bullet_init_speed_y = enemy_speed,
	      bullet_accel_x = 0,
	      bullet_accel_y = 0,
	      bullet_dmg = 3.0,
	      bullet_name="tri_bullet",
	      bullet_color = "purple",
	      hitboxes = bullet_hitboxes}

blue_bullet={bullet_init_speed_x = 0.0,
	      bullet_init_speed_y = enemy_speed,
	      bullet_accel_x = 0,
	      bullet_accel_y = 0,
	      bullet_dmg = 5.0,
	      bullet_name="tri_bullet",
	      bullet_color = "blue",
	      hitboxes = bullet_hitboxes}

orange_bullet={bullet_init_speed_x = 0.0,
	      bullet_init_speed_y = enemy_speed,
	      bullet_accel_x = 0,
	      bullet_accel_y = 0,
	      bullet_dmg = 10.0,
	      bullet_name="tri_bullet",
	      bullet_color = "orange",
	      hitboxes = bullet_hitboxes}


blue_pellet={bullet_init_speed_x = 0.0,
             bullet_init_speed_y = fast_speed,
             bullet_accel_x = 0,
             bullet_accel_y = 0,
             bullet_dmg = 10.0,
             bullet_name="circle_bullet",
             bullet_color = "blue",
	     hitboxes = pellet_hitboxes}

purple_pea={bullet_init_speed_x = 0.0,
             bullet_init_speed_y = fast_speed,
             bullet_accel_x = 0,
             bullet_accel_y = 0,
             bullet_dmg = 5.0,
             bullet_name="tiny_bullet",
             bullet_color = "purple",
	     hitboxes = pea_hitboxes}


green_missile={bullet_init_speed_x = 15.0,
	      bullet_init_speed_y = slow_speed,
	      bullet_accel_x = 0,
	      bullet_accel_y = fast_accel,
	      bullet_dmg = 50.0,
	      bullet_name="tri_bullet",
	      bullet_color = "green",
	      hitboxes = bullet_hitboxes}

blue_missile={bullet_init_speed_x = 150.0,
	      bullet_init_speed_y = -slow_speed,
	      bullet_accel_x = 0,
	      bullet_accel_y = fast_accel/2,
	      bullet_dmg = 50.0,
	      bullet_name="tri_bullet",
	      bullet_color = "blue",
	      hitboxes = bullet_hitboxes}

orange_missile={bullet_init_speed_x = 60.0,
	      bullet_init_speed_y = slow_speed/2,
	      bullet_accel_x = 0,
	      bullet_accel_y = fast_accel,
	      bullet_dmg = 50.0,
	      bullet_name="tri_bullet",
	      bullet_color = "orange",
	      hitboxes = bullet_hitboxes}

blue_angle_pea={bullet_init_speed_x = fast_speed/2,
                bullet_init_speed_y = fast_speed,
                bullet_accel_x = 0,
                bullet_accel_y = 0,
                bullet_dmg = 2.0,
                bullet_name="tiny_bullet",
                bullet_color = "blue",
	        hitboxes = pea_hitboxes}

green_angle_pellet={bullet_init_speed_x = fast_speed/2,
             bullet_init_speed_y = fast_speed,
             bullet_accel_x = 0,
             bullet_accel_y = 0,
             bullet_dmg = 10.0,
             bullet_name="circle_bullet",
             bullet_color = "green",
	     hitboxes = pellet_hitboxes}

-- combining lists --
function ListConcat(t1,t2)
    for i=1,#t2 do
        t1[#t1+1] = t2[i]
    end
    return t1
end

--combining a gun type with a bullet type
function Loadwith(gun, bullet)
	 local ggun = {}
	 for k,v in pairs(gun) do
	     ggun[k] = v
	 end
	 for k,v in pairs(bullet) do
	     ggun[k] = v
	 end
	 return ggun
end