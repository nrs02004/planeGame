--[[ FIX BY SUBTRACTING HALF OF HEIGHT AND WIDTH --]]

tri_hitboxes = {{x = 10-40, y = 4-20, r = 5},
	      	 {x = 23-40, y = 9-20, r = 10},
		 {x = 39-40, y = 9-20, r = 10},
		 {x = 55-40, y = 9-20, r = 10},
		 {x = 68-40, y = 4-20, r = 5},
		 {x = 39-40, y = 26-20, r = 10}}


green_baddie={speed = 200,
              life = 50,
              cool_down_length = 50,
              name = "tri_enemy",
	      color = "green",
	      hitboxes = tri_hitboxes}

blue_baddie={speed = 200,
             life = 100,
             cool_down_length = 50,
             name = "tri_enemy",
	     color = "blue",
	     hitboxes = tri_hitboxes}

purple_baddie={speed = 200,
               life = 20,
               cool_down_length = 40,
               name = "tri_enemy",
	       color = "purple",
	       hitboxes = tri_hitboxes}

orange_baddie={speed = 200,
               life = 80,
               cool_down_length = 20,
               name = "tri_enemy",
	       color = "orange",
	       hitboxes = tri_hitboxes}

-- Creates a baddie with given x and y position --
function create(baddie, x, y)
  local bad = {}
  for k,v in pairs(baddie) do
    bad[k] = v
  end
  bad.x = x; bad.y = y
  return bad
end

-- makes a copy with y_val of all enemies increased by fixed amount
function push_back(enemies, y_push)
  local enems = {}
  for u,v in pairs(enemies) do
      enems[u] = v
      enems[u].y = enems[u].y + y_push
  end
  return enems
end

-- Creates a V-formation --
function Vformation(x_start, y_start, del_x, del_y, num, baddie)
  local enemies = {}
  count = 1
  for i=1,num do
    enemies[count] = create(baddie,
                            x_start + (i-1)*del_x,
			    y_start + (i-1)*del_y)
    count = count + 1

    enemies[count] = create(baddie,
                            x_start - (i-1)*del_x,
			    y_start + (i-1)*del_y)
    count = count + 1
  end
  return enemies
end

-- Creates half-V-formation --
function hVformation(x_start, y_start, del_x, del_y, num, baddie)
  local enemies = {}
  for count=1,num do
    enemies[count] = create(baddie,
                            x_start + (count-1)*del_x,
			    y_start + (count-1)*del_y)
  end
  return enemies
end


-- Creates horizontal-formation --
function hformation(x_start, y_start, del_x, num, baddie)
  local enemies = {}
  for count=1,num do
    enemies[count] = create(baddie,
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


function deepcopy(orig)
    local orig_type = type(orig)
    local copy
    if orig_type == 'table' then
        copy = {}
        for orig_key, orig_value in next, orig, nil do
            copy[deepcopy(orig_key)] = deepcopy(orig_value)
        end
        setmetatable(copy, deepcopy(getmetatable(orig)))
    else -- number, string, boolean, etc
        copy = orig
    end
    return copy
end