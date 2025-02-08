-- BOID_COUNT = 200;

WALL_DISTANCE = 24
WALL_WEIGHT = 100
WALL_SCALE = 32
HALF_WALL_SCALE = WALL_SCALE / 2

MIN_SPEED = 0.1
MAX_SPEED = 10

S_COEF = 0.2
A_COEF = 0.5
C_COEF = 0.5

neighbour_entity_buffer = { {} }
asset_guids = { 
    "02783a6c-6300-4547-bb18-e119b45fee9d",
    "b0518fbc-9ab8-462f-a6a1-43308f1b114d", 
    "ae2f651b-03f6-49ed-8a17-bb75fa7b1769" } 

function init_boids(narechi__scene__component__position, narechi__scene__component__sprite, boid)
    local pos = narechi__scene__component__position
    pos:set_depth(2)
    pos:set_vec2(vec2(math.random(), math.random()))

    local sprite = narechi__scene__component__sprite
    sprite:set_str("texture_asset_guid", asset_guids[math.random(1, 3)])

    -- local vel = boid:get_vec2()
    -- boid:set_float(math.random())
    -- boid:set_float(1, math.random())
    boid:set_depth(2)
    boid:set_vec2(1, vec2((math.random() * 2) - 1, (math.random() * 2) - 1))

    -- boid:set_vec2(1, vec2(math.random(), math.random()))

    -- pos:set_vec2(vec2(2, 2))
end

function update_boid_movement(narechi__scene__component__position, narechi__scene__component__rotation, boid)
    function clamp(x, min, max)
        if x < min then return min end
        if x > max then return max end
        return x
    end

    local position_component = narechi__scene__component__position
    position_component:set_depth(2)
    local rotation_component = narechi__scene__component__rotation
    rotation_component:set_depth(1)

    boid:set_depth(2)

    local pos = position_component:get_vec2()

    local vel = boid:get_vec2()
    local acc = boid:get_vec2(1)

    local fixed_delta_time = math.min(delta_time, 0.2)

    vel = vel + acc * fixed_delta_time

    local dir = vel:normalize()
    local speed = vel:length()

    vel = dir * clamp(speed, MIN_SPEED, MAX_SPEED)
    pos = pos + vel * fixed_delta_time

    rotation_component:set_float(math.atan(dir.y, dir.x) * (180 / math.pi))

    -- print("test")

    -- Set position
    position_component:set_vec2(pos)

    -- Set velocity
    boid:set_vec2(vel)
    boid:set_vec2(1, acc)
end

function update_boid_wall(narechi__scene__component__position, boid)
    function accel_against_wall(dist, dir, thresh, weight)
        if dist < thresh then
            return dir * (weight / math.abs(dist / thresh))
        else
            return vec2(0)
        end
    end

    local u = vec2(0, 1)
    local d = vec2(0, -1)
    local l = vec2(-1, 0)
    local r = vec2(1, 0)

    local thresh = WALL_DISTANCE
    local weight = WALL_WEIGHT

    local position_component = narechi__scene__component__position
    position_component:set_depth(2)
    local pos = position_component:get_vec2()

    boid:set_depth(2)
    local acc = boid:get_vec2(1)

    acc = acc +
        accel_against_wall(-HALF_WALL_SCALE - pos.x, r, thresh, weight) +
        accel_against_wall(-HALF_WALL_SCALE - pos.y, u, thresh, weight) +
        accel_against_wall(HALF_WALL_SCALE - pos.x, l, thresh, weight) +
        accel_against_wall(HALF_WALL_SCALE - pos.y, d, thresh, weight)

    boid:set_vec2(1, acc)
end

-- function update_neighbour_buffer(boid, spatial_query_result)
--     neighbour_entity_buffer
--     e.remove(spatial_query_result)
-- end
