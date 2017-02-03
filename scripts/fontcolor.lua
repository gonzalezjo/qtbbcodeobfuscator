function main(message, opened)
    local color = "#"
    local random

    --[[ 
    -- my method of generating random color codes
    -- apologies if it's confusing
    -- but i didn't like any of the methods online
    -- so i had to make my own 
    -- i tried to add comments though
    ]]-- 
    
    for i = 1, 6 do 
        -- random ascii code for 0 - F
        random = math.random(48, 70) 
        -- ignore colons, semicolons, etc
        random = random - ((random > 57 and random < 65) and 7 or 0) 
        -- append it to the color code
        color = color .. string.char(random)
    end

    -- open or close the tag appropriately
    return opened and "[color="..color.."]"..message or message.."[/color]"
end
