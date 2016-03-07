green_baddie={speed = 200,
              life = 50,
              cool_down_length = 50,
              name = "green_tri_enemy"}

blue_baddie={speed = 200,
             life = 100,
             cool_down_length = 50,
             name = "blue_tri_enemy"}

purple_baddie={speed = 200,
               life = 20,
               cool_down_length = 40,
               name = "purple_tri_enemy"}

orange_baddie={speed = 200,
               life = 80,
               cool_down_length = 20,
               name = "orange_tri_enemy"}

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