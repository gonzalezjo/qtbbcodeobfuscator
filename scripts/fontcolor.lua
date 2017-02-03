function main(message, opened)
    local color = ""
    local random

    for i = 1, 6 do
        random = math.random(48, 70)
        random = random - ((random > 57 and random < 65) and 7 or 0)
        color = (color .. string.char(random)) -- random hex!
    end

    return not opened and "[color=#"..color.."]"..message or message.."[/color]"
end