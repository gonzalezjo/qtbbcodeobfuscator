local punctuation = {
	".",
	",",
	"?",
	"!",
	"`",
	"'",
	"\"",
	";",
	":",
	"/",
}
function main(message, opened)
	local addition = punctuation[math.random(#punctuation)]

	if message == " " then
		if math.random(4) == 2 then
			return addition .. " "
		end

		if math.random(4) == 2 then
			return (" %s "):format(addition)
		end

		if math.random(4) == 2 then
			return " " .. addition
		end

		return addition;
	end

end