normal_baddie={speed = 200,
	       life = 50,
               cool_down_length = 50,
               image_file = "enemy.png"}

-- Creates a baddie with given x and y position --
function create(baddie, x, y)
  local bad = {}
  for k,v in pairs(baddie) do
    bad[k] = v
  end
  bad.x = x; bad.y = y
  return bad
end


-- Creates a V-formation --
function Vformation(x_start, y_start, del_x, del_y, num)
  local enemies = {}
  count = 1
  for i=1,num do
    enemies[count] = create(normal_baddie,
                            x_start + (i-1)*del_x,
			    y_start + (i-1)*del_y)
    count = count + 1

    enemies[count] = create(normal_baddie,
                            x_start - (i-1)*del_x,
			    y_start + (i-1)*del_y)
    count = count + 1
  end
  return enemies
end

-- Creates half-V-formation --
function hVformation(x_start, y_start, del_x, del_y, num)
  local enemies = {}
  for count=1,num do
    enemies[count] = create(normal_baddie,
                            x_start + (count-1)*del_x,
			    y_start + (count-1)*del_y)
  end
  return enemies
end


-- Creates horizontal-formation --
function hformation(x_start, y_start, del_x, num)
  local enemies = {}
  for count=1,num do
    enemies[count] = create(normal_baddie,
                            x_start + (count-1)*del_x,
			    y_start)
  end
  return enemies
end


-- SOME UTILITY FUNCTIONS --


-- combining lists --
function ListConcat(t1,t2)
    for i=1,#t2 do
        t1[#t1+1] = t2[i]
    end
    return t1
end
