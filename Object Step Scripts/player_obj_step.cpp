DELTA_T_SCALE = 100000;
TILT_SCALE = 10;

// Check Orientation and get gyro-input
if display_get_orientation() = display_landscape
{
    x_tilt = -(device_get_tilt_y());
}
else
{
    x_tilt = device_get_tilt_x();
}
y_tilt = device_get_tilt_z();

// Check for and resolve *UP* Input & Collisions
if (vNegSpeed > 0 || y_tilt > 0)
{
    if place_meeting(x, y - (vNegSpeed * (delta_time / DELTA_T_SCALE)), block_obj)
    {
        while (!place_meeting(x, y-1, block_obj))
        {
            y -= 1;
        }
        if (vNegSpeed >= bounceSpeed)
        {
            vPosSpeed = vNegSpeed / 4;
        }
        vNegSpeed = 0;
    }
    else if (y_tilt > 0)
    {
        if (!place_meeting(x, y-1, block_obj))
        {
            if (vNegSpeed < maxSpeed) vNegSpeed += (accelSpeed * abs(y_tilt * TILT_SCALE));
        }
    }
    else
    {
        if (vNegSpeed > 0)
        {
            vNegSpeed -= 2;
        }
        else
        {
            vNegSpeed = 0;
        }
    }
}
// Check for and resolve *DOWN* Input & Collisions
if (vPosSpeed > 0 || y_tilt < 0)
{
    if place_meeting(x, y + (vPosSpeed * (delta_time / DELTA_T_SCALE)), block_obj)
    {
        while (!place_meeting(x, y+1, block_obj))
        {
            y -= 1;
        }
        if (vPosSpeed >= bounceSpeed)
        {
            vNegSpeed = vPosSpeed / 4;
        }
        vPosSpeed = 0;
    }
    else if (y_tilt > 0)
    {
        if (!place_meeting(x, y+1, block_obj))
        {
            if (vPosSpeed < maxSpeed) vPosSpeed += (accelSpeed * abs(y_tilt * TILT_SCALE));
        }
    }
    else
    {
        if (vPosSpeed > 0)
        {
            vPosSpeed -= 2;
        }
        else
        {
            vPosSpeed = 0;
        }
    }
}

// Check for and resolve *LEFT* Input & Collisions
if (hNegSpeed > 0 || x_tilt > 0)
{
    if place_meeting(x - (hNegSpeed * (delta_time / DELTA_T_SCALE)), y, block_obj)
    {
        while (!place_meeting(x-1, y, block_obj))
        {
            x -= 1;
        }
        if (hNegSpeed >= bounceSpeed)
        {
            hPosSpeed = hNegSpeed / 4;
        }
        hNegSpeed = 0;
    }
    else if (x_tilt > 0)
    {
        if (!place_meeting(x-1, y, block_obj))
        {
            if (hNegSpeed < maxSpeed) hNegSpeed += (accelSpeed * abs(x_tilt * TILT_SCALE));
        }
    }
    else
    {
        if (hNegSpeed > 0)
        {
            hNegSpeed -= 2;
        }
        else
        {
            hNegSpeed = 0;
        }
    }
}

// Check for and resolve *RIGHT* Input & Collisions
if (hPosSpeed > 0 || x_tilt < 0)
{
    if place_meeting(x + (hPosSpeed * (delta_time / DELTA_T_SCALE)), y, block_obj)
    {
        while (!place_meeting(x+1, y, block_obj))
        {
            x += 1;
        }
        if (hPosSpeed >= bounceSpeed)
        {
            hNegSpeed = hPosSpeed / 4;
        }
        hPosSpeed = 0;
    }
    else if (x_tilt > 0)
    {
        if (!place_meeting(x+1, y, block_obj))
        {
            if (hPosSpeed < maxSpeed) hPosSpeed += (accelSpeed * abs(x_tilt * TILT_SCALE));
        }
    }
    else
    {
        if (hPosSpeed > 0)
        {
            hPosSpeed -= 2;
        }
        else
        {
            hPosSpeed = 0;
        }
    }
}

// Update player_obj position according to momentum
x = (hPosSpeed - hNegSpeed) * (delta_time / DELTA_T_SCALE);
y = (vPosSpeed - vNegSpeed) * (delta_time / DELTA_T_SCALE);