function ListConcat(t1,t2)
    for i=1,#t2 do
        t1[#t1+1] = t2[i]
    end
    return t1
end

-- list of image names and paths --
bullet_images = {{name="tri_bullet",path="image/tri_bullet.png", width = 16, height = 16},
	         {name="circle_bullet",path="image/circle_bullet.png", width = 8, height = 8},
		 {name="tiny_bullet",path="image/tiny_bullet.png", width = 4, height = 4}}

for u,v in pairs(bullet_images) do
    v.alpha = 240
end


ship_images = {{name="ship_image", path="image/ship_geom/geo_ship.png"},
	       {name="ship_imageL", path="image/ship_geom/geo_shipL.png"},
	       {name="ship_imageLL", path="image/ship_geom/geo_shipLL.png"},
	       {name="ship_imageR", path="image/ship_geom/geo_shipR.png"},
	       {name="ship_imageRR", path="image/ship_geom/geo_shipRR.png"}}

for u,v in pairs(ship_images) do
    v.width = 80
    v.height = 100
    v.alpha = 240
end

enemy_images = {{name="tri_enemy", path="image/tri_enemy.png"}}

for u,v in pairs(enemy_images) do
    v.width = 80
    v.height = 40
    v.alpha = 240
end

background_images = {{name="background",path="image/background.png",width=959,height=799, alpha = 255}}

images = ListConcat(ListConcat(ListConcat(bullet_images, ship_images), enemy_images), background_images)



-- Old Ship
--[[
ship_images = {{name="ship_image", path="image/ship/ship.png"},
	       {name="ship_imageL", path="image/ship/shipL.png"},
	       {name="ship_imageLL", path="image/ship/shipLL.png"},
	       {name="ship_imageR", path="image/ship/shipR.png"},
	       {name="ship_imageRR", path="image/ship/shipRR.png"}}

for u,v in pairs(ship_images) do
    v.width = 94
    v.height = 100
    v.alpha = 240
end
--]]