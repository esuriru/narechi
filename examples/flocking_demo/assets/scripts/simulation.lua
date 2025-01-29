-- BOID_COUNT = 200;

S_COEF = 0.2;
A_COEF = 0.5;
C_COEF = 0.5;

function boid_movement(narechi__scene__component__position, boid)
    local pos = narechi__scene__component__position
    pos:set_depth(2)

    boid:set_depth(2)
    pos:set_vec2(pos:get_vec2() + boid:get_vec2())
end