local substitutions = setmetatable(
{
	["a"] = 4,
	["b"] = 8,
	["e"] = 3,
	["g"] = 6,
	["l"] = 1,
	["o"] = 0,
	["s"] = 5,
	["t"] = 7,
},
{
	__index = function(self, value)
		return rawget(self, value:lower()) or value
	end
})

function main(message, opened)
	return substitutions[message]
end