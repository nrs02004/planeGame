function ListConcat(t1,t2)
    for i=1,#t2 do
        t1[#t1+1] = t2[i]
    end
    return t1
end

-- list of image names and paths --
bullet_images = {{name="purple_bullet",path="image/bul_tri_purple.png", width = 16, height = 16},
		 {name="green_bullet",path="image/bul_tri_green.png", width = 16, height = 16},
		 {name="blue_bullet",path="image/bul_tri_blue.png", width = 20, height = 16},
		 {name="orange_bullet",path="image/bul_tri_orange.png", width = 16, height = 16}}

ship_images = {{name="ship_image", path="image/ship/ship.png"},
	       {name="ship_imageL", path="image/ship/shipL.png"},
	       {name="ship_imageLL", path="image/ship/shipLL.png"},
	       {name="ship_imageR", path="image/ship/shipR.png"},
	       {name="ship_imageRR", path="image/ship/shipRR.png"}}

for u,v in pairs(ship_images) do
    v.width = 94
    v.height = 100
end

enemy_images = {{name="enemy_image", path="image/enemy.png", width=80, height=40},
	        {name="green_tri_enemy", path="image/green_triangle.png", width=80, height=40},
		{name="orange_tri_enemy", path="image/orange_triangle.png", width=80, height=40},
		{name="purple_tri_enemy", path="image/purple_triangle.png", width=80, height=40},
		{name="blue_tri_enemy", path="image/blue_triangle.png", width=80, height=40}}

background_images = {{name="background",path="image/background.png",width=959,height=799}}

images = ListConcat(ListConcat(ListConcat(bullet_images, ship_images), enemy_images), background_images)