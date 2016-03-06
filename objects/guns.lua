slow_speed = 150.0
fast_speed = 800.0

fast_accel = 1600.0

machine_gun={alternate = 1,
	     portWidth = 0,
	     fireport = 1,
	     cool_down_length = 0.1}

missle_launcher={alternate = -1,
		 portWidth = 25.0,
		 fireport = 1,
		 cool_down_length = 0.3}
		 
green_bullet={bullet_init_speed_x = 0.0,
	      bullet_init_speed_y = fast_speed,
	      bullet_accel_x = 0,
	      bullet_accel_y = 0,
	      bullet_dmg = 1.0,
	      bullet_name="bullet_image"}

green_missile={bullet_init_speed_x = 0.0,
	      bullet_init_speed_y = slow_speed,
	      bullet_accel_x = 0,
	      bullet_accel_y = fast_accel,
	      bullet_dmg = 50.0,
	      bullet_name="bullet_image"}


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