function ListConcat(t1,t2)
    for i=1,#t2 do
        t1[#t1+1] = t2[i]
    end
    return t1
end

-- list of image names and paths --
bullet_images = {{name="bullet_image",path="image/bul_tri_purple.png", width = 20, height = 40}}

ship_images = {{name="ship_image", path="image/ship/ship.png"},
	       {name="ship_imageL", path="image/ship/shipL.png"},
	       {name="ship_imageLL", path="image/ship/shipLL.png"},
	       {name="ship_imageR", path="image/ship/shipR.png"},
	       {name="ship_imageRR", path="image/ship/shipRR.png"}}

for u,v in pairs(ship_images) do
    v.width = 94
    v.height = 100
end

enemy_images = {{name="enemy_image", path="image/enemy.png", width=71, height=77}}

background_images = {{name="background",path="image/background.png",width=0,height=0}}

images = ListConcat(ListConcat(ListConcat(bullet_images, ship_images), enemy_images), background_images)