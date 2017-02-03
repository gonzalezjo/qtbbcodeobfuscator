local sizes = {
    "xx-small",
    "x-small",
    "small",
    "medium",
    "large",
    "xx-large",
}

function main(message, opened)
	if opened then
		return ("[size=%s]%s"):format(sizes[math.random(#sizes)], message)
	else
		return message .. "[/size]"
	end
end